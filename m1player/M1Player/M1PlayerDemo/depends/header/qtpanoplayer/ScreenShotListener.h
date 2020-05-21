#ifndef SCREEN_SHOT_LISTENER_H
#define SCREEN_SHOT_LISTENER_H

/************************************************************************/
/* 截屏结构体，获取数据格式为RGBA                                       */
/************************************************************************/

namespace DetuPanoPlayer {
typedef struct ScreenShot
{
	int width;
	int height;
	unsigned char* data;
} ScreenShot;

class ScreenShotListener
{
public:
	ScreenShotListener(){}
	~ScreenShotListener(){}
	virtual void onScreenShotFinished(ScreenShot* screenShot) = 0;
};
    
}

#endif
