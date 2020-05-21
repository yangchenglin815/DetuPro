//
//  View.hpp
//  QtPanoPlayer
//
//  Created by chao on 2017/12/1.
//

#ifndef View_hpp
#define View_hpp

#include <stdio.h>
#include "LayoutParams.h"
#include "MotionEvent.h"
#include "Rect.h"
#include "Canvas.h"
#include "Context.h"
#include <iostream>
#include <cstdint>
using namespace std;

namespace DetuPanoPlayer {
    
    class ViewPrivate;
    
    class View {
    public:
        static const int VISIBLE = 0;
        static const int INVISIBLE = 1;
        static const int GONE = 2;
        static const int TAP_TIMEOUT = 115;
        static const int LONG_PRESS_TIMEOUT = 500;
        static const int TOUCH_SLOP = 16;
        
        static const int MOTION_INVALIDATE = 0;
        static const int MOTION_PRESSED = 1;
        static const int MOTION_PRE_PRESSED = 2;
        
        static const int DRAWABLE_STATE_UN_FOCUSED = 0;
        static const int DRAWABLE_STATE_FOCUSED = 1;
    public:
        class OnClickListener {
        public:
            OnClickListener(){}
            virtual ~OnClickListener() {}
            virtual void onClick(View* view) = 0;
        };
        
        class OnTouchListener {
        public:
            OnTouchListener(){}
            virtual ~OnTouchListener() {}
            virtual bool onTouch(View* view, MotionEvent* event) = 0;
        };
        
        View(Context* context);
        virtual ~View();
        void setOnClickListener(OnClickListener* listener);
        void setOnTouchListener(OnTouchListener* listener);
        void setLayoutParams(LayoutParams* params);
        LayoutParams* getLayoutParams() const;
        void setVisibility(int visibility);
        int getVisibility() const;
        int getMeasureWidth() const;
        int getMeasureHeight() const;
        int getWidth() const;
        int getHeight() const;
        int getLeft() const;
        int getTop() const;
        int getRight() const;
        int getBottom() const;
        void setTag(string tag);
        string getTag() const;
        virtual void measure(int widthMeasureSpec, int heightMeasureSpec);
        virtual void layout(int left, int top, int right, int bottom);
        virtual void draw(Canvas* canvas, DisplayType displayType);
        virtual void dispatchDraw(Canvas* canvas, DisplayType displayType);
        virtual bool dispatchTouchEvent(MotionEvent* motionEvent);
        virtual bool onTouchEvent(MotionEvent* motionEvent);
        virtual void refreshDrawableState();
        bool performClick();
        virtual void getHitRect(Rect* outRect);
        Context* getContext() const;
        void checkForTap();
        void checkForLongClick();
        void setFocusStateDrawableUrls(string focusDrawablePath, string unFocusDrawablePath);
    protected:
        OnClickListener* mOnClickListener;
        OnTouchListener* mOnTouchListener;
        LayoutParams* mLayoutParams;
        Context* mContext;
        int mVisibility;
        int mMeasureWidth;
        int mMeasureHeight;
        int mLeft;
        int mRight;
        int mTop;
        int mBottom;
        bool mIsLayoutChanged;
        int mMotionFlag;
        int mDrawableFlag;
    protected:
        virtual void onMeasure(int widthMeasureSpec, int heightMeasureSpec);
        virtual void onLayout(bool changed, int l, int t, int r, int b);
        virtual void onDraw(Canvas* canvas, DisplayType displayType);
        void setMeasureDimension(int measureWidth, int measureHeight);
        bool setFrame(int left, int top, int right, int bottom);
    private:
        int64_t mCheckTapTime;
        int64_t mCheckLongClickTime;
        string mTag;
        ViewPrivate* viewPrivate;
    };
}

#endif /* View_hpp */
