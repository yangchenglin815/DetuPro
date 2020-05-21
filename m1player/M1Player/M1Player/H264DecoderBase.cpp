//
//  H264DecoderBase.cpp
//  M1Decoder
//
//  Created by chao on 2017/11/8.
//  Copyright © 2017年 detu. All rights reserved.
//

#include "H264DecoderBase.h"
#include "ijksdl_log.h"
#include "Error.h"


static void ff_log_callback(void*avcl, int level, const char*fmt, va_list vl)
{
	char str[1024] = "";
	vsnprintf(str, sizeof(str) - 1, fmt, vl);
	ALOGE("%s", str);
}

H264DecoderBase::H264DecoderBase() : m_codec_ctx(NULL), m_codec(NULL), identityId(0) {
#if defined(MAC_QT)
    this->h264DecoderType = H264DecoderType_VDA;
#elif defined(__APPLE__)
    this->h264DecoderType = H264DecoderType_VTB;
#elif defined(_WIN32)
	this->h264DecoderType = H264DecoderType_SOFT;
#elif defined(_WIN64)
	this->h264DecoderType = H264DecoderType_SOFT;
#else
    this->h264DecoderType = H264DecoderType_MEDIACODEC;
#endif
    
    this->spsPpsData = NULL;

	m_vfps = 0;
	m_vbitrate = 0;
}

H264DecoderBase::~H264DecoderBase() {
    if(this->spsPpsData != NULL) {
        free(this->spsPpsData);
        this->spsPpsData = NULL;
    }
}

void H264DecoderBase::SetDecodeType(H264DecoderType decoderType) {
    this->h264DecoderType = decoderType;
}

int H264DecoderBase::InitDecoder(int identityId, unsigned char* spsPpsData, int length, int width, int height) {
    this->identityId = identityId;
    
    //av_log_set_callback(ff_log_callback);
    //av_log_set_level(AV_LOG_INFO);
    switch (h264DecoderType) {
        case H264DecoderType_CUDA:
            m_codec = avcodec_find_decoder_by_name("h264_cuvid");
            ALOGE("start hardware decode by cuvid");
            break;
        case H264DecoderType_QSV:
            m_codec = avcodec_find_decoder_by_name("h264_qsv");
            ALOGE("start hardware decode by qsv");
            break;
        case H264DecoderType_VDA:
            m_codec = avcodec_find_decoder_by_name("h264_vda");
            ALOGE("start hardware decode by mac vda");
            break;
        default:
            m_codec = avcodec_find_decoder(AV_CODEC_ID_H264);
			ALOGE("start software decode by ffmpeg.");
            break;
    }
    if (m_codec == NULL) {
        ALOGE("can't find h264 codec.");
        return ERROR_H264_FIND_DECODER;
    }
    m_codec_ctx = avcodec_alloc_context3(m_codec);
    if (m_codec_ctx == NULL) {
        ALOGE("alloc codec context error.");
        return ERROR_H264_ALLOC_CODEC_CONTEXT;
    }
    
    this->spsPpsData = (unsigned char*)calloc(1, length);
    memcpy(this->spsPpsData, spsPpsData, length);
    m_codec_ctx->coded_width = width;
    m_codec_ctx->width = width;
    m_codec_ctx->coded_height = height;
    m_codec_ctx->height = height;
    m_codec_ctx->thread_count = 2;
    m_codec_ctx->thread_type |= FF_THREAD_SLICE;
    m_codec_ctx->refcounted_frames = 1;
    m_codec_ctx->extradata_size = length;
    
    if (avcodec_open2(m_codec_ctx, m_codec, NULL) < 0) {
        ALOGE("can not open h264 codec.");
        return ERROR_H264_OPEN_DECODER;
    }
    
    ALOGE("h264 decoder init success, camera id:%d.", identityId);
    return 0;
}

void H264DecoderBase::unRefFrame(AVFrame *picture) {
    
}

void H264DecoderBase::CloseDecoder(void) {
    if (m_codec_ctx) {
        avcodec_close(m_codec_ctx);
        m_codec_ctx = NULL;
    }
}

int H264DecoderBase::GetVfps()
{
	return 0;
}

int H264DecoderBase::GetVbitrate()
{
	return 0;
}
