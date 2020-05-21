/************************************************
* \file ReplayCtrWgt.h
*
* \author yangchenglin
* \date 20180109
* 封装的回放控制界面
************************************************/
#ifndef REPLAYCTRWGT_H
#define REPLAYCTRWGT_H0

#include <QWidget>
#include "ui_ReplayCtrWgt.h"

class ReplayCtrWgt : public QWidget
{
	Q_OBJECT

public:
	ReplayCtrWgt(QWidget *parent = 0);
	~ReplayCtrWgt();

	void setSpeedPos(int width);
	int getDurationBySlider();
	void initData(QList<m_replayInfoList> infoList);
	QString getSelectedDate();

private:
	Ui::ReplayCtrWgt ui;
};

#endif // REPLAYCTRWGT_H
