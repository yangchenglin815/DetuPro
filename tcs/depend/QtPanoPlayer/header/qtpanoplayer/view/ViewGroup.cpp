//
//  ViewGroup.cpp
//  PanoPlayer
//
//  Created by chao on 2017/12/1.
//  Copyright © 2017年 detu. All rights reserved.
//

#include "ViewGroup.h"

namespace DetuPanoPlayer {
    
    ViewGroup::ViewGroup(Context* context) : View(context), mMotionTarget(NULL) {
        mChildren.clear();
        isLayoutRequested = false;
    }
    
    ViewGroup::~ViewGroup() {
        
    }
    
    void ViewGroup::addView(View* view, LayoutParams* params) {
        addView(view, mChildren.size(), params);
    }
    
    void ViewGroup::addView(View* view, int index, LayoutParams* params) {
        if(index < 0 || view == NULL || params == NULL) {
            return;
        }
        view->setLayoutParams(params);
        const int size = mChildren.size();
        if(index > size) {
            return;
        }
        if(index < size) {
            mChildren[index] = view;
        } else {
            mChildren.push_back(view);
        }
        isLayoutRequested = true;
    }
    
    void ViewGroup::removeView(View* view) {
        vector<View*>::iterator it = mChildren.begin();
        for(; it != mChildren.end(); it++) {
            if(*it == view) {
                mChildren.erase(it);
                break;
            }
        }
    }
    
    void ViewGroup::removeAllViews() {
        mChildren.clear();
    }
    
    bool ViewGroup::dispatchTouchEvent(MotionEvent* motionEvent) {
        const int action = motionEvent->getAction();
        const int x = motionEvent->getX();
        const int y = motionEvent->getY();
        if(action == MotionEvent::ACTION_DOWN) {
            mMotionTarget = NULL;
            View* child = NULL;
            const int count = getChildCount();
            for(int i = 0; i < count; i++) {
                child = mChildren[i];
                child->getHitRect(&tempRect);
                if(tempRect.contains(x, y)) {
//                    const int xChild = x - child->getLeft();
//                    const int yChild = y - child->getTop();
//                    motionEvent->setX(xChild);
//                    motionEvent->setY(yChild);
                    if(child->dispatchTouchEvent(motionEvent)) {
                        mMotionTarget = child;
                        return true;
                    }
                }
            }
        }
        if(mMotionTarget != NULL) {
//            const int xChild = x - mMotionTarget->getLeft();
//            const int yChild = y - mMotionTarget->getTop();
//            motionEvent->setX(xChild);
//            motionEvent->setY(yChild);
            return mMotionTarget->dispatchTouchEvent(motionEvent);
        }
        return true;
    }
    
    void ViewGroup::dispatchDraw(Canvas* canvas, DisplayType displayType) {
        const int count = getChildCount();
        LayoutParams* lp = NULL;
        View* child = NULL;
        for(int i = 0; i < count; i++) {
            child = getChildAt(i);
            lp = child->getLayoutParams();
            if(displayType != lp->displayType) {
                continue;
            }
            child->getHitRect(&tempChildRect);
            canvas->setFrame(&tempChildRect);
            child->draw(canvas, displayType);
        }
        getHitRect(&tempChildRect);
    }
    
    bool ViewGroup::drawChild(Canvas* canvas, View* child, long drawingTime) {
		return true;
    }
    
    void ViewGroup::measureChild(View* child, int parentWidthMeasureSpec, int parentHeightMeasureSpec) {
        if(child == NULL) {
            return;
        }
        child->measure(parentWidthMeasureSpec, parentHeightMeasureSpec);
    }
    
    View* ViewGroup::getChildAt(int index) {
        return mChildren.at(index);
    }
    
    int ViewGroup::getChildCount() const {
        return mChildren.size();
    }
}
