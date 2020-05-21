#ifndef _RTMP_SOURCE_H_
#define _RTMP_SOURCE_H_

#include <memory>
#include <thread>

#include "FlvParser.h"
#include "rtmp.h"
#include "log.h"

#define DATA_HEADER_LENGTH		9
#define VIDEO_TIMESTAMP_LENGTH	17
#define VIDEO_TIMESTAMP_LENGTH_DATA 0x0D
#define AUDIO_DATA_TIMESTAMP_LENGTH	13		//0x00 0x00 0x00 0x05 0x09 + timestamp(8bytes)
#define AUDIO_DATA_HEAD_LENGTH  2			//0xaf 0x01

class CIDataSource;

class CRtmpSource: public CIDataSource
{
public:
	CRtmpSource();
	virtual ~CRtmpSource();

public:
	virtual int  InitSource(std::string url);
	virtual int  HandShake(void);
	virtual int  StartRecv(void);
	virtual int  CloseSource(void);
	virtual void SetStreamSaveTag(bool save_tag);
    
private:
	bool generate_flv_tag(void);
	void write_flv_tag(bool tag);

	void handle_stream_input(void);

	int  seq_head_to_sync_packet(void);
	int  nual_tag_to_sync_packet(void);
	void generate_sync_sequence_id(int cam_seq);
	void reset_sync_resource(void);
	bool sync_detect(int &counter);
	void reset(void);

private:
	bool m_is_closed;
	std::shared_ptr<std::thread>	m_net_recv_thread;

	bool m_recv_all_cam_packet;
	bool m_recv_cam_packet[M1_VIDEO_NUM_PER_CHANNEL];
	int  m_packets_num_befor_sync[M1_VIDEO_NUM_PER_CHANNEL];
	long m_seq_id;

private:
	PILI_RTMP		*m_rtmp_handle;
	PILI_RTMPPacket *m_rtmp_packet;
	SyncPacket		*m_sync_packet;

private:
	FlvTag			*m_current_flv_tag;
	CFlvParser		*m_flv_parser[M1_VIDEO_NUM_PER_CHANNEL];
};

#endif
