//
// Created by chao on 2018/3/22.
//

#include <pthread.h>
#include "jni_utils.h"

static JavaVM *g_jvm;
static pthread_key_t current_env;
static pthread_once_t once = PTHREAD_ONCE_INIT;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

static void jni_detach_env(void *data) {
    if (g_jvm) {
        (*g_jvm)->DetachCurrentThread(g_jvm);
    }
}

static void jni_create_pthread_key(void) {
    pthread_key_create(&current_env, jni_detach_env);
}

JNIEnv *jniUtils_setupThreadEnv() {
    int ret = 0;
    JNIEnv *env = NULL;

    pthread_mutex_lock(&lock);
    pthread_once(&once, jni_create_pthread_key);

    if ((env = (JNIEnv *) pthread_getspecific(current_env)) != NULL) {
        goto done;
    }

    ret = (*g_jvm)->GetEnv(g_jvm, (void **) &env, JNI_VERSION_1_6);
    switch (ret) {
        case JNI_EDETACHED:
            if ((*g_jvm)->AttachCurrentThread(g_jvm, &env, NULL) != 0) {
                env = NULL;
            } else {
                pthread_setspecific(current_env, env);
            }
            break;
        case JNI_OK:
            break;
        case JNI_EVERSION:
            break;
        default:
            break;
    }
    done:
    pthread_mutex_unlock(&lock);
    return env;
}

void jniUtils_detachThreadEnv() {
    JavaVM *jvm = g_jvm;
    pthread_once(&once, jni_create_pthread_key);

    JNIEnv *env = (JNIEnv *) pthread_getspecific(current_env);
    if (!env)
        return;
    pthread_setspecific(current_env, NULL);

    if ((*jvm)->DetachCurrentThread(jvm) == JNI_OK)
        return;
}

void jniUtils_setJavaVm(JavaVM *jvm) {
    g_jvm = jvm;
}

JavaVM *jniUtils_getJavaVm() {
    return g_jvm;
}
