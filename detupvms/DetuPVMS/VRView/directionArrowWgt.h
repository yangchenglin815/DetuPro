/************************************************
* \file directionArrowWgt.h
*
* \author HuZhengdong
* \date 20171214
* 场景切换箭头点窗口
************************************************/
#ifndef DIRECTIONARROWWGT_H
#define DIRECTIONARROWWGT_H

#include <QWidget>
#include <QMouseEvent>
#include "constStruct.h"

class myQGraphicsScene;
class ArrowItem;

class directionArrowWgt : public QWidget
{
    Q_OBJECT
public:
    explicit directionArrowWgt(QWidget *parent = 0);
	//yaw经度
	//pitch维度
	void addPixItem(int id, double yaw);

	void setArrow(PanoMapPointInfo_t panoMapInfo);
public slots:
	void slotToTrigArrowRotate(double yaw,double pitch);
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    void init();
private:
    int m_PosX;
    int m_PosY;
    QPointF m_upPoints[7];
    QPointF m_downPoints[7];
    QVector<QPointF> m_upArrowGroup;
    QVector<QPointF> m_downArrowGroup;
    int m_onArrow_flag;    //0:不在  1:在上箭头  2:在下箭头

	myQGraphicsScene *scene_;
	QGraphicsView *view_;

	QList<ArrowItem*> arrow_list_;
	double last_yaw_;
};

#endif // DIRECTIONARROWWGT_H
