//
// Created by chao on 2017/11/20.
//

#include "MediaCodecDecoder.h"
#include <pthread.h>
#include <ijksdl_log.h>

extern "C" {
#include "jni_utils.h"
}

static const char *MEDIACODEC_H264_PATH = "com/detu/m1decoder/MediaCodecH264";

struct MediaCodecDecoderPrivate {
    jobject jObjMediaCodec;
    jmethodID jMethodIdOnGetMediaInfo;
    jmethodID jMethodIdOnGetPacket;
    jfieldID jFieldIdPacketCache;
    jobject jObjPacketCache;
};

MediaCodecDecoder::MediaCodecDecoder() {
    mediaCodecDecoderPrivate = (MediaCodecDecoderPrivate *) calloc(1,
                                                                   sizeof(MediaCodecDecoderPrivate));
}

MediaCodecDecoder::~MediaCodecDecoder() {
    if (mediaCodecDecoderPrivate != NULL) {
        free(mediaCodecDecoderPrivate);
        mediaCodecDecoderPrivate = NULL;
    }
}

int MediaCodecDecoder::InitDecoder(int identityId, unsigned char *spsPpsData, int length, int width,
                                   int height) {
    H264DecoderBase::InitDecoder(identityId, spsPpsData, length, width, height);
    JNIEnv *env = jniUtils_setupThreadEnv();
    jbyteArray jArraySpsPps = env->NewByteArray(length);
    env->SetByteArrayRegion(jArraySpsPps, 0, length, (jbyte *) spsPpsData);
    env->CallVoidMethod(mediaCodecDecoderPrivate->jObjMediaCodec,
                        mediaCodecDecoderPrivate->jMethodIdOnGetMediaInfo, jArraySpsPps, width,
                        height);
    env->DeleteLocalRef(jArraySpsPps);
    jbyteArray jArrayPacketCache = (jbyteArray) env->GetObjectField(
            mediaCodecDecoderPrivate->jObjMediaCodec,
            mediaCodecDecoderPrivate->jFieldIdPacketCache);
    mediaCodecDecoderPrivate->jObjPacketCache = env->NewGlobalRef(jArrayPacketCache);
    jniUtils_detachThreadEnv();
    return 0;
}

int MediaCodecDecoder::DecodeVideo(AVFrame *picture, int *got_picture_ptr, AVPacket *avpkt) {
    JNIEnv *env = jniUtils_setupThreadEnv();
    env->SetByteArrayRegion((jbyteArray) mediaCodecDecoderPrivate->jObjPacketCache, 0, avpkt->size,
                            (const jbyte *) avpkt->data);
    //ALOGE("DecodeVideo, id:%d, key:%d\n", identityId, avpkt->flags == AV_PKT_FLAG_KEY);
    int isKeyFrame = avpkt->flags == AV_PKT_FLAG_KEY ? 1 : 0;
    int ret = env->CallIntMethod(mediaCodecDecoderPrivate->jObjMediaCodec,
                                 mediaCodecDecoderPrivate->jMethodIdOnGetPacket, avpkt->size,
                                 isKeyFrame);
    *got_picture_ptr = ret == 0 ? 1 : 0;
    if(picture != NULL) {
        picture->format = AV_PIX_FMT_MEDIACODEC;
    }
    jniUtils_detachThreadEnv();
    return 0;
}

void MediaCodecDecoder::setMediaCodec(jobject jMediaCodec) {
    JNIEnv *env = jniUtils_setupThreadEnv();
    jclass jClassMediaCodec = env->GetObjectClass(jMediaCodec);
    mediaCodecDecoderPrivate->jObjMediaCodec = env->NewGlobalRef(jMediaCodec);
    mediaCodecDecoderPrivate->jMethodIdOnGetMediaInfo = env->GetMethodID(jClassMediaCodec,
                                                                         "onGetMediaInfo",
                                                                         "([BII)V");
    mediaCodecDecoderPrivate->jMethodIdOnGetPacket = env->GetMethodID(jClassMediaCodec,
                                                                      "onGetPacket",
                                                                      "(II)I");

    mediaCodecDecoderPrivate->jFieldIdPacketCache = env->GetFieldID(jClassMediaCodec,
                                                                    "mPacketCache", "[B");
    jniUtils_detachThreadEnv();
}

void MediaCodecDecoder::CloseDecoder(void) {
    ALOGE("this is the mediacodec decoder close, identityId:%d!", identityId);
    int ret = 0;
    AVPacket packet = {0};
    packet.size = 0;
    packet.pts = 0;
    //通知mediaCodec结束
    DecodeVideo(NULL, &ret, &packet);
    JNIEnv *env = jniUtils_setupThreadEnv();
    if (mediaCodecDecoderPrivate->jObjMediaCodec != NULL) {
        env->DeleteGlobalRef(mediaCodecDecoderPrivate->jObjMediaCodec);
        mediaCodecDecoderPrivate->jObjMediaCodec = NULL;
    }
    if (mediaCodecDecoderPrivate->jObjPacketCache != NULL) {
        env->DeleteGlobalRef(mediaCodecDecoderPrivate->jObjPacketCache);
        mediaCodecDecoderPrivate->jObjPacketCache = NULL;
    }
    jniUtils_detachThreadEnv();
    H264DecoderBase::CloseDecoder();
}