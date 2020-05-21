#ifndef _CFL_CLOSE_VIDEO_H_
#define _CFL_CLOSE_VIDEO_H_

#include "CFL_Message.h"

class CFLCloseVideo: public CFLMessage
{
public:
	CFLCloseVideo();
	virtual ~CFLCloseVideo();

public:
	//获取负载数据
	virtual char* getBody();
	//获取消息总长度
	virtual int getMessageLength();
	//生成消息
	virtual void generateMessage();

public:
	api_detu_client_close_video_t* _messageBody;
};



class CFLCloseVideoResponse: public CFLMessage
{
public:
	CFLCloseVideoResponse();
	virtual ~CFLCloseVideoResponse();

public:
	//获取负载数据
	virtual char* getBody();
	//获取消息总长度
	virtual int getMessageLength();
	//生成消息
	virtual void generateMessage();
};

#endif
