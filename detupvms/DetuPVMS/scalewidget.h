#ifndef SCALEWIDGET_H
#define SCALEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class scaleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit scaleWidget(QWidget *parent = 0);
    void setScale(int x);
	void setCurrTime(int time);
	void resetRadition();
	void setRecoderPos(int time);
signals:
	void sigOnRequestReplayRadio(int time);
protected:
    void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
private:
	int nx_;
	int ny_;
	float m_space;
	QString curr_time_;
};

#endif // SCALEWIDGET_H
