#include "ProtocolParser.h"
#include "APIProtocol.h"
#include "logging.h"
#include <assert.h>

#include "CFL_RequestVideo.h"
#include "CFL_CloseVideo.h"
#include "CFL_TcsHeartBeat.h"
#include "CFL_TcsRegister.h"
#include "CFL_TcsTranscode.h"
#include "CFL_TcsStopTranscode.h"

CFLCmdParser::CFLCmdParser(ICmdListener* listener)
{
	m_listener = listener;
}

CFLCmdParser::~CFLCmdParser()
{

}

int CFLCmdParser::parse(int conn_id, const char* data, int len)
{
	assert(len >= 4);

	char* read_ptr = (char*)data;
	skip(read_ptr, 2);
	unsigned short cmd_type = read_2bytes(read_ptr);
	switch (cmd_type)
	{
	case CMD_DETU_TCS_REGISTER_RES:
		handle_register_response(cmd_type, conn_id, data, len);
		break;
	case CMD_DETU_TCS_HEARTBEAT_RES:
		handle_heartbeat_response(cmd_type, conn_id, data, len);
		break;
	case CMD_DETU_CLIENT_REQUEST_VIDEO_RES:
		handle_request_video_response(cmd_type, conn_id, data, len);
		break;
	case CMD_DETU_CLIENT_CLOSE_VIDEO_RES:
		handle_close_video_response(cmd_type, conn_id, data, len);
		break;
	case CMD_DETU_TCS_TRANSCODE:
		handle_transcode_request(cmd_type, conn_id, data, len);
		break;
	case CMD_DETU_TCS_TRANSCODE_STOP:
		handle_stop_transcode_request(cmd_type, conn_id, data, len);
		break;
	default:
		Log::Error("CFLCmdParser unknow message type:%d, length:%d, socket:%d", cmd_type, len, conn_id);
		return Pdu_Error_Parse_Failed;
	}

	return 0;
}

unsigned char CFLCmdParser::read_1bytes(char* &ptr)
{
	return (unsigned char)*ptr++;
}

unsigned short CFLCmdParser::read_2bytes(char* &ptr)
{
	unsigned short value;
	char* pp = (char*)&value;
	pp[1] = *ptr++;
	pp[0] = *ptr++;

	return value;
}

unsigned int CFLCmdParser::read_4bytes(char* &ptr)
{
	unsigned int value = 0;
	char* pp = (char*)&value;
	pp[3] = *ptr++;
	pp[2] = *ptr++;
	pp[1] = *ptr++;
	pp[0] = *ptr++;

	return value;
}

void CFLCmdParser::read_bytes(char* &ptr, char* data, int size)
{
	memcpy(data, ptr, size);
	ptr += size;

	return;
}

void CFLCmdParser::skip(char* &ptr, int size)
{
	ptr += size;
	return;
}

void CFLCmdParser::handle_register_response(int type, int conn_id, const char* data, int len)
{
	assert(len >= sizeof(protocol_head_t));

	char* ptr = (char*)data;
	skip(ptr, 8);

	CFLTcsRegisterResponse* response = new CFLTcsRegisterResponse;
	response->_messageHead->nCmd = type;
	response->_messageHead->nResult = read_2bytes(ptr);
	response->_messageHead->nM1Id = read_1bytes(ptr);
	response->_messageHead->nStreamId = read_1bytes(ptr);


	m_listener->onPDU(conn_id, response);
	delete response;
}

void CFLCmdParser::handle_heartbeat_response(int type, int conn_id, const char* data, int len)
{
	assert(len >= sizeof(protocol_head_t));

	char* ptr = (char*)data;
	skip(ptr, 8);

	CFLHeartBeatResponse* response = new CFLHeartBeatResponse;
	response->_messageHead->nCmd = type;
	response->_messageHead->nResult = read_2bytes(ptr);
	response->_messageHead->nM1Id = read_1bytes(ptr);
	response->_messageHead->nStreamId = read_1bytes(ptr);

	m_listener->onPDU(conn_id, response);
	delete response;
}

