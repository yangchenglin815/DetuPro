#pragma once

#include <stdio.h>


#include <math.h>
#include <float.h>
#include <stdbool.h>




#include "re_vector3.h"
#include "re_vector4.h"

#ifdef WIN32
#pragma pack(push,16)
union _Matrix4 {
	struct {
		float m00, m01, m02, m03;
		float m10, m11, m12, m13;
		float m20, m21, m22, m23;
		float m30, m31, m32, m33;
	};
	float m[16];
};
#pragma pack(pop)
#else
union _Matrix4 {
	struct {
		float m00, m01, m02, m03;
		float m10, m11, m12, m13;
		float m20, m21, m22, m23;
		float m30, m31, m32, m33;
	};
	float m[16];
} __attribute__((aligned(16)));
#endif // WIN32



typedef union _Matrix4 ReMatrix4;

ReMatrix4 const g_matrix4Identity = { 1., 0., 0., 0., 0., 1., 0., 0., 0., 0., 1., 0., 0., 0., 0., 1. };
ReMatrix4 const g_matrix4Zero = { 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. };

static inline ReMatrix4 matrix4MakeScale(float sx, float sy, float sz) {
    ReMatrix4 m = g_matrix4Identity;
    m.m[0] = sx;
    m.m[5] = sy;
    m.m[10] = sz;
    return m;
}

static inline ReMatrix4 matrix4MakeRotation(float radians, float x, float y, float z) {
    ReVector3 v = vector3Normalize(vector3Make(x, y, z));
    float cosr = cos(radians);
    float cosp = 1.0f - cosr;
    float sinr = sin(radians);
    
    ReMatrix4 m = {cosr + cosp * v.v[0] * v.v[0],
        cosp * v.v[0] * v.v[1] + v.v[2] * sinr,
        cosp * v.v[0] * v.v[2] - v.v[1] * sinr,
        0.0f,
        cosp * v.v[0] * v.v[1] - v.v[2] * sinr,
        cosr + cosp * v.v[1] * v.v[1],
        cosp * v.v[1] * v.v[2] + v.v[0] * sinr,
        0.0f,
        cosp * v.v[0] * v.v[2] + v.v[1] * sinr,
        cosp * v.v[1] * v.v[2] - v.v[0] * sinr,
        cosr + cosp * v.v[2] * v.v[2],
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        1.0f};
    
    return m;
}

static inline ReMatrix4 matrix4Translate(ReMatrix4 matrix, float tx, float ty, float tz) {
    ReMatrix4 m = {matrix.m[0], matrix.m[1], matrix.m[2], matrix.m[3],
        matrix.m[4], matrix.m[5], matrix.m[6], matrix.m[7],
        matrix.m[8], matrix.m[9], matrix.m[10], matrix.m[11],
        matrix.m[0] * tx + matrix.m[4] * ty + matrix.m[8] * tz + matrix.m[12],
        matrix.m[1] * tx + matrix.m[5] * ty + matrix.m[9] * tz + matrix.m[13],
        matrix.m[2] * tx + matrix.m[6] * ty + matrix.m[10] * tz + matrix.m[14],
        matrix.m[3] * tx + matrix.m[7] * ty + matrix.m[11] * tz + matrix.m[15]};
    return m;
}

static inline ReMatrix4 matrix4Scale(ReMatrix4 matrix, float sx, float sy, float sz) {
    ReMatrix4 m = {matrix.m[0] * sx, matrix.m[1] * sx, matrix.m[2] * sx, matrix.m[3] * sx,
        matrix.m[4] * sy, matrix.m[5] * sy, matrix.m[6] * sy, matrix.m[7] * sy,
        matrix.m[8] * sz, matrix.m[9] * sz, matrix.m[10] * sz, matrix.m[11] * sz,
        matrix.m[12], matrix.m[13], matrix.m[14], matrix.m[15]};
    return m;
}

