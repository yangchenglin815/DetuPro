#include "Platform.h"
#include "Config.h"
#include "Error.h"
#include "TcsGlobal.h"
#include "TcpStream.h"
#include "TcsLiveSvr.h"
#include "TcsLiveChannel.h"
#include "TcsSvrSession.h"
#include "logging.h"

#include "CFL_RequestVideo.h"
#include "CFL_CloseVideo.h"
#include "CFL_TcsTranscode.h"
#include "CFL_TcsStopTranscode.h"

#include <assert.h>

CSvrSession::CSvrSession()
{
	m_closed = false;
	m_is_pts_new = false;
	m_socket = -1;
	m_config = NULL;
	m_tcp_stream = NULL;
	m_parser = NULL;
	m_live_svr = NULL;
	m_live_channel = NULL;
	m_protocol_buf = (char*)malloc(MAX_SOCKET_BUFFER_LENGTH);
	memset(m_protocol_buf, 0, MAX_SOCKET_BUFFER_LENGTH);
}

CSvrSession::~CSvrSession()
{

}

void CSvrSession::onPDU(int conn_id, CFLMessage* pdu)
{
	int message_type = pdu->_messageHead->nCmd;
	switch (message_type)
	{
	case CMD_DETU_TCS_TRANSCODE:
		handle_transcode_request(conn_id, pdu);
		break;
	case CMD_DETU_TCS_TRANSCODE_STOP:
		handle_stop_transcode_request(conn_id, pdu);
		break;
	default:
		Log::Error("CSvrSession unknow message type:%d from cu.", message_type);
	}
}

void CSvrSession::onMessage(long session_id, int message_type)
{
	switch (message_type)
	{
	case ERROR_TRANSCODE_PLAYER_ERROR:
		Log::Info("live channel error(play error), devide name:%s", m_transcode_param.device_name.c_str());
		handle_stop_video_request(m_transcode_param.device_name, RESUKT_PULL_RTMP_ERROR);
		Notify(m_owner, GetID(), ERROR_SESSION_CLOSED);
		break;
	case ERROR_TRANSCODE_PUBLISH:
		Log::Info("live channel error(publish error), devide name:%s", m_transcode_param.device_name.c_str());
		handle_stop_video_request(m_transcode_param.device_name, RESULT_PUSH_RTMP_ERROR);
		Notify(m_owner, GetID(), ERROR_SESSION_CLOSED);
		break;
	default:
		break;
	}
}

int CSvrSession::Init(int fd, char* pre_buf, int length)
{
	m_tcp_stream = new CTcpstream;
	m_parser = new CFLCmdParser(this);

	m_socket = fd;
	memcpy(m_protocol_buf, pre_buf, length);

	int ret = 0;                              
	int recv_length = sizeof(protocol_head_t);
	int body_length = get_body_length(m_protocol_buf, recv_length);
	while (body_length) {
		ret = m_tcp_stream->ReceiveData(m_socket, m_protocol_buf + recv_length, 1024);
		if ((ret == ConnectionTimedOut) || (ret == ConnectionReset) || (ret == ConnectionClosed)) {
			close_invalid_socket(m_socket, ret);
			handle_session_error(ret);
			return ERROR_FAILED;
		}
		recv_length += ret;
		body_length -= ret;
	}
	m_parser->parse(fd, m_protocol_buf, recv_length);

	return ERROR_SUCCESS;
}

void CSvrSession::Start()
{
	if (m_protocol_thread && m_protocol_thread->joinable()){
		m_protocol_thread->join();
	}
	m_protocol_thread.reset(new std::thread(&CSvrSession::handle_stream_input, this));

	Log::Info("session start success, id:%d, fd:%d,device name:%s", GetID(), m_socket, m_transcode_param.device_name.c_str());
}

void CSvrSession::Close()
{
	m_closed = true;
	if (m_socket != -1) {
		::shutdown(m_socket, SD_BOTH);
		closesocket(m_socket);
	}
	if (m_protocol_thread && m_protocol_thread->joinable()){
		m_protocol_thread->join();
	}

	if (m_live_channel){
		m_live_channel->Close();
		delete m_live_channel;
		m_live_channel = NULL;
	}
	if (m_live_svr){
		m_live_svr->DelSession(m_transcode_param.device_name);
	}
	if (m_tcp_stream){
		delete m_tcp_stream;
		m_tcp_stream = NULL;
	}
	if (m_parser){
		delete m_parser;
		m_parser = NULL;
	}
	if (m_protocol_buf){
		free(m_protocol_buf);
		m_protocol_buf = NULL;
	}

	Log::Info("session closed, device name:%s", m_transcode_param.device_name.c_str());
}

