#ifndef _MESSAGE_THREAD_H_
#define _MESSAGE_THREAD_H_

#include <deque>
#include <mutex>
#include <memory>
#include <thread>
#include <condition_variable>

class CMessageHandle;

typedef struct SigNode
{
	CMessageHandle	*handle;
	long			session_id;
	int				message_type;
	void			*opaque;
}SigNode;

class CMessageThread
{
public:
	CMessageThread();
	~CMessageThread();

public:
	void Enqueue(CMessageHandle* handle, long session_id, int message_type);
	void Dequeue(CMessageHandle* handle);
	void Close(void);

private:
	void messge_looper_thread(void);

private:
	std::mutex					m_msg_mtx;
	std::condition_variable		m_msg_con;
	std::deque<SigNode>			m_messages;

	bool							m_is_close;
	std::shared_ptr<std::thread>	m_message_loop_thread;
};

#endif
