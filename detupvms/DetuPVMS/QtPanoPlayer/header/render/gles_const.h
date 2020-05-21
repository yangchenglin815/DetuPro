//
// Created by chao on 2017/4/20.
//

#ifndef PANOVIDEOPLAYER_ANDROID_5_0_0_GLES_CONST_H
#define PANOVIDEOPLAYER_ANDROID_5_0_0_GLES_CONST_H
#ifdef __cplusplus
extern "C" {
#endif

#if defined(MAC_QT)
#include "glew.h"
#define IS_OPENGL_ES false
#elif defined(__APPLE__)
#import <OpenGLES/ES3/gl.h>
#import <OpenGLES/ES3/glext.h>
#define IS_OPENGL_ES true
#elif defined(WIN32)
#include "glew.h"
#define IS_OPENGL_ES false
#elif defined(_WIN64)
#include "glew.h"
#define IS_OPENGL_ES false
#else
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <GLES3/gl3platform.h>
#define IS_OPENGL_ES true
#endif
#ifdef __cplusplus
}
#endif
#endif //PANOVIDEOPLAYER_ANDROID_5_0_0_GLES_CONST_H
