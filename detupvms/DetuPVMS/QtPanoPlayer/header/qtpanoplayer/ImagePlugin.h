#ifndef SpherePlugin_h__
#define SpherePlugin_h__

#include "Plugin.h"
#include "FfmpegImagePlugin.h"
#define  PLUGIN_DESCRIPTION_SPHERE "sphere_plugin"

namespace DetuPanoPlayer {
    
class ImagePlugin : public FfmpegImagePlugin
{
public:
	ImagePlugin(string imgCachePath);
	~ImagePlugin();
	void setPanoData(PanoramaData panoramaData);
	string getDescription();
};
    
}

#endif // SpherePlugin_h__
