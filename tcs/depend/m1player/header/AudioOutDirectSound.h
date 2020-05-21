#ifndef _AUDIO_OUT_DIRECT_SOUND_H_
#define _AUDIO_OUT_DIRECT_SOUND_H_

//copy from ijkplayer, modify for m1

#include <mutex>
#include <memory>
#include <thread>
#include <condition_variable>

#include "AudioOutBase.h"
#include "AudioDisplayDirectSound.h"

class CAudioOutDirectSound: public IAudioOutBase
{
public:
	CAudioOutDirectSound();
	virtual ~CAudioOutDirectSound();

public:
	virtual int  AoutOpenAudio(const SDL_AudioSpec *desired, SDL_AudioSpec *obtained);
	virtual void AoutPauseAudio(int pause_on);
	virtual void AoutSetStereoVolume(float left_volume, float right_volume);
	virtual void AoutCloseAudio(void);
	virtual void AoutSetPlaybackRate(float playbackRate);

private:
	void audio_thread(void);

private:
	std::condition_variable	m_wakeup_cond;
	std::mutex				m_wakeup_mutex;

	SDL_AudioSpec	m_spec;
	uint8_t*		m_buffer;
	int				m_buffer_size;

	CAudioDisplayDirectSound* m_atrack;

	std::shared_ptr<std::thread> m_audio_thread;

	volatile bool m_need_flush;
	volatile bool m_pause_on;
	volatile bool m_abort_request;

	volatile bool  m_need_set_volume;
	volatile float m_right_volume;
	volatile float m_left_volume;
	volatile float m_speed;
	volatile bool  m_speed_changed;
};

#endif
