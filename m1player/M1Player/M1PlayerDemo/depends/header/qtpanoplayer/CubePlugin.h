#ifndef CubePlugin_h__
#define CubePlugin_h__
#include "Plugin.h"

#define PLUGIN_DESCRIPTION_CUBE "cube_plugin"

namespace DetuPanoPlayer {

class CubePlugin : public Plugin
{
public:
	CubePlugin();
	~CubePlugin();
	void setPanoData(PanoramaData panoramaData);
	vector<PluginMetaData> getPluginMetaDatas();
	string getDescription();
};
    
}

#endif // CubePlugin_h__
