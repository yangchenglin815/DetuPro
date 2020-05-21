//
//  CapturePixelPanoPlayer.hpp
//  QtPanoPlayer
//
//  Created by chao on 2017/12/7.
//

#ifndef CapturePixelPanoPlayer_hpp
#define CapturePixelPanoPlayer_hpp

#include <stdio.h>
#include "PixelPanoPlayer.h"
#include "QtPanoPlayer.h"

namespace DetuPanoPlayer {
    
    class ICapturePixelListener {
    public:
        ICapturePixelListener() {}
        virtual ~ICapturePixelListener() {}
        virtual void onCapturePixel() = 0;
    };
    
    class CapturePixelPanoPlayer : public PixelPanoPlayer {
    public:
        CapturePixelPanoPlayer();
        ~CapturePixelPanoPlayer();
        void setCapturePixelListener(ICapturePixelListener* listener);
        void grabPixel(int width, int height, unsigned char* outData, bool usePbo = false);
    protected:
        void handlePanoPlayerRenderOneFrame();
    protected:
        ICapturePixelListener* mCapturePixelListener;
        int* mReadPboIds;
    };
}

#endif /* CapturePixelPanoPlayer_hpp */
