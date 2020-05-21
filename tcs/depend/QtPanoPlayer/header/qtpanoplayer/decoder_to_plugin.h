#pragma once
#include "PluginListener.h"
#include "ijk_ffplay_decoder.h"

namespace DetuPanoPlayer {
    
void decoderToPlugin_ijkFrameToPluginFrame(IjkVideoFrame* ijkFrame, PluginFrame* pluginFrame)
{
	pluginFrame->data[0] = ijkFrame->data[0];
	pluginFrame->data[1] = ijkFrame->data[1];
	pluginFrame->data[2] = ijkFrame->data[2];
	pluginFrame->width = ijkFrame->w;
	pluginFrame->height = ijkFrame->h;
	pluginFrame->linesize[0] = ijkFrame->linesize[0];
	pluginFrame->linesize[1] = ijkFrame->linesize[1];
	pluginFrame->linesize[2] = ijkFrame->linesize[2];
	pluginFrame->planes = ijkFrame->planes;
	switch (ijkFrame->format)
	{
	case PIX_FMT_YUV420P:
		pluginFrame->colorFormat = PluginColorFormat_YUV420P;
		break;
    case PIX_FMT_NV12:
        pluginFrame->colorFormat = PluginColorFormat_NV12;
        break;
    case PIX_FMT_VDA:
        pluginFrame->colorFormat = PluginColorFormat_UYVY422;
        break;
	}
}

PluginState decoderToPlugin_ijkStateToPluginState(IjkMsgState state)
{
	PluginState pluginState = PluginState_COMPLETED;
	switch (state)
	{
	case IJK_MSG_PREPARED:
		pluginState = PluginState_PREPARED;
		break;
	case IJK_MSG_ERROR:
		pluginState = PluginState_PREPARED;
		break;
	case IJK_MSG_COMPLETED:
		pluginState = PluginState_COMPLETED;
		break;
	case IJK_MSG_SEEK_COMPLETE:
		pluginState = PluginState_SEEK_COMPLETE;
		break;
	case IJK_MSG_FLUSH:
		break;
	default:
		break;
	}
	return pluginState;
}
    
}
