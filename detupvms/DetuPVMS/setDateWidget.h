#ifndef SETDATEWIDGET_H
#define SETDATEWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include "ui_setDateWidget.h"

class setDateWidget : public QWidget
{
	Q_OBJECT

public:
	setDateWidget(QWidget *parent = 0);
	~setDateWidget();
	void setSelectedDate(QString date);
	QString getSelectedDate();
	void initStyleSheet();
signals:
	void sigOnShowCalendar();
protected:
	void enterEvent(QEvent *event);
	void leaveEvent(QEvent *event);
	void mousePressEvent(QMouseEvent *event);
private:
	void init();
private:
	Ui::setDateWidget ui;
	QString m_date;
};

#endif // SETDATEWIDGET_H
