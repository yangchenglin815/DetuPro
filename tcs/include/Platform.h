#ifndef _PLATFORM_H_
#define _PLATFORM_H_


#ifdef WIN32

#ifdef _XBOX
#include <winsockx.h>
#include <xtl.h>
#define snprintf _snprintf
#define strcasecmp stricmp
#define strncasecmp strnicmp
#define vsnprintf _vsnprintf
#else
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <io.h>
#define snprintf _snprintf
#define strcasecmp _stricmp
#define strncasecmp _strnicmp
#define vsnprintf _vsnprintf
#endif

#define GetSockError()	WSAGetLastError()
#define SetSockError(e) WSASetLastError(e)
#define setsockopt(a, b, c, d, e) (setsockopt)(a, b, c, (const char *)d, (int)e)
#define EWOULDBLOCK	WSAETIMEDOUT //we don't use nonblocking, but we do use timeouts
#define SET_SCKTIMEO(tv, s) int tv = s * 1000

#else /* !WIN32 */

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <unistd.h>

#define GetSockError() errno
#define SetSockError(e) errno = e
#undef  closesocket
#define closesocket(s) close(s)
#define msleep(n) usleep(n * 1000)
#define SET_SCKTIMEO(tv, s) struct timeval tv = {s, 0}

#endif

#ifdef _WIN32
typedef unsigned long long u_int64_t;
typedef long long int64_t;
typedef unsigned int u_int32_t;
typedef u_int32_t uint32_t;
typedef int int32_t;
typedef unsigned char u_int8_t;
//typedef char int8_t;
typedef unsigned short u_int16_t;
typedef short int16_t;
typedef int64_t ssize_t;
struct iovec {
	void  *iov_base;    /* Starting address */
	size_t iov_len;     /* Number of bytes to transfer */
};
#endif

#include <sys/types.h>
#include <sys/stat.h>  

#ifndef _WIN32
#include <sys/uio.h>
#endif

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#define PRId64 "lld"

#include<direct.h>

typedef int mode_t;
#define S_IRUSR 0
#define S_IWUSR 0
#define S_IXUSR 0
#define S_IRGRP 0
#define S_IWGRP 0
#define S_IXGRP 0
#define S_IROTH 0
#define S_IXOTH 0

#include <fcntl.h>
#define open _open
#define close _close
#define lseek _lseek
#define write _write
#define read _read

#endif

#endif
