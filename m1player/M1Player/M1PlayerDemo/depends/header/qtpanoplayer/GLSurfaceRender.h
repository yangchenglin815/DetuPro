#ifndef GLSurfaceRender_h__
#define GLSurfaceRender_h__

#include "IGestureListener.h"
#include <iostream>

namespace DetuPanoPlayer {

    class GLSurfaceRender {
    public:
        int defaultFrameBufferObject = 0;
        IGestureListener *gestureListener = nullptr;
        int zoomRatio;
    public:
        GLSurfaceRender() {
        }

        ~GLSurfaceRender() {
        }

        virtual void setDefaultFrameBufferObject(int defaultFrameBufferObject);

        void setGestureListener(IGestureListener *gestureListener);

        IGestureListener *getGestureListener() const;
        /************************************************************************/
        /* @param ratio ���ű���(1-100)
        /************************************************************************/
        void setZoomRatio(int ratio);

        virtual void onSurfaceCreated() = 0;

        virtual void onSurfaceChanged(int width, int height);

        virtual void onDrawFrame() = 0;
    };

}
#endif // GLSurfaceRender_h__
