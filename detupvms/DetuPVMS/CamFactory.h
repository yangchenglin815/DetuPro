/************************************************
* \file CamFactory.h
*
* \author HuZhengdong
* \date 20170925
* 工厂类，封装工厂
************************************************/
#ifndef CAMFACTORY_H
#define CAMFACTORY_H

#include <stdio.h>
#include "CamProduct.h"

class CamFactory
{
public:
	CamFactory();
	virtual ~CamFactory();

public:
	virtual CamProduct* createProduct() = 0;
};

#endif // CAMFACTORY_H