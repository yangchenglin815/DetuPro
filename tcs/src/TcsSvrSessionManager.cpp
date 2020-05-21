#include "Platform.h"
#include "Config.h"
#include "Error.h"
#include "TcpStream.h"
#include "TcsSvrSession.h"
#include "TcsLiveSvr.h"
#include "TcsSvrSessionManager.h"
#include "APIProtocol.h"
#include "logging.h"

CSvrSessionManager::CSvrSessionManager()
{
	m_closed = false;
	m_config = NULL;
	m_tcp_stream = NULL;
	m_pre_buf = NULL;
	m_live_svr = NULL;
}

CSvrSessionManager::~CSvrSessionManager()
{

}

void CSvrSessionManager::onMessage(long session_id, int message_type)
{
	if (ERROR_SESSION_CLOSED == message_type){
		std::unique_lock<std::mutex> lock(m_session_mtx);
		std::map<long, CSvrSession*>::iterator iter = m_session_manager.find(session_id);
		if (iter != m_session_manager.end()){
			CSvrSession* session = iter->second;
			session->Close();
			delete session;
			m_session_manager.erase(iter);
			Log::Info("session delete from manager, session id:%d", session_id);
		}
	}
}

void CSvrSessionManager::Start()
{
	m_tcp_stream = new CTcpstream;
	m_pre_buf = (char*)malloc(sizeof(protocol_head_t));
	memset(m_pre_buf, 0, sizeof(protocol_head_t));

	if (m_conn_manager_thread && m_conn_manager_thread->joinable()){
		m_conn_manager_thread->join();
	}
	m_conn_manager_thread.reset(new std::thread(&CSvrSessionManager::handle_input,this));
}

void CSvrSessionManager::Close()
{
	m_closed = true;
	std::unique_lock<std::mutex> empty_lock(m_emytp_mtx);
	m_empty_con.notify_one();
	empty_lock.unlock();

	if (m_conn_manager_thread && m_conn_manager_thread->joinable()){
		m_conn_manager_thread->join();
	}

	std::unique_lock<std::mutex> lock(m_emytp_mtx);
	while (m_connections.size() > 0) {
		m_connections.pop_front();
	}
	lock.unlock();

	std::unique_lock<std::mutex> session_lock(m_session_mtx);
	std::map<long, CSvrSession*>::iterator iter = m_session_manager.begin();
	for (; iter != m_session_manager.end();) {
		CSvrSession* session = iter->second;
		session->Close();
		delete session;
		m_session_manager.erase(iter++);
	}
	session_lock.unlock();

	if (m_tcp_stream){
		delete m_tcp_stream;
	}
	if (m_pre_buf){
		free(m_pre_buf);
		m_pre_buf = NULL;
	}

	Log::Info("svrsessionmanager closed.");
}

void CSvrSessionManager::Enqueue(int client_sockfd)
{
	std::unique_lock<std::mutex> lock(m_emytp_mtx);
	m_connections.push_back(client_sockfd);
	m_empty_con.notify_one();
	lock.unlock();
}

void CSvrSessionManager::SetConfig(CTcsConfig* config)
{
	m_config = config;
}

void CSvrSessionManager::SetLiveSvr(CTcsLiveSvr* live_svr)
{
	m_live_svr = live_svr;
}

void CSvrSessionManager::close_invalid_socket(int client_socket, int errorno)
{
	if (errorno == ConnectionReset) {
		int sockerr = GetSockError();
		Log::Error("CSvrSessionManager::socket error, socket:%d, errorno:%d(%s)", client_socket, sockerr, strerror(sockerr));
	} else if (errorno == ConnectionClosed) {
		Log::Error("CSvrSessionManager::connection close, socket:%d", client_socket);
	} else if (errorno == ConnectionTimedOut){
		Log::Error("CSvrSessionManager::connection timeout(5s), socket:%d", client_socket);
	}
	::shutdown(client_socket, SD_BOTH);
	closesocket(client_socket);
}

void CSvrSessionManager::handle_input()
{
	while (true) {
		if (m_closed) {
			break;
		}

		std::unique_lock<std::mutex> lock(m_emytp_mtx);
		if (m_connections.empty()) {
			m_empty_con.wait(lock);
			if (m_closed) {
				break;
			}
		}
		int client_socket = m_connections.front();
		m_connections.pop_front();
		lock.unlock();

		if (m_tcp_stream) {
			int ret = m_tcp_stream->ReceiveData(client_socket, m_pre_buf, sizeof(protocol_head_t), 5);
			if ((ret == ConnectionTimedOut) || (ret == ConnectionReset) || (ret == ConnectionClosed)) {
				close_invalid_socket(client_socket, ret);
			} else {
				CSvrSession* session = new CSvrSession;
				session->SetConfig(m_config);
				session->SetLiveSvr(m_live_svr);
				session->SetOwner(this);
				int ret = session->Init(client_socket, m_pre_buf, sizeof(protocol_head_t));
				if (ret == ERROR_SUCCESS){
					session->Start();
					std::lock_guard<std::mutex> session_lock(m_session_mtx);
					m_session_manager.insert(std::pair<long, CSvrSession*>(session->GetID(), session));
				} else {
					session->Close();
					delete session;
					session = NULL;
				}
			}
		}
	}

	Log::Info("CSvrSessionManager handle_input thread quit, stop handle client request.");
}
