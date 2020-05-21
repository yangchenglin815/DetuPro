/************************************************
* \file myQGraphicsScene.h
*
* \author HuZhengdong
* \date 20170118
* QGraphicsScene
************************************************/
#ifndef MYQGRAPHICSSCENE_H
#define MYQGRAPHICSSCENE_H

#include <QGraphicsScene>

class myQGraphicsScene : public QGraphicsScene
{
	Q_OBJECT

public:
	myQGraphicsScene(QObject *parent = 0);

	~myQGraphicsScene();

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
	
};

#endif // MYQGRAPHICSSCENE_H
