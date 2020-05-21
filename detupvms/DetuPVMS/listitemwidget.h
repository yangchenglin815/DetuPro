#ifndef LISTITEMWIDGET_H
#define LISTITEMWIDGET_H

#include <QWidget>
#include "ui_listitemwidget.h"

namespace Ui {
	class ListItemWidget;
}

class ListItemWidget : public QWidget
{
	Q_OBJECT

public:
	ListItemWidget(QWidget *parent = 0);
	~ListItemWidget();
	void setCheckState(bool state);
	bool getCheckState();

signals:
	void onStateChanged(int state);
    void setSelectItemIDeviceName(QString device_name);
public slots:
    //通知设备名称
    void onStateChangedSlot(int state);

public:
	void setDveiceName(QString devicename);
	void setDeviceStatus(QString status);
	void setCheckBoxVisable(bool check_box_visable);
	void setOnline(bool online);
	QString getDveiceName(){ return ui->devicelabel_->text(); };

private:
	Ui::ListItemWidget *ui;
};

#endif // LISTITEMWIDGET_H
