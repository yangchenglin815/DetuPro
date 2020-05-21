
#include <QPainter>
#include <QGraphicsView>

#include "directionArrowWgt.h"
#include "myQGraphicsScene.h"
#include "ArrowItem.h"

#include "math.h"

//全局控制器
#include "BallCamLinkageManager.h"
#include "MessageManager.h"
#include "SocketManager.h"
#include "TcpDataManager.hpp"
#include "ListAndGLWindowManager.h"
#include "MapPointListManager.h"
#include "SequencerManager.h"

#define DEG(r) ( 180.0 * (r) / M_PI )
#define RAD(d) ( M_PI * (d) / 180.0 )

const int arrowWidth = 30;
const int arrowHeight = 20;
const int lineWidth = 8;
const int space = 5;

directionArrowWgt::directionArrowWgt(QWidget *parent) : QWidget(parent)
  , m_PosX(0)
  , m_PosY(arrowHeight)
  , m_onArrow_flag(0)
  , last_yaw_(0.0)
{
    setMouseTracking(true);
    init();
}

void directionArrowWgt::paintEvent(QPaintEvent *event)
{

}

void directionArrowWgt::mousePressEvent(QMouseEvent *event)
{

    QWidget::mousePressEvent(event);
}

void directionArrowWgt::mouseMoveEvent(QMouseEvent *event)
{

    QWidget::mouseMoveEvent(event);
}

void directionArrowWgt::init()
{


}



void directionArrowWgt::setArrow(PanoMapPointInfo_t panoMapInfo)
{
	scene_ = new myQGraphicsScene(this);
	scene_->setSceneRect(0, 0, width(), height());
	scene_->setItemIndexMethod(QGraphicsScene::NoIndex);

	view_ = new QGraphicsView(scene_, this);

	view_->setRenderHint(QPainter::Antialiasing);
	view_->setStyleSheet("background: transparent;border:0px");
	view_->setCacheMode(QGraphicsView::CacheBackground);

	view_->show();

	QMapIterator<int, float> i(panoMapInfo.sequencer_point_info_map_);
	while (i.hasNext())
	{
		i.next();
		i.value();
		addPixItem(i.key(), i.value());
	}

}

void directionArrowWgt::addPixItem(int id, double yaw)
{
	//弧度转化
	double	yaw_angle = 90-DEG(yaw);

	ArrowItem *item = new ArrowItem(id,yaw_angle);
	item->setMyPixMap(":/image/image/Sequencer_prev.png");
	item->setTransformOriginPoint(51, -20);
	QTransform transform;
	transform.rotate(45, Qt::XAxis);
	item->setTransform(transform);
	item->setPos(width() / 2 - 51, height() / 2 + 20);

	item->setRotation(yaw_angle);
	scene_->addItem(item);
	arrow_list_.append(item);
}

void directionArrowWgt::slotToTrigArrowRotate(double yaw, double pitch)
{
	if (last_yaw_==yaw)
	{
		//不动的话 不旋转，有点卡
		return;
	}
	else
	{
		last_yaw_ = yaw;
		for (int i = 0; i < arrow_list_.size(); i++)
		{
			//需要加上初始角度
			QTransform transform;
			double	pitch_angle = pitch;
			transform.rotate((90 - pitch_angle) / 2 + 45, Qt::XAxis);
			arrow_list_.at(i)->setTransform(transform);

			//弧度转化
			arrow_list_.at(i)->setRotation(arrow_list_.at(i)->getInitialValue() + yaw);
		}
	}

}
