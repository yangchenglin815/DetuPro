#pragma once
namespace DetuPanoPlayer {

typedef enum PanoViewMode {
	PanoViewMode_DEFAULT = 1, //ȫ��ģʽ
	PanoViewMode_FISHEYE, //����ģʽ
	PanoViewMode_VR_HORIZONTAL, //����vrģʽ
	PanoViewMode_VR_VERTICAL, //����vrģʽ
	PanoViewMode_ORIGINAL, //ԭͼģʽ��ԭʼͼ��
	PanoViewMode_FLAT, //ƽ��ģʽ��չ����2:1ģʽ
	PanoViewMode_LITTLE_PLANET, //С����ģʽ
	PanoViewMode_SPHERE, //����ģʽ
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

	float curfov=0.0;//��ǰ�ӽ�
	float deffov = 60.0f;//��ͨ�ӽ�
	float deffovMin = 40.0f;
	float deffovMax = 110.0f;

	float spherefov = 45.0f;//�����ӽ�
	float spherefovMin = 20.0f;
	float spherefovMax = 120.0f;

	float littlePlanetfov = 140.0f;//С�����ӽ�
	float littlePlanetfovMax = 160.0f;
	float littlePlanetfovMin = 45.0f;

	float fisheyefov = 120.0f;//�����ӽ�
	float fisheyefovMax = 130.0f;
	float fisheyefovMin = 45.0f;

	float VREyeOffset=0.2;//Vrģʽ���۾�ƫ����
	float vrFov = 90.0f;
	PanoViewMode viewMode;
};

}