void CFLCmdParser::handle_request_video_response(int type, int conn_id, const char* data, int len)
{
	int message_length = sizeof(protocol_head_t) + sizeof(api_detu_client_request_video_res_t);

	assert(len >= message_length);

	char* ptr = (char*)data;
	skip(ptr, 8);

	CFLRequestVideoResponse* response = new CFLRequestVideoResponse;
	response->_messageHead->nCmd = type;
	response->_messageHead->nResult = read_2bytes(ptr);
	response->_messageHead->nM1Id = read_1bytes(ptr);
	response->_messageHead->nStreamId = read_1bytes(ptr);

	skip(ptr, 2);
	read_bytes(ptr, (char*)response->_messageBody->szDeviceId, API_ARRAY_LEN);
	read_bytes(ptr, (char*)response->_messageBody->szRtmpURL, API_RTMP_LEN);

	m_listener->onPDU(conn_id, response);
	delete response;
}

void CFLCmdParser::handle_close_video_response(int type, int conn_id, const char* data, int len)
{
	assert(len >= sizeof(protocol_head_t));

	char* ptr = (char*)data;
	skip(ptr, 8);

	CFLCloseVideoResponse* response = new CFLCloseVideoResponse;
	response->_messageHead->nCmd = type;
	response->_messageHead->nResult = read_2bytes(ptr);
	response->_messageHead->nM1Id = read_1bytes(ptr);
	response->_messageHead->nStreamId = read_1bytes(ptr);

	m_listener->onPDU(conn_id, response);
	delete response;
}

void CFLCmdParser::handle_transcode_request(int type, int conn_id, const char* data, int len)
{
	int message_length = sizeof(protocol_head_t) + sizeof(api_detu_tcs_transcode_t);

	assert(len >= message_length);

	char* ptr = (char*)data;
	skip(ptr, 8);

	CFLTrancscode* response = new CFLTrancscode;
	response->_messageHead->nCmd = type;
	response->_messageHead->nResult = read_2bytes(ptr);
	response->_messageHead->nM1Id = read_1bytes(ptr);
	response->_messageHead->nStreamId = read_1bytes(ptr);
	skip(ptr, 2);
	read_bytes(ptr, (char*)response->_messageBody->szRtmpURL, API_URL_LENGTH);
	read_bytes(ptr, (char*)response->_messageBody->szDeviceId, API_ARRAY_LEN);
	response->_messageBody->nDeviceId = read_1bytes(ptr);
	response->_messageBody->nStreamType = read_1bytes(ptr);
	response->_messageBody->nFps = read_1bytes(ptr);
	response->_messageBody->nbitrate = read_4bytes(ptr);
	response->_messageBody->nWidth = read_4bytes(ptr);
	response->_messageBody->nHeight = read_4bytes(ptr);
	response->_messageBody->nStartTime = read_4bytes(ptr);
	response->_messageBody->nEndTime = read_4bytes(ptr);
	response->_messageBody->nPtsLen = read_4bytes(ptr);
	read_bytes(ptr, (char*)response->_messageBody->pts_data, API_PTS_LEN);

	m_listener->onPDU(conn_id, response);
	delete response;
}

void CFLCmdParser::handle_stop_transcode_request(int type, int conn_id, const char* data, int len)
{
	int message_length = sizeof(protocol_head_t) + sizeof(api_detu_tcs_transcode_stop_t);

	assert(len >= message_length);

	char* ptr = (char*)data;
	skip(ptr, 8);

	CFLStopTranscode* response = new CFLStopTranscode;
	response->_messageHead->nCmd = type;
	response->_messageHead->nResult = read_2bytes(ptr);
	response->_messageHead->nM1Id = read_1bytes(ptr);
	response->_messageHead->nStreamId = read_1bytes(ptr);
	skip(ptr, 2);
	read_bytes(ptr, (char*)response->_messageBody->szDeviceId, API_ARRAY_LEN);

	m_listener->onPDU(conn_id, response);
	delete response;
}
