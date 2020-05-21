//
//  ImageLoader.hpp
//  QtPanoPlayer
//
//  Created by chao on 2017/10/28.
//

#ifndef ImageLoader_hpp
#define ImageLoader_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "FfmpegLoadImgResult.h"
using namespace std;

namespace DetuPanoPlayer {
    
    typedef struct FfmpegImageLoaderCallBack {
        void (*onFfmpegImageLoaderItemCompleted)(void* opaque, string url, int index, FfmpegLoadImgResult* result, bool isSuccess);
    } FfmpegImageLoaderCallBack;
    
    class FfmpegImageLoaderPrivate;
    
    typedef struct FfmpegImageLoaderTask {
        vector<string> urls;
        vector<int> maxWidths;
    } FfmpegImageLoaderTask;
    
    class FfmpegImageLoader {
    public:
        FfmpegImageLoader(string defaultCacheAbsolutePath);
        ~FfmpegImageLoader();
        void start(FfmpegImageLoaderTask task, void* opaque, FfmpegImageLoaderCallBack listener);
        void cancel();
    public:
        FfmpegImageLoaderPrivate* mLoaderPrivate;
        static void* loadThreadFunc(void* arg);
        string defaultCacheAbsolutePath;
    };
}

#endif /* ImageLoader_hpp */
