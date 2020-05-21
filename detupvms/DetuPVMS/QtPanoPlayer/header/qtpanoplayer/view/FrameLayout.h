//
//  FrameLayout.hpp
//  QtPanoPlayer
//
//  Created by chao on 2017/12/1.
//

#ifndef FrameLayout_hpp
#define FrameLayout_hpp

#include <stdio.h>
#include "ViewGroup.h"

namespace DetuPanoPlayer {
    
    class FrameLayout : public ViewGroup {
    public:
        FrameLayout(Context* context);
        ~FrameLayout();
    protected:
		void onLayout(bool changed, float l, float t, float r, float b) override;
		void onMeasure(float widthMeasureSpec, float heightMeasureSpec) override;
    };
}

#endif /* FrameLayout_hpp */
