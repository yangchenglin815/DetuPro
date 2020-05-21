//
//  LayoutParams.hpp
//  PanoPlayer
//
//  Created by chao on 2017/12/1.
//  Copyright © 2017年 detu. All rights reserved.
//

#ifndef LayoutParams_hpp
#define LayoutParams_hpp

#include <stdio.h>

namespace DetuPanoPlayer {
    
    typedef enum DisplayType {
        DisplayType_DISTORTED,
        DisplayType_UN_DISTORTED
    } DisplayType;
    
    class LayoutParams {
    public:
        static const int MATCH_PARENT = 0;
        static const int WRAP_CONTENT = 1;
        int width;
        int height;
        DisplayType displayType;
        float rx;
        float ry;
        float rz;
        float scale;
        float ath;
        float atv;
    public:
        LayoutParams(int width, int height);
        virtual ~LayoutParams();
    };
    
    class MarginLayoutParams : public LayoutParams {
    public:
        int topMargin;
        int bottomMargin;
        int leftMargin;
        int rightMargin;
    public:
        MarginLayoutParams(int width, int height);
        ~MarginLayoutParams();
        void setMargins(int left, int right, int top, int bottom);
    };
}

#endif /* LayoutParams_hpp */