void CSvrSession::SetConfig(CTcsConfig* config)
{
	m_config = config;
}

void CSvrSession::SetLiveSvr(CTcsLiveSvr* live_svr)
{
	m_live_svr = live_svr;
}

void CSvrSession::HandlePdu(int conn_id, CFLMessage* pdu)
{
	int message_type = pdu->_messageHead->nCmd;
	switch (message_type)
	{
	case CMD_DETU_CLIENT_REQUEST_VIDEO_RES:
		handle_start_video_response(conn_id, pdu);
		break;
	case CMD_DETU_CLIENT_CLOSE_VIDEO_RES:
		handle_stop_video_response(conn_id, pdu);
		break;
	default:
		Log::Error("CSvrSession unknow message type:%d from cms.", message_type);
	}
}

int CSvrSession::get_body_length(const char* data, int length)
{
	assert(length >= (2 * sizeof(unsigned char)+sizeof(unsigned short)+sizeof(unsigned int)));

	char* ptr = (char*)data + 2 * sizeof(unsigned char)+sizeof(unsigned short);

	unsigned int value = 0;
	char* pp = (char*)&value;
	pp[3] = *ptr++;
	pp[2] = *ptr++;
	pp[1] = *ptr++;
	pp[0] = *ptr++;

	return (int)value;
}

void CSvrSession::close_invalid_socket(int client_socket, int errorno)
{
	if (errorno == ConnectionReset) {
		int sockerr = GetSockError();
		Log::Error("CSvrSession::socket error, socket:%d, errorno:%d(%s)", client_socket, sockerr, strerror(sockerr));
	} else if (errorno == ConnectionClosed) {
		Log::Error("CSvrSession::connection close, socket:%d", client_socket);
	} else if (errorno == ConnectionTimedOut){
		Log::Error("CSvrSession::connection timeout, socket:%d", client_socket);
	}
	::shutdown(client_socket, SD_BOTH);
	closesocket(client_socket);
	client_socket = -1;
}

void CSvrSession::handle_transcode_request(int conn_id, CFLMessage* pdu)
{
	CFLTrancscode* request = (CFLTrancscode*)pdu;
	std::string device_name = (char*)request->_messageBody->szDeviceId;

	bool ret = m_live_svr->IsSessionLive(device_name);
	if (ret){
		handle_transcode_response(conn_id, device_name, RESULT_TRANSCODE_EXIST);
		Notify(m_owner, GetID(), ERROR_SESSION_CLOSED);
		Log::Info("livechannel already exist, device:%s", device_name.c_str());
		return;
	} else {
		m_live_svr->AddSession(device_name, StatePrepare, this);
	}

	m_transcode_param.stream_type = request->_messageBody->nStreamType;
	m_transcode_param.device_name = device_name;
	m_transcode_param.push_url = (char*)request->_messageBody->szRtmpURL;
	m_transcode_param.bitrate = request->_messageBody->nbitrate;
	m_transcode_param.fps = request->_messageBody->nFps;
	m_transcode_param.height = request->_messageBody->nHeight;
	m_transcode_param.width = request->_messageBody->nWidth;

	unsigned int  end_time = request->_messageBody->nEndTime;
	unsigned int  start_time = request->_messageBody->nStartTime;
	unsigned char device_id = request->_messageBody->nDeviceId;
	create_pts_file(request->_messageBody->pts_data, request->_messageBody->nPtsLen);

#if 0
	std::string url = "rtmp://192.168.6.222:1935/0D2A14/1";
	start_transcode(m_transcode_param.stream_type, device_name, url);
#else
	handle_start_video_request(device_name, m_transcode_param.stream_type, device_id, start_time, end_time);
	
	//TODO: request timeout.
#endif
	Log::Info("transcode request, device name:%s, stream type:%d, publish url:%s", device_name.c_str(), m_transcode_param.stream_type, m_transcode_param.push_url.c_str());
}

