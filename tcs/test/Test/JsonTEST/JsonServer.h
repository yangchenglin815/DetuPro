#ifndef _JSON_SERVER_H_
#define _JSON_SERVER_H_

#include <string>
#include <thread>
#include <memory>

class CTcpstream;

class CJsonServer
{
public:
	CJsonServer();
	~CJsonServer();

public:
	int  Init(void);
	void Start(void);
	void Close(void);

private:
	void handle_stream_input();

private:
	int sock_init();
	int sock_clean();
	int init_server();
	void parser_request(int socket);
	std::string parser_http_head(std::string data);

private:
	bool m_is_closed;
	bool m_listening;
	int	 m_server_sockfd;

	CTcpstream*		m_tcp_stream;
	char*			m_protocol_buf;

	std::shared_ptr<std::thread>	m_recv_thread;

private:
	int m_listen_port;
};

#endif
