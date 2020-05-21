/************************************************
* \file playmodewgt.h
*
* \author HuZhengdong
* \date 20170721
* ��ͼ�࣬����ץȫ��ͼƬ
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

//�㷨���ýṹ��
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

	//��ʼ������ƴ�Ӳ�����ͼ��ʵʱ�Ż���ͼƴ��
	void InitRealTimeCapture(m1_video_frame_s** frame_sync);

	//�궨
	int Calibration();

	//�ӳ����Ż�
	int OptimizePts();

	//����wtͼ
	int CreatMaskAndWeight();

	//����ƴ��
	void LinearStitch();

	//ʵʱץͼ����Ӧ��ť����
	void RealTimeCapture(m1_video_frame_s** frame_sync);

	//�������
	MMD_RESULT CheckWarningBoard(m1_video_frame_s** frame_sync);

	//��ȡ����б�
	void readList(QString list_path);


signals:
	void SignalToRFIDUi(int type, int id);
private:
	//���ŵ�m1�豸id
	QString select_m1_device_;						

	//����ƴ����
	vector<Mat>         ySrcCpu_;
	vector<Mat>         uSrcCpu_;
	vector<Mat>         vSrcCpu_;

	vector<Mat>         ySrcCpu_nv12_;
	vector<Mat>         uSrcCpu_nv12_;
	vector<Mat>         vSrcCpu_nv12_;

	Size    srcSize_;								// ����ͼ���С
	Algrithom_Cfg algrithom_cfg_;

	std::vector<PhotoParam> photoparam_list_;
	cv::Size pano_size_;


	//��
	boost::mutex mutex_capture_;

	vector<TargetInfo> target_list_;
};

#endif // PANOCAPTURER_H
