#pragma once
#include "logging.hpp"

#define DEM1SERIVCE_VERSION 1.0

#define SERVER_IP "192.168.1.95"
#define DEM1SERIVCE_PORT 8088

#define MYSQL_THREAD_POOL_SIZE 100
#define MYSQL_CONNECT_URL ("tcp://127.0.0.1:3306")
#define MYSQL_USERNAME "root"
#define MYSQL_PASSWORD "detu123"
#define MYSQL_DATABASE "dem1server"

static std::string string_format(const std::string fmt, ...) {
	int size = ((int)fmt.size()) * 3 + 50;   // Use a rubric appropriate for your code
	std::string str;
	va_list ap;
	while (1) {     // Maximum two passes on a POSIX system...
		str.resize(size);
		va_start(ap, fmt);
		int n = vsnprintf((char *)str.data(), size, fmt.c_str(), ap);
		va_end(ap);
		if (n > -1 && n < size) {  // Everything worked
			str.resize(n);
			return str;
		}
		if (n > -1)  // Needed size returned
			size = n + 1;   // For null char
		else
			size *= 2;      // Guess at a larger size (OS specific)
	}
	return str;
}