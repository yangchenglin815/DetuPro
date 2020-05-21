//
//  gl_model_spheref4.h
//  DetuPanoPlayer
//
//  Created by zhangjing on 2017/5/12.
//  Copyright © 2017年 detu. All rights reserved.
//

#ifndef gl_model_sphere4_h
#define gl_model_sphere4_h
#ifdef __cplusplus
extern "C" {
#endif
    
#include "gl_model.h"
#include <stdio.h>
#include "../utils/sphereutil.h"
#define IMG_NUM 4 
    typedef struct GlModelSphere4 {
        GlModel glModel;
		GLuint mweightCoordinateHandle;
		GLuint mTextureCoordinateHandle[4];
		GLuint weightHandle[4];
		GLuint viewmodeHandle;
		int size_ratio;
		GLuint mTextureUniformHandle;
		GLuint mweightUniformHandle[4];
		GLfloat *weighttextureCoords; //weight纹理坐标1
		int weighttextureCoordsSize;

		bool isinit;
    } GlModelSphere4;
    void modelSphere4_initdata(GlModelSphere4 *glModelSpheref4) ;
    void modelSphere4_initShader(GlModelSphere4 *glModelSpheref4);
	void modelSpheref4_parseCalibration(GlModelSphere4* glModelSpheref4);
    void modelSpherem1_parseCalibration(GlModelSphere4* glModelSpheref4);

	void modelSphere4_initVertexCoords(GlModelSphere4 *glModelSphere4);
    
	void modelSphere4_initTexCoords(GlModelSphere4 *glModelSphere4);
    
	void modelSphere4_draw(GlModelSphere4 *glModelSpheref4, float *tmatrix);
    void modelSphere4_delete(GlModelSphere4 *glModelSpheref4);
    
    
#ifdef __cplusplus
}
#endif
#endif /* gl_model_spheref4_h */





