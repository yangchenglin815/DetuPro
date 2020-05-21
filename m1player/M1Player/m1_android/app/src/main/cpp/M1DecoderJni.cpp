//
// Created by chao on 2017/11/20.
//

#include "com_detu_m1decoder_M1Decoder.h"
#include "Error.h"
#include "Global.h"
#include "M1Player.h"
#include "IGenerator.h"
#include "FfmpegH264Decoder.h"
#include "MediaCodecDecoder.h"

class AndroidDecoderGenerator : public IGenerator {
private:
    int mIndex;
    MediaCodecDecoder *mDecoders[4];
public:
    AndroidDecoderGenerator() {
        memset(mDecoders, 0, sizeof(mDecoders));
        mIndex = 0;
    }

    ~AndroidDecoderGenerator() {

    }

    void setMediaCodecDecoder(int index, MediaCodecDecoder* decoder) {
        mDecoders[index] = decoder;
    }

    H264DecoderBase *generateDecoderByType(decode_type_e type) {
        H264DecoderBase *decoder = NULL;
        if (type == DecodeTypeMediaCodec) {
            decoder = mDecoders[mIndex];
            mIndex += 1;
            if (mIndex == 3) {
                mIndex = 0;
            }
        } else if (type == DecodeTypeSoft) {
            decoder = new FfmpegH264Decoder;
        }
        return decoder;
    }
};

class CM1PlayerJni {
public:
    CM1Player *m1Player;
    IGenerator* decoderGenerator;
    jobjectArray jArraySurface;
public:
    void onGetFrames(m1_video_frame_s **video, int index, unsigned int timestamp) {

    }
};

/*
 * Class:     com_detu_m1decoder_M1Decoder
 * Method:    _setMediaCodecH264
 * Signature: ([Lcom/detu/m1decoder/MediaCodecH264;)V
 */
JNIEXPORT void JNICALL Java_com_detu_m1decoder_M1Decoder__1setMediaCodecH264
        (JNIEnv *env, jobject jObj, jobjectArray jMediaH264) {
    JavaVM *jvm;
    env->GetJavaVM(&jvm);
    MediaCodecDecoder::setJavaVm(jvm);
    jclass jClassM1Decoder = env->GetObjectClass(jObj);
    jfieldID jFieldIdNativeRef = env->GetFieldID(jClassM1Decoder, "nativeRef", "J");
    CM1PlayerJni *cm1PlayerJni = new CM1PlayerJni;
    cm1PlayerJni->m1Player = new CM1Player;
    cm1PlayerJni->jArraySurface = (jobjectArray) env->NewGlobalRef(jMediaH264);
    AndroidDecoderGenerator *decoderGenerator = new AndroidDecoderGenerator();
    cm1PlayerJni->decoderGenerator = decoderGenerator;
    {
        for (int i = 0; i < 4; i++) {
            jobject jObjMediaH264 = env->GetObjectArrayElement(cm1PlayerJni->jArraySurface, i);
            MediaCodecDecoder *decoder = new MediaCodecDecoder;
            decoder->setMediaCodec(jObjMediaH264);
            decoderGenerator->setMediaCodecDecoder(i, decoder);
        }
    }
    env->SetLongField(jObj, jFieldIdNativeRef, (long) cm1PlayerJni);
}

/*
 * Class:     com_detu_m1decoder_M1Decoder
 * Method:    _start
 * Signature: (JLjava/lang/String;Z)V
 */
JNIEXPORT void JNICALL Java_com_detu_m1decoder_M1Decoder__1start
        (JNIEnv *env, jobject jObj, jlong jNativeRef, jstring jStringUrl, jboolean jIsHwDecoder) {
    CM1PlayerJni *cm1PlayerJni = static_cast<CM1PlayerJni *>((void *) jNativeRef);
    if (cm1PlayerJni == NULL) {
        return;
    }
    CM1Player *cm1Player = cm1PlayerJni->m1Player;
    m1_player_config_s config;
    memset(&config, 0, sizeof(m1_player_config_s));
    const char *url = env->GetStringUTFChars(jStringUrl, 0);
    config.url = url;
    env->ReleaseStringUTFChars(jStringUrl, url);
    config.videoproc = std::bind(&CM1PlayerJni::onGetFrames, cm1PlayerJni, std::placeholders::_1,
                                 std::placeholders::_2, std::placeholders::_3);
    cm1Player->Init(config);
    cm1Player->Play();
}

/*
 * Class:     com_detu_m1decoder_M1Decoder
 * Method:    _stop
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_detu_m1decoder_M1Decoder__1stop
        (JNIEnv *env, jobject jObj, jlong jNativeRef) {
    CM1PlayerJni *cm1PlayerJni = static_cast<CM1PlayerJni *>((void *) jNativeRef);
    if (cm1PlayerJni == NULL) {
        return;
    }
    CM1Player *cm1Player = cm1PlayerJni->m1Player;
}

/*
 * Class:     com_detu_m1decoder_M1Decoder
 * Method:    _refresh
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_detu_m1decoder_M1Decoder__1refresh
        (JNIEnv *env, jobject jObj, jlong jNativeRef) {
    CM1PlayerJni *cm1PlayerJni = static_cast<CM1PlayerJni *>((void *) jNativeRef);
    if (cm1PlayerJni == NULL) {
        return;
    }
    CM1Player *cm1Player = cm1PlayerJni->m1Player;
    cm1Player->RePlay();
}

/*
 * Class:     com_detu_m1decoder_M1Decoder
 * Method:    _close
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_detu_m1decoder_M1Decoder__1close
        (JNIEnv *env, jobject jObj, jlong jNativeRef) {
    CM1PlayerJni *cm1PlayerJni = static_cast<CM1PlayerJni *>((void *) jNativeRef);
    if (cm1PlayerJni == NULL) {
        return;
    }
    CM1Player *cm1Player = cm1PlayerJni->m1Player;
    cm1Player->Close();
}
