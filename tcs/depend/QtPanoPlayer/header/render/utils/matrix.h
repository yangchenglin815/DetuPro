//
// Created by chao on 2017/3/30.
//

#ifndef PANOPLAYER_MATRIX_H
#define PANOPLAYER_MATRIX_H

void matrix_perspectiveM(float m[], int offset, float fovy, float aspect, float zNear, float zFar);

void matrix_setIdentityM(float sm[], int smOffset);

void matrix_scaleM(float m[], int mOffset, float x, float y, float z);

void matrix_translateM(float m[], int mOffset, float x, float y, float z);

void matrix_multiplyMM(float result[], int resultOffset,
                float lhs[], int lhsOffset, float rhs[], int rhsOffset);

void matrix_setRotateM(float rm[], int rmOffset, float a, float x, float y, float z);

void matrix_rotateM(float m[], int mOffset, float a, float x, float y, float z);

void matrix_setLookAtM(float rm[], int rmOffset,
                float eyeX, float eyeY, float eyeZ,
                float centerX, float centerY, float centerZ, float upX, float upY,
                float upZ);

void matrix_setRotateEulerM(float rm[], int rmOffset,
                     float x, float y, float z);

void matrix_frustumM(float m[], int offset,
              float left, float right, float bottom, float top,
              float near, float far);


#endif //PANOPLAYER_MATRIX_H
