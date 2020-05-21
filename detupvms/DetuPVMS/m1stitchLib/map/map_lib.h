/***************************************************************************************************
*
* 版权信息：Copyright (c) 得图网络 2016
*
* 文件名称：map_lib.h
* 摘    要：映射函数
*
* 当前版本：V1.0.0
* 作  者： 涂植跑
* 日  期： 2016.12
* 备  注： 创建
***************************************************************************************************/

#ifndef _MAP_LIB_H_
#define _MAP_LIB_H_

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

#ifdef WIN32
#include "stitch_lib_defs.h"
#include "ZReproject.h"
#else
#include "stitch_lib_defs.h"
#include "ZReproject.h"
#endif



using namespace cv;

#define MAP_IMG_MIN_WIDTH       (64)  //图像最小宽度
#define MAP_IMG_MIN_HEIGHT      (64)  //图像最小高度

/**************************************************************************************************/
/* 空间映射处理类型 */
/**************************************************************************************************/
typedef enum _MAP_PROC_TYPE
{
    MAP_FISHEYE2CUBE_8UC3    = 0x0000,   // 原始鱼眼到六面体映射

    MAP_CUBE2EQTANG_8UC3     = 0x0001,   // 六面体到等距圆柱(2:1)映射

    //MAP_FISHEYE2CYL_GL_8UC3  = 0x0002,   // 原始鱼眼到等距圆柱(2:1)映射OPENGL实现

    MAP_FISHEYE2CYL_CPU_8UC3 = 0x0003,   // 原始鱼眼到等距圆柱(2:1)映射cpu实现

    MAP_GET_MASK_8UC1        = 0x0100,   // 根据映射参数，获取有效区mask

}MAP_PROC_TYPE;

/**************************************************************************************************/
/* 空间映射，需要输出映射关系表时，处理类型 */
/**************************************************************************************************/
typedef enum _MAP_PROC_TABLE_TYPE
{
    MAP_TABLE_FISHEYE2CUBE    = 0x1000,   // 原始鱼眼到六面体映射

    MAP_TABLE_CUBE2EQTANG     = 0x1001,   // 六面体到等距圆柱(2:1)映射

    MAP_TABLE_FISHEYE2CYL_CPU = 0x1003,   // 原始鱼眼到等距圆柱(2:1)映射cpu实现

}MAP_PROC_TABLE_TYPE;

/***************************************************************************************************
* 功  能： 空间映射变换
* 参  数：
           srcImg：          -I         输入图像
           procType：        -I         映射类型
           photoPm：         -I         映射参数
           dstImg：          -O         映射后图像
* 返回值： STL_OK：处理成功
*          其  他: 处理失败
* 备  注：
***************************************************************************************************/
STL_STATUS MAP_Process(Mat srcImg, MAP_PROC_TYPE procType, PhotoParam photoPm, Mat &dstImg);

/***************************************************************************************************
* 功  能： 空间映射变换，可输出映射关系表
* 参  数：
           srcImg：          -I         输入图像
           procType：        -I         映射类型
           photoPm：         -I         映射参数
           dstImg：          -O         映射后图像
           map：             -O         映射关系
* 返回值： STL_OK：处理成功
*          其  他: 处理失败
* 备  注： 
***************************************************************************************************/
STL_STATUS MAP_Process_Table(Mat srcImg, MAP_PROC_TABLE_TYPE procType, PhotoParam photoPm, Mat &dstImg, Point2f *mapTable);









#endif // _MAP_LIB_H_







