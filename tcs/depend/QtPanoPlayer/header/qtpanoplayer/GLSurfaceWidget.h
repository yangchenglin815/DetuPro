#pragma once
#include "GLSurfaceRender.h"
#include "glew.h"
#include <QOpenGLWidget>
#include <QtGui/QVector2D>
#include <QMouseEvent>
#include <QTime>
#include <QTimer>
#include <QThread>
#include <QtCore/QDebug>

class GLSurfaceWidgetPrivate;

namespace DetuPanoPlayer {
    
    class MotionEvent;
    
class GLSurfaceWidget : public QOpenGLWidget, public IGestureListener
{
	Q_OBJECT
public:
	GLSurfaceWidget(GLSurfaceRender* render);
	GLSurfaceWidget(GLSurfaceRender* render, int fps);
	~GLSurfaceWidget();
	void onPause();
	void onResume();
	void onStop();

	void setZoomEnable(bool toggle);

	void setRender(GLSurfaceRender* render);

signals:
	//鼠标移动事件触发球机联动数据管理器
	void SignalToTrigBallCamData(double yaw, double pitch);

private slots:
	void UpdateView();


private:
    int windowRatio;
private:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
	void setPlaying(bool playing);
    void updateMotionEvent(QMouseEvent* event);

protected:
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void mouseDoubleClickEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void wheelEvent(QWheelEvent* event);
    void enterEvent(QEvent* event);
	void upEvent(QEvent *event);
	void onGestureRequestData(GestureData* gestureData,float *gyoEuler, bool isFlat, float *fovadd, float *yawadd, float *pitchadd);
protected:
	GLSurfaceRender* render_;

	//鼠标操作缩放等
	QPoint last_mouse_pos_;
	QVector2D cur_camera_pos_;//QVector(theta, phi)
	double cur_lon_; // 当前经度
	double cur_lat_; // 当前纬度
	double last_lon_;
	double last_lat_;
	double step_lon_;
	double step_lat_;
	double detax_;
	double detay_;
	bool is_stretching_ = false;
	int last_width_;
	double wheeldegree_;//The degree of the mouse's response to one scrolling
	bool isUpdated_;
	float fovadd_;
	float pitchadd_;
	float yawadd;
	QTime startTime;
	QTime endTime;
	bool isflat_;
	bool ismove_;
	QRect screenRect_;
	QPoint last_pos_;
    QCursor cursor;//Current mouse style

	bool mIsPlaying;
	int fps_;
	QTimer* renderTimer_;
	QThread* updateThread;
    MotionEvent* mMotionEvent;
    int windowWidth;
    int windowHeight;
    int processtime;//Statistics(tongji) mouse response time
    int responsenum ;//Record the number of mouse responses
    

};
    
}
