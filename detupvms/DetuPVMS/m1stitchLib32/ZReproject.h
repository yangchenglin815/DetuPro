#pragma once
//#include <opencv2/core/core.hpp>
#include <memory>
#include <string>
#include <vector>
//#include "..\..\depano-include\libsift\ControlPoint.h"

#ifndef _Z_REPROJECT_H_
#define _Z_REPROJECT_H_

using namespace std;

struct PhotoParam
{
	int width;
	int height;

	int cropX;
	int cropY;
	int cropWidth;
	int cropHeight;

	int f; 
	double v;

	double y;
	double r;
	double p;

	double a;
	double b;
	double c;

	double d;
	double e;

	double g;
	double t;

    bool isVerticFlip;
	bool isflip;

};

// 控制点结构体
typedef struct _PAT_CPS
{
    int   imgIdx0;
    int   imgIdx1;
    float x0;
    float x1;
    float y0;
    float y1;

}PAT_CPS;

// 全景输入参数结构体
typedef struct _PAT_PANO_PARAM
{
    int         imgNum;     // 图像数量(镜头数量)
    PhotoParam *photoPm;    // 每个图像参数
    PAT_CPS    *cps;        // 控制点信息
    int         cpsNum;     // 控制点数量

}PAT_PANO_PARAM;

void loadPhotoParamFromPTS(string fileName, vector<PhotoParam>& params);

void ReadPtsFile(string fileName, PAT_PANO_PARAM *panoPm, float *cpsDist, int *distNum);



#endif // _Z_REPROJECT_H_

