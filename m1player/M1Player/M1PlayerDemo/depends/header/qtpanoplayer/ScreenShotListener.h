#ifndef SCREEN_SHOT_LISTENER_H
#define SCREEN_SHOT_LISTENER_H

/************************************************************************/
/* �����ṹ�壬��ȡ���ݸ�ʽΪRGBA                                       */
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
