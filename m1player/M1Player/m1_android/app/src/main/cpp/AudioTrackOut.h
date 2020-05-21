//
// Created by chao on 2018/3/22.
//

#ifndef M1_ANDROID_AUDIOTRACKOUT_H
#define M1_ANDROID_AUDIOTRACKOUT_H

#include "AudioOutBase.h"

class AudioTrackOutPrivate;

class AudioTrackOut : public IAudioOutBase {
public:
    AudioTrackOut();

    ~AudioTrackOut();

    int AoutOpenAudio(const SDL_AudioSpec *desired, SDL_AudioSpec *obtained) override;

    void AoutPauseAudio(int pause_on) override;

    void AoutSetStereoVolume(float left_volume, float right_volume) override;

    void AoutCloseAudio(void) override;

    void AoutSetPlaybackRate(float playbackRate) override;

private:
    AudioTrackOutPrivate *mPrivate;
};

#endif //M1_ANDROID_AUDIOTRACKOUT_H
