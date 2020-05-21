#include "CudaH264Decoder.h"

CudaH264Decoder::CudaH264Decoder()
{
	mPboId = 0;
}
CudaH264Decoder::~CudaH264Decoder()
{
	
}

int CudaH264Decoder::DecodeVideo(AVFrame* picture, int* got_picture_ptr, AVPacket* avpkt)
{
	return 0;
}

void CudaH264Decoder::setPboId(const int pboId)
{
	mPboId = pboId;
}

bool CudaH264Decoder::copyDecodedFrameToTexture()
{
	return false;
}
