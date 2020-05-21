//
//  Rect.hpp
//  QtPanoPlayer
//
//  Created by chao on 2017/12/2.
//

#ifndef Rect_hpp
#define Rect_hpp

#include <stdio.h>

namespace DetuPanoPlayer {
    
    class Rect {
    public:
        Rect();
        Rect(int l, int t, int r, int b);
        ~Rect();
        void set(int l, int t, int r, int b);
        bool isValid();
        bool contains(int x, int y);
    public:
        int mL;
        int mT;
        int mR;
        int mB;
    };
}

#endif /* Rect_hpp */
