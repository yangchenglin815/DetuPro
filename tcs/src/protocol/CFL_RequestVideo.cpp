#ifdef WIN32
#include <winsock2.h>
#else
#include <netinet/in.h>
#endif
#include "CFL_RequestVideo.h"

CFLRequestVideo::CFLRequestVideo()
{
	_cmdType = MODEL_REQUEST;
	_messageHead->nCmd = htons(CMD_DETU_CLIENT_REQUEST_VIDEO);
	_messageHead->nDataLen = htonl(sizeof(api_detu_client_request_video_t));

	_messageBody = (api_detu_client_request_video_t*)malloc(sizeof(api_detu_client_request_video_t));
	memset(_messageBody, 0, sizeof(api_detu_client_request_video_t));

	_message = (char*)malloc(sizeof(protocol_head_t) + sizeof(api_detu_client_request_video_t));
	memset(_message, 0, sizeof(protocol_head_t) + sizeof(api_detu_client_request_video_t));
}

CFLRequestVideo::~CFLRequestVideo()
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

char* CFLRequestVideo::getBody()
{
	return (char*)_messageBody;
}

int CFLRequestVideo::getMessageLength()
{
	return (sizeof(protocol_head_t) + sizeof(api_detu_client_request_video_t));
}

void CFLRequestVideo::generateMessage()
{
	if (_messageHead && _messageBody && _message) {
		memcpy(_message, _messageHead, sizeof(protocol_head_t));
		memcpy(_message + sizeof(protocol_head_t), _messageBody, sizeof(api_detu_client_request_video_t));
	}
}


CFLRequestVideoResponse::CFLRequestVideoResponse()
{
	_cmdType = MODEL_RESPONSE;
	_messageHead->nCmd = htons(CMD_DETU_CLIENT_REQUEST_VIDEO_RES);
	_messageHead->nDataLen = htonl(sizeof(api_detu_client_request_video_res_t));

	_messageBody = (api_detu_client_request_video_res_t*)malloc(sizeof(api_detu_client_request_video_res_t));
	memset(_messageBody, 0, sizeof(api_detu_client_request_video_res_t));

	_message = (char*)malloc(sizeof(protocol_head_t) + sizeof(api_detu_client_request_video_res_t));
	memset(_message, 0, sizeof(protocol_head_t) + sizeof(api_detu_client_request_video_res_t));
}

CFLRequestVideoResponse::~CFLRequestVideoResponse()
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

char* CFLRequestVideoResponse::getBody()
{
	return (char*)_messageBody;
}

int CFLRequestVideoResponse::getMessageLength()
{
	return (sizeof(protocol_head_t) + sizeof(api_detu_client_request_video_res_t));
}

void CFLRequestVideoResponse::generateMessage()
{
	if (_messageHead && _messageBody && _message) {
		memcpy(_message, _messageHead, sizeof(protocol_head_t));
		memcpy(_message + sizeof(protocol_head_t), _messageBody, sizeof(api_detu_client_request_video_res_t));
	}
}
