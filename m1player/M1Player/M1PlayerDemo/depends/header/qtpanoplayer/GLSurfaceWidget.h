#pragma once
#include "GLSurfaceRender.h"
#include "glew.h"
#include <QOpenGLWidget>
#include <QtGui/QVector2D>
#include <QMouseEvent> 


class GLSurfaceWidgetPrivate;

namespace DetuPanoPlayer {

class GLSurfaceWidget : public QOpenGLWidget, public IGestureListener
{
	Q_OBJECT
public:
	GLSurfaceWidget(GLSurfaceRender* render);
	GLSurfaceWidget(GLSurfaceRender* render, int fps);
	~GLSurfaceWidget();

	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

	void pause();
	void resume();
	void close();
private:
	GLSurfaceRender* render;
	bool stopFlag;

	//���������ŵ�
	QPoint last_mouse_pos;
	QVector2D cur_camera_pos;//QVector(theta, phi)
	double cur_lon; // ��ǰ����
	double cur_lat; // ��ǰγ��
	double last_lon;
	double last_lat;
	double step_lon;
	double step_lat;
	bool is_stretching = false;
	int last_width;
	double wheeldegree;
	bool isUpdated ;
	GestureData *data;
private slots:
	void UpdateView();
	void setPlaying(bool playing);

protected:
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void mouseDoubleClickEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void wheelEvent(QWheelEvent* event);
	void enterEvent(QEvent* event);
	void upEvent(QEvent *event);
	void onGestureRequestData(GestureData* gestureData, bool isflat) override;

private:
	bool isPlaying;
	int fps;
};
    
}
