//
//  QtPanoPlayer.hpp
//  QtPanoPlayer
//
//  Created by chao on 2017/10/26.
//

#ifndef QtPanoPlayer_hpp
#define QtPanoPlayer_hpp

#include <stdio.h>
#include "PanoPlayer.h"
#include "SpherePlugin.h"
#include "VideoPlugin.h"
#include "CubePlugin.h"
#include "SpherePlugin.h"

namespace DetuPanoPlayer {
    
    class QtPanoPlayer : public PanoPlayer {
    public:
        QtPanoPlayer();
        QtPanoPlayer(PanoPlayerPlatform platform);
        ~QtPanoPlayer();
    private:
        Plugin* configPlugin(PanoramaData panoData, vector<PlayerOption> options);
        map<string, Plugin*> mapPluginCache;
    };
}

#endif /* QtPanoPlayer_hpp */
