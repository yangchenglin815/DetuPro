#ifndef _CFL_TCS_TRANSCODE_H_
#define _CFL_TCS_TRANSCODE_H_

#include "CFL_Message.h"

class CFLTrancscode: public CFLMessage
{
public:
	CFLTrancscode();
	virtual ~CFLTrancscode();

public:
	//��ȡ��������
	virtual char* getBody();
	//��ȡ��Ϣ�ܳ���
	virtual int getMessageLength();
	//������Ϣ
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
	//��ȡ��������
	virtual char* getBody();
	//��ȡ��Ϣ�ܳ���
	virtual int getMessageLength();
	//������Ϣ
	virtual void generateMessage();

public:
	api_detu_tcs_transcode_res_t* _messageBody;
};

#endif
