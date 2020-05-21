#ifndef _CFL_MESSAGE_H_
#define _CFL_MESSAGE_H_

#include "APIProtocol.h"

//命令类型
enum{
	MODEL_RESPONSE = 1,		// 请求消息
	MODEL_REQUEST,			// 响应消息
};

class CFLMessage
{
public:
	CFLMessage();
	virtual ~CFLMessage();

public:
	//获取命令类型
	virtual int getCmdType();
	//获得消息类型
	virtual int getMsgType();
	//获取消息头长度
	virtual int getHeadLength();
	//获取负载长度
	virtual int getBodyLength();
	//获取消息总长度
	virtual int getMessageLength();
	//获取负载数据
	virtual char* getBody();
	//获取消息头数据
	virtual char* getHead();
	//获取消息
	virtual char* getMessage();
	//生成消息
	virtual void generateMessage();

public:
	int					_cmdType;
	char*				_message;
	protocol_head_t*	_messageHead;
};

#endif
