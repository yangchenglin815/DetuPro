/************************************************
* \file calendarWidget.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* »’¿˙ªÊ÷∆
************************************************/
#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QWidget>
#include "ui_calendarWidget.h"

class calendarWidget : public QWidget
{
	Q_OBJECT

public:
	calendarWidget(QWidget *parent = 0);
	~calendarWidget();
signals:
	void sigOnSetDate(QString date);
private slots:
    void slot_setDate();
private:
	void init();
private:
	Ui::calendarWidget ui;
};

#endif // CALENDARWIDGET_H
