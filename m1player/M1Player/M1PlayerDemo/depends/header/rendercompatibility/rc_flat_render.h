//
// Created by chao on 2017/6/27.
//
#ifndef PANOVIDEOPLAYER_ANDROID_CAPTURE_FLAT_RENDER_H
#define PANOVIDEOPLAYER_ANDROID_CAPTURE_FLAT_RENDER_H

#include <stdbool.h>
#include "rc_opengl_const.h"
#include "rc_inner_entity.h"

typedef struct RcFlatRenderConfig {
    RcFrameInfo rcFrameInfo[RC_MAX_FRAME_SIZE];
    RcTextureReflect rcTextureReflect;
    GLfloat targetTextureCoordWeights[RC_MAX_FRAME_SIZE][RC_TARGET_TEXTURE_COORD_SIZE];
    int textureWidths[RC_MAX_FRAME_SIZE]; //要渲染rgb纹理的宽度集合;N合为1场景，仅赋值index=0
    int textureHeights[RC_MAX_FRAME_SIZE]; //要渲染rgb纹理的高度集合;N合为1场景，仅赋值index=0
    GLuint uploadTextureIds[RC_MAX_FRAME_SIZE][RC_MAX_UPLOAD_TEXTURE_ID_SIZE];
    int frameSize;
} RcFlatRenderConfig;

typedef struct RcFlatRenderExtra {
    GLfloat extraTextureTransformMatrix[RC_MAX_FRAME_SIZE][RC_ANDROID_TEXTURE_TRANSFORM_MATRIX_SIZE];
}RcFlatRenderExtra;

struct RcFlatRender;

typedef struct RcFlatRender RcFlatRender;

RcFlatRender *rcFlatRender_new(RcPlatform rcPlatform);

bool rcFlatRender_initProgram(RcFlatRender *flatRender, RcFlatRenderConfig* config);

void rcFlatRender_drawFrame(RcFlatRender *flatRender, RcFlatRenderExtra* extra);

void rcFlatRender_delete(RcFlatRender *flatRender);

#endif //PANOVIDEOPLAYER_ANDROID_CAPTURE_FLAT_RENDER_H
