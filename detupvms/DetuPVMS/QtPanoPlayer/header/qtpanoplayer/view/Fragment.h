//
//  Fragment.hpp
//  QtPanoPlayer
//
//  Created by chao on 2017/12/2.
//

#ifndef Fragment_hpp
#define Fragment_hpp

#include <stdio.h>
#include "ViewGroup.h"

namespace DetuPanoPlayer {
    
    class Fragment {
    public:
        Fragment();
        virtual ~Fragment();
        virtual void onCreate();
        virtual void onCreateView(ViewGroup* container);
        virtual void onDestroy();
        View* getView() const;
        void setView(View* view);
    protected:
        View* mRootView;
    };
}
#endif /* Fragment_hpp */
