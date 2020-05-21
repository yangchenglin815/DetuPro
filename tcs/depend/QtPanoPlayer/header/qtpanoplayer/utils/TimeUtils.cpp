//
//  TimeUtils.cpp
//  QtPanoPlayer
//
//  Created by chao on 2017/12/2.
//

#include "TimeUtils.h"
#ifdef _WIN32
#include <winsock2.h>
#include <time.h>
#else
#include <sys/time.h>
#endif

namespace DetuPanoPlayer {

    int64_t TimeUtils::getSystemTimeMills() {
#ifdef _WIN32
        struct timeval tv;
        time_t clock;
        struct tm tm;
        SYSTEMTIME wtm;
        
        GetLocalTime(&wtm);
        tm.tm_year = wtm.wYear - 1900;
        tm.tm_mon = wtm.wMonth - 1;
        tm.tm_mday = wtm.wDay;
        tm.tm_hour = wtm.wHour;
        tm.tm_min = wtm.wMinute;
        tm.tm_sec = wtm.wSecond;
        tm.tm_isdst = -1;
        clock = mktime(&tm);
        tv.tv_sec = clock;
        tv.tv_usec = wtm.wMilliseconds * 1000;
        return ((unsigned long long)tv.tv_sec * 1000 + (unsigned long long)tv.tv_usec / 1000);
#else
        struct timeval tv;
        gettimeofday(&tv,NULL);
        return ((unsigned long long)tv.tv_sec * 1000 + (unsigned long long)tv.tv_usec / 1000);
#endif  
    }
}
