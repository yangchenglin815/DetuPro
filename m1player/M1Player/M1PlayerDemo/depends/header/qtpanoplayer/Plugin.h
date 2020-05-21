#pragma once
#include "PlayerOption.h"
#include <vector>
#include "PanoramaData.h"
#include "PluginListener.h"
using namespace std;

//�Զ���KEY

//des:��������,����noneΪ���, type:PlayerOptionType_Codec, value:["none"|"qsv"|"cuda"|"media_codec"|"video_toolbox"]
#define PLAYER_OPTION_DETU_KEY_DECODER "detu_hw_decoder"

//des:�Ƿ�ͳ������, type:PlayerOptionType_Player, value:["true"|"false"]
#define PLAYER_OPTION_DETU_KEY_IS_SHOW_STATISTICS "detu_show_statistics" 

//des:�Ƿ���������, type:PlayerOptionType_Player, value:["true"|"false"]
#define PLAYER_OPTION_DETU_KEY_IS_BLOCK_FRAME "detu_block_frame"

namespace DetuPanoPlayer {
    
    typedef struct  PluginLimits {
        int maxTextureSize;
    } PluginLimits;

typedef enum PluginMediaType
{
	PluginMediaType_VIDEO,
	PluginMediaType_PIC,
} PluginMediaType;

typedef struct PluginMetaData
{
	PluginMediaType mediaType;

	//video
	int width;
	int height;
	PluginColorFormat pluginFormat;
	int lineSize[3];
	int videoBitRate;
	float videoFrameRate;
	long duration;

	//����
	int audioBitRate;
	int audioSampleRate;

	//detu
	string calibration;
} PluginMetaData;

class Plugin
{
public:
	Plugin();
	~Plugin();
	virtual void setPanoData(PanoramaData panoramaData) = 0;
	PanoramaData* getPanoData();

	void setOptions(vector<PlayerOption> options);
    void setPluginLimits(PluginLimits pluginLimits);
	vector<PlayerOption> getOptions() const;
    PluginLimits getPluginLimits() const;

	void setPluginListener(PluginListener* pluginListener);
	PluginListener* getPluginListener() const;

	virtual vector<PluginMetaData> getPluginMetaDatas() = 0;

	/**
	 * ��ȡPlugin����
	 */
	virtual string getDescription() = 0;

protected:
	vector<PlayerOption> options;
	PluginListener* pluginListener;
	PanoramaData panoramaData;
	bool is_close_flag_;
    PluginLimits limits;
};
    
    
}

