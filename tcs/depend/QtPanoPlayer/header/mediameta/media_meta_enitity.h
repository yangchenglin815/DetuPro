//
//  MediaMetaEnitity.h
//  MediaMetaLib
//
//  Created by chao on 2017/1/7.
//  Copyright © 2017年 detu. All rights reserved.
//

#ifndef MediaMetaEnitity_h
#define MediaMetaEnitity_h
#define inline __inline

#include<stdio.h>

#define MEDIA_META_MAX_CALIBRATION 2000

#define MEDIA_META_MAX_SERIAL_NUMBER 2000

typedef enum MediaMetaMediaType{
    MediaMetaMediaType_PIC = 0,
    MediaMetaMediaType_VIDEO = 1,
    MediaMetaMediaType_UNKNOW = 2
} MediaMetaMediaType;

typedef enum {
    //详细型号类型
    Sphere800 = 1,
    SphereS = 2,

    //双鱼眼
    Twin_01 = 10, //TB401
    Twin_02 = 11, //TB402
    Twin_03 = 12, //TB403
    Liveman_D1 = 13,  //TB404
    Dragon = 14,      //DB405
    NIX = 15,         //NB406

    //四鱼眼
    F4 = 100, //F4
    F4_Pro = 101, //F4_Pro

    //大致类型
    OneFishEye = 200,
    TwoFishEye = 201,
    FourFishEye = 202,
    UnKnow = 0,
} MediaCameraId;

typedef struct MediaInfo {
    MediaMetaMediaType mediaType;
    int width;
    int height;
	long duration;
} MediaInfo;

typedef struct CameraMediaInfo {
    MediaInfo mediaInfo;
    MediaCameraId mediaCameraId;
    char calibration[MEDIA_META_MAX_CALIBRATION]; //标定字符串
    char serialNumber[MEDIA_META_MAX_SERIAL_NUMBER]; // sn或者ssid
} CameraMediaInfo;

typedef struct LiveMediaInfo {
    CameraMediaInfo cameraMediaInfo;
    char serverIp[MEDIA_META_MAX_CALIBRATION]; //服务器地址
} LiveMediaInfo;

#endif /* MediaMetaEnitity_h */
