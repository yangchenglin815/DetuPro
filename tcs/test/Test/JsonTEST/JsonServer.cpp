#include "Platform.h"
#include "Error.h"
#include "TcsGlobal.h"
#include "TcpStream.h"
#include "JsonServer.h"

CJsonServer::CJsonServer()
{
	m_is_closed = false;
	m_listening = false;
	m_server_sockfd = -1;
	m_tcp_stream = NULL;
	m_listen_port = 0;

	m_protocol_buf = (char*)malloc(MAX_SOCKET_BUFFER_LENGTH);
	memset(m_protocol_buf, 0, MAX_SOCKET_BUFFER_LENGTH);
}

CJsonServer::~CJsonServer()
{

}

int CJsonServer::Init(void)
{
	sock_init();

	m_listen_port = 8080;
	m_tcp_stream = new CTcpstream;

	int ret = init_server();
	if (ret != ERROR_SUCCESS) {
		printf("json server init error.");
		return ERROR_SOCKET_ERROR;
	}

	printf("json server init succesed, listen port:%d\n", m_listen_port);

	return ERROR_SUCCESS;
}

void CJsonServer::Start(void)
{
	if (m_listening == false) {
		return;
	}

	if (m_recv_thread && m_recv_thread->joinable()) {
		m_recv_thread->join();
	}
	m_recv_thread.reset(new std::thread(&CJsonServer::handle_stream_input, this));

	printf("json server start now.\n");
}

void CJsonServer::Close(void)
{
	m_is_closed = true;
	m_listening = false;
	closesocket(m_server_sockfd);

	if (m_recv_thread && m_recv_thread->joinable()) {
		m_recv_thread->join();
	}

	if (m_tcp_stream) {
		delete m_tcp_stream;
		m_tcp_stream = NULL;
	}
	if (m_protocol_buf) {
		free(m_protocol_buf);
		m_protocol_buf = NULL;
	}

	sock_clean();
	printf("json server stop now.\n");
}

void CJsonServer::handle_stream_input()
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
		
		parser_request(client_sockfd);
	}

	printf("json server stop listening.\n");
}

int CJsonServer::sock_init()
{
#ifdef WIN32
	WORD version;
	WSADATA wsaData;
	version = MAKEWORD(2, 2);
	if (WSAStartup(version, &wsaData) != 0) {
		printf("CJsonServer sock_init(): windows socket init error\n");
		return -1;
	}
#endif
	return 0;
}

int CJsonServer::sock_clean()
{
#ifdef WIN32
	WSACleanup();
#endif
	return 0;
}

int CJsonServer::init_server()
{
	m_server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (m_server_sockfd == -1) {
		printf("CJsonServer could not create socket\n");
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
		printf("CJsonServer bind socket Failed\n");
		closesocket(m_server_sockfd);
		return ERROR_SOCKET_BIND;
	}

	result = ::listen(m_server_sockfd, 10);
	if (result != 0) {
		printf("CJsonServer listen port:%d failed\n");
		closesocket(m_server_sockfd);
		return ERROR_SOCKET_LISTEN;
	}

	m_listening = true;

	return ERROR_SUCCESS;
}

void CJsonServer::parser_request(int socket)
{
	int recv_length = 0;
	int ret = m_tcp_stream->ReceiveData(socket, m_protocol_buf + recv_length, 1024);
	bool result = strstr(m_protocol_buf, "\r\n\r\n");
	if (result) {
		std::string header = m_protocol_buf;
		header = header.substr(0, header.find("\r\n\r\n", 0));

		std::string tmp = header.substr(header.find("Content-Length:", 0) + strlen("Content-Length:"));
		tmp = tmp.substr(0, tmp.find("\r\n", 0));
		int content_length = ::atoi(tmp.c_str());

		recv_length = ret;
		int expect_length = content_length - (recv_length - header.length()) + 4;
		printf("content_length:%d, expect_length:%d.\n", content_length, expect_length);
		
		while (expect_length) {
			ret = m_tcp_stream->ReceiveData(socket, m_protocol_buf + recv_length, expect_length);
			if ((ret == ConnectionTimedOut) || (ret == ConnectionReset) || (ret == ConnectionClosed)) {
				printf("socket recv error.\n");
				return;
			}
			recv_length += ret;
			expect_length -= ret;
		}

		std::string message = m_protocol_buf;
		printf("message:%s", message.c_str());
	} else {
		printf("message type wrong.\n");
	}
}

std::string CJsonServer::parser_http_head(std::string data)
{
	return NULL;
}

///////////////////////////////////////////////////////////////////////////

#include "Configure.h"

#ifdef TCS_TEST_JSON

#include <windows.h>

int main()
{
	CJsonServer* jsvr = new CJsonServer;
	int ret = jsvr->Init();
	if (ret == ERROR_SUCCESS) {
		jsvr->Start();
	}

	while (true) {
		char input = ' ';
		scanf("%c", &input);

		if (input == 'Q' || input == 'q') {
			break;
		} 
		Sleep(2000);
	}

	if (jsvr) {
		jsvr->Close();
		delete jsvr;
	}

	printf("json exit now.\n");
	return 0;
}

#endif
