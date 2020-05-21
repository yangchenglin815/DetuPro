#ifdef WIN32
#include <winsock2.h>
#else
#include <netinet/in.h>
#endif
#include "CFL_TcsStopTranscode.h"

CFLStopTranscode::CFLStopTranscode()
{
	_cmdType = MODEL_REQUEST;
	_messageHead->nCmd = htons(CMD_DETU_TCS_TRANSCODE_STOP);
	_messageHead->nDataLen = htonl(sizeof(api_detu_tcs_transcode_stop_t));

	_messageBody = (api_detu_tcs_transcode_stop_t*)malloc(sizeof(api_detu_tcs_transcode_stop_t));
	memset(_messageBody, 0, sizeof(api_detu_tcs_transcode_stop_t));

	_message = (char*)malloc(sizeof(protocol_head_t) + sizeof(api_detu_tcs_transcode_stop_t));
	memset(_message, 0, sizeof(protocol_head_t) + sizeof(api_detu_tcs_transcode_stop_t));
}

CFLStopTranscode::~CFLStopTranscode()
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

char* CFLStopTranscode::getBody()
{
	return (char*)_messageBody;
}

int CFLStopTranscode::getMessageLength()
{
	return (sizeof(protocol_head_t) + sizeof(api_detu_tcs_transcode_stop_t));
}

void CFLStopTranscode::generateMessage()
{
	if (_messageHead && _messageBody && _message) {
		memcpy(_message, _messageHead, sizeof(protocol_head_t));
		memcpy(_message + sizeof(protocol_head_t), _messageBody, sizeof(api_detu_tcs_transcode_stop_t));
	}
}



CFLStopTranscodeResponse::CFLStopTranscodeResponse()
{
	_cmdType = MODEL_RESPONSE;
	_messageHead->nCmd = htons(CMD_DETU_TCS_TRANSCODE_STOP_RES);
	_messageHead->nDataLen = htonl(sizeof(api_detu_tcs_transcode_stop_res_t));

	_messageBody = (api_detu_tcs_transcode_stop_res_t*)malloc(sizeof(api_detu_tcs_transcode_stop_res_t));
	memset(_messageBody, 0, sizeof(api_detu_tcs_transcode_stop_res_t));

	_message = (char*)malloc(sizeof(protocol_head_t) + sizeof(api_detu_tcs_transcode_stop_res_t));
	memset(_message, 0, sizeof(protocol_head_t) + sizeof(api_detu_tcs_transcode_stop_res_t));
}

CFLStopTranscodeResponse::~CFLStopTranscodeResponse()
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

char* CFLStopTranscodeResponse::getBody()
{
	return NULL;
}

int CFLStopTranscodeResponse::getMessageLength()
{
	return (sizeof(protocol_head_t) + sizeof(api_detu_tcs_transcode_stop_res_t));
}


void CFLStopTranscodeResponse::generateMessage()
{
	if (_messageHead && _messageBody && _message) {
		memcpy(_message, _messageHead, sizeof(protocol_head_t));
		memcpy(_message + sizeof(protocol_head_t), _messageBody, sizeof(api_detu_tcs_transcode_stop_res_t));
	}
}
