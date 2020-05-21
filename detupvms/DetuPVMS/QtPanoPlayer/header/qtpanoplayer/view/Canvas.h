//
//  Canvas.hpp
//  QtPanoPlayer
//
//  Created by chao on 2017/12/2.
//

#ifndef Canvas_hpp
#define Canvas_hpp

#include <stdio.h>
#include "RectF.h"
#include "Paint.h"

struct RcCommonRender;
namespace DetuPanoPlayer {
    
    class Canvas {
    public:
        Canvas();
        virtual ~Canvas();
        void drawLines(float* pts, Paint* paint);
        void drawRect(RectF* rect, Paint* paint);
        void drawColor(float red, float green, float blue, float alpha);
        void drawCircle(float cx, float cy, float radius, Paint* paint);
		void drawBitmap(unsigned char* data, float width, float height, float rx, float ry, float rz, bool isDistorted, Paint* paint);
		/**
		 *@param data ͼ����������
		 *@param width ͼ�����ؿ��
		 *@patam height ͼ�����ظ߶�
		 *@param vertextCoords �����openglwidget�ľ�������
		 *@rx x����ת��
		 *@ry y����ת��
		 *@rz z����ת��
		 */
		void drawBitmap(unsigned char* data, float width, float height, RectF* rectF, float rx, float ry, float rz, bool isDistorted, Paint* paint);
		void updateWindowSize(float width, float height);
		void updateRenderWindowSize(float renderWindowWidth, float renderWindowHeight);
		void translate(float dx, float dy);
		void setFrame(float x, float y, float w, float h);
        void setFrame(RectF* rect);
        void setCommonRender(struct RcCommonRender* commonRender);
    private:
        struct RcCommonRender* mCommonRender;
        float mWindowWidth;
		float mWindowHeight;
		float mRenderWindowWidth;
		float mRenderWindowHeight;
		float mX;
		float mY;
		float mW;
		float mH;
        float mCacheVertexCoord[8];
    private:
		void getVertexCoord(float* outCoord, float w, float h, bool isDistorted);
		void getVertexCoord(float* outCoord, RectF* rectF, bool isDistorted);
    };
}

#endif /* Canvas_hpp */
