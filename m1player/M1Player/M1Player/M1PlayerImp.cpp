#include "M1PlayerImp.h"
#include "PrivateSource.h"
#include "RtmpSource.h"
#include "MessageQueue.h"
#include "ijksdl_log.h"
#include "FfmpegH264Decoder.h"
#include "Error.h"

extern "C"
{
#include "libavutil/time.h"
#include "libavutil/common.h"
}

#ifdef _TIMESETEVENT
#undef _TIMESETEVENT
#endif


CM1PlayerImp::CM1PlayerImp(bool is_audio_open)
{
	m_is_closed = false;
	m_stream_type = StreamTypeRtmp;

#if defined(MAC_QT)
	m_decode_type = DecodeTypeVda;
#elif defined(__APPLE__)
	m_decode_type = DecodeTypeVtb;
#elif defined(_WIN32)
	m_decode_type = DecodeTypeSoft;
#elif defined(_WIN64)
	m_decode_type = DecodeTypeSoft;
#else
	m_decode_type = DecodeTypeMediaCodec;
#endif

	m_display_fps = 33.0;
	m_is_record_local_file = false;
	m_is_display_picture = true;
	m_is_decoder_inited = false;
	m_video_sync_tag = false;

	m_video_timestamp = 0;
	m_last_refresh_time = 0.0;
	m_last_sleep_time = 0.0;
	m_video_width = 0;
	m_video_heght = 0;
	m_owner_id = 0;
	m_packets_per_sec = 0;
	m_start_time = 0.0;
	m_statis_duration = DEFAULT_DURATION;
#ifdef WIN32
	m_timer_id = 0;
#endif

	m_data_source = NULL;

#ifdef WIN32
	m_audio_out = NULL;
	m_audio_decoder = NULL;
	m_au_convert_ctx = NULL;
	m_audio_buf = NULL;
	is_audio_open_ = is_audio_open;
#endif

#ifdef AUDIO_CONFIG_FILE
	m_g711a = fopen("g711a", "wb+");
	m_resample_output = fopen("resample_output", "wb+");
#endif

	for (int i = 0; i < M1_VIDEO_NUM_PER_CHANNEL; i++) {
		m_h264_decoders[i] = NULL;
		memset(&m_frame_queues[i], 0, sizeof(struct re_circular_queue));
	}
	memset(&m_audio_frame_queue, 0, sizeof(struct re_circular_queue));
}

CM1PlayerImp::~CM1PlayerImp() {
}

int CM1PlayerImp::Init(m1_player_config_s &config)
{
	av_register_all();

	m_player_config = config;

	for (int i = 0; i < M1_VIDEO_NUM_PER_CHANNEL; i++){
		m_frame_list[i] = (m1_video_frame_s*)malloc(sizeof(m1_video_frame_s));
	}

	for (int i = 0; i < M1_VIDEO_NUM_PER_CHANNEL; i++) {
		re_circular_queue_init(&m_frame_queues[i]);
	}
	re_circular_queue_init(&m_audio_frame_queue);

	int ret = init_data_source();
	if (ret != 0) {
		ALOGE("init data source error.");
		return ret;
	}

	m_audio_decoder = new CAudioDecoder;
	ret = m_audio_decoder->InitDecoder();
	if (ret != 0){
		ALOGE("audio decoder init error.");
		return ret;
	}
	if (is_audio_open_)
	{
		m_audio_out = new CAudioOutDirectSound();
		audio_open();
	}

	ALOGE("m1 player init success.");
	return 0;
}

void CM1PlayerImp::setDecoderGenerator(IGenerator *decoderGenerator) {
}

void CM1PlayerImp::SetAudioVolume(int volume)
{
	if (m_audio_out != NULL){
		m_audio_out->AoutSetStereoVolume(volume, volume);
	}
}

void CM1PlayerImp::PauseAudio(bool pause_on)
{
	if (m_audio_out != NULL){
		m_audio_out->AoutPauseAudio(pause_on);
	}
}

