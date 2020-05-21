#pragma once
#pragma execution_character_set("utf-8")
// 本文件为utf-8 编码格式

#ifndef _BLEND_TYPE_H_
#define _BLEND_TYPE_H_

#include <functional>
#include <vector>
#include <cstdint>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "../stitch_lib_defs.h"


#define BLD_MAX_IMG_DATA_NUM       (30)



enum outputFormat
{
    RGB = 0,
    YUV = 1,
};


typedef enum _IMG_FORMAT
{
    IMG_BGR    = 0,
    IMG_YUV420 = 1

}IMG_FORMAT;



typedef enum _MULTI_UV_TYPE
{
    MULTI_UV_MULTI  = 0x0001,     // 多重融合中uv分量使用多重融合
    MULTI_UV_LINEAR = 0x0002,    // 多重融合中uv分量使用线性融合

}MULTI_UV_TYPE;


struct RenderInfo
{
    STL_U64 ts;
    STL_S32 frameindex;
    STL_S64 duration;
};
struct RenderInput
{
    std::vector<cv::Mat> matCpu;
    struct               RenderInfo info;
};


struct RenderInputYuv
{
    std::vector<cv::Mat> yImgCpu;       // cpu拼接时输入y图像
    std::vector<cv::Mat> uImgCpu;       // cpu拼接时输入u图像
    std::vector<cv::Mat> vImgCpu;       // cpu拼接时输入v图像
    struct RenderInfo    info;

    std::vector<cv::Size>        addImgSize;    // 增加需要输出的图像分辨率
};

struct RenderOutput
{
    unsigned char *data[BLD_MAX_IMG_DATA_NUM];
    int            step[BLD_MAX_IMG_DATA_NUM];
    int            width;
    int            height;
    IMG_FORMAT     imgFormat;

    struct RenderInfo info;

	RenderOutput(){
		width = 0;
		height = 0;
		for (int i = 0; i < BLD_MAX_IMG_DATA_NUM; i++)
		{
			data[i] = NULL;
		}
		memset(step, 0, sizeof(int) * BLD_MAX_IMG_DATA_NUM);
	}
};



#endif // _BLEND_TYPE_H_


