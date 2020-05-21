//
// Created by chao on 2017/4/20.
//

#ifndef PANOVIDEOPLAYER_ANDROID_5_0_0_OPENGL_UTIL_H
#define PANOVIDEOPLAYER_ANDROID_5_0_0_OPENGL_UTIL_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "../gles_const.h"

GLuint openglutil_loadShaders(const char *vsh_str, const char *fsh_str);

#ifdef __cplusplus
}
#endif
#endif //PANOVIDEOPLAYER_ANDROID_5_0_0_OPENGL_UTIL_H
