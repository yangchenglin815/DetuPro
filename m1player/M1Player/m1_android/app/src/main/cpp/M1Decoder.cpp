//
// Created by chao on 2017/11/22.
//

#include "M1Decoder.h"
#include "Error.h"
#include "Global.h"
#include "M1Player.h"
#include "IGenerator.h"
#include "FfmpegH264Decoder.h"
#include "MediaCodecDecoder.h"
#include <pthread.h>
#include "ijksdl_log.h"
extern "C" {
#include "jni_utils.h"
}

#include "AudioTrackOut.h"
class AndroidDecoderGenerator : public IGenerator {
private:
    int mIndex;
    MediaCodecDecoder *mDecoders[M1_DECODER_MAX_DECODER_SIZE];
public:
    AndroidDecoderGenerator() {
        memset(mDecoders, 0, sizeof(mDecoders));
        mIndex = 0;
    }

    ~AndroidDecoderGenerator() {

    }

    void setMediaCodecDecoder(int index, MediaCodecDecoder *decoder) {
        mDecoders[index] = decoder;
    }

    H264DecoderBase *generateDecoderByType(decode_type_e type) {
        H264DecoderBase *decoder = NULL;
        if (type == DecodeTypeMediaCodec) {
            decoder = mDecoders[mIndex];
            mIndex += 1;
            if (mIndex == M1_DECODER_MAX_DECODER_SIZE) {
                mIndex = 0;
            }
        } else if (type == DecodeTypeSoft) {
            decoder = new FfmpegH264Decoder;
        }
        return decoder;
    }

    IAudioOutBase *generateAudioOut() {
        return new AudioTrackOut;
    }
};

class M1DecoderPrivate {
public:
    AndroidDecoderGenerator *mDecoderGenerator;
    CM1Player *mCm1Player;
    string mUrl;
    bool mIsHwDecoder;
    IM1DecoderListener *mListener;
    M1DecoderFrame cacheFrames[M1_DECODER_MAX_DECODER_SIZE];
    MediaCodecDecoder *mJavaDecoders[M1_DECODER_MAX_DECODER_SIZE];
public:
    M1DecoderPrivate() : mDecoderGenerator(NULL), mListener(NULL), mCm1Player(NULL), mIsHwDecoder(
            true) {
        memset(cacheFrames, 0, sizeof(cacheFrames));
        memset(mJavaDecoders, 0, sizeof(mJavaDecoders));
    }

    ~M1DecoderPrivate() {
        if (mDecoderGenerator != NULL) {
            delete mDecoderGenerator;
            mDecoderGenerator = NULL;
        }
        if (mCm1Player != NULL) {
            delete mCm1Player;
            mCm1Player = NULL;
        }
    }

    void setMediaCodec(JNIEnv *env, jobjectArray jArrayMediaCodec) {
        JavaVM *jvm;
        env->GetJavaVM(&jvm);
        jniUtils_setJavaVm(jvm);
        mDecoderGenerator = new AndroidDecoderGenerator;
        if (jArrayMediaCodec != NULL) {
            const int size = env->GetArrayLength(jArrayMediaCodec);
            for (int i = 0; i < size; i++) {
                jobject jObjMediaH264 = env->GetObjectArrayElement(jArrayMediaCodec, i);
                MediaCodecDecoder *decoder = new MediaCodecDecoder;
                decoder->setMediaCodec(jObjMediaH264);
                mJavaDecoders[i] = decoder;
                mDecoderGenerator->setMediaCodecDecoder(i, decoder);
            }
        }
    }

    void onM1GetMessage(int message_type, long attach) {
        if (message_type == ERROR_SOCKET_READ) {
            //链接成功，但是服务器并没有流，10s到来该消息
            ALOGE("this is m1 connect success, but have not stream!");
            if (mListener != NULL) {
                mListener->onM1DecoderStateChanged(M1DecoderState_ERROR);
            }
        }
    }

