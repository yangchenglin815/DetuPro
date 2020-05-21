#pragma once
#include <stdint.h>

#define PLUGIN_MAX_PLANE 4 //Frame最大通道数

namespace DetuPanoPlayer {

typedef enum PluginState
{
	PluginState_PREPARED,
	PluginState_PLAYING,
	PluginState_PAUSE,
	PluginState_STOP,
	PluginState_SEEK_COMPLETE,
	PluginState_COMPLETED,
	PluginState_ERROR, 
	PluginState_DECODER_CHANGE
} PluginState;

typedef enum PluginColorFormat
{
	PluginColorFormat_RGBA,
	PluginColorFormat_ARGB,
	PluginColorFormat_ABGR,
	PluginColorFormat_BGRA,
	PluginColorFormat_RGB24,
	PluginColorFormat_BGR24,
	PluginColorFormat_YUV420P,
	PluginColorFormat_YV12,
	PluginColorFormat_NV12,
	PluginColorFormat_NV21,
    PluginColorFormat_UYVY422,
	PluginColorFormat_OPENGL_RGBA_TEXTURE,
} PluginColorFormat;

typedef struct PluginFrame
{
	uint8_t* data[PLUGIN_MAX_PLANE];
	int linesize[PLUGIN_MAX_PLANE];
	int width;
	int height;
    int planes;
	PluginColorFormat colorFormat;
	void* opaque; //opengl texture 或者ios硬解数据
} PluginFrame;

class PluginListener
{
public:
	PluginListener(){}
	~PluginListener(){}
	virtual void onPluginStateChanged(PluginState state, string tip) = 0;
	virtual void onPluginGetFrames(PluginFrame* frame, int count) = 0;
	virtual void onPluginProgressChanged(long playTime, long bufferTime, long duration) = 0;
};
    
}