static inline  ReMatrix4 matrix4Multiply(ReMatrix4 matrixLeft, ReMatrix4 matrixRight) {
    ReMatrix4 m;
    
    m.m[0] = matrixLeft.m[0] * matrixRight.m[0] + matrixLeft.m[4] * matrixRight.m[1] + matrixLeft.m[8] * matrixRight.m[2] + matrixLeft.m[12] * matrixRight.m[3];
    m.m[4] = matrixLeft.m[0] * matrixRight.m[4] + matrixLeft.m[4] * matrixRight.m[5] + matrixLeft.m[8] * matrixRight.m[6] + matrixLeft.m[12] * matrixRight.m[7];
    m.m[8] = matrixLeft.m[0] * matrixRight.m[8] + matrixLeft.m[4] * matrixRight.m[9] + matrixLeft.m[8] * matrixRight.m[10] + matrixLeft.m[12] * matrixRight.m[11];
    m.m[12] = matrixLeft.m[0] * matrixRight.m[12] + matrixLeft.m[4] * matrixRight.m[13] + matrixLeft.m[8] * matrixRight.m[14] + matrixLeft.m[12] * matrixRight.m[15];
    
    m.m[1] = matrixLeft.m[1] * matrixRight.m[0] + matrixLeft.m[5] * matrixRight.m[1] + matrixLeft.m[9] * matrixRight.m[2] + matrixLeft.m[13] * matrixRight.m[3];
    m.m[5] = matrixLeft.m[1] * matrixRight.m[4] + matrixLeft.m[5] * matrixRight.m[5] + matrixLeft.m[9] * matrixRight.m[6] + matrixLeft.m[13] * matrixRight.m[7];
    m.m[9] = matrixLeft.m[1] * matrixRight.m[8] + matrixLeft.m[5] * matrixRight.m[9] + matrixLeft.m[9] * matrixRight.m[10] + matrixLeft.m[13] * matrixRight.m[11];
    m.m[13] = matrixLeft.m[1] * matrixRight.m[12] + matrixLeft.m[5] * matrixRight.m[13] + matrixLeft.m[9] * matrixRight.m[14] + matrixLeft.m[13] * matrixRight.m[15];
    
    m.m[2] = matrixLeft.m[2] * matrixRight.m[0] + matrixLeft.m[6] * matrixRight.m[1] + matrixLeft.m[10] * matrixRight.m[2] + matrixLeft.m[14] * matrixRight.m[3];
    m.m[6] = matrixLeft.m[2] * matrixRight.m[4] + matrixLeft.m[6] * matrixRight.m[5] + matrixLeft.m[10] * matrixRight.m[6] + matrixLeft.m[14] * matrixRight.m[7];
    m.m[10] = matrixLeft.m[2] * matrixRight.m[8] + matrixLeft.m[6] * matrixRight.m[9] + matrixLeft.m[10] * matrixRight.m[10] + matrixLeft.m[14] * matrixRight.m[11];
    m.m[14] = matrixLeft.m[2] * matrixRight.m[12] + matrixLeft.m[6] * matrixRight.m[13] + matrixLeft.m[10] * matrixRight.m[14] + matrixLeft.m[14] * matrixRight.m[15];
    
    m.m[3] = matrixLeft.m[3] * matrixRight.m[0] + matrixLeft.m[7] * matrixRight.m[1] + matrixLeft.m[11] * matrixRight.m[2] + matrixLeft.m[15] * matrixRight.m[3];
    m.m[7] = matrixLeft.m[3] * matrixRight.m[4] + matrixLeft.m[7] * matrixRight.m[5] + matrixLeft.m[11] * matrixRight.m[6] + matrixLeft.m[15] * matrixRight.m[7];
    m.m[11] = matrixLeft.m[3] * matrixRight.m[8] + matrixLeft.m[7] * matrixRight.m[9] + matrixLeft.m[11] * matrixRight.m[10] + matrixLeft.m[15] * matrixRight.m[11];
    m.m[15] = matrixLeft.m[3] * matrixRight.m[12] + matrixLeft.m[7] * matrixRight.m[13] + matrixLeft.m[11] * matrixRight.m[14] + matrixLeft.m[15] * matrixRight.m[15];
    
    return m;
}

static inline ReVector4 matrix4MultiplyVector4(ReMatrix4 matrixLeft, ReVector4 vectorRight) {
    ReVector4 v = {matrixLeft.m[0] * vectorRight.v[0] + matrixLeft.m[4] * vectorRight.v[1] + matrixLeft.m[8] * vectorRight.v[2] + matrixLeft.m[12] * vectorRight.v[3],
        matrixLeft.m[1] * vectorRight.v[0] + matrixLeft.m[5] * vectorRight.v[1] + matrixLeft.m[9] * vectorRight.v[2] + matrixLeft.m[13] * vectorRight.v[3],
        matrixLeft.m[2] * vectorRight.v[0] + matrixLeft.m[6] * vectorRight.v[1] + matrixLeft.m[10] * vectorRight.v[2] + matrixLeft.m[14] * vectorRight.v[3],
        matrixLeft.m[3] * vectorRight.v[0] + matrixLeft.m[7] * vectorRight.v[1] + matrixLeft.m[11] * vectorRight.v[2] + matrixLeft.m[15] * vectorRight.v[3]};
    return v;
}

