/************************************************
* \file gviewsetingwgt.h
*
* \author HuZhengdong
* \date 20171128
* 全景地图上，相机视角设置窗口
************************************************/
#ifndef GVIEWSETINGWGT_H
#define GVIEWSETINGWGT_H

#include <QWidget>
#include "ui_GlViewsetingwgt.h"

#include "constStruct.h"

class GlViewSettingItemWgt;
class myQGraphicsScene;

class GlViewSetingWgt : public QWidget
{
	Q_OBJECT

public:
	GlViewSetingWgt(QWidget *parent = 0);
	~GlViewSetingWgt();

	void setPanoParam(PanoMapPointInfo_t panoramaInfo);

signals:
	void sigOnUpdateInitAngle(float init_angle);
public slots:

	void slotOnConfirmClicked();
protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:
	void setPanoImg(QString img_path);
private:
	Ui::GlViewSetingWgt ui;

	PanoMapPointInfo_t panoramaInfo_;

	GlViewSettingItemWgt *gl_view_setting_item_;


	QPoint delta_pos_;
	QPoint last_pos_;
};

#endif // GVIEWSETINGWGT_H
