#ifndef _TCP_STREAM_H_
#define _TCP_STREAM_H_

#include <mutex>

enum {
	ConnectionClosed = 0,
	ConnectionReset = -1,
	ConnectionTimedOut = -2
};

class CTcpstream
{
public:
	CTcpstream();
	~CTcpstream();

	int SendData(int socketed, const char* buffer, size_t len);
	int ReceiveData(int socketed, char* buffer, size_t len, int timeout = 0);

private:
	bool wait_read_event(int socketed, int timeout);

private:
	typedef std::lock_guard<std::mutex> lock_guard;
	std::mutex m_read_mutex;
	std::mutex m_write_mutex;
};

#endif
