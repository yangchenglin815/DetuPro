//
//  H264DecoderBase.hpp
//  M1Decoder
//
//  Created by chao on 2017/11/8.
//  Copyright © 2017年 detu. All rights reserved.
//

#ifndef H264DecoderBase_hpp
#define H264DecoderBase_hpp

#include <iostream>
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/error.h"
#include <libavutil/frame.h>
}

typedef enum {
    H264DecoderType_SOFT,
    H264DecoderType_QSV,
    H264DecoderType_CUDA,
    H264DecoderType_VTB,
    H264DecoderType_VDA,
    H264DecoderType_MEDIACODEC,
} H264DecoderType;

class H264DecoderBase
{
public:
    H264DecoderBase();
    virtual ~H264DecoderBase();
    
public:
    void SetDecodeType(H264DecoderType decoderType);
    virtual int InitDecoder(int identityId, unsigned char* spsPpsData, int length, int width, int height);
    virtual int DecodeVideo(AVFrame *picture,int *got_picture_ptr, AVPacket *avpkt) = 0;
    virtual void unRefFrame(AVFrame *picture);
    virtual void CloseDecoder(void);
    
	virtual int GetVfps();
	virtual int GetVbitrate();

protected:
    AVCodecContext        *m_codec_ctx;
    AVCodec               *m_codec;
    int  identityId;
    H264DecoderType h264DecoderType;
    unsigned char* spsPpsData;
	int m_vfps;
	int m_vbitrate;
};


#endif /* H264DecoderBase_hpp */
