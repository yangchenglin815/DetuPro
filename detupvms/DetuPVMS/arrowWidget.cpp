#include "arrowWidget.h"
#include <QPainter>

arrowWidget::arrowWidget(QWidget *parent) : QWidget(parent)
{

}

void arrowWidget::paintEvent(QPaintEvent *event)
{
     QWidget::paintEvent(event);
     QPainter painter(this);
     painter.setRenderHint(QPainter::Antialiasing, true);
     painter.setPen(QPen(QBrush("#969696"), 1, Qt::SolidLine));//设置画笔形式
     painter.setBrush(QBrush("#969696"));//设置画刷形式

     int xPos = 0;
     int yPos = 0;
     const int arrowWidth = 12;
     const int arrowHeight = 8;
	 const int space = 12;
	 xPos += space;
     QPoint p1(xPos, yPos+arrowHeight);
     QPoint p2(xPos+arrowWidth/2, yPos);
     QPoint p3(xPos+arrowWidth, yPos+arrowHeight);
     QPoint triangle[3] = {p1, p2, p3};
     painter.drawPolygon(triangle,3);
}


