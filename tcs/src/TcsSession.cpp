#include "Platform.h"
#include "TcsGlobal.h"
#include "Error.h"
#include "Config.h"
#include "logging.h"

#include "TcpStream.h"
#include "TcsLiveSvr.h"
#include "TcsServer.h"
#include "TcsSession.h"

#include "CFL_Message.h"
#include "CFL_TcsHeartBeat.h"
#include "CFL_TcsRegister.h"

#ifdef WIN32
#include <windows.h>
#include "threading-windows.h"
#else
#include <unistd.h>
#include "threading-posix.h"
#endif

#include <assert.h>

CTcsSession::CTcsSession()
{
	m_is_closed = false;
	m_connect_succesed = false;
	m_register_success = false;
	m_inited_once = false;
	m_bls_sockfd = -1;
	m_expires = DEFAULT_HEARTBEAT;
	m_max_numbers = DEFAULT_MAX_CONNCETIONS;
	m_server_id = -1;
	m_timeout_nums = 0;

	m_config = NULL;
	m_tcp_stream = NULL;
	m_prot_parser = NULL;
	m_live_svr = NULL;
	m_tcs_server = NULL;

	m_socket_buf = (char*)malloc(MAX_SOCKET_BUFFER_LENGTH);
	memset(m_socket_buf, 0, MAX_SOCKET_BUFFER_LENGTH);
}

CTcsSession::~CTcsSession()
{

}

void CTcsSession::onPDU(int conn_id, CFLMessage* pdu)
{
	if (pdu->_messageHead->nCmd == CMD_DETU_TCS_REGISTER_RES){
		handle_register_response(conn_id, pdu);
		return;
	}
	if (pdu->_messageHead->nCmd == CMD_DETU_TCS_HEARTBEAT_RES){
		handle_hearbeat_response(conn_id, pdu);
		return;
	}

	if (m_live_svr){
		m_live_svr->HandlePdu(conn_id, pdu);
	}
}

int CTcsSession::Start()
{
	sock_init();
	m_tcp_stream = new CTcpstream;
	m_prot_parser = new CFLCmdParser(this);
	m_live_svr = new CTcsLiveSvr;
	m_tcs_server = new CTcsServer;

	if (m_config){
		m_expires = m_config->GetExpires();
		m_max_numbers = m_config->GetMaxConnections();
		m_server_id = m_config->GetServerId();
		m_bls_addr = m_config->GetBLS();
		m_url_addr = m_config->GetUrlAddr();
		Log::Info("server id:%d, expires:%d, limits:%d", m_server_id, m_expires, m_max_numbers);
	}

	int ret = init_cms_socket();
	if (ret != ERROR_SUCCESS){
		Log::Error("CTcsSession init socket error, can't connect to cms:%s", m_bls_addr.c_str());
		return ERROR_SOCKET_ERROR;
	}
	register_to_cms();

	if (m_timeout_thread && m_timeout_thread->joinable()){
		m_timeout_thread->join();
	}
	m_timeout_thread.reset(new std::thread(&CTcsSession::handle_timeout, this));

	if (m_protocl_thread && m_protocl_thread->joinable()){
		m_protocl_thread->join();
	}
	m_protocl_thread.reset(new std::thread(&CTcsSession::handle_input, this));

	return ERROR_SUCCESS;
}

int CTcsSession::Close()
{
	m_is_closed = true;
	m_connect_succesed = false;
	m_register_success = false;
	m_live_svr->SetSocket(-1);
	::shutdown(m_bls_sockfd, SD_BOTH);
	closesocket(m_bls_sockfd);
	if (m_timeout_thread && m_timeout_thread->joinable()){
		m_timeout_thread->join();
	}
	if (m_protocl_thread && m_protocl_thread->joinable()){
		m_protocl_thread->join();
	}

	if (m_tcs_server){
		m_tcs_server->Close();
		delete m_tcs_server;
		m_tcs_server = NULL;
	}
	if (m_live_svr){
		m_live_svr->Close();
		delete m_live_svr;
		m_live_svr = NULL;
	}
	if (m_prot_parser){
		delete m_prot_parser;
		m_prot_parser = NULL;
	}
	if (m_tcp_stream){
		delete m_tcp_stream;
		m_tcp_stream = NULL;
	}
	if (m_socket_buf){
		free(m_socket_buf);
		m_socket_buf = NULL;
	}

	sock_clean();
	return ERROR_SUCCESS;
}

