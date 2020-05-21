#ifndef _TCS_SESSION_H_
#define _TCS_SESSION_H_

#include <string>
#include <memory>
#include <thread>
#include "ProtocolParser.h"

class CTcsConfig;
class CTcpstream;
class CFLMessage;
class CTcsLiveSvr;
class CTcsServer;

class CTcsSession : public ICmdListener
{
public:
	CTcsSession();
	virtual ~CTcsSession();

	virtual void onPDU(int conn_id, CFLMessage* pdu);

public:
	int Start();
	int Close();
	void SetConfig(CTcsConfig* config);

private:
	int  init_cms_socket(void);
	void register_to_cms(void);
	void send_heartbeat_request(void);
	void handle_register_response(int conn_id, CFLMessage* pdu);
	void handle_hearbeat_response(int conn_id, CFLMessage* pdu);
	int  get_body_length(const char* data, int length);
	void close_invalid_socket(int client_socket, int errorno);

private:
	void handle_timeout(void);
	void handle_input(void);

private:
	int sock_init();
	int sock_clean();

private:
	bool		m_is_closed;
	bool		m_connect_succesed;
	bool		m_register_success;
	bool		m_inited_once;
	int			m_bls_sockfd;
	int			m_expires;
	int			m_max_numbers;
	int			m_server_id;
	long		m_timeout_nums;
	std::string m_bls_addr;
	std::string m_url_addr;

	char*				m_socket_buf;
	CTcsConfig*			m_config;
	CTcpstream*			m_tcp_stream;
	CFLCmdParser*		m_prot_parser;
	CTcsLiveSvr*		m_live_svr;
	CTcsServer*			m_tcs_server;

	std::shared_ptr<std::thread>	m_timeout_thread;
	std::shared_ptr<std::thread>	m_protocl_thread;
};

#endif
