#ifndef _CFL_REQUEST_VIDEO_H_
#define _CFL_REQUEST_VIDEO_H_

#include "CFL_Message.h"

class CFLRequestVideo: public CFLMessage
{
public:
	CFLRequestVideo();
	virtual ~CFLRequestVideo();

public:
	//��ȡ��������
	virtual char* getBody();
	//��ȡ��Ϣ�ܳ���
	virtual int getMessageLength();
	//������Ϣ
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
	//��ȡ��������
	virtual char* getBody();
	//��ȡ��Ϣ�ܳ���
	virtual int getMessageLength();
	//������Ϣ
	virtual void generateMessage();

public:
	api_detu_client_request_video_res_t* _messageBody;
};

#endif
