//
// Created by chao on 2017/4/20.
//

#ifndef PANOVIDEOPLAYER_ANDROID_5_0_0_GL_MODEL_SPHEREEYE_H
#define PANOVIDEOPLAYER_ANDROID_5_0_0_GL_MODEL_SPHEREEYE_H
#ifdef __cplusplus
extern "C" {
#endif

#include "gl_model.h"
#include "../utils/sphereutil.h"

typedef struct GlModelSphereEye
{
	GlModel glModel;
	GLuint textureUniformHandle;
	GLuint textureCoordinateHandle;
	GLuint ylimtHandle;
	GLuint modetypeHandle;
} GlModelSphereEye;


void modelSphereEye_initShader(GlModelSphereEye* glModelSphereEye);

void modelSphereEye_initVertexCoords(GlModelSphereEye* glModelSphereEye);

void modelSphereEye_initTexCoords(GlModelSphereEye* glModelSphereEye);

void modelSphereEye_parseCalibration(GlModelSphereEye* glModelSphereEye);

void modelSphereEye_draw(GlModelSphereEye* glModelSphereEyes, GLfloat *tmatrix);

#ifdef __cplusplus
}
#endif
#endif //PANOVIDEOPLAYER_ANDROID_5_0_0_GL_MODEL_SPHEREEYE_H
