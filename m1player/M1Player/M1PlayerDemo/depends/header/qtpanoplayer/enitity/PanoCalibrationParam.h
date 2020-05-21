#pragma once
class PanoCalibrationParam
{
public:
	PanoCalibrationParam();
	~PanoCalibrationParam();

	int dr;
	int centerX;
	int centerY;
	int yaw;
	int pitch;
	int roll;
	int a;
	int b;
	int c;
	int d;
	int e;
};

