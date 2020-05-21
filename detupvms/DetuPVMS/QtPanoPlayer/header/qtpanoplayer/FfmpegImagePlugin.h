//
//  FfmpegImagePlugin.hpp
//  QtPanoPlayer
//
//  Created by chao on 2017/10/28.
//

#ifndef FfmpegImagePlugin_hpp
#define FfmpegImagePlugin_hpp

#include <stdio.h>
#include "PixelPlugin.h"

#define  PLUGIN_DESCRIPTION_FFMPEG_IMAGE "ffmpeg_image_plugin"

//cube模式 一张缩略图和六面图
#define PLUGIN_FFMPEG_IMAGE_MAX_FRAME_SIZE 7

namespace DetuPanoPlayer {
    
    class FfmpegImageLoader;
    
    class FfmpegImagePlugin : public PixelPlugin {
    public:
        PluginFrame cacheFrames[PLUGIN_FFMPEG_IMAGE_MAX_FRAME_SIZE];
        FfmpegImagePlugin(string imgCachePath);
        bool havePostPreparedEvent;
        ~FfmpegImagePlugin();
        void setPanoData(PanoramaData panoramaData);
        void startLoadImage(PanoNodeImage nodeImage);
        string getDescription();
    private:
        FfmpegImageLoader* imageLoader;
        static void* cancelThreadFunc(void* arg);
        string imgCachePath;
    };
}

#endif /* FfmpegImagePlugin_hpp */
