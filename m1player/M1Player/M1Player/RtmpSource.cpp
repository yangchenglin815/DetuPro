#include "DataSource.h"
#include "RtmpSource.h"
#include "ijksdl_log.h"
#include "Error.h"

extern "C"
{
#include "libavutil/time.h"
}


#ifdef WIN32
static void  rtmp_log_callback(int level, const char *format, va_list vl)
{
	char str[1024] = "";
	if (level <= RTMP_debuglevel) {
		vsnprintf(str, sizeof(str) - 1, format, vl);
		ALOGI("%s", str);
	}
}
#endif

CRtmpSource::CRtmpSource()
{
	m_is_closed  = false;
	m_rtmp_handle = NULL;
	m_rtmp_packet = NULL;
	m_current_flv_tag = NULL;
	m_sync_packet = NULL;
	m_recv_all_cam_packet = false;
	m_seq_id = 0;

	for (int i = 0; i < M1_VIDEO_NUM_PER_CHANNEL; i++) {
		m_flv_parser[i] = NULL;
		m_recv_cam_packet[i] = false;
		m_packets_num_befor_sync[i] = 0;
	}
}

CRtmpSource::~CRtmpSource()
{

}

int CRtmpSource::InitSource(std::string url)
{
	SockInit();

#ifdef WIN32
	RTMP_LogLevel loglevel = RTMP_LOGDEBUG;
	RTMP_LogSetLevel(loglevel);
	RTMP_LogSetCallback(rtmp_log_callback);
#endif

	m_url = url;
	m_rtmp_handle = PILI_RTMP_Alloc();
	PILI_RTMP_Init(m_rtmp_handle);
	m_rtmp_handle->Link.timeout = 10;
	PILI_RTMP_SetupURL(m_rtmp_handle, url.c_str(), NULL);
	PILI_RTMP_SetBufferMS(m_rtmp_handle, 10 * 1000);
	if (!PILI_RTMP_Connect(m_rtmp_handle, NULL, NULL)) {
		ALOGE("connect rtmp server error, check your network");
		return ERROR_RTMP_HANDSHAKE;
	}

	m_rtmp_packet = (PILI_RTMPPacket*)malloc(sizeof(PILI_RTMPPacket));
	memset(m_rtmp_packet, 0, sizeof(PILI_RTMPPacket));
	PILI_RTMPPacket_Reset(m_rtmp_packet);

	m_sync_packet = (SyncPacket*)malloc(sizeof(SyncPacket));
	memset(m_sync_packet, 0, sizeof(SyncPacket));
	av_init_packet(&(m_sync_packet->av_packet));

	m_current_flv_tag = (FlvTag*)malloc(sizeof(FlvTag));
	memset(m_current_flv_tag, 0, sizeof(FlvTag));

	return 0;
}

int CRtmpSource::HandShake()
{
	if (!PILI_RTMP_ConnectStream(m_rtmp_handle, 0, NULL)) {
		ALOGE("connect stream error, check your rtmp server");
		return ERROR_RTMP_CONNECT_STREAM;
	}
	PILI_RTMP_SetChunkSize(m_rtmp_handle, NULL, 4096);

	return 0;
}

int CRtmpSource::StartRecv()
{
	if (m_net_recv_thread && m_net_recv_thread->joinable()) {
		m_net_recv_thread->join();
	}
	m_net_recv_thread.reset(new std::thread(&CRtmpSource::handle_stream_input, this));
	//HANDLE th = m_net_recv_thread->native_handle();
	//BOOL res = SetThreadPriority(th, THREAD_PRIORITY_HIGHEST);
	//if (res == FALSE) {
	//	int err = GetLastError();
	//	ALOGE("Set thread priority error, err code:%d", err);
	//	return -1;
	//}

	return 0;
}

int CRtmpSource::CloseSource()
{
	m_is_closed = true;
	reset();
	SockClean();
	return 0;
}

