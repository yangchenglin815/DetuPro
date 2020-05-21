//
// Created by chao on 2017/11/22.
//

#include "DefaultGenerator.h"
#include "FfmpegH264Decoder.h"

#if defined(MAC_QT)
#elif defined(__APPLE__)
#include "VtbH264Decoder.h"
#elif defined(_WIN32)
#elif defined(_WIN64)
#else
#endif


DefaultGenerator::DefaultGenerator() {

}

DefaultGenerator::~DefaultGenerator() {

}

H264DecoderBase *DefaultGenerator::generateDecoderByType(decode_type_e type) {
    H264DecoderBase *decoder = NULL;
    switch (type) {
        case DecodeTypeSoft:
        case DecodeTypeIntel:
        case DecodeTypeCuda:
        case DecodeTypeVda:
            decoder = new FfmpegH264Decoder;
            break;
        case DecodeTypeVtb:
#if defined(__APPLE__)
            m_h264_decoders[i] = new VtbH264Decoder;
#endif
        default:
            break;
    }

    return decoder;
}

IAudioOutBase *DefaultGenerator::generateAudioOut() {
    return NULL;
}