#ifndef _TCS_SERVER_H_
#define _TCS_SERVER_H_

#include <string>
#include <thread>
#include <memory>

class CTcsConfig;
class CTcsLiveSvr;
class CSvrSessionManager;

class CTcsServer
{
public:
	CTcsServer();
	~CTcsServer();

public:
	int  Init(void);
	void Start(void);
	void Close(void);
	void SetConfig(CTcsConfig* config);
	void SetLiveSvr(CTcsLiveSvr* live_svr);

private:
	void handle_stream_input();

private:
	int init_server();

private:
	bool m_is_closed;
	bool m_listening;
	int	 m_server_sockfd;

	CTcsConfig* m_config;
	CSvrSessionManager* m_manager;

	std::shared_ptr<std::thread>	m_recv_thread;

private:
	int m_listen_port;
	CTcsLiveSvr* m_live_svr;
};

#endif
