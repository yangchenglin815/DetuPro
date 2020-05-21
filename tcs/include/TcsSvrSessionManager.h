#ifndef _TCS_SVR_SESSION_MANAGER_H_
#define _TCS_SVR_SESSION_MANAGER_H_

#include <deque>
#include <string>
#include <mutex>
#include <memory>
#include <thread>
#include <condition_variable>
#include "MessageHandle.h"

class CTcsConfig;
class CTcpstream;
class CTcsLiveSvr;
class CSvrSession;

class CSvrSessionManager : public CMessageHandle
{
public:
	CSvrSessionManager();
	virtual ~CSvrSessionManager();

	virtual void onMessage(long session_id, int message_type);

public:
	void Start();
	void Close();
	void Enqueue(int client_sockfd);
	void SetConfig(CTcsConfig* config);
	void SetLiveSvr(CTcsLiveSvr* live_svr);

private:
	void close_invalid_socket(int client_socket, int errorno);
	void handle_input();

private:
	std::deque<int>					m_connections;
	std::shared_ptr<std::thread>	m_conn_manager_thread;
	std::mutex						m_emytp_mtx;
	std::condition_variable			m_empty_con;

	std::mutex						m_session_mtx;
	std::map<long, CSvrSession*>	m_session_manager;

	bool			m_closed;
	char*			m_pre_buf;
	CTcsConfig*		m_config;
	CTcpstream*		m_tcp_stream;
	CTcsLiveSvr*	m_live_svr;
};

#endif
