#include "myQGraphicsScene.h"
#include <QGraphicsScene>
#include <QDebug>

myQGraphicsScene::myQGraphicsScene(QObject *parent)
: QGraphicsScene(parent)
{

}

myQGraphicsScene::~myQGraphicsScene()
{

}

void myQGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mousePressEvent(event);
}

void myQGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mouseMoveEvent(event);
}

void myQGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mouseReleaseEvent(event);
}
