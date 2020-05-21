/***************************************************************************************************
*
* 版权信息：Copyright (c) 得图网络 2018
*
* 文件名称：M1LIB_MoveDetect_lib.h
* 摘    要：M1物体移动检测
*
* 当前版本：V1.0.0
* 作  者： 涂植跑
* 日  期： 2018.08
* 备  注： 创建
***************************************************************************************************/

#include <opencv2/core/core.hpp>

#ifndef _M1LIB_MOVEDETECT_LIB_H_
#define _M1LIB_MOVEDETECT_LIB_H_

typedef enum _MMD_RESULT
{
    MMD_SAME = 1,
    MMD_DIFF = 2
}MMD_RESULT;

/***************************************************************************************************
* 功  能： 检测物体是否有变化
* 参  数：
           backGoundImg：    -I         背景图像
           curImg：          -I         当前检测图像
           targetPts：       -I         需跟踪的目标点
           difTh：           -I         移动距离阈值
           result：          -O         检测结果
* 返回值： 0： 处理成功
*         -1： 处理失败
* 备  注： 如果输入的目标点为空，会自动检测目标点
***************************************************************************************************/
int MMD_MoveDetect(cv::Mat backGoundImg, cv::Mat curImg, std::vector<cv::Point2f> targetPts,
                   MMD_RESULT *result);



#endif // _M1LIB_MOVEDETECT_LIB_H_


