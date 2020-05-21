#ifndef PTZPOINTCTRLWIDGET_H
#define PTZPOINTCTRLWIDGET_H

#include <QList>
#include <QWidget>
#include "paneWidget.h"
#include "ui_ptzPointCtrlWidget.h"

class ptzPointCtrlWidget : public QWidget
{
	Q_OBJECT

public:
	ptzPointCtrlWidget(QWidget *parent = 0);
	~ptzPointCtrlWidget();
	void getPointStatus(QString ip);
private:
	void init();

signals:
	//全景画面预置点按钮的点击事件
	void sigOnClicked(bool checked, int num);
	void sigOnStepOnPoint(int num);
private slots:
   void slotOnGetPtzPoint(QString ip, QString point);
   void slotOnClicked(bool checked, int num);
private:
	Ui::ptzPointCtrlWidget ui;
	int m_row;
	int m_column;
	QList<paneWidget*>  widgetList;
	QString pointStatus;
};

#endif // PTZPOINTCTRLWIDGET_H
