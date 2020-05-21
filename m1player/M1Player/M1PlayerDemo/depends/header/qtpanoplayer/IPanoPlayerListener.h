#pragma once

namespace DetuPanoPlayer {

typedef enum PanoPlayerErrorCode {
	PanoPlayerErrorCode_LACK_CALIBRATION,

}PanoPlayerErrorCode;

class IPanoPlayerListener
{
public:
	IPanoPlayerListener(){}
	~IPanoPlayerListener(){}

	virtual void onPanoPlayerLoading() = 0;
	virtual void onPanoPlayerLoaded() = 0; //插件加载完毕，此时可以获取媒体信息
	virtual void onPanoPlayerError(PanoPlayerErrorCode errorCode) = 0;
};
}
