#include "MiniMapPointItem.h"
#include "ViewSignal.h"

MiniMapPointItem::MiniMapPointItem()
{
}


MiniMapPointItem::MiniMapPointItem(PanoMapPointInfo_t info)
	:is_playing_(false)
{
	m_info_ = info;
	if (m_info_.curr_id == -1)
	{
		return;
	}

	switch (m_info_.map_point_type)
	{
	case PANOSCENE_ON_LINE:
	{
		setPixmap(QPixmap(":/image/image/miniPointOnLine.png"));
		break;
	}
	case PANOSCENE_OFF_LINE:		
	{	
		setPixmap(QPixmap(":/image/image/miniPointOffLine.png"));
		break;
	}
	case DEVICE_ON_LINE:			
	{
		setPixmap(QPixmap(":/image/image/miniPointOnLine.png"));
		break;
	}
	case DEVICE_OFF_LINE:			
	{
		setPixmap(QPixmap(":/image/image/miniPointOffLine.png"));
		break;
	}
	default:
		break;
	}
	this->setScale(0.5);
}

MiniMapPointItem::~MiniMapPointItem()
{
	is_playing_ = false;
}

void MiniMapPointItem::setPix()
{
	is_playing_ = true;
	setPixmap(QPixmap(":/image/image/currMiniPointOnLine.png"));
}

void MiniMapPointItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	ViewSignal::instance()->sigOnArrowClicked(m_info_.curr_id);
	QGraphicsItem::mousePressEvent(event);
}

void MiniMapPointItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsItem::mouseReleaseEvent(event);
}
