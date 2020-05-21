/************************************************
* \file gviewsetingwgt.h
*
* \author HuZhengdong
* \date 20171128
* ��ͼ�����ý��棬���������ӽǡ�·�����ӡ��Ƴ�
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
