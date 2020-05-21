//
// Created by zhangjing on 2017/8/9.
//
#include <string.h>
#ifndef GETMASKANDWEIGHT_GETRESULT_H
#define GETMASKANDWEIGHT_GETRESULT_H

#include <iostream>

using  namespace std;

typedef struct WeightAndMaskData
{
    int width;
    int height;
    char biaoding[512];
    uint8_t *data;
}WeightAndMaskData;
bool getResult(string path,WeightAndMaskData &weightAndMaskData);
bool getResultwithpath(string path, WeightAndMaskData &weightAndMaskData, std::vector<string>  resultpath);

#endif //GETMASKANDWEIGHT_GETRESULT_H
