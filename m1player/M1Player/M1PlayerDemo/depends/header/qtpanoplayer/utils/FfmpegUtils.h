//
//  FfmpegUtils.hpp
//  QtPanoPlayer
//
//  Created by chao on 2017/10/28.
//

#ifndef FfmpegUtils_hpp
#define FfmpegUtils_hpp

#include <stdio.h>
#include <iostream>
using namespace std;

namespace DetuPanoPlayer {
    
    typedef enum FfmpegLoadImgFmt {
        FfmpegLoadImgFmt_YUV420P,
        FfmpegLoadImgFmt_GRAY,
        FfmpegLoadImgFmt_RGBA,
        FfmpegLoadImgFmt_NV12,
        FfmpegLoadImgFmt_UYVY422,
    } FfmpegLoadImgFmt;
    
    //默认输出yuv420p格式
    typedef struct FfmpegLoadImgResult {
        unsigned char* data;
        int width;
        int height;
        FfmpegLoadImgFmt imgFmt;
    } FfmpegLoadImgResult;

    class FfmpegUtils {
    public:
        //根据maxWidth加载图片，会根据maxWidth等比例缩放
        bool loadImage(string fileAbsolutePath, string cacheImgAbsolutePath, int maxWidth, FfmpegLoadImgResult* outResult, FfmpegLoadImgFmt fmt = FfmpegLoadImgFmt_YUV420P);
    };
}

#endif /* FfmpegUtils_hpp */
