#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include "ui_settingWidget.h"

class settingWidget : public QWidget
{
	Q_OBJECT

public:
	settingWidget(QWidget *parent = 0);
	~settingWidget();
signals:
	void sigOnCloseDlg();
protected:
	bool eventFilter(QObject *watched, QEvent *event);
private slots:
	void slot_autoClicked();
private:
	void init();
	void initConnect();
private:
	Ui::settingWidget ui;
	bool isAuto_;
};

#endif // SETTINGWIDGET_H
