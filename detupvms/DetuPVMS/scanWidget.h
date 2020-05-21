#ifndef SCANWIDGET_H
#define SCANWIDGET_H

#include <QWidget>
#include "ui_scanWidget.h"

class scanWidget : public QWidget
{
	Q_OBJECT

public:
	scanWidget(QWidget *parent = 0);
	~scanWidget();
	void setUrlText(QString text);

public slots:
    //ÉèÖÃ×¥Í¼Â·¾¶
    void SetCapturePath();

private:
	Ui::scanWidget ui;
};

#endif // SCANWIDGET_H
