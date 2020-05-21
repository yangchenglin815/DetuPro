#pragma once

#include <QObject>

#include <stdio.h>   
#include <windows.h>  

#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>

#include "logging.hpp"

class RFIDReader :public QObject
{
	Q_OBJECT

public:
	RFIDReader();
	~RFIDReader();

public:
	//�򿪶�д��ͨ��
	void Open();
	//�����̶߳�ȡ��ǩ
	void StartRead();
	//�ر�����ͨ��
	void close();

private:
	typedef int(__stdcall *PAutoOpenComPort)(int *port,
		unsigned char *address,
		unsigned char Baud,
		int *Frmhandle);
	typedef int(__stdcall *POpenComPort)(int port,
		unsigned char *address,
		unsigned char Baud,
		int *Frmhandle);
	typedef int(__stdcall *PCloseComPort)();

	typedef int(__stdcall *POpenNetPort)(int Port,
		LPSTR IPaddr,
		unsigned char*ComAdr,
		int *Frmhandle);
	typedef int(__stdcall *PCloseNetPort)(int FrmHandle);

	typedef int(__stdcall *PCloseSpecComPort)(int Frmhandle);

	typedef int(__stdcall *PGetReaderInformation)(unsigned char* ComAdr,				//��д����ַ		
		unsigned char* VersionInfo,			//����汾
		unsigned char* ReaderType,				//��д���ͺ�
		unsigned char* TrType,		//֧�ֵ�Э��
		unsigned char* dmaxfre,           //��ǰ��д��ʹ�õ����Ƶ��
		unsigned char* dminfre,           //��ǰ��д��ʹ�õ����Ƶ��
		unsigned char* powerdBm,             //��д�����������
		unsigned char* ScanTime,
		unsigned char*Ant,
		unsigned char*BeepEn,
		unsigned char*OutputRep,
		unsigned char*CheckAnt,
		int FrmHandle);
	typedef int(__stdcall *PInventory_G2)(unsigned char *address,
		unsigned char QValue,
		unsigned char Session,
		unsigned char MaskMem,
		unsigned char *MaskAdr,
		unsigned char MaskLen,
		unsigned char *MaskData,
		unsigned char MaskFlag,
		unsigned char AdrTID,
		unsigned char LenTID,
		unsigned char TIDFlag,
		unsigned char Target,
		unsigned char InAnt,
		unsigned char Scantime,
		unsigned char FastFlag,
		unsigned char *pEPCList,
		unsigned char *Ant,
		int *Totallen,
		int *CardNum,
		int FrmHandle);




	PAutoOpenComPort        RR_AutoOpenComPort;
	POpenComPort            RR_OpenComPort;
	PCloseComPort           RR_CloseComPort;
	PCloseSpecComPort       RR_CloseSpecComPort;
	POpenNetPort            RR_OpenNetPort;
	PCloseNetPort           RR_CloseNetPort;
	PGetReaderInformation   RR_GetReaderInformation;
	PInventory_G2           RR_Inventory_G2;


private:
	void InventoryEPC();
	void Query(int Ant);

	//���̶߳�ȡ����
	void ReadThreadFunc();
private:

	HINSTANCE g_hRRLibrary;
	bool nFlag_;
	unsigned char AntArr_[4];
	int FrmHandle_;
	int fcmdRet_;
	unsigned char fComAddr_;

	boost::shared_ptr<boost::thread> read_data_thread_;
	boost::mutex mutex_stop_;
	bool is_stop_;
};

