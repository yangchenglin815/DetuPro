#ifndef _MESSAGE_QUEUE_H_
#define _MESSAGE_QUEUE_H_

#include <vector>
#include <functional>
#include <memory>
#include <thread>
#include "LockingQueue.h"

typedef struct signal_node
{
	int		message_type;
	long	siganl_id;
	long	attach;
}signal_node;

typedef struct sigantion_node
{
	std::function<void(int message_type, long attach)> sigaction;
	long	signal_id;
}sigantion_node;

class CMessageQueue
{
public:
	static CMessageQueue& GetInstance()
	{
		if (m_instance == NULL) {
			std::lock_guard<std::mutex> lock(m_mtx);
			if (m_instance == NULL) {
				m_instance = new CMessageQueue();
			}
			return *m_instance;
		}
		return *m_instance;
	}

private:
	static CMessageQueue* volatile m_instance;
	static std::mutex m_mtx;

private:
	CMessageQueue(void);
	~CMessageQueue(void);

public:
	void Register(std::function<void(int message_type, long attach)> sigaction, long& signal_id);
	void Unregister(long signal_id);
	void Notify(long signal_id, int message_type, long attach);

private:
	void messge_looper_thread(void);

private:
	bool							m_is_close;
	long							m_signal_base;
	std::mutex						m_map_mtx;
	CLockingQueue<signal_node>		m_messages;
	std::vector<sigantion_node>		m_sigaction_map;
	std::shared_ptr<std::thread>	m_message_loop_thread;
};

#endif
