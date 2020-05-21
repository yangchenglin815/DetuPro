#ifndef PANEWIDGET_H
#define PANEWIDGET_H

#include <QWidget>
#include "ui_paneWidget.h"

class paneWidget : public QWidget
{
	Q_OBJECT

public:
	paneWidget(QWidget *parent = 0);
	~paneWidget();
	void setButtonNum(int num);
	int getButtonStatus();
	void setButtonStatus(bool checked);
	void setButtonEnabled(bool enabled);
private slots:
	void slotOnClicked(bool checked);
signals:
	//全景画面预置点按钮的点击事件
	void sigOnClicked(bool checked, int num);
	void sigOnStepOnPoint(int num);
private:
	Ui::paneWidget ui;
};

#endif // PANEWIDGET_H
