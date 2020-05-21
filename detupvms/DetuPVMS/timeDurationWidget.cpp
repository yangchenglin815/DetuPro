#include "timeDurationWidget.h"
#include "commonFun.h"
#include "logging.hpp"
#include "feedback.h"

#include <QPainter>
#include <QTimer>
#include <QDebug>

timeDurationWidget::timeDurationWidget(QWidget *parent) : QWidget(parent)
  , arrowXPos_(9)
  , arrowYPos_(14)
  , space_(42)
  , needed_(true)
  , curr_time("")
  , m_moveabled(true)
  , bPressed(false)
  , curr_time_(1502812800)
{
	this->setMouseTracking(true);
}

void timeDurationWidget::initData(m_replayInfoList infoList)
{
      m_infoList = infoList;
      switch(m_infoList.duration)
      {
      case DURATION_HOUR:
          duration_ = 24;
          space_ = mWidth_ / 24;
          break;
      case DURATION_HALF_HOUR:
          duration_ = 24 * 2;
		  space_ = mWidth_ / 48;
          break;
      case DURATION_TEN_MIN:
          duration_ = 24 * 60 / 10;
          space_ = 16;
          break;
      case DURATION_MIN:
          duration_ = 24 * 60;
          space_ = 12;
          break;
      case DURATION_TEN_SECOND:
          duration_ = 24 * 60 * 60 / 10;
          space_ = 6;
          break;
      case DURATION_SECOND:
          duration_ = 24 * 60 * 60;
          space_ = 6;
          break;
      }
      update();
}

void timeDurationWidget::setRecoderPos(int time)
{
	if (bPressed)
	{
		return;
	}
	curr_time = QDateTime::fromTime_t(time).toString("hh:mm:ss");
	int num = commonFun::timeExchange(curr_time, m_infoList.duration);
	arrowXPos_ = num * space_ + 9;
	initData(m_infoList);
}

void timeDurationWidget::resetRadition()
{
	arrowXPos_ = 9;
	update();
}

void timeDurationWidget::setWidth(int width)
{
	mWidth_ = width;
}

void timeDurationWidget::updateSliderPos(int duration)
{
	QString currTime;
	switch (duration)
	{
	case DURATION_HOUR:
	{
						  currTime = QDateTime::fromTime_t(curr_time_).toString("hh");
						  arrowXPos_ = currTime.toInt() * mWidth_ / 24 + 9;
						  break;
	}
	case DURATION_HALF_HOUR:
	{
							   currTime = QDateTime::fromTime_t(curr_time_).toString("hh:mm");
							   int min = currTime.left(2).toInt() * 60 + currTime.mid(3, 2).toInt();
							   if (min / 30 == 0)
							   {
								   arrowXPos_ = min / 30 * mWidth_ / 48 + 9;
							   }
							   else
							   {
								   arrowXPos_ = min / 30 * mWidth_ / 48;
							   }
							   break;
	}
	case DURATION_TEN_MIN:
	{
							 currTime = QDateTime::fromTime_t(curr_time_).toString("hh:mm");
							 int min = currTime.left(2).toInt() * 60 + currTime.mid(3, 2).toInt();
							 arrowXPos_ = min / 10 * 16 + 9;
							 break;
	}
	case DURATION_MIN:
	{
						 currTime = QDateTime::fromTime_t(curr_time_).toString("hh:mm");
						 int min = currTime.left(2).toInt() * 60 + currTime.mid(3, 2).toInt();
						 arrowXPos_ = min * 12 + 9;
						 break;
	}
	case DURATION_TEN_SECOND:
	{
								currTime = QDateTime::fromTime_t(curr_time_).toString("hh:mm:ss");
								QStringList list = currTime.split(":");
								if (list.size() > 0){
									int second = list.at(0).toInt() * 60 * 60 + list.at(1).toInt() * 60 + list.at(2).toInt();
									arrowXPos_ = second / 10 * 6 + 9;
								}
								break;
	}
	case DURATION_SECOND:
	{
							currTime = QDateTime::fromTime_t(curr_time_).toString("hh:mm:ss");
							QStringList list = currTime.split(":");
							if (list.size() > 0){
								int second = list.at(0).toInt() * 60 * 60 + list.at(1).toInt() * 60 + list.at(2).toInt();
								arrowXPos_ = second * 6 + 9;
							}
							break;
	}
	}
	emit sigOnUpdateSlider(arrowXPos_);
}

