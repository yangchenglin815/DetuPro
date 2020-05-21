//
//  Context.hpp
//  QtPanoPlayer
//
//  Created by chao on 2017/12/3.
//

#ifndef Context_hpp
#define Context_hpp

#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;

namespace DetuPanoPlayer {
    
    typedef struct Runnable {
        int64_t time;
        void* opaque;
        void (*run)(void* opaque);
    } Runnable;
    
    class ContextPrivate;
    
    class Context {
    public:
        Context();
        virtual ~Context();
        virtual void post(Runnable runnable);
        virtual void postDelayed(Runnable runnable, long delayMillis);
        virtual void remove(long executeTime);
        virtual void panoDegreeToWindowPoint(float ath, float atv, int width, int height, float windowPoint[2]) = 0;
        void panoDegreeToTextureCoord(float ath, float atv, float textureCoord[2]);
        void setWindowSize(int windowWidth, int windowHeight);
        void setRenderWindowSize(int renderWindowWidth, int renderWindowHeight);
    protected:
        vector<Runnable> mRunnableTasks;
    private:
        ContextPrivate* mContextPrivate;
        float mCacheVertexCoord[8];
        int mWindowWidth;
        int mWindowHeight;
        int mRenderWindowWidth;
        int mRenderWindowHeight;
    private:
        void getVertexCoord(int x, int y, int w, int h, int windowWidth, int windowHeight, float* outCoord);
    };
}

#endif /* Context_hpp */


