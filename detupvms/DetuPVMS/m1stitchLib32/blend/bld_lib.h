/***************************************************************************************************
*
* 版权信息：Copyright (c) 得图网络 2017
*
* 文件名称：bld_lib.h
* 摘    要：图像渲染
*
* 当前版本：V1.0.0
* 作  者： 涂植跑
* 日  期： 2017.02
* 备  注： 创建
***************************************************************************************************/

#pragma once
#pragma execution_character_set("utf-8")
// 本文件为utf-8 编码格式

#ifndef _BLD_LIB_H_
#define _BLD_LIB_H_


#include <string>
#include <vector>
#include <opencv2/gpu/gpumat.hpp>


#include "../stitch_lib_defs.h"
#include "../ZReproject.h"


//#include "..\openGl\OPENGL_REPROJECTION.h"

#include "multi_cpu_lib.h"
#include "linear_cpu_lib.h"
#include "Blend_type.h"

using namespace cv;
using namespace std;

#define TEST_OPENGL_USED
//#define BLD_TEST_TIME

#define BLD_IMG_MIN_WIDTH       (64)      // 图像最小宽度
#define BLD_IMG_MAX_WIDTH       (10000)   // 图像最大宽度
#define BLD_IMG_MIN_HEIGHT      (64)      // 图像最小高度
#define BLD_IMG_MAX_HEIGHT      (10000)   // 图像最大高度
#define BLD_MIN_IMG_NUM         (2)       // 图像最少个数
#define BLD_MAX_IMG_NUM         (10)      // 图像最多个数
#define BLD_MAX_THREAD_NUM      (4)       // 最大线程数

typedef enum _BLD_PROC_TYPE
{
    BLD_CPU_MULTI     = 0x0002,    // 多重融合CPU实现
    BLD_CPU_LINEAR    = 0x0012,    // 线性融合CPU实现

}BLD_PROC_TYPE;

typedef struct _BLD_CPU_SPEC
{
    STL_U08 *mulBuf;
    STL_U08 *lnBuf;
    STL_U08 *expsBuf;

    vector<Mat> masks;
    vector<Mat> repImg;
    vector<Mat> yRepImg;
    vector<Mat> uRepImg;
    vector<Mat> vRepImg;

    Mat         dstImg; // bgr输入，cpu融合，yuv输出时，所需内存 CV_8UC3

    // opengl处理
    void        *repPanoGL;
    Mat         tmpMat;     // yuv图像 opengl映射时使用
    Mat         cvtMat;     // 输入yuv，点映射时，bgr转换内存

}BLD_CPU_SPEC;



typedef struct _BLD_CONFIG
{
    vector<PhotoParam> photoPm;         // 空间映射参数
    Size               srcSize;         // 输入图像大小
    Size               dstSize;         // 输出图像大小
    IMG_FORMAT         outImgFormat;    // 输出图像格式
    MULTI_UV_TYPE      uvType;

}BLD_CONFIG;



class BlendFunction
{
public:
    BlendFunction();

public:

    // 预处理，输入图像为RGB格式
    STL_STATUS BLD_Prepare(BLD_PROC_TYPE procType, BLD_CONFIG cfg);

    // 融合处理，输入图像为RGB格式
    STL_STATUS BLD_Process(RenderInput *inputData, BLD_PROC_TYPE procType, BLD_CONFIG cfg, RenderOutput *outputData);

    // 预处理，输入图像为yuv格式
    STL_STATUS BLD_PrepareYuv(BLD_PROC_TYPE procType, BLD_CONFIG cfg);

    // 融合处理，输入图像为yuv格式
    STL_STATUS BLD_ProcessYuv(RenderInputYuv *inputData, BLD_PROC_TYPE procType, BLD_CONFIG cfg, 
                              RenderOutput *outputData);

//     // GPU线性融合优化，输入图像为yuv格式
//     STL_STATUS BLD_LinearGpuYuv(RenderInputYuv *inputData, BLD_PROC_TYPE procType, BLD_CONFIG cfg,
//                                 RenderOutput *outputData);

    // 释放内存
    void BLD_ReleaseMemory();

private:
    // 内存
    STL_U08                 *cpuBuf_;

    // 句柄
    BLD_CPU_SPEC            cpuSpec_;

    // rgb图像格式，融合句柄
    MULTI_CPU_SPEC          multiCpuHandle_;        // 多重融合cpu实现句柄
    LINEAR_CPU_SPEC         linearCpuHandle_;       // 线性融合cpu实现句柄

    // yuv图像格式，融合句柄
    MULTI_CPU_SPEC_YUV      multiCpuHandleYuv_;     // yuv图像，多重融合cpu实现句柄
    LINEAR_CPU_SPEC_YUV     linearCpuHandleYuv_;    // yuv图像，线性融合cpu实现句柄


private:
    STL_STATUS BLD_CreateHandle(BLD_PROC_TYPE procType, BLD_CONFIG cfg);

    STL_STATUS BLD_CreateHandleYuv(BLD_PROC_TYPE procType, BLD_CONFIG cfg);
};


#endif // _BLD_LIB_H_





