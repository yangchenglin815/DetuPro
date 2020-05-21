//
// Created by chao on 2018/3/22.
//

#ifndef M1_ANDROID_JNI_UTILS_H_H
#define M1_ANDROID_JNI_UTILS_H_H

#include <jni.h>

JNIEnv *jniUtils_setupThreadEnv();

void jniUtils_detachThreadEnv();

void jniUtils_setJavaVm(JavaVM *jvm);

JavaVM *jniUtils_getJavaVm();

#endif //M1_ANDROID_JNI_UTILS_H_H
