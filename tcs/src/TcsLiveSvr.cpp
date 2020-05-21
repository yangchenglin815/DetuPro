#include "TcsSvrSession.h"
#include "CFL_Message.h"
#include "CFL_RequestVideo.h"
#include "CFL_CloseVideo.h"
#include "TcsLiveSvr.h"
#include "TcpStream.h"
#include "logging.h"

CTcsLiveSvr::CTcsLiveSvr()
{
	m_bls_socket = -1;
	m_bls_stream = new CTcpstream;
}

CTcsLiveSvr::~CTcsLiveSvr()
{

}

void CTcsLiveSvr::AddSession(std::string device_name, live_channel_state_e state, CSvrSession* ptr)
{
	std::lock_guard<std::mutex> lock(m_session_mtx);
	live_channel_node_t* node = (live_channel_node_t*)calloc(1,sizeof(live_channel_node_t));
	node->state = state;
	node->session = ptr;
	m_session_map.insert(std::pair<std::string, live_channel_node_t*>(device_name, node));
	Log::Info("add svrsession in live svr, device name:%s", device_name.c_str());
}

void CTcsLiveSvr::UpdateSessionInfo(std::string device_name, live_channel_state_e state)
{
	std::lock_guard<std::mutex> lock(m_session_mtx);
	std::map<std::string, live_channel_node_t*>::iterator iter = m_session_map.find(device_name);
	if (iter != m_session_map.end()){
		live_channel_node_t* node = iter->second;
		node->state = state;
	}
}

void CTcsLiveSvr::DelSession(std::string device_name)
{
	std::lock_guard<std::mutex> lock(m_session_mtx);
	std::map<std::string, live_channel_node_t*>::iterator iter = m_session_map.find(device_name);
	if (iter != m_session_map.end()){
		live_channel_node_t* node = iter->second;
		m_session_map.erase(iter);
		free(node);
		Log::Info("delete svrsession from live svr, device name:%s", device_name.c_str());
	} else {
		//Log::Error("can't find device:%s in session map",device_name.c_str());
	}
}

bool CTcsLiveSvr::IsSessionLive(std::string device_name)
{
	std::lock_guard<std::mutex> lock(m_session_mtx);
	std::map<std::string, live_channel_node_t*>::iterator iter = m_session_map.find(device_name);
	if (iter != m_session_map.end()){
		return true;
	}

	return false;
}

int CTcsLiveSvr::GetLiveChannelNum()
{
	int nums = 0;
	std::lock_guard<std::mutex> lock(m_session_mtx);
	std::map<std::string, live_channel_node_t*>::iterator iter = m_session_map.begin();
	for (; iter != m_session_map.end();iter++){
		if (iter->second->state == StateSuccess){
			nums += 1;
		}
	}

	Log::Debug("currrent live channel nums:%d", nums);
	return nums;
}

void CTcsLiveSvr::Close()
{
	std::lock_guard<std::mutex> lock(m_session_mtx);
	std::map<std::string, live_channel_node_t*>::iterator iter = m_session_map.begin();
	for (; iter != m_session_map.end(); iter++){
		live_channel_node_t* node = iter->second;
		m_session_map.erase(iter);
		free(node);
	}
	delete m_bls_stream;
}

void CTcsLiveSvr::HandlePdu(int conn_id, CFLMessage* pdu)
{
	int message_type = pdu->_messageHead->nCmd;
	switch (message_type)
	{
	case CMD_DETU_CLIENT_REQUEST_VIDEO_RES:
		handle_start_video_response(conn_id, pdu);
		break;
	case CMD_DETU_CLIENT_CLOSE_VIDEO_RES:
		handle_close_video_response(conn_id, pdu);
		break;
	default:
		Log::Error("CTcsLiveSvr unknow message type:%d", message_type);
	}
}

void CTcsLiveSvr::SendMsgToCMS(char* data, int length)
{
	std::lock_guard<std::mutex> lock(m_socket_mtx);
	if (m_bls_stream && (m_bls_socket != -1)){
		m_bls_stream->SendData(m_bls_socket, data, length);
	} else {
		Log::Error("can't send message to cms.");
	}
}

void CTcsLiveSvr::SetSocket(int fd)
{
	std::lock_guard<std::mutex> lock(m_socket_mtx);
	m_bls_socket = fd;
}

CSvrSession* CTcsLiveSvr::get_session(std::string device_name)
{
	std::lock_guard<std::mutex> lock(m_session_mtx);
	std::map<std::string, live_channel_node_t*>::iterator iter = m_session_map.find(device_name);
	if (iter != m_session_map.end()){
		return iter->second->session;
	}

	return NULL;
}

void CTcsLiveSvr::handle_start_video_response(int conn_id, CFLMessage* pdu)
{
	CFLRequestVideoResponse* response = (CFLRequestVideoResponse*)pdu;
	std::string	device_name = (char*)response->_messageBody->szDeviceId;
	CSvrSession* session = get_session(device_name);
	if (session != NULL){
		session->HandlePdu(conn_id, pdu);
	} else {
		Log::Error("can't find session by device:%s", device_name.c_str());
	}
}

void CTcsLiveSvr::handle_close_video_response(int conn_id, CFLMessage* pdu)
{
	//do nothing
}
