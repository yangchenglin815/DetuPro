/***************************************************************************************************
*
* 版权信息：Copyright (c) 得图网络 2016
*
* 文件名称：gbw_proc.h
* 摘    要：计算融合系数相关处理函数
*
* 当前版本：V1.0.0
* 作  者： 涂植跑
* 日  期： 2016.12
* 备  注： 创建
***************************************************************************************************/

#ifndef _GBW_PROC_H_
#define _GBW_PROC_H_

#include "gbw_type.h"
#include "../stitch_lib_defs.h"


#ifdef __cplusplus
extern "C" {
#endif

using namespace cv;
using namespace std;


/***************************************************************************************************
* 功  能： 计算融合系数
* 参  数：
           masks：           -I         输入mask
           radius：          -I         模糊半径
           weights：         -O         融合系数
           spec：            -I         内存结构体
* 返回值： 无
* 备  注： 
***************************************************************************************************/
void GBW_GetWeight(vector<Mat> masks, int radius, vector<Mat> &weights, GBW_SPEC *spec);

// 降采样
void GBW_DownSample_8UC1(Mat srcImg, Mat &dstImg);

// 上采样
void GBW_UpSample_32SC1(Mat srcImg, Mat &dstImg);
void GBW_UpSample_8UC1(Mat srcImg, Mat &dstImg);

// 相邻图像
void GBW_NeightborImg(vector<Mat> masks, vector< vector<int>> &neighborImg, int sizeTh);

// 获取idxImg图像
void GBW_GetIdxImg(vector<Mat> masks, vector< vector<int>> &neighborImg, vector<Mat> distMat, Mat &idxImg);

// 计算相邻图像idxImg
void GBW_NeighborIdxImg(Mat mask1, Mat mask2, Mat distMat1, Mat distMat2, int idx1, int idx2, 
                        vector<int> procIdx, int firstTime, Mat &idxImg);

// 检测idx是否已经确定;
// 1:已经处理过，不用再处理
// 0:没处理过
int GBW_CheckIdx(int idx, vector<int> procIdx);

// mask拼接
void GBW_MaskStitch(Mat srcMask, Mat &dstMast);

void GBW_DistanceTransform(vector<Mat> masks, Mat stichMask, vector<Mat> &distMat);

// 生成uniqmask
void GBW_GetUniqMask(Mat idxImg, Mat belong, vector<Mat> &uniqMask);

// mask模糊
void GBW_MaskBlur(vector<Mat> uniqMask, vector<Mat> uniqMask2, int radius, vector<Mat> blurDist,
                  vector<Mat> masks, Mat distTmp1, Mat distTmp2, Mat srcTmp);

// 改变位置
void GBW_ChangeLocation(cv::Mat src, cv::Mat &dst);

void GBW_CalcWeights(vector<cv::Mat> dists, vector<cv::Mat> &weights);

/***************************************************************************************************
* 功  能： 生成蒙版示意图
* 参  数：
           masks：           -I         输入mask
           pallet：          -O         输出蒙版示意图
           spec：            -I         内存结构体
* 返回值： 无
* 备  注： 
***************************************************************************************************/
void GBW_GetPallet(vector<Mat> masks, Mat &pallet, GBW_SPEC *spec);

/***************************************************************************************************
* 功  能： 输入蒙版，生成weight
* 参  数：
           imgNum：          -I         图像个数
           pallet：          -I         输入mask
           radius：          -I         模糊半径
           weights：         -O         融合系数
           spec：            -I         内存结构体
* 返回值： 无
* 备  注： 
***************************************************************************************************/
void GBW_PalletGetWeight(int imgNum, Mat pallet, int radius, vector<Mat> &weights, GBW_SPEC *spec);

/***************************************************************************************************
* 功  能： 蒙版边缘检测
* 参  数：
           pallet：          -I         蒙版示意图
           palletEdge：      -O         蒙版边缘图
* 返回值： 无
* 备  注： 
***************************************************************************************************/
void GBW_GetPalletEdge(Mat pallet, Mat &palletEdge);

/***************************************************************************************************
* 功  能： mask边缘检测
* 参  数：
           masks：          -I         蒙版示意图
           masksEdge：      -O         蒙版边缘图
* 返回值： 无
* 备  注： 
***************************************************************************************************/
void GBW_GetMasksEdge(Mat masks, Mat &masksEdge);


#ifdef __cplusplus
}
#endif

#endif // _GBW_PROC_H_







