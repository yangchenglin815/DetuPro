
#include "midArrowWidget.h"
#include <QPainter>

midArrowWidget::midArrowWidget(QWidget *parent)
	: QWidget(parent)
{

}

midArrowWidget::~midArrowWidget()
{

}

void midArrowWidget::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setPen(QPen(QBrush("#eeeeee"), 1, Qt::SolidLine));//设置画笔形式
	painter.setBrush(QBrush("#eeeeee"));//设置画刷形式

	int xPos = 0;
	int yPos = 0;
	int nWidth = this->width();
	const int arrowWidth = 12;
	const int arrowHeight = 8;
	const int space = nWidth/2 - arrowWidth/2;
	xPos += space;
	QPoint p1(xPos, yPos + arrowHeight);
	QPoint p2(xPos + arrowWidth / 2, yPos);
	QPoint p3(xPos + arrowWidth, yPos + arrowHeight);
	QPoint triangle[3] = { p1, p2, p3 };
	painter.drawPolygon(triangle, 3);
}
