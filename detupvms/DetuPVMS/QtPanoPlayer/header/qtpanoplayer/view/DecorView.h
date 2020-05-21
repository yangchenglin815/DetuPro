//
//  DecorView.hpp
//  QtPanoPlayer
//
//  Created by chao on 2017/12/1.
//

#ifndef DecorView_hpp
#define DecorView_hpp

#include "FrameLayout.h"

#include <stdio.h>

namespace DetuPanoPlayer {
    
    class DecorView : public FrameLayout {
    public:
        DecorView(Context* context);
        ~DecorView();
    };
}

#endif /* DecorView_hpp */
