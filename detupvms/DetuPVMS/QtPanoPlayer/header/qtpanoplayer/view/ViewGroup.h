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
#include "RectF.h"

using namespace std;

namespace DetuPanoPlayer {
    class ViewGroup : public View {
    public:
        ViewGroup(Context* context);
        ~ViewGroup();
        void addView(View* view, LayoutParams* params);
        void addView(View* view, int index, LayoutParams* params);
        void removeView(View* view);
        void removeAllViews();
        View* getChildAt(int index);
        View* getChildByTag(string tag);
        int getChildCount() const;
        bool dispatchTouchEvent(MotionEvent* motionEvent);
        void dispatchDraw(Canvas* canvas, DisplayType displayType);
    protected:
		void measureChild(View* child, float parentWidthMeasureSpec, float parentHeightMeasureSpec);
        bool drawChild(Canvas* canvas, View* child, long drawingTime);
    private:
        vector<View*> mChildren;
        RectF tempRect;
        RectF tempChildRect;
        View* mMotionTarget;
    };
}

#endif /* ViewGroup_hpp */
