//
//  GlfwSurface.hpp
//  QtPanoPlayer
//
//  Created by chao on 2017/12/12.
//

#ifndef GlfwSurface_hpp
#define GlfwSurface_hpp

#include <stdio.h>
#include "GLOffscreenSurface.h"

namespace DetuPanoPlayer {
    
	class GlfwSurfacePrivate;
    
    class GlfwSurface : public GLOffscreenSurface {
    private:
        GlfwSurfacePrivate* mGlfwSurfacePrivate;
    public:
        GlfwSurface(PanoPlayer* panoPlayer);
        ~GlfwSurface();
		void initOpenglContext() override;
		void eglMakeCurrent() override;
		void destroyOpenglContext() override;
    };
}




#endif /* GlfwSurface_hpp */
