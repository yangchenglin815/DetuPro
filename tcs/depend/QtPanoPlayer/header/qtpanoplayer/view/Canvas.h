//
//  Canvas.hpp
//  QtPanoPlayer
//
//  Created by chao on 2017/12/2.
//

#ifndef Canvas_hpp
#define Canvas_hpp

#include <stdio.h>
#include "Rect.h"
#include "Paint.h"

struct RcCommonRender;
namespace DetuPanoPlayer {
    
    class Canvas {
    public:
        Canvas();
        virtual ~Canvas();
        void drawLines(float* pts, Paint* paint);
        void drawRect(Rect* rect, Paint* paint);
        void drawColor(float red, float green, float blue, float alpha);
        void drawCircle(float cx, float cy, float radius, Paint* paint);
        void drawBitmap(unsigned char* data, int width, int height, float rx, float ry, float rz, bool isDistorted, Paint* paint);
        void drawBitmap(unsigned char* data, int width, int height, float vertextCoord[8], float rx, float ry, float rz, Paint* paint);
        void updateWindowSize(int width, int height);
        void updateRenderWindowSize(int renderWindowWidth, int renderWindowHeight);
        void translate(int dx, int dy);
        void setFrame(int x, int y, int w, int h);
        void setFrame(Rect* rect);
        void setCommonRender(struct RcCommonRender* commonRender);
    private:
        struct RcCommonRender* mCommonRender;
        int mWindowWidth;
        int mWindowHeight;
        int mRenderWindowWidth;
        int mRenderWindowHeight;
        int mX;
        int mY;
        int mW;
        int mH;
        float mCacheVertexCoord[8];
    private:
        void getVertexCoord(float* outCoord, int w, int h, bool isDistorted);
    };
}

#endif /* Canvas_hpp */
