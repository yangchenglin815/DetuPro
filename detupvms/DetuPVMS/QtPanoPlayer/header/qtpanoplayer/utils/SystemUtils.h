//
//  SystemUtils.hpp
//  QtPanoPlayer
//
//  Created by chao on 2018/1/10.
//

#ifndef SystemUtils_hpp
#define SystemUtils_hpp

#include <stdio.h>

namespace DetuPanoPlayer {
    
    class SystemUtils {
    public:
        static void sleep(int second);
        static void mSleep(int ms);
        static void uSleep(int us);
    };
}

#endif /* SystemUtils_hpp */
