//
//  Paint.cpp
//  QtPanoPlayer
//
//  Created by chao on 2017/12/2.
//

#include "Paint.h"

namespace DetuPanoPlayer {
    
    Paint::Paint() : mColor(0x000000){
        
    }
    Paint::~Paint() {
        
    }
    void Paint::setColor(int color) {
        mColor = color;
    }
    
    int Paint::getColor() const {
        return mColor;
    }
}
