//
//  ImageView.cpp
//  QtPanoPlayer
//
//  Created by chao on 2017/12/1.
//

#include "ImageView.h"
#include "FfmpegUtils.h"

namespace DetuPanoPlayer {
    
    ImageView::ImageView(Context* context) : View(context){
    }
    
    ImageView::~ImageView() {
        
    }
    
    void ImageView::onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        setMeasureDimension(mLayoutParams->width, mLayoutParams->height);
    }
    
    void ImageView::onDraw(Canvas* canvas, DisplayType displayType) {
        View::onDraw(canvas, displayType);
    }

}
