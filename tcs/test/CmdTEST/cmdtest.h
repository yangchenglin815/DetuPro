#ifndef CMDTEST_H
#define CMDTEST_H

#include <QtWidgets/QMainWindow>
#include <memory>
#include <thread>
#include "ui_cmdtest.h"

#define RECV_TIME_OUT 60
#define SEND_TIME_OUT	RECV_TIME_OUT
#define SEND_BUF_SIZE 4096

class CTcpstream;

class CmdTEST : public QMainWindow
{
	Q_OBJECT

public:
	CmdTEST(QWidget *parent = 0);
	~CmdTEST();

public slots:
	void onConnectBtnClk();
	void onStartTranscodeBtnClk();
	void onStopTranscodeBtnClk();

signals:
	void ConnectBtnClkSig();

private:
	int sock_init();
	int sock_clean();

	int init_bls_socket(std::string ip, std::string port, int &client_sockfd);
	int start_transcode(std::string device_name, std::string push_url);
	int stop_transcode(std::string device_name);

	void handle_stream_input(void);

private:
	Ui::CmdTESTClass ui;

private:
	bool m_connect_state;
	int  m_bls_sockfd;
	char*		m_protocol_buf;
	CTcpstream*	m_tcp_stream;
	std::shared_ptr<std::thread>	m_thread;
};

#endif // CMDTEST_H
