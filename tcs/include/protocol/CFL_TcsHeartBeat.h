#ifndef _CFL_HEART_BEAT_H_
#define _CFL_HEART_BEAT_H_

#include "CFL_Message.h"

class CFLHeartBeat: public CFLMessage
{
public:
	CFLHeartBeat();
	virtual ~CFLHeartBeat();

public:
	//��ȡ��������
	virtual char* getBody();
	//��ȡ��Ϣ�ܳ���
	virtual int getMessageLength();
	//������Ϣ
	virtual void generateMessage();

public:
	api_detu_tcs_heartbeat_t* _messageBody;
};



class CFLHeartBeatResponse : public CFLMessage
{
public:
	CFLHeartBeatResponse();
	virtual ~CFLHeartBeatResponse();

public:
	//��ȡ��������
	virtual char* getBody();
	//��ȡ��Ϣ�ܳ���
	virtual int getMessageLength();
	//������Ϣ
	virtual void generateMessage();
};

#endif
