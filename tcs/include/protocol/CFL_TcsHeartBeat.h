#ifndef _CFL_HEART_BEAT_H_
#define _CFL_HEART_BEAT_H_

#include "CFL_Message.h"

class CFLHeartBeat: public CFLMessage
{
public:
	CFLHeartBeat();
	virtual ~CFLHeartBeat();

public:
	//获取负载数据
	virtual char* getBody();
	//获取消息总长度
	virtual int getMessageLength();
	//生成消息
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
	//获取负载数据
	virtual char* getBody();
	//获取消息总长度
	virtual int getMessageLength();
	//生成消息
	virtual void generateMessage();
};

#endif
