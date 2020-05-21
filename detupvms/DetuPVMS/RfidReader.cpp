#include "RfidReader.h"

#include "RRU2881.h"
#include "constStruct.h"
#include "feedback.h"

#include "RFIDDataManager.h"

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
	else
	{

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
	Log::Info("fcmdRet_ =%d", fcmdRet_);
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

			QString  temp = QString::fromWCharArray((LPCTSTR)temps, temps.GetLength());

			BOOL inList = FALSE;

			Log::Info("Ant: %d", Ant);

			RFIDDataManagerIns.AddId(temp,Ant);
			//发信号通知播放界面，通知视频画面跳转
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
