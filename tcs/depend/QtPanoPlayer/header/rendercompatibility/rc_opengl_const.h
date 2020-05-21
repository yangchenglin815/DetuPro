//
// Created by chao on 2017/7/14.
//

#ifndef RENDERCOMPATIBILITYANDROIDDEMO_RC_OPENGL_CONST_H
#define RENDERCOMPATIBILITYANDROIDDEMO_RC_OPENGL_CONST_H

#if defined(MAC_QT)
#include "glew.h"
#elif defined(__APPLE__)
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#elif defined(_WIN32)
#include "glew.h"
#elif defined(_WIN64)
#include "glew.h"
#else
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <GLES3/gl3platform.h>
#endif

#endif //RENDERCOMPATIBILITYANDROIDDEMO_RC_OPENGL_CONST_H
