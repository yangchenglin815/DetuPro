//
// Created by chao on 2018/3/22.
//

#include <stdbool.h>
#include <malloc.h>
#include <memory.h>
#include "android_byte_buffer.h"

#define BYTE_BUFFER_CLASS_PATH "java.nio.ByteBuffer"

struct ByteBuffer {
    bool isDirect;
    jobject jObjBuffer;
};

ByteBuffer *byteBuffer_allocate(JNIEnv *env, int capacity) {
    ByteBuffer *byteBuffer = (ByteBuffer *) calloc(1, sizeof(ByteBuffer));
    jclass jClassByteBuffer = (*env)->FindClass(env, BYTE_BUFFER_CLASS_PATH);
    jmethodID jMethodAllocate = (*env)->GetStaticMethodID(env, jClassByteBuffer, "allocate",
                                                          "(I)Ljava/nio/ByteBuffer;");
    jobject jObjByteBuffer = (*env)->CallStaticObjectMethod(env, jClassByteBuffer, jMethodAllocate,
                                                            capacity);
    byteBuffer->jObjBuffer = (*env)->NewGlobalRef(env, jObjByteBuffer);
    return byteBuffer;
}

ByteBuffer *byteBuffer_allocateDirect(JNIEnv *env, int capacity) {
    ByteBuffer *byteBuffer = (ByteBuffer *) calloc(1, sizeof(ByteBuffer));
    jclass jClassByteBuffer = (*env)->FindClass(env, BYTE_BUFFER_CLASS_PATH);
    jmethodID jMethodAllocateDirect = (*env)->GetStaticMethodID(env, jClassByteBuffer,
                                                                "allocateDirect",
                                                                "(I)Ljava/nio/ByteBuffer;");
    jobject jObjByteBuffer = (*env)->CallStaticObjectMethod(env, jClassByteBuffer,
                                                            jMethodAllocateDirect,
                                                            capacity);
    byteBuffer->jObjBuffer = (*env)->NewGlobalRef(env, jObjByteBuffer);
    byteBuffer->isDirect = true;
    return byteBuffer;
}

void byteBuffer_put(JNIEnv *env, ByteBuffer *byteBuffer, void *data, int length) {
    if (byteBuffer == NULL || byteBuffer == NULL || !byteBuffer->isDirect) {
        return;
    }
    void *buffer = (*env)->GetDirectBufferAddress(env, byteBuffer->jObjBuffer);
    memcpy(buffer, data, length);
}

void byteBuffer_delete(JNIEnv *env, ByteBuffer *byteBuffer) {
    if (byteBuffer == NULL) {
        return;
    }
    if (byteBuffer->jObjBuffer != NULL) {
        (*env)->DeleteGlobalRef(env, byteBuffer->jObjBuffer);
    }
    free(byteBuffer);
}
