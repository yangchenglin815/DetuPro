//
// Created by chao on 2017/7/14.
//

#ifndef RENDERCOMPATIBILITYANDROIDDEMO_RENDER_COMPATIBILITY_H
#define RENDERCOMPATIBILITYANDROIDDEMO_RENDER_COMPATIBILITY_H

#include "rc_entity.h"
#include <stdbool.h>
#if defined(__ANDROID__)
#include <jni.h>
#endif

struct RenderCompatibility;

typedef struct RenderCompatibility RenderCompatibility;

typedef struct RenderCompatibilityCallBack {
	void(*onUpdateTexImage)(void* opaque, int index);
} RenderCompatibilityCallBack;

#if defined(__ANDROID__)
void renderCompatibility_jniLoad(JavaVM* vm);
#endif

RenderCompatibility *renderCompatibility_new(RcPlatform platform);

void renderCompatibility_setCallBack(RenderCompatibility *renderCompatibility, void* opaque, RenderCompatibilityCallBack* callBack);

bool renderCompatibility_config(RenderCompatibility *renderCompatibility, RcTexturesConfig* config, RcTextureReply *outReply);

void renderCompatibility_renderTexture(RenderCompatibility *renderCompatibility, RcFrame* frames);

void renderCompatibility_updateDefaultFrameBufferObject(RenderCompatibility *renderCompatibility, GLuint defaultFrameBufferObject);

void renderCompatibility_delete(RenderCompatibility *renderCompatibility);

#endif //RENDERCOMPATIBILITYANDROIDDEMO_RENDER_COMPATIBILITY_H