void CRtmpSource::SetStreamSaveTag(bool save_tag)
{
	m_is_save_flv = save_tag;

	if (m_is_save_flv) {
		char file_name[512] = { 0 };
		for (int i = 0; i < M1_VIDEO_NUM_PER_CHANNEL; i++) {
			if (m_record_path.size()>0){
				sprintf(file_name, "%s/%s_%d", m_record_path.c_str(), "flv", i+1);
			} else {
				sprintf(file_name, "%s_%d", "flv", i+1);
			}
			m_flv_parser[i] = new CFlvParser();
			m_flv_parser[i]->Init();
			m_flv_parser[i]->CreateFlvFile(file_name);
		}

		ALOGE("start save flv file as: %s.", file_name);
	} else {
		for (int i = 0; i < M1_VIDEO_NUM_PER_CHANNEL; i++) {
			if (m_flv_parser[i]) {
				m_flv_parser[i]->Close();
				delete m_flv_parser[i], m_flv_parser[i] = NULL;
			}
		}
	}

	return;
}

bool CRtmpSource::generate_flv_tag(void)
{
	m_current_flv_tag->type = m_rtmp_packet->m_packetType;
	m_current_flv_tag->datalength = m_rtmp_packet->m_nBodySize;
	m_current_flv_tag->timestamp = m_rtmp_packet->m_nTimeStamp;
	m_current_flv_tag->streamid = 0;
	m_current_flv_tag->buffer = m_rtmp_packet->m_body;
	m_current_flv_tag->taglength = m_rtmp_packet->m_nBodySize + FLV_TAG_HEADER_LENGTH;

	if (m_current_flv_tag->type == 0x09){			//video tag
		m_current_flv_tag->frame_type = (m_rtmp_packet->m_body[0] >> 4) & 0x0f;

		int con_time = 0;
		char* p = (char*)&con_time;
		p[0] = m_current_flv_tag->buffer[4];
		m_current_flv_tag->composition_time = con_time - 1;

		m_current_flv_tag->buffer[8] = VIDEO_TIMESTAMP_LENGTH_DATA;

		return !m_current_flv_tag->buffer[1];
	} else if (m_current_flv_tag->type == 0x08){	//audio tag
		return false;
	} else {										//info tag
		return false;
	}
}

void CRtmpSource::write_flv_tag(bool tag)
{
	if (m_is_save_flv && tag) {
		m_packets_num_befor_sync[m_current_flv_tag->composition_time] += 1;

		m_flv_parser[m_current_flv_tag->composition_time]->WriteTag(m_current_flv_tag);
	}

	return;
}

void CRtmpSource::handle_stream_input(void)
{
	int counter = 0;
	unsigned int last_packet_seq[M1_VIDEO_NUM_PER_CHANNEL] = { 0 };
	while (true) {
		if (m_is_closed) {
			break;
		}

		if (PILI_RTMP_GetNextMediaPacket(m_rtmp_handle, m_rtmp_packet)) {
			bool is_sequnce_hearder = generate_flv_tag();

			if (is_sequnce_hearder) {
				seq_head_to_sync_packet();
				continue;
			} else {
				nual_tag_to_sync_packet();
			}

			if (m_sync_packet->codec_type == AVMEDIA_TYPE_VIDEO){
				if (last_packet_seq[m_current_flv_tag->composition_time] == 0){
					last_packet_seq[m_current_flv_tag->composition_time] = m_sync_packet->packet_seq;
				} else {
					if ((last_packet_seq[m_current_flv_tag->composition_time] + 1) != m_sync_packet->packet_seq){
						ALOGE("rtmp packet is not continuous, cam seq:%d, last seq:%d, cunrrent seq:%d", m_current_flv_tag->composition_time, last_packet_seq[m_current_flv_tag->composition_time], m_sync_packet->packet_seq);
					}
					last_packet_seq[m_current_flv_tag->composition_time] = m_sync_packet->packet_seq;
				}

				bool ret = sync_detect(counter);
				if (!ret){
					for (int i = 0; i < M1_VIDEO_NUM_PER_CHANNEL; i++){
						last_packet_seq[i] = 0;
					}
				}
				generate_sync_sequence_id(m_current_flv_tag->composition_time);
				write_flv_tag(m_recv_cam_packet[m_current_flv_tag->composition_time]);
			}

			if ((m_sync_packet_callback != nullptr) && 
				(m_recv_cam_packet[m_current_flv_tag->composition_time] || 
				 (m_sync_packet->codec_type == AVMEDIA_TYPE_AUDIO)))
			{
				m_sync_packet_callback(m_sync_packet);
			}

			PILI_RTMPPacket_Free(m_rtmp_packet);
			PILI_RTMPPacket_Reset(m_rtmp_packet);
		} else {
			ALOGE("get rtmp packet error,check network.");

			{
				counter = 0;
				for (int i = 0; i < M1_VIDEO_NUM_PER_CHANNEL; i++){
					last_packet_seq[i] = { 0 };
				}
			}

			if (m_message_callback != nullptr) {
				if (m_is_closed) {
					m_message_callback(ERROR_SYSTEM_PLAYER_CLOSE);
				}
				else {
					m_message_callback(ERROR_SOCKET_READ);
				}
			}
			break;
		}
	}

	ALOGE("rtmp recv thread stop now.");
}

