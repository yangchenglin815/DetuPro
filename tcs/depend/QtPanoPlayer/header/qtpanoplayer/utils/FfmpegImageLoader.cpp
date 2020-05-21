//
//  ImageLoader.cpp
//  QtPanoPlayer
//
//  Created by chao on 2017/10/28.
//

#include "FfmpegImageLoader.h"
extern "C" {
#include "pthread.h"
}
#include "FfmpegUtils.h"
#include "Md5.h"
#include "ExifUtils.h"
namespace DetuPanoPlayer {
    
    class FfmpegImageLoaderPrivate {
    public:
        FfmpegImageLoaderPrivate();
        ~FfmpegImageLoaderPrivate();
        pthread_mutex_t mMutex;
        pthread_t mLoadThread;
        FfmpegImageLoaderTask mTask;
        FfmpegImageLoaderCallBack mListener;
        bool mHaveInitLoadThread;
        void* mOpaque;
    };

    FfmpegImageLoaderPrivate::FfmpegImageLoaderPrivate() {
        pthread_mutex_init(&mMutex, NULL);
        mHaveInitLoadThread = false;
        mOpaque = NULL;

    }

    FfmpegImageLoaderPrivate::~FfmpegImageLoaderPrivate() {
        pthread_mutex_destroy(&mMutex);
    }
    
    FfmpegImageLoader::FfmpegImageLoader(string defaultCacheAbsolutePath) : defaultCacheAbsolutePath(defaultCacheAbsolutePath){
        mLoaderPrivate = new FfmpegImageLoaderPrivate;
    }
    
    FfmpegImageLoader::~FfmpegImageLoader() {
        if(mLoaderPrivate != NULL) {
            delete mLoaderPrivate;
            mLoaderPrivate = NULL;
        }
    }
    
    void* FfmpegImageLoader::loadThreadFunc(void* arg) {
        FfmpegImageLoader* imageLoader = static_cast<FfmpegImageLoader*>(arg);
        FfmpegImageLoaderPrivate* loaderPrivate = imageLoader->mLoaderPrivate;
        FfmpegImageLoaderTask* task = &loaderPrivate->mTask;
        vector<string> urls = task->urls;
        vector<int> maxWidths = task->maxWidths;
        const unsigned long size = urls.size();
        FfmpegUtils* ffmpegUtils = new FfmpegUtils;
        FfmpegLoadImgResult result;
        memset(&result, 0, sizeof(FfmpegLoadImgResult));
        for(int i = 0; i < size; i++) {
            string url = urls[i];
            string suffix =  url.substr(url.find_last_of("."));
            //http 地址图像先在本地缓存目录查找
            bool isHttp = (url.find("http://") == 0);
            bool ret = true;
            if(isHttp) {
                MD5* md5 = new MD5(url);
                string temp = md5->toStr();
                delete md5;
                string cacheFileAbsolutePath = imageLoader->defaultCacheAbsolutePath.append(temp).append(suffix);
                ret = ffmpegUtils->loadAndCacheHttpImage(url, cacheFileAbsolutePath, maxWidths[0], &result);
                url = cacheFileAbsolutePath;
            } else {
                ret = ffmpegUtils->loadImage(url, maxWidths[0], &result);
            }
            if(ret) {
                if(result.imgType == FfmpegLoadImgType_JPG) {
                    ExifUtils* exifUtils = new ExifUtils;
                    result.calibration = exifUtils->readExif(url);
                    delete exifUtils;
                    exifUtils=NULL;
                }
            }
            if(loaderPrivate->mOpaque == NULL) {
                break;
            }
            pthread_mutex_lock(&loaderPrivate->mMutex);
            if(loaderPrivate->mOpaque != NULL && loaderPrivate->mListener.onFfmpegImageLoaderItemCompleted != NULL) {
                (*loaderPrivate->mListener.onFfmpegImageLoaderItemCompleted)(loaderPrivate->mOpaque, url, i, &result, ret);
            }
            pthread_mutex_unlock(&loaderPrivate->mMutex);
        }
        delete ffmpegUtils;
        return NULL;
    }
    
    void FfmpegImageLoader::start(FfmpegImageLoaderTask task, void* opaque, FfmpegImageLoaderCallBack listener) {
        pthread_mutex_lock(&mLoaderPrivate->mMutex);
        mLoaderPrivate->mListener = listener;
        mLoaderPrivate->mTask = task;
        mLoaderPrivate->mOpaque = opaque;
        pthread_create(&mLoaderPrivate->mLoadThread, NULL, &loadThreadFunc, this);
        mLoaderPrivate->mHaveInitLoadThread = true;
        pthread_mutex_unlock(&mLoaderPrivate->mMutex);
    }

    void FfmpegImageLoader::cancel() {
        pthread_mutex_lock(&mLoaderPrivate->mMutex);
        if (!mLoaderPrivate->mHaveInitLoadThread) {
            pthread_mutex_unlock(&mLoaderPrivate->mMutex);
            return;
        }
        mLoaderPrivate->mOpaque = NULL;
        mLoaderPrivate->mHaveInitLoadThread = false;
        pthread_mutex_unlock(&mLoaderPrivate->mMutex);
        pthread_join(mLoaderPrivate->mLoadThread, NULL);
    }
}
