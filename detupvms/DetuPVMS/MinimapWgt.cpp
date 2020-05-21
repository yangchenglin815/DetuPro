#include <QGraphicsView>

#include "MinimapWgt.h"
#include "MiniMapPointItem.h"

#include "myQGraphicsScene.h"

//初始化控制器
#include "MessageManager.h"
#include "SocketManager.h"
#include "TcpDataManager.hpp"
#include "ListAndGLWindowManager.h"
#include "MapPointListManager.h"

MinimapWgt::MinimapWgt(QWidget *parent)
	: QWidget(parent),
	view_(NULL),
	scene_(NULL),
	last_yaw_(0.0)
{
	ui.setupUi(this);
	setMouseTracking(true);
	ui.mapWgt_->setMouseTracking(true);


}

MinimapWgt::~MinimapWgt()
{

}

void MinimapWgt::init()
{

}

void MinimapWgt::initConnect()
{

}



void MinimapWgt::setCurrPlayInfo(PanoMapPointInfo_t info)
{
	m_panoPointInfo = info;
}

void MinimapWgt::drawAllMiniPoint()
{
	//每次重置
	if (scene_!=NULL)
	{
		scene_->deleteLater();
		scene_ = NULL;
	}
	if (view_ != NULL)
	{
		view_->deleteLater();
		view_ = NULL;
	}


	scene_ = new myQGraphicsScene(ui.mapWgt_);
	scene_->setSceneRect(0, 0, 320,155);

	scene_->setItemIndexMethod(QGraphicsScene::NoIndex);

	view_ = new QGraphicsView(scene_, ui.mapWgt_);

	view_->setRenderHint(QPainter::Antialiasing);
	view_->setStyleSheet("background: transparent;border:0px");
	view_->setCacheMode(QGraphicsView::CacheBackground);
	view_->resize(320, 155);
	view_->show();


	PanoMap_t panoMap = MapPointListManagerIns.getMap();

	for (int j = 0; j < panoMap.panoramaList.size(); j++)
	{
		if (panoMap.panoramaList[j].onMapFlag)
		{
			MiniMapPointItem *mini_point_map_item = new MiniMapPointItem(panoMap.panoramaList.at(j));
			if (panoMap.panoramaList[j]==m_panoPointInfo)
			{
				curr_map_point_item_ = mini_point_map_item;
				mini_point_map_item->setPix();
				mini_point_map_item->setPos(int(panoMap.panoramaList.at(j).pos_x*width()) - 14, int(panoMap.panoramaList.at(j).pos_y*height()) - 22);
				mini_point_map_item->setTransformOriginPoint(21, 30);
			}			
			else
			{
				mini_point_map_item->setPos(int(panoMap.panoramaList.at(j).pos_x*width()), int(panoMap.panoramaList.at(j).pos_y*height()));
			}


			
			scene_->addItem(mini_point_map_item);
			mini_map_point_item_list_.insert(j, mini_point_map_item);
			mini_point_map_item->show();
		}
	}

}

void MinimapWgt::slotToTrigArrowRotate(double yaw, double pitch)
{
	if (last_yaw_ == yaw)
	{
		//不动的话 不旋转，有点卡
		return;
	}
	else
	{
		last_yaw_ = yaw;
		curr_map_point_item_->setRotation(yaw - m_panoPointInfo.initial_angle + 155);
	}
}
