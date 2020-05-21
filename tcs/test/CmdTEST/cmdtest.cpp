#include "cmdtest.h"
#include "Platform.h"
#include <string>

#include "CFL_TcsTranscode.h"
#include "CFL_TcsStopTranscode.h"
#include "TcpStream.h"
#include "logging.h"

CmdTEST::CmdTEST(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	m_connect_state = false;
	m_bls_sockfd = -1;
	m_tcp_stream = new CTcpstream;
	m_protocol_buf = (char*)malloc(sizeof(protocol_head_t));
	memset(m_protocol_buf, 0, sizeof(protocol_head_t));

	connect(ui.connect_button, SIGNAL(clicked()), this, SLOT(onConnectBtnClk()));
	connect(ui.start_transcode, SIGNAL(clicked()), this, SLOT(onStartTranscodeBtnClk()));
	connect(ui.stop_transcode, SIGNAL(clicked()), this, SLOT(onStopTranscodeBtnClk()));
	connect(this, SIGNAL(ConnectBtnClkSig()), this, SLOT(onConnectBtnClk()));

	sock_init();
}

CmdTEST::~CmdTEST()
{
	m_connect_state = false;
	if (m_thread && m_thread->joinable()){
		m_thread->join();
	}

	if (m_tcp_stream) {
		delete m_tcp_stream;
		m_tcp_stream = NULL;
	}
	if (m_protocol_buf){
		free(m_protocol_buf);
		m_protocol_buf = NULL;
	}

	sock_clean();
}

void CmdTEST::onConnectBtnClk()
{
	std::string port = ui.lineEdit_server_port->text().toLocal8Bit().data();
	std::string server_ip = ui.lineEdit_server_ip->text().toLocal8Bit().data();

	if (!m_connect_state) {
		m_connect_state = true;
		init_bls_socket(server_ip, port, m_bls_sockfd);

		if (m_thread && m_thread->joinable()){
			m_thread->join();
		}
		m_thread.reset(new std::thread(&CmdTEST::handle_stream_input, this));

		QString name = QStringLiteral("¶Ï¿ª");
		ui.connect_button->setText(name);
	} else {
		m_connect_state = false;
		::shutdown(m_bls_sockfd, SD_BOTH);
		closesocket(m_bls_sockfd);
		m_bls_sockfd = -1;
		if (m_thread && m_thread->joinable()){
			m_thread->join();
		}

		QString name = QStringLiteral("Á¬½Ó");
		ui.connect_button->setText(name);
	}
}

void CmdTEST::onStartTranscodeBtnClk()
{
	std::string device_name = ui.lineEdit_device_name->text().toLocal8Bit().data();
	std::string push_url = ui.lineEdit_push_url->text().toLocal8Bit().data();
	start_transcode(device_name, push_url);
}

void CmdTEST::onStopTranscodeBtnClk()
{
	std::string device_name = ui.lineEdit_device_name->text().toLocal8Bit().data();
	stop_transcode(device_name);
}

int CmdTEST::sock_init(void)
{
	WORD version;
	WSADATA wsaData;
	version = MAKEWORD(2, 2);
	if (WSAStartup(version, &wsaData) != 0) {
		Log::Error("Windows socket init error");
		return -1;
	}
	return 0;
}

int CmdTEST::sock_clean(void)
{
	WSACleanup();
	return 0;
}

int CmdTEST::init_bls_socket(std::string ip, std::string port, int &client_sockfd)
{
	struct addrinfo hints = { 0 }, *ai;
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	int addrret = getaddrinfo(ip.c_str(), port.c_str(), &hints, &ai);
	if (addrret != 0) {
		Log::Error("Problem accessing the DNS. addr:%s:%s", ip.c_str(), port.c_str());
		return -1;
	}

	client_sockfd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
	if (client_sockfd == -1) {
		freeaddrinfo(ai);
		Log::Error("Could not create socket");
		return -1;
	}

	if (::connect(client_sockfd, ai->ai_addr, ai->ai_addrlen) < 0) {
		int err = GetSockError();
		Log::Error("Failed to connect to server,addr:%s:%s, error code:%d(%s)", ip.c_str(), port.c_str(), err, strerror(err));

		freeaddrinfo(ai);
		return -1;
	}

	freeaddrinfo(ai);

	int on = 1;
	setsockopt(client_sockfd, IPPROTO_TCP, TCP_NODELAY, (char *)&on, sizeof(on));

	int cur_sendbuf_size = SEND_BUF_SIZE;
	setsockopt(client_sockfd, SOL_SOCKET, SO_SNDBUF, (const char*)&cur_sendbuf_size, sizeof(int));

	return 0;
}

int CmdTEST::start_transcode(std::string device_name, std::string push_url)
{
	FILE* pts = fopen("pat.pts", "rb+");
	fseek(pts, 0, SEEK_END);
	int size = ftell(pts);
	fseek(pts, 0, SEEK_SET);
	char* buf = (char*)malloc(size);
	fread(buf, 1, size, pts);
	fclose(pts);

	CFLTrancscode* request = new CFLTrancscode;
	memcpy(request->_messageBody->szRtmpURL, push_url.c_str(), API_URL_LENGTH);
	memcpy(request->_messageBody->szDeviceId, device_name.c_str(), API_ARRAY_LEN);
	request->_messageBody->nPtsLen = htonl(size);
	memcpy(request->_messageBody->pts_data, buf, size);
	request->generateMessage();

	if (m_bls_sockfd != -1) {
		m_tcp_stream->SendData(m_bls_sockfd, request->_message, request->getMessageLength());
	}
	return 0;
}

int CmdTEST::stop_transcode(std::string device_name)
{
	CFLStopTranscode* request = new CFLStopTranscode;
	memcpy(request->_messageBody->szDeviceId, device_name.c_str(), API_ARRAY_LEN);
	request->generateMessage();

	if (m_bls_sockfd != -1) {
		m_tcp_stream->SendData(m_bls_sockfd, request->_message, request->getMessageLength());
	}
	return 0;
}

void CmdTEST::handle_stream_input(void)
{
	while (true)
	{
		if (!m_connect_state){
			break;
		}

		int ret = m_tcp_stream->ReceiveData(m_bls_sockfd, m_protocol_buf, sizeof(protocol_head_t));
		if ((ret == ConnectionTimedOut) || (ret == ConnectionReset) || (ret == ConnectionClosed)) {
			::shutdown(m_bls_sockfd, 2);
			closesocket(m_bls_sockfd);
			if (m_connect_state){
				emit ConnectBtnClkSig();
			}
			break;
		}
	}
}
