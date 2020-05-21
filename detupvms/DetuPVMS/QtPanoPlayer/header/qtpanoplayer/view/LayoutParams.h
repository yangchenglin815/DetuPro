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
        DisplayType_GL_DISTORTED,
        DisplayType_GL_UN_DISTORTED,
		DisplayType_PLATFORM,
		DisplayType_UNKNOW
    } DisplayType;
    
    class LayoutParams {
    public:
        static const int MATCH_PARENT = 0;
        static const int WRAP_CONTENT = 1;
		static const float LAYOUT_INVALIDATE_VALUE;
        float width;
        float height;
        DisplayType displayType;
		bool isFollow;
        float rx;
        float ry;
        float rz;
        float scale;
        float ath;
        float atv;
    public:
		LayoutParams(float width, float height);
        virtual ~LayoutParams();
    };
    
    class MarginLayoutParams : public LayoutParams {
    public:
		float topMargin;
		float bottomMargin;
		float leftMargin;
		float rightMargin;
    public:
		MarginLayoutParams(float width, float height);
        ~MarginLayoutParams();
		void setMargins(float left, float right, float top, float bottom);
    };
}

#endif /* LayoutParams_hpp */
