//
//  VtbH264Decoder.hpp
//  M1Decoder
//
//  Created by chao on 2017/11/8.
//  Copyright © 2017年 detu. All rights reserved.
//

#ifndef VtbH264Decoder_hpp
#define VtbH264Decoder_hpp

#include "H264DecoderBase.h"
#include <stdio.h>

class VtbH264DecoderPrivate;

class VtbH264Decoder : public H264DecoderBase {
private:
    VtbH264DecoderPrivate* decoderPrivate;
public:
    VtbH264Decoder();
    ~VtbH264Decoder();
public:
    int InitDecoder(int identityId, unsigned char* spsPpsData, int length, int width, int height);
    int DecodeVideo(AVFrame *picture,int *got_picture_ptr, AVPacket *avpkt);
    void unRefFrame(AVFrame *picture);
    void CloseDecoder(void);
};

#endif /* VtbH264Decoder_hpp */
