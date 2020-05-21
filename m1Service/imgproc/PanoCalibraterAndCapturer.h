/************************************************
* \file playmodewgt.h
*
* \author HuZhengdong
* \date 20170721
* 截图类，负责抓全景图片
************************************************/
#ifndef PANOCAPTURER_H
#define PANOCAPTURER_H

#include "constStruct.h"
#include "M1LIB_MoveDetect_lib.h"

#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>

using namespace std;
using namespace cv;
class PanoCalibraterAndCapturer 
{
public:
	PanoCalibraterAndCapturer();
	~PanoCalibraterAndCapturer();

public:


	//检测入侵
	MMD_RESULT CheckWarningBoard();
	
	void readList(string list_path);

private:
				

	//线性拼接用
	vector<Mat>         ySrcCpu_;
	vector<Mat>         uSrcCpu_;
	vector<Mat>         vSrcCpu_;

	vector<Mat>         ySrcCpu_nv12_;
	vector<Mat>         uSrcCpu_nv12_;
	vector<Mat>         vSrcCpu_nv12_;

	cv::Size    srcSize_;								// 输入图像大小


	cv::Size pano_size_;


	//锁
	boost::mutex mutex_capture_;

	vector<TargetInfo> target_list_;
};

#endif // PANOCAPTURER_H
