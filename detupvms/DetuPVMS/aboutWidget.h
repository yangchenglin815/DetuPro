/************************************************
* \file aboutWidget.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* ¹ØÓÚµ¯´°
************************************************/

#ifndef ABOUTWIDGET_H
#define ABOUTWIDGET_H

#include <QWidget>
#include "ui_aboutWidget.h"

class aboutWidget : public QWidget
{
	Q_OBJECT

public:
	aboutWidget(QWidget *parent = 0);
	~aboutWidget();
private:
	void init();
private:
	Ui::aboutWidget ui;
};

#endif // ABOUTWIDGET_H
