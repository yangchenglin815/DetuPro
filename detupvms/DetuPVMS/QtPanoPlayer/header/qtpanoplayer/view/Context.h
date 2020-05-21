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

    typedef struct Message {
        int what;
        int arg1;
        int arg2;
        void* opaque;
    } Message;
    
    typedef struct Runnable {
        int64_t time;
        void* opaque;
        Message message;
        void (*run)(void* opaque, Message msg);
    } Runnable;
        
    class Context {
    public:
        Context();
        virtual ~Context();
        virtual void post(Runnable runnable);
        virtual void postDelayed(Runnable runnable, long delayMillis);
        virtual void remove(long executeTime);
		virtual void clear();
		virtual void panoDegreeToWindowPoint(float ath, float atv, float widthRatio, float heightRatio, float windowPoint[2]) = 0;
        void panoDegreeToTextureCoord(float ath, float atv, float textureCoord[2]);
        void setWindowSize(int windowWidth, int windowHeight);
        void setRenderWindowSize(int renderWindowWidth, int renderWindowHeight);
    protected:
        vector<Runnable> mRunnableTasks;
    private:
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


