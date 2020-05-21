//
//  ImageView.hpp
//  QtPanoPlayer
//
//  Created by chao on 2017/12/1.
//

#ifndef ImageView_hpp
#define ImageView_hpp

#include <stdio.h>
#include "View.h"

namespace DetuPanoPlayer {
    
    class ImageView : public View {
    public:
        ImageView(Context* context);
        ~ImageView();
        void onMeasure(int widthMeasureSpec, int heightMeasureSpec);
        void onDraw(Canvas* canvas, DisplayType displayType);
    };
}

#endif /* ImageView_hpp */