static inline ReMatrix4 matrix4Rotate(ReMatrix4 matrix, float radians, float x, float y, float z) {
    ReMatrix4 rm = matrix4MakeRotation(radians, x, y, z);
    return matrix4Multiply(matrix, rm);
}

static inline ReMatrix4 matrix4Invert(ReMatrix4 m, bool* isInvertible) {
    float a0 = m.m[0] * m.m[5] - m.m[1] * m.m[4];
    float a1 = m.m[0] * m.m[6] - m.m[2] * m.m[4];
    float a2 = m.m[0] * m.m[7] - m.m[3] * m.m[4];
    float a3 = m.m[1] * m.m[6] - m.m[2] * m.m[5];
    float a4 = m.m[1] * m.m[7] - m.m[3] * m.m[5];
    float a5 = m.m[2] * m.m[7] - m.m[3] * m.m[6];
    float b0 = m.m[8] * m.m[13] - m.m[9] * m.m[12];
    float b1 = m.m[8] * m.m[14] - m.m[10] * m.m[12];
    float b2 = m.m[8] * m.m[15] - m.m[11] * m.m[12];
    float b3 = m.m[9] * m.m[14] - m.m[10] * m.m[13];
    float b4 = m.m[9] * m.m[15] - m.m[11] * m.m[13];
    float b5 = m.m[10] * m.m[15] - m.m[11] * m.m[14];
    
    float det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;
    if (fabs(det) > DBL_EPSILON) {
        ReMatrix4 result;
        result.m[0] = +m.m[5] * b5 - m.m[6] * b4 + m.m[7] * b3;
        result.m[4] = -m.m[4] * b5 + m.m[6] * b2 - m.m[7] * b1;
        result.m[8] = +m.m[4] * b4 - m.m[5] * b2 + m.m[7] * b0;
        result.m[12] = -m.m[4] * b3 + m.m[5] * b1 - m.m[6] * b0;
        result.m[1] = -m.m[1] * b5 + m.m[2] * b4 - m.m[3] * b3;
        result.m[5] = +m.m[0] * b5 - m.m[2] * b2 + m.m[3] * b1;
        result.m[9] = -m.m[0] * b4 + m.m[1] * b2 - m.m[3] * b0;
        result.m[13] = +m.m[0] * b3 - m.m[1] * b1 + m.m[2] * b0;
        result.m[2] = +m.m[13] * a5 - m.m[14] * a4 + m.m[15] * a3;
        result.m[6] = -m.m[12] * a5 + m.m[14] * a2 - m.m[15] * a1;
        result.m[10] = +m.m[12] * a4 - m.m[13] * a2 + m.m[15] * a0;
        result.m[14] = -m.m[12] * a3 + m.m[13] * a1 - m.m[14] * a0;
        result.m[3] = -m.m[9] * a5 + m.m[10] * a4 - m.m[11] * a3;
        result.m[7] = +m.m[8] * a5 - m.m[10] * a2 + m.m[11] * a1;
        result.m[11] = -m.m[8] * a4 + m.m[9] * a2 - m.m[11] * a0;
        result.m[15] = +m.m[8] * a3 - m.m[9] * a1 + m.m[10] * a0;
        
        float invDet = ((float) 1) / det;
        result.m[0] *= invDet;
        result.m[1] *= invDet;
        result.m[2] *= invDet;
        result.m[3] *= invDet;
        result.m[4] *= invDet;
        result.m[5] *= invDet;
        result.m[6] *= invDet;
        result.m[7] *= invDet;
        result.m[8] *= invDet;
        result.m[9] *= invDet;
        result.m[10] *= invDet;
        result.m[11] *= invDet;
        result.m[12] *= invDet;
        result.m[13] *= invDet;
        result.m[14] *= invDet;
        result.m[15] *= invDet;
        
        *isInvertible = true;
        return result;
    } else {
        *isInvertible = false;
        return g_matrix4Identity;
    }
}


