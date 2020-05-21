#include "timeLabel.h"

#include <QPainter>
#include <QDebug>
#include "logging.hpp"

timeLabel::timeLabel(QWidget *parent) : QLabel(parent)
{
	   // setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
    	//setAttribute(Qt::WA_TranslucentBackground);
        curr_time_ = "0000-00-00 00:00:00";
}

void timeLabel::setShowTime(QString time)
{
     curr_time_ = time;
     update();
}

void timeLabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QFont font("微软雅黑", 50, 50, false);
	font.setBold(true);
    font.setPixelSize(14);
    painter.setFont(font);
    QPen pen;
	pen.setColor("#444444");
	pen.setWidth(1);
	painter.setPen(pen);
    QPainterPath path;
    path.addText(10, 20, font, curr_time_);
	painter.strokePath(path, pen);
	painter.drawPath(path);
	painter.fillPath(path, QBrush("#ffffff"));
}
