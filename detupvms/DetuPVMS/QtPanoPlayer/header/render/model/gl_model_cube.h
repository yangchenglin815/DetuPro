//
// Created by zhj on 17/4/21.
//

#ifndef PANOVIDEOPLAYER_ANDROID_GL_MODEL_CUBE_H
#define PANOVIDEOPLAYER_ANDROID_GL_MODEL_CUBE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "gl_model.h"

#define SIZE 80
#define CUBE_POINTCOUNT SIZE*(SIZE+1)*2
#define CUBE_2D_POINTCOUNT CUBE_POINTCOUNT * 2
#define CUBE_3D_POINTCOUNT CUBE_POINTCOUNT * 3

typedef struct GlModelCube {
    GlModel glModel;
    GLuint textureUniformHandle;
    GLuint textureCoordinateHandle;


} GlModelCube;
	
void modelCube_initShader(GlModelCube *glModelCube);

void modelCube_initVertexCoords(GlModelCube *glModelCube);

void modelCube_initTexCoords(GlModelCube *glModelCube);

void modelCube_draw(GlModelCube *glModelCube,float *tmatrix);
#ifdef __cplusplus
}
#endif

#endif //PANOVIDEOPLAYER_ANDROID_GL_MODEL_CUBE_H
