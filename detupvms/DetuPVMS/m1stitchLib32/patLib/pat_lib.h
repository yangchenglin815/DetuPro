/***************************************************************************************************
*
* 版权信息：Copyright (c) 得图网络 2016
*
* 文件名称：pat_lib.h
* 摘    要：自动获取拼接模板
*
* 当前版本：V1.0.0
* 作  者： 涂植跑
* 日  期： 2016.11
* 备  注： 创建
***************************************************************************************************/

#pragma once
#pragma execution_character_set("utf-8")
// 本文件为utf-8 编码格式

#ifndef _PAT_LIB_H_
#define _PAT_LIB_H_


#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include "../stitch_lib_defs.h"
#include "../ZReproject.h"




using namespace cv;
using namespace std;

typedef enum _PAT_F4_TYPE
{
    PAT_F4_OLD = 0x0001,    // 老的F4机器
    PAT_F4_NEW = 0x0002,    // 新的F4机器

}PAT_F4_TYPE;


#define PAT_IMG_WIDTH_MAX           (7000)
#define PAT_IMG_HEIGHT_MAX          (7000)
#define PAT_IMG_WIDTH_MIN           (64)
#define PAT_IMG_HEIGHT_MIN          (64)
#define PAT_IMG_NUM_MAX             (8)
#define PAT_IMG_NUM_MIN             (2)

#define PAT_PANO_HEIGHT             (1024)                   // 畸变矫正全景图像高度
#define PAT_PANO_WIDTH              (PAT_PANO_HEIGHT * 2)   // 畸变矫正全景图像宽度


// 裁切圆结构体
typedef struct _PAT_CORP_CIRCLE
{
    int cropX;
    int cropY;
    int cropWidth;
    int cropHeight;

}PAT_CORP_CIRCLE;


/***************************************************************************************************
* 功  能： 计算所需内存大小
* 参  数：
         imgNum：         -I       图像个数
         bufSize：        -O       所需内存大小
* 返回值： 无
* 备  注：
***************************************************************************************************/
void PAT_BufferSize(int imgNum, int *bufSize);

/***************************************************************************************************
* 功  能： F4Plus标定
* 参  数：
           srcImg：          -I         输入图像
           fileName：        -I         输入图像路径
           crop：            -I         裁切圆
           path：            -I         临时文件路径
           imgFlag：         -I         获取图像的机器类型
           photoPm：         -O         优化参数
           workBuf：         -I         工作内存
* 返回值： 0： 成功
*         -1： 失败
* 备  注： 已预知图像顺序0123
***************************************************************************************************/
int PAT_F4PlusCalib(vector<Mat> srcImg, vector<string> fileName, vector<PAT_CORP_CIRCLE> crop, 
                    string path, vector<PhotoParam> &photoPm, STL_U08 *workBuf);

/***************************************************************************************************
* 功  能： F4Plus标定，拍摄2次
* 参  数：
           srcImg0：         -I         第一次拍摄的图像
           fileName0：       -I         图像路径及名称
           srcImg1：         -I         第二次拍摄的图像
           crop：            -I         裁切圆
           path：            -I         临时文件路径
           photoPm：         -O         优化参数
           workBuf：         -I         工作内存
* 返回值： 0： 成功
*         -1： 失败
* 备  注： 已预知图像顺序0123
***************************************************************************************************/
int PAT_F4PlusCalib2Img(vector<Mat> srcImg0, vector<string> fileName0, vector<Mat> srcImg1, 
           vector<PAT_CORP_CIRCLE> crop, string path, vector<PhotoParam> &photoPm, STL_U08 *workBuf);

/***************************************************************************************************
* 功  能： F4Plus市场角优化
* 参  数：
           srcImg：          -I         输入图像
           fileName：        -I         图像路径及名称
           path：            -I         临时文件路径
           photoPm：         -I/O       原始参数以及优化后输出参数
           workBuf：         -I         工作内存
* 返回值： 0： 成功
*         -1： 失败
* 备  注： 在已有模板的情况下，优化市场角参数；
*          已预知图像顺序0123
***************************************************************************************************/
int PAT_F4PlusViewAdjust(vector<Mat> srcImg, vector<string> fileName, string path,
                         vector<PhotoParam> &photoPm, STL_U08 *workBuf);

/***************************************************************************************************
* 功  能： F4市场角优化
* 参  数：
           srcImg：          -I         输入图像
           fileName：        -I         图像路径及名称
           path：            -I         临时文件路径
           imgFlag：         -I         获取图像的机器类型
           photoPm：         -I/O       原始参数以及优化后输出参数
           workBuf：         -I         工作内存
* 返回值： 0： 成功
*         -1： 失败
* 备  注： 在已有模板的情况下，优化市场角参数；
***************************************************************************************************/
int PAT_F4ViewAdjust(vector<Mat> srcImg, vector<string> fileName, string path, PAT_F4_TYPE imgFlag,
                     vector<PhotoParam> &photoPm, STL_U08 *workBuf);

