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
#elif defined(__APPLE__)
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#elif defined(WIN32)
#include "glew.h"
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#endif
#ifdef __cplusplus
}
#endif
#endif //PANOVIDEOPLAYER_ANDROID_5_0_0_GLES_CONST_H
