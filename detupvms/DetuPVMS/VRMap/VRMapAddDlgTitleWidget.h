#ifndef VRMAPADDDLGTITLEWIDGET_H
#define VRMAPADDDLGTITLEWIDGET_H

#include <QWidget>
#include "ui_VRMapAddDlgTitleWidget.h"

class VRMapAddDlgTitleWidget : public QWidget
{
	Q_OBJECT

public:
	VRMapAddDlgTitleWidget(QWidget *parent = 0);
	~VRMapAddDlgTitleWidget();
	void setTitleText(QString text_1, QString text_2);
	void setCheckBoxChecked(bool checked);
signals:
	void stateChanged(int checkState);
private:
	Ui::VRMapAddDlgTitleWidget ui;
};

#endif // VRMAPADDDLGTITLEWIDGET_H
