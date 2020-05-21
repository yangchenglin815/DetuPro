/************************************************
* \file StitchStatusMachine.h
*
* \author HuZhengdong
* \date 20180316
* ˫�����ſ�ʼ���״̬��
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
	//״̬���������������˫���б����ŵ�״̬��ת
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
