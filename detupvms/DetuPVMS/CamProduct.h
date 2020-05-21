/************************************************
* \file CamProduct.h
*
* \author HuZhengdong
* \date 20170925
* 工厂类，封装产品
************************************************/
#ifndef CAMPRODUCT_H
#define CAMPRODUCT_H

#include <QString>

#include "GeneralDef.h"
#include "logging.hpp"
#include "constStruct.h"

class CamProduct
{
public:
	CamProduct();
	virtual ~CamProduct();

public:
	virtual bool Login(QString Ip, int port, QString user, QString passwd) = 0;
	virtual void SetCfg(HWND PlayWnd) = 0;
	virtual bool Play() = 0;
	virtual bool Contral(int index) = 0;
	virtual bool Close() = 0;
};

#endif // CAMPRODUCT_H