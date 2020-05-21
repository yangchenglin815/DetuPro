//
//  IDecorListener.h
//  QtPanoPlayer
//
//  Created by chao on 2017/12/3.
//

#ifndef IDecorListener_h
#define IDecorListener_h

namespace DetuPanoPlayer {
    
    class IDecorListener {
    public:
        IDecorListener() {}
        virtual ~IDecorListener() {}
        virtual void onRendeDistortedDecor() = 0;
        virtual void onRendeUnDistortedDecor() = 0;
    };
}

#endif /* IDecorListener_h */
