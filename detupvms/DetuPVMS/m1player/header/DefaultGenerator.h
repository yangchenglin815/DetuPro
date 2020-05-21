//
// Created by chao on 2017/11/22.
//

#ifndef M1_ANDROID_DEFAULTDECODERGENERATOR_H
#define M1_ANDROID_DEFAULTDECODERGENERATOR_H

#include "IGenerator.h"
#include "H264DecoderBase.h"

class DefaultGenerator : public IGenerator {
public:
    DefaultGenerator();

    ~DefaultGenerator();

    H264DecoderBase *generateDecoderByType(decode_type_e type) override;

    IAudioOutBase *generateAudioOut() override;
};

#endif //M1_ANDROID_DEFAULTDECODERGENERATOR_H