void CTcsSession::SetConfig(CTcsConfig* config)
{
	m_config = config;
}

int CTcsSession::init_cms_socket(void)
{
	struct addrinfo hints = { 0 }, *ai;
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	std::string bls_ip = m_bls_addr.substr(0, m_bls_addr.find(":", 0));
	std::string bls_port = m_bls_addr.substr(m_bls_addr.find(":", 0) + 1);
	int addrret = getaddrinfo(bls_ip.c_str(), bls_port.c_str(), &hints, &ai);
	if (addrret != 0) {
		Log::Error("problem accessing the DNS. addr:%s", m_bls_addr.c_str());
		return ERROR_FAILED;
	}

	m_bls_sockfd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
	if (m_bls_sockfd == -1) {
		freeaddrinfo(ai);
		Log::Error("could not create socket");
		return ERROR_SOCKET_CREATE;
	}

	if (::connect(m_bls_sockfd, ai->ai_addr, ai->ai_addrlen) < 0) {
		int err = GetSockError();
		Log::Error("failed to connect to server,error code:%d(%s)", err, strerror(err));

		freeaddrinfo(ai);
		return ERROR_SOCKET_CONNECT;
	}

	freeaddrinfo(ai);

	int on = 1;
	setsockopt(m_bls_sockfd, IPPROTO_TCP, TCP_NODELAY, (char *)&on, sizeof(on));

	int cur_sendbuf_size = SEND_BUF_SIZE;
	setsockopt(m_bls_sockfd, SOL_SOCKET, SO_SNDBUF, (const char*)&cur_sendbuf_size, sizeof(int));

	m_connect_succesed = true;
	m_live_svr->SetSocket(m_bls_sockfd);

	Log::Info("connect to cms success, socket:%d, cms server address:%s", m_bls_sockfd, m_bls_addr.c_str());
	return ERROR_SUCCESS;
}

void CTcsSession::register_to_cms(void)
{
	std::string url_ip = m_url_addr.substr(0, m_url_addr.find(":", 0));
	std::string url_port = m_url_addr.substr(m_url_addr.find(":", 0) + 1);
	int listen_port = ::atoi(url_port.c_str());

	CFLTcsRegister* request = new CFLTcsRegister;
	request->_messageBody->nServerId = htonl(m_server_id);
	request->_messageBody->nLimits = htonl(m_max_numbers);
	request->_messageBody->nHeartbeatInterval = htonl(m_expires);
	request->_messageBody->nPort = htonl(listen_port);
	memcpy(request->_messageBody->szTcsIp, url_ip.c_str(), API_ARRAY_LEN);
	request->generateMessage();

	m_tcp_stream->SendData(m_bls_sockfd, request->_message, request->getMessageLength());
	delete request;

	Log::Info("CMD_DETU_TCS_REGISTER send successed.");
}

void CTcsSession::send_heartbeat_request(void)
{
	CFLHeartBeat* request = new CFLHeartBeat;
	request->_messageBody->nServerId = htonl(m_server_id);
	request->_messageBody->nLimits = htonl(m_max_numbers);
	request->_messageBody->nCAU = htonl(m_live_svr->GetLiveChannelNum());
	request->generateMessage();

	m_tcp_stream->SendData(m_bls_sockfd, request->_message, request->getMessageLength());
	delete request;
	Log::Info("CMD_DETU_TCS_HEARTBEAT send success.");
}

void CTcsSession::handle_register_response(int conn_id, CFLMessage* pdu)
{
	CFLTcsRegisterResponse* response = (CFLTcsRegisterResponse*)pdu;
	int result = response->_messageHead->nResult;
	if (result == RESULT_SUCCESS){
		m_register_success = true;
		if (!m_inited_once){
			m_tcs_server->SetConfig(m_config);
			m_tcs_server->SetLiveSvr(m_live_svr);
			int ret = m_tcs_server->Init();
			if (ret == ERROR_SUCCESS){
				m_inited_once = true;
				m_tcs_server->Start();
			}
		}
		Log::Info("CMD_DETU_TCS_REGISTER_RES recv, register to bls success.");
	} else {
		Log::Info("register to bls error:%d, try reconnect cms.", result);
	}
}

void CTcsSession::handle_hearbeat_response(int conn_id, CFLMessage* pdu)
{
	os_atomic_dec_long(&m_timeout_nums);
	Log::Info("CMD_DETU_TCS_HEARTBEAT_RES recv success.");
}

