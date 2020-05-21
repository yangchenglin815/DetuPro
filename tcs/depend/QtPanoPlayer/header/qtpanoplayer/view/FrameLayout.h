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
        void onLayout(bool changed, int l, int t, int r, int b) override;
        void onMeasure(int widthMeasureSpec, int heightMeasureSpec) override;
    };
}

#endif /* FrameLayout_hpp */