#if defined(_TIMESETEVENT)
void CM1PlayerImp::VideoRefresh()
{
	double diff = 0.0;
	double time = av_gettime_relative() / 1000000.0;

	if (m_last_refresh_time) {
		diff = (double)(time - m_last_refresh_time) * 1000 - m_last_sleep_time;
	}

	int frame_sum = 0;
	for (int i = 0; i < M1_VIDEO_NUM_PER_CHANNEL; i++) {
		if (re_circular_queue_size(&m_frame_queues[i]) > 0) {
			frame_sum += 1;
		}
	}

	int decode_sum = 0;
	if (frame_sum == M1_VIDEO_NUM_PER_CHANNEL) {
		for (int i = 0; i < M1_VIDEO_NUM_PER_CHANNEL; i++) {
			Frame* frame = re_circular_queue_peek_read(&m_frame_queues[i]);
			for (int j = 0; j < k_NUM_DATA_POINTERS; j++){
				m_frame_list[i]->data[j] = frame->frame->data[j];
				m_frame_list[i]->linesize[j] = frame->frame->linesize[j];
			}
			m_frame_list[i]->fps = m_h264_decoders[i]->GetVfps();
			m_frame_list[i]->bitrate = m_h264_decoders[i]->GetVbitrate();
			m_frame_list[i]->h = frame->frame->height;
			m_frame_list[i]->w = frame->frame->width;
			m_frame_list[i]->opaque = frame->frame->opaque;
			if (frame->frame->format == AV_PIX_FMT_YUV420P){
				m_frame_list[i]->format = PIX_FMT_YUV420P;
				m_frame_list[i]->planes = 3;
				m_frame_list[i]->opaque = NULL;
			}
			else if (frame->frame->format == AV_PIX_FMT_NV12){
				m_frame_list[i]->format = PIX_FMT_NV12;
				m_frame_list[i]->planes = 2;
			}
			else if (frame->frame->format == AV_PIX_FMT_VIDEOTOOLBOX) {
				m_frame_list[i]->format = PIX_FMT_VIDEOTOOLBOX;
				m_frame_list[i]->planes = 2;
			}
			else if (frame->frame->format == AV_PIX_FMT_MEDIACODEC) {
				m_frame_list[i]->format = PIX_FMT_MEDIACODEC;
				m_frame_list[i]->planes = 1;
			}

			if (frame->decode_successd) {
				decode_sum += 1;
			}
		}

		if ((m_player_config.videoproc != nullptr) && (decode_sum == M1_VIDEO_NUM_PER_CHANNEL)) {
			m_player_config.videoproc(m_frame_list, 1, m_video_timestamp);
			AVFrame tempFrame = { 0 };
			for (int i = 0; i < M1_VIDEO_NUM_PER_CHANNEL; i++){
				const int planes = m_frame_list[i]->planes;
				for (int j = 0; j < planes; j++) {
					tempFrame.data[j] = m_frame_list[i]->data[j];
					tempFrame.linesize[j] = m_frame_list[i]->linesize[j];
				}
				tempFrame.opaque = m_frame_list[i]->opaque;
				m_h264_decoders[i]->unRefFrame(&tempFrame);
			}
		}
		for (int i = 0; i < M1_VIDEO_NUM_PER_CHANNEL; i++) {
			re_circular_queue_advance_read(&m_frame_queues[i]);
		}
	}

	double time2 = av_gettime_relative() / 1000000.0;
	double exec_time = (double)(time2 - time) * 1000;

	m_last_refresh_time = time2;

	//ALOGI("exec time:%f, time diff:%f", exec_time, diff);
}

void CALLBACK timeEvent(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
	CM1PlayerImp* imp = (CM1PlayerImp*)dwUser;
	imp->VideoRefresh();
}
#endif

