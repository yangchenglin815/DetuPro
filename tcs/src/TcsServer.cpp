#include "Platform.h"
#include "Config.h"
#include "Error.h"
#include "TcsGlobal.h"
#include "TcsLiveSvr.h"
#include "TcsSvrSessionManager.h"
#include "TcsServer.h"
#include "logging.h"

CTcsServer::CTcsServer()
{
	m_is_closed = false;
	m_listening = false;
	m_server_sockfd = -1;
	m_config = NULL;
	m_manager = NULL;

	m_listen_port = 0;
	m_live_svr = NULL;
}

CTcsServer::~CTcsServer()
{

}

int CTcsServer::Init(void)
{
	if (m_config) {
		m_listen_port = m_config->GetListenPort();
	}

	int ret = init_server();
	if (ret != ERROR_SUCCESS) {
		Log::Error("tcs server init error.");
		return ERROR_SOCKET_ERROR;
	}

	m_manager = new CSvrSessionManager;
	m_manager->SetConfig(m_config);
	m_manager->SetLiveSvr(m_live_svr);
	m_manager->Start();

	Log::Info("tcs server init succesed, listen port:%d", m_listen_port);

	return ERROR_SUCCESS;
}

void CTcsServer::Start(void)
{
	if (m_listening == false) {
		return;
	}

	if (m_recv_thread && m_recv_thread->joinable()) {
		m_recv_thread->join();
	}
	m_recv_thread.reset(new std::thread(&CTcsServer::handle_stream_input, this));

	Log::Info("tcs server start now.");
}

void CTcsServer::Close(void)
{
	m_is_closed = true;
	m_listening = false;
	closesocket(m_server_sockfd);

	if (m_recv_thread && m_recv_thread->joinable()) {
		m_recv_thread->join();
	}

	if (m_manager) {
		m_manager->Close();
		delete m_manager;
		m_manager = NULL;
	}

	Log::Info("tcs server stop now.");
}

void CTcsServer::SetConfig(CTcsConfig* config)
{
	m_config = config;
}

void CTcsServer::SetLiveSvr(CTcsLiveSvr* live_svr)
{
	m_live_svr = live_svr;
}

void CTcsServer::handle_stream_input()
{
	while (true) {
		struct sockaddr_in address;
		socklen_t len = sizeof(address);
		memset(&address, 0, sizeof(address));
		int client_sockfd = ::accept(m_server_sockfd, (struct sockaddr*)&address, &len);
		if (m_is_closed) {
			break;
		}
		if (client_sockfd < 0) {
			continue;
		}

		if (m_manager) {
			m_manager->Enqueue(client_sockfd);
			Log::Debug("recv client connect, ip:%s, socketed:%d, ", inet_ntoa(address.sin_addr), client_sockfd);
		}
	}

	Log::Info("tcs server stop listening.");
}

int CTcsServer::init_server()
{
	m_server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (m_server_sockfd == -1) {
		Log::Error("CTcsServer could not create socket");
		return ERROR_SOCKET_CREATE;
	}

	struct sockaddr_in serverAddress;
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(m_listen_port);

	int optval = 1;
	setsockopt(m_server_sockfd, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof(optval));

#ifndef WIN32
	//ignore sigpipe
	int kOne = 1;
#ifdef __linux
	setsockopt(m_server_sockfd, SOL_SOCKET, MSG_NOSIGNAL, &kOne, sizeof(kOne));
#else
	setsockopt(m_server_sockfd, SOL_SOCKET, SO_NOSIGPIPE, &kOne, sizeof(kOne));
#endif
#endif

	int on = 1;
	setsockopt(m_server_sockfd, IPPROTO_TCP, TCP_NODELAY, (char *)&on, sizeof(on));

	int cur_sendbuf_size = SEND_BUF_SIZE;
	setsockopt(m_server_sockfd, SOL_SOCKET, SO_SNDBUF, (const char*)&cur_sendbuf_size, sizeof(int));

	int result = ::bind(m_server_sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
	if (result) {
		Log::Error("CTcsServer bind socket Failed");
		closesocket(m_server_sockfd);
		return ERROR_SOCKET_BIND;
	}

	result = ::listen(m_server_sockfd, 10);
	if (result != 0) {
		Log::Error("CTcsServer listen port:%d failed");
		closesocket(m_server_sockfd);
		return ERROR_SOCKET_LISTEN;
	}

	m_listening = true;

	return ERROR_SUCCESS;
}
