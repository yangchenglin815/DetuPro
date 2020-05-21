//
//  GLOffscreenSurface.hpp
//  QtPanoPlayer
//
//  Created by chao on 2017/12/25.
//

#ifndef GLOffscreenSurface_hpp
#define GLOffscreenSurface_hpp

#include <stdio.h>
#include "PanoPlayer.h"

namespace DetuPanoPlayer {

	class GLOffscreenSurfacePrivate;
    
    class GLOffscreenSurface {
    public:
        GLOffscreenSurface(PanoPlayer* panoPlayer);
        virtual ~GLOffscreenSurface();
        void start(int renderBufferWidth, int renderBufferHeight, bool isMultiSample = true);
        void stop();
		void prepareForReadPixel();
		virtual void initOpenglContext();
		virtual void eglMakeCurrent();
		virtual void destroyOpenglContext();
        PanoPlayer* getPanoplayer();
    protected:
        PanoPlayer* mPanoPlayer;
		int mRenderBufferWidth;
    	int mRenderBufferHeight;
        bool mIsMultiSample;
		bool mStopFlag;
	private:
		GLOffscreenSurfacePrivate* mGLOffscreenSurfacePrivate;
	private:
		static void* renderThreadFunc(void* opaque);
    };
}

#endif /* GLOffscreenSurface_hpp */
