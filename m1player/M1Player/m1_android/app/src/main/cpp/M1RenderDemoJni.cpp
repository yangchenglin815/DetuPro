//
// Created by chao on 2017/11/23.
//

#include "com_detu_m1decoderdemo_M1FourRender.h"
#include "M1Decoder.h"
#include "ijksdl_log.h"

/*
 * Class:     com_detu_m1decoderdemo_M1FourRender
 * Method:    _init
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_detu_m1decoderdemo_M1FourRender__1init
        (JNIEnv *env, jobject jObj) {
    jclass jClassM1Decoder = env->GetObjectClass(jObj);
    jfieldID jFieldIdNativeRef = env->GetFieldID(jClassM1Decoder, "nativeRef", "J");
    M1Decoder *decoder = new M1Decoder;
    env->SetLongField(jObj, jFieldIdNativeRef, (long) decoder);
}

class M1DecoderListenerImpl : public IM1DecoderListener {
public:
    M1DecoderListenerImpl() {

    }

    ~M1DecoderListenerImpl() {

    }

    void onM1DecoderStateChanged(M1DecoderState state) {
        switch (state) {
            case M1DecoderState_ERROR:
                ALOGE("this is the onM1DecoderStateChanged error");
                break;
        }
    }

    void onM1DecoderFramesChanged(M1DecoderFrame frames[M1_DECODER_MAX_DECODER_SIZE]) {

    }
};

/*
 * Class:     com_detu_m1decoderdemo_M1FourRender
 * Method:    _start
 * Signature: (JLjava/lang/String;Z[Lcom/detu/m1decoder/MediaCodecH264;)V
 */
JNIEXPORT void JNICALL Java_com_detu_m1decoderdemo_M1FourRender__1start
        (JNIEnv *env, jobject jObj, jlong jNativeRef, jstring jUrl, jboolean jIsHwDecoder,
         jobjectArray jArrayMediaCodec) {
    M1Decoder *decoder = static_cast<M1Decoder *>((void *) jNativeRef);
    if (decoder != NULL) {
        decoder->setMediaCodec(env, jArrayMediaCodec);
        const char *url = env->GetStringUTFChars(jUrl, 0);
        decoder->setM1DecoderListener(new M1DecoderListenerImpl);
        decoder->start(url, jIsHwDecoder);
        env->ReleaseStringUTFChars(jUrl, url);
    }
}

/*
 * Class:     com_detu_m1decoderdemo_M1FourRender
 * Method:    _refresh
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_detu_m1decoderdemo_M1FourRender__1refresh
        (JNIEnv *env, jobject jObj, jlong jNativeRef) {
    M1Decoder *decoder = static_cast<M1Decoder *>((void *) jNativeRef);
    if (decoder != NULL) {
       decoder->refresh();
    }
}

/*
 * Class:     com_detu_m1decoderdemo_M1FourRender
 * Method:    _close
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_detu_m1decoderdemo_M1FourRender__1close
        (JNIEnv *env, jobject jObj, jlong jNativeRef) {
    M1Decoder *decoder = static_cast<M1Decoder *>((void *) jNativeRef);
    if (decoder != NULL) {
        decoder->close();
    }
}

/*
 * Class:     com_detu_m1decoderdemo_M1FourRender
 * Method:    _finalize
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_detu_m1decoderdemo_M1FourRender__1finalize
        (JNIEnv *env, jobject jObj, jlong jNativeRef) {
    M1Decoder *decoder = static_cast<M1Decoder *>((void *) jNativeRef);
    if (decoder != NULL) {
        delete decoder;
    }
}
