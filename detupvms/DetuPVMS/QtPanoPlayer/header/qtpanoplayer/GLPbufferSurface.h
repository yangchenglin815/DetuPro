//
//  GLPbufferSurface.hpp
//  QtPanoPlayer
//
//  Created by chao on 2017/11/11.
//

#ifndef GLPbufferSurface_hpp
#define GLPbufferSurface_hpp

#include <stdio.h>
#include "GLOffscreenSurface.h"

namespace DetuPanoPlayer {
    
    class GLPbufferSurfacePrivate;
    
    class GLPbufferSurface : public GLOffscreenSurface {
    private:
        GLPbufferSurfacePrivate* pBufferSurfacePrivate;
    public:
        GLPbufferSurface(PanoPlayer* panoPlayer);
        ~GLPbufferSurface();
		void initOpenglContext() override;
		void eglMakeCurrent() override;
		void destroyOpenglContext() override;
    };
}

#endif /* GLPbufferSurface_hpp */
