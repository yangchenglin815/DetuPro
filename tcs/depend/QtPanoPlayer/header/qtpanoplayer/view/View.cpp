//
//  View.cpp
//  QtPanoPlayer
//
//  Created by chao on 2017/12/1.
//

#include "View.h"
#include "TimeUtils.h"
#include <cstdint>
#include "pthread.h"
#include "FfmpegUtils.h"

namespace DetuPanoPlayer {
    
    class ViewPrivate {
    public:
        pthread_t loadStateDrawableThread;
        FfmpegLoadImgResult results[2];
        string urls[2];
        
        ViewPrivate() {
            for(int i = 0; i < 2; i++) {
                results[i].data = NULL;
                results[i].width = 0;
                results[i].height = 0;
            }
            //loadStateDrawableThread = 0;
        }
        
        void releaseLogData() {
            for(int i = 0; i < 2; i++) {
                if(results[i].data != NULL) {
                    free(results[i].data);
                    results[i].data = NULL;
                }
            }
        }
        
        ~ViewPrivate() {
            releaseLogData();
        }
        
        static void* loadStateDrawbleThreadFunc(void* opaque) {
            ViewPrivate* viewPrivate = static_cast<ViewPrivate*>(opaque);
            viewPrivate->releaseLogData();
            FfmpegUtils ffmpegUtils;
            ffmpegUtils.loadImage(viewPrivate->urls[0], 10000, &viewPrivate->results[0]);
            ffmpegUtils.loadImage(viewPrivate->urls[1], 10000, &viewPrivate->results[1]);
            return NULL;
        }
        
    };
    
    View::View(Context* context) : mOnClickListener(NULL), mOnTouchListener(NULL), mVisibility(VISIBLE), mMeasureWidth(0), mMeasureHeight(0){
        mLeft = 0;
        mTop = 0;
        mRight = 0;
        mBottom = 0;
        mIsLayoutChanged = false;
        mMotionFlag = 0;
        mCheckTapTime = 0;
        mCheckLongClickTime = 0;
        mLayoutParams = new LayoutParams(0, 0);
        mDrawableFlag = DRAWABLE_STATE_UN_FOCUSED;
        mContext = context;
        viewPrivate = new ViewPrivate;
    }
    
    View::~View() {
        if(mLayoutParams != NULL) {
            delete mLayoutParams;
            mLayoutParams = NULL;
        }
        if(viewPrivate != NULL) {
            delete viewPrivate;
            viewPrivate = NULL;
        }
    }
    
    void View::setOnClickListener(OnClickListener* listener) {
        mOnClickListener = listener;
    }
    
    void View::setOnTouchListener(OnTouchListener* listener) {
        mOnTouchListener = listener;
    }
    
