//
//  SequenceImageView.hpp
//  QtPanoPlayer
//
//  Created by chao on 2017/12/5.
//

#ifndef SequenceImageView_hpp
#define SequenceImageView_hpp

#include <stdio.h>
#include "ImageView.h"

namespace DetuPanoPlayer {
    
    class SequenceImageViewPrivate;
    
    class SequenceImageView : public ImageView {
    public:
        SequenceImageView(Context* context);
        ~SequenceImageView();
        void setSequenceDrawableUrls(vector<string> urls);
        void onDraw(Canvas* canvas, DisplayType displayType);
    private:
        SequenceImageViewPrivate* sivPrivate;
    };
}

#endif /* SequenceImageView_hpp */

