#ifndef _AUDIO_DISPLAY_DIRECT_SOUND_H_
#define _AUDIO_DISPLAY_DIRECT_SOUND_H_

//copy from ijkplayer, modify for m1
//use directsound to display audio, need dsound.lib

#include <dsound.h>
#include "AudioGlobal.h"

typedef struct SDL_Win_DirectSound{
	LPDIRECTSOUND8 sound;//LPDIRECTSOUND sound;
	LPDIRECTSOUNDBUFFER mixbuf;
	LPDIRECTSOUNDCAPTURE capture;
	LPDIRECTSOUNDCAPTUREBUFFER capturebuf;
	int num_buffers;
	DWORD lastchunk;
	Uint8 *locked_buf;
}SDL_Win_DirectSound;

class CAudioDisplayDirectSound
{
public:
	CAudioDisplayDirectSound();
	~CAudioDisplayDirectSound();

private:
	int set_dsound_error(const char *function, int code);
	int create_secondary(const DWORD bufsize, WAVEFORMATEX *wfmt, Uint8 silence);

public:
	int  DSoundOpenDevice(SDL_AudioSpec *sdl_spec);
	void DSoundCloseDevice(void);
	void DSoundPlayDevice(SDL_AudioSpec *sdl_spec);
	void DSoundWaitDevice(SDL_AudioSpec *sdl_spec);
	void DSoundSetVolume(float left_volume, float right_volume);
	Uint8 * DSoundGetDeviceBuf(SDL_AudioSpec *sdl_spec);

private:
	SDL_Win_DirectSound*	m_directsound;
};

#endif
