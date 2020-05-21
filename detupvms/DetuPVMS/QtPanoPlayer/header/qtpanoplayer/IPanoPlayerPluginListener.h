#ifndef IPanoPlayerPluginListener_h__
#define IPanoPlayerPluginListener_h__

#include <iostream>

using namespace std;

namespace DetuPanoPlayer {

    typedef enum PanoPluginStatus {
        PanoPluginStatus_PREPARED,
        PanoPluginStatus_PLAYING,
        PanoPluginStatus_PAUSE,
        PanoPluginStatus_STOP,
        PanoPluginStatus_FINISH,
        PanoPluginStatus_HW_TO_AVCODEC, //Ӳ��ʧ���л�Ϊ���
        PanoPluginStatus_ERROR,
		PanoPluginStatue_Gopsize,
		PanoPluginStatue_Decoderfps,
        PanoPluginStatus_Statistics,
    } PanoPluginStatus;

    typedef enum PanoPluginError {
        PanoPluginError_NETWORK
    } PanoPluginError;
    
    typedef struct PanoPluginStatisticsData {
        int renderFps;
        int decodeFps;
    } PanoPluginStatisticsData;

    class IPanoPlayerPluginListener {
    public:
        IPanoPlayerPluginListener() {}

        virtual ~IPanoPlayerPluginListener() {}

        virtual void onPanoPlayerPluginStatusChanged(PanoPluginStatus status, string tip) = 0;

        virtual void onPanoPlayerPluginProgressChanged(long playTime, long bufferTime, long duration) = 0;
        
        virtual void onPanoPlayerPluginStatisticsDataChanged(PanoPluginStatisticsData* statisticsData) = 0;
    };

}
#endif // IPanoPlayerPluginListener_h__
