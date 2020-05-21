#pragma once

#include <iostream>
#include <string>
#include <map>
#include <memory>

#include <QObject>
#include <QString>

#include "constStruct.h"
#include "UiSingleton.h"

#define  RFIDDataManagerIns RFIDDataManager::Instance()

class RFIDDataManager : public QObject, public CUiSingleton<RFIDDataManager>
{
	Q_OBJECT
		friend class CUiSingleton<RFIDDataManager>;
public:
	RFIDDataManager();

	void AddId(QString id, int type);

signals:
	//通知开门，1进0出
	void SignalToOpenDoor(int in_or_out);
	void SignalToUi(int area, int type);

private:
	//在线数据库结构体列表，包含6个员工的id信息
	std::vector<RFIDOnlineData> online_data_list_;

	//RFID数据库
	std::vector<RFIDData> data_base_list_;
}; 

