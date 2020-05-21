/***************************************************************************************************
*
* 版权信息：Copyright (c) 得图网络 2016
*
* 文件名称：gbw_lib.h
* 摘    要：计算融合系数
*
* 当前版本：V1.0.0
* 作  者： 涂植跑
* 日  期： 2016.12
* 备  注： 创建
***************************************************************************************************/

#ifndef _GBW_LIB_H_
#define _GBW_LIB_H_

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

#include "../stitch_lib_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

using namespace cv;
using namespace std;

#define GBW_IMG_MIN_WIDTH       (64)  //图像最小宽度
#define GBW_IMG_MIN_HEIGHT      (64)  //图像最小高度
#define GBW_MAX_IMG_NUM         (10)  //图像最多个数


/***************************************************************************************************
* 功  能： 计算所需内存大小
* 参  数：
           imgNum：          -I         图像数量
           dstSize：         -I         输出图像大小
           bufSize：         -O         所需内存大小
* 返回值： 无
* 备  注：
***************************************************************************************************/
void GBW_BufferSize(STL_S32 imgNum, Size dstSize, STL_S64 *bufSize);

/***************************************************************************************************
* 功  能： 计算融合系数
* 参  数：
           masks：           -I         输入mask
           radius：          -I         模糊半径
           weights：         -O         融合系数
           workBuf：         -I         工作内存
* 返回值： 状态码
* 备  注： 
***************************************************************************************************/
STL_STATUS GBW_Process(vector<Mat> masks, STL_S32 radius, vector<Mat> &weights, STL_U08 *workBuf);



/***************************************************************************************************
* 功  能： 生成蒙版示意图以及相应边界图
* 参  数：
           masks：           -I         输入mask
           pallet：          -O         输出蒙版示意图
           masksEdge：       -O         mask边界图
           palletEdge：      -O         蒙版边界图
           workBuf：         -I         工作内存
* 返回值： 状态码
* 备  注： pallet值为0 1 2 3...； 0表示无效区，1表示图像0的区域，以此类推
***************************************************************************************************/
STL_STATUS GBW_ProcessPallet(vector<Mat> masks,  Mat &pallet, vector<Mat> &masksEdge, Mat &palletEdge,
                             STL_U08 *workBuf);

/***************************************************************************************************
* 功  能： 根据蒙版生成weight
* 参  数：
           imgNum：          -I         图像个数
           pallet：          -I         输入mask
           radius：          -I         模糊半径
           weights：         -O         融合系数
           workBuf：         -I         工作内存
* 返回值： 状态码
* 备  注： 
***************************************************************************************************/
STL_STATUS GBW_PalletWeight(STL_S32 imgNum, Mat pallet, STL_S32 radius, vector<Mat> &weights, 
                            STL_U08 *workBuf);



#ifdef __cplusplus
}
#endif



#endif // _GBW_LIB_H_







