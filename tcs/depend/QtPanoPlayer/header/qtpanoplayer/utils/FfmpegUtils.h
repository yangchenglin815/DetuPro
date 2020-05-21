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
#include "FfmpegLoadImgResult.h"
using namespace std;

namespace DetuPanoPlayer {
    
    class FfmpegUtils {
    public:
        //根据maxWidth加载图片，会根据maxWidth等比例缩放
        bool loadImage(string fileAbsolutePath, int maxWidth, FfmpegLoadImgResult* outResult, FfmpegLoadImgFmt fmt = FfmpegLoadImgFmt_RGBA);
        
        bool loadAndCacheHttpImage(string httpUrl, string cacheImgAbsolutePath, int maxWidth, FfmpegLoadImgResult* outResult, FfmpegLoadImgFmt fmt = FfmpegLoadImgFmt_RGBA);
        
        bool cacheHttpImage(string httpUrl, string cacheImgAbsolutePath);
    };
}

#endif /* FfmpegUtils_hpp */
