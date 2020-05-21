//
// Created by chao on 2017/4/19.
//

#ifndef PANOVIDEOPLAYER_ANDROID_5_0_0_ENITITY_H
#define PANOVIDEOPLAYER_ANDROID_5_0_0_ENITITY_H
#ifdef __cplusplus
extern "C" {
#endif
    
#include <stdbool.h>
#include <stdint.h>
    
#define MODEL_MAX_LENS_COUNT 4 //最多4目鱼眼
#define GAMA  1.776f //gama值
#define MODEL_MAX_FRAME_SIZE 6 //2:1模式cube类型6张全景图
#define MODEL_MAX_CALIBRATION_SIZE 2000
#define MODEL_MAX_PTSPSTH_SIZE 500
#define RENDER_TEXTURE_TRANSFORM_MATRIX_SIZE 16
    
#include "rc_common_render.h"
    
    /**
     * 设备id
     */
    typedef enum ModelDeviceId {
        MODEL_DEVICE_2_1 = 0,
        MODEL_DEVICE_SPHERE_800 = 1,
        MODEL_DEVICE_SPHERE_S = 11,
        MODEL_DEVICE_482 = 101,
        MODEL_DEVICE_SPACE3D=300,
        MODEL_DEVICE_SPHERE_360 = 360,
        MODEL_DEVICE_TWO_SPHERE = 2000,
        MODEL_DEVICE_SPHERE_DETU_TWINS = 2002,
        MODEL_DEVICE_SPHERE_THETAS = 2003,
        MODEL_DEVICE_SPHERE_INSTA_360 = 2004,
        MODEL_DEVICE_SPHERE_Real3D = 2005,
        MODEL_DEVICE_SPHERE_DETU_f4 = 4001,
        MODEL_DEVICE_SPHERE_DETU_M1 = 4003,
        
    } ModelDeviceId;
    
    /**
     * 2:1资源类型
     */
    typedef enum ModelResourceType {
        ModelResourceType_CUBE, //六面体图片
        ModelResourceType_SPHERE, //单张图片
        ModelResourceType_VIDEO, //视频
        ModelResourceType_SPACE3D,//obj模型
    } ModelResourceType;
    
    typedef enum ViewMode {
        VIEWMODE_UNKNOW = 0,
        VIEWMODE_DEF = 1,
        VIEWMODE_FISHEYE = 2,
        VIEWMODE_VR_HORIZONTAL = 3,
        VIEWMODE_VR_VERTICAL = 4,
        VIEWMODE_PLANE = 5, //原图模式
        VIEWMODE_FLAT = 6, //展开的2:1
        VIEWMODE_LITTLEPLANET = 7,
        VIEWMODE_SPHERE = 8,//曲面,
        VIEMMODE_SPACE3D = 9//obj 3d模式
    } ModelViewMode;
    
    typedef struct CalibrationParam {
        int dr; //半径
        int centerX; //圆心x
        int centerY; //圆心y
        float yaw; //绕y
        float pitch; //绕x
        float roll; //绕z
        float fisheye_fov;//f4参数
        
        //畸变矫正参数
        float a;
        float b;
        float c;
        float d;
        float e;
        
        float hd;// 水平平移参数
        float ve;// 垂直平移参数
        float sg;// 水平裁剪参数
        float st;// 垂直裁剪参数
        
        float fisheye_hd;
        float fisheye_ve;
        
        
    } CalibrationParam;
    
    typedef struct ImageData {
        ModelDeviceId modelDeviceId;
        ModelResourceType modelResourceType;
        
        int lensCount; //鱼眼个数
        int label;
        //实际宽高
        int width;
        int height;
        //鱼眼或者双鱼眼标定宽高
        int originwidth;
        int originheight;
        
        int panow;// 鱼眼对应全景的宽
        int panoh;// 鱼眼对应全景的高
        
        float degree; //鱼眼度数
        float maskdegree;//模板度数-针对各种鱼眼
        CalibrationParam params[MODEL_MAX_LENS_COUNT]; //镜头参数
        
        char calibration[MODEL_MAX_CALIBRATION_SIZE];//标定字符串
        int textureWidths[MODEL_MAX_FRAME_SIZE];
        int textureHeights[MODEL_MAX_FRAME_SIZE];
        bool isProcess2_1;
        bool isPushFlow;
        bool isCameraUpsideDown;
        float gamma;
        float rz;
        float rx;
        float ry;
        bool isreplay_f4;

        int textureIds[MODEL_MAX_FRAME_SIZE];
    } ImageData;
    
    typedef struct ViewData {
        int defaultFrameBufferId;
        
        float hLookAt; //横向偏移角度
        float hLookAtMin;
        float hLookAtMax;
        
        float vLookAt; //纵向偏移角度
        float vLookAtMin;
        float vLookAtMax;
        
        float vrFov;  //vr模式下的摄像机视角
        float VREyeOffset;//Vr模式的眼睛偏移量
        
        float curfov;//当前视角
        
        float deffov;     //摄像机视角,默认60
        float deffovMin;
        float deffovMax;
        
        float spherefov;//曲面视角
        float spherefovMin;
        float spherefovMax;
        
        float littlePlanetfov;//小行星视角
        float littlePlanetfovMax;
        float littlePlanetfovMin;
        
        float fisheyefov;//鱼眼视角
        float fisheyefovMax;
        float fisheyefovMin;
        
        float scale;//平面
        float scaleMax;
        float scaleMin;

        bool gyroEnable;
        ModelViewMode viewMode;
        bool isPointSelecting;
        float zOffsetScale;
    } ViewData;
    
    typedef struct Pointf {
        float x;
        float y;
    } Pointf;
    typedef struct Point3f {
        float x;
        float y;
        float z;
    } Point3f;
    
    typedef struct Vector3D {
        float x;
        float y;
        float z;
    } Vector3D;
    
    typedef struct PanoViewEuler
    {
        float pitch;//欧拉角y方向变量
        float yaw;//欧拉角x方向变量
        float roll;//欧拉角z方向变量
        float fov;//非平面模式的透视投影角
        float scale;//2:1平面模式的缩放值
        float x_offset;//2:1平面模式的x偏移量
        float y_offset;//2:1平面模式的y偏移量
        bool isgestureaction;//判断当前是否有手势动作，自动旋转播放时控制当前是否旋转
        bool isfovscale;//判断当前是否是正在缩放操作
    } PanoViewEuler;
    
    typedef struct PanoRenderCallBack
    {
        void (*onPanoRenderRequestChangeEuler)(void* opaque, PanoViewEuler* viewEuler, float* gyoeuler, bool isflat,
                                               float* fovadd, float* yawadd, float* pitchadd);
    } PanoRenderCallBack;
    
    typedef struct PanoRenderDecorCallBack
    {
        void (*onPanoRenderDrawDistortedDecor)(void* opaque);
        void (*onPanoRenderDrawUnDistortedDecor)(void* opaque);
    } PanoRenderDecorCallBack;
    
    typedef struct PanoRenderTexCallBack{
        void(*onUpdateTexImage)(void* opaque, int index, float outCoords[RENDER_TEXTURE_TRANSFORM_MATRIX_SIZE]);
    }PanoRenderTexCallBack;
    
    
#ifdef __cplusplus
}
#endif
#endif //PANOVIDEOPLAYER_ANDROID_5_0_0_ENITITY_H
