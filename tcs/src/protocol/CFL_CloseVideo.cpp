#ifdef WIN32
#include <winsock2.h>
#else
#include <netinet/in.h>
#endif
#include "CFL_CloseVideo.h"

CFLCloseVideo::CFLCloseVideo()
{
	_cmdType = MODEL_REQUEST;
	_messageHead->nCmd = htons(CMD_DETU_CLIENT_CLOSE_VIDEO);
	_messageHead->nDataLen = htonl(sizeof(api_detu_client_close_video_t));

	_messageBody = (api_detu_client_close_video_t*)malloc(sizeof(api_detu_client_close_video_t));
	memset(_messageBody, 0, sizeof(api_detu_client_close_video_t));

	_message = (char*)malloc(sizeof(protocol_head_t) + sizeof(api_detu_client_close_video_t));
	memset(_message, 0, sizeof(protocol_head_t) + sizeof(api_detu_client_close_video_t));
}

CFLCloseVideo::~CFLCloseVideo()
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

char* CFLCloseVideo::getBody()
{
	return (char*)_messageBody;
}

int CFLCloseVideo::getMessageLength()
{
	return (sizeof(protocol_head_t) + sizeof(api_detu_client_close_video_t));
}

void CFLCloseVideo::generateMessage()
{
	if (_messageHead && _messageBody && _message) {
		memcpy(_message, _messageHead, sizeof(protocol_head_t));
		memcpy(_message + sizeof(protocol_head_t), _messageBody, sizeof(api_detu_client_close_video_t));
	}
}


CFLCloseVideoResponse::CFLCloseVideoResponse()
{
	_cmdType = MODEL_RESPONSE;
	_messageHead->nCmd = htons(CMD_DETU_CLIENT_CLOSE_VIDEO_RES);
	_messageHead->nDataLen = 0;
	_message = (char*)_messageHead;
}

CFLCloseVideoResponse::~CFLCloseVideoResponse()
{

}

char* CFLCloseVideoResponse::getBody()
{
	return NULL;
}

int CFLCloseVideoResponse::getMessageLength()
{
	return sizeof(protocol_head_t);
}


void CFLCloseVideoResponse::generateMessage()
{
	_message = (char*)_messageHead;
}
