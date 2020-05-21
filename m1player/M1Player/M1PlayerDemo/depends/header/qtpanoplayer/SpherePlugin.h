#ifndef SpherePlugin_h__
#define SpherePlugin_h__

#include "Plugin.h"
#include "FfmpegImagePlugin.h"
#define  PLUGIN_DESCRIPTION_SPHERE "sphere_plugin"

namespace DetuPanoPlayer {
    
class SpherePlugin : public FfmpegImagePlugin
{
public:
	SpherePlugin();
	~SpherePlugin();
	void setPanoData(PanoramaData panoramaData);
	string getDescription();
};
    
}

#endif // SpherePlugin_h__
