#pragma once
#include "PanoNodeBgm.h"
#include "PanoramaData.h"
#include "PanoNodeSetting.h"

#include <iostream>
#include <vector>
using namespace std;

class PanoXmlData
{
public:
	PanoXmlData();
	~PanoXmlData();

	PanoNodeBgm nodeBgm;
	PanoNodeSetting nodeSetting;
	vector<PanoramaData> panoramaDatas;
};

