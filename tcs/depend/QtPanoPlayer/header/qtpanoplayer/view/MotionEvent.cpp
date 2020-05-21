//
//  MotionEvent.cpp
//  QtPanoPlayer
//
//  Created by chao on 2017/12/1.
//

#include "MotionEvent.h"

namespace DetuPanoPlayer {
    MotionEvent::MotionEvent() : mAction(0), mX(0), mY(0) {
        
    }
    
    MotionEvent::~MotionEvent() {
        
    }
    
    float MotionEvent::getRawX() const{
        return 0.0f;
    }
    
    float MotionEvent::getRawY() const{
        return 0.0f;
    }
    
    void MotionEvent::setX(int x) {
        mX = x;
    }
    
    float MotionEvent::getX() const {
        return mX;
    }
    
    void MotionEvent::setY(int y) {
        mY = y;
    }
    
    float MotionEvent::getY() const {
        return mY;
    }
    
    void MotionEvent::setAction(int action) {
        mAction = action;
    }
    
    int MotionEvent::getAction() const {
        return mAction;
    }
}

