#ifndef _CFL_TCS_REGISTER_H_
#define _CFL_TCS_REGISTER_H_

#include "CFL_Message.h"

class CFLTcsRegister: public CFLMessage
{
public:
	CFLTcsRegister();
	virtual ~CFLTcsRegister();

public:
	//获取负载数据
	virtual char* getBody();
	//获取消息总长度
	virtual int getMessageLength();
	//生成消息
	virtual void generateMessage();

public:
	api_detu_tcs_register_t* _messageBody;
};



class CFLTcsRegisterResponse: public CFLMessage
{
public:
	CFLTcsRegisterResponse();
	virtual ~CFLTcsRegisterResponse();

public:
	//获取负载数据
	virtual char* getBody();
	//获取消息总长度
	virtual int getMessageLength();
	//生成消息
	virtual void generateMessage();
};

#endif
