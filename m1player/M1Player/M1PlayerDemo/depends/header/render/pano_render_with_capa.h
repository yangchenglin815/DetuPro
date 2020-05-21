#ifndef PANO_RENDER_WITH_CAPA_H
#define PANO_RENDER_WITH_CAPA_H
#ifdef __cplusplus
extern "C" {
#endif
	//tween
#include <stdio.h>
#include <stdbool.h>
#include "enitity.h"
#include "rc_entity.h"
#include "Tween/Easing.h"

typedef struct ImageDataWrapper
{
    RcPlatform platform;
	ModelDeviceId modelDeviceId;
	ModelResourceType modelResourceType;
	char calibration[MODEL_MAX_CALIBRATION_SIZE];
	RcFrameInfo rcFrameInfos[RC_MAX_FRAME_SIZE];
    GLfloat targetTextureCoordWeights[RC_MAX_FRAME_SIZE][RC_TARGET_TEXTURE_COORD_SIZE];
	int frameSize; //×ÜÖ¡Êý
	int textureWidths[RC_MAX_FRAME_SIZE]; 
	int textureHeights[RC_MAX_FRAME_SIZE];
	float gamma;

	//for android mediacodec only
	GLuint textureIds[RC_MAX_FRAME_SIZE];
} ImageDataWrapper;

struct PanoRenderWithCompatibility;

typedef struct PanoRenderWithCompatibility PanoRenderWithCompatibility;

PanoRenderWithCompatibility* panoRenderWithCompatibility_new();

bool panoRenderWithCompatibility_setup(PanoRenderWithCompatibility* panoRenderWithCompatibility, ImageDataWrapper* imageData, ViewData* viewData);

void panoRenderWithCompatibility_setRenderCallBack(PanoRenderWithCompatibility* panoRenderWithCompatibility, void* opaque, PanoRenderCallBack* callBack);

void panoRenderWithCompatibility_setViewport(PanoRenderWithCompatibility* panoRenderWithCompatibility, int w, int h);
    
    void panoRenderWithCompatibility_updateDefaultFrameBufferObject(PanoRenderWithCompatibility* panoRenderWithCompatibility, GLuint defaultFrameBufferObject);

void panoRenderWithCompatibility_draw(PanoRenderWithCompatibility* panoRenderWithCompatibility, RcFrame* frames);

void panoRenderWithCompatibility_switchViewMode(PanoRenderWithCompatibility* panoRenderWithCompatibility, ModelViewMode viewMode);
void panoRenderWithCompatibility_animationswitchViewMode(PanoRenderWithCompatibility* panoRenderWithCompatibility, ModelViewMode viewMode, int duration, EaseType easeType);
void panoRenderWithCompatibility_delete(PanoRenderWithCompatibility* panoRenderWithCompatibility);
PanoViewEuler* panoRenderWithCompatibility_getcurrentPanoramaData(PanoRenderWithCompatibility* panoRenderWithCompatibility);
void panoRenderWithCompatibility_setweightTexture(PanoRenderWithCompatibility* panoRenderWithCompatibility,uint8_t *data);

void panoRenderWithCompatibility_setpausetime(PanoRenderWithCompatibility* panoRenderWithCompatibility, float time);
void panoRenderWithCompatibility_autoplay(PanoRenderWithCompatibility* panoRenderWithCompatibility, bool autoplay);
void panoRenderWithCompatibility_autoplayhlookat(PanoRenderWithCompatibility* panoRenderWithCompatibility, float hlookat);
#ifdef __cplusplus
}
#endif
#endif //PANO_RENDER_WITH_CAPA_H
