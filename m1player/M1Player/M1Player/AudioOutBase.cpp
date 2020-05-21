#include "AudioOutBase.h"

IAudioOutBase::IAudioOutBase()
{
	m_minimal_latency_seconds = 0.0;
}

IAudioOutBase::~IAudioOutBase()
{

}

int IAudioOutBase::AoutOpenAudio(const SDL_AudioSpec *desired, SDL_AudioSpec *obtained)
{
	return -1;
}

void IAudioOutBase::AoutPauseAudio(int pause_on)
{

}

void IAudioOutBase::AoutFlushAudio(void)
{

}

void IAudioOutBase::AoutSetStereoVolume(float left_volume, float right_volume)
{

}

void IAudioOutBase::AoutCloseAudio(void)
{

}

double IAudioOutBase::AoutGetLatencySeconds(void)
{
	return m_minimal_latency_seconds;
}

void IAudioOutBase::AoutSetDefaultLatencySeconds(double latency)
{
	m_minimal_latency_seconds = latency;
}

int IAudioOutBase::AoutGetAudioPerSecondCallBacks(void)
{
	return SDL_AUDIO_MAX_CALLBACKS_PER_SEC;
}

void IAudioOutBase::AoutSetPlaybackRate(float playbackRate)
{

}

int IAudioOutBase::AoutGetAudioSessionId(void)
{
	return 0;
}

SDL_AudioSpec* IAudioOutBase::AoutGetSpec(void)
{
	return NULL;
}
