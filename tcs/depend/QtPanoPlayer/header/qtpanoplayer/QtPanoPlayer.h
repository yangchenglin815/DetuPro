//
//  QtPanoPlayer.hpp
//  QtPanoPlayer
//
//  Created by chao on 2017/10/26.
//

#ifndef QtPanoPlayer_hpp
#define QtPanoPlayer_hpp

#include <stdio.h>
#include "DetuConfig.h"
#include "PanoPlayer.h"

#if CONFIG_DETU_IJK

#include "VideoPlugin.h"

#endif
#if CONFIG_DETU_FFMPEG

#include "ImagePlugin.h"

#endif

#include "CubePlugin.h"

namespace DetuPanoPlayer {

    class QtPanoPlayer : public PanoPlayer {
    public:
        QtPanoPlayer();

        QtPanoPlayer(PanoPlayerPlatform platform);

        ~QtPanoPlayer();

    protected:
        Plugin *configPlugin(PanoramaData panoData, vector<PlayerOption> options);

        map<string, Plugin *> mapPluginCache;

        void close() override;
    public:
        virtual void handlePanoPlayerRenderOneFrame();
    };
}

#endif /* QtPanoPlayer_hpp */
