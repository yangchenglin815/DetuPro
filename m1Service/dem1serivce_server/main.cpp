#include <iostream>

#include "tcpserver.hpp"
#include "APIProtocol.h"
#include "setip.h"
#include "dump.h"
#include "sqliteManage.h"
#include "PTZManageTemplate.h"

#include "KillExe.h"
#include "../rfiddispatcher/RFIDReader.h"
#include "../imgproc/imgProc.h"

using namespace std;

KillExe kill_exe_;
RFIDReader rfid_reader_;
imgProc img_proc_;

void server_tcpserver()
{
	std::unique_ptr<dem1::server::tcpserver> s;

	string server_ip = ConfigFileRead("server");
	string port = ConfigFileRead("port");
	Log::Info("Server_IP: %s Port: %s\n", server_ip.c_str(), port.c_str());

	SQLITE3Manage.initDataBase();
	s.reset(new dem1::server::tcpserver(server_ip, port));
	s->run();


}

void rfid_reader()
{
	rfid_reader_.Open();
	rfid_reader_.send(); 
}

void img_proc()
{
	img_proc_.capture();
}

void main()
{
	kill_exe_.KillProcess(_T("dem1serivce_server.exe"));
	Sleep(500);

	//system("mode con cols=130 lines=30");//�ı���
	//system("color fc");//�ı���ɫ

	char  buf[256];
	GetModuleFileName(NULL, (TCHAR*)buf, MAX_PATH);
	string path;
	path.assign(buf);
	path.append("\\..\\log.txt");
	Log::Initialise(path);
	Log::SetThreshold(Log::LOG_TYPE_DEBUG);


	//********************************����dump�ļ�**************************//
	EnableAutoDump();

	//********************************����ͨ�ŷ�����**************************//
	boost::shared_ptr<boost::thread> server_thread_;
	if (server_thread_ && server_thread_->joinable())
	{
		server_thread_->join();
	}
	server_thread_.reset(new boost::thread(&server_tcpserver));



	// ********************************����RFID������************************** //
	boost::shared_ptr<boost::thread> rfid_thread_;
	if (rfid_thread_ && rfid_thread_->joinable())
	{
		rfid_thread_->join();
	}
	rfid_thread_.reset(new boost::thread(&rfid_reader));

/*
	// ********************************������ʱ��ͼ���ͼ���Ƿ��ƶ�************************** //
	boost::shared_ptr<boost::thread> img_thread_;
	if (img_thread_ && img_thread_->joinable())
	{
		img_thread_->join();
	}
	img_thread_.reset(new boost::thread(&img_proc));

*/
	while (1)
	{

	}

	Log::Finalise();
}