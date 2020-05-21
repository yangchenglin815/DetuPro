#include "Platform.h"
#include "Tcpstream.h"
#include "logging.h"


CTcpstream::CTcpstream() 
{

}

CTcpstream::~CTcpstream()
{

}

int CTcpstream::SendData(int socketed, const char* buffer, size_t len)
{
	lock_guard guard(m_write_mutex);
	if (socketed == -1) {
		Log::Error("CTcpstream SendData(): socket error, socketed:%d", socketed);
		return -1;
	}

	return ::send(socketed, buffer, len, 0);
}

int CTcpstream::ReceiveData(int socketed, char* buffer, size_t len, int timeout)
{
	lock_guard guard(m_read_mutex);
	if (socketed == -1) {
		Log::Error("CTcpstream SendData(): socket error, socketed:%d", socketed);
		return -1;
	}

	if (timeout <= 0) return ::recv(socketed, buffer, len, 0);

	if (wait_read_event(socketed, timeout) == true) {
		return ::recv(socketed, buffer, len, 0);
	}
	return ConnectionTimedOut;

}

bool CTcpstream::wait_read_event(int socketed, int timeout)
{
	fd_set sdset;
	struct timeval tv;

	tv.tv_sec = timeout;
	tv.tv_usec = 0;
	FD_ZERO(&sdset);
	FD_SET(socketed, &sdset);
	if (select(socketed + 1, &sdset, NULL, NULL, &tv) > 0) {
		return true;
	}

	return false;
}
