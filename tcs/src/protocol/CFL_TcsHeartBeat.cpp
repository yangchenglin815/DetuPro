#ifdef WIN32
#include <winsock2.h>
#else
#include <netinet/in.h>
#endif
#include "CFL_TcsHeartBeat.h"

CFLHeartBeat::CFLHeartBeat()
{
	_cmdType = MODEL_REQUEST;
	_messageHead->nCmd = htons(CMD_DETU_TCS_HEARTBEAT);
	_messageHead->nDataLen = htonl(sizeof(api_detu_tcs_heartbeat_t));

	_messageBody = (api_detu_tcs_heartbeat_t*)malloc(sizeof(api_detu_tcs_heartbeat_t));
	memset(_messageBody, 0, sizeof(api_detu_tcs_heartbeat_t));

	_message = (char*)malloc(sizeof(protocol_head_t) + sizeof(api_detu_tcs_heartbeat_t));
	memset(_message, 0, sizeof(protocol_head_t) + sizeof(api_detu_tcs_heartbeat_t));
}

CFLHeartBeat::~CFLHeartBeat()
{
	if (_messageBody) {
		free(_messageBody);
		_messageBody = NULL;
	}
	if (_message) {
		free(_message);
		_message = NULL;
	}
}

char* CFLHeartBeat::getBody()
{
	return (char*)_messageBody;
}

int CFLHeartBeat::getMessageLength()
{
	return (sizeof(protocol_head_t) + sizeof(api_detu_tcs_heartbeat_t));
}

void CFLHeartBeat::generateMessage()
{
	if (_messageHead && _messageBody && _message) {
		memcpy(_message, _messageHead, sizeof(protocol_head_t));
		memcpy(_message + sizeof(protocol_head_t), _messageBody, sizeof(api_detu_tcs_heartbeat_t));
	}
}



CFLHeartBeatResponse::CFLHeartBeatResponse()
{
	_cmdType = MODEL_RESPONSE;
	_messageHead->nCmd = htons(CMD_DETU_TCS_HEARTBEAT_RES);
	_messageHead->nDataLen = 0;
	_message = (char*)_messageHead;
}

CFLHeartBeatResponse::~CFLHeartBeatResponse()
{

}

char* CFLHeartBeatResponse::getBody()
{
	return NULL;
}

int CFLHeartBeatResponse::getMessageLength()
{
	return sizeof(protocol_head_t);
}


void CFLHeartBeatResponse::generateMessage()
{
	_message = (char*)_messageHead;
}
