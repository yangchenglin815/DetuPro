/************************************************
* \file consoletabwidget.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* 主界面上的tabwidget
************************************************/
#ifndef CONSOLETABWIDGET_H
#define CONSOLETABWIDGET_H

#include <QWidget>
#include "ui_consoletabwidget.h"

class consoleTabWidget : public QWidget
{
	Q_OBJECT

public:
	consoleTabWidget(QWidget *parent = 0);
	~consoleTabWidget();
	void setSelectedStatus(bool selected);
protected:
	virtual void mousePressEvent(QMouseEvent *event);

signals:
	//tab上控制台按钮点击事件
	void TrigTabConsoleButtonClicked();


private:
	Ui::consoleTabWidget ui;
};

#endif // CONSOLETABWIDGET_H
