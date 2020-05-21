//
//  LayoutParams.cpp
//  PanoPlayer
//
//  Created by chao on 2017/12/1.
//  Copyright © 2017年 detu. All rights reserved.
//

#include "LayoutParams.h"

namespace DetuPanoPlayer {
    LayoutParams::LayoutParams(int width, int height) {
        this->width = width;
        this->height = height;
        rx = 0.0f;
        ry = 0.0f;
        rz = 0.0f;
        scale = 1.0f;
        ath = 0.0f;
        atv = 0.0f;
        displayType = DisplayType_UN_DISTORTED;
    }
    
    LayoutParams::~LayoutParams() {
        
    }
    
    MarginLayoutParams::MarginLayoutParams(int width, int height) : DetuPanoPlayer::LayoutParams(width, height){
        
    }
    
    MarginLayoutParams::~MarginLayoutParams() {
        
    }
    
    void MarginLayoutParams::setMargins(int left, int right, int top, int bottom) {
        this->leftMargin = left;
        this->rightMargin = right;
        this->topMargin = top;
        this->bottomMargin = bottom;
    }
    
}
