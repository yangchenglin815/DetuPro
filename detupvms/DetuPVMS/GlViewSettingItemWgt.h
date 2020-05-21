/************************************************
* \file gviewsetingwgt.h
*
* \author HuZhengdong
* \date 20170118
* ȫ����ͼ�ϣ�����ӽ����õĻ�������
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
