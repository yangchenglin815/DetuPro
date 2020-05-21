#ifndef MAPTOOLWIDGET_H
#define MAPTOOLWIDGET_H

#include <QWidget>
#include "ui_mapToolWidget.h"

class mapToolWidget : public QWidget
{
	Q_OBJECT

public:
	mapToolWidget(QWidget *parent = 0);
	~mapToolWidget();
	void setCurrPlayInfo(PanoMapPointInfo_t info);
	void setBackground();
	void initData(PanoSceneInfo info);
	void setPicGroupPage(bool isChecked);
	void setMiniMapPage(bool isChecked);
signals:
	void sigOnBindPTZWarning();
	void sigOnPTZPlayStatus(bool success);
	void sigOnHiddenPicGroup();
	void sigOnHiddenMiniMap();

	void SignalToSetSwtichScreen(int button_num);
public slots:
	void slotToTrigArrowRotate(double yaw, double pitch);
	void slotOnHiddenPicGroup();
	void slotOnHiddenMiniMap();

private:
	Ui::mapToolWidget ui;
};

#endif // MAPTOOLWIDGET_H
