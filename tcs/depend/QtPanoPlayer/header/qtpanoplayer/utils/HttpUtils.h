//
//  HttpUtils.h
//  PanoPlayer
//
//  Created by chao on 2017/11/3.
//  Copyright © 2017年 detu. All rights reserved.
//

#ifndef HttpUtils_h
#define HttpUtils_h

#include<iostream>

using namespace std;

//每个平台需要单独实现
namespace DetuPanoPlayer {
    
    class HttpUtils {
    public:
        bool cacheHttpFileToLocal(string remoteUrl, string localAbsolutePath);
    };
}


#endif /* HttpUtils_h */
