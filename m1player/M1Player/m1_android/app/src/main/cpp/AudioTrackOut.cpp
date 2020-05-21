//
// Created by chao on 2018/3/22.
//

#include "AudioTrackOut.h"

extern "C" {
#include "android_audiotrack.h"
#include "jni_utils.h"
}

#include <pthread.h>
#include <malloc.h>

class AudioTrackOutPrivate {
public:
    AudioTrackOutPrivate();

    ~AudioTrackOutPrivate();

    int aoutOpenAudio(const SDL_AudioSpec *desired, SDL_AudioSpec *obtained);

    void aoutPauseAudio(int pause_on);

    void aoutSetStereoVolume(float left_volume, float right_volume);

    void aoutCloseAudio(void);

    void aoutSetPlaybackRate(float playbackRate);

private:
    AndroidAudioTrack *mAndroidTrack;
    pthread_t mThreadAudio;
    bool mIsInitThread;
    bool mIsAbortRequest;
    bool mIsPause;
    SDL_AudioSpec mSpec;
    uint8_t* mBuffer;
private:
    static void* audioThreadFunc(void* opaque);
    void audioThread();
};

AudioTrackOutPrivate::AudioTrackOutPrivate() {
    mAndroidTrack = NULL;
    mIsInitThread = false;
    mBuffer = NULL;
    mIsAbortRequest = false;
    memset(&mBuffer, 0, sizeof(SDL_AudioSpec));
    mIsPause = false;
}

AudioTrackOutPrivate::~AudioTrackOutPrivate() {

}

void *AudioTrackOutPrivate::audioThreadFunc(void *opaque) {
    AudioTrackOutPrivate* mPrivate = static_cast<AudioTrackOutPrivate*>(opaque);
    mPrivate->audioThread();
    return NULL;
}

void AudioTrackOutPrivate::audioThread() {
    SDL_AudioCallback audio_cblk = mSpec.callback;
    void *userdata = mSpec.userdata;
    uint8_t *buffer = mBuffer;
    JNIEnv *env = jniUtils_setupThreadEnv();
    const int minBufferSize = androidAudioTrack_getMinBufferSize(mAndroidTrack);
    androidAudioTrack_play(env, mAndroidTrack);
    jniUtils_detachThreadEnv();
    while (!mIsAbortRequest) {
        if (mIsPause) {
            continue;
        }
        JNIEnv *env = jniUtils_setupThreadEnv();
        audio_cblk(userdata, buffer, minBufferSize);
        androidAudioTrack_write(env, mAndroidTrack, buffer, minBufferSize);
        jniUtils_detachThreadEnv();
    }
    env = jniUtils_setupThreadEnv();
    androidAudioTrack_flush(env, mAndroidTrack);
    androidAudioTrack_setStereoVolume(env, mAndroidTrack, 0.0f, 0.0f);
    androidAudioTrack_pause(env, mAndroidTrack);
    androidAudioTrack_stop(env, mAndroidTrack);
    androidAudioTrack_delete(env, mAndroidTrack);
    mAndroidTrack = NULL;
    jniUtils_detachThreadEnv();
}

int AudioTrackOutPrivate::aoutOpenAudio(const SDL_AudioSpec *desired, SDL_AudioSpec *obtained) {
    mSpec = *desired;
    JNIEnv *env = jniUtils_setupThreadEnv();
    Android_AudioTrack_Spec spec;
    spec.stream_type = STREAM_MUSIC;
    spec.sample_rate_in_hz = desired->freq;
    spec.channel_config = CHANNEL_OUT_MONO;
    spec.audio_format = ENCODING_PCM_16BIT;
    spec.mode = MODE_STREAM;
    mAndroidTrack = androidAudioTrack_new(env, &spec);
    const int size = androidAudioTrack_getMinBufferSize(mAndroidTrack);
    mBuffer = (uint8_t*)calloc(1, size);
    jniUtils_detachThreadEnv();
    if (mIsInitThread) {
        pthread_join(mThreadAudio, NULL);
    }
    pthread_create(&mThreadAudio, NULL, &audioThreadFunc, this);
    return 0;
}

void AudioTrackOutPrivate::aoutPauseAudio(int pause_on) {
    JNIEnv *env = jniUtils_setupThreadEnv();
    mIsPause = pause_on;
    if (pause_on) {
        androidAudioTrack_pause(env, mAndroidTrack);
    } else {
        androidAudioTrack_play(env, mAndroidTrack);
    }
    jniUtils_detachThreadEnv();
}

void AudioTrackOutPrivate::aoutSetStereoVolume(float left_volume, float right_volume) {
    JNIEnv *env = jniUtils_setupThreadEnv();
    androidAudioTrack_setStereoVolume(env, mAndroidTrack, left_volume, right_volume);
    jniUtils_detachThreadEnv();
}

void AudioTrackOutPrivate::aoutCloseAudio(void) {
    mIsAbortRequest = true;
}

void AudioTrackOutPrivate::aoutSetPlaybackRate(float playbackRate) {

}

AudioTrackOut::AudioTrackOut() {
    mPrivate = new AudioTrackOutPrivate;
}

AudioTrackOut::~AudioTrackOut() {
    if (mPrivate != NULL) {
        delete mPrivate;
    }
}

int AudioTrackOut::AoutOpenAudio(const SDL_AudioSpec *desired, SDL_AudioSpec *obtained) {
    return mPrivate->aoutOpenAudio(desired, obtained);
}

void AudioTrackOut::AoutPauseAudio(int pause_on) {
    mPrivate->aoutPauseAudio(pause_on);
}

void AudioTrackOut::AoutSetStereoVolume(float left_volume, float right_volume) {
    mPrivate->aoutSetStereoVolume(left_volume, right_volume);
}

void AudioTrackOut::AoutCloseAudio(void) {
    mPrivate->aoutCloseAudio();
}

void AudioTrackOut::AoutSetPlaybackRate(float playbackRate) {
    mPrivate->aoutSetPlaybackRate(playbackRate);
}
