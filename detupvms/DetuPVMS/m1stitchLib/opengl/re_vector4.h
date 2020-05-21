#pragma once

#include <stdio.h>


#pragma pack(push,16)
union _Vector4 {
	struct {
		float x, y, z, w;
	};
	struct {
		float r, g, b, a;
	};
	struct {
		float s, t, p, q;
	};
	float v[4];
};
#pragma pack(pop)


typedef union _Vector4 ReVector4;

static inline ReVector4 vector4Make(float x, float y, float z, float w) {
    ReVector4 v = {x, y, z, w};
    return v;
}
