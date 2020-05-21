#include "GLRenderThread.h"


GLRenderThread::GLRenderThread(QGLWidget* glView, int frameRate, QObject* parent) : QThread(parent), flag(false)
{
	this->glView = glView;
	this->frameRate = 25;// frameRate;
}

void GLRenderThread::run()
{
	if (frameRate <= 0)
	{
		return;
	}
	unsigned long sleepTime = (unsigned long)(1000 * 1.0 / frameRate);
	while (!flag)
	{
		msleep(sleepTime);
		glView->update();
	}
}
