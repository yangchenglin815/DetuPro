//
//  Rect.cpp
//  QtPanoPlayer
//
//  Created by chao on 2017/12/2.
//

#include "Rect.h"

namespace DetuPanoPlayer {
    
    Rect::Rect() : Rect(0, 0, 0, 0){
        
    }

    Rect::Rect(int l, int t, int r, int b) {
        set(l, t, r, b);
    }
    
    Rect::~Rect() {
        
    }
    
    void Rect::set(int l, int t, int r, int b) {
        mL = l;
        mT = t;
        mR = r;
        mB = b;
    }
    
    bool Rect::isValid() {
        return mR > 0 && mB > 0;
    }
    
    bool Rect::contains(int x, int y) {
        return x >= mL && y >= mT && x < mR && y < mB;
    }
}
