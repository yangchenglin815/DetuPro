//
// Created by chao on 2017/4/20.
//

#ifndef PANOVIDEOPLAYER_ANDROID_5_0_0_GL_MODEL_STANDARD_H
#define PANOVIDEOPLAYER_ANDROID_5_0_0_GL_MODEL_STANDARD_H
#ifdef __cplusplus
extern "C" {
#endif

#include "gl_model.h"
 
typedef struct GlModelStandard {
    GlModel glModel;
    GLint textureUniformHandle;
    GLint textureCoordinateHandle;
    GLint alphaHandle;
    GLint isbgraHandle;
} GlModelStandard;

void modelStandard_initShader(GlModelStandard *glModelStandard);

void modelStandard_initVertexCoords(GlModelStandard *glModelStandard);

void modelStandard_initTexCoords(GlModelStandard *glModelStandard);

void modelStandard_draw(GlModelStandard *glModelStandard,GLfloat *tmatrix,float alpha,int isrgba);

#ifdef __cplusplus
}
#endif
#endif //PANOVIDEOPLAYER_ANDROID_5_0_0_GL_MODEL_STANDARD_H
