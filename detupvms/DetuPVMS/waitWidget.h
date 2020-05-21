#ifndef WAITWIDGET_H
#define WAITWIDGET_H

#include <QWidget>
#include "ui_waitWidget.h"

class waitWidget : public QWidget
{
	Q_OBJECT

public:
	waitWidget(QWidget *parent = 0);
	~waitWidget();

private:
	Ui::waitWidget ui;
};

#endif // WAITWIDGET_H
