#include "lineWidget.h"

#include <QPainter>

lineWidget::lineWidget(QWidget *parent) : QWidget(parent)
  , m_isFinal(false)
{

}

void lineWidget::setIsFinal(bool isFinal)
{
     m_isFinal = isFinal;
}

void lineWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);

    QPen pen;
    pen.setColor("#444444");
    pen.setWidth(1);
    painter.setPen(pen);

    int nHeight = this->height();
    int nWidth = this->width();

    if(m_isFinal){
        painter.drawLine(0, 0, 0, nHeight / 2);
    }
    else
    {
          painter.drawLine(0, 0, 0, nHeight);
    }
    painter.drawLine(0, nHeight / 2, nWidth, nHeight / 2);
}
