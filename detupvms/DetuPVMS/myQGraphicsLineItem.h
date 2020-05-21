#ifndef MYQGRAPHICSLINEITEM_H
#define MYQGRAPHICSLINEITEM_H

#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>

class myQGraphicsLineItem : public QObject, public QGraphicsLineItem
{
	Q_OBJECT

public:
	myQGraphicsLineItem();

	void startDraw(QGraphicsSceneMouseEvent * event);
	void drawing(QGraphicsSceneMouseEvent * event);
protected:
	void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
	void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
private:
	
};

#endif // MYQGRAPHICSLINEITEM_H
