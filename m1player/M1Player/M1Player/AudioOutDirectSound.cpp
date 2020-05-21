#include "AudioOutDirectSound.h"
#include "AudioGlobal.h"
#include "ijksdl_log.h"
#include <assert.h>

extern "C"{
#include "libavutil/time.h"
}

CAudioOutDirectSound::CAudioOutDirectSound()
{
	m_buffer = NULL;
	m_buffer_size = 0;
	m_atrack = NULL;

	m_need_flush = false;
	m_pause_on = false;
	m_abort_request = false;

	m_need_set_volume = false;
	m_right_volume = 0.0;
	m_left_volume = 0.0;
	m_speed = 1.0;
	m_speed_changed = false;

	memset(&m_spec, 0, sizeof(SDL_AudioSpec));
}

CAudioOutDirectSound::~CAudioOutDirectSound()
{
	if (m_buffer){
		free(m_buffer);
		m_buffer = NULL;
	}
	if (m_atrack){
		delete m_atrack;
	}
}

int CAudioOutDirectSound::AoutOpenAudio(const SDL_AudioSpec *desired, SDL_AudioSpec *obtained)
{
	assert(desired);

	m_spec = *desired;
	m_atrack = new CAudioDisplayDirectSound;
	if (!m_atrack) {
		ALOGE("AoutOpenAudio: failed to new AudioDisplayDirectSound");
		return -1;
	}

	int ret = m_atrack->DSoundOpenDevice(&m_spec);
	if (ret < 0) {
		delete m_atrack;
		m_atrack = NULL;
		return -1;
	}

	m_buffer_size = m_spec.size;
	m_buffer = (uint8_t*)malloc(m_buffer_size);
	if (!m_buffer) {
		ALOGE("AoutOpenAudio: failed to allocate buffer");
		delete m_atrack;
		m_atrack = NULL;
		return -1;
	}

	if (obtained) {
		obtained->freq = desired->freq;
		obtained->format = desired->format;
		obtained->channels = desired->channels;
		obtained->silence = desired->silence;
		obtained->samples = desired->samples;
		obtained->size = desired->size;
		obtained->callback = desired->callback;
		ALOGI("audio target format fmt:0x%x, channel:0x%x", (int)obtained->format, (int)obtained->channels);
	}

	m_pause_on = 0;
	m_abort_request = 0;

	if (m_audio_thread && m_audio_thread->joinable()){
		m_audio_thread->join();
	}
	m_audio_thread.reset(new std::thread(&CAudioOutDirectSound::audio_thread, this));

	return 0;
}

void CAudioOutDirectSound::AoutPauseAudio(int pause_on)
{
	std::lock_guard<std::mutex> lock(m_wakeup_mutex);
	m_pause_on = pause_on;
}

void CAudioOutDirectSound::AoutSetStereoVolume(float left_volume, float right_volume)
{
	std::lock_guard<std::mutex> lock(m_wakeup_mutex);
	m_left_volume  = left_volume;
	m_right_volume = right_volume;
	m_need_set_volume = 1;
}

void CAudioOutDirectSound::AoutCloseAudio(void)
{
	std::unique_lock<std::mutex> lock(m_wakeup_mutex);
	m_abort_request = true;
	lock.unlock();

	if (m_audio_thread && m_audio_thread->joinable()){
		m_audio_thread->join();
	}

	ALOGI("audio diaplay closed.");
}

void CAudioOutDirectSound::AoutSetPlaybackRate(float playbackRate)
{
	std::lock_guard<std::mutex> lock(m_wakeup_mutex);
	m_speed = playbackRate;
	m_speed_changed = 1;
}

void CAudioOutDirectSound::audio_thread(void)
{
	SDL_AudioCallback audio_cblk = m_spec.callback;
	void *userdata = m_spec.userdata;
	uint8_t *buffer = m_buffer;
	const Uint32 delay = ((m_spec.samples * 1000) / m_spec.freq);

	Uint8 *stream;
	const int stream_len = m_spec.size;

	assert(m_atrack);
	assert(buffer);

	if (!m_abort_request && !m_pause_on){
		m_atrack->DSoundPlayDevice(&m_spec);
	}

	while (!m_abort_request) {
		stream = m_atrack->DSoundGetDeviceBuf(&m_spec);
		if (stream == NULL){
			stream = buffer;
		}
		std::unique_lock<std::mutex> lock(m_wakeup_mutex);
		if (!m_abort_request) {
			audio_cblk(userdata, stream, stream_len);
			if (m_pause_on){
				memset(stream, 0, stream_len);
			} 
		}
		if (m_need_set_volume) {
			m_need_set_volume = 0;
			m_atrack->DSoundSetVolume(m_left_volume, m_right_volume);
		}
		lock.unlock();

		if (stream == buffer){
			av_usleep(delay*1000);
		} else {
			m_atrack->DSoundPlayDevice(&m_spec);
			m_atrack->DSoundWaitDevice(&m_spec);
		}
	}

	m_atrack->DSoundCloseDevice();
}
