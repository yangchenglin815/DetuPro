#ifndef _CFL_REQUEST_VIDEO_H_
#define _CFL_REQUEST_VIDEO_H_

#include "CFL_Message.h"

class CFLRequestVideo: public CFLMessage
{
public:
	CFLRequestVideo();
	virtual ~CFLRequestVideo();

public:
	//获取负载数据
	virtual char* getBody();
	//获取消息总长度
	virtual int getMessageLength();
	//生成消息
	virtual void generateMessage();

public:
	api_detu_client_request_video_t* _messageBody;
};



class CFLRequestVideoResponse: public CFLMessage
{
public:
	CFLRequestVideoResponse();
	virtual ~CFLRequestVideoResponse();

public:
	//获取负载数据
	virtual char* getBody();
	//获取消息总长度
	virtual int getMessageLength();
	//生成消息
	virtual void generateMessage();

public:
	api_detu_client_request_video_res_t* _messageBody;
};

#endif
