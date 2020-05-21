
#ifndef DPV_ANDROID_PANORAMADATA_H
#define DPV_ANDROID_PANORAMADATA_H

#include <iostream>
#include "PanoNodeView.h"
#include "PanoNodeImage.h"
using namespace std;

namespace DetuPanoPlayer {

    class PanoramaData {
    public:
        PanoramaData();

        ~PanoramaData();

        PanoNodeView nodeView;
        PanoNodeImage nodeImage;
    };

}


#endif //DPV_ANDROID_PANORAMADATA_H
