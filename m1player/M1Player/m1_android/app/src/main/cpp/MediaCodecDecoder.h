//
// Created by chao on 2017/11/20.
//

#ifndef M1_ANDROID_MEDIACODECDECODER_H
#define M1_ANDROID_MEDIACODECDECODER_H

#include "H264DecoderBase.h"
#include <jni.h>
#include "Global.h"

struct MediaCodecDecoderPrivate;

class MediaCodecDecoder : public H264DecoderBase {
private:
    MediaCodecDecoderPrivate *mediaCodecDecoderPrivate;

public:
    MediaCodecDecoder();

    ~MediaCodecDecoder();

public:

    int InitDecoder(int identityId, unsigned char *spsPpsData, int length, int width, int height);

    int DecodeVideo(AVFrame *picture, int *got_picture_ptr, AVPacket *avpkt);

    void setMediaCodec(jobject jMediaCodec);

    void CloseDecoder(void);
};


#endif //M1_ANDROID_MEDIACODECDECODER_H
