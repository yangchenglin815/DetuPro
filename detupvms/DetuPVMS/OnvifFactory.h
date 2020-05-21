/************************************************
* \file OnvifFactory.h
*
* \author HuZhengdong
* \date 20170925
* �����࣬Onvif��װ����
************************************************/
#ifndef ONVIFFACTORY_H
#define ONVIFFACTORY_H

#include "CamFactory.h"
#include "OnvifProduct.h"

class OnvifFactory:public CamFactory
{
public:
	OnvifFactory();
	virtual ~OnvifFactory();

public:
	CamProduct* createProduct();
};

#endif // ONVIFFACTORY_H