//
// Created by chao on 2017/4/20.
//

#ifndef PANOVIDEOPLAYER_ANDROID_5_0_0_GL_MODEL_H
#define PANOVIDEOPLAYER_ANDROID_5_0_0_GL_MODEL_H
#ifdef __cplusplus
extern "C" {
#endif

#include "../gles_const.h"
#include "../enitity.h"

#define GL_MODEL_SIZEY 80
#define GL_MODEL_SIZEX 160
#define GL_MODEL_POINT_COUNT (GL_MODEL_SIZEX + 1) * GL_MODEL_SIZEY * 2
#define GL_MODEL_POINT_2D_COUNT GL_MODEL_POINT_COUNT * 2
#define GL_MODEL_POINT_3D_COUNT GL_MODEL_POINT_COUNT * 3

#define GL_MODEL_MAX_TEXTURE_ID_SIZE 16 // 最大纹理id个数
#define GL_MODEL_MATRIX_SIZE 16
#define STEP M_PI/GL_MODEL_SIZEY

static GLfloat GL_MODEL_IDENTITY_MATRIX[16] = { 
	1.0f, 0.f, 0.0f, 0.0f,
	0.0f, 1.f, 0.0f, 0.0f,
	0.0f, 0.f, 1.0f, 0.0f,
	0.0f, 0.f, 0.0f, 1.0f
};

//原图顶点坐标
 

static GLfloat GL_MODEL_ORIGIN_TEXTURE_COORDS[8] = {
	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
};
static GLfloat GL_MODEL_ORIGIN_TEXTURE_REPLAYF4_COORDS[8] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
};

typedef struct GlModel {
    ImageData imageData;
    ViewData viewData;
 
    int viewPortWidth; //viewPort宽
    int viewPortHeight; //viewPort高
 
    float znear;//透视投影近平面的值
    float zOffset;//模型z轴方向离0点的距离
    float zOffsetmin;
	float yfollow;//垂直方向视角跟随的值
    GLuint programHandle;
    GLuint mVPMatrixHandle;
    GLuint positionHandle;

    GLfloat projectionMatrix[GL_MODEL_MATRIX_SIZE];//透视投影矩阵
    GLfloat mvpMatrix[GL_MODEL_MATRIX_SIZE];//所有矩阵相乘得到的总矩阵
    GLfloat modelMatrix[GL_MODEL_MATRIX_SIZE];//模型矩阵
	GLfloat leftmodelMatrix[GL_MODEL_MATRIX_SIZE];//vr模式下左边画面矩阵
	GLfloat rightmodelMatrix[GL_MODEL_MATRIX_SIZE];//vr模式下右边画面矩阵

    GLfloat cameraMatrix[GL_MODEL_MATRIX_SIZE];
 
    GLfloat **cubevertexCoords;//立方体的顶点坐标
    GLfloat *vertexCoords; //顶点坐标
	GLfloat *vertexlineflatCoords; //展开平面顶点坐标
	GLfloat *vertexplaneCoords;//原始纹理平面顶点坐标
	
	int vertexplaneSize;//平面顶点个数
	int vertexlineflatSize; //2:1平面顶点个数
    int vertexCoordsSize;
	GLfloat* flatVertexCoords;
    GLfloat *textureCoords; //纹理坐标1
    GLfloat *textureCoordsB; //双鱼眼纹理坐标2
	GLfloat *textureCoords2; //4鱼眼纹理坐标2
	GLfloat *textureCoords3; //4鱼眼纹理坐标3
	GLfloat *textureCoords4; //4鱼眼纹理坐标4

    int textureCoordsSize;

    int textureIdSize;
	GLuint weighttexID[4];

    GLuint *vertexCoordBuffers; //顶点坐标缓冲区
    int vertexCoordBuffferSize;

    GLuint *textureCoordBuffers; //纹理坐标缓冲区
    int textureCoordBuffferSize;
	float x_rate;//
	float y_rate;
} GlModel;

void model_reset(GlModel* model);
void model_initVertexCoords(GlModel* model);//初始化球面3D模型顶点坐标共用函数（鱼眼，双鱼眼，2：1共用）
void model_initVertexlineflatCoords(GlModel* model, int w, int h, float rate);//初始化平面展开2：1顶点坐标共用函数（鱼眼，双鱼眼，2：1共用）
void model_initVertexlineplaneCoords(GlModel* model, int w, int h, float rate);//初始化平面顶点坐标共用函数（鱼眼，双鱼眼，2：1共用）

#ifdef __cplusplus
}
#endif
#endif //PANOVIDEOPLAYER_ANDROID_5_0_0_GL_MODEL_H
