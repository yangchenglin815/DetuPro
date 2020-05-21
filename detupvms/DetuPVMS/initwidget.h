/************************************************
* \file playmodewgt.h
*
* \author HuZhengdong
* \date 20171127
* 播放界面初始画面，设置透明浮在glwindow上
************************************************/

#ifndef INITWIDGET_H
#define INITWIDGET_H

#include <QWidget>
#include "ui_initwidget.h"

class initWidget : public QWidget
{
	Q_OBJECT

public:
	initWidget(QWidget *parent = 0);
	~initWidget();


	void setLabelText(QString text);
private:
	Ui::initWidget ui;
};

#endif // INITWIDGET_H
