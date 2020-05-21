#include "SequencerManager.h"

#define DEG(r) ( 180.0 * (r) / M_PI )
#define RAD(d) ( M_PI * (d) / 180.0 )

SequencerManager::SequencerManager()
{
}


void SequencerManager::SlotToTrigSequencer(double yaw, double pitch)
{
	//yaw经度
	//pitch维度
	yaw = DEG(yaw);
	pitch = DEG(pitch);

	//定点转移
	yaw = yaw + 180;
	pitch = 90 - pitch;

	if (pitch >= 180)
	{
		pitch = pitch - 180;
	}
	while (yaw >= 360)
	{
		yaw = yaw - 360;
	}
	while (yaw < 0)
	{
		yaw = yaw + 360;
	}

	SignalToTrigArrowRotate(yaw,pitch);
}
