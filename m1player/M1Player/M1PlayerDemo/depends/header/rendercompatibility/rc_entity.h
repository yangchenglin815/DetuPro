//
// Created by chao on 2017/7/14.
//

#ifndef RENDERCOMPATIBILITYANDROIDDEMO_RC_ENTITY_H
#define RENDERCOMPATIBILITYANDROIDDEMO_RC_ENTITY_H

#include <stdint.h>
#include "stdio.h"
#include "rc_opengl_const.h"

#define RC_MAX_PLANE 4 //Frame最大通道数
#define RC_MAX_FRAME_SIZE 8 //最大帧个数
#define RC_ANDROID_TEXTURE_TRANSFORM_MATRIX_SIZE 16 //android surfacetexture硬解数据转换矩阵
#define RC_TARGET_TEXTURE_COORD_SIZE 4 //每帧画面在整张画面位置分布坐标

typedef enum RcPlatform {
    RcPlatform_ANDROID,
    RcPlatform_IOS,
    RcPlatform_WINDOWS,
	RcPlatform_MAC,
    RcPlatform_LINUX,
} RcPlatform;

typedef enum RcColorFormat {
    RcColorFormat_RGBA,
    RcColorFormat_ARGB,
    RcColorFormat_ABGR,
    RcColorFormat_BGRA,
    RcColorFormat_RGB24,
    RcColorFormat_BGR24,
    RcColorFormat_YUV420P,
    RcColorFormat_YV12,
    RcColorFormat_NV12,
    RcColorFormat_NV21,
    RcColorFormat_UYVY422,
    RcColorFormat_MEDIACODEC,
    RcColorFormat_VIDEOTOOLBOX,
} RcColorFormat;

typedef enum RcTextureReflect {
    RcTextureReflect_ONE_TO_ONE, //一帧数据渲为一个rgb纹理
    RcTextureReflect_MANY_TO_ONE //多帧数据渲染为一个rgb纹理
} RcTextureReflect;

typedef struct RcFrameInfo {
    int width;
    int height;
	int linesize[RC_MAX_PLANE];
    RcColorFormat colorFormat;
} RcFrameInfo;

typedef struct RcFrame {
    uint8_t *data[RC_MAX_PLANE];
    RcFrameInfo rcFrameInfo;

    //额外原始纹理转换矩阵
    GLfloat extraTextureTransformMatrix[RC_ANDROID_TEXTURE_TRANSFORM_MATRIX_SIZE];
} RcFrame;

typedef struct RcTexturesConfig {
    GLuint defaultFboId; //主要兼容QOpenglWidget环境
    RcFrameInfo rcFrameInfos[RC_MAX_FRAME_SIZE];
    int frameSize; //总帧数
    RcTextureReflect rcTextureReflect;
    int textureWidths[RC_MAX_FRAME_SIZE]; //要渲染rgb纹理的宽度集合;N合为1场景，仅赋值index=0
    int textureHeights[RC_MAX_FRAME_SIZE]; //要渲染rgb纹理的高度集合;N合为1场景，仅赋值index=0

    //每帧图像在整张图像位置分布，整张图像纹理坐标按照（0-1计算）
    GLfloat targetTextureCoordWeights[RC_MAX_FRAME_SIZE][RC_TARGET_TEXTURE_COORD_SIZE];

    //可能来自mediacodec surfaceTexture或者bitmap创建的纹理
    GLuint textureIds[RC_MAX_FRAME_SIZE];
} RcTexturesConfig;

typedef struct RcTextureReply {
    GLuint textureIds[RC_MAX_FRAME_SIZE]; //生成的rgb纹理id集合
    int textureSize; //渲染出来的rgb纹理个数
} RcTextureReply;


#endif //RENDERCOMPATIBILITYANDROIDDEMO_RC_ENTITY_H
