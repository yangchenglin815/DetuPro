#ifdef WIN32
#include <winsock2.h>
#else
#include <netinet/in.h>
#endif
#include "CFL_TcsTranscode.h"

CFLTrancscode::CFLTrancscode()
{
	_cmdType = MODEL_REQUEST;
	_messageHead->nCmd = htons(CMD_DETU_TCS_TRANSCODE);
	_messageHead->nDataLen = htonl(sizeof(api_detu_tcs_transcode_t));

	_messageBody = (api_detu_tcs_transcode_t*)malloc(sizeof(api_detu_tcs_transcode_t));
	memset(_messageBody, 0, sizeof(api_detu_tcs_transcode_t));

	_message = (char*)malloc(sizeof(protocol_head_t) + sizeof(api_detu_tcs_transcode_t));
	memset(_message, 0, sizeof(protocol_head_t) + sizeof(api_detu_tcs_transcode_t));
}

CFLTrancscode::~CFLTrancscode()
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

char* CFLTrancscode::getBody()
{
	return (char*)_messageBody;
}

int CFLTrancscode::getMessageLength()
{
	return (sizeof(protocol_head_t) + sizeof(api_detu_tcs_transcode_t));
}

void CFLTrancscode::generateMessage()
{
	if (_messageHead && _messageBody && _message) {
		memcpy(_message, _messageHead, sizeof(protocol_head_t));
		memcpy(_message + sizeof(protocol_head_t), _messageBody, sizeof(api_detu_tcs_transcode_t));
	}
}


CFLTranscodeResponse::CFLTranscodeResponse()
{
	_cmdType = MODEL_RESPONSE;
	_messageHead->nCmd = htons(CMD_DETU_TCS_TRANSCODE_RES);
	_messageHead->nDataLen = htonl(sizeof(api_detu_tcs_transcode_res_t));

	_messageBody = (api_detu_tcs_transcode_res_t*)malloc(sizeof(api_detu_tcs_transcode_res_t));
	memset(_messageBody, 0, sizeof(api_detu_tcs_transcode_res_t));

	_message = (char*)malloc(sizeof(protocol_head_t) + sizeof(api_detu_tcs_transcode_res_t));
	memset(_message, 0, sizeof(protocol_head_t) + sizeof(api_detu_tcs_transcode_res_t));
}

CFLTranscodeResponse::~CFLTranscodeResponse()
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

char* CFLTranscodeResponse::getBody()
{
	return NULL;
}

int CFLTranscodeResponse::getMessageLength()
{
	return (sizeof(protocol_head_t) + sizeof(api_detu_tcs_transcode_res_t));
}

void CFLTranscodeResponse::generateMessage()
{
	if (_messageHead && _messageBody && _message) {
		memcpy(_message, _messageHead, sizeof(protocol_head_t));
		memcpy(_message + sizeof(protocol_head_t), _messageBody, sizeof(api_detu_tcs_transcode_res_t));
	}
}