void timeDurationWidget::setMoveEnabled(bool enable)
{
	m_moveabled = enable;
}

void timeDurationWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    const int xPos = this->x();
    const int yPos =this->y();
    const int nWidth = this->width();
    const int nHeight = this->height();
    const int m_nFontSize = 1;
    QFont font;
    font.setPixelSize(m_nFontSize);
    painter.setFont(font);
    QPen pen;
    pen.setColor("#121212");
    painter.setPen(pen);
    //三角滑块
    const int arrowWidth = 13;
    const int arrowHeight = 8;

    //绘制刻度线
    int bXpos = 15;
    int bYpos = yPos + 15;
    int usedWidth = nWidth - 2 * bXpos;
    int count = duration_ + 1;
    int num;
    setFixedSize(duration_ * space_ + 2 * bXpos + 10, this->height());
    for(int i = 0; i < count; ++i)
    {
        switch(m_infoList.duration)
        {
        case DURATION_HOUR:
        {
            num = 25;
            painter.drawLine(bXpos, bYpos, bXpos, bYpos + 8);
            break;
        }
        case DURATION_HALF_HOUR:
        {
            num = 25;
            if(i % 2 == 0){
                painter.drawLine(bXpos, bYpos, bXpos, bYpos + 8);
            }
            else
            {
                painter.drawLine(bXpos, bYpos + 3, bXpos, bYpos+8);
            }
            break;
        }
        case DURATION_TEN_MIN:
        {
            num = 25;
            if(i % 6 == 0){
                painter.drawLine(bXpos, bYpos, bXpos, bYpos + 8);
            }
            else
            {
                painter.drawLine(bXpos, bYpos + 3, bXpos, bYpos+8);
            }
            break;
        }
        case DURATION_MIN:
        {
            num = 24 * 6 + 1;
            if(i % 10 == 0){
                painter.drawLine(bXpos, bYpos, bXpos, bYpos + 8);
            }
            else
            {
                painter.drawLine(bXpos, bYpos + 3, bXpos, bYpos+8);
            }
            break;
        }
        case DURATION_TEN_SECOND:
        {
            num = 24 * 60 + 1;
            if(i % 6 == 0){
                painter.drawLine(bXpos, bYpos, bXpos, bYpos + 8);
            }
            else
            {
                painter.drawLine(bXpos, bYpos + 3, bXpos, bYpos+8);
            }
            break;
        }
        case DURATION_SECOND:
        {
            num = 24 * 60 * 6 + 1;
            if(i % 10 == 0){
                painter.drawLine(bXpos, bYpos, bXpos, bYpos + 8);
            }
            else
            {
                painter.drawLine(bXpos, bYpos + 3, bXpos, bYpos+8);
            }
            break;
        }
        }
        bXpos += space_;
    }
    pen.setWidth(1);
	pen.setColor("#121212");
    painter.setPen(pen);
	painter.drawLine(xPos, bYpos + 8, xPos + duration_ * space_ + 2 * bXpos + 10, bYpos + 8);
    //绘制时刻
    font.setPixelSize(11);
	pen.setColor("#888888");
	painter.setPen(pen);
    painter.setFont(font);
    bXpos = 5;
    for(int i = 0; i < num; ++i)
    {
        QRect rect(bXpos, 4, 30, 8);
        QString time;
        switch (m_infoList.duration) {
        case DURATION_HOUR:
            time = QString("%1:00").arg(i);
            painter.drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, time);
			bXpos += space_;
            break;
        case DURATION_HALF_HOUR:
            time = QString("%1:00").arg(i);
            painter.drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, time);
			bXpos += space_ * 2;
            break;
        case DURATION_TEN_MIN:
            time = QString("%1:00").arg(i);
            painter.drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, time);
            bXpos += space_ * 6;
            break;
        case DURATION_MIN:
            time = commonFun::getCurrentTipTime(i * 10);
            painter.drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, time);
            bXpos += space_ * 10;
            break;
        case DURATION_TEN_SECOND:
            time = commonFun::getCurrentTimeBySscond(i * 10);
            painter.drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, time);
            bXpos += space_ * 6;
            break;
        case DURATION_SECOND:
            time = commonFun::getCurrentTimeByPerSscond(i * 10);
            painter.drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, time);
            bXpos += space_ * 10;
            break;
        }
    }
    pen.setWidth(1);
	pen.setColor("#121212");
    painter.setPen(pen);
	painter.drawLine(xPos, bYpos + 38, xPos + duration_ * space_ + 2 * bXpos + 10, bYpos + 38);
    //绘制时间域
    bXpos = 15;
    for (int i = 0; i < m_infoList.m_infoList.length(); i++){
        QString startDate_;
         int scale, pos, Offx;
		 QString strat_time = QDateTime::fromTime_t(m_infoList.m_infoList[i].startTime).toString("yy-MM-dd hh:mm:ss");
		 QString end_time = QDateTime::fromTime_t(m_infoList.m_infoList[i].endTime).toString("yy-MM-dd hh:mm:ss");
		 //Log::Debug("time %d  :  start - %s  end - %s", i + 1, strat_time.toLocal8Bit().data(), end_time.toLocal8Bit().data());
        switch(m_infoList.duration)
        {
              case DURATION_HOUR:
        {
            startDate_ = QDateTime::fromTime_t(m_infoList.m_infoList[i].startTime).toString("hh");
            scale = commonFun::timeExchange(startDate_, 1);
            pos = space_ * scale;
            Offx = (m_infoList.m_infoList[i].endTime - m_infoList.m_infoList[i].startTime) / 60 / 60 * space_;
            break;
        }
        case DURATION_HALF_HOUR:
        {
            startDate_ = QDateTime::fromTime_t(m_infoList.m_infoList[i].startTime).toString("hh:mm");
            scale = commonFun::timeExchange(startDate_, 2);
            pos = space_ * scale;
            Offx = (m_infoList.m_infoList[i].endTime - m_infoList.m_infoList[i].startTime) / 60 / 30 * space_;
            break;
        }
        case DURATION_TEN_MIN:
        {
            startDate_ = QDateTime::fromTime_t(m_infoList.m_infoList[i].startTime).toString("hh:mm");
            scale = commonFun::timeExchange(startDate_, 3);
            pos = space_ * scale;
             Offx = (m_infoList.m_infoList[i].endTime - m_infoList.m_infoList[i].startTime) / 60 / 10 * space_;
            break;
        }
        case DURATION_MIN:
        {
            startDate_ = QDateTime::fromTime_t(m_infoList.m_infoList[i].startTime).toString("hh:mm");
            QString startDate = QDateTime::fromTime_t(m_infoList.m_infoList[i].startTime).toString("hh:mm");
            QString endDate = QDateTime::fromTime_t(m_infoList.m_infoList[i].endTime).toString("hh:mm");
            scale = commonFun::timeExchange(startDate_, 4);
            pos = space_ * scale;
            Offx = (commonFun::getMinFromStr(endDate) - commonFun::getMinFromStr(startDate)) * space_;
            break;
        }
        case DURATION_TEN_SECOND:
        {
            startDate_ = QDateTime::fromTime_t(m_infoList.m_infoList[i].startTime).toString("hh:mm:ss");
            scale = commonFun::timeExchange(startDate_, 5);
            pos = space_ * scale;
            Offx = (m_infoList.m_infoList[i].endTime - m_infoList.m_infoList[i].startTime) / 10 * space_;
            break;
        }
        case DURATION_SECOND:
        {
            startDate_ = QDateTime::fromTime_t(m_infoList.m_infoList[i].startTime).toString("hh:mm:ss");
            scale = commonFun::timeExchange(startDate_, 6);
            pos = space_ * scale;
            Offx = (m_infoList.m_infoList[i].endTime - m_infoList.m_infoList[i].startTime)  * space_;
            break;
        }
        }
        painter.setBrush(QBrush("#a6abab", Qt::SolidPattern));
        QFont font;
        font.setPixelSize(10);
        painter.setFont(font);
        QPen pen;
        pen.setColor("#4e5050");
        painter.setPen(pen);
        painter.drawRect(bXpos + pos, bYpos + 10, Offx, 26);
    }
    //绘制三角滑块
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(QBrush("#ffd500"), 1, Qt::SolidLine));//设置画笔形式
    painter.setBrush(QBrush("#ffd500"));//设置画刷形式
    bXpos = 15;
    QPoint p1(arrowXPos_, arrowYPos_);
    QPoint p2(arrowXPos_ + arrowWidth, arrowYPos_);
    QPoint p3(arrowXPos_ + arrowWidth / 2, arrowYPos_ + arrowHeight);
    QPoint triangle[3] = { p1, p2, p3 };
    painter.drawPolygon(triangle, 3);

    pen.setWidth(1);
    pen.setColor("#ffd500");
    painter.setPen(pen);
    painter.drawLine(arrowXPos_ + arrowWidth / 2, bYpos, arrowXPos_ + arrowWidth / 2, bYpos + 38);
}