    void View::onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        const int width = mLayoutParams->width;
        const int height = mLayoutParams->height;
        setMeasureDimension(width, height);
    }
    
    void View::measure(int widthMeasureSpec, int heightMeasureSpec) {
        onMeasure(widthMeasureSpec, heightMeasureSpec);
    }
    void View::setMeasureDimension(int measureWidth, int measureHeight) {
        mMeasureWidth = measureWidth;
        mMeasureHeight = measureHeight;
    }
    
    void View::onDraw(Canvas* canvas, DisplayType displayType) {
        FfmpegLoadImgResult* result = NULL;
        switch (mDrawableFlag) {
            case DRAWABLE_STATE_FOCUSED:
                result = &viewPrivate->results[0];
                break;
            case DRAWABLE_STATE_UN_FOCUSED:
                result = &viewPrivate->results[1];
                break;
            default:
                break;
        }
        if(result->data != NULL) {
            canvas->drawBitmap(result->data, result->width, result->height, mLayoutParams->rx, mLayoutParams->ry, mLayoutParams->rz, displayType == DisplayType_DISTORTED,  NULL);
        }
    }
    
    void View::setLayoutParams(LayoutParams* params) {
        *mLayoutParams = *params;
    }
    
    LayoutParams* View::getLayoutParams() const {
        return mLayoutParams;
    }
    
    void View::onLayout(bool changed, int l, int t, int r, int b) {
        
    }
    
    void View::layout(int left, int top, int right, int bottom) {
        setFrame(left, top, right, bottom);
        if(mIsLayoutChanged) {
           
        }
         onLayout(mIsLayoutChanged, left, top, right, bottom);
    }
    
    bool View::setFrame(int left, int top, int right, int bottom) {
        if(mLeft != left || mTop != top || mRight != right || mBottom != bottom) {
            mIsLayoutChanged = true;
            mLeft = left;
            mTop = top;
            mRight = right;
            mBottom = bottom;
        } else {
            mIsLayoutChanged = false;
        }
		return true;
    }
    
    bool View::dispatchTouchEvent(MotionEvent* motionEvent) {
        if(mOnTouchListener != NULL && mOnTouchListener->onTouch(this, motionEvent)) {
            return true;
        }
        return onTouchEvent(motionEvent);
    }
    
    void View::draw(Canvas* canvas, DisplayType displayType) {
        onDraw(canvas, displayType);
        dispatchDraw(canvas, displayType);
    }
    
    void View::dispatchDraw(Canvas* canvas, DisplayType displayType) {
        
    }
    
    void View::setFocusStateDrawableUrls(string focusDrawablePath, string unFocusDrawablePath) {
		/*if(viewPrivate->loadStateDrawableThread) {

		}*/
		//pthread_join(viewPrivate->loadStateDrawableThread, NULL);
        viewPrivate->urls[0] = focusDrawablePath;
        viewPrivate->urls[1] = unFocusDrawablePath;
        pthread_create(&viewPrivate->loadStateDrawableThread, NULL, &ViewPrivate::loadStateDrawbleThreadFunc, viewPrivate);
    }
    
    static void checkTapEvent(void* opaque) {
        View* view = static_cast<View*>(opaque);
        view->checkForTap();
    }
    
    void View::checkForTap() {
        if(mCheckTapTime != 0) {
            mMotionFlag = MOTION_PRESSED;
            mDrawableFlag = DRAWABLE_STATE_FOCUSED;
            refreshDrawableState();
            mCheckLongClickTime = TimeUtils::getSystemTimeMills() + LONG_PRESS_TIMEOUT;
            mCheckTapTime = 0;
        }
    }
    
    void View::checkForLongClick() {
        
    }
    
    Context* View::getContext() const {
        return mContext;
    }
    
    bool View::onTouchEvent(MotionEvent* motionEvent) {
        switch (motionEvent->getAction()) {
            case MotionEvent::ACTION_DOWN:
                mMotionFlag = MOTION_PRE_PRESSED;
                mCheckTapTime = TimeUtils::getSystemTimeMills() + TAP_TIMEOUT;
                Runnable runnableCheckTap;
                runnableCheckTap.opaque = this;
                runnableCheckTap.time = mCheckTapTime;
                runnableCheckTap.run = &checkTapEvent;
                mContext->postDelayed(runnableCheckTap, TAP_TIMEOUT);
                break;
            case MotionEvent::ACTION_MOVE:{
                const int x = motionEvent->getX();
                const int y = motionEvent->getY();
                int64_t currentTime = TimeUtils::getSystemTimeMills();
                if(x < getLeft() - TOUCH_SLOP || x >= getRight() + TOUCH_SLOP || y < getTop() - TOUCH_SLOP || y >= getBottom() + TOUCH_SLOP) {
                    //触点超出边界
                    mCheckTapTime = 0;
                    if(mMotionFlag == MOTION_PRESSED) {
                        mCheckLongClickTime = 0;
                        mMotionFlag = 0;
                        mDrawableFlag = DRAWABLE_STATE_UN_FOCUSED;
                        refreshDrawableState();
                    }
                } else {
                    if(currentTime >= mCheckTapTime) {
                        //checkForTap();
                    } else if(currentTime >= mCheckLongClickTime) {
                        //checkForLongClick();
                    }
                }
            }
                break;
            case MotionEvent::ACTION_UP:{
                if(mMotionFlag == MOTION_PRESSED) {
                    //此为点击事件，移除长按检测
                    mCheckLongClickTime = 0;
                    mDrawableFlag = DRAWABLE_STATE_UN_FOCUSED;
                    performClick();
                }
            }
                break;
                
            default:
                break;
        }
        return true;
    }
    
    void View::refreshDrawableState() {
        
    }
    
    void View::setTag(string tag) {
        mTag = tag;
    }
    string View::getTag() const {
        return mTag;
    }
    
    void View::setVisibility(int visibility) {
        mVisibility = visibility;
    }
    int View::getVisibility() const {
        return mVisibility;
    }
    
    int View::getMeasureWidth() const {
        return mMeasureWidth;
    }
    
    int View::getMeasureHeight() const {
        return mMeasureHeight;
    }
    
    int View::getWidth() const {
        return mRight - mLeft;
    }
    int View::getHeight() const {
        return mBottom - mTop;
    }
    
    int View::getLeft() const {
        return mLeft;
    }
    int View::getTop() const {
        return mTop;
    }
    int View::getRight() const {
        return mRight;
    }
    int View::getBottom() const {
        return mBottom;
    }
    
    bool View::performClick() {
        bool ret = true;
        if(mOnClickListener != NULL) {
            mOnClickListener->onClick(this);
        }
        return ret;
    }
    
    void View::getHitRect(Rect* outRect) {
        outRect->set(mLeft, mTop, mRight, mBottom);
    }
    
}
