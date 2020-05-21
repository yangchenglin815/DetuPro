#include <windows.h>
#include "MessageThread.h"
#include "MessageHandle.h"


CMessageThread::CMessageThread()
{
	m_is_close = false;
	m_message_loop_thread.reset(new std::thread(&CMessageThread::messge_looper_thread, this));
}

CMessageThread::~CMessageThread()
{
	
}

void CMessageThread::Enqueue(CMessageHandle* handle, long session_id, int message_type)
{
	SigNode sig_node = { 0 };
	sig_node.handle = handle;
	sig_node.message_type = message_type;
	sig_node.session_id = session_id;

	std::unique_lock<std::mutex> lock(m_msg_mtx);
	m_messages.push_back(sig_node);
	m_msg_con.notify_one();
	lock.unlock();

	return;
}

void CMessageThread::Dequeue(CMessageHandle* handle)
{
	std::unique_lock<std::mutex> lock(m_msg_mtx);
	std::deque<SigNode>::iterator iter = m_messages.begin();
	for (; iter != m_messages.end();){
		if ((*iter).handle == handle){
			iter = m_messages.erase(iter);
		} else {
			iter++;
		}
	}
	lock.unlock();
}

void CMessageThread::Close(void)
{
	m_is_close = true;
	std::unique_lock<std::mutex> lock(m_msg_mtx);
	m_msg_con.notify_one();

	while (m_messages.size() > 0) {
		m_messages.pop_front();
	}
	lock.unlock();

	if (m_message_loop_thread && m_message_loop_thread->joinable()){
		m_message_loop_thread->join();
	}
}

void CMessageThread::messge_looper_thread()
{
	while (true) {
		if (m_is_close) {
			break;
		}

		SigNode sig_node = { 0 };
		std::unique_lock<std::mutex> lock(m_msg_mtx);
		if (m_messages.empty()) {
			m_msg_con.wait(lock);
			if (m_is_close) {
				break;
			}
		}
		sig_node = m_messages.front();
		m_messages.pop_front();
		lock.unlock();

		if (sig_node.handle->m_own_id > 10000){
			sig_node.handle->onMessage(sig_node.session_id, sig_node.message_type);
		}
	}
	return;
}
