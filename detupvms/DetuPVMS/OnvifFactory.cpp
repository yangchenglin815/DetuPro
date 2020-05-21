#include "OnvifFactory.h"

OnvifFactory::OnvifFactory()
{
}


OnvifFactory::~OnvifFactory()
{
}

CamProduct* OnvifFactory::createProduct()
{
	CamProduct* temp = NULL;
	temp = new OnvifProduct();
	return temp;
}
