/************************************************
* \file MinimapWgt.h
*
* \author HuZhengdong
* \date 20171128
* 地图缩略图，右上角展示，类似球机界面
************************************************/
#ifndef MINIMAPWGT_H
#define MINIMAPWGT_H

#include <QWidget>
#include "ui_MinimapWgt.h"

#include "constStruct.h"

class MiniMapPointItem;
class myQGraphicsScene;

class MinimapWgt : public QWidget
{
	Q_OBJECT

public:
	MinimapWgt(QWidget *parent = 0);
	~MinimapWgt();

	void init();
	void initConnect();

	void setCurrPlayInfo(PanoMapPointInfo_t info);
	void drawAllMiniPoint();
signals:
	void sigOnHiddenMiniMap();

public slots:
	void slotToTrigArrowRotate(double yaw, double pitch);

private:
	Ui::MinimapWgt ui;

	MiniMapPointItem *curr_map_point_item_;
	QMap<int, MiniMapPointItem*> mini_map_point_item_list_;

	myQGraphicsScene *scene_;
	QGraphicsView *view_;

	PanoMapPointInfo_t m_panoPointInfo;

	double last_yaw_;
};

#endif // MINIMAPWGT_H
