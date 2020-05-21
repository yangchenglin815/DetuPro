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
		GLuint mweightCoordinateHandle[4];
		GLuint mTextureCoordinateHandle[4];
		GLuint weightHandle;
		GLuint viewmodeHandle;
		int size_ratio;
		GLuint mTextureUniformHandle;
		GLuint mweightUniformHandle;
		GLfloat *weighttextureCoords1; //weight纹理坐标1
		GLfloat *weighttextureCoords2; //weight纹理坐标2
		GLfloat *weighttextureCoords3; //weight鱼眼纹理坐标3
		GLfloat *weighttextureCoords4; //weight鱼眼纹理坐标4
		int weighttextureCoordsSize;

		bool isinit;
    } GlModelSphere4;
    void modelSphere4_initdata(GlModelSphere4 *glModelSpheref4) ;
    void modelSphere4_initShader(GlModelSphere4 *glModelSpheref4);
	void modelSphere4_parseCalibration(GlModelSphere4* glModelSpheref4);

	void modelSphere4_initVertexCoords(GlModelSphere4 *glModelSphere4);
    
	void modelSphere4_initTexCoords(GlModelSphere4 *glModelSphere4);
    
	void modelSphere4_draw(GlModelSphere4 *glModelSpheref4, float *tmatrix);
    
    
    
#ifdef __cplusplus
}
#endif
#endif /* gl_model_spheref4_h */





