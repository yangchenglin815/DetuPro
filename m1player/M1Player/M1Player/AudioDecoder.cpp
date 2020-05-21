#include "AudioDecoder.h"
#include "ijksdl_log.h"
#include "Error.h"

CAudioDecoder::CAudioDecoder()
{
	m_codec_ctx = NULL;
	m_codec = NULL;

#ifdef AUDIO_CONFIG_FILE
	m_decoder_output = fopen("decoder_output", "wb+");
#endif
}

CAudioDecoder::~CAudioDecoder()
{
#ifdef AUDIO_CONFIG_FILE
	if (m_decoder_output){
		fclose(m_decoder_output);
		m_decoder_output = NULL;
	}
#endif
}

int CAudioDecoder::InitDecoder(void)
{
	//find decoder for audio stream
	m_codec = avcodec_find_decoder(AV_CODEC_ID_PCM_ALAW);//g711a
	if (m_codec == NULL){
		ALOGE("audio codec not found.");
		return -1;
	}

	//alloc codec context for audio stream
	m_codec_ctx = avcodec_alloc_context3(m_codec);
	if (m_codec_ctx == NULL) {
		printf("alloc audio codec context error.");
		return -1;
	}
	m_codec_ctx->channel_layout = DEFAULT_AUDIO_CHANNEL_LAYOUT;			//和channels值相同
	m_codec_ctx->channels = DEFAULT_AUDIO_CHANNELS;						//单声道
	m_codec_ctx->sample_rate = DEFAULT_AUDIO_SAMPLE_RATE;				//8k采样率
	m_codec_ctx->sample_fmt = DEFAULT_AUDIO_SAMPLE_FORMAT;				//16位采样深度
	m_codec_ctx->frame_size = DEFAULT_AUDIO_FRAME_SIZE;					//景阳发送的音频帧实际大小

	m_codec_ctx->refcounted_frames = 1;									//取消内存复用

	//open codec
	if (avcodec_open2(m_codec_ctx, m_codec, NULL) < 0){
		ALOGE("could not open audio codec.");
		return -1;
	}

	ALOGI("audio decoder init success.");
	return 0;
}

int CAudioDecoder::DecodeAudio(AVFrame *picture, int *got_picture_ptr, AVPacket *avpkt)
{
	if (m_codec_ctx) {
		int ret = avcodec_decode_audio4(m_codec_ctx, picture, got_picture_ptr, avpkt);
		if (!(*got_picture_ptr)) {
			char err_buf[AV_ERROR_MAX_STRING_SIZE] = { 0 };
			av_strerror(ret, err_buf, AV_ERROR_MAX_STRING_SIZE);
			ALOGE("audio decode error, error string:%s", err_buf);
		}

		//pcm data ok, freq:8k, channel:1, dep:16
#ifdef AUDIO_CONFIG_FILE
		fwrite(picture->data[0], 1, picture->linesize[0], m_decoder_output);
		fflush(m_decoder_output);
#endif

		return ret;
	} else {
		ALOGE("audio codec context is NULL");
		return ERROR_AUDIO_CODEC_CONTEXT_NULL;
	}

	return 0;
}

void CAudioDecoder::CloseDecoder(void)
{
	if (m_codec_ctx) {
		avcodec_close(m_codec_ctx);
		m_codec_ctx = NULL;
	}
}