int CM1PlayerImp::Play(void)
{
	if (m_data_source) {
		m_data_source->SetStreamSavePath(m_record_path);
		m_data_source->SetStreamSaveTag(m_is_record_local_file);
		m_data_source->StartRecv();
	}

#if defined(_TIMESETEVENT)
	m_timer_id = timeSetEvent((UINT)(1000 / m_display_fps) - 1, 1, (LPTIMECALLBACK)timeEvent, (DWORD)this, TIME_PERIODIC);
	if(m_timer_id == 0){
		Log::Error("timer event create failed, timer id:%d", m_timer_id);
		return -1;
	} else {
		m_last_sleep_time = 1000/m_display_fps -1;
		Log::Info("refresh timer interval:%d", (int)m_last_sleep_time);
	}
#else
	if (m_video_refresh_thread && m_video_refresh_thread->joinable()) {
		m_video_refresh_thread->join();
	}
	m_video_refresh_thread.reset(new std::thread(&CM1PlayerImp::handle_video_refresh, this));
#endif

	if (m_audio_decoder_thread && m_audio_decoder_thread->joinable()){
		m_audio_decoder_thread->join();
	}
	m_audio_decoder_thread.reset(new std::thread(&CM1PlayerImp::handle_audio_decoder, this));

	for (int i = 0; i < M1_VIDEO_NUM_PER_CHANNEL; i++) {
		if (m_video_decoder_threads[i] && m_video_decoder_threads[i]->joinable()) {
			m_video_decoder_threads[i]->join();
		}
		m_video_decoder_threads[i].reset(new std::thread(&CM1PlayerImp::handle_video_decoder, this, i));
	}

	return 0;
}

int CM1PlayerImp::RePlay(void)
{
	if (m_data_source) {
		m_data_source->CloseSource();
	}

	int ret = init_data_source();
	if (ret != 0) {
		ALOGE("init data source error.");
		return ret;
	}
	if (m_data_source) {
		m_data_source->SetStreamSavePath(m_record_path);
		m_data_source->SetStreamSaveTag(m_is_record_local_file);
		m_data_source->StartRecv();
	}

	ALOGI("datasource restart success.");
	return 0;
}

int CM1PlayerImp::Close(void)
{
	ALOGE("close m1 player now.");

	if (!m_is_closed) {

		if (m_data_source) {
			m_data_source->CloseSource();
		}

		for (int i = 0; i < M1_VIDEO_NUM_PER_CHANNEL; i++) {
			re_circular_queue_abort(&m_frame_queues[i]);
		}
		re_circular_queue_abort(&m_audio_frame_queue);

		if (m_audio_decoder_thread && m_audio_decoder_thread->joinable()){
			m_audio_decoder_thread->join();
		}
		for (int i = 0; i < M1_VIDEO_NUM_PER_CHANNEL; i++) {
			if (m_video_decoder_threads[i] && m_video_decoder_threads[i]->joinable()) {
				m_video_decoder_threads[i]->join();
			}
		}

		m_is_closed = true;

		av_usleep(500000);

#if defined(_TIMESETEVENT)
		timeKillEvent(m_timer_id);
#else
		if (m_video_refresh_thread && m_video_refresh_thread->joinable()) {
			m_video_refresh_thread->join();
		}
#endif

		for (int i = 0; i < M1_VIDEO_NUM_PER_CHANNEL; i++) {
			if (m_h264_decoders[i]) {
				m_h264_decoders[i]->CloseDecoder();
			}

			free(m_frame_list[i]);

			SyncPacket* packet = NULL;
			while (m_sync_packet_queues[i].size() > 0) {
				packet = m_sync_packet_queues[i].pop();
				free_sync_packet(packet);
			}

			re_circular_queue_free(&m_frame_queues[i]);
		}

		if (m_audio_out){
			m_audio_out->AoutCloseAudio();
			delete m_audio_out;
		}
		if (m_audio_decoder){
			m_audio_decoder->CloseDecoder();
			delete m_audio_decoder;
		}
//		if (m_au_convert_ctx){
//			swr_free(&m_au_convert_ctx);
//		}
		if (m_audio_buf){
			av_free(m_audio_buf);
			m_audio_buf = NULL;
		}
		SyncPacket* packet = NULL;
		while (m_audio_sync_packet_queues.size() > 0) {
			packet = m_audio_sync_packet_queues.pop();
			free_sync_packet(packet);
		}
		re_circular_queue_free(&m_audio_frame_queue);
	}

#ifdef AUDIO_CONFIG_FILE
	if (m_g711a){
		fclose(m_g711a);
		m_g711a = NULL;
	}
	if (m_resample_output){
		fclose(m_resample_output);
		m_resample_output = NULL;
	}
#endif

	ALOGE("m1 player closed.");
	return 0;
}