int CRtmpSource::seq_head_to_sync_packet(void)
{
	char index[4] = { 0x00, 0x00, 0x00, 0x01 };
	if (m_current_flv_tag->type != RTMP_PACKET_TYPE_VIDEO) {
		ALOGE("not rtmp video tag,ignore.");
		return -1;
	}

	m_sync_packet->codec_type = AVMEDIA_TYPE_VIDEO;
	if (m_current_flv_tag->frame_type == KEYFRAME) {
		m_sync_packet->av_packet.flags = AV_PKT_FLAG_KEY;
	}

	int sps_size = (int)m_current_flv_tag->buffer[12];
	m_sps_pps_length = sps_size + 12;
	m_sps_pps = (char*)malloc(m_sps_pps_length);
	memcpy(m_sps_pps, index, 4);
	memcpy(m_sps_pps + 4, (const void*)(m_current_flv_tag->buffer + 13), sps_size);
	memcpy(m_sps_pps + sps_size + 4, index, 4);
	memcpy(m_sps_pps + sps_size + 8, (const void*)(m_current_flv_tag->buffer + 13 + sps_size + 3), 4);
	m_sync_packet->av_packet.data = (uint8_t*)m_sps_pps;
	m_sync_packet->av_packet.size = m_sps_pps_length;
	m_sync_packet->came_seq = m_current_flv_tag->composition_time;

	parse_sps(m_sync_packet->video_w, m_sync_packet->video_h);

	return 0;
}

int CRtmpSource::nual_tag_to_sync_packet(void)
{
	if (m_current_flv_tag->type == RTMP_PACKET_TYPE_INFO) {
		return -1;
	} else if (m_current_flv_tag->type == RTMP_PACKET_TYPE_AUDIO){
		unsigned long long audio_timestamp = 0;
		char* p = (char*)&audio_timestamp;
		p[0] = m_current_flv_tag->buffer[14];
		p[1] = m_current_flv_tag->buffer[13];
		p[2] = m_current_flv_tag->buffer[12];
		p[3] = m_current_flv_tag->buffer[11];
		p[4] = m_current_flv_tag->buffer[10];
		p[5] = m_current_flv_tag->buffer[9];
		p[6] = m_current_flv_tag->buffer[8];
		p[7] = m_current_flv_tag->buffer[7];
		m_sync_packet->timestamp = audio_timestamp;

		m_sync_packet->codec_type = AVMEDIA_TYPE_AUDIO;
		m_sync_packet->av_packet.size = m_current_flv_tag->datalength - AUDIO_DATA_HEAD_LENGTH - AUDIO_DATA_TIMESTAMP_LENGTH;
		m_sync_packet->av_packet.data = (uint8_t *)m_current_flv_tag->buffer + AUDIO_DATA_HEAD_LENGTH + AUDIO_DATA_TIMESTAMP_LENGTH;
	} else {
		if (m_current_flv_tag->frame_type == KEYFRAME) {
			m_sync_packet->av_packet.flags = AV_PKT_FLAG_KEY;
		} else {
			m_sync_packet->av_packet.flags = 0;
		}

		unsigned long long video_timestamp = 0;
		char* p = (char*)&video_timestamp;
		p[0] = m_current_flv_tag->buffer[17];
		p[1] = m_current_flv_tag->buffer[16];
		p[2] = m_current_flv_tag->buffer[15];
		p[3] = m_current_flv_tag->buffer[14];
		p[4] = m_current_flv_tag->buffer[13];
		p[5] = m_current_flv_tag->buffer[12];
		p[6] = m_current_flv_tag->buffer[11];
		p[7] = m_current_flv_tag->buffer[10];
		m_sync_packet->timestamp = video_timestamp;

		unsigned int packet_sequence = 0;
		p = (char*)&packet_sequence;
		p[0] = m_current_flv_tag->buffer[21];
		p[1] = m_current_flv_tag->buffer[20];
		p[2] = m_current_flv_tag->buffer[19];
		p[3] = m_current_flv_tag->buffer[18];
		m_sync_packet->packet_seq = packet_sequence;

		m_sync_packet->came_seq = m_current_flv_tag->composition_time;

		m_sync_packet->codec_type = AVMEDIA_TYPE_VIDEO;
		m_sync_packet->av_packet.size = m_current_flv_tag->datalength - DATA_HEADER_LENGTH - VIDEO_TIMESTAMP_LENGTH;
		m_sync_packet->av_packet.data = (uint8_t *)m_current_flv_tag->buffer + DATA_HEADER_LENGTH + VIDEO_TIMESTAMP_LENGTH;
		//m_sync_packet->pts = av_gettime_relative()/1000000.0;
	}

	return 0;
}

