//
// Created by chao on 2017/11/22.
//

#ifndef M1_ANDROID_M1DECODER_H
#define M1_ANDROID_M1DECODER_H

#include <jni.h>
#include <iostream>

using namespace std;

#define M1_DECODER_MAX_PLANE_SIZE 3

#define M1_DECODER_MAX_DECODER_SIZE 4

typedef enum M1ColorFormat {
    M1ColorFormat_YUV420P,
    M1ColorFormat_MEDIACODEC,
} M1ColorFormat;

typedef struct M1DecoderFrame {
    uint8_t *data[M1_DECODER_MAX_PLANE_SIZE];
    int linesize[M1_DECODER_MAX_PLANE_SIZE];
    int width;
    int height;
    int planes;
    M1ColorFormat colorFormat;
} M1DecoderFrame;

typedef enum M1DecoderState {
    M1DecoderState_PREPARED,
    M1DecoderState_PLAYING,
    M1DecoderState_ERROR,
    M1DecoderState_STOP
} M1DecoderState;

class IM1DecoderListener {
public:
    IM1DecoderListener() {}
    virtual ~IM1DecoderListener() {}
    virtual void onM1DecoderStateChanged(M1DecoderState state) = 0;
    virtual void onM1DecoderFramesChanged(M1DecoderFrame frames[M1_DECODER_MAX_DECODER_SIZE]) = 0;
};

class M1DecoderPrivate;

class M1Decoder {
private:
    M1DecoderPrivate *m1DecoderPrivate;
public:
    M1Decoder();

    ~M1Decoder();

    void setMediaCodec(JNIEnv *env, jobjectArray jArrayMediaCodec);

    void setM1DecoderListener(IM1DecoderListener *listener);

    void start(const char *url, bool isHwDecoder = false);

    void refresh();

    void close();
};

#endif //M1_ANDROID_M1DECODER_H
