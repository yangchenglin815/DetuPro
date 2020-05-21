//
//  RectF.hpp
//  QtPanoPlayer
//
//  Created by chao on 2017/12/2.
//

#ifndef Rect_hpp
#define Rect_hpp

#include <stdio.h>

namespace DetuPanoPlayer {
    
    class RectF {
    public:
        RectF();
		RectF(float l, float t, float r, float b);
        ~RectF();
		void set(float l, float t, float r, float b);
        bool isValid();
		bool contains(float x, float y);
    public:
		float mL;
		float mT;
		float mR;
		float mB;
    };
}

#endif /* Rect_hpp */
