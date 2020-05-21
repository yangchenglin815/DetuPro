#ifndef _CFL_TCS_REGISTER_H_
#define _CFL_TCS_REGISTER_H_

#include "CFL_Message.h"

class CFLTcsRegister: public CFLMessage
{
public:
	CFLTcsRegister();
	virtual ~CFLTcsRegister();

public:
	//��ȡ��������
	virtual char* getBody();
	//��ȡ��Ϣ�ܳ���
	virtual int getMessageLength();
	//������Ϣ
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
	//��ȡ��������
	virtual char* getBody();
	//��ȡ��Ϣ�ܳ���
	virtual int getMessageLength();
	//������Ϣ
	virtual void generateMessage();
};

#endif
