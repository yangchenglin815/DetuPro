#pragma once

#include <math.h>


union _Vector2 {
    struct {
        float x, y;
    };
   
    float v[2];
};
typedef union _Vector2 ReVector2;

static inline ReVector2 vector2Make(float x, float y) {
    ReVector2 v = {x, y};
    return v;
}



