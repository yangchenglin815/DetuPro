/************************************************
* \file loginWidget.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* µÇÂ½½çÃæ
************************************************/
#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include "ui_loginWidget.h"
#include "bubbleWidget.h"

class loginWidget : public QWidget
{
	Q_OBJECT

public:
	loginWidget(QWidget *parent = 0);
	~loginWidget();
	void closeBubble();
signals:
	void sigOnClose();
	void sigOnLogin();
	void sigOnForget();
	void sigOnSetDlgModal(bool modal);
protected:
	void keyPressEvent(QKeyEvent *event);
	void mousePressEvent(QMouseEvent *event);
	bool eventFilter(QObject *watched, QEvent *event);
private slots:
void slot_loginDetu();
void slotOnLoginChecked(std::string cuuid, short result);
private:
	void initConnect();
	void init();
private:
	Ui::loginWidget ui;
	bubbleWidget *bubble_;
	int nXPos_;
	int nYPos_;
};

#endif // LOGINWIDGET_H
