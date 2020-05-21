#ifndef _CFL_MESSAGE_H_
#define _CFL_MESSAGE_H_

#include "APIProtocol.h"

//��������
enum{
	MODEL_RESPONSE = 1,		// ������Ϣ
	MODEL_REQUEST,			// ��Ӧ��Ϣ
};

class CFLMessage
{
public:
	CFLMessage();
	virtual ~CFLMessage();

public:
	//��ȡ��������
	virtual int getCmdType();
	//�����Ϣ����
	virtual int getMsgType();
	//��ȡ��Ϣͷ����
	virtual int getHeadLength();
	//��ȡ���س���
	virtual int getBodyLength();
	//��ȡ��Ϣ�ܳ���
	virtual int getMessageLength();
	//��ȡ��������
	virtual char* getBody();
	//��ȡ��Ϣͷ����
	virtual char* getHead();
	//��ȡ��Ϣ
	virtual char* getMessage();
	//������Ϣ
	virtual void generateMessage();

public:
	int					_cmdType;
	char*				_message;
	protocol_head_t*	_messageHead;
};

#endif
