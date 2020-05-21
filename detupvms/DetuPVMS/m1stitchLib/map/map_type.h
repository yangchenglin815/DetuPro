/***************************************************************************************************
*
* 版权信息：Copyright (c) 得图网络 2016
*
* 文件名称：map_type.h
* 摘    要：映射函数相关结构体定义
*
* 当前版本：V1.0.0
* 作  者： 涂植跑
* 日  期： 2016.12
* 备  注： 创建
***************************************************************************************************/

#pragma once
#pragma execution_character_set("utf-8")
// 本文件为utf-8 编码格式

#ifndef _MAP_TYPE_H_
#define _MAP_TYPE_H_

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>



#define MAP_PI                      (3.14159265358979323846264338327950288)
#define MAP_PI_2                    (MAP_PI / 2)
#define MAP_PI_4                    (MAP_PI / 4)
#define MAP_PI3_4                   (MAP_PI_4 * 3)
#define MAP_PI5_4                   (MAP_PI_4 * 5)
#define MAP_PI7_4                   (MAP_PI_4 * 5)
#define MAP_FLOAT_MIN               (0.0000001f)    // 最小浮点数
#define MAP_TODEGRESS(a)            ((a) * 180.0f / MAP_PI)
#define MAP_TORADIANS(a)            ((a) * MAP_PI / 180.0f)


typedef enum _MAP_FACE
{
    MAP_FACE_FRONT  = 0,
    MAP_FACE_BACK   = 1,
    MAP_FACE_LEFT   = 2,
    MAP_FACE_RIGHT  = 3,
    MAP_FACE_TOP    = 4,
    MAP_FACE_BOTTOM = 5

}MAP_FACE;

typedef struct _MAP_CUBIC_COORD
{
    float x;
    float y;
    float z;
}MAP_CUBIC_COORD;

typedef struct _MAP_POINT_2I
{
    int x;
    int y;
}MAP_POINT_2I;

typedef struct _MAP_POINT_2F
{
    float x;
    float y;
}MAP_POINT_2F;

typedef struct _MAP_XY_RANGE
{

    int xStart;
    int xEnd;
    int yStart;
    int yEnd;

}MAP_XY_RANGE;

typedef union _MAP_VECTOR3 {
    struct
    {
        float x, y, z;
    };
    struct
    {
        float r, g, b;
    };
    struct
    {
        float s, t, p;
    };
    float v[3];
}MAP_VECTOR3;

typedef struct _MAP_SPHERE_PM
{

    float dx;
    float dy;
    float dz;
    int width;
    int height;
    float theta;
    float phi;
    float x;
    float y;

}MAP_SPHERE_PM;

typedef struct _MAP_UTIL_MAT
{
    float x00, x01, x02, x03;
    float x10, x11, x12, x13;
    float x20, x21, x22, x23;
    float x30, x31, x32, x33;
}MAP_UTIL_MAT;





#endif // _MAP_TYPE_H_







