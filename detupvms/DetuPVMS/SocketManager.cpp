#include "SocketManager.h"


SocketManager::SocketManager() :
	comm_conn_(NULL), 
	data_conn_(NULL)
{
}

void SocketManager::SetCommSocket(dmconnection* conn)
{
	comm_conn_ = conn;
}

void SocketManager::SetDataSocket(dmconnection* conn)
{
	data_conn_ = conn;
}

void SocketManager::SetMainWindow(DetuPVMS* main_window)
{
	mainwindow_ = main_window;
}

void SocketManager::setIsConnected(bool is_onnected)
{
	is_connected_ = is_onnected;
}

