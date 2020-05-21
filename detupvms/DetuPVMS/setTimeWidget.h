#ifndef SETTIMEWIDGET_H
#define SETTIMEWIDGET_H

#include <QWidget>
#include "ui_setTimeWidget.h"

class setTimeWidget : public QWidget
{
	Q_OBJECT

public:
	setTimeWidget(QWidget *parent = 0);
	~setTimeWidget();
	void initStyleSheet();
protected:
	void enterEvent(QEvent *event);
	void leaveEvent(QEvent *event);
signals:
	void sigOnEditFinished(QString request_time);
private slots:
	void slotOnClicked();
	void slotOnEditFinished();
private:
	void initConnect();
private:
	Ui::setTimeWidget ui;
	QString last_request_time;
};

#endif // SETTIMEWIDGET_H
