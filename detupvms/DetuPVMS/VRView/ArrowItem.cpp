#include "ArrowItem.h"
#include "ViewSignal.h"

ArrowItem::ArrowItem() :ArrowItem(-1, 0.0)
{
	
}


ArrowItem::ArrowItem(int id, float angle):
current_id_(id),
yaw_angle_(angle)
{

}



int ArrowItem::getArrowType()
{
	return arrow_type_;
}

void ArrowItem::setMyPixMap(QString file_PATH)
{
    QPixmap pixmap;
	pixmap.load(file_PATH);
    pixmap= pixmap.scaled(102,128,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setPixmap(pixmap);
	this->setScale(0.5);
}


void ArrowItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	ViewSignal::instance()->sigOnArrowClicked(current_id_);
     QGraphicsItem::mousePressEvent(event);
}

void ArrowItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
     QGraphicsItem::mouseReleaseEvent(event);
}
