#ifndef _CFL_TCS_TRANSCODE_H_
#define _CFL_TCS_TRANSCODE_H_

#include "CFL_Message.h"

class CFLTrancscode: public CFLMessage
{
public:
	CFLTrancscode();
	virtual ~CFLTrancscode();

public:
	//获取负载数据
	virtual char* getBody();
	//获取消息总长度
	virtual int getMessageLength();
	//生成消息
	virtual void generateMessage();

public:
	api_detu_tcs_transcode_t* _messageBody;
};



class CFLTranscodeResponse: public CFLMessage
{
public:
	CFLTranscodeResponse();
	virtual ~CFLTranscodeResponse();

public:
	//获取负载数据
	virtual char* getBody();
	//获取消息总长度
	virtual int getMessageLength();
	//生成消息
	virtual void generateMessage();

public:
	api_detu_tcs_transcode_res_t* _messageBody;
};

#endif
