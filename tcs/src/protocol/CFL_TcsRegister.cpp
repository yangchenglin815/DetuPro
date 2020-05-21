#ifdef WIN32
#include <winsock2.h>
#else
#include <netinet/in.h>
#endif
#include "CFL_TcsRegister.h"

CFLTcsRegister::CFLTcsRegister()
{
	_cmdType = MODEL_REQUEST;
	_messageHead->nCmd = htons(CMD_DETU_TCS_REGISTER);
	_messageHead->nDataLen = htonl(sizeof(api_detu_tcs_register_t));

	_messageBody = (api_detu_tcs_register_t*)malloc(sizeof(api_detu_tcs_register_t));
	memset(_messageBody, 0, sizeof(api_detu_tcs_register_t));

	_message = (char*)malloc(sizeof(protocol_head_t) + sizeof(api_detu_tcs_register_t));
	memset(_message, 0, sizeof(protocol_head_t) + sizeof(api_detu_tcs_register_t));
}

CFLTcsRegister::~CFLTcsRegister()
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

char* CFLTcsRegister::getBody()
{
	return (char*)_messageBody;
}

int CFLTcsRegister::getMessageLength()
{
	return (sizeof(protocol_head_t) + sizeof(api_detu_tcs_register_t));
}

void CFLTcsRegister::generateMessage()
{
	if (_messageHead && _messageBody && _message) {
		memcpy(_message, _messageHead, sizeof(protocol_head_t));
		memcpy(_message + sizeof(protocol_head_t), _messageBody, sizeof(api_detu_tcs_register_t));
	}
}


CFLTcsRegisterResponse::CFLTcsRegisterResponse()
{
	_cmdType = MODEL_RESPONSE;
	_messageHead->nCmd = htons(CMD_DETU_TCS_REGISTER_RES);
	_messageHead->nDataLen = 0;
	_message = (char*)_messageHead;
}

CFLTcsRegisterResponse::~CFLTcsRegisterResponse()
{

}

char* CFLTcsRegisterResponse::getBody()
{
	return NULL;
}

int CFLTcsRegisterResponse::getMessageLength()
{
	return sizeof(protocol_head_t);
}


void CFLTcsRegisterResponse::generateMessage()
{
	_message = (char*)_messageHead;
}
