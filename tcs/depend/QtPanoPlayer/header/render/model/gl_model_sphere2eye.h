//
// Created by chao on 2017/4/20.
//

#ifndef PANOVIDEOPLAYER_ANDROID_5_0_0_GL_MODEL_SPHERE2EYE_H
#define PANOVIDEOPLAYER_ANDROID_5_0_0_GL_MODEL_SPHERE2EYE_H
#ifdef __cplusplus
extern "C" {
#endif

#include "gl_model.h"
#include "../utils/sphereutil.h"
#include "../enitity.h"
typedef struct GlModelSphere2Eye {
    GlModel glModel;
    GLuint textureUniformHandle;
    GLuint sizeHandle; // 为双鱼眼合成服务。
    GLuint textureCoordHandleA;
    GLuint textureCoordHandleB;

    GLuint modetypeHandle;
    GLuint gammaHandler;

    GLuint yaw0Handle;
    GLuint yaw1Handle;
	GLuint x_rateHandle;
	GLuint y_rateHanle;
} GlModelSphere2Eye;


void modelSphere2Eye_initShader(GlModelSphere2Eye *glModelSphere2Eye);

void modelSphere2Eye_parseCalibration(GlModelSphere2Eye *glModelSphere2Eye);

void modelSphere2Eye_initVertexCoords(GlModelSphere2Eye *glModelSphere2Eye);

void modelSphere2Eye_initTexCoords(GlModelSphere2Eye *glModelSphere2Eye);

void modelSphere2Eye_draw(GlModelSphere2Eye *glModelSphere2Eye, float *tmatrix);


#ifdef __cplusplus
}
#endif
#endif //PANOVIDEOPLAYER_ANDROID_5_0_0_GL_MODEL_SPHERE2EYE_H
