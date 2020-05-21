//
// Created by zhj on 17/4/24.
//

#ifndef PANOVIDEOPLAYER_ANDROID_SPHEREUTIL_H
#define PANOVIDEOPLAYER_ANDROID_SPHEREUTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../gles_const.h"
#include "../enitity.h"
typedef struct SphereUtil {
    float dx, dy, dz;
    int width;
    int height;
    float theta;
    float phi;
    float x;
    float y;
} SphereUtil;

void setWidth_height( SphereUtil *sphereUtil,int h,int w);
void setHeight(SphereUtil *sphereUtil, int height);

void Rotation(Vector3D v, float radians, Vector3D *b);

void cal_norm_xy(SphereUtil *sphereUtil, int px, int py);

void cal_theta_phi(SphereUtil *sphereUtil);

void cal_xyz_from_theta_phi(SphereUtil *sphereUtil);

void cal_sphere_xyz(SphereUtil *sphereUtil,int px, int py);


#ifdef __cplusplus
}
#endif


#endif //PANOVIDEOPLAYER_ANDROID_SPHEREUTIL_H
