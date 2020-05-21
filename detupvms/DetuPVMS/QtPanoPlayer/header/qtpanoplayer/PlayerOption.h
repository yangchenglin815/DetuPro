#pragma once

#include <iostream>

using namespace std;

namespace DetuPanoPlayer {

    typedef enum PlayerOptionType {
        PlayerOptionType_Codec,
        PlayerOptionType_Sws,
        PlayerOptionType_Player,
        PlayerOptionType_Format
    } PlayerOptionType;

    typedef enum PlayerOptionValueType {
        PlayerOptionValueType_INTEGER,
        PlayerOptionValueType_STRING,
    } PlayerOptionValueType;

    typedef struct PlayerOption {
        string key;
        string value;
        PlayerOptionType type;
        PlayerOptionValueType valueType;
    } PlayerOption;

}
