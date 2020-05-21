#pragma once
#include <iostream>
#include "PanoNodeView.h"
#include "PanoNodeImage.h"
using namespace std;

namespace DetuPanoPlayer {

class PanoramaData
{
public:
	PanoramaData();
	~PanoramaData();
	PanoNodeView nodeView;
	PanoNodeImage nodeImage;
};

}
