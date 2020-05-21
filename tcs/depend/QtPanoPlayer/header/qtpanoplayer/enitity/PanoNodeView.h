//
// Created by chao on 2017/11/6.
//

#ifndef DPV_ANDROID_PANONODEVIEW_H
#define DPV_ANDROID_PANONODEVIEW_H


namespace DetuPanoPlayer {

    typedef enum PanoViewMode {
        PanoViewMode_UNKNOW =0, //全景模式
        PanoViewMode_DEFAULT = 1, //全景模式
        PanoViewMode_FISHEYE, //鱼眼模式
        PanoViewMode_VR_HORIZONTAL, //左右vr模式
        PanoViewMode_VR_VERTICAL, //上下vr模式
        PanoViewMode_ORIGINAL, //原图模式，原始图像
        PanoViewMode_FLAT, //平面模式，展开的2:1模式
        PanoViewMode_LITTLE_PLANET, //小行星模式
        PanoViewMode_SPHERE, //曲面模式
        PanoViewMode_SPACE3D,//obj 3d模式
    } PanoViewMode;


    class PanoNodeView {
    public:
        PanoNodeView();

        ~PanoNodeView();

        float hLookAt = 0.0f;
        float hLookAtMin = -180.0f;
        float hLookAtMax = 180.0f;

        float vLookAt = 0.0f;
        float vLookAtMin = -90.0f;
        float vLookAtMax = 90.0f;

        float curfov = 0.0;//当前视角
        float deffov = 65.0f;//普通视角
        float deffovMin = 40.0f;
        float deffovMax = 90.0f;

        float spherefov = 45.0f;//曲面视角
        float spherefovMin = 20.0f;
        float spherefovMax = 120.0f;

        float littlePlanetfov = 125.0f;//小行星视角
        float littlePlanetfovMax = 150.0f;
        float littlePlanetfovMin = 45.0f;

        float fisheyefov = 125.0f;//鱼眼视角
        float fisheyefovMax = 130.0f;
        float fisheyefovMin = 45.0f;
        
        float scale =1.0f;//平面
        float scaleMax=3.0f;
        float scaleMin=0.8f;
        float VREyeOffset = 0;//Vr模式的眼睛偏移量
        float vrFov = 90.0f;
        PanoViewMode viewMode;
        bool  isPointSelecting = false;
    };

}

#endif //DPV_ANDROID_PANONODEVIEW_H
