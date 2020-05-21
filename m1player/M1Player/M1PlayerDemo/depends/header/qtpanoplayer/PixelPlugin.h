#ifndef PixelPlugin_h__
#define PixelPlugin_h__

#include "Plugin.h"

#define  PLUGIN_DESCRIPTION_PIXEL "pixel_plugin"

namespace DetuPanoPlayer {

class PixelPlugin : public Plugin
{

public:
	PixelPlugin();
	~PixelPlugin();
	void setPanoData(PanoramaData panoramaData);
	vector<PluginMetaData> getPluginMetaDatas();
	string getDescription();

	void notifyMetaDatas(vector<PluginMetaData> metaDatas);
	void notifyStateChanged(PluginState state, string tip);
	void notifyProgressChanged(long playTime, long bufferTime, long duration);
	void notifyFramesChanged(PluginFrame* frames, int count);
private:
	vector<PluginMetaData> metaDatas;
};
}

#endif // PixelPlugin_h__
