#include "CFL_Message.h"

CFLMessage::CFLMessage()
{
	_cmdType = 0;
	_message = NULL;
	_messageHead = (protocol_head_t*)malloc(sizeof(protocol_head_t));
	memset(_messageHead, 0, sizeof(protocol_head_t));
	
	_messageHead->nStartFlags	= 0xAF;
	_messageHead->nVersion		= 0x01;
	_messageHead->deviceNum		= SERVER_TYPE_TCS;
	_messageHead->nEndFlags		= 0xFA;
}

CFLMessage::~CFLMessage()
{
	if (_messageHead) {
		free(_messageHead);
		_messageHead = NULL;
	}
}

int CFLMessage::getCmdType()
{
	return _cmdType;
}

int CFLMessage::getMsgType()
{
	return _messageHead->nCmd;
}

int CFLMessage::getHeadLength()
{
	return sizeof(protocol_head_t);
}

int CFLMessage::getBodyLength()
{
	return _messageHead->nDataLen;
}

int CFLMessage::getMessageLength()
{
	return 0;
}

char* CFLMessage::getBody()
{
	return NULL;
}

char* CFLMessage::getHead()
{
	return (char*)_messageHead;
}

char* CFLMessage::getMessage()
{
	return _message;
}

void CFLMessage::generateMessage()
{
	return;
}
