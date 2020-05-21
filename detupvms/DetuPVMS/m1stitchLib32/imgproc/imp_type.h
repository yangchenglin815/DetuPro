/***************************************************************************************************
*
* 版权信息：Copyright (c) 得图网络 2017
*
* 文件名称：imp_type.h
* 摘    要：图像处理函数相关类型定义
*
* 当前版本：V1.0.0
* 作  者： 涂植跑
* 日  期： 2017.01
* 备  注： 创建
***************************************************************************************************/

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#ifndef _IMP_TYPE_H_
#define _IMP_TYPE_H_

#define IMP_HIST_BIN_NUM        (256)
#define IMP_MAP_MAX_VALUE       (255)
#define IMP_128_SHIFT8          (32768)

// 所需内存结构体
typedef struct _IMP_HIST_SPEC
{
    int *rHist;
    int *gHist;
    int *bHist;
    int *rMap;
    int *gMap;
    int *bMap;

}IMP_HIST_SPEC;


#endif //_IMP_TYPE_H_