void timeDurationWidget::mousePressEvent(QMouseEvent *event)
{
	if (!m_moveabled)
	{
		Feedback::instance()->maskUI(WAIT_PLAY);
		event->ignore();
	}
	else{
		if (event->buttons() == Qt::LeftButton){
			int x = event->pos().x();
			if (x >= 15 && x <= 15 + duration_ * space_){
				arrowXPos_ = x;
				bPressed = true;
				update();

			}
		}
	}
}

void timeDurationWidget::mouseMoveEvent(QMouseEvent *event)
{
	if (!m_moveabled)
	{
		event->ignore();
	}
	else
	{
		QPoint mousepos = event->pos();
		if (mousepos.rx() >= arrowXPos_ && mousepos.rx() <= arrowXPos_ + 13 && mousepos.ry() >= arrowYPos_ && mousepos.ry() <= arrowYPos_ + 8 + 38){
			setCursor(Qt::SizeHorCursor);
		}
		else
		{
			setCursor(Qt::PointingHandCursor);
		}
	}
}

void timeDurationWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (!m_moveabled)
	{
		event->ignore();
	}
	else
	{
		int x = event->pos().x();
		if (x >= 15 && x <= 15 + duration_ * space_){
			int time = (x - 9) / space_;
			QString date = "2017-08-16";
			arrowXPos_ = time *space_ + 9;
			bPressed = true;
			update();
			curr_time_ = commonFun::getDateTime(time, date, m_infoList.duration);
			QString currentTime = QDateTime::fromTime_t(curr_time_).toString("hh:mm:ss");
			Log::Debug("current selected time is %s", currentTime.toLocal8Bit().data());
			emit sigOnRequestReplayRadio(time, m_infoList.duration);
			QTimer::singleShot(500, this, SLOT(slotOnUpdateFlag()));
		}
	}
}

void timeDurationWidget::enterEvent(QEvent *event)
{
	setCursor(Qt::PointingHandCursor);
}

void timeDurationWidget::leaveEvent(QEvent *event)
{
    setCursor(Qt::ArrowCursor);
}

void timeDurationWidget::wheelEvent(QWheelEvent *event)
{
   if(event->delta() > 0)
   {
       emit sigOnAddDuration();
   }
   else
   {
      emit sigOnDecreaseDuration();
   }
   emit sigOnGetCurrentX(arrowXPos_);
}

void timeDurationWidget::slotOnUpdateFlag()
{
	bPressed = false;
}
