#ifndef _TCS_SVR_SESSION_H_
#define _TCS_SVR_SESSION_H_

#include <memory>
#include <thread>
#include "ProtocolParser.h"
#include "MessageHandle.h"
#include "TcsLiveChannel.h"

class CTcsConfig;
class CTcpstream;
class CTcsLiveSvr;

class CSvrSession : public CMessageHandle, public ICmdListener
{
public:
	CSvrSession();
	virtual ~CSvrSession();

	virtual void onPDU(int conn_id, CFLMessage* pdu);
	virtual void onMessage(long session_id, int message_type);

public:
	int  Init(int fd, char* pre_buf, int length);
	void Start();
	void Close();
	void SetConfig(CTcsConfig* config);
	void SetLiveSvr(CTcsLiveSvr* live_svr);
	void HandlePdu(int conn_id, CFLMessage* pdu);

private:
	int  get_body_length(const char* data, int length);
	void close_invalid_socket(int client_socket, int errorno);
	void handle_transcode_request(int conn_id, CFLMessage* pdu);
	void handle_stop_transcode_request(int conn_id, CFLMessage* pdu);
	void handle_start_video_response(int conn_id, CFLMessage* pdu);
	void handle_start_video_request(std::string device_name, unsigned char stream_type, unsigned char device_id, unsigned int start_time, unsigned int end_time);
	void handle_stop_video_response(int conn_id, CFLMessage* pdu);
	void handle_stop_video_request(std::string device_name, int errorno);
	void handle_session_error(int error);

	void handle_transcode_response(int conn_id, std::string device_name, int errorno);
	void handle_stop_transcode_response(int conn_id, std::string device_name, int errorno);

	void start_transcode(int stream_type, std::string device_name, std::string rtmp_url);
	void stop_transcode(std::string device_name);

	void create_pts_file(unsigned char* data, int length);
	bool create_directory(const char* dir);

private:
	void handle_stream_input(void);

private:
	std::shared_ptr<std::thread>	m_protocol_thread;

	bool			m_closed;
	bool			m_is_pts_new;
	int				m_socket;
	char*			m_protocol_buf;
	CTcsConfig*		m_config;
	CTcpstream*		m_tcp_stream;
	CFLCmdParser*	m_parser;
	CTcsLiveSvr*	m_live_svr;
	CTcsLiveChannel* m_live_channel;

	transcode_param_t m_transcode_param;
};

#endif
