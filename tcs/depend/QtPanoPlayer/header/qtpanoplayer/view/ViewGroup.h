//
//  ViewGroup.hpp
//  PanoPlayer
//
//  Created by chao on 2017/12/1.
//  Copyright © 2017年 detu. All rights reserved.
//

#ifndef ViewGroup_hpp
#define ViewGroup_hpp

#include <stdio.h>
#include "View.h"
#include <vector>
#include "Rect.h"

using namespace std;

namespace DetuPanoPlayer {
    class ViewGroup : public View {
    public:
        bool isLayoutRequested;
    public:
        ViewGroup(Context* context);
        ~ViewGroup();
        void addView(View* view, LayoutParams* params);
        void addView(View* view, int index, LayoutParams* params);
        void removeView(View* view);
        void removeAllViews();
        View* getChildAt(int index);
        int getChildCount() const;
        bool dispatchTouchEvent(MotionEvent* motionEvent);
        void dispatchDraw(Canvas* canvas, DisplayType displayType);
    protected:
        void measureChild(View* child, int parentWidthMeasureSpec, int parentHeightMeasureSpec);
        bool drawChild(Canvas* canvas, View* child, long drawingTime);
    private:
        vector<View*> mChildren;
        Rect tempRect;
        Rect tempChildRect;
        View* mMotionTarget;
    };
}

#endif /* ViewGroup_hpp */
