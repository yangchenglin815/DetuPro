//
//  PixelPanoPlayer.hpp
//  QtPanoPlayer
//
//  Created by chao on 2017/10/24.
//

#ifndef PixelPanoPlayer_hpp
#define PixelPanoPlayer_hpp

#include <stdio.h>
#include "PanoPlayer.h"
#include "PixelPlugin.h"

namespace DetuPanoPlayer {
    
class PixelPanoPlayer : public PanoPlayer {
public:
    PixelPanoPlayer();
    PixelPanoPlayer(PanoPlayerPlatform platForm);
    virtual PixelPlugin* getPixelPlugin() const;
    Plugin* configPlugin(PanoramaData panoData, vector<PlayerOption> options);
    ~PixelPanoPlayer();
};
    
}

#endif /* PixelPanoPlayer_hpp */
