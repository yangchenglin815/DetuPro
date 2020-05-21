#pragma once

#include <stdio.h>

#include "re_vector3.h"

typedef  struct 
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
    
}gl_sphere_struct;

void re_sphere_rotation(ReVector3 v,float radians, ReVector3* b);

void re_init_gl_sphere_struct(gl_sphere_struct *sp);

void re_cal_xyz_from_theta_phi(gl_sphere_struct *sp);

void re_cal_sphere_xyz(gl_sphere_struct *sp,int px,int py);


