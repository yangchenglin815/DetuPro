//
//  gl_model_spheref4.h
//  DetuPanoPlayer
//
//  Created by zhangjing on 2017/5/12.
//  Copyright © 2017年 detu. All rights reserved.
//

#ifndef gl_model_spheref4_h
#define gl_model_spheref4_h
#ifdef __cplusplus
extern "C" {
#endif
    
#include "gl_model.h"
#include <stdio.h>
#include "../utils/sphereutil.h"
#define IMG_NUM 4 
    typedef struct GlModelSpheref4 {
        GlModel glModel;
        GLuint colorConversionMatrix_Handle;
        GLuint isYuvHandle;
        GLuint gammaHandle;
        GLuint sizeHandle;
        GLuint size_ratioHandle;
        GLuint sampler_weightHandle[4];
        GLuint sampler_fisheyeHandle[4];
//        GLuint SamplerYHandle[4];
        GLuint SamplerUHandle[4];
        GLuint SamplerVHandle[4];
        GLuint a_Handle[4];
        GLuint b_Handle[4];
        GLuint c_Handle[4];
        GLuint radius_Handle[4];
        GLuint center_Handle[4];
        GLuint yaw_Handle[4];
        GLuint pitch_Handle[4];
        GLuint roll_Handle[4];
        GLuint hd_Handle[4];
        GLuint ve_Handle[4];
        GLuint fov_Handle[4];
        float size_ratio;
        int is_yuv;
        
        GLuint fish_textureIds[12];
        GLuint weight_textureIds[4];
        
    } GlModelSpheref4;
    
    static const GLfloat kColorConversion709[3][3] = {
        1.164, 1.164, 1.164,
        0.0, -0.213, 2.112,
        1.793, -0.533, 0.0};
    void modelSpheref4_initdata(GlModelSpheref4 *glModelSpheref4) ;
    void modelSpheref4_inittexture(GlModelSpheref4 *glModelSpheref4,GLuint *ids);
    void modelSpheref4_initShader(GlModelSpheref4 *glModelSpheref4);
    
    void modelSpheref4_initVertexCoords(GlModelSpheref4 *glModelSpheref4);
    
    void modelSpheref4_initTexCoords(GlModelSpheref4 *glModelSpheref4);
    
    void modelSpheref4_draw(GlModelSpheref4 *glModelSpheref4,float *tmatrix);
    
    
    
#ifdef __cplusplus
}
#endif
#endif /* gl_model_spheref4_h */





