/************************************************
* \file gviewsetingwgt.h
*
* \author HuZhengdong
* \date 20171128
* 地图点设置界面，包括调整视角、路径连接、移除
************************************************/
#ifndef MAPPOINTSETINGWGT_H
#define MAPPOINTSETINGWGT_H

#include <QWidget>
#include "ui_MapPointSetingWgt.h"

class MapPointSetingWgt : public QWidget
{
	Q_OBJECT

public:
	MapPointSetingWgt(QWidget *parent = 0);
	~MapPointSetingWgt();
private:
	void init();
	void initConnect();
signals:
	void sigOnGviewBtnClicked();
	void sigOnConnBtnClicked();
	void sigOnDeleteBtnClicked();
public slots:
	void slotOnGviewBtnClicked();
	void slotOnConnBtnClicked();
	void slotOnDeleteBtnClicked();
private:
	Ui::MapPointSetingWgt ui;
};

#endif // MAPPOINTSETINGWGT_H
