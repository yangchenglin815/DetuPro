//
// Created by chao on 2018/3/21.
//

#include <malloc.h>
#include "android_audiotrack.h"
#include "android_byte_buffer.h"

#define ANDROID_AUDIO_TRACK_CLASS_PATH "android/media/AudioTrack"

struct AndroidAudioTrack {
    int minBufferSize;
    jobject jObjAudioTrack;
    jmethodID jMethodIdPlay;
    jmethodID jMethodIdPause;
    jmethodID jMethodIdStop;
    jmethodID jMethodIdRelease;
    jmethodID jMethodIdFlush;
    jmethodID jMethodIdWrite;
    jmethodID jMethodIdSetStereoVolume;
    jobject jArrayBuffer;
};

AndroidAudioTrack* androidAudioTrack_new(JNIEnv *env, Android_AudioTrack_Spec *spec) {
    AndroidAudioTrack *androidAudioTrack = (AndroidAudioTrack *) calloc(1, sizeof(AndroidAudioTrack));
    jclass jClassAudioTrack = (*env)->FindClass(env, ANDROID_AUDIO_TRACK_CLASS_PATH);
    {
        //获取minBufferSize
        jmethodID jMethodIdGetMinBufferSize = (*env)->GetStaticMethodID(env, jClassAudioTrack, "getMinBufferSize", "(III)I");
        androidAudioTrack->minBufferSize = (*env)->CallStaticIntMethod(env, jClassAudioTrack, jMethodIdGetMinBufferSize, spec->sample_rate_in_hz, spec->channel_config, spec->audio_format);
        jobject jArrayBuffer = (*env)->NewByteArray(env, androidAudioTrack->minBufferSize);
        androidAudioTrack->jArrayBuffer = (*env)->NewGlobalRef(env, jArrayBuffer);
    }
    {
        androidAudioTrack->jMethodIdPlay = (*env)->GetMethodID(env, jClassAudioTrack, "play", "()V");
        androidAudioTrack->jMethodIdPause = (*env)->GetMethodID(env, jClassAudioTrack, "pause", "()V");
        androidAudioTrack->jMethodIdStop = (*env)->GetMethodID(env, jClassAudioTrack, "stop", "()V");
        androidAudioTrack->jMethodIdFlush = (*env)->GetMethodID(env, jClassAudioTrack, "flush", "()V");
        androidAudioTrack->jMethodIdRelease = (*env)->GetMethodID(env, jClassAudioTrack, "release", "()V");
        androidAudioTrack->jMethodIdWrite = (*env)->GetMethodID(env, jClassAudioTrack, "write", "([BII)I");
        androidAudioTrack->jMethodIdSetStereoVolume = (*env)->GetMethodID(env, jClassAudioTrack, "setStereoVolume", "(FF)I");
    }
    {
        //AudioManager.STREAM_MUSIC, 16000, AudioFormat.CHANNEL_OUT_MONO, AudioFormat.ENCODING_PCM_16BIT, bufferSize, AudioTrack.MODE_STREAM);
        jmethodID jMethodIdInit = (*env)->GetMethodID(env, jClassAudioTrack, "<init>", "(IIIIII)V");
        jobject jObjAudioTrack = (*env)->NewObject(env, jClassAudioTrack,
                                                   jMethodIdInit, spec->stream_type,
                                                   spec->sample_rate_in_hz, spec->channel_config,
                                                   spec->audio_format, androidAudioTrack->minBufferSize, spec->mode);
        androidAudioTrack->jObjAudioTrack = (*env)->NewGlobalRef(env, jObjAudioTrack);
    }
    return androidAudioTrack;
}

void androidAudioTrack_delete(JNIEnv *env, AndroidAudioTrack *audioTrack) {
    if (audioTrack == NULL) {
        return;
    }
    (*env)->CallVoidMethod(env, audioTrack->jObjAudioTrack, audioTrack->jMethodIdRelease);
    (*env)->NewGlobalRef(env, audioTrack->jObjAudioTrack);
    free(audioTrack);
}

void androidAudioTrack_play(JNIEnv *env, AndroidAudioTrack *audioTrack) {
    if (audioTrack == NULL) {
        return;
    }
    (*env)->CallVoidMethod(env, audioTrack->jObjAudioTrack, audioTrack->jMethodIdPlay);
}

void androidAudioTrack_pause(JNIEnv *env, AndroidAudioTrack *audioTrack) {
    if (audioTrack == NULL) {
        return;
    }
    (*env)->CallVoidMethod(env, audioTrack->jObjAudioTrack, audioTrack->jMethodIdPause);
}

void androidAudioTrack_stop(JNIEnv *env, AndroidAudioTrack *audioTrack) {
    if (audioTrack == NULL) {
        return;
    }
    (*env)->CallVoidMethod(env, audioTrack->jObjAudioTrack, audioTrack->jMethodIdStop);
}

void androidAudioTrack_flush(JNIEnv *env, AndroidAudioTrack *atrack) {
    if (atrack == NULL) {
        return;
    }
    (*env)->CallVoidMethod(env, atrack->jObjAudioTrack, atrack->jMethodIdFlush);
}

int androidAudioTrack_write(JNIEnv *env, AndroidAudioTrack *atrack, uint8_t *data, int sizeInByte) {
    if (atrack == NULL) {
        return 0;
    }
    (*env)->SetByteArrayRegion(env, atrack->jArrayBuffer, 0, sizeInByte, data);
    return (*env)->CallIntMethod(env, atrack->jObjAudioTrack, atrack->jMethodIdWrite,
                                 atrack->jArrayBuffer, 0, sizeInByte);
}

int androidAudioTrack_setStereoVolume(JNIEnv *env, AndroidAudioTrack *atrack, float leftGain,
                                      float rightGain) {
    if (atrack == NULL) {
        return -1;
    }
    return (*env)->CallIntMethod(env, atrack->jObjAudioTrack, atrack->jMethodIdSetStereoVolume, leftGain, rightGain);
}

int androidAudioTrack_getMinBufferSize(AndroidAudioTrack *atrack) {
    return atrack->minBufferSize;
}
