/************************************************
* \file MyMd5.h
*
* \author HuZhengdong
* \date 20171020
* ȫ��md5У��
************************************************/
#pragma once
#include <QObject>
#include <QString>
#include <QFile>
#include "UiSingleton.h"

#include "md5.h"

#define  MyMd5Ins MyMd5::Instance()

class DetuPVMS;

class MyMd5 :public QObject, public CUiSingleton<MyMd5>
{
	Q_OBJECT
		friend class CUiSingleton<MyMd5>;
public:
	MyMd5();
	~MyMd5();

	void WriteMd5FromPts(QString pts_path, QString md5_path);							//��pts�ļ���ȡmd5�룬��д��md5.txt
	void WriteMd5FromMemory(unsigned char* source_md5, QString md5_path);							//��pts�ļ���ȡmd5�룬��д��md5.txt

	unsigned char* GetMd5FromPts(QString pts_path);										//��pat.pts��ȡmd5��
	unsigned char* GetMd5FromTxt(QString md5_path);										//��md5.txt��ȡmd5��

	bool CheckMd5(QString pts_path, QString md5_path);				//У��ԭʼmd5������µ�md5��

private:
	DetuPVMS *mainwindow_;

};

