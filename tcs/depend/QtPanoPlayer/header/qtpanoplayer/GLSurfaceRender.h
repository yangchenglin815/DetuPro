#ifndef GLSurfaceRender_h__
#define GLSurfaceRender_h__

#include "IGestureListener.h"
#include <iostream>
#include "Context.h"

namespace DetuPanoPlayer {

    class GLSurfaceRender : public Context {
    public:
        int defaultFrameBufferObject = 0;
        IGestureListener *gestureListener;
    protected:

    public:
        GLSurfaceRender();

        virtual ~GLSurfaceRender();

        virtual void setDefaultFrameBufferObject(int defaultFrameBufferObject);

        void setGestureListener(IGestureListener *gestureListener);

        IGestureListener *getGestureListener() const;

        virtual void onSurfaceCreated() = 0;

        virtual void onSurfaceChanged(int width, int height);

        virtual void onDrawFrame();

        virtual void close();
    };

}
#endif // GLSurfaceRender_h__
