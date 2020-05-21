/************************************************
* \file VRViewWidget.h
*
* \author HuZhengdong
* \date 20171218
* ȫ����ͼԤ������
************************************************/
#ifndef VRVIEWWIDGET_H
#define VRVIEWWIDGET_H

#include <QWidget>
#include "ui_VRViewWidget.h"

class VRViewWidget : public QWidget
{
	Q_OBJECT

public:
	VRViewWidget(QWidget *parent = 0);
	~VRViewWidget();

	void clearPlayerStatus();

	void setPosMove();

public slots:
    void slotOnSetMapView();

	//ˢ�µ�ͼ��С
	void slotOnResizePreviewMap();



signals:
	void sigOnStepOnMapSettings();
private:
	void initConnect();
private:
	Ui::VRViewWidget ui;

	bool is_map_load_;
};

#endif // VRVIEWWIDGET_H
