#include "FfmpegH264Decoder.h"
#include "ijksdl_log.h"
#include "Error.h"

FfmpegH264Decoder::FfmpegH264Decoder()
{

}

FfmpegH264Decoder::~FfmpegH264Decoder()
{

}


int FfmpegH264Decoder::DecodeVideo(AVFrame *picture, int *got_picture_ptr, AVPacket *avpkt)
{
	if (m_codec_ctx) {
		int ret = avcodec_decode_video2(m_codec_ctx, picture, got_picture_ptr, avpkt);
		if (!(*got_picture_ptr)) {
			char err_buf[AV_ERROR_MAX_STRING_SIZE] = { 0 };
			av_strerror(ret, err_buf, AV_ERROR_MAX_STRING_SIZE);
			ALOGE("decode error, error string:%s, camera id:%d", err_buf, identityId);
		}
		return ret;
	} else {
		ALOGE("codec context is NULL, camera id:%d", identityId);
		return ERROE_H264_CODEC_CONTEXT_NULL;
	}
}

int FfmpegH264Decoder::GetVfps()
{
	if (m_vfps == 0 && m_codec_ctx->time_base.num != 0 && m_codec_ctx->ticks_per_frame != 0) {
		m_vfps = m_codec_ctx->time_base.den / (m_codec_ctx->time_base.num * m_codec_ctx->ticks_per_frame);
	}

	return m_vfps;
}

int FfmpegH264Decoder::GetVbitrate()
{
	if (m_vbitrate == 0) {
		m_vbitrate = m_codec_ctx->bit_rate / 1000; 
	}

	return m_vbitrate;
}
