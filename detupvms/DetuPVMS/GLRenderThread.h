#pragma once
#include <QThread>
#include <QOpenGLWidget>
#include <QtOpenGL/QGLWidget>


typedef enum GLRenderThreadState {
	STARTED, 
}GLRenderThreadState;

class GLRenderThread : public QThread
{
public:
	GLRenderThread(QGLWidget* glView, int frameRate, QObject* parent = 0);
	void resume();
	void pause();
	void stop();
protected:
	QGLWidget* glView;
	int frameRate;
	bool flag;
	void run();
};

