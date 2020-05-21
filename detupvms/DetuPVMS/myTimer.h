/************************************************
* \file MinimapWgt.h
*
* \author yangchenglin
* \date 20180109
* 回放进度条窗口
************************************************/
#ifndef MYTIMER_H
#define MYTIMER_H

#include <QWidget>
#include <QScrollBar>

#include "constStruct.h"
#include "durationWidget.h"

namespace Ui {
class myTimer;
}

class myTimer : public QWidget
{
    Q_OBJECT
public:
    explicit myTimer(QWidget *parent = 0);
    ~myTimer();
	void initData(QList<m_replayInfoList> infoList);
	void setRecoderPos(int time);
	void resetRadition();
	void setSpeedPos(int w);
	int getDurationBySlider();
	void setMoveEnabled(bool enable);
signals:
	void sigOnRequestReplayRadio(int time, int duration);
private:
    void initConnect();
	void init();
private slots:
    void slotOnValueChanged(int value);
    void slotOnAddDuration();
    void slotOnDecreaseDuration();
    void slotOnGetCurrentX(int x);
	void slotOnUpdateSlider(int x);
	void updateSlider();
private:
    Ui::myTimer *ui;
    durationWidget *durationWgt_;
    m_replayInfoList info_;
    QScrollBar *scrollBar_;
	int currXpos_;
};

#endif // MYTIMER_H
