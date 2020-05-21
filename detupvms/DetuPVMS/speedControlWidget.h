#ifndef SPEEDCONTROLWIDGET_H
#define SPEEDCONTROLWIDGET_H

#include <QWidget>
#include "ui_speedControlWidget.h"

class speedControlWidget : public QWidget
{
	Q_OBJECT

public:
	speedControlWidget(QWidget *parent = 0);
	~speedControlWidget();
	void setFastBtnEnable(bool enable);
	void setSlowBtnEnable(bool enable);
	void setSpeedLabel(QString speed);
signals:
	void sigOnFastPlay();
	void sigOnSlowPlay();
private:
	void init();
	void initConnect();
private:
	Ui::speedControlWidget ui;
};

#endif // SPEEDCONTROLWIDGET_H
