//
//  SystemUtils.cpp
//  QtPanoPlayer
//
//  Created by chao on 2018/1/10.
//

#include "SystemUtils.h"
#if defined(_WIN32)
#include <windows.h>
#elif defined(_WIN64)
#include <windows.h>
#else
#include <unistd.h>
#endif

namespace DetuPanoPlayer {
    
    void SystemUtils::sleep(int second) {

    }
    void SystemUtils::mSleep(int ms) {
#if defined(_WIN32)
		Sleep(ms);
#elif defined(_WIN64)
        Sleep(us);
#else
        usleep(ms * 1000);
#endif
    }
    
    void SystemUtils::uSleep(int us) {
#if defined(_WIN32)
        Sleep(us * 1000);
#elif defined(_WIN64)
        Sleep(us * 1000);
#else
#include <unistd.h>
        usleep(us);
#endif
    }
}
