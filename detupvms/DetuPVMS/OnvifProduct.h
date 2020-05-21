/************************************************
* \file OnvifProduct.h
*
* \author HuZhengdong
* \date 20170925
* 工厂类，Onvif封装产品
************************************************/
#ifndef ONVIFPRODUCT_H
#define ONVIFPRODUCT_H

#include "CamProduct.h"

class OnvifProduct:public CamProduct
{
public:
	OnvifProduct();
	virtual ~OnvifProduct();

public:
	bool Login(QString Ip, int port, QString user, QString passwd);
	void SetCfg(HWND PlayWnd);
	bool Play();
	bool Contral(int index);
	bool Close();

};

#endif // ONVIFPRODUCT_H