void CM1PlayerImp::SetStreamType(stream_type_e stream_type)
{
	m_stream_type = stream_type;
	ALOGE("set stream type success, stream type: %d", m_stream_type);
}

void CM1PlayerImp::SetDeocdeType(decode_type_e deocde_type)
{
	m_decode_type = deocde_type;
	ALOGE("set decode type success, decode type: %d", m_decode_type);
}

void CM1PlayerImp::SetDisplayFps(int fps)
{
	m_display_fps = (double)fps;
	ALOGE("set display fps success, display fps: %d", fps);
}

void CM1PlayerImp::SetRecordTag(bool is_record)
{
	m_is_record_local_file = is_record;
	if (m_data_source) {
		m_data_source->SetStreamSaveTag(m_is_record_local_file);
	}
	ALOGE("set record tag success: %s", m_is_record_local_file ? "record local file" : "not record");
}

void CM1PlayerImp::SetRecordPath(char* path)
{
	m_record_path = path;
	if (m_data_source) {
		m_data_source->SetStreamSavePath(path);
	}
	ALOGE("set record path success: %s",path);
}

void CM1PlayerImp::SetDisplayTag(bool is_display)
{
	m_is_display_picture = is_display;
	ALOGE("set display tag success: %s", m_is_display_picture ? "display picture" : "not display picture");
}

void CM1PlayerImp::SetOnwer(long owner_id)
{
	m_owner_id = owner_id;
	ALOGE("set signal id success, signal id: %ld", owner_id);
}

void CM1PlayerImp::SetStatDuration(double sec)
{
	m_statis_duration = sec;
}

void CM1PlayerImp::func_sync_packet_callback(const SyncPacket *stream_packet)
{
	if (stream_packet->codec_type == AVMEDIA_TYPE_VIDEO){
		//init decoder for first time
		if (!m_is_decoder_inited) {
			m_is_decoder_inited = true;
			m_video_heght = stream_packet->video_h;
			m_video_width = stream_packet->video_w;

			SpsPpsInfo spsPpsInfo;
			memset(&spsPpsInfo, 0, sizeof(SpsPpsInfo));
			m_data_source->getSpsPpsInfo(&spsPpsInfo);			
			for (int i = 0; i < M1_VIDEO_NUM_PER_CHANNEL; i++) {
				H264DecoderType h264DecoderType = static_cast<H264DecoderType>(m_decode_type);
				m_h264_decoders[i] = new FfmpegH264Decoder();
				m_h264_decoders[i]->SetDecodeType(h264DecoderType);
				m_h264_decoders[i]->InitDecoder(i, spsPpsInfo.spsPpsData, spsPpsInfo.length,
					m_video_width, m_video_heght);
			}
			m_start_time = av_gettime_relative() / 1000000.0;
		}

		m_packets_per_sec++;

		if ((av_gettime_relative() / 1000000.0 - m_start_time) > m_statis_duration) {
			m_start_time = av_gettime_relative() / 1000000.0;
			m_display_fps = m_packets_per_sec / (M1_VIDEO_NUM_PER_CHANNEL * m_statis_duration) + m_sync_packet_queues[0].size() / SPEEDUP_DURATION;
			ALOGI("packets per five secs: %d, fps:%f, p1:%d, p2:%d, p3:%d, p4:%d, f1:%d, f2 : %d, f3 : %d, f4 : %d",
				m_packets_per_sec, m_display_fps, m_sync_packet_queues[0].size(), m_sync_packet_queues[1].size(), m_sync_packet_queues[2].size(), m_sync_packet_queues[3].size(),
				re_circular_queue_size(&m_frame_queues[0]), re_circular_queue_size(&m_frame_queues[1]), re_circular_queue_size(&m_frame_queues[2]), re_circular_queue_size(&m_frame_queues[3]));
			m_packets_per_sec = 0;
		}

		//clean up cache data when coming packet out of sync
		if (stream_packet->is_sync != m_video_sync_tag) {
			m_video_sync_tag = stream_packet->is_sync;
			if (!m_video_sync_tag) {
				cleanup_cache_data();
			}
		}
	}

	//get sync packet
	SyncPacket* sync_packet = (SyncPacket*)malloc(sizeof(SyncPacket));
	memset(sync_packet, 0, sizeof(SyncPacket));
	av_new_packet(&(sync_packet->av_packet), stream_packet->av_packet.size);
	sync_packet_copy(stream_packet, sync_packet);

	if (stream_packet->codec_type == AVMEDIA_TYPE_VIDEO){
		//push in locking queue
		m_sync_packet_queues[sync_packet->came_seq].enqueue(sync_packet);
	} else if (stream_packet->codec_type == AVMEDIA_TYPE_AUDIO){

		m_audio_sync_packet_queues.enqueue(sync_packet);

		//g711 data ok
#ifdef AUDIO_CONFIG_FILE
		fwrite(sync_packet->av_packet.data, 1, sync_packet->av_packet.size, m_g711a);
		fflush(m_g711a);
#endif
	}

	return;
}

