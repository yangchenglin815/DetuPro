#ifndef _TCS_PROTOCOL_PARSER_H_
#define _TCS_PROTOCOL_PARSER_H_

#include "CFL_Message.h"


typedef enum
{
	Pdu_Error_Parse_Failed = 1, //解析失败
	Pdu_Error_Buf_Full,			//缓冲满
	Pdu_Error_Buf_Lack,			//包不完整
	Pdu_Error_Buf_Allocate,		//动态分配缓存失败
}EnumPduError;

class ICmdListener;

class CFLCmdParser
{
public:
	CFLCmdParser(ICmdListener* listener);
	~CFLCmdParser();

	int parse(int conn_id, const char* data, int len);

private:
	unsigned char	read_1bytes(char* &ptr);
	unsigned short	read_2bytes(char* &ptr);
	unsigned int	read_4bytes(char* &ptr);
	void			read_bytes(char* &ptr, char* data, int size);
	void			skip(char* &ptr, int size);

private:
	void handle_register_response(int type, int conn_id, const char* data, int len);
	void handle_heartbeat_response(int type, int conn_id, const char* data, int len);
	void handle_request_video_response(int type, int conn_id, const char* data, int len);
	void handle_close_video_response(int type, int conn_id, const char* data, int len);
	void handle_transcode_request(int type, int conn_id, const char* data, int len);
	void handle_stop_transcode_request(int type, int conn_id, const char* data, int len);

public:
	ICmdListener*	m_listener;
};

class ICmdListener
{
public:
	ICmdListener(){}
	virtual ~ICmdListener(){}
public:
	virtual void onPDU(int conn_id, CFLMessage* pdu) {}
};

#endif