void CRtmpSource::generate_sync_sequence_id(int cam_seq)
{
	if (m_recv_all_cam_packet) {
		m_sync_packet->is_sync  = true;
		m_sync_packet->sync_seq = m_seq_id++ / 4 + 1;
	} else {
		m_sync_packet->is_sync = false;
		m_sync_packet->sync_seq = 0;
	}

	if (!m_recv_cam_packet[cam_seq]) {
		if (m_current_flv_tag->frame_type != 1 || m_current_flv_tag->taglength < 100) {
			return;
		}

		m_recv_cam_packet[cam_seq] = true;

		if (m_recv_cam_packet[0] && m_recv_cam_packet[1] && m_recv_cam_packet[2] && m_recv_cam_packet[3]) {
			m_recv_all_cam_packet = true;
			m_seq_id = 1;
			ALOGE("recv all camera packet, start display picture.");

			if (m_is_save_flv) {
				ALOGE("pakcets before sync, cam1:%d,cam2:%d,cam3:%d,cam4:%d", m_packets_num_befor_sync[0],
					m_packets_num_befor_sync[1], m_packets_num_befor_sync[2], m_packets_num_befor_sync[3]);
			}
		}
	}

	return;
}

void CRtmpSource::reset_sync_resource(void)
{
	m_recv_all_cam_packet = false;
	m_seq_id = 0;

	for (int i = 0; i < M1_VIDEO_NUM_PER_CHANNEL; i++) {
		m_recv_cam_packet[i] = false;
		m_packets_num_befor_sync[i] = 0;
	}
}

bool CRtmpSource::sync_detect(int &counter)
{
	if (m_recv_all_cam_packet) {
		if (m_seq_id % 8) {
			if (1 == m_current_flv_tag->composition_time) {
				counter += 1;
			}
		}

		if (!(m_seq_id % 8)) {
			if ((counter > 2) || (counter == 0)) {
				ALOGE("rtmp packet out of sync, clean up cache resouce.");
				reset_sync_resource();
				counter = 0;
				return false;
			} 
			counter = 0;
		}
	}

	return true;
}

void CRtmpSource::reset(void)
{
	if (m_rtmp_handle) {
		PILI_RTMP_Close(m_rtmp_handle, NULL);
	}

	if (m_net_recv_thread && m_net_recv_thread->joinable()) {
		m_net_recv_thread->join();
	}

	PILI_RTMP_Free(m_rtmp_handle);
	m_rtmp_handle = NULL;

	for (int i = 0; i < M1_VIDEO_NUM_PER_CHANNEL; i++) {
		if (m_flv_parser[i]) {
			m_flv_parser[i]->Close();
			delete m_flv_parser[i], m_flv_parser[i] = NULL;
		}
	}

	if (m_current_flv_tag) {
		free(m_current_flv_tag);
	}

	if (m_rtmp_packet) {
		free(m_rtmp_packet);
		m_rtmp_packet = NULL;
	}

	if (m_sync_packet) {
		free(m_sync_packet);
		m_sync_packet = NULL;
	}
}
