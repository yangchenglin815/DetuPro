//
// Created by chao on 2017/11/15.
//

#ifndef DPV_ANDROID_SURFACE_TEXTURE_JNI_H
#define DPV_ANDROID_SURFACE_TEXTURE_JNI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <jni.h>

struct SurfaceTextureJni;

typedef struct SurfaceTextureJni SurfaceTextureJni;

SurfaceTextureJni* surfaceTextureJni_new(JNIEnv * env, jobject jObjSurfaceTexture);

void surfaceTextureJni_getTransformMatrix(JNIEnv * env, SurfaceTextureJni *surfaceTexture, float *mtx);

void surfaceTextureJni_updateTexImage(JNIEnv * env, SurfaceTextureJni *surfaceTexture);

void surfaceTextureJni_delete(JNIEnv * env, SurfaceTextureJni *surfaceTexture);

#ifdef __cplusplus
}
#endif
#endif //DPV_ANDROID_SURFACE_TEXTURE_JNI_H
