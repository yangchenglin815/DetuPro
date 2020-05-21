/************************************************
* \file StitchStatusMachine.h
*
* \author HuZhengdong
* \date 20180316
* 双击播放开始后的状态机
************************************************/
#ifndef STITCHSTATUSMACHINE_H
#define STITCHSTATUSMACHINE_H

#include "constStruct.h"

class StitchStatusMachine
{
public:
	StitchStatusMachine();
	~StitchStatusMachine();

public:
	void setStitchStatus(StitchStatus stitch_status);
	//状态机处理函数，处理从双击列表到播放的状态流转
	void StitchStatusMachineFunc();
private:
	void StitchStatusCommunication();
	void StitchStatusGetSrs();
	void StitchStatueCheckStitchPara();
	void StitchStatusCapture();
	void StitchStatusCreatWt();
	void StitchStatusOptimize();
	void StitchStatusCalibration();
};

#endif // STITCHSTATUSMACHINE_H
