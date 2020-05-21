/************************************************
* \file gviewsetingwgt.h
*
* \author HuZhengdong
* \date 20170118
* 全景地图上，相机视角设置的滑动区域
************************************************/
#ifndef GLVIEWSETTINGITEMWGT_H
#define GLVIEWSETTINGITEMWGT_H

#include <QWidget>
#include "ui_GlViewSettingItemWgt.h"

class GlViewSettingItemWgt : public QWidget
{
	Q_OBJECT

public:
	GlViewSettingItemWgt(QWidget *parent = 0);
	~GlViewSettingItemWgt();

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
private:
	Ui::GlViewSettingItemWgt ui;
};

#endif // GLVIEWSETTINGITEMWGT_H
