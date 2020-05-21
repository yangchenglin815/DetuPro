//
//  FfmpegLoadImgResult.h
//  PanoPlayer
//
//  Created by chao on 2017/11/4.
//  Copyright © 2017年 detu. All rights reserved.
//

#ifndef FfmpegLoadImgResult_h
#define FfmpegLoadImgResult_h

#include <iostream>
using namespace std;

namespace DetuPanoPlayer {
    typedef enum FfmpegLoadImgFmt {
        FfmpegLoadImgFmt_YUV420P,
        FfmpegLoadImgFmt_GRAY,
        FfmpegLoadImgFmt_RGBA,
        FfmpegLoadImgFmt_RGB,
        FfmpegLoadImgFmt_NV12,
        FfmpegLoadImgFmt_UYVY422,
    } FfmpegLoadImgFmt;
    
    typedef enum FfmpegLoadImgType {
        FfmpegLoadImgType_PNG,
        FfmpegLoadImgType_JPG,
    } FfmpegLoadImgType;
    
    //默认输出rgba格式
    typedef struct FfmpegLoadImgResult {
        unsigned char* data;
        int width;
        int height;
        FfmpegLoadImgFmt imgFmt;
        FfmpegLoadImgType imgType;
        string calibration;
    } FfmpegLoadImgResult;
}

#endif /* FfmpegLoadImgResult_h */
