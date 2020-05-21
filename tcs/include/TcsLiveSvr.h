#ifndef _TCS_LIVE_SVR_H_
#define _TCS_LIVE_SVR_H_

#include <map>
#include <string>
#include <mutex>

class CSvrSession;
class CFLMessage;
class CTcpstream;

typedef enum live_channel_state{ 
	StatePrepare = 0,
	StateSuccess,
	StateFail,
}live_channel_state_e;

typedef struct live_channel_node{
	live_channel_state_e state;
	CSvrSession* session;
}live_channel_node_t;

class CTcsLiveSvr
{
public:
	CTcsLiveSvr();
	~CTcsLiveSvr();

	void AddSession(std::string device_name, live_channel_state_e state, CSvrSession* ptr);
	void UpdateSessionInfo(std::string device_name, live_channel_state_e state);
	void DelSession(std::string device_name);
	bool IsSessionLive(std::string device_name);
	int  GetLiveChannelNum();
	void Close();
	void HandlePdu(int conn_id, CFLMessage* pdu);
	void SendMsgToCMS(char* data, int length);
	void SetSocket(int fd);

private:
	CSvrSession* get_session(std::string device_name);

private:
	void handle_start_video_response(int conn_id, CFLMessage* pdu);
	void handle_close_video_response(int conn_id, CFLMessage* pdu);

private:
	int			m_bls_socket;
	CTcpstream*	m_bls_stream;
	std::mutex	m_socket_mtx;
	std::mutex	m_session_mtx;
	std::map<std::string, live_channel_node_t*> m_session_map;
};

#endif
