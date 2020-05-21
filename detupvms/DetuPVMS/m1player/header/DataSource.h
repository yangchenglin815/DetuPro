#ifndef _DATA_SOURCE_H_
#define _DATA_SOURCE_H_

#include <string>
#include <functional>
#include <stdio.h>
#include <stdint.h>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
}

#define M1_VIDEO_NUM_PER_CHANNEL 4

typedef struct SyncPacket{
	bool				is_sync;	//ͬ����־λ
	unsigned int		video_h;	//��Ƶ�߶�
	unsigned int		video_w;	//��Ƶ���
	unsigned int		came_seq;	//��ͷ���к�
	unsigned int		sync_seq;	//ͬ�����к�
	unsigned int		packet_seq;	//֡���к�
	unsigned long long 	timestamp;	//����ʱ���
	double				pts;		//��ʾʱ���
	enum AVMediaType	codec_type;	//���ݰ����ͣ�audio or video
	AVPacket			av_packet;	//���ݰ�
}SyncPacket;

typedef std::function<void(const SyncPacket *stream_packet)> stream_packet_callback;
typedef std::function<void(int message)> message_callback;

typedef struct SpsPpsInfo {
    unsigned char* spsPpsData;
    int length;
} SpsPpsInfo;

class CIDataSource
{
public:
	CIDataSource();
	virtual ~CIDataSource();

public:
	virtual int  SockInit(void);
	virtual void SockClean(void);

	virtual int  InitSource(std::string url);
	virtual int  HandShake(void);
	virtual int  StartRecv(void);
	virtual int  ReConnet(void);
	virtual int  CloseSource(void);

	virtual void SetStreamSaveTag(bool save_tag);
	virtual void SetStreamSavePath(std::string path);
	virtual bool GetStreamSaveTag(void);

	virtual void SetPacketCallback(stream_packet_callback packet_call_back);
	virtual void SetMsgCallback(message_callback msg_call_back);
    virtual bool getSpsPpsInfo(SpsPpsInfo* info);

protected:
	void parse_sps(unsigned int &width, unsigned int &height);
	unsigned int read_bit(void);
	unsigned int read_bits(int n);
	unsigned int read_se(void);
	unsigned int read_exponential_golomb_code(void);

protected:
	std::string		m_url;
	std::string		m_record_path;
	bool			m_is_save_flv;

	char *m_sps_pps;
	int	 m_sps_pps_length;
	int	 m_sps_current_bit;

	message_callback		m_message_callback;
	stream_packet_callback	m_sync_packet_callback;
};

#endif
