#ifndef _CFL_STOP_TRANSCODE_H_
#define _CFL_STOP_TRANSCODE_H_

#include "CFL_Message.h"

class CFLStopTranscode: public CFLMessage
{
public:
	CFLStopTranscode();
	virtual ~CFLStopTranscode();

public:
	//��ȡ��������
	virtual char* getBody();
	//��ȡ��Ϣ�ܳ���
	virtual int getMessageLength();
	//������Ϣ
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
	//��ȡ��������
	virtual char* getBody();
	//��ȡ��Ϣ�ܳ���
	virtual int getMessageLength();
	//������Ϣ
	virtual void generateMessage();

public:
	api_detu_tcs_transcode_stop_res_t* _messageBody;
};


#endif