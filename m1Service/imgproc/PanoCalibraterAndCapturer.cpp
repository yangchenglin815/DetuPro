#include "PanoCalibraterAndCapturer.h"


#include "logging.hpp"



PanoCalibraterAndCapturer::PanoCalibraterAndCapturer()
	:pano_size_(CAPTURE_PANO_WIDTH, CAPTURE_PANO_HEIGHT)
	,srcSize_(0, 0)
{
}


PanoCalibraterAndCapturer::~PanoCalibraterAndCapturer()
{
}



MMD_RESULT PanoCalibraterAndCapturer::CheckWarningBoard()
{
// 	//清空列表
// 	emit SignalToRFIDUi(200, 100);
// 
// 
// 	STL_S32 i;
// 	STL_S32 cnt;
// 	STL_S32 imgNum;
// 	STL_S32 cudaSts;
// 	STL_U08 *yImg = NULL;
// 	STL_U08 *uImg = NULL;
// 	STL_U08 *vImg = NULL;
// 	STL_STATUS sts = STL_ERR;
// 	Size  srcSize;
// 
// 	vector<Mat>         ySrcCpu;
// 	vector<Mat>         uSrcCpu;
// 	vector<Mat>         vSrcCpu;
// 
// 	// 初始化
// 	imgNum = 4;
// 
// 	srcSize.width = frame_sync[0]->w;
// 	srcSize.height = frame_sync[0]->h;
// 
// 	//写RGB图片
// 	cv::Mat background_img(frame_sync[0]->h, frame_sync[0]->w, CV_8UC3);
// 
// 
// 	vector<Mat>  rgb_img;
// 	rgb_img.resize(4);
// 	for (int j = 0; j < imgNum; j++)
// 	{
// 		rgb_img[j].create(frame_sync[0]->h, frame_sync[0]->w, CV_8UC3);
// 	}
// 
// 	//拷贝内存
// 	ySrcCpu.resize(imgNum);
// 	uSrcCpu.resize(imgNum);
// 	vSrcCpu.resize(imgNum);
// 	for (int j = 0; j < imgNum; j++)
// 	{
// 		ySrcCpu[j].create(srcSize, CV_8UC1);
// 		uSrcCpu[j].create(srcSize.height / 2, srcSize.width / 2, CV_8UC1);
// 		vSrcCpu[j].create(srcSize.height / 2, srcSize.width / 2, CV_8UC1);
// 
// 		rgb_img[j].create(frame_sync[0]->h, frame_sync[0]->w, CV_8UC3);
// 	}
// 
// 
// 	//截断copy
// 	for (int j = 0; j < imgNum; j++)
// 	{
// 		for (int i = 0; i < srcSize.height; i++)
// 		{
// 			memcpy(ySrcCpu[j].data + i*srcSize.width, frame_sync[j]->data[0] + i*frame_sync[j]->linesize[0], srcSize.width);
// 			if (i < srcSize.height / 2)
// 			{
// 				memcpy(uSrcCpu[j].data + i*srcSize.width / 2, frame_sync[j]->data[1] + i*frame_sync[j]->linesize[0] / 2, srcSize.width / 2);
// 				memcpy(vSrcCpu[j].data + i*srcSize.width / 2, frame_sync[j]->data[2] + i*frame_sync[j]->linesize[0] / 2, srcSize.width / 2);
// 			}
// 		}
// 	}
// 
// 	//以下需要起线程干
// 
// 	for (int j = 0; j < imgNum; j++)
// 	{
// 		IMP_DataConvert_yuv4202bgr(ySrcCpu[j].data, uSrcCpu[j].data, vSrcCpu[j].data, srcSize.width, srcSize.height, rgb_img[j].data);
// 	}
// 
// 
// 	int img_num = 0;
// 	MMD_RESULT result;
// 	for (std::vector<TargetInfo>::iterator iter = target_list_.begin(); iter != target_list_.end(); iter++)
// 	{
// 
// 		QString path = QString(QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/Map/warning_board") + "/%1.jpg")
// 			.arg(QString::number(iter->img_id));
// 		QString path1 = QString(QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/Map/warning_board") + "/%1%2.jpg")
// 			.arg(QString::number(iter->img_id), QString::number(iter->target_id));
// 		QString path11 = QString(QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/Map/warning_board") + "/%1%2rect.jpg")
// 			.arg(QString::number(iter->img_id), QString::number(iter->target_id));
// 
// 
// 		cv::imwrite(path1.toStdString(), rgb_img[iter->img_id]);
// 
// 		background_img = imread(path.toStdString());
// 
// 		//检测
// 		int difTh;
// 		cv::Rect roiArea;
// 		Mat curImg;
// 		Mat standImg, dectecImg;
// 		string backGroundImgName, curImgName;
// 		MMD_RESULT detectRes;
// 		std::vector<cv::Point2f> targetPts;
// 		
// 		roiArea.x = iter->pos_x;
// 		roiArea.y = iter->pos_y;
// 		roiArea.width = iter->w;
// 		roiArea.height = iter->h;
// 
// 		standImg = background_img(roiArea);
// 		dectecImg = rgb_img[iter->img_id](roiArea);
// 		cv::imwrite(path11.toStdString(), dectecImg);
// 
// 		int res = MMD_MoveDetect(standImg, dectecImg, targetPts, &result);
// 
// 
// 		if (result == 2)
// 		{
// 			//发信号给RFIDDataManager，在发给screen
// 			connect(this, SIGNAL(SignalToRFIDUi(int, int)), &RFIDDataManagerIns, SIGNAL(SignalToUi(int, int)));
// 
// 			emit SignalToRFIDUi(200, img_num);
// 		}
// 
// 		img_num++;
// 	}
// 	return result;
	return MMD_RESULT::MMD_DIFF;
}

void PanoCalibraterAndCapturer::readList(string list_path)
{
// 	target_list_.clear();
// 	target_list_.resize(0);
// 
// 	QFile file(list_path);
// 	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
// 	{
// 		while (!file.atEnd())
// 		{
// 			QString temp = QString(file.readLine());
// 			TargetInfo temp_info;
// 			temp_info.img_id = temp.mid(temp.indexOf("imageid=")+8, 1).toInt();
// 			temp_info.target_id = temp.mid(temp.indexOf("targetid=")+9, 1).toInt();
// 			temp_info.pos_x = temp.mid(temp.indexOf("pos_x=")+6, 5).toInt();
// 			temp_info.pos_y = temp.mid(temp.indexOf("pos_y=")+6, 5).toInt();
// 			temp_info.w = temp.mid(temp.indexOf("w=")+2, 5).toInt();
// 			temp_info.h = temp.mid(temp.indexOf("h=")+2, 5).toInt();
// 			target_list_.push_back(temp_info);
// 		}
// 
// 		file.close();
// 	}



}
