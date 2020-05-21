#pragma once
#include <iostream>
#include <vector>
using namespace std;

namespace DetuPanoPlayer {

typedef enum PanoResourceType {
	PanoResourceType_CUBE, //ȫ��ͼ���ŵ�ͼ��Դ
	PanoResourceType_SPHERE, //ȫ��ͼ����ͼƬ��Դ
	PanoResourceType_VIDEO, //ȫ����Ƶ��Դ
}PanoResourceType;

typedef enum PanoDeviceId {
	PanoDeviceId_UNKNOW = -1,
	PanoDeviceId_2_1 = 0,
	PanoDeviceId_SPHERE_800 = 1,
	PanoDeviceId_SPHERE_S = 11,
	PanoDeviceId_482 = 101,
	PanoDeviceId_SPHERE_360 = 360,
	PanoDeviceId_TWO_SPHERE = 2000,
	PanoDeviceId_SPHERE_DETU_TWINS = 2002,
	PanoDeviceId_SPHERE_THETAS = 2003,
	PanoDeviceId_SPHERE_INSTA_360 = 2004,
	PanoDeviceId_SPHERE_Real3D = 2005,
	PanoDeviceId_SPHERE_DETU_F4 = 4001,
}PanoDeviceId;

class PanoNodeImage
{
public:
	PanoNodeImage();
	~PanoNodeImage();
	PanoResourceType panoResourceType;
	vector<string> urls;
	PanoDeviceId panoDeviceId;
	string calibration;
};
}
