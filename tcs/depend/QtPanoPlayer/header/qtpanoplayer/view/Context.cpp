//
//  Context.cpp
//  QtPanoPlayer
//
//  Created by chao on 2017/12/3.
//

#include "Context.h"
#include "TimeUtils.h"
#include "pthread.h"

namespace DetuPanoPlayer {
    
    class ContextPrivate {
    public:
        pthread_mutex_t mutex;
        ContextPrivate() {
            pthread_mutex_init(&mutex, NULL);
        }
        ~ContextPrivate() {
            pthread_mutex_destroy(&mutex);
        }
    };
    
    Context::Context() {
        mRunnableTasks.clear();
        mContextPrivate = new ContextPrivate;
        memset(mCacheVertexCoord, 0, sizeof(mCacheVertexCoord));
        mWindowWidth = 0;
        mWindowHeight = 0;
        mRenderWindowWidth = 0;
        mRenderWindowHeight = 0;
    }
    
    Context::~Context() {
        if(mContextPrivate != NULL) {
            delete mContextPrivate;
            mContextPrivate = NULL;
        }
    }
    
    void Context::post(Runnable runnable) {
        pthread_mutex_lock(&mContextPrivate->mutex);
        mRunnableTasks.push_back(runnable);
        pthread_mutex_unlock(&mContextPrivate->mutex);
    }
    
    void Context::postDelayed(Runnable runnable, long delayMillis) {
        int64_t currentTime = TimeUtils::getSystemTimeMills();
        runnable.time = currentTime + delayMillis;
        post(runnable);
    }
    
    void Context::remove(long executeTime) {
        pthread_mutex_lock(&mContextPrivate->mutex);
        const int count = mRunnableTasks.size();
        vector<Runnable>::iterator it;
        for(it = mRunnableTasks.begin(); it != mRunnableTasks.end(); it++) {
            Runnable* runnable = &(*it);
            if(runnable->time == executeTime) {
                mRunnableTasks.erase(it);
            }
        }
        pthread_mutex_unlock(&mContextPrivate->mutex);
    }
    
    void Context::setWindowSize(int windowWidth, int windowHeight) {
        mWindowWidth = windowWidth;
        mWindowHeight = windowHeight;
    }
    void Context::setRenderWindowSize(int renderWindowWidth, int renderWindowHeight) {
        mRenderWindowWidth = renderWindowWidth;
        mRenderWindowHeight = renderWindowHeight;
    }
    
    void Context::getVertexCoord(int x, int y, int w, int h, int windowWidth, int windowHeight, float* outCoord) {
        const int halfWindowWindth = windowWidth / 2;
        const int halfWindowHeight = windowHeight / 2;
        float left = (x - halfWindowWindth) * 1.0 / halfWindowWindth;
        float top = -((y - halfWindowHeight) * 1.0 / halfWindowHeight);
        float right = (x - halfWindowWindth + w) * 1.0 / halfWindowWindth;
        float bottom = -((y - halfWindowHeight + h) * 1.0 / halfWindowHeight);
        outCoord[0] = left;
        outCoord[1] = top;
        outCoord[2] = left;
        outCoord[3] = bottom;
        outCoord[4] = right;
        outCoord[5] = top;
        outCoord[6] = right;
        outCoord[7] = bottom;
    }
    
    void Context::panoDegreeToTextureCoord(float ath, float atv, float textureCoord[2]) {
        textureCoord[0] = (ath + 180) * 1.0 / 360;
        textureCoord[1] = (atv + 90) * 1.0 / 180;
    }
}
