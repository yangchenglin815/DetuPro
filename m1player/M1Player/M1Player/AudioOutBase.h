#ifndef _AUDIO_OUT_H_
#define _AUDIO_OUT_H_

//copy from ijkplayer, modify for m1

#include "AudioGlobal.h"
#include <pthread.h>

class IAudioOutBase
{
public:
	IAudioOutBase();
	virtual ~IAudioOutBase();

protected:
	pthread_mutex_t m_mutex;
	double			m_minimal_latency_seconds;

public:
	virtual int  AoutOpenAudio(const SDL_AudioSpec *desired, SDL_AudioSpec *obtained);
	virtual void AoutPauseAudio(int pause_on);
	virtual void AoutFlushAudio(void);
	virtual void AoutSetStereoVolume(float left_volume, float right_volume);
	virtual void AoutCloseAudio(void);

	virtual double AoutGetLatencySeconds(void);
	virtual void   AoutSetDefaultLatencySeconds(double latency);
	virtual int    AoutGetAudioPerSecondCallBacks(void);

	// optional
	virtual void   AoutSetPlaybackRate(float playbackRate);

	// android only
	virtual int    AoutGetAudioSessionId(void);

	virtual SDL_AudioSpec* AoutGetSpec(void);
};

#endif
