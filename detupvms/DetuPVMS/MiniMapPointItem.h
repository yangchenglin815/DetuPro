/************************************************
* \file MiniMapPointItem.h
*
* \author HuZhengdong
* \date 20171128
* 地图缩略图，上的地图点
************************************************/
#pragma once

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

#include "constStruct.h"

class MiniMapPointItem : public QObject, public QGraphicsPixmapItem
{
public:
	MiniMapPointItem();
	MiniMapPointItem(PanoMapPointInfo_t info);

	~MiniMapPointItem();

	void setPix();
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

	bool is_playing_;

private:
	PanoMapPointInfo_t m_info_;
};

