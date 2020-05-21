//
//  MotionEvent.hpp
//  QtPanoPlayer
//
//  Created by chao on 2017/12/1.
//

#ifndef MotionEvent_hpp
#define MotionEvent_hpp

#include <stdio.h>

namespace DetuPanoPlayer {
    
    class MotionEvent {
    public:
        static const int ACTION_MASK = 0xff;
        static const int ACTION_DOWN = 0;
        static const int ACTION_UP = 1;
        static const int ACTION_MOVE = 2;
        static const int ACTION_CANCEL = 3;
    public:
        MotionEvent();
        ~MotionEvent();
        
        float getRawX() const;
        float getRawY() const;
        void setX(float x);
        float getX() const;
		void setY(float y);
        float getY() const;
        void setAction(int action);
        int getAction() const;
    private:
        int mAction;
		float mX;
		float mY;
    };
}

#endif /* MotionEvent_hpp */
