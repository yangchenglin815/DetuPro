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
	//֪ͨ���ţ�1��0��
	void SignalToOpenDoor(int in_or_out);
	void SignalToUi(int area, int type);

private:
	//�������ݿ�ṹ���б�����6��Ա����id��Ϣ
	std::vector<RFIDOnlineData> online_data_list_;

	//RFID���ݿ�
	std::vector<RFIDData> data_base_list_;
}; 

