#ifndef UPDATEWIDGET_H
#define UPDATEWIDGET_H

#include <QWidget>
#include "ui_updateWidget.h"

class updateWidget : public QWidget
{
	Q_OBJECT

public:
	updateWidget(QWidget *parent = 0);
	~updateWidget();

private:
	Ui::updateWidget ui;
};

#endif // UPDATEWIDGET_H
