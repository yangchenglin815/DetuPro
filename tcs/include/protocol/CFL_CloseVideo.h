#ifndef _CFL_CLOSE_VIDEO_H_
#define _CFL_CLOSE_VIDEO_H_

#include "CFL_Message.h"

class CFLCloseVideo: public CFLMessage
{
public:
	CFLCloseVideo();
	virtual ~CFLCloseVideo();

public:
	//��ȡ��������
	virtual char* getBody();
	//��ȡ��Ϣ�ܳ���
	virtual int getMessageLength();
	//������Ϣ
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
	//��ȡ��������
	virtual char* getBody();
	//��ȡ��Ϣ�ܳ���
	virtual int getMessageLength();
	//������Ϣ
	virtual void generateMessage();
};

#endif
