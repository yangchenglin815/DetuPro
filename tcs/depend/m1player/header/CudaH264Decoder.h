#ifndef CUDA_H264_DECODER_H_
#define CUDA_H264_DECODER_H_

#include "H264DecoderBase.h"

class CudaH264Decoder : public H264DecoderBase
{
public:
	CudaH264Decoder();
	~CudaH264Decoder();
	int DecodeVideo(AVFrame *picture, int *got_picture_ptr, AVPacket *avpkt) override;
	void setPboId(int pboId);
	bool copyDecodedFrameToTexture();
protected:
	int mPboId;
};

#endif