void CM1PlayerImp::func_message_callback(int message)
{
	if (m_owner_id != 0){
		CMessageQueue::GetInstance().Notify(m_owner_id, message, 0);
	}

	if (m_player_config.messageproc != nullptr){
		m_player_config.messageproc(message, 0);
	}
}

int CM1PlayerImp::init_data_source()
{
	if (m_stream_type == StreamTypeRtmp) {
		m_data_source = new CRtmpSource;
	}
	else if (m_stream_type == StreamTypePrivate) {
		m_data_source = new CPrivateSource;
	}
	else {
		ALOGE("Unknow stream type:%d.", m_stream_type);
		return ERROR_STREAM_TYPE_UNKNOW;
	}
	if (m_data_source) {
		m_data_source->SetPacketCallback(std::bind(&CM1PlayerImp::func_sync_packet_callback, this, std::placeholders::_1));
		m_data_source->SetMsgCallback(std::bind(&CM1PlayerImp::func_message_callback, this, std::placeholders::_1));
		int ret = m_data_source->InitSource(m_player_config.url);
		if (ret != 0) {
			ALOGE("connect server error, error code:%d", ret);
			return ret;
		}
		ret = m_data_source->HandShake();
		if (ret != 0) {
			ALOGE("handshake with server error, error code:%d", ret);
			return ret;
		}
	}
	return 0;
}

void CM1PlayerImp::sync_packet_copy(const SyncPacket *src, SyncPacket *dst)
{
	dst->is_sync = src->is_sync;
	dst->sync_seq = src->sync_seq;
	dst->timestamp = src->timestamp;
	dst->pts = src->pts;
	dst->video_h = src->video_h;
	dst->video_w = src->video_w;
	dst->came_seq = src->came_seq;
	dst->codec_type = src->codec_type;
	dst->av_packet.size = src->av_packet.size;
	dst->av_packet.flags = src->av_packet.flags;
	memcpy(dst->av_packet.data, src->av_packet.data, dst->av_packet.size);
}

void CM1PlayerImp::free_sync_packet(SyncPacket* packet)
{
	if (packet) {
		av_packet_unref(&(packet->av_packet));
		free(packet);
	}
	return;
}

void CM1PlayerImp::cleanup_cache_data(void)
{
	for (int i = 0; i < M1_VIDEO_NUM_PER_CHANNEL; i++) {
		SyncPacket* packet = NULL;
		while (m_sync_packet_queues[i].size() > 0) {
			packet = m_sync_packet_queues[i].pop();
			free_sync_packet(packet);
		}

		re_circular_queue_reset(&m_frame_queues[i]);
	}

	ALOGE("packet out of sync, clean up cache souce");
}