/***************************************************************************************************
* 功  能： M1标定
* 参  数：
           srcImg：          -I         输入图像
           fileName：        -I         输入图像路径
           crop：            -I         裁切圆
           path：            -I         临时文件路径
           imgFlag：         -I         获取图像的机器类型
           photoPm：         -O         优化参数
           workBuf：         -I         工作内存
* 返回值： 0： 成功
*         -1： 失败
* 备  注： 已预知图像顺序0132
***************************************************************************************************/
int PAT_M1Calibration(vector<Mat> srcImg, vector<string> fileName, vector<PAT_CORP_CIRCLE> crop, 
                      string path, vector<PhotoParam> &photoPm, STL_S32 *score, STL_U08 *workBuf);

/***************************************************************************************************
* 功  能： M1标定
* 参  数：
           srcImg：          -I         输入图像
           fileName：        -I         输入图像路径
           crop：            -I         裁切圆
           path：            -I         临时文件路径
           imgFlag：         -I         获取图像的机器类型
           photoPm：         -O         优化参数
           workBuf：         -I         工作内存
* 返回值： 0： 成功
*         -1： 失败
* 备  注： 已预知图像顺序0132
***************************************************************************************************/
int PAT_M1ViewAdjust(vector<Mat> srcImg, vector<string> fileName, string path,
                     vector<PhotoParam> &photoPm, STL_S32 *score, STL_U08 *workBuf);

/***************************************************************************************************
* 功  能： F4标定
* 参  数：
           srcImg：          -I         输入图像
           fileName：        -I         输入图像路径
           crop：            -I         裁切圆
           path：            -I         临时文件路径
           imgFlag：         -I         获取图像的机器类型
           photoPm：         -O         优化参数
           workBuf：         -I         工作内存
* 返回值： 0： 成功
*         -1： 失败
* 备  注：
***************************************************************************************************/
int PAT_ProcessAuto(vector<Mat> srcImg, vector<string> fileName, vector<PAT_CORP_CIRCLE> crop, 
                    string path, PAT_F4_TYPE imgFlag, vector<PhotoParam> &photoPm, uchar *workBuf);


/***************************************************************************************************
* 功  能： F4标定，图像顺序不确定时使用
* 参  数：
           srcImg：          -I         输入图像
           fileName：        -I         输入图像路径
           crop：            -I         裁切圆
           path：            -I         临时文件路径
           imgFlag：         -I         获取图像的机器类型
           photoPm：         -O         优化参数
           workBuf：         -I         工作内存
* 返回值： 0： 成功
*         -1： 失败
* 备  注：
***************************************************************************************************/
int PAT_ProcessAutoDisOrder(vector<Mat> srcImg, vector<string> fileName, vector<PAT_CORP_CIRCLE> crop, 
                   string path, PAT_F4_TYPE imgFlag, vector<PhotoParam> &photoPm, STL_U08 *workBuf);


/***************************************************************************************************
* 功  能： 智能模板
* 参  数：
           imgFile：         -I         输入图像路径
           ptsFile：         -I         pts路径
           path：            -I         临时文件路径
           imgFlag：         -I         获取图像的机器类型
           photoPm：         -O         优化后全景参数
           workBuf：         -I         工作内存
* 返回值： 0： 成功
*         -1： 失败
* 备  注：
***************************************************************************************************/
int PAT_ProcessIntellgent(vector<string> imgFile, string ptsFile, string path, PAT_F4_TYPE imgFlag,
                          vector<PhotoParam>& photoPm, uchar *workBuf);

/***************************************************************************************************
* 功  能： F4Plus标定
* 参  数：
           srcImg：          -I         输入图像
           fileName：        -I         输入图像路径
           crop：            -I         裁切圆
           path：            -I         临时文件路径
           imgFlag：         -I         获取图像的机器类型
           photoPm：         -O         优化参数
           workBuf：         -I         工作内存
* 返回值： 0： 成功
*         -1： 失败
* 备  注： 无需预知图像顺序
***************************************************************************************************/
int PAT_ProcessAutoF4Plus(vector<Mat> srcImg, vector<string> fileName, vector<PAT_CORP_CIRCLE> crop, 
                          string path, vector<PhotoParam> &photoPm, STL_U08 *workBuf);














/***************************************************************************************************
* 功  能： 自动模板
* 参  数：
           srcImg：          -I         输入图像
           fileName：        -I         输入图像路径
           crop：            -I         裁切圆
           hFov：            -I         相机视场角
           path：            -I         临时文件路径
           photoPm：         -O         优化参数
           workBuf：         -I         工作内存
* 返回值： 状态码
* 备  注：
***************************************************************************************************/
STL_STATUS PAT_ProcessCommon(vector<Mat> srcImg, vector<string> fileName, vector<PAT_CORP_CIRCLE> crop, 
                          STL_F32 hFov, string path, vector<PhotoParam> &photoPm, STL_U08 *workBuf);







#endif // _PAT_LIB_H_







