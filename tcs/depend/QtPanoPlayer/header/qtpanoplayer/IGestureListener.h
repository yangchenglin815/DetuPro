#ifndef IGestureListener_h__
#define IGestureListener_h__

#include <iostream>
using namespace std;

namespace DetuPanoPlayer {
    
typedef struct GestureData
{
    float pitch;//欧拉角y方向变量
    float yaw;//欧拉角x方向变量
    float roll;//欧拉角z方向变量
    float fov;//非平面模式的透视投影角
    float scale;//2:1平面模式的缩放值
    float x_offset;//2:1平面模式的x偏移量
    float y_offset;//2:1平面模式的y偏移量
    bool isgestureaction;//判断当前是否有手势动作，自动旋转播放时控制当前是否旋转
    bool isfovscale;//判断当前是否是正在缩放操作

} GestureData;

class IGestureListener
{
public:
	IGestureListener(){}

	virtual ~IGestureListener(){}

	virtual void onGestureRequestData(GestureData* gestureData,float *gyoEuler, bool isFlat, float *fovadd, float *yawadd, float *pitchadd) = 0;
};
}

#endif
