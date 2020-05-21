//
//  ExifUtils.hpp
//  QtPanoPlayer
//
//  Created by chao on 2017/11/3.
//

#ifndef ExifUtils_hpp
#define ExifUtils_hpp

#include <iostream>
using namespace std;

namespace DetuPanoPlayer {
    class ExifUtils {
    public:
        string readExif(string imgAbsolutePath);
    };
}

#endif /* ExifUtils_hpp */