void CM1PlayerImp::video_refresh(m1_video_frame_s **frames, double *remaining_time)
{
	double diff = 0.0;
	double time = av_gettime_relative() / 1000000.0;

	if (m_last_refresh_time) {
		diff = (double)(time - m_last_refresh_time) * 1000 - m_last_sleep_time;
	}

	int frame_sum = 0;
	for (int i = 0; i < M1_VIDEO_NUM_PER_CHANNEL; i++) {
		if (re_circular_queue_size(&m_frame_queues[i]) > 0) {
			frame_sum += 1;
		}
	}

	int decode_sum = 0;
	if (frame_sum == M1_VIDEO_NUM_PER_CHANNEL) {
		for (int i = 0; i < M1_VIDEO_NUM_PER_CHANNEL; i++) {
			Frame* frame = re_circular_queue_peek_read(&m_frame_queues[i]);
			for (int j = 0; j < k_NUM_DATA_POINTERS; j++){
				frames[i]->data[j] = frame->frame->data[j];
				frames[i]->linesize[j] = frame->frame->linesize[j];
			}
			frames[i]->fps = m_h264_decoders[i]->GetVfps();
			frames[i]->bitrate = m_h264_decoders[i]->GetVbitrate();
			frames[i]->h = frame->frame->height;
			frames[i]->w = frame->frame->width;
            frames[i]->opaque = frame->frame->opaque;
			if (frame->frame->format == AV_PIX_FMT_YUV420P){
				frames[i]->format = PIX_FMT_YUV420P;
                frames[i]->planes = 3;
                frames[i]->opaque = NULL;
			}
			else if (frame->frame->format == AV_PIX_FMT_NV12){
				frames[i]->format = PIX_FMT_NV12;
                frames[i]->planes = 2;
            } else if(frame->frame->format == AV_PIX_FMT_VIDEOTOOLBOX) {
                frames[i]->format = PIX_FMT_VIDEOTOOLBOX;
                frames[i]->planes = 2;
            } else if(frame->frame->format == AV_PIX_FMT_MEDIACODEC) {
			    frames[i]->format = PIX_FMT_MEDIACODEC;
			    frames[i]->planes = 1;
			}

			if (frame->decode_successd) {
				decode_sum += 1;
			}
		}

		if ((m_player_config.videoproc != nullptr) && (decode_sum == M1_VIDEO_NUM_PER_CHANNEL)) {
			m_player_config.videoproc(frames, 1, m_video_timestamp);
			AVFrame tempFrame = {0};
            for(int i = 0; i < M1_VIDEO_NUM_PER_CHANNEL; i++){
                const int planes = frames[i]->planes;
                for(int j = 0; j < planes; j++) {
                    tempFrame.data[j] = frames[i]->data[j];
                    tempFrame.linesize[j] = frames[i]->linesize[j];
                }
                tempFrame.opaque = frames[i]->opaque;
                m_h264_decoders[i]->unRefFrame(&tempFrame);
            }
		}
		for (int i = 0; i < M1_VIDEO_NUM_PER_CHANNEL; i++) {
			re_circular_queue_advance_read(&m_frame_queues[i]);
		}
	}
	double time2 = av_gettime_relative() / 1000000.0;
	double exec_time = (double)(time2 - time) * 1000;

	if (1000 / m_display_fps > (diff + exec_time)){
		*remaining_time = 1000 / m_display_fps - diff - exec_time;
	}

	m_last_refresh_time = time2;
	m_last_sleep_time = *remaining_time;

	//ALOGI("sleep time:%f, exec time:%f, time diff:%f, fps:%f", *remaining_time, exec_time, diff, m_display_fps);
}

