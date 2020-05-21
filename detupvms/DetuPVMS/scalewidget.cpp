#include "scalewidget.h"
#include "commonFun.h"
#include <QPainter>

scaleWidget::scaleWidget(QWidget *parent) : QWidget(parent)
  , nx_(0)
  , ny_(10)
  , m_space(0)
  , curr_time_("00:00:00")
{

}

void scaleWidget::setScale(int x)
{
	nx_ = x;
	update();
}

void scaleWidget::setCurrTime(int time)
{
	curr_time_ = commonFun::getCurrentShowTime(time) + ":00";
	update();
}

void scaleWidget::resetRadition()
{
	nx_ = 0;
	curr_time_ = "00:00:00";
	update();
}

//实时更改三角形箭头位置和时间显示
void scaleWidget::setRecoderPos(int time)
{
	curr_time_ = QDateTime::fromTime_t(time).toString("hh:mm:ss");
	QString curr_time_ = QDateTime::fromTime_t(time).toString("hh:mm");
	int num = commonFun::timeExchange(curr_time_, 1);
	nx_ = num * m_space;
	update();
}

void scaleWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
        QPainter painter(this);

        const int m_nFontSize = 1;
        QFont font;
        font.setPixelSize(m_nFontSize);
        painter.setFont(font);
        QPen pen;
        pen.setColor("#a6abab");
        painter.setPen(pen);

        int nWidth =this->width();
		int one_per = 24*60;
		m_space = nWidth*1.0 / one_per;
		int xPos = 0;
        int yPos = 8;
        int nOffx = nWidth / 48;

		for (int i = 0; i<52; i++){
              painter.drawLine(xPos,yPos,xPos,yPos+8);
              xPos += nOffx;
        }
		painter.setRenderHint(QPainter::Antialiasing, true);
		painter.setPen(QPen(QBrush("#f7a500"), 1, Qt::SolidLine));//设置画笔形式
		painter.setBrush(QBrush("#f7a500"));//设置画刷形式
		const int arrowWidth = 12;
		const int arrowHeight = 9;
		if (nx_ + arrowWidth >= nWidth)
		{
			nx_ = nWidth - arrowWidth;
		}
		QPoint p1(nx_, ny_);
		QPoint p2(nx_ + arrowWidth, ny_);
		QPoint p3(nx_ + arrowWidth / 2, ny_ + arrowHeight);
		QPoint triangle[3] = { p1, p2, p3 };
		painter.drawPolygon(triangle, 3);

		//绘制当前时间点
		font.setPixelSize(10);
		painter.setFont(font);
		int nx_;
		if (nx_ + 50 >= nWidth)
		{
			nx_ = nWidth - 50;
		}
		else
		{
			nx_ = nx_;
		}
		QRect rect(nx_, 0, 50, 8);
		painter.drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, curr_time_);

}

void scaleWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->buttons() == Qt::LeftButton){
		int x = event->pos().x();
		setScale(x);
	}
}

void scaleWidget::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() == Qt::LeftButton){
		int x = event->pos().x();
		if (x>0 && x<this->width()-12){
			setScale(x);
		}
	}

}

void scaleWidget::mouseReleaseEvent(QMouseEvent *event)
{
	int x = event->pos().x();
	int time = x / m_space;
	setCurrTime(time);
	emit sigOnRequestReplayRadio(time);
}
