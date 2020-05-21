//
// Created by chao on 2017/11/20.
//

#ifndef M1_ANDROID_IDECODERGENERATOR_H
#define M1_ANDROID_IDECODERGENERATOR_H

//#include "H264DecoderBase.h"
#include "Global.h"

class H264DecoderBase;

class IDecoderGenerator {
public:
    IDecoderGenerator() {}

    virtual ~IDecoderGenerator() {}

    virtual H264DecoderBase *generateDecoderByType(decode_type_e type) = 0;
};

#endif //M1_ANDROID_IDECODERGENERATOR_H
