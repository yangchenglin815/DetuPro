/************************************************
* \file MyMd5.h
*
* \author HuZhengdong
* \date 20171020
* 全局md5校验
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

	void WriteMd5FromPts(QString pts_path, QString md5_path);							//从pts文件获取md5码，并写入md5.txt
	void WriteMd5FromMemory(unsigned char* source_md5, QString md5_path);							//从pts文件获取md5码，并写入md5.txt

	unsigned char* GetMd5FromPts(QString pts_path);										//从pat.pts获取md5码
	unsigned char* GetMd5FromTxt(QString md5_path);										//从md5.txt获取md5码

	bool CheckMd5(QString pts_path, QString md5_path);				//校验原始md5码和最新的md5码

private:
	DetuPVMS *mainwindow_;

};

