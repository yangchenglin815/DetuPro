//
//  SequenceImageView.cpp
//  QtPanoPlayer
//
//  Created by chao on 2017/12/5.
//

#include "SequenceImageView.h"
#include "pthread.h"
#include "FfmpegUtils.h"

namespace DetuPanoPlayer {
    
    class SequenceImageViewPrivate {
    public:
        SequenceImageViewPrivate() {
            urls.clear();
            results.clear();
            drawIndex = 0;
            isLoadState = false;
        }
        ~SequenceImageViewPrivate() {
            
        }
        
        static void* loadIconThreadFunc(void* opaque) {
            SequenceImageViewPrivate* sivPrivate = static_cast<SequenceImageViewPrivate*>(opaque);
            if(sivPrivate != NULL) {
                sivPrivate->loadIconFunc();
            }
            return NULL;
        }
        
        void releaseLoadData() {
            const int count = results.size();
            for(int i = 0; i < count;i++) {
                if(results[i].data != NULL) {
                    free(results[i].data);
                }
            }
            results.clear();
        }
        
        void loadIconFunc() {
            isLoadState = true;
            releaseLoadData();
            FfmpegUtils ffmpegUtils;
            const int count = urls.size();
            for(int i = 0; i < count;i++) {
                string url = urls[i];
                FfmpegLoadImgResult result;
                ffmpegUtils.loadImage(url, 10000, &result, FfmpegLoadImgFmt_RGBA);
                results.push_back(result);
            }
            isLoadState = false;
        }
        
        void onDraw(Canvas* canvas, int drawWidth, int drawHeight, float rx, float ry, float rz, bool isDistorted) {
            const int loadCount = results.size();
            const int urlSize = urls.size();
            if(isLoadState || loadCount == 0 || urlSize == 0 || urlSize != loadCount) {
                return;
            }
            FfmpegLoadImgResult* result = &results[drawIndex++];
            if(result->data != NULL) {
                //qDebug("drawBitmap:%d, %d\n", result->width, result->height);
                canvas->drawBitmap(result->data, 90, 90, rx, ry, rz, isDistorted, NULL);
            }
            if(drawIndex == urlSize - 1) {
                drawIndex = 0;
            }
        }
    public:
        vector<string> urls;
        vector<FfmpegLoadImgResult> results;
        pthread_t loadIconThreadId;
        int drawIndex;
        bool isLoadState;
    };
    
    SequenceImageView::SequenceImageView(Context* context) : ImageView(context) {
        sivPrivate = new SequenceImageViewPrivate;
    }
    
    SequenceImageView::~SequenceImageView() {
        if(sivPrivate != NULL) {
            delete sivPrivate;
            sivPrivate = NULL;
        }
    }
    
    void SequenceImageView::onDraw(Canvas* canvas, DisplayType displayType) {
        ImageView::onDraw(canvas, displayType);
        sivPrivate->onDraw(canvas, mLayoutParams->width, mLayoutParams->height, mLayoutParams->rx, mLayoutParams->ry, mLayoutParams->rz, displayType == DisplayType_DISTORTED);
    }
    
	void SequenceImageView::setSequenceDrawableUrls(vector<string> urls) {
		//if (sivPrivate->loadIconThreadId != NULL)
		//{
		//	pthread_join(sivPrivate->loadIconThreadId, NULL);
		//}
        sivPrivate->urls = urls;
        pthread_create(&sivPrivate->loadIconThreadId, NULL, &SequenceImageViewPrivate::loadIconThreadFunc, sivPrivate);
    }
}
