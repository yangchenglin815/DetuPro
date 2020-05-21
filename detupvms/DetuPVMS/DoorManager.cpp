#include "DoorManager.h"

#include <WINSOCK2.H>

#include <iostream>

#include <string>
#include <conio.h>

#include "door/FC8800frame.h"
#include "door/FC8800frameCompile.h"

#include "RFIDDataManager.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

DoorManager::DoorManager()
{

	connect(&RFIDDataManagerIns, SIGNAL(SignalToOpenDoor(int)), this, SLOT(slotOnOpenDoor(int)));

}


DoorManager::~DoorManager()
{
}

void DoorManager::slotOnOpenDoor(int in_or_out)
{
	openDoor(in_or_out);
}

void DoorManager::openDoor(int in_or_out)
{
	SOCKET clientsocket;
	SOCKADDR_IN serveraddr;
	SOCKADDR_IN clientaddr;

	char *sn = (char*)"YC-3224T27115438";
	BYTE *password = (BYTE*)"FFFFFFFF";
	int isize;
	int isize1;
	password = Hex2Byte((char*)password, 8, &isize);

	BYTE data[4];
	UINT len = 0;
	if (1)
	{
		data[0] = 0; //进门
		data[1] = 1;
	}
	else
	{
		data[0] = 1; //出门
		data[1] = 0;
	}
	data[2] = 0;
	data[3] = 0;


	FC8800frame frame;
	IniFrame(&frame);
	frame = CreateFrame(sn, password, 15, 3, 3, 0, 4, data, 4);
	char *buf1 = Byte2Hex(frame.Frame, frame.Framesize);
	std::string temp = "7E0000000046432D38383230413233313030303038FFFFFFFF3102000000001046432D38383230413433303630303232F07E";
	char *buf = (char *)Hex2Byte(buf1, temp.size(), &isize1);

	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 0), &wsa); //初始化WS2_32.DLL  

	//创建套接字  
	if ((clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <= 0)
	{
		return;
	}
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(8000);
	serveraddr.sin_addr.S_un.S_addr = inet_addr("192.168.1.150");

	//请求连接  
	if (::connect(clientsocket, (SOCKADDR *)&serveraddr, sizeof(serveraddr)) != 0)
	{
		return;
	}
	int  len1 = strlen(buf) + 1;
	//发送数据  
	if (send(clientsocket, (char*)buf, 38, 0) <= 0)
	{
		return;
	}
	//接收数据  
	while (1) {
		if (recv(clientsocket, buf, 1024, 0) <= 0)
		{
			closesocket(clientsocket);
			return;
		}
		printf("接收来自服务器的信息: %s\n", buf);
		break;
	}
	//关闭套接字  
	closesocket(clientsocket);
	WSACleanup();    //释放WS2_32.DLL  
	return;
}
