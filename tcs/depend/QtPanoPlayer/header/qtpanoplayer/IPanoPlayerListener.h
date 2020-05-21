#pragma once

namespace DetuPanoPlayer {

typedef enum PanoPlayerErrorCode {
	PanoPlayerErrorCode_LACK_CALIBRATION,

}PanoPlayerErrorCode;

class IPanoPlayerListener
{
public:
	IPanoPlayerListener(){}
	virtual ~IPanoPlayerListener(){}

	virtual void onPanoPlayerLoading() = 0;
	virtual void onPanoPlayerLoaded() = 0; //���������ϣ���ʱ���Ի�ȡý����Ϣ
	virtual void onPanoPlayerError(PanoPlayerErrorCode errorCode) = 0;
};
}
