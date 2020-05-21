/************************************************
* \file helpPageWidget.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* °ïÖúµ¯´°
************************************************/
#ifndef HELPPAGEWIDGET_H
#define HELPPAGEWIDGET_H

#include <QWidget>
#include "ui_helpPageWidget.h"

class HelpPageWidget : public QWidget
{
	Q_OBJECT

public:
	HelpPageWidget(QWidget *parent = 0);
	~HelpPageWidget();
signals:
void sigOnclickToHelpBtn();
void sigOnclickToAboutBtn();
void sigOnclickToFeedbackBtn();
protected:
	void leaveEvent(QEvent *event);
	void enterEvent(QEvent *event);
private:
	void initConnect();
private:
	Ui::helpPageWidget ui;
};

#endif // HELPPAGEWIDGET_H
