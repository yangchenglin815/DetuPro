#ifndef _H264_DECODER_H_
#define _H264_DECODER_H_

#include "H264DecoderBase.h"

class FfmpegH264Decoder : public H264DecoderBase
{
public:
	FfmpegH264Decoder();
	~FfmpegH264Decoder();

public:
	int DecodeVideo(AVFrame *picture,int *got_picture_ptr, AVPacket *avpkt);

	int GetVfps();
	int GetVbitrate();
};

#endif
