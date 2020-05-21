//
//  Fragment.cpp
//  QtPanoPlayer
//
//  Created by chao on 2017/12/2.
//

#include "Fragment.h"

namespace DetuPanoPlayer {
    
    Fragment::Fragment() : mRootView(NULL) {
        
    }
    
    Fragment::~Fragment() {
        
    }
    
    void Fragment::onCreate() {
        
    }
    
    void Fragment::onCreateView(ViewGroup* container) {
    }
    
    View* Fragment::getView() const {
        return mRootView;
    }
    
    void Fragment::setView(View* view) {
        mRootView = view;
    }
    
    void Fragment::onDestroy() {
        
    }
}
