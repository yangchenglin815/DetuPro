#pragma once

namespace DetuPanoPlayer {
    
typedef struct GestureData
{
	float pitch;
	float yaw;
	float roll;
	float fov;
	float scale;
	float x_offset;
	float y_offset;
	bool isgestureaction;//判断是否有手势操作，为自动选择服务

} GestureData;

class IGestureListener
{
public:
	IGestureListener(){}

	~IGestureListener(){}

	virtual void onGestureRequestData(GestureData* gestureData,bool isFlat) = 0;
};
}
