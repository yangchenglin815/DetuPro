//
//  Canvas.cpp
//  QtPanoPlayer
//
//  Created by chao on 2017/12/2.
//

#include "Canvas.h"
#include <string.h>
extern "C" {
#include "rc_common_render.h"
}
//#include <qlogging.h>

namespace DetuPanoPlayer {
    
    Canvas::Canvas() : mWindowWidth(0), mWindowHeight(0) {
        mCommonRender = NULL;
        mX = 0;
        mY = 0;
        mW = 0;
        mH = 0;
        memset(mCacheVertexCoord, 0, sizeof(mCacheVertexCoord));
    }
    
    Canvas::~Canvas() {
        
    }
    
    void Canvas::drawLines(float* pts, Paint* paint) {
        if(mCommonRender != NULL) {
            
        }
    }
    
    void Canvas::drawRect(Rect* rect, Paint* paint) {
        if(mCommonRender != NULL) {
            
        }
    }
    
    void Canvas::drawColor(float red, float green, float blue, float alpha) {
        if(mCommonRender != NULL) {
            getVertexCoord(mCacheVertexCoord, mW, mH, true);
//            qDebug("getVertexCoord:%f, %f, %f, %f\n", mCacheVertexCoord[0], mCacheVertexCoord[1], mCacheVertexCoord[2], mCacheVertexCoord[3]) ;
            float color[4] = {red, green, blue, alpha};
            rcCommonRender_drawRect(mCommonRender, mCacheVertexCoord, color);
        }
    }
    
    void Canvas::getVertexCoord(float* outCoord, int w, int h, bool isDistorted) {
        //        static const GLfloat VERTEX_COORDS[8] = {
        //            -0.2f, 0.2f,
        //            -0.2f, -0.2f,
        //            0.2f, 0.2f,
        //            0.2f, -0.2f,
        //        };
        const int halfWindowWindth = (isDistorted ? mRenderWindowWidth : mWindowWidth) / 2;
        const int halfWindowHeight = (isDistorted ? mRenderWindowHeight : mWindowHeight) / 2;
        
        //layout都是按照屏幕openglwidget;
        const int x = isDistorted ? mX * (mRenderWindowWidth * 1.0 / mWindowWidth) : mX;
        const int y = isDistorted ? mY * (mRenderWindowHeight * 1.0 / mWindowHeight) : mY;
        float left = (x - halfWindowWindth) * 1.0 / halfWindowWindth;
        float top = -((y - halfWindowHeight) * 1.0 / halfWindowHeight);
        float right = (x - halfWindowWindth + w) * 1.0 / halfWindowWindth;
        float bottom = -((y - halfWindowHeight + h) * 1.0 / halfWindowHeight);
        outCoord[0] = left;
        outCoord[1] = top;
        outCoord[2] = left;
        outCoord[3] = bottom;
        outCoord[4] = right;
        outCoord[5] = top;
        outCoord[6] = right;
        outCoord[7] = bottom;
    }
    
    void Canvas::drawCircle(float cx, float cy, float radius, Paint* paint) {
        
    }
    
    void Canvas::setCommonRender(struct RcCommonRender* commonRender) {
        mCommonRender = commonRender;
    }
    
    void Canvas::setFrame(int x, int y, int w, int h) {
        mX = x;
        mY = y;
        mW = w;
        mH = h;
    }
    
    void Canvas::setFrame(Rect* rect) {
        setFrame(rect->mL, rect->mT, rect->mR - rect->mL, rect->mB - rect->mT);
    }
    
    void Canvas::drawBitmap(unsigned char* data, int width, int height, float rx, float ry, float rz, bool isDistorted, Paint* paint) {
        if(mCommonRender != NULL) {
            getVertexCoord(mCacheVertexCoord, mW, mH, isDistorted);
            rcCommonRender_drawBitmap(mCommonRender, mCacheVertexCoord,
                                      (mCacheVertexCoord[4] + mCacheVertexCoord[0]) / 2,
                                      ((mCacheVertexCoord[1] + mCacheVertexCoord[3]) / 2),
                                      rx, ry, rz, data, width, height);
        }
    }
    
    void Canvas::drawBitmap(unsigned char* data, int width, int height, float vertextCoord[8], float rx, float ry, float rz, Paint* paint) {
        if(mCommonRender != NULL) {
            rcCommonRender_drawBitmap(mCommonRender, vertextCoord,
                                      (vertextCoord[4] + vertextCoord[0]) / 2,
                                      ((vertextCoord[1] + vertextCoord[3]) / 2),
                                      rx, ry, rz, data, width, height);
        }
    }
    
    void Canvas::translate(int dx, int dy) {
        mX += dx;
        mY += dy;
    }
    
    void Canvas::updateRenderWindowSize(int renderWindowWidth, int renderWindowHeight) {
        mRenderWindowWidth = renderWindowWidth;
        mRenderWindowHeight = renderWindowHeight;
    }
    
    void Canvas::updateWindowSize(int width, int height) {
        mWindowWidth = width;
        mWindowHeight = height;
    }
}