    void onGetFrames(m1_video_frame_s **video, int index, unsigned int timestamp) {
        M1DecoderFrame *targetFrame = NULL;
        m1_video_frame_s *srcFrame = NULL;
        for (int i = 0; i < M1_DECODER_MAX_DECODER_SIZE; i++) {
            targetFrame = &cacheFrames[i];
            srcFrame = video[i];
            targetFrame->width = srcFrame->w;
            targetFrame->height = srcFrame->h;
            for (int i = 0; i < M1_DECODER_MAX_PLANE_SIZE; ++i) {
                targetFrame->data[i] = srcFrame->data[i];
                targetFrame->linesize[i] = srcFrame->linesize[i];
            }
            switch (srcFrame->format) {
                case PIX_FMT_YUV420P:
                    targetFrame->colorFormat = M1ColorFormat_YUV420P;
                    break;
                default:
                    targetFrame->colorFormat = M1ColorFormat_MEDIACODEC;
                    break;
            }
            targetFrame->planes = (targetFrame->colorFormat == M1ColorFormat_YUV420P) ? 3 : 1;
        }
        if (mListener != NULL) {
            mListener->onM1DecoderFramesChanged(cacheFrames);
        }
    }

    static void *m1PlayerThreadFunc(void *opaque) {
        M1DecoderPrivate *m1DecoderPrivate = static_cast<M1DecoderPrivate *>(opaque);
        CM1Player *cm1Player = m1DecoderPrivate->mCm1Player;
        if (cm1Player != NULL) {
            cm1Player->Close();
            delete cm1Player;
            m1DecoderPrivate->mCm1Player = NULL;
        }
        cm1Player = new CM1Player;
        cm1Player->setDecoderGenerator(m1DecoderPrivate->mDecoderGenerator);
        m1DecoderPrivate->mCm1Player = cm1Player;
        m1_player_config_s config;
        config.url = m1DecoderPrivate->mUrl;
        config.videoproc = std::bind(&M1DecoderPrivate::onGetFrames, m1DecoderPrivate,
                                     std::placeholders::_1,
                                     std::placeholders::_2, std::placeholders::_3);
        config.messageproc = std::bind(&M1DecoderPrivate::onM1GetMessage, m1DecoderPrivate,
                                       std::placeholders::_1,
                                       std::placeholders::_2);
        int ret = cm1Player->Init(config);
        ALOGE("the cm1player init:%d， url:%s", ret, config.url.c_str());
        if (ret != 0 && m1DecoderPrivate->mListener != NULL) {
            m1DecoderPrivate->mListener->onM1DecoderStateChanged(M1DecoderState_ERROR);
        }
        if (ret != 0) {
            return NULL;
        }
        decode_type_e decoderType = m1DecoderPrivate->mIsHwDecoder ? DecodeTypeMediaCodec
                                                                   : DecodeTypeSoft;
        cm1Player->SetDeocdeType(decoderType);
        cm1Player->Play();
        return NULL;
    }

    void start(const char* url, bool isHwDecoder) {
        //m1 player初始化操作为阻塞操作，放到子线程
        pthread_t m1Thread;
        mUrl = url;
        mIsHwDecoder = isHwDecoder;
        pthread_create(&m1Thread, NULL, &m1PlayerThreadFunc, this);
    }

    void refresh() {
        if (mCm1Player != NULL) {
            mCm1Player->RePlay();
        }
    }

    void close() {
        if (mCm1Player != NULL) {
            mCm1Player->Close();
        }
        MediaCodecDecoder *javaDecoder = NULL;
        for (int i = 0; i < M1_DECODER_MAX_DECODER_SIZE; i++) {
            javaDecoder = mJavaDecoders[i];
            if (javaDecoder != NULL) {
                delete javaDecoder;
            }
        }
        memset(mJavaDecoders, 0, sizeof(mJavaDecoders));
    }
};

M1Decoder::M1Decoder() {
    m1DecoderPrivate = new M1DecoderPrivate;
}

M1Decoder::~M1Decoder() {
    if (m1DecoderPrivate != NULL) {
        delete m1DecoderPrivate;
        m1DecoderPrivate = NULL;
    }
}

void M1Decoder::setMediaCodec(JNIEnv *env, jobjectArray jArrayMediaCodec) {
    if (m1DecoderPrivate != NULL) {
        m1DecoderPrivate->setMediaCodec(env, jArrayMediaCodec);
    }
}

void M1Decoder::start(const char* url, bool isHwDecoder) {
    if (m1DecoderPrivate != NULL) {
        m1DecoderPrivate->start(url, isHwDecoder);
    }
}

void M1Decoder::setM1DecoderListener(IM1DecoderListener *listener) {
    if (m1DecoderPrivate != NULL) {
        m1DecoderPrivate->mListener = listener;
    }
}

void M1Decoder::refresh() {
    if (m1DecoderPrivate != NULL) {
        m1DecoderPrivate->refresh();
    }
}

void M1Decoder::close() {
    if (m1DecoderPrivate != NULL) {
        m1DecoderPrivate->close();
    }
}