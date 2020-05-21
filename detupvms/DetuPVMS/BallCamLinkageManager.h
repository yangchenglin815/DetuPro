/************************************************
* \file BallCamLinkageManager.h
*
* \author HuZhengdong
* \date 20171025
* 球机联动数据控制管理器
************************************************/
#pragma once

#include <iostream>
#include <string>
#include <map>
#include <QObject>
#include <memory>

#include "UiSingleton.h"

#define  BallCamLinkageManagerIns BallCamLinkageManager::Instance()

class BallCamLinkageManager : public QObject, public CUiSingleton<BallCamLinkageManager>
{
	Q_OBJECT
		friend class CUiSingleton<BallCamLinkageManager>;
public:
	BallCamLinkageManager();

	double getYaw(){ return yaw_; };
public slots:
void SlotToTrigBallCamData(double yaw, double pitch);

signals:
	void SignalToTrigBallCamLinkage(int pre_point_num, int contral_type);

private:
	int last_ball_cam_point_num_;
	double yaw_;
	double pitch_;
	
};

