#ifndef TIMEDURATIONWIDGET_H
#define TIMEDURATIONWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

#include "constStruct.h"

class timeDurationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit timeDurationWidget(QWidget *parent = 0);
    void initData(m_replayInfoList infoList);
	void setRecoderPos(int time);
	void resetRadition();
	void setWidth(int width);
	void updateSliderPos(int duration);
	void setMoveEnabled(bool enable);
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void wheelEvent(QWheelEvent *event);
signals:
    void sigOnAddDuration();
    void sigOnDecreaseDuration();
    void sigOnGetCurrentX(int x);
	void sigOnRequestReplayRadio(int time, int duration);
	void sigOnUpdateSlider(int x);
	private slots:
	void slotOnUpdateFlag();
private:
    //滑块坐标
    int arrowXPos_;
    int arrowYPos_;
    m_replayInfoList m_infoList;
    int space_;
    int duration_;
    bool needed_;
	QString curr_time;
	int mWidth_;
	int curr_time_;
	bool m_moveabled;
	bool bPressed;
};

#endif // TIMEDURATIONWIDGET_H
