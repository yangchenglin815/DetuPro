//
//  TimeUtils.hpp
//  QtPanoPlayer
//
//  Created by chao on 2017/12/2.
//

#ifndef TimeUtils_hpp
#define TimeUtils_hpp

#include <stdio.h>
#include <cstdint>

namespace DetuPanoPlayer {
    
    class TimeUtils {
    public:
        static int64_t getSystemTimeMills();
    };
}

#endif /* TimeUtils_hpp */