int CTcsSession::get_body_length(const char* data, int length)
{
	assert(length >= (2 * sizeof(unsigned char)+sizeof(unsigned short)+sizeof(unsigned int)));

	char* ptr = (char*)data + 2 * sizeof(unsigned char)+sizeof(unsigned short);

	unsigned int value = 0;
	char* pp = (char*)&value;
	pp[3] = *ptr++;
	pp[2] = *ptr++;
	pp[1] = *ptr++;
	pp[0] = *ptr++;

	return (int)value;
}

void CTcsSession::close_invalid_socket(int client_socket, int errorno)
{
	if (errorno == ConnectionReset) {
		int sockerr = GetSockError();
		Log::Error("CTcsSession::socket error, socket:%d, errorno:%d(%s)", client_socket, sockerr, strerror(sockerr));
	}else if (errorno == ConnectionClosed) {
		Log::Error("CTcsSession::connection close, socket:%d", client_socket);
	}else if (errorno == ConnectionTimedOut){
		Log::Error("CTcsSession::connection timeout, socket:%d", client_socket);
	}
	::shutdown(client_socket, SD_BOTH);
	closesocket(client_socket);

	return;
}

void CTcsSession::handle_timeout(void)
{
	while (true) {
#ifdef WIN32
		Sleep(m_expires * 1000);
#else
		sleep(m_expires);
#endif

		if (m_is_closed){
			break;
		}

		if (!m_connect_succesed) {
			init_cms_socket();
		}

		if (!m_register_success && m_connect_succesed) {
			register_to_cms();
		} else if (m_connect_succesed){
			send_heartbeat_request();
			os_atomic_inc_long(&m_timeout_nums);
			if (m_timeout_nums > DEFAULT_MAX_TIMEOUT_NUMS) {
				Log::Error("can't recv heartbeat from bls, reconncet to bls.");
				m_connect_succesed = false;
				m_register_success = false;
				m_live_svr->SetSocket(-1);
				os_atomic_set_long(&m_timeout_nums, 0);
				close_invalid_socket(m_bls_sockfd, 1);
			}
		}

		if (!m_inited_once && m_register_success){
			m_tcs_server->SetConfig(m_config);
			m_tcs_server->SetLiveSvr(m_live_svr);
			int ret = m_tcs_server->Init();
			if (ret == ERROR_SUCCESS){
				m_inited_once = true;
				m_tcs_server->Start();
			}
		}
	}
}

void CTcsSession::handle_input(void)
{
	int head_length = sizeof(protocol_head_t);
	while (true) {
		if (m_is_closed){
			break;
		}

		if (m_connect_succesed) {
			int ret = m_tcp_stream->ReceiveData(m_bls_sockfd, m_socket_buf, head_length);
			if ((ret == ConnectionReset) || (ret == ConnectionClosed) || (ret == ConnectionTimedOut)) {
				m_live_svr->SetSocket(-1);
				close_invalid_socket(m_bls_sockfd, ret);
				m_connect_succesed = false;
				m_register_success = false;
				os_atomic_set_long(&m_timeout_nums, 0);
				continue;
			}

			int body_length = get_body_length(m_socket_buf, head_length);
			if (body_length != 0){
				ret = m_tcp_stream->ReceiveData(m_bls_sockfd, m_socket_buf + head_length, body_length);
				if ((ret == ConnectionReset) || (ret == ConnectionClosed) || (ret == ConnectionTimedOut)) {
					m_live_svr->SetSocket(-1);
					close_invalid_socket(m_bls_sockfd, ret);
					m_connect_succesed = false;
					m_register_success = false;
					os_atomic_set_long(&m_timeout_nums, 0);
					continue;
				}
			}
			m_prot_parser->parse(m_bls_sockfd, m_socket_buf, body_length + head_length);
		}
	}
}

int CTcsSession::sock_init()
{
#ifdef WIN32
	WORD version;
	WSADATA wsaData;
	version = MAKEWORD(2, 2);
	if (WSAStartup(version, &wsaData) != 0) {
		Log::Error("CTcsSession sock_init(): windows socket init error");
		return -1;
	}
#endif
	return 0;
}

int CTcsSession::sock_clean()
{
#ifdef WIN32
	WSACleanup();
#endif
	return 0;
}
