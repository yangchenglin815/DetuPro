#include "RRU2881.h"

#include "RfidReader.h"
#include "logging.hpp"

RFIDReader::RFIDReader() :is_stop_(true)
{
	g_hRRLibrary = LoadLibrary(_T("RRU2881.dll"));

	if (g_hRRLibrary == NULL)
		return ;
	if (!(RR_OpenComPort = (POpenComPort)GetProcAddress(g_hRRLibrary, "OpenComPort")))
		return ;
	if (!(RR_CloseComPort = (PCloseComPort)GetProcAddress(g_hRRLibrary, "CloseComPort")))
		return ;
	if (!(RR_CloseSpecComPort = (PCloseSpecComPort)GetProcAddress(g_hRRLibrary, "CloseSpecComPort")))
		return ;

	if (!(RR_GetReaderInformation = (PGetReaderInformation)GetProcAddress(g_hRRLibrary, "GetReaderInformation")))
		return ;

	if (!(RR_OpenNetPort = (POpenNetPort)GetProcAddress(g_hRRLibrary, "OpenNetPort")))
		return ;
	if (!(RR_CloseNetPort = (PCloseNetPort)GetProcAddress(g_hRRLibrary, "CloseNetPort")))
		return ;

	if (!(RR_Inventory_G2 = (PInventory_G2)GetProcAddress(g_hRRLibrary, "Inventory_G2")))
		return ;

	AntArr_[0] = 1;
	AntArr_[1] = 1;
	AntArr_[2] = 1;
}


RFIDReader::~RFIDReader()
{
}

void RFIDReader::Open()

{
	//InitTcp();
	//Sleep(500);

	CString strip;
	CString str;
	fComAddr_ = 255;
	FrmHandle_ = 0;
	strip = "";

	int port = 27011;
	char ip[15] = "192.168.1.149";
	fcmdRet_ = RR_OpenNetPort(port, ip, &fComAddr_, &FrmHandle_);
	if (fcmdRet_ == 0)
	{
		mutex_stop_.lock();
		is_stop_ = false;
		mutex_stop_.unlock();

		StartRead();
	}


}

void RFIDReader::StartRead()
{
	if (read_data_thread_ && read_data_thread_->joinable())
	{
		read_data_thread_->join();
	}
	read_data_thread_.reset(new boost::thread(&RFIDReader::ReadThreadFunc, this));
}

void RFIDReader::close()
{
	mutex_stop_.lock();
	is_stop_ = true;
	mutex_stop_.unlock();

	Sleep(300);

	FrmHandle_ = 0;
	fcmdRet_ = RR_CloseNetPort(FrmHandle_);	
	if (fcmdRet_ == 0)
	{
		Log::Info("RFIDReader::close failed");
	}
}

void RFIDReader::send()
{
	if (comm_socket_thread_ && comm_socket_thread_->joinable())
	{
		comm_socket_thread_->join();
	}
	comm_socket_thread_.reset(new boost::thread(&RFIDReader::InitTcp, this));

	Sleep(500);
	if (receive_data_thread_ && receive_data_thread_->joinable())
	{
		receive_data_thread_->join();
	}
	receive_data_thread_.reset(new boost::thread(&RFIDReader::receiveData, this));
}

void RFIDReader::InitTcp()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 0), &wsa); //初始化WS2_32.DLL  

	//创建套接字  
	if ((clientsocket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <= 0)
	{
		return;
	}
	serveraddr_.sin_family = AF_INET;
	serveraddr_.sin_port = htons(8087);
	serveraddr_.sin_addr.S_un.S_addr = inet_addr("192.168.8.100");

	//请求连接  
	if (::connect(clientsocket_, (SOCKADDR *)&serveraddr_, sizeof(serveraddr_)) != 0)
	{
		return;
	}

	//接收数据  
	while (1) {

	}
	//关闭套接字  
	closesocket(clientsocket_);
	WSACleanup();    //释放WS2_32.DLL  
}

void RFIDReader::sendData(int ant, char* buf1)
{
	char *bufhead = (char *)"af010018fa";/* (char*)&temp*/;

	char *buf = (char *)malloc(18);
	memset(buf, 0, 18);
	switch (ant) //00门禁，01警告，02权限
	{
	case 128:
	{
				memcpy(buf, "00", 2);
				memcpy(buf + 2, buf1, 16);
				break;
	}
	case 129:
	{
				memcpy(buf, "01", 2);
				memcpy(buf + 2, buf1, 16);
				break;
	}
	case 130:
	{
				memcpy(buf, "02", 2);
				memcpy(buf + 2, buf1, 16);
				break;
	}
	default:
		break;
	}
	printf("发送信息: %s %s\n", bufhead, buf);

	//发送数据  
	if (::send(clientsocket_, (char*)bufhead, 10, 0) <= 0)
	{
		return;
	}
	if (::send(clientsocket_, (char*)buf, 18, 0) <= 0)
	{
		return;
	}
}

