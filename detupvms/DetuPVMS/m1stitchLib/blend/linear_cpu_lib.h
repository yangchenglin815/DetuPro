/***************************************************************************************************
*
* 版权信息：Copyright (c) 得图网络 2017
*
* 文件名称：linear_cpu_lib.h
* 摘    要：线性融合CPU实现
*
* 当前版本：V1.0.0
* 作  者： 涂植跑
* 日  期： 2017.02
* 备  注： 创建
***************************************************************************************************/

#ifndef _LINEAR_CPU_LIB_H_
#define _LINEAR_CPU_LIB_H_

#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include "../stitch_lib_defs.h"

using namespace cv;
using namespace std;

#define LINEAR_CPU_IMG_MIN_WIDTH       (64)      //图像最小宽度
#define LINEAR_CPU_IMG_MAX_WIDTH       (10000)   //图像最大宽度
#define LINEAR_CPU_IMG_MIN_HEIGHT      (64)      //图像最小高度
#define LINEAR_CPU_IMG_MAX_HEIGHT      (10000)   //图像最大高度
#define LINEAR_CPU_MIN_IMG_NUM         (2)       //图像最少个数
#define LINEAR_CPU_MAX_IMG_NUM         (10)      //图像最多个数



// 内存结构体
typedef struct _LINEAR_CPU_SPEC
{
    STL_U08    *calWeightBuf;
    vector<Mat> weights;
    Mat         sumImg;
    Mat         validArea;

}LINEAR_CPU_SPEC;

typedef struct _LINEAR_CPU_SPEC_YUV
{
    STL_U08    *calWeightBuf;
    vector<Mat> weights;
    Mat         validArea;
    Mat         ySum;
    Mat         uSum;
    Mat         vSum;

}LINEAR_CPU_SPEC_YUV;


/***************************************************************************************************
* 功  能： 获取所需cpu内存大小
* 参  数：
           imgNum：          -I         图像个数
           dstSize：         -I         输出图像大小
           bufSize：         -O         显存大小
* 返回值： 无
* 备  注：
***************************************************************************************************/
void LinearCpu_BufSize(STL_S32 imgNum, Size dstSize, STL_S64 *bufSize);
void LinearCpu_BufSize_yuv(STL_S32 imgNum, Size dstSize, STL_S64 *bufSize);

/***************************************************************************************************
* 功  能： 创建句柄
* 参  数：
           imgNum：          -I         图像个数
           dstSize：         -I         输出图像大小
           bufSize：         -O         显存大小
* 返回值： 无
* 备  注：
***************************************************************************************************/
void LinearCpu_CreateHandle(STL_S32 imgNum, Size dstSize, LINEAR_CPU_SPEC *spec, STL_U08 *workBuf);
void LinearCpu_CreateHandle_yuv(STL_S32 imgNum, Size dstSize, LINEAR_CPU_SPEC_YUV *spec, STL_U08 *workBuf);


/***************************************************************************************************
* 功  能： yuv图像处理，预处理
* 参  数：
           imgNum：          -I         图像个数
           dstSize：         -I         输出图像大小
           masks：           -I         映射图像有效区
           spec：            -O         句柄
* 返回值： 无
* 备  注：
***************************************************************************************************/
STL_STATUS LinearCpu_Perpare(STL_S32 imgNum, Size dstSize, vector<Mat> masks, LINEAR_CPU_SPEC *spec);
STL_STATUS LinearCpu_Perpare_yuv(STL_S32 imgNum, Size dstSize, vector<Mat> masks, LINEAR_CPU_SPEC_YUV *spec);

/***************************************************************************************************
* 功  能： 线性融合, BGR图像
* 参  数：
           imgNum：          -I         图像个数
           ySrc：            -I         输入图像
           yDst：            -O         输出图像
           persistHandle：   -I         句柄
* 返回值： 状态码
* 备  注：
***************************************************************************************************/
STL_STATUS LinearCpu_Process(STL_S32 imgNum, vector<Mat> srcImg, Mat &dstImg, LINEAR_CPU_SPEC *spec);

/***************************************************************************************************
* 功  能： yuv图像处理，线性融合
* 参  数：
           imgNum：          -I         图像个数
           ySrc：            -I         输入y图像
           uSrc：            -I         输入u图像
           vSrc：            -I         输入v图像
           yDst：            -O         输出y图像
           uDst：            -O         输出u图像
           vDst：            -O         输出v图像
           spec：            -I         句柄
* 返回值： 状态码
* 备  注：
***************************************************************************************************/
STL_STATUS LinearCpu_Process_yuv(STL_S32              imgNum,
                                 vector<Mat>          ySrc,
                                 vector<Mat>          uSrc,
                                 vector<Mat>          vSrc,
                                 Mat                 &yDst,
                                 Mat                 &uDst,
                                 Mat                 &vDst,
                                 LINEAR_CPU_SPEC_YUV *spec);


#endif // _LINEAR_CPU_LIB_H_







