#include <string>
#include "MessageQueue.h"

CMessageQueue* volatile CMessageQueue::m_instance = NULL;
std::mutex CMessageQueue::m_mtx;

CMessageQueue::CMessageQueue()
{
	m_is_close = false;
	m_signal_base = 10000;
	m_message_loop_thread.reset(new std::thread(&CMessageQueue::messge_looper_thread, this));
}

CMessageQueue::~CMessageQueue()
{
	m_is_close = true;

	signal_node signal = { 0 };
	m_messages.enqueue(signal);

	if (m_message_loop_thread && m_message_loop_thread->joinable()) {
		m_message_loop_thread->join();
	}
}

void CMessageQueue::Register(std::function<void(int message_type, long attach)> sigaction, long& signal_id)
{
	std::unique_lock<std::mutex> lock(m_map_mtx);
	signal_id = m_signal_base++;
	sigantion_node node;
	node.sigaction = sigaction;
	node.signal_id = signal_id;
	m_sigaction_map.push_back(node);
	lock.unlock();
}

void CMessageQueue::Unregister(long signal_id)
{
	std::unique_lock<std::mutex> lock(m_map_mtx);
	std::vector<sigantion_node>::iterator iter = m_sigaction_map.begin();
	for ( ; m_sigaction_map.end() != iter; ) {
		if (iter->signal_id == signal_id) {
			m_sigaction_map.erase(iter);
			break;
		}
	}
	lock.unlock();
}

void CMessageQueue::Notify(long signal_id, int message_type, long attach)
{
	signal_node signal = { 0 };
	signal.attach = attach;
	signal.siganl_id = signal_id;
	signal.message_type = message_type;
	m_messages.enqueue(signal);
}

void CMessageQueue::messge_looper_thread(void)
{
	while (true) {
		if (m_is_close) {
			break;
		}

		signal_node node = { 0 };
		if (m_messages.wait_dequeue(node)) {
			if (m_is_close) {
				break;
			}

			std::unique_lock<std::mutex> lock(m_map_mtx);
			std::vector<sigantion_node>::iterator iter = m_sigaction_map.begin();
			for (; m_sigaction_map.end() != iter; iter++) {
				if (iter->signal_id == node.siganl_id) {
					std::function<void(int message_type, long attach)> sigaction = iter->sigaction;
					sigaction(node.message_type, node.attach);
					break;
				}
			}
			lock.unlock();
		}
	}
}
