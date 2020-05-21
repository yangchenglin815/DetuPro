#ifndef _M1_PLAYER_IMP_H_
#define _M1_PLAYER_IMP_H_
 
#include <memory>
#include <thread>
#include <stdio.h>
#include <stdlib.h>  
#include "Global.h"
#include "CircularQueue.h"
#include "LockingQueue.h"
#include "DataSource.h"
#include "H264DecoderBase.h"
#include "IGenerator.h"

#include "AudioOutBase.h"
#include "AudioDecoder.h"
#ifdef WIN32
#include <windows.h>
#include "AudioOutDirectSound.h"
#endif

extern "C"
{
#include "libswresample/swresample.h"
}

#define DEFAULT_DURATION 5.0
#define REFRESH_DURATION 0
#define SPEEDUP_DURATION 10
#define FFMIN(a,b) ((a) > (b) ? (b) : (a))
#define FFMAX(a,b) ((a) > (b) ? (a) : (b))

typedef CLockingQueue<SyncPacket*> sync_packet_lock_queue;

class CM1PlayerImp
{
public:
	CM1PlayerImp(bool is_audio_open);
	~CM1PlayerImp();

public:
	int Init(m1_player_config_s &config);
	int Play(void);
	int RePlay(void);
	int Close(void);

public:
	void SetStreamType(stream_type_e stream_type);
	void SetDeocdeType(decode_type_e deocde_type);
	void SetDisplayFps(int fps);
	void SetRecordTag(bool is_record);
	void SetRecordPath(char* path);
	void SetDisplayTag(bool is_display);
	void SetOnwer(long owner_id);
	void SetStatDuration(double sec);
	void setDecoderGenerator(IGenerator* decoderGenerator);
	void SetAudioVolume(int volume);
	void PauseAudio(bool pause_on);
	void VideoRefresh();

private:
	void func_sync_packet_callback(const SyncPacket *stream_packet);
	void func_message_callback(int message);

	int init_data_source();
	void sync_packet_copy(const SyncPacket *src, SyncPacket *dst);
	void free_sync_packet(SyncPacket* packet);
	void cleanup_cache_data(void);
	void video_refresh(m1_video_frame_s **frames, double *remaining_time);
	int  audio_open(void);

    AVPixelFormat getPixFmtByDecoderType(decode_type_e decoderType);

private:
	void handle_video_refresh(void);
	void handle_audio_decoder(void);
	void handle_video_decoder(int decoder_id);

private:
	static void sdl_audio_callback(void *opaque, Uint8 *stream, int len);
	void audio_callback_func(Uint8 *stream, int len);

private:
	CIDataSource*			m_data_source;
	IAudioOutBase*			m_audio_out;
	CAudioDecoder*			m_audio_decoder;
	SwrContext*				m_au_convert_ctx;
	unsigned char*			m_audio_buf;
	int						m_audio_out_buf_size;
	int						m_audio_out_buf_current_pos;
	H264DecoderBase*		m_h264_decoders[M1_VIDEO_NUM_PER_CHANNEL];
	re_circular_queue		m_frame_queues[M1_VIDEO_NUM_PER_CHANNEL];
	re_circular_queue		m_audio_frame_queue;
	sync_packet_lock_queue	m_sync_packet_queues[M1_VIDEO_NUM_PER_CHANNEL];
	sync_packet_lock_queue  m_audio_sync_packet_queues;
	m1_video_frame_s*		m_frame_list[M1_VIDEO_NUM_PER_CHANNEL];
private:
	bool							m_is_closed;
	std::shared_ptr<std::thread>	m_audio_decoder_thread;
	std::shared_ptr<std::thread>	m_video_refresh_thread;
	std::shared_ptr<std::thread>	m_video_decoder_threads[M1_VIDEO_NUM_PER_CHANNEL];

private:
	bool is_audio_open_;

	stream_type_e		m_stream_type;
	decode_type_e	    m_decode_type;

	double				m_display_fps;
	bool				m_is_record_local_file;
	bool				m_is_display_picture;
	bool				m_is_decoder_inited;
	bool				m_video_sync_tag;

	unsigned int		m_video_timestamp;
	double				m_last_refresh_time;
	double				m_last_sleep_time;
	int					m_video_width;
	int					m_video_heght;
	long				m_owner_id;
	int					m_packets_per_sec;
	double				m_start_time;
	double				m_statis_duration;
	std::string			m_record_path;

	m1_player_config_s	m_player_config;

#ifdef WIN32
    MMRESULT 			m_timer_id;
#endif

#ifdef AUDIO_CONFIG_FILE
	FILE*				m_g711a;			//g711a, 8000������,��������16λ�������
	FILE*				m_resample_output;
#endif
};

#endif
