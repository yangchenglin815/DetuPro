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
#include "RectF.h"
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
		View* mParent;
		bool mIsLayoutRequested;
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
		float getMeasureWidth() const;
		float getMeasureHeight() const;
		float getWidth() const;
		float getHeight() const;
		float getLeft() const;
		float getTop() const;
		float getRight() const;
		float getBottom() const;
        void setTag(string tag);
        string getTag() const;
		virtual void measure(float widthMeasureSpec, float heightMeasureSpec);
		virtual void layout(float left, float top, float right, float bottom);
        virtual void draw(Canvas* canvas, DisplayType displayType);
        virtual void dispatchDraw(Canvas* canvas, DisplayType displayType);
        virtual bool dispatchTouchEvent(MotionEvent* motionEvent);
        virtual bool onTouchEvent(MotionEvent* motionEvent);
        virtual void refreshDrawableState();
		void requestLayout();
        bool performClick();
        virtual void getHitRect(RectF* outRect);
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
		float mMeasureWidth;
		float mMeasureHeight;
		float mLeft;
		float mRight;
		float mTop;
		float mBottom;
        bool mIsLayoutChanged;
        int mMotionFlag;
        int mDrawableFlag;
    protected:
		virtual void onMeasure(float widthMeasureSpec, float heightMeasureSpec);
		virtual void onLayout(bool changed, float l, float t, float r, float b);
        virtual void onDraw(Canvas* canvas, DisplayType displayType);
		void setMeasureDimension(float measureWidth, float measureHeight);
		bool setFrame(float left, float top, float right, float bottom);
		RectF mCacheRectF;
    private:
        int64_t mCheckTapTime;
        int64_t mCheckLongClickTime;
        string mTag;
        ViewPrivate* viewPrivate;
    };
}

#endif /* View_hpp */
