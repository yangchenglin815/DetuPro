/************************************************
* \file SetAdminMananger.h
*
* \author HuZhengdong
* \date 20180329
* 管理员账户全局宏
************************************************/

#pragma once
#include <iostream>
#include <string>
#include <map>
#include <QObject>
#include <memory>

#include "UiSingleton.h"

#define  SetAdminManangerIns SetAdminMananger::Instance()

class SetAdminMananger : public QObject, public CUiSingleton<SetAdminMananger>
{
	Q_OBJECT
		friend class CUiSingleton<SetAdminMananger>;

public:
	SetAdminMananger();

	void setAdmin(bool is_admin);
	bool getAdmin(){ return is_admin_; };

private:
	bool is_admin_;
};

