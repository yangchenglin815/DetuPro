/************************************************
* \file HkSdkFactory.h
*
* \author HuZhengdong
* \date 20170925
* �����࣬HKSDK��װ����
************************************************/
#ifndef HKSDKFACTORY_H
#define HKSDKFACTORY_H

#include "CamFactory.h"
#include "HkSdkProduct.h"

class HkSdkFactory:public CamFactory
{
public:
	HkSdkFactory();
	virtual ~HkSdkFactory();

public:
	CamProduct* createProduct();

};

#endif // HKSDKFACTORY_H