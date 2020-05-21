/***************************************************************************************************
*
* 版权信息：Copyright (c) 得图网络 2016
*
* 文件名称：map_proc.h
* 摘    要：映射相关处理函数
*
* 当前版本：V1.0.0
* 作  者： 涂植跑
* 日  期： 2016.12
* 备  注： 创建
***************************************************************************************************/


#ifndef _MAP_PROC_H_
#define _MAP_PROC_H_

#include "map_type.h"
#include "ZReproject.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;


void MAP_SphereRotation(MAP_VECTOR3 v, float radians, MAP_VECTOR3 *b);



void MAP_GetImageXY(PhotoParam param, int x, int y, int dstHeight, int dstWidth,
                    float *dstx, float *dsty);

// 获取有效区mask
void MAP_GetMask_8UC1(PhotoParam photoPm, Mat &mask);





#endif // _MAP_PROC_H_







