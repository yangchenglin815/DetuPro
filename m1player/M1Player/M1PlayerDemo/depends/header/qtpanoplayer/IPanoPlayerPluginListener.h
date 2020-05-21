#ifndef IPanoPlayerPluginListener_h__
#define IPanoPlayerPluginListener_h__
#include <iostream>
using namespace std;

namespace DetuPanoPlayer {

typedef enum PanoPluginStatus
{
	PanoPluginStatus_PREPARED,
	PanoPluginStatus_PLAYING,
	PanoPluginStatus_PAUSE,
	PanoPluginStatus_STOP,
	PanoPluginStatus_FINISH,
	PanoPluginStatus_HW_TO_AVCODEC, //Ó²½âÊ§°ÜÇÐ»»ÎªÈí½â
	PanoPluginStatus_ERROR,
} PanoPluginStatus;

typedef enum PanoPluginError
{
	PanoPluginError_NETWORK
} PanoPluginError;

class IPanoPlayerPluginListener
{
public:
	IPanoPlayerPluginListener()
	{
	};

	~IPanoPlayerPluginListener()
	{
	};
	virtual void onPanoPlayerPluginStatusChanged(PanoPluginStatus status, string tip) = 0;
	virtual void onPanoPlayerPluginProgressChanged(long playTime, long bufferTime, long duration) = 0;
};

}
#endif // IPanoPlayerPluginListener_h__
