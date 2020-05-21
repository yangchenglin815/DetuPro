#pragma once
#include <QThread>
#include <QOpenGLWidget>
#include <QMutex> 
#include <QWaitCondition> 

typedef enum GLRenderThreadState {
	GLRenderThreadState_STARTED, GLRenderThreadState_PAUSED, GLRenderThreadState_STOPED
} GLRenderThreadState;

class GLRenderThread : public QThread
{
public:
	GLRenderThread(QOpenGLWidget* glView, int frameRate, QObject* parent = 0);
	~GLRenderThread();
	void stop();
	void pause();
	void resume();
protected:
	QOpenGLWidget* glView;
	QMutex* mutex;
	QWaitCondition* cond;
	int frameRate;
	unsigned long sleepTime;
	void run();
private:
	GLRenderThreadState threadState;

	int count;
	int identityId;
};

