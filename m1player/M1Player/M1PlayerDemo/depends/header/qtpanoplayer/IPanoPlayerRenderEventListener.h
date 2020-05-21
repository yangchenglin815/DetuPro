#ifndef IPanoPlayerRenderEventListener_h__
#define IPanoPlayerRenderEventListener_h__

namespace DetuPanoPlayer {
    class IPanoPlayerRenderEventListener {
    public:
        IPanoPlayerRenderEventListener() {
        }

        ~IPanoPlayerRenderEventListener() {
        }

        virtual void onPanoPlayerRenderBefore() = 0;

        virtual void onPanoPlayerRenderAfter() = 0;
    };
}


#endif // IPanoPlayerRenderEventListener_h__
