#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <stdio.h>

#include <atlbase.h>
#include <atlconv.h>




#include <tchar.h>

#include "imgProc.h"
#include "logging.hpp"


using namespace std;

imgProc::imgProc()
{
}


imgProc::~imgProc()
{
}

void imgProc::capture()
{
	std::vector<string> list;
	list = GetRtspAddress();

	SHELLEXECUTEINFO sei;
	ZeroMemory(&sei, sizeof(SHELLEXECUTEINFO));//ʹ��ǰ������
	sei.cbSize = sizeof(SHELLEXECUTEINFO);//����ԱȨ��ִ��cmd���������ʹ���� ShellExecute ����
	sei.fMask = SEE_MASK_NOCLOSEPROCESS;
	sei.lpFile = _T("ffmpeg.exe");
	sei.nShow = SW_HIDE;
	sei.hwnd = NULL;
	sei.lpVerb = _T("runas");
	sei.lpDirectory = NULL;
	sei.hInstApp = NULL;

	sei.lpParameters = _T("-i rtsp://192.168.8.31/snl/live/1/1 -y -f image2 -vframes 1 ceshi1.jpg");
	if (ShellExecuteEx(&sei))//ִ�гɹ�
	{
		if (sei.hProcess)//ָ�� SEE_MASK_NOCLOSEPROCESS ����ɹ�ִ�У��� hProcess ���᷵��ִ�гɹ��Ľ��̾��
			WaitForSingleObject(sei.hProcess, INFINITE);//�ȴ�ִ�����
	}

	sei.lpParameters = _T("-i rtsp://192.168.8.32/snl/live/1/1 -y -f image2 -vframes 1 ceshi2.jpg");
	if (ShellExecuteEx(&sei))//ִ�гɹ�
	{
		if (sei.hProcess)//ָ�� SEE_MASK_NOCLOSEPROCESS ����ɹ�ִ�У��� hProcess ���᷵��ִ�гɹ��Ľ��̾��
			WaitForSingleObject(sei.hProcess, INFINITE);//�ȴ�ִ�����
	}
	sei.lpParameters = _T("-i rtsp://192.168.8.33/snl/live/1/1 -y -f image2 -vframes 1 ceshi3.jpg");
	if (ShellExecuteEx(&sei))//ִ�гɹ�
	{
		if (sei.hProcess)//ָ�� SEE_MASK_NOCLOSEPROCESS ����ɹ�ִ�У��� hProcess ���᷵��ִ�гɹ��Ľ��̾��
			WaitForSingleObject(sei.hProcess, INFINITE);//�ȴ�ִ�����
	}
	sei.lpParameters = _T("-i rtsp://192.168.8.34/snl/live/1/1 -y -f image2 -vframes 1 ceshi4.jpg");
	if (ShellExecuteEx(&sei))//ִ�гɹ�
	{
		if (sei.hProcess)//ָ�� SEE_MASK_NOCLOSEPROCESS ����ɹ�ִ�У��� hProcess ���᷵��ִ�гɹ��Ľ��̾��
			WaitForSingleObject(sei.hProcess, INFINITE);//�ȴ�ִ�����
	}
}

std::vector<std::string> imgProc::GetRtspAddress()
{
	USES_CONVERSION;

	ifstream configFile;
	wchar_t buf[256];
	GetModuleFileName(NULL, buf, MAX_PATH);
	char* buf1 = W2A(buf);
	string path;
	string strLine;
	string rtsp_address;
	vector<string> rtsp_address_list;
	rtsp_address_list.resize(0);
	path.assign(buf1);
	path.append("\\..\\ip.ini");
	configFile.open(path.c_str());
	if (configFile.is_open())
	{
		while (!configFile.eof())
		{
			getline(configFile, strLine);
			size_t pos = strLine.find('=');
			string key = strLine.substr(0, pos);


			rtsp_address = strLine.substr(pos + 1);
			rtsp_address_list.push_back(rtsp_address);
		}
	}
	else
	{
		printf("open file failed\n");
		Log::Debug("dem1service:: open file failed\n");
	}
	return rtsp_address_list;
}
