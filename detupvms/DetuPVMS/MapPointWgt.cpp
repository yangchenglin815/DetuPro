#include "MapPointWgt.h"

#include "feedback.h"
MapPointWgt::MapPointWgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
}

MapPointWgt::~MapPointWgt()
{

}

void MapPointWgt::init()
{

}

void MapPointWgt::initConnect()
{

}

void MapPointWgt::setMapPointInfo(const PanoMapPointInfo_t &panoMapInfo)
{
	m_panoMapInfo = panoMapInfo;
}

void MapPointWgt::getMapPointInfo(PanoMapPointInfo_t &panoMapInfo)
{
	panoMapInfo = m_panoMapInfo;
}

void MapPointWgt::setMapPointTitle(QString title)
{
	ui.label->setText(title);
}

void MapPointWgt::setMapPointType(MapPointType type)
{
	//¶¯Ì¬ÉèÖÃÍ¼±ê
	switch (type)
	{
	case PANOSCENE_ON_LINE:
	{
		ui.label_2->setStyleSheet(QStringLiteral("border-image:url(:/image/image/panoSceneOnLine.png);"));
		break;
	}
	case PANOSCENE_OFF_LINE:
	{
		ui.label_2->setStyleSheet(QStringLiteral("border-image:url(:/image/image/panoSceneOffLine.png);"));
		break;
	}
	case DEVICE_ON_LINE:
	{
		ui.label_2->setStyleSheet(QStringLiteral("border-image:url(:/image/image/panoDeviceOnLine.png);"));
		break;
	}
	case DEVICE_OFF_LINE:
	{
		ui.label_2->setStyleSheet(QStringLiteral("border-image:url(:/image/image/panoDeviceOffLine.png);"));
		break;
	}
	default:
		break;
	}
}

void MapPointWgt::updatePoint(QPoint point, int width, int height)
{
	m_panoMapInfo.pos_x = point.x()* 1.0 / width;
	m_panoMapInfo.pos_y = point.y()* 1.0 / height;
}

void MapPointWgt::removePointInfo(int key)
{
	m_panoMapInfo.sequencer_point_info_map_.remove(key);
}

void MapPointWgt::updatePointInfo(int key, float value)
{
	m_panoMapInfo.sequencer_point_info_map_.insert(key, value);
}

void MapPointWgt::slotOnUpdateInitAngle(float init_angle)
{
	m_panoMapInfo.initial_angle = init_angle;
}

void MapPointWgt::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		QPoint minPos = ui.label_2->pos();
		QPoint maxPos = ui.label_2->pos();
		maxPos.setX(ui.label_2->pos().x() + ui.label_2->width());
		maxPos.setY(ui.label_2->pos().y() + ui.label_2->height());
		if (event->pos().x() >= minPos.x() && event->pos().y() >= minPos.y() && 
			event->pos().x() <= maxPos.x() && event->pos().y() <= maxPos.y()){
			emit sigOnDragCurrMapPoint(m_panoMapInfo);
		}
	}
	else if (event->button() == Qt::RightButton)
	{
		QPoint minPos = ui.label_2->pos();
		QPoint maxPos = ui.label_2->pos();
		maxPos.setX(ui.label_2->pos().x() + ui.label_2->width());
		maxPos.setY(ui.label_2->pos().y() + ui.label_2->height());
		if (event->pos().x() >= minPos.x() && event->pos().y() >= minPos.y() &&
			event->pos().x() <= maxPos.x() && event->pos().y() <= maxPos.y()){
			emit sigOnSettingPointPath(m_panoMapInfo);
		}
	}
	QWidget::mousePressEvent(event);
}

void MapPointWgt::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		QPoint minPos = ui.label_2->pos();
		QPoint maxPos = ui.label_2->pos();
		maxPos.setX(ui.label_2->pos().x() + ui.label_2->width());
		maxPos.setY(ui.label_2->pos().y() + ui.label_2->height());
		if (event->pos().x() >= minPos.x() && event->pos().y() >= minPos.y() &&
			event->pos().x() <= maxPos.x() && event->pos().y() <= maxPos.y())
		{
			emit sigOnDoubleCurrMapPoint(m_panoMapInfo);
		}
	}
	QWidget::mouseDoubleClickEvent(event);
}
