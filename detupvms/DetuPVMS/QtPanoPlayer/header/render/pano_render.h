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
    
    void panoRender_setweightTexture(PanoRender* render, uint8_t *data, int w, int h,int index);//set weight picture texture
    
    void panoRender_setViewport(PanoRender* render, int w, int h);
    
    void panoRender_draw(PanoRender* render,float alpha);
    
    void panoRender_switchViewMode(PanoRender* render, ModelViewMode viewMode);
    void panoRender_animationswitchViewMode(PanoRender* render, ModelViewMode viewMode, float duration, EaseType easeType);
    
    void panoRender_delete(PanoRender* render);
    PanoViewEuler* getcurrentPanoramaData(PanoRender *render);
    void panoRender_setpausetime(PanoRender *render,float time);//自动播放暂停参数
    void panoRender_autoplay(PanoRender *render, bool autoplay, float hlookat);//自动播放速度
    void panoRender_autoVertical(PanoRender *render,bool autoVertical);//自动播放垂直方向是否回归到水平线
    
    void panoRender_reverse(PanoRender *render, float degree);//reverse function--f4p or m1
    void panoRender_getClipsparam(PanoRender *render, float *fov, float *hlookat, float*vlookat);//get clips param
    void panoRender_setClipsparam(PanoRender *render, float fov, float hlookat, float vlookat, float near, float zoffset); //set clips param
    void panoRender_animationsetfov(PanoRender* render,float detafov, float duration, EaseType easeType);//设置m1离场动画
    
    void panoRender_setClipsswitch(PanoRender *render,bool isclips);//clips switch
    void panoRender_setPointSelectingSwitch(PanoRender *render,bool isPointSelecting);//设置点选开关，为真时，fov不受模式的最大最小值限制
    /*
     * Mutual conversion between latitude and longitude and screen coordinates
     */
    void panoRender_calDegByWinPoint(PanoRender *render,float px, float py,float*outdeg);// screen coordinates  to latitude&&longitude
    void panoRender_calDegByWinPointleft(PanoRender *render,float px, float py,float *outdeg);//vr left window screen coordinates  to latitude&&longitude
    void panoRender_calDegByWinPointRight(PanoRender *render,float px, float py,float *outdeg);//vr right window screen coordinates  to latitude&&longitude
    void panoRender_calWinPointByDeg(PanoRender *render,float degX, float degY, int sw, int sh,float *out);//latitude&&longitude to screen coordinates
    void panoRender_calWinPointByDegleft(PanoRender *render,float degX, float degY, int sw, int sh,float *out);//vr left window latitude&&longitude to screen coordinates
    void panoRender_calWinPointByDegright(PanoRender *render,float degX, float degY, int sw, int sh,float *out);//vr right window latitude&&longitude to screen coordinates
    float panoRender_calScaleByFov(PanoRender *render);
    
#ifdef __cplusplus
}
#endif
#endif //PANOVIDEOPLAYER_ANDROID_5_0_0_GLES_RENDER_H
