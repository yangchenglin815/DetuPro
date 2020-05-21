#ifndef _MESSAGE_HANDLE_H_
#define _MESSAGE_HANDLE_H_

#include <mutex>

#include "MessageThread.h"

class CMessageHandle
{
public:
	CMessageHandle();
	virtual ~CMessageHandle();

public:
	void Notify(CMessageHandle* handle, long session_id, int message_type);
	long GetID(void);
	void SetOwner(CMessageHandle* owner);

public:
	virtual void onMessage(long session_id, int message_type);

protected:
	CMessageHandle*						m_owner;

private:
	static long							m_session_id;
	static long							m_refrence_num;
	static std::mutex					m_refrence_mtx;

	static CMessageThread*				m_message_thread;

public:
	long								m_own_id;
};	

#endif
