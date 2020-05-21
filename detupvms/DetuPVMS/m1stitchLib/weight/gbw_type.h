/***************************************************************************************************
*
* 版权信息：Copyright (c) 得图网络 2016
*
* 文件名称：gbw_type.h
* 摘    要：计算融合系数相关结构体等定义头文件
*
* 当前版本：V1.0.0
* 作  者： 涂植跑
* 日  期： 2016.12
* 备  注： 创建
***************************************************************************************************/

#include <vector>
#include <opencv2/core/core.hpp>

#ifndef _GBW_TYPE_H_
#define _GBW_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

#define GBW_UNIT_SHIFT           (16)
#define GBW_UNIT                 (1 << GBW_UNIT_SHIFT)

// 内存变量结构体
typedef struct _GBW_SPEC
{
    std::vector<cv::Mat> uniqueMasks;
    std::vector<cv::Mat> uniqueMasks2;
    std::vector<cv::Mat> weightTmp;
    std::vector<cv::Mat> reMasks;
    std::vector<cv::Mat> distMat;
    std::vector<cv::Mat> blurDist;


    cv::Mat distTmp1;
    cv::Mat distTmp2;
    cv::Mat belong;
    cv::Mat stichMask;
    cv::Mat idxImg;
    cv::Mat srcTmp;

} GBW_SPEC;




#ifdef __cplusplus
}
#endif



#endif // _GBW_TYPE_H_







