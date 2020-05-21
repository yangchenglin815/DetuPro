/***************************************************************************************************
*
* 版权信息：Copyright (c) 得图网络 2017
*
* 文件名称：imp_lib.h
* 摘    要：图像处理函数
*
* 当前版本：V1.0.0
* 作  者： 涂植跑
* 日  期： 2017.01
* 备  注： 创建
***************************************************************************************************/

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#ifdef WIN32
#include "stitch_lib_defs.h"
#else
#include "stitch_lib_defs.h"
#endif

#ifndef _IMP_LIB_H_
#define _IMP_LIB_H_

using namespace cv;


#define IMP_IMG_MIN_WIDTH       (64)  // 图像最小宽度
#define IMP_IMG_MIN_HEIGHT      (64)  // 图像最小高度

/***************************************************************************************************
* 功  能： bgr转yuv420
* 参  数：
           srcImg：          -I         输入bgr图像
           width：           -I         图像宽度
           height：          -I         图像高度
           yImg：            -O         输出y图像
           uImg：            -O         输出u图像
           vImg：            -O         输出v图像
* 返回值： STL_OK：处理成功
*          其  他: 处理失败
* 备  注：
***************************************************************************************************/
STL_STATUS IMP_DataConvert_bgr2yuv420(STL_U08 *srcImg, STL_S32 width, STL_S32 height, STL_U08 *yImg,
                                      STL_U08 *uImg, STL_U08 *vImg);

/***************************************************************************************************
* 功  能： bgra转yuv420
* 参  数：
           srcImg：          -I         输入bgra图像
           width：           -I         图像宽度
           height：          -I         图像高度
           yImg：            -O         输出y图像
           uImg：            -O         输出u图像
           vImg：            -O         输出v图像
* 返回值： STL_OK：处理成功
*          其  他: 处理失败
* 备  注：
***************************************************************************************************/
STL_STATUS IMP_DataConvert_bgra2yuv420(STL_U08 *srcImg, STL_S32 width, STL_S32 height, STL_U08 *yImg,
                                      STL_U08 *uImg, STL_U08 *vImg);

/***************************************************************************************************
* 功  能： yuv420转bgr
* 参  数：
yImg：            -O         输入y图像
uImg：            -O         输入u图像
vImg：            -O         输入v图像
dstImg：          -I         输出bgr图像
width：           -I         图像宽度
height：          -I         图像高度

* 返回值： STL_OK：处理成功
*          其  他: 处理失败
* 备  注：
***************************************************************************************************/
STL_STATUS IMP_DataConvert_yuv4202bgr(STL_U08 *yImg, STL_U08 *uImg, STL_U08 *vImg, STL_S32 width, 
                                      STL_S32 height, STL_U08 *dstImg);




#endif //_IMP_LIB_H_

