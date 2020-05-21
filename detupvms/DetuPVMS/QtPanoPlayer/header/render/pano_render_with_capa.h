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

#if defined(__ANDROID__)

#include <jni.h>

#endif

#include "rc_common_render.h"

typedef struct ImageDataWrapper {
    RcPlatform platform;
    ModelDeviceId modelDeviceId;
    ModelResourceType modelResourceType;
    char calibration[MODEL_MAX_CALIBRATION_SIZE];
    RcFrameInfo rcFrameInfos[RC_MAX_FRAME_SIZE];
    GLfloat targetTextureCoordWeights[RC_MAX_FRAME_SIZE][RC_TARGET_TEXTURE_COORD_SIZE];
    int frameSize; //��֡��
    int textureWidths[RC_MAX_FRAME_SIZE];
    int textureHeights[RC_MAX_FRAME_SIZE];
    float gamma;
    float rz;
    float rx;
    float ry;
    bool isreplay_f4;
    bool isProcess2_1;
    bool isPushFlow;//判断是否推流
    bool isCameraUpsideDown;//判断推流时相机是否倒置
    bool isReverse; //是否倒置，默认是false
    bool isRenderBgra;
    bool prohibitSwitchAnimation;
    bool notRenderOutput;
    //for android mediacodec ore cuda
    GLuint textureIds[RC_MAX_FRAME_SIZE];
    void *opaque;
} ImageDataWrapper;

struct PanoRenderWithCompatibility;

typedef struct PanoRenderWithCompatibility PanoRenderWithCompatibility;

#if defined(__ANDROID__)

void panoRenderWithCompatibility_jniLoad(JavaVM *vm);

#endif

PanoRenderWithCompatibility *panoRenderWithCompatibility_new();

bool panoRenderWithCompatibility_setup(PanoRenderWithCompatibility *panoRenderWithCompatibility,
                                       ImageDataWrapper *imageData, ViewData *viewData);

void panoRenderWithCompatibility_setRenderCallBack(
        PanoRenderWithCompatibility *panoRenderWithCompatibility, void *opaque,
        PanoRenderCallBack *callBack);

void panoRenderWithCompatibility_setDecorCallBack(
        PanoRenderWithCompatibility *panoRenderWithCompatibility, void *opaque,
        PanoRenderDecorCallBack *callBack);

void
panoRenderWithCompatibility_setTexCallBack(PanoRenderWithCompatibility *panoRenderWithCompatibility,
                                           void *opaque, PanoRenderTexCallBack *callBack);

RcCommonRender *panoRenderWithCompatibility_getCommonRender(
        PanoRenderWithCompatibility *panoRenderWithCompatibility);

void
panoRenderWithCompatibility_setViewport(PanoRenderWithCompatibility *panoRenderWithCompatibility,
                                        int w, int h);

void panoRenderWithCompatibility_updateDefaultFrameBufferObject(
        PanoRenderWithCompatibility *panoRenderWithCompatibility, GLuint defaultFrameBufferObject);

/**
 *
 * @param panoRenderWithCompatibility
 * @param frames
 * @param isUpdateFrame
 * @param isShow 是否显示画面，有时候需要消耗硬解纹理但是不需要显示
 */
void panoRenderWithCompatibility_draw(PanoRenderWithCompatibility *panoRenderWithCompatibility,
                                      RcFrame *frames, bool isUpdateFrame, bool isShow);

void panoRenderWithCompatibility_getRenderWindowSize(
        PanoRenderWithCompatibility *panoRenderWithCompatibility, int outRenderWindowSize[2]);

void
panoRenderWithCompatibility_switchViewMode(PanoRenderWithCompatibility *panoRenderWithCompatibility,
                                           ModelViewMode viewMode);

void panoRenderWithCompatibility_animationswitchViewMode(
        PanoRenderWithCompatibility *panoRenderWithCompatibility, ModelViewMode viewMode,
        float duration, EaseType easeType);

void panoRenderWithCompatibility_delete(PanoRenderWithCompatibility *panoRenderWithCompatibility);

PanoViewEuler *panoRenderWithCompatibility_getcurrentPanoramaData(
        PanoRenderWithCompatibility *panoRenderWithCompatibility);

void panoRenderWithCompatibility_setweightTexture(
        PanoRenderWithCompatibility *panoRenderWithCompatibility, uint8_t *data, int w, int h,
        int index);

void
panoRenderWithCompatibility_setpausetime(PanoRenderWithCompatibility *panoRenderWithCompatibility,
                                         float time);

void panoRenderWithCompatibility_autoplay(PanoRenderWithCompatibility *panoRenderWithCompatibility,
                                          bool autoplay, float hlookat);

void
panoRenderWithCompatibility_autoVertical(PanoRenderWithCompatibility *panoRenderWithCompatibility,
                                         bool autoVertical);//自动播放垂直方向是否回归到水平线

void panoRenderWithCompatibility_reverse(PanoRenderWithCompatibility *panoRenderWithCompatibility,
                                         float degree);//��ת����

void
panoRenderWithCompatibility_getClipsparam(PanoRenderWithCompatibility *panoRenderWithCompatibility,
                                          float *fov, float *hlookat,
                                          float *vlookat);//get clips param
void
panoRenderWithCompatibility_setClipsparam(PanoRenderWithCompatibility *panoRenderWithCompatibility,
                                          float fov, float hlookat, float vlookat, float near,
                                          float zoffset); //set clips param
void
panoRenderWithCompatibility_setClipsswitch(PanoRenderWithCompatibility *panoRenderWithCompatibility,
                                           bool isclips);//clips switch

void panoRenderWithCompatibility_setPointSelectingSwitch(PanoRenderWithCompatibility *panoRenderWithCompatibility,bool isPointSelecting);//设置点选开关，为真时，fov不受模式的最大最小值限制

void panoRenderWithCompatibility_animationsetfov(
        PanoRenderWithCompatibility *panoRenderWithCompatibility, float detafov, float duration,
        EaseType easeType);//设置m1离场动画
/*
 * Mutual conversion between latitude and longitude and screen coordinates
 */
void panoRenderWithCompatibility_calDegByWinPoint(
        PanoRenderWithCompatibility *panoRenderWithCompatibility, float px, float py,
        float *outdeg);

void panoRenderWithCompatibility_calDegByWinPointleft(
        PanoRenderWithCompatibility *panoRenderWithCompatibility, float px, float py,
        float *outdeg);

void panoRenderWithCompatibility_calDegByWinPointRight(
        PanoRenderWithCompatibility *panoRenderWithCompatibility, float px, float py,
        float *outdeg);

void panoRenderWithCompatibility_calWinPointByDeg(
        PanoRenderWithCompatibility *panoRenderWithCompatibility, float degX, float degY, int sw,
        int sh, float *out);

void panoRenderWithCompatibility_calWinPointByDegleft(
        PanoRenderWithCompatibility *panoRenderWithCompatibility, float degX, float degY, int sw,
        int sh, float *out);

void panoRenderWithCompatibility_calWinPointByDegright(
        PanoRenderWithCompatibility *panoRenderWithCompatibility, float degX, float degY, int sw,
        int sh, float *out);

#ifdef __cplusplus
}
#endif
#endif //PANO_RENDER_WITH_CAPA_H
