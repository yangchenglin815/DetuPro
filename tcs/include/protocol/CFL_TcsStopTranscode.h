#ifndef _CFL_STOP_TRANSCODE_H_
#define _CFL_STOP_TRANSCODE_H_

#include "CFL_Message.h"

class CFLStopTranscode: public CFLMessage
{
public:
	CFLStopTranscode();
	virtual ~CFLStopTranscode();

public:
	//获取负载数据
	virtual char* getBody();
	//获取消息总长度
	virtual int getMessageLength();
	//生成消息
	virtual void generateMessage();

public:
	api_detu_tcs_transcode_stop_t* _messageBody;
};



class CFLStopTranscodeResponse: public CFLMessage
{
public:
	CFLStopTranscodeResponse();
	virtual ~CFLStopTranscodeResponse();

public:
	//获取负载数据
	virtual char* getBody();
	//获取消息总长度
	virtual int getMessageLength();
	//生成消息
	virtual void generateMessage();

public:
	api_detu_tcs_transcode_stop_res_t* _messageBody;
};


#endif