//
// Created by chao on 2017/11/6.
//

#include "PanoNodeImage.h"

namespace DetuPanoPlayer {
    PanoNodeImage::PanoNodeImage() : panoResourceType(PanoResourceType_VIDEO), panoDeviceId(PanoDeviceId_2_1), isReverse(false) {
        urls.clear();
        isRenderBgra = false;
        isPushFlow = false;
        isCameraUpsideDown = false;
        prohibitSwitchAnimation = false;
		isProcess2_1 = false;
		memset(textureIds, 0, sizeof(textureIds));
    }


    PanoNodeImage::~PanoNodeImage() {
    }
}
