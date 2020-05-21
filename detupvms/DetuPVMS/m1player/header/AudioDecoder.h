#ifndef _AUDIO_DECODER_H_
#define _AUDIO_DECODER_H_

//copy from ijkplayer, modify for m1
//PVS出来的音频：G711a，8k采样率，单声道，16位采样深度;若音频格式变了，需要对应修改代码

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/frame.h"
#include "libavutil/error.h"
}

//#define AUDIO_CONFIG_FILE

#define DEFAULT_AUDIO_CODEC				AV_CODEC_ID_PCM_ALAW	//codec: g711a
#define DEFAULT_AUDIO_CHANNEL_LAYOUT	1						//channel_layout: 1
#define DEFAULT_AUDIO_SAMPLE_RATE		8000					//freq: 8k
#define DEFAULT_AUDIO_CHANNELS			1						//channels: 1
#define DEFAULT_AUDIO_SAMPLE_FORMAT		AV_SAMPLE_FMT_S16		//sampel_format: signed 16 bits
#define DEFAULT_AUDIO_FRAME_SIZE		800						//audio frame size: 800(g711a audio packet size send by jinyang)

#define MAX_AUDIO_FRAME_SIZE			192000	// 1 second of 48khz 32bit audio

class CAudioDecoder
{
public:
	CAudioDecoder();
	~CAudioDecoder();

public:
	int InitDecoder(void);
	int DecodeAudio(AVFrame *picture, int *got_picture_ptr, AVPacket *avpkt);
	void CloseDecoder(void);

private:
	AVCodecContext		*m_codec_ctx;
	AVCodec				*m_codec;

#ifdef AUDIO_CONFIG_FILE
	FILE				*m_decoder_output;	//pcm, 8000采样率,单声道，16位采样深度
#endif
};

#endif
