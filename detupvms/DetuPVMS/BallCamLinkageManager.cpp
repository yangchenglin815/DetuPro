#include "BallCamLinkageManager.h"

#define DEG(r) ( 180.0 * (r) / M_PI )
#define RAD(d) ( M_PI * (d) / 180.0 )

BallCamLinkageManager::BallCamLinkageManager() :
last_ball_cam_point_num_(0),
yaw_(0.0),
pitch_(0.0)
{
}

void BallCamLinkageManager::SlotToTrigBallCamData(double yaw, double pitch)
{
	//yaw����
	//pitchά��
	yaw = -DEG(yaw);
	pitch = DEG(pitch);


	yaw_ = -yaw;
	pitch_ = pitch;


	//����ת��
	yaw = yaw + 180;
	pitch =90 - pitch;


	if (pitch >= 180)
	{
		pitch = pitch - 180;
	}
	while (yaw >= 360)
	{
		yaw = yaw - 360;
	}
	while (yaw<0)
	{
		yaw = yaw + 360;
	}
	
	int x = (int)pitch / 45 + 1;
	int y = (int)yaw / 90 + 1;
	int cam_point = 4 * (x-1) + y;

	//��ͣ������̨�����Ῠ�õ�Ƭ���л������ʱ���ٵ���
	if (last_ball_cam_point_num_ != cam_point)
	{
		last_ball_cam_point_num_ = cam_point;

		//29��������Ԥ�õ�
		emit SignalToTrigBallCamLinkage(cam_point, 39);
	}



}

