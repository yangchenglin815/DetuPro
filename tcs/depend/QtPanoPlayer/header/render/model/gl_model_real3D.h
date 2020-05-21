//
//  gl_model_real3D.h
//  PanoPlayer
//
//  Created by zhangjing on 2018/1/29.
//  Copyright © 2018年 detu. All rights reserved.
//

#ifndef gl_model_real3D_h
#define gl_model_real3D_h
#ifdef __cplusplus
extern "C" {
#endif

#include "gl_model.h"

typedef struct GlModelReal3D {
    GlModel glModel;
    GLint textureUniformHandle;
    GLint textureCoordinateHandle;
    GLuint modetypeHandle;
} GlModelReal3D;

void modelReal3D_initShader(GlModelReal3D *glModelReal3D);

void modelReal3D_initVertexCoords(GlModelReal3D *glModelReal3D);

void modelReal3D_initTexCoords(GlModelReal3D *glModelReal3D);

void modelReal3D_draw(GlModelReal3D *glModelReal3D, GLfloat *tmatrix, int modetype);

#ifdef __cplusplus
}
#endif
#endif /* gl_model_real3D_h */