int CM1PlayerImp::audio_open(void)
{
	SDL_AudioSpec wanted_spec, spec;

	int wanted_channel_layout = AV_CH_LAYOUT_STEREO;
	int wanted_nb_channels = av_get_channel_layout_nb_channels(wanted_channel_layout);
	int wanted_sample_rate = 44100;

	wanted_spec.channels = 1;//wanted_nb_channels;
	wanted_spec.freq = 8000;//wanted_sample_rate;
	if (wanted_spec.freq <= 0 || wanted_spec.channels <= 0) {
		ALOGE("invalid sample rate or channel count!");
		return -1;
	}
	wanted_spec.format = AUDIO_S16SYS;
	wanted_spec.silence = 0;
	wanted_spec.samples = 800;//FFMAX(SDL_AUDIO_MIN_BUFFER_SIZE, 2 << av_log2(wanted_spec.freq / m_audio_out->AoutGetAudioPerSecondCallBacks()));
	wanted_spec.callback = sdl_audio_callback;
	wanted_spec.userdata = (void*)this;

	m_audio_buf = (uint8_t *)av_malloc(MAX_AUDIO_FRAME_SIZE * 2);
	m_audio_out_buf_size = av_samples_get_buffer_size(NULL, wanted_nb_channels, 1024, AV_SAMPLE_FMT_S16, 1);
	m_audio_out_buf_current_pos = m_audio_out_buf_size;

	if(m_audio_out->AoutOpenAudio(&wanted_spec, &spec) < 0) {
		ALOGE("audio open failed, AoutOpenAudio (%d channels, %d Hz)", wanted_spec.channels, wanted_spec.freq);
		return -1;
	}
	if (spec.format != AUDIO_S16SYS) {
		ALOGE("advised audio format %d is not supported!\n", spec.format);
		return -1;
	}
	if (spec.channels != wanted_spec.channels) {
		wanted_channel_layout = av_get_default_channel_layout(spec.channels);
		if (!wanted_channel_layout) {
			ALOGE("advised channel count %d is not supported!\n", spec.channels);
			return -1;
		}
	}

	int frame_size = av_samples_get_buffer_size(NULL, spec.channels, 1, AV_SAMPLE_FMT_S16, 1);
	int bytes_per_sec = av_samples_get_buffer_size(NULL, spec.channels, spec.freq, AV_SAMPLE_FMT_S16, 1);
	if (bytes_per_sec <= 0 || frame_size <= 0) {
		ALOGE("av_samples_get_buffer_size failed.");
		return -1;
	}

	m_audio_out->AoutSetDefaultLatencySeconds(((double)(2 * spec.size)) / bytes_per_sec);

	m_audio_out->AoutPauseAudio(0);

	//init audio resample ctx
//	m_au_convert_ctx = swr_alloc();
//	m_au_convert_ctx = swr_alloc_set_opts(m_au_convert_ctx, AV_CH_LAYOUT_STEREO, AV_SAMPLE_FMT_S16, 44100,
//		DEFAULT_AUDIO_CHANNEL_LAYOUT, DEFAULT_AUDIO_SAMPLE_FORMAT, DEFAULT_AUDIO_SAMPLE_RATE, 0, NULL);
//	swr_init(m_au_convert_ctx);
	return 0;
}

void CM1PlayerImp::handle_video_refresh(void)
{
	double remaining_time = 0.0;

	while (true){
		if (m_is_closed) {
			break;
		}

		if (remaining_time > 0.0){
			av_usleep((int)(int64_t)(remaining_time * 1000.0));
		}
		remaining_time = REFRESH_DURATION;
		video_refresh(m_frame_list, &remaining_time);
	}

	ALOGE("video refresh thread stop now.");
}

AVPixelFormat CM1PlayerImp::getPixFmtByDecoderType(decode_type_e decoderType) {
    AVPixelFormat pixFmt = AV_PIX_FMT_YUV420P;
    switch (decoderType) {
        case DecodeTypeVda:
            pixFmt = AV_PIX_FMT_VDA;
            break;
        case DecodeTypeIntel:
        case DecodeTypeCuda:
            pixFmt = AV_PIX_FMT_NV12;
            break;
        case DecodeTypeVtb:
            pixFmt = AV_PIX_FMT_VIDEOTOOLBOX;
            break;
        case DecodeTypeMediaCodec:
            pixFmt = AV_PIX_FMT_MEDIACODEC;
            break;
        default:
            break;
    }
    return pixFmt;
}

void CM1PlayerImp::handle_video_decoder(int decoder_id)
{
	while (true) {
		if (m_is_closed) {
			break;
		}

		int ret = re_circular_queue_wait_write(&m_frame_queues[decoder_id]);
		if (ret) {
			ALOGE("decode thread abort, decoder id: %d", decoder_id);
			break;
		}

		if (m_sync_packet_queues[decoder_id].size() == 0) {
			continue;
		}

		SyncPacket *packet = NULL;
		if (m_sync_packet_queues[decoder_id].wait_dequeue(packet)) {
			if (m_is_display_picture == false) {
				free_sync_packet(packet);
				av_usleep(10*1000);
				continue;
			}

			Frame* frame = re_circular_queue_peek_write(&m_frame_queues[decoder_id]);
			if (frame->err_code != OK) {
				break;
			}

			int got_picture = 1;
			int ret = m_h264_decoders[decoder_id]->DecodeVideo(frame->frame, &got_picture, &(packet->av_packet));
			if (got_picture) {
				frame->pts = packet->pts;
				frame->decode_successd = true;
				frame->frame->width = m_video_width;
				frame->frame->height = m_video_heght;
                frame->frame->format = getPixFmtByDecoderType(m_decode_type);

				if (packet->is_sync) {
					re_circular_queue_advance_write(&m_frame_queues[decoder_id]);
                } else {
                    m_h264_decoders[decoder_id]->unRefFrame(frame->frame);
                }
				m_video_timestamp = packet->timestamp / 1000000;
			} else {
				frame->pts = packet->pts;
				frame->decode_successd = false;
				ALOGE("decode error, decoder id:%d", decoder_id);
				frame->frame->format = getPixFmtByDecoderType(m_decode_type);

				if (packet->is_sync) {
					re_circular_queue_advance_write(&m_frame_queues[decoder_id]);
				}
			}
		}

		if (packet) {
			free_sync_packet(packet);
		}
	}

	ALOGE("video decode threads stop now, decoder id:%d", decoder_id);
}