void CSvrSession::handle_stop_transcode_request(int conn_id, CFLMessage* pdu)
{
	CFLStopTranscode* request = (CFLStopTranscode*)pdu;
	std::string device_name = (char*)request->_messageBody->szDeviceId;

	Log::Info("CMD_DETU_TCS_TRANSCODE_STOP recv, stoping transcode, device name:%s", device_name.c_str());

	stop_transcode(device_name);

	handle_stop_video_request(device_name, RESULT_SUCCESS);
	handle_stop_transcode_response(conn_id, device_name, RESULT_SUCCESS);

	if (m_live_svr){
		m_live_svr->DelSession(device_name);
	}

	Notify(m_owner, GetID(), ERROR_SESSION_CLOSED);
}

void CSvrSession::handle_start_video_response(int conn_id, CFLMessage* pdu)
{
	CFLRequestVideoResponse* response = (CFLRequestVideoResponse*)pdu;
	std::string	url = (char*)response->_messageBody->szRtmpURL;
	std::string	device_name = (char*)response->_messageBody->szDeviceId;

	if (response->_messageHead->nResult != RESULT_SUCCESS) {
		if (m_socket != -1) {
			handle_transcode_response(m_socket, device_name, response->_messageHead->nResult);
		}
		if (m_live_svr){
			m_live_svr->DelSession(device_name);
		}

		Notify(m_owner, GetID(), ERROR_SESSION_CLOSED);
		Log::Error("start video error, device name:%s, errorno:%d", device_name.c_str(), response->_messageHead->nResult);
		return;
	} else {
		Log::Info("CMD_DETU_CLIENT_REQUEST_VIDEO_RES recv, start video success, device name:%s", device_name.c_str());
	}

	start_transcode(m_transcode_param.stream_type, device_name, url);
}

void CSvrSession::handle_start_video_request(std::string device_name, unsigned char stream_type, unsigned char device_id, unsigned int start_time, unsigned int end_time)
{
	CFLRequestVideo* request = new CFLRequestVideo;
	request->_messageHead->nStreamId = stream_type;
	request->_messageBody->nDeviceId = device_id;
	request->_messageBody->nStartTime = htonl(start_time);
	request->_messageBody->nEndTime = htonl(end_time);
	memcpy(request->_messageBody->szDeviceId, device_name.c_str(), API_ARRAY_LEN);
	request->generateMessage();

	if (m_live_svr){
		m_live_svr->SendMsgToCMS(request->_message, request->getMessageLength());
	}
	delete request;

	Log::Info("CMD_DETU_CLIENT_REQUEST_VIDEO send successed, device name:%d", device_name.c_str());
}

void CSvrSession::handle_stop_video_response(int conn_id, CFLMessage* pdu)
{
	//do nothing
}

void CSvrSession::handle_stop_video_request(std::string device_name, int errorno)
{
	CFLCloseVideo* request = new CFLCloseVideo;
	request->_messageHead->nResult = ntohs(errorno);
	memcpy(request->_messageBody->szDeviceId, device_name.c_str(), API_ARRAY_LEN);
	request->generateMessage();

	if (m_live_svr){
		m_live_svr->SendMsgToCMS(request->_message, request->getMessageLength());
	}
	delete request;

	Log::Info("CMD_DETU_CLIENT_CLOSE_VIDEO send successed, device name:%d", device_name.c_str());
}

void CSvrSession::handle_session_error(int error)
{
	if (m_live_channel){
		m_live_channel->Close();
		delete m_live_channel;
		m_live_channel = NULL;
	}

	if (m_live_svr){
		m_live_svr->DelSession(m_transcode_param.device_name);
	}

	Notify(m_owner, GetID(), ERROR_SESSION_CLOSED);
}

void CSvrSession::handle_transcode_response(int conn_id, std::string device_name, int errorno)
{
	CFLTranscodeResponse* response = new CFLTranscodeResponse;
	response->_messageHead->nResult = ntohs(errorno);
	memcpy(response->_messageBody->szDeviceId, device_name.c_str(), API_ARRAY_LEN);
	response->generateMessage();

	m_tcp_stream->SendData(conn_id, response->_message, response->getMessageLength());
	delete response;
}

void CSvrSession::handle_stop_transcode_response(int conn_id, std::string device_name, int errorno)
{
	CFLStopTranscodeResponse* response = new CFLStopTranscodeResponse;
	response->_messageHead->nResult = ntohs(errorno);
	memcpy(response->_messageBody->szDeviceId, device_name.c_str(), API_ARRAY_LEN);
	response->generateMessage();

	m_tcp_stream->SendData(conn_id, response->_message, response->getMessageLength());
	delete response;
}

