#ifndef GLSurfaceRender_h__
#define GLSurfaceRender_h__

#include "IGestureListener.h"
#include <iostream>
#include "Context.h"

namespace DetuPanoPlayer {

	class GLSurfaceRenderPrivate;

    class GLSurfaceRender : public Context {
    public:
        int defaultFrameBufferObject = 0;
        IGestureListener *gestureListener;
    private:
		GLSurfaceRenderPrivate* mPrivate;
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

		void post(Runnable runnable);
		void postDelayed(Runnable runnable, long delayMillis);
		void remove(long executeTime);
		void clear();
    };

}
#endif // GLSurfaceRender_h__
