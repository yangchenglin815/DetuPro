//
//  gl_model_space3D.h
//  PanoRender
//
//  Created by zhangjing on 2018/3/15.
//

#ifndef gl_model_space3D_h
#define gl_model_space3D_h

#ifdef __cplusplus
extern "C" {
#endif
    
#include "gl_model.h"
#include "../utils/cvector.h"

    typedef struct MeshVertex
    {
        Point3f position;
        Pointf texCoords;
        Point3f normal;
    }MeshVertex;
    // 表示obj文件中一个顶点的位置、纹理坐标和法向量 索引
    typedef struct MeshFace
    {
        GLuint posIndex[3];
        GLuint textCoordIndex[3];
        GLuint normIndex[3];
    }MeshFace;
    typedef struct GlModelSpace3D {
        GlModel glModel;
        GLuint VAOId, VBOId;
        cvector meshFace;//索引坐标
        MeshVertex *meshVertex;//坐标集合
        unsigned long Vertexsize;
        GLint textureUniformHandle;
        GLint textureCoordinateHandle;
        GLuint mNormalHandle;
        GLint alphaHandle;
        GLint isBgraHandle;
        bool isInit;
        bool isSetupMesh;
        bool isHaveNormal;
    } GlModelSpace3D;
    
    void modelSpace3D_initShader(GlModelSpace3D *glModelSpace3D);
    void modelSpace3D_initdata(GlModelSpace3D *glModelSpace3D);
//    void modelSpace3D_setupMesh(GlModelSpace3D *glModelSpace3D); // 建立VAO,VBO等缓冲区
    void modelSpace3D_delete(GlModelSpace3D *glModelSpace3D);
    void modelSpace3D_draw(GlModelSpace3D *glModelSpace3D,GLfloat *tmatrix);
    
#ifdef __cplusplus
}
#endif
#endif /* gl_model_space3D_h */
