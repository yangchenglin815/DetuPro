//
//  rc_common_render.h
//  RenderCompatibility
//
//  Created by chao on 2017/12/2.
//  Copyright © 2017年 detu. All rights reserved.
//

#ifndef rc_common_render_h
#define rc_common_render_h

#include <stdio.h>
#include <stdbool.h>

struct RcCommonRender;

typedef struct RcCommonRender RcCommonRender;

RcCommonRender *rcCommonRender_new(bool isOpengles);

bool rcCommonRender_initProgram(RcCommonRender *commonRender);

void rcCommonRender_drawCircle(RcCommonRender *commonRender, float cx, float cy, float radius, float color[4]);

void rcCommonRender_drawRect(RcCommonRender *commonRender, float vertexCoords[8], float color[4]);

void rcCommonRender_drawBitmap(RcCommonRender *commonRender, float vertexCoords[8], float mx, float my, float rx, float ry, float rz, unsigned char* data, int width, int height);

void rcCommonRender_drawTexture(RcCommonRender *commonRender, int textureId, float alpha);

void rcCommonRender_delete(RcCommonRender *commonRender);

#endif /* rc_common_render_h */
