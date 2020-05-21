//
//  FrameLayout.cpp
//  QtPanoPlayer
//
//  Created by chao on 2017/12/1.
//

#include "FrameLayout.h"
#include <math.h>
#include <stdlib.h>
#include <stdlib.h>

namespace DetuPanoPlayer {
    
    FrameLayout::FrameLayout(Context* context) : ViewGroup(context) {
        
    }
    FrameLayout::~FrameLayout() {
        
    }
    
    void FrameLayout::onLayout(bool changed, int l, int t, int r, int b) {
        const int count = getChildCount();
        View* view = NULL;
        LayoutParams* lp = NULL;
        for(int i = 0; i < count; i++) {
            view = getChildAt(i);
            if(view->getVisibility() == View::GONE) {
                continue;
            }
            const int measureWidth = view->getMeasureWidth();
            const int measureHeight = view->getMeasureHeight();
            lp = view->getLayoutParams();
            float windowPoint[2] = {0.0f};
            switch (lp->displayType) {
                case DisplayType_DISTORTED:
                    mContext->panoDegreeToTextureCoord(lp->ath, lp->atv, windowPoint);
                    windowPoint[0] *= mLayoutParams->width;
                    windowPoint[1] *= mLayoutParams->height;
                    break;
                case DisplayType_UN_DISTORTED:
                    mContext->panoDegreeToWindowPoint(lp->ath, lp->atv, measureWidth, measureHeight, windowPoint);
                    break;
                    
                default:
                    break;
            }
            int childLeft = windowPoint[0];
            int childTop = windowPoint[1];
            int childRight = childLeft + measureWidth;
//            if(childRight > r) {
//                childRight = r;
//            }
            int childBottom = childTop + measureHeight;
//            if(childBottom > b) {
//                childBottom = b;
//            }
            view->layout(childLeft, childTop, childRight, childBottom);
        }
    }
    
    void FrameLayout::onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        int maxWidth = 0;
        int maxHeight = 0;
        const int count = getChildCount();
        View* view = NULL;
        for(int i = 0; i < count; i++) {
            view = getChildAt(i);
            if(view->getVisibility() == View::GONE) {
                continue;
            }
            measureChild(view, widthMeasureSpec, heightMeasureSpec);
            maxWidth =  maxWidth > view->getMeasureWidth() ? maxWidth : view->getMeasureWidth();
            maxHeight = maxHeight > view->getMeasureHeight() ? maxHeight : view->getMeasureHeight();
        }
        setMeasureDimension(maxWidth, maxHeight);
	}
}