void CM1PlayerImp::handle_audio_decoder(void)
{
	while (true) {
		if (m_is_closed) {
			break;
		}

		int ret = re_circular_queue_wait_write(&m_audio_frame_queue);
		if (ret) {
			ALOGE("audio decode thread abort");
			break;
		}

		if (m_audio_sync_packet_queues.size() == 0) {
			continue;
		}

		SyncPacket *packet = NULL;
		if (m_audio_sync_packet_queues.wait_dequeue(packet)) {
			if (m_is_display_picture == false) {
				free_sync_packet(packet);
				av_usleep(10 * 1000);
				continue;
			}

			Frame* frame = re_circular_queue_peek_write(&m_audio_frame_queue);
			if (frame->err_code != OK) {
				break;
			}

			int got_picture = 1;
			int ret = m_audio_decoder->DecodeAudio(frame->frame, &got_picture, &(packet->av_packet));
			if (got_picture) {
				frame->decode_successd = true;
				if (packet->is_sync) {
					re_circular_queue_advance_write(&m_audio_frame_queue);
				}
			}
			else {
				frame->decode_successd = false;
				ALOGE("audio decode error");

				if (packet->is_sync) {
					re_circular_queue_advance_write(&m_audio_frame_queue);
				}
			}
		}

		if (packet) {
			free_sync_packet(packet);
		}
	}
	ALOGI("audio decode threads stop now");
}

void CM1PlayerImp::sdl_audio_callback(void *opaque, Uint8 *stream, int len)
{
	CM1PlayerImp* imp = (CM1PlayerImp*)opaque;
	if (imp){
		imp->audio_callback_func(stream, len);
	}
}

void CM1PlayerImp::audio_callback_func(Uint8 *stream, int len)
{
	int len1 = 0;
	while (len > 0) {
		if (m_is_closed) {
			break;
		}

		if (m_audio_out_buf_current_pos >= m_audio_out_buf_size){
			if (re_circular_queue_size(&m_audio_frame_queue) <= 0){
				continue;
			}

			Frame* frame = re_circular_queue_peek_read(&m_audio_frame_queue);
			if (!frame->decode_successd){
				continue;
			}

			//swr_convert(m_au_convert_ctx, &m_audio_buf, MAX_AUDIO_FRAME_SIZE, (const uint8_t **)frame->frame->data, frame->frame->nb_samples);

			m_audio_out_buf_size = frame->frame->linesize[0];
			memcpy(m_audio_buf, frame->frame->data[0], m_audio_out_buf_size);

			m_audio_out_buf_current_pos = 0;

#ifdef AUDIO_CONFIG_FILE
			//resample pcm audio data
			fwrite(m_audio_buf, 1, m_audio_out_buf_size, m_resample_output);
			fflush(m_resample_output);
#endif
			re_circular_queue_advance_read(&m_audio_frame_queue);
		}

		len1 = m_audio_out_buf_size - m_audio_out_buf_current_pos;
		if (len1 > len){
			len1 = len;
		}
		memcpy(stream, m_audio_buf + m_audio_out_buf_current_pos, len1);

		len -= len1;
		stream += len1;
		m_audio_out_buf_current_pos += len1;
	}
}
