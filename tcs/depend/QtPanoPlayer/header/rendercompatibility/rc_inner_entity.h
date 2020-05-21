//
// Created by chao on 2017/7/15.
//

#ifndef RENDERCOMPATIBILITYANDROIDDEMO_RC_INNER_ENTITY_H
#define RENDERCOMPATIBILITYANDROIDDEMO_RC_INNER_ENTITY_H

#include "rc_entity.h"
#include "rc_opengl_const.h"

#define RC_MAX_UPLOAD_TEXTURE_ID_SIZE 3 //yuv数据三个纹理

typedef enum RcFrameUploadTextureType {
    RcFrameUploadTextureType_COMMON, //rgb一个纹理id, yuv三个纹理id，nv12两个纹理id
    RcFrameUploadTextureType_SINGLE, //yuv类数据一个纹理id
} RcFrameUploadTextureType;

typedef struct RcTextureUploadWrapper {
    RcFrameUploadTextureType uploadTextureType;
    GLuint uploadTextureIds[RC_MAX_UPLOAD_TEXTURE_ID_SIZE];
    int widths[RC_MAX_UPLOAD_TEXTURE_ID_SIZE];
    int heights[RC_MAX_UPLOAD_TEXTURE_ID_SIZE];
    GLuint internalFormats[RC_MAX_UPLOAD_TEXTURE_ID_SIZE];
    GLuint formats[RC_MAX_UPLOAD_TEXTURE_ID_SIZE];
    GLuint types[RC_MAX_UPLOAD_TEXTURE_ID_SIZE];
    int planes;
} RcTextureUploadWrapper;

#endif //RENDERCOMPATIBILITYANDROIDDEMO_RC_INNER_ENTITY_H
