#pragma once

#include <math.h>


union _Vector3 {
    struct {
        float x, y, z;
    };
    struct {
        float r, g, b;
    };
    struct {
        float s, t, p;
    };
    float v[3];
};
typedef union _Vector3 ReVector3;

static inline  ReVector3 vector3Make(float x, float y, float z) {
    ReVector3 v = {x, y, z};
    return v;
}

 static inline float vector3Length(ReVector3 vector) {
    return sqrt(vector.v[0] * vector.v[0] + vector.v[1] * vector.v[1] + vector.v[2] * vector.v[2]);
}

 static inline ReVector3 vector3Normalize(ReVector3 vector) {
    float scale = 1.0f / vector3Length(vector);
    ReVector3 v = {vector.v[0] * scale, vector.v[1] * scale, vector.v[2] * scale};
    return v;
}

