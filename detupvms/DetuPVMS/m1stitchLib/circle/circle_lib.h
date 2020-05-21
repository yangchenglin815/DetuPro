/***************************************************************************************************
*
* 版权信息：Copyright (c) 得图网络 2016
*
* 文件名称：circle_lib.h
* 摘    要：提取鱼眼圆周镜头裁切圆
*
* 当前版本：V1.0.0
* 作  者： 涂植跑
* 日  期： 2016.12
* 备  注： 创建
***************************************************************************************************/

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#ifndef _CIRCLE_LIB_H_
#define _CIRCLE_LIB_H_



/***************************************************************************************************
* 功  能： 提取鱼眼圆周镜头裁切圆
* 参  数：
           srcImg：          -I         输入图像
           cropX：           -O         裁切圆x偏移量
           cropY：           -O         裁切圆y偏移量
           cropWidth：       -O         裁切圆宽度
           cropHeight：      -O         裁切圆高度

* 返回值： 无
* 备  注：
***************************************************************************************************/
void CIRCLE_Process(cv::Mat srcImg, int *cropX, int *cropY, int *cropWidth, int *cropHeight);



#endif //_CIRCLE_LIB_H_
