/***************************************************************************************************
*
* 版权信息：Copyright (c) 得图网络 2017
*
* 文件名称：multi_cpu_lib.h
* 摘    要：多重融合CPU实现
*
* 当前版本：V1.0.0
* 作  者： 涂植跑
* 日  期： 2017.02
* 备  注： 创建
***************************************************************************************************/


#ifndef _MULTI_CPU_LIB_H_
#define _MULTI_CPU_LIB_H_

#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include "Blend_type.h"
#include "../stitch_lib_defs.h"


using namespace cv;
using namespace std;

#define MULTI_CPU_IMG_MIN_WIDTH       (64)      //图像最小宽度
#define MULTI_CPU_IMG_MAX_WIDTH       (10000)   //图像最大宽度
#define MULTI_CPU_IMG_MIN_HEIGHT      (64)      //图像最小高度
#define MULTI_CPU_IMG_MAX_HEIGHT      (10000)   //图像最大高度
#define MULTI_CPU_MIN_IMG_NUM         (2)       //图像最少个数
#define MULTI_CPU_MAX_IMG_NUM         (10)      //图像最多个数


// 内存结构体
typedef struct _MULTI_CPU_SPEC
{
    STL_U08            *calWeightBuf;   // 计算weight所需内存

    Mat                 validArea;      // 全景图有效区域 CV_8UC1
    vector<Mat>         imgMask;        // aux  CV_16SC1
    vector<Mat>         weights;        // 权重 CV_32SC1
    vector<vector<Mat>> weightsPyr;     // weight金字塔  CV_16UC1
    vector<Mat>         resultPyr;      // 融合结果金字塔 CV_32SC1
    vector<Mat>         imgPyr;         // 图像金字塔 CV_16SC1
    vector<Mat>         newAlpha;       // 临时内存 CV_16SC1
    vector<Mat>         dstImage32S;    // 临时结果 CV_32SC1 可以是CV_16SC1
    vector<Mat>         dstAlpha32S;    // 临时结果 CV_32SC1
    vector<Mat>         pyrCalTmp;      // 金字塔计算中间过程缓存 CV_16SC1
    vector<Mat>         pyrTmp;         // 重建金字塔缓存 CV_32SC1

}MULTI_CPU_SPEC;

typedef struct _MULTI_CPU_SPEC_YUV
{
    STL_U08            *calWeightBuf;   // 计算weight所需内存
    Mat                 validArea;      // 全景图有效区域 CV_8UC1
    Mat                 uSum;           // u累加和 CV_32SC1
    Mat                 vSum;           // v累加和 CV_32SC1
    vector<Mat>         imgMask;        // aux  CV_16SC1
    vector<Mat>         weights;        // 权重 CV_32SC1
    vector<vector<Mat>> weightsPyr;     // weight金字塔  CV_16UC1
    vector<vector<Mat>> imgMaskPyr;     // imgMask金字塔  CV_16SC1
    //vector<vector<Mat>> uvMaskPyr;      // uvMask金字塔   CV_16SC1
    vector<Mat>         resultPyr;      // 融合结果金字塔 CV_32SC1
    vector<Mat>         imgPyr;         // 图像金字塔 CV_16SC1
    vector<Mat>         dstImage32S;    // 临时结果 CV_32SC1 可以是CV_16SC1
    vector<Mat>         pyrCalTmp;      // 金字塔计算中间过程缓存 CV_16SC1
    vector<Mat>         pyrTmp;         // 重建金字塔缓存 CV_32SC1
    vector<Mat>         weightSum;      // 权重和  CV_32SC1

}MULTI_CPU_SPEC_YUV;


/***************************************************************************************************
* 功  能： 获取所需内存大小
* 参  数：
           imgNum：          -I         图像个数
           dstSize：         -I         输出图像大小
           bufSize：         -O         显存大小
* 返回值： 无
* 备  注：
***************************************************************************************************/
void MultiCpu_BufSize(STL_S32 imgNum, Size dstSize, STL_S64 *bufSize);
void MultiCpu_BufSize_yuv(STL_S32 imgNum, Size dstSize, STL_S64 *bufSize);

/***************************************************************************************************
* 功  能： 创建句柄
* 参  数：
           imgNum：          -I         图像个数
           dstSize：         -I         输出图像大小
           spec：            -O         句柄
           workBuf：         -I         工作内存
* 返回值： 无
* 备  注：
***************************************************************************************************/
void MultiCpu_Create(STL_S32 imgNum, Size dstSize, MULTI_CPU_SPEC *spec, STL_U08 *workBuf);
void MultiCpu_Create_yuv(STL_S32 imgNum, Size dstSize, MULTI_CPU_SPEC_YUV *spec, STL_U08 *workBuf);


/***************************************************************************************************
* 功  能： 预处理
* 参  数：
           imgNum：          -I         图像个数
           dstSize：         -I         输出图像大小
           masks：           -O         映射图像有效区
           persistHandle：   -O         句柄
           cpuBuf：          -O         cpu内存
* 返回值： 无
* 备  注：
***************************************************************************************************/
STL_STATUS MultiCpu_Perpare(STL_S32 imgNum, Size dstSize, vector<Mat> masks, MULTI_CPU_SPEC *spec);
STL_STATUS MultiCpu_Perpare_yuv(STL_S32 imgNum, Size dstSize, vector<Mat> masks, MULTI_CPU_SPEC_YUV *spec);

/***************************************************************************************************
* 功  能： 多重融合, bgr图像处理
* 参  数：
           imgNum：          -I         图像个数
           srcImg：          -I         输入y图像
           dstImg：          -O         输出y图像
           spec：            -I         内存信息结构体
* 返回值： 状态码
* 备  注：
***************************************************************************************************/
STL_STATUS MultiCpu_Process(STL_S32 imgNum, vector<Mat> srcImg, Mat &dstImg, MULTI_CPU_SPEC *spec);

/***************************************************************************************************
* 功  能： 多重融合, yuv图像处理
* 参  数：
           imgNum：          -I         图像个数
           ySrc：            -I         输入y图像
           uSrc：            -I         输入u图像
           vSrc：            -I         输入v图像
           yDst：            -O         输出y图像
           uDst：            -O         输出u图像
           vDst：            -O         输出v图像
           spec：            -I         内存信息结构体
* 返回值： 状态码
* 备  注：
***************************************************************************************************/
STL_STATUS MultiCpu_Process_yuv(STL_S32             imgNum,
                                vector<Mat>         ySrc,
                                vector<Mat>         uSrc,
                                vector<Mat>         vSrc,
                                MULTI_UV_TYPE       uvType,
                                Mat                &yDst,
                                Mat                &uDst,
                                Mat                &vDst,
                                MULTI_CPU_SPEC_YUV *spec);




#endif // _MULTI_CPU_LIB_H_







