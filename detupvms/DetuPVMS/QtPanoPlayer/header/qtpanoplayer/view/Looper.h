//
//  Looper.hpp
//  QtPanoPlayer
//
//  Created by chao on 2017/12/2.
//

#ifndef Looper_hpp
#define Looper_hpp

#include <stdio.h>
#include <cstdint>

namespace DetuPanoPlayer {
    
    typedef struct Event {
        int what;
        int arg1;
        int arg2;
        void (*run)(struct Event event, void* opaque);
    } Event;
    
    class Looper {
    public:
        Looper();
        ~Looper();
        void post(Event* event, int64_t delayMillis, void* opaque);
        void remove(int what);
    };
}

#endif /* Looper_hpp */
