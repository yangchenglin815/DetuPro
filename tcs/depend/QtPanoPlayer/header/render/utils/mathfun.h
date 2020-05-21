//
// Created by zhj on 17/4/26.
//

#ifndef PANOVIDEOPLAYER_ANDROID_MATHFUN_H
#define PANOVIDEOPLAYER_ANDROID_MATHFUN_H
#ifdef __cplusplus
extern "C" {
#endif
#include "../enitity.h"
#include "opengl_util.h"
#define  MAX_VALUE 2147483647 // 最大�?

float toRadiansse(float angle);
float toDegree(float radiansse);
bool gluProjectJing(const GLfloat * obj,const GLfloat * model,const GLint* viewport ,GLfloat *win);
bool gluUnProjectJing (const GLfloat * win ,const GLfloat *model ,const GLint* viewport ,GLfloat *obj);
void degToPoint3D(const float *inP ,float *outP);
void point3DToDeg(float *inP,float *outP);
void Rotation_matrix(float *m,float *ret, float degree, float x, float y, float z);
void vertetodeg(float *inP,float *outP);
void euler2Matrix(float* euler, float* matrix);
#ifdef __cplusplus
}
#endif
#endif //PANOVIDEOPLAYER_ANDROID_MATHFUN_H