void RFIDReader::receiveData()
{
	while (1)
	{
		char *recv_buf;
		recv_buf = (char *)malloc(1024);
		int recv_len = recv(clientsocket_, recv_buf, 1024, 0);

		if (recv_len == 0)
		{
			closesocket(clientsocket_);
			return;
		}
		else if (recv_len > 0)
		{
			char *desp_buf;
			desp_buf = (char *)malloc(recv_len);
			memcpy(desp_buf, recv_buf, recv_len);
			printf("接收来自服务器的信息: %s\n", desp_buf);
			free(desp_buf);
			desp_buf = NULL;
		}
		free(recv_buf);
		recv_buf = NULL;
	}
}

void RFIDReader::InventoryEPC()
{
	BOOL ANTFLAG = FALSE;
	for (int m_index = 0; m_index < 4; m_index++)//遍历4天线
	{
		if (AntArr_[m_index] == 1)
		{
			int ant = 0;
			switch (m_index)
			{
			case 0:
				ant = 0x80;
				break;
			case 1:
				ant = 0x81;
				break;
			case 2:
				ant = 0x82;
				break;
			case 3:
				ant = 0x83;
				break;
			default:
				ant = 0x80;
				break;
			}
			Query(ant);
			ANTFLAG = TRUE;
		}
	}
	if (!ANTFLAG)
	{
		Query(0);
	}
}

void RFIDReader::Query(int Ant)
{
 	unsigned char OutAnt = 0;
	int CardNum = 0;
	int Totallen = 0;
	int EPClen = 0;
	int m = 0;
	unsigned char EPC[20000];
	int CardIndex;
	CString temps, temp, sEPC;
	unsigned char MaskMem = 0;
	unsigned char MaskAdr[2];
	unsigned char MaskLen = 0;
	unsigned char MaskData[100];
	unsigned char MaskFlag = 0;
	unsigned char AdrTID = 0;
	unsigned char LenTID = 0;
	unsigned char TIDFlag = 0;//询查EPC
	unsigned char Target = 0;
	unsigned char Scantime = 20;
	unsigned char FastFlag = 0;
	MaskFlag = 0;
	CardNum = 1;
	unsigned char InAnt = Ant;
	unsigned char Qvalue = 4 /*((CComboBox*)GetDlgItem(IDC_COMBO4))->GetCurSel()*/;
	unsigned char Session =0 /*((CComboBox*)GetDlgItem(IDC_COMBO3))->GetCurSel()*/;
	if (Session == 4)
		Session = 255;
	if (Ant == 0)
	{
		FastFlag = 0;
	}
	else
	{
		FastFlag = 1;
	}
	if (0/*((CButton *)GetDlgItem(IDC_CHECK5))->GetCheck() == 1*/)
	{
		AdrTID = 0;
		LenTID = 6;
		TIDFlag = 1;
	}

	fcmdRet_ = RR_Inventory_G2(&fComAddr_, Qvalue, Session, MaskMem, MaskAdr, MaskLen, MaskData, MaskFlag, AdrTID, LenTID, TIDFlag, Target, InAnt, Scantime, FastFlag, EPC, &OutAnt, &Totallen, &CardNum, FrmHandle_);
	//Log::Info("fcmdRet_ =%d", fcmdRet_);
	if (CardNum > 0)
	{
		Log::Info("CardNum=%d", CardNum);
		m = 1;
		if (CardNum == 0)
		{
			return;
		}
		for (CardIndex = 0; CardIndex < CardNum; CardIndex++)
		{
			temp = _T("");
			temps = _T("");
			BOOL EPCflag = FALSE;
			EPClen = EPC[m - 1];
			byte EPC1[250];
			memcpy(EPC1, &EPC[m], EPClen);
			byte RSSI = EPC[m + EPClen];
			m = m + EPClen + 2;
			//得到标签的EPC号
			for (int n = 0; n < EPClen; n++)
			{
				temp.Format(_T("%02X"), EPC1[n]);
				temps = temps + temp;
			}

			BOOL inList = FALSE;

			Log::Info("Ant: %d", Ant);

			//发送信号到PHP客户端
			USES_CONVERSION;
			char* buf1 = W2A(temps);
			sendData(Ant, buf1);
		}
	}
}

void RFIDReader::ReadThreadFunc()
{
	while (true)
	{
		if (is_stop_)
		{
			return;
		}
		//测试用
		Sleep(100);
		InventoryEPC();
	}
}
