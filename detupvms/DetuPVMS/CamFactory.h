/************************************************
* \file CamFactory.h
*
* \author HuZhengdong
* \date 20170925
* �����࣬��װ����
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