#pragma once
#include <iostream>
#include <string>
#include <map>
#include <QObject>
#include <memory>

#include "APIProtocol.h"
#include "UiSingleton.h"

#include "dmconnection.hpp"

using namespace dm::server;

#define  SocketManagerIns SocketManager::Instance()

class DetuPVMS;

class SocketManager :public QObject, public CUiSingleton<SocketManager>
{
	Q_OBJECT
		friend class CUiSingleton<SocketManager>;
private:
	SocketManager();

public:

	void SetCommSocket(dmconnection* conn);		//设置通信socket
	dmconnection* GetCommSocket(){ return comm_conn_; };

	void SetDataSocket(dmconnection* conn);		//设置地图数据传输socket
	dmconnection* GetDataSocket(){ return data_conn_; };

	void SetMainWindow(DetuPVMS* main_window);

	void setIsConnected(bool is_onnected);
	bool isConnected(){ return is_connected_; };
signals:


private:

	DetuPVMS *mainwindow_;

	dmconnection *comm_conn_;
	dmconnection *data_conn_;

	bool is_connected_ = false;
};
