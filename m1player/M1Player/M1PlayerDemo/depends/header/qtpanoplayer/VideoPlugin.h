#ifndef VideoPlugin_h__
#define VideoPlugin_h__
#include "Plugin.h"
#include <memory>
#define PLUGIN_DESCRIPTION_VIDEO "video_plugin"

//windows
#define VIDEO_PLUGIN_CODEC_NAME_CUDA "cuda" //cudaӲ�⣬Ĭ�Ͻ�������
#define VIDEO_PLUGIN_CODEC_NAME_QSV "qsv"   //qsvӲ��

//mac
#define VIDEO_PLUGIN_CODEC_NAME_VDA "vda"   //qsvӲ��

//ios
#define VIDEO_PLUGIN_CODEC_NAME_VTB "vtb"   //qsvӲ��

//android
#define VIDEO_PLUGIN_CODEC_NAME_MEDIACODEC "media_codec"   //qsvӲ��

#define VIDEO_PLUGIN_CODEC_NAME_SOFT "soft" //���

namespace DetuPanoPlayer {
    
class VideoPluginPrivate;

class VideoPlugin : public Plugin
{
public:
	std::shared_ptr<VideoPluginPrivate> videoPluginPrivate_;
public:
	VideoPlugin();
	~VideoPlugin();
	void setPanoData(PanoramaData panoramaData);
	void start() const;
	void pause() const;
	void stop() const;
	void close();
    void refresh();

	void setVolume(float volume);
	float getVolume() const;
	bool isPlaying() const;
	void seekTo(long msec);
	vector<PluginMetaData> getPluginMetaDatas();
	string getDescription();
};
    
}
#endif // VideoPlugin_h__
