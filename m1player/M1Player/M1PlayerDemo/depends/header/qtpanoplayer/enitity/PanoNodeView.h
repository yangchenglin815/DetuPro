#pragma once
namespace DetuPanoPlayer {

typedef enum PanoViewMode {
	PanoViewMode_DEFAULT = 1, //全景模式
	PanoViewMode_FISHEYE, //鱼眼模式
	PanoViewMode_VR_HORIZONTAL, //左右vr模式
	PanoViewMode_VR_VERTICAL, //上下vr模式
	PanoViewMode_ORIGINAL, //原图模式，原始图像
	PanoViewMode_FLAT, //平面模式，展开的2:1模式
	PanoViewMode_LITTLE_PLANET, //小行星模式
	PanoViewMode_SPHERE, //曲面模式
}PanoViewMode;


class PanoNodeView
{
public:
	PanoNodeView();
	~PanoNodeView();
	float hLookAt = 90.0f;
	float hLookAtMin = -180.0f;
	float hLookAtMax = 180.0f;

	float vLookAt = 0.0f;
	float vLookAtMin =-90.0f;
	float vLookAtMax = 90.0f;

	float curfov=0.0;//当前视角
	float deffov = 60.0f;//普通视角
	float deffovMin = 40.0f;
	float deffovMax = 110.0f;

	float spherefov = 45.0f;//曲面视角
	float spherefovMin = 20.0f;
	float spherefovMax = 120.0f;

	float littlePlanetfov = 140.0f;//小行星视角
	float littlePlanetfovMax = 160.0f;
	float littlePlanetfovMin = 45.0f;

	float fisheyefov = 120.0f;//鱼眼视角
	float fisheyefovMax = 130.0f;
	float fisheyefovMin = 45.0f;

	float VREyeOffset=0.2;//Vr模式的眼睛偏移量
	float vrFov = 90.0f;
	PanoViewMode viewMode;
};

}
