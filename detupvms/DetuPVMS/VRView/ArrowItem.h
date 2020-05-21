/************************************************
* \file ArrowItem.h
*
* \author HuZhengdong
* \date 20171214
* ³¡¾°ÇÐ»»¼ýÍ·item
************************************************/
#ifndef MYGRAPHICSPIXMAPITEM_H
#define MYGRAPHICSPIXMAPITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class ArrowItem : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    ArrowItem();
    ArrowItem(int id,float angle);

	int getArrowType();

    void setMyPixMap(QString file_PATH);

	double getInitialValue(){ return yaw_angle_; };


public slots:

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
	int arrow_type_;   //2:next 1:previous

	int current_id_;
	float angle_;

	double yaw_angle_;
};

#endif // MYGRAPHICSPIXMAPITEM_H
