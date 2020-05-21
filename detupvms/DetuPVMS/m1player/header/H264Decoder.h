#ifndef _H264_DECODER_H_
#define _H264_DECODER_H_

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/error.h"
}

class CH264Decoder
{
public:
	CH264Decoder();
	~CH264Decoder();

public:
	int InitDecoder(int decoder_id, int width, int height);
	int DecodeVideo(AVFrame *picture,int *got_picture_ptr,const AVPacket *avpkt);

	void SetDecodeType(int decode_type);
	void SetHardwareDecode(bool is_hardware_decode);
	void GetVideoHeight(int &height);
	void CloseDecoder(void);

private:
	AVCodecContext		*m_codec_ctx;
	AVCodec				*m_codec;

	bool m_is_hardware_decode;
	int  m_decode_type;
	int  m_decoder_id;
};

#endif
