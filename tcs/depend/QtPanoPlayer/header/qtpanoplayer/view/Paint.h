//
//  Paint.hpp
//  QtPanoPlayer
//
//  Created by chao on 2017/12/2.
//

#ifndef Paint_hpp
#define Paint_hpp

#include <stdio.h>

namespace DetuPanoPlayer {
    
    class Paint {
    public:
        Paint();
        virtual ~Paint();
        void setColor(int color);
        int getColor() const;
    private:
        int mColor;
    };
}

#endif /* Paint_hpp */
