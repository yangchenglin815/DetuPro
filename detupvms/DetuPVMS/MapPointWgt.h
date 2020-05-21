/************************************************
* \file MapPointWgt.h
*
* \author HuZhengdong
* \date 20171128
* µØÍ¼µã
************************************************/
#ifndef MAPPOINTWGT_H
#define MAPPOINTWGT_H

#include <QWidget>
#include <QMouseEvent>
#include "ui_MapPointWgt.h"

#include "constStruct.h"

class MapPointWgt : public QWidget
{
	Q_OBJECT

public:
	MapPointWgt(QWidget *parent = 0);
	~MapPointWgt();

	void setMapPointInfo(const PanoMapPointInfo_t &panoMapInfo);
	void getMapPointInfo(PanoMapPointInfo_t &panoMapInfo);
	void setMapPointTitle(QString title);
	void setMapPointType(MapPointType type);
	void updatePoint(QPoint point,int width,int height);
	void removePointInfo(int key);
	void updatePointInfo(int key, float value);
signals:
	void sigOnDragCurrMapPoint(PanoMapPointInfo_t panoMapInfo);
	void sigOnSettingPointPath(PanoMapPointInfo_t panoMapInfo);
	void sigOnDoubleCurrMapPoint(PanoMapPointInfo_t panoMapPointInfo);

public slots:
	void slotOnUpdateInitAngle(float init_angle);
protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
private:
	void init();
	void initConnect();
private:
	Ui::MapPointWgt ui;
	PanoMapPointInfo_t m_panoMapInfo;


};

#endif // MAPPOINTWGT_H
