//
// Created by chao on 2017/4/19.
//

#ifndef PANOVIDEOPLAYER_ANDROID_5_0_0_GLES_RENDER_H
#define PANOVIDEOPLAYER_ANDROID_5_0_0_GLES_RENDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "enitity.h"
#include "gles_const.h"
#include "Tween/Easing.h"

typedef struct PanoRenderConfig
{
	bool isRewindVertexCoord; //�Ƿ��ö�������
	bool isRewindTextureCoord; //�Ƿ�����������
	bool isRewindGesture; //�Ƿ������Ʋ���
} PanoRenderConfig;

typedef enum PanoRenderPlatForm {
	PanoRenderPlatForm_ANDROID,
	PanoRenderPlatForm_IOS,
	PanoRenderPlatForm_WINDOWS,
	PanoRenderPlatForm_MAC,
	PanoRenderPlatForm_LINUX
}PanoRenderPlatForm;

struct PanoRender;

typedef struct PanoRender PanoRender;
 
PanoRender* panoRender_create(PanoRenderPlatForm platform);

bool panoRender_setup(PanoRender* render, ImageData* imageData, ViewData* viewData);

void panoRender_setRenderCallBack(PanoRender* render, void* opaque, PanoRenderCallBack* callBack);

void panoRender_setTextures(PanoRender* render, GLuint* textureIds, int size);
void panoRender_setweightTexture(PanoRender* render,uint8_t *data);

void panoRender_setViewport(PanoRender* render, int w, int h);

void panoRender_draw(PanoRender* render);

void panoRender_switchViewMode(PanoRender* render, ModelViewMode viewMode);
void panoRender_animationswitchViewMode(PanoRender* render, ModelViewMode viewMode, int duration, EaseType easeType);

void panoRender_delete(PanoRender* render);
PanoViewEuler* getcurrentPanoramaData(PanoRender *render);
void panoRender_setpausetime(PanoRender *render,float time);
void panoRender_autoplay(PanoRender *render,bool autoplay);
void panoRender_autoplayhlookat(PanoRender *render, float hlookat);

#ifdef __cplusplus
}
#endif
#endif //PANOVIDEOPLAYER_ANDROID_5_0_0_GLES_RENDER_H
