//
// Created by chao on 2018/3/21.
//

#ifndef M1_ANDROID_ANDROID_AUDIOTRACK_H
#define M1_ANDROID_ANDROID_AUDIOTRACK_H

#include <stdio.h>
#include <jni.h>

#define AUDIOTRACK_PLAYBACK_MAXSPEED (2)

typedef enum StreamType {
    STREAM_VOICE_CALL = 0,
    STREAM_SYSTEM = 1,
    STREAM_RING = 2,
    STREAM_MUSIC = 3,
    STREAM_ALARM = 4,
    STREAM_NOTIFICATION = 5,
} StreamType;

typedef enum ChannelConfig {
    CHANNEL_OUT_INVALID = 0x0,
    CHANNEL_OUT_DEFAULT = 0x1, /* f-l */
    CHANNEL_OUT_MONO = 0x4, /* f-l, f-r */
    CHANNEL_OUT_STEREO = 0xc, /* f-l, f-r, b-l, b-r */
    CHANNEL_OUT_QUAD = 0xcc, /* f-l, f-r, b-l, b-r */
    CHANNEL_OUT_SURROUND = 0x41c, /* f-l, f-r, f-c, b-c */
    CHANNEL_OUT_5POINT1 = 0xfc, /* f-l, f-r, b-l, b-r, f-c, low */
    CHANNEL_OUT_7POINT1 = 0x3fc, /* f-l, f-r, b-l, b-r, f-c, low, f-lc, f-rc */

    CHANNEL_OUT_FRONT_LEFT = 0x4,
    CHANNEL_OUT_FRONT_RIGHT = 0x8,
    CHANNEL_OUT_BACK_LEFT = 0x40,
    CHANNEL_OUT_BACK_RIGHT = 0x80,
    CHANNEL_OUT_FRONT_CENTER = 0x10,
    CHANNEL_OUT_LOW_FREQUENCY = 0x20,
    CHANNEL_OUT_FRONT_LEFT_OF_CENTER = 0x100,
    CHANNEL_OUT_FRONT_RIGHT_OF_CENTER = 0x200,
    CHANNEL_OUT_BACK_CENTER = 0x400,
} ChannelConfig;

typedef enum AudioFormat {
    ENCODING_INVALID = 0,
    ENCODING_DEFAULT = 1,
    ENCODING_PCM_16BIT = 2, // signed, guaranteed to be supported by devices.
    ENCODING_PCM_8BIT = 3, // unsigned, not guaranteed to be supported by devices.
    ENCODING_PCM_FLOAT = 4, // single-precision floating-point per sample
} AudioFormat;

typedef enum Mode {
    MODE_STATIC = 0,
    MODE_STREAM = 1,
} Mode;

typedef enum WriteMode {
    WRITE_BLOCKING = 0,
    WRITE_NON_BLOCKING = 1,
} WriteMode; // not used

typedef struct Android_AudioTrack_Spec {
    StreamType stream_type;
    int sample_rate_in_hz;
    ChannelConfig channel_config;
    AudioFormat audio_format;
    int buffer_size_in_bytes;
    Mode mode;
    WriteMode write_mode; // not used
    // extra field
    int sdl_samples;
} Android_AudioTrack_Spec;

struct AndroidAudioTrack;
typedef struct AndroidAudioTrack AndroidAudioTrack;

AndroidAudioTrack* androidAudioTrack_new(JNIEnv *env, Android_AudioTrack_Spec *spec);

void androidAudioTrack_play(JNIEnv *env, AndroidAudioTrack *audioTrack);

void androidAudioTrack_pause(JNIEnv *env, AndroidAudioTrack *audioTrack);

void androidAudioTrack_stop(JNIEnv *env, AndroidAudioTrack *audioTrack);

int androidAudioTrack_write(JNIEnv *env, AndroidAudioTrack *atrack, uint8_t *data, int sizeInByte);

void androidAudioTrack_flush(JNIEnv *env, AndroidAudioTrack *atrack);

int androidAudioTrack_getMinBufferSize(AndroidAudioTrack *atrack);

int androidAudioTrack_setStereoVolume(JNIEnv *env, AndroidAudioTrack *atrack, float leftGain, float rightGain);

void androidAudioTrack_delete(JNIEnv *env, AndroidAudioTrack *audioTrack);

#endif //M1_ANDROID_ANDROID_AUDIOTRACK_H
