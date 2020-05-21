//
// Created by chao on 2018/5/14.
//

#ifndef DPV_ANDROID_LITEDECOR_H
#define DPV_ANDROID_LITEDECOR_H

#include <stdio.h>
#include <iostream>
#include "LayoutParams.h"

using namespace std;

namespace DetuPanoPlayer {

    class LiteDecor {
    public:
        string tag;
        string imgAbsolutePath;
        LayoutParams* params;
    public:
        LiteDecor();
        LiteDecor& operator =(const LiteDecor& src);
        virtual ~LiteDecor();
    };
}

#endif //DPV_ANDROID_LITEDECOR_H