void CSvrSession::start_transcode(int stream_type, std::string device_name, std::string rtmp_url)
{
	m_live_channel = new CTcsLiveChannel;
	m_live_channel->SetOwner(this);
	m_live_channel->SetConfig(m_config);
	m_live_channel->SetNewPts(m_is_pts_new);

	m_transcode_param.rtmp_url = rtmp_url;
	int ret = m_live_channel->Init(&m_transcode_param);
	if (ret != ERROR_SUCCESS) {
		if (m_live_svr){
			m_live_svr->DelSession(device_name);
		}
		m_live_channel->Close();
		delete m_live_channel;
		m_live_channel = NULL;

		handle_transcode_response(m_socket, device_name, RESULT_FAILED);

		Notify(m_owner, GetID(), ERROR_SESSION_CLOSED);
		Log::Error("init live_channel failed, device name:%s", device_name.c_str());
		return;
	}
	m_live_channel->Start();

	if (m_live_svr){
		m_live_svr->UpdateSessionInfo(device_name, StateSuccess);
	}

	handle_transcode_response(m_socket, device_name, RESULT_SUCCESS);

	Log::Info("transcode strat succesed, device name:%s", device_name.c_str());
}

void CSvrSession::stop_transcode(std::string device_name)
{
	if (m_live_channel){
		m_live_channel->Close();
		delete m_live_channel;
		m_live_channel = NULL;
	}

	Log::Info("device:%s stop transcode.", device_name.c_str());
}

void CSvrSession::create_pts_file(unsigned char* data, int length)
{
	char cwd[MAX_DIRECT_LENGTH];
	getcwd(cwd, MAX_DIRECT_LENGTH);

	char pts[32] = { 0 };
	sprintf(pts, "\\pts\\%s\\", m_transcode_param.device_name.c_str());
	
	std::string dir = cwd;
	dir += pts;
	create_directory(dir.c_str());

	std::string filename = dir + "pat.pts";
	if (_access(filename.c_str(), 0) != 0){
		FILE* pts = fopen(filename.c_str(), "wb+");
		fwrite(data, 1, length, pts);
		fflush(pts);
		fclose(pts);

		m_is_pts_new = true;
		Log::Info("create pat.pts file in first time, device name:%s", m_transcode_param.device_name.c_str());
	} else {
		char* pts_data = (char*)malloc(length);
		FILE* pts = fopen(filename.c_str(), "rb+");
		fread(pts_data, 1, length, pts);
		fclose(pts);

		if (0 != memcmp(pts_data, data, length)) {
			FILE* pts = fopen(filename.c_str(), "wb+");
			fwrite(data, 1, length, pts);
			fflush(pts);
			fclose(pts);

			m_is_pts_new = true;
			Log::Info("pts file changed, generate new weight mask jpg, device name:%s", m_transcode_param.device_name.c_str());
		}
	}
}

bool CSvrSession::create_directory(const char* dir)
{
	char path[MAX_DIRECT_LENGTH] = { 0 };
	const char* pos = dir;
	while ((pos = strchr(pos, '\\')) != NULL){
		memcpy(path, dir, pos - dir + 1);
		pos++;
		if (_access(path, 0) == 0){
			continue;
		} else {
			int ret = _mkdir(path);
			if (ret == -1){
				return false;
			}
		}
	}
	return true;
}

void CSvrSession::handle_stream_input(void)
{
	while (true)
	{
		if (m_closed){
			break;
		}

		int ret = m_tcp_stream->ReceiveData(m_socket, m_protocol_buf, sizeof(protocol_head_t));
		if ((ret == ConnectionTimedOut) || (ret == ConnectionReset) || (ret == ConnectionClosed)) {
			close_invalid_socket(m_socket, ret);
			handle_session_error(ret);
			break;
		}

		int recv_length = sizeof(protocol_head_t);
		int body_length = get_body_length(m_protocol_buf, sizeof(protocol_head_t));
		while (body_length){
			ret = m_tcp_stream->ReceiveData(m_socket, m_protocol_buf + recv_length, 1024);
			if ((ret == ConnectionTimedOut) || (ret == ConnectionReset) || (ret == ConnectionClosed)) {
				close_invalid_socket(m_socket, ret);
				handle_session_error(ret);
				return;
			}
			recv_length += ret;
			body_length -= ret;
		}
		m_parser->parse(m_socket, m_protocol_buf, recv_length);
	}
}
