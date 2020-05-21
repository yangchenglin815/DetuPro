//
// Created by chao on 2018/3/22.
//

#ifndef M1_ANDROID_ANDROID_BYTE_BUFFER_H
#define M1_ANDROID_ANDROID_BYTE_BUFFER_H

#include <jni.h>

struct ByteBuffer;
typedef struct ByteBuffer ByteBuffer;

ByteBuffer *byteBuffer_allocate(JNIEnv *env, int capacity);

ByteBuffer *byteBuffer_allocateDirect(JNIEnv *env, int capacity);

void byteBuffer_put(JNIEnv *env, ByteBuffer *byteBuffer, void *data, int length);

void byteBuffer_delete(JNIEnv *env, ByteBuffer *byteBuffer);

#endif //M1_ANDROID_ANDROID_BYTE_BUFFER_H
