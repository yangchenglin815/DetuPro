/************************************************
* \file playmodewgt.h
*
* \author HuZhengdong
* \date 20170721
* 截图类，负责抓全景图片
************************************************/
#ifndef PANOCAPTURER_H
#define PANOCAPTURER_H


#include "ZReproject.h"
#include "imgproc/imp_lib.h"
#include "map/map_proc.h"
#include "weight/gbw_lib.h"
#include "patLib/pat_lib.h"
#include "circle/circle_lib.h"
#include "blend/bld_lib.h"

#include "constStruct.h"
#include "m1player/header/M1Player.h"

#include "M1LIB_MoveDetect_lib.h"

#include "RFIDDataManager.h"

#include <QObject>

//算法调用结构体
typedef struct _Algrithom_Cfg
{
	int					imgNum = 4;
	int					width = MASK_WIDTH;
	int					height = MASK_HEIGHT;
	int					blendWidth = 20;
	int					radius;
	int					ret;
	cv::Size			dstSize = cv::Size(MASK_WIDTH, MASK_HEIGHT);
	STL_S64				bufSize;
	STL_U08				*workBuf = NULL;
	STL_S32				pat_bufSize;
	STL_U08				*pat_workBuf = NULL;
	STL_S32				score;
	FILE				*fpCfg = NULL;
	vector<PhotoParam>	photoPm;
	vector<Mat>			srcImg;
	vector<Mat>			masks;
	vector<Mat>			weights;
	vector<string>		imgFile;
	std::string			ptsPath;
	std::string			output;
}Algrithom_Cfg;


class PanoCalibraterAndCapturer : public QObject
{
	Q_OBJECT

public:
	PanoCalibraterAndCapturer();
	~PanoCalibraterAndCapturer();

public:
	void setDevice(QString m1_device);

	//初始化生成拼接参数截图、实时优化截图拼接
	void InitRealTimeCapture(m1_video_frame_s** frame_sync);

	//标定
	int Calibration();

	//视场角优化
	int OptimizePts();

	//生成wt图
	int CreatMaskAndWeight();

	//线性拼接
	void LinearStitch();

	//实时抓图，响应按钮操作
	void RealTimeCapture(m1_video_frame_s** frame_sync);

	//检测入侵
	MMD_RESULT CheckWarningBoard(m1_video_frame_s** frame_sync);

	//读取检测列表
	void readList(QString list_path);


signals:
	void SignalToRFIDUi(int type, int id);
private:
	//播放的m1设备id
	QString select_m1_device_;						

	//线性拼接用
	vector<Mat>         ySrcCpu_;
	vector<Mat>         uSrcCpu_;
	vector<Mat>         vSrcCpu_;

	vector<Mat>         ySrcCpu_nv12_;
	vector<Mat>         uSrcCpu_nv12_;
	vector<Mat>         vSrcCpu_nv12_;

	Size    srcSize_;								// 输入图像大小
	Algrithom_Cfg algrithom_cfg_;

	std::vector<PhotoParam> photoparam_list_;
	cv::Size pano_size_;


	//锁
	boost::mutex mutex_capture_;

	vector<TargetInfo> target_list_;
};

#endif // PANOCAPTURER_H
