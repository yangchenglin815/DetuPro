#include <QtWidgets>
#include <QtGui>
#include <QtCore>
#include "TimeScaleItem.h"
#include "TimeScaleDrawWidget.h"

TimeScaleItem::TimeScaleItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , frame_per_mark_(1)
    , duration_(0)
    , fps_(30)
    , total_frames_(0)
    , view_(NULL)
    , mark_per_sencond_(60)
{
    setZValue(0);
    //setFlag(QGraphicsItem::ItemIsMovable, false);
    setCursor(Qt::PointingHandCursor);
    setCacheMode(QGraphicsItem::DeviceCoordinateCache);     //设置缓存，提升绘制速度
    //setEnabled(false);
}

TimeScaleItem::~TimeScaleItem()
{

}

void TimeScaleItem::SetDurationAndFps(qint64 duration, int fps)
{
    duration_ = duration;
    fps_ = fps;
    total_frames_ = fps_ * duration;
    GetMarkNumPerSecond();
    CalculateMarkNum();
    update();
}

void TimeScaleItem::SetMinimumFrame(qint64 frame_per_mark)
{
    frame_per_mark_ = frame_per_mark;
    GetMarkNumPerSecond();
    CalculateMarkNum();
    update();
}

QRectF TimeScaleItem::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(0, 0 - SCALEITEMHEIGHT, scene()->width() + adjust, SCALEITEMHEIGHT);
}

void TimeScaleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //先画刻度
    if (duration_ <= 0)
    {
        return;
    }

    QPen frame_mark_pen(QColor(0, 0, 0));
    QPen time_mark_pen(QColor(136, 136, 136));
    QPen frame_text_pen(QColor(136, 136, 136));
    QPen time_text_Pen(QColor(204, 204, 204));
    frame_mark_pen.setWidth(1);
    time_mark_pen.setWidth(1);
    time_text_Pen.setWidth(1);
    frame_text_pen.setWidth(1);

    QFont font;
    font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
    font.setPointSize(8);
    painter->setFont(font);

    qreal line_x = GetZeroX();
    //帧刻度线和秒刻度线样式不一样
    for (qint64 i = 0; i < total_mark_num_; i++)
    {
        //绘制帧和时间
        if (time_only_)
        {
            //只绘制时间
            painter->setPen(time_mark_pen);
            painter->drawLine(line_x, -2, line_x, 0 - MARKHEIGHT);

            painter->setPen(time_text_Pen);
            qint64 time = i * frame_per_mark_ / fps_;          //一定能整除，单位秒
            QString time_str = TimeToString(time);
            if (i == total_mark_num_ - 1)
            {
                //最后时刻
                time_str = TimeToString(duration_);
            }

            painter->drawText(line_x - TIMETEXTWIDTH / 2 - 1, 0 - 2 - MARKHEIGHT, time_str);
        }
               else if (i == 0)
               {
                   //单独绘制0刻度
                   painter->setPen(time_mark_pen);
                   painter->drawLine(line_x, -2, line_x, 0 - MARKHEIGHT);
                   painter->setPen(time_text_Pen);
                   painter->drawText(line_x - FRAMETEXTWIDTH / 2 - 1, 0 - 2 - MARKHEIGHT, QString("00:00(hr)"));
               }
               else
               {
                   //绘制帧和时间
                   int mark_per_second = mark_per_sencond_;
                   qint64 seconds = i / mark_per_second;
                   int more_mark = i - seconds * mark_per_second;
                   if (more_mark == 0)
                   {
                       //时间刻度
                       painter->setPen(time_mark_pen);
                       painter->drawLine(line_x, -2, line_x, 0 - MARKHEIGHT);
       
                       painter->setPen(time_text_Pen);
                       QString time_str = TimeToString(seconds);
                       if (i == total_mark_num_ || seconds > duration_)
                       {
                           time_str = TimeToString(duration_);
                       }
                       painter->drawText(line_x - TIMETEXTWIDTH / 2 - 1, 0 - 2 - MARKHEIGHT, time_str);
                   }
                   else
                   {
                       //帧刻度
                       painter->setPen(frame_mark_pen);
                       painter->drawLine(line_x, -2, line_x, 0 - MARKHEIGHT);
       
                       painter->setPen(frame_text_pen);
                       int frames = more_mark * frame_per_mark_;
                       QString frame_str = QString("%1h").arg(QString::number(frames));
                       if (frame_str.size() < 3)
                       {
                           frame_str.push_front("0");
                       }
                      // painter->drawText(line_x - FRAMETEXTWIDTH / 2 - 1, 0 - 2 - MARKHEIGHT, frame_str);
                   }
              }

        line_x += MINMARKWIDTH;
    }    
}

//时间转换成字符串mm:ss
QString TimeScaleItem::TimeToString(qint64 time)
{
    int minutes = time / 60;
    int seconds = time % 60;

    QString minute = "";
    QString second = "";

    minute = QString::number(minutes);
    if (minutes < 10)
    {
        minute.push_front("0");
    }

    second = QString::number(seconds);
    if (seconds < 10)
    {
        second.push_front("0");
    }

    return minute + ":" + second;
}

//时间转换成字符串mm:ss
QString TimeScaleItem::FramesToString(qint64 frames)
{
    int seconds = frames / fps_;
    int minutes = seconds / 60;
    seconds = seconds % 60;

    QString minute = "";
    QString second = "";

    minute = QString::number(minutes);
    if (minutes < 10)
    {
        minute.push_front("0");
    }

    second = QString::number(seconds);
    if (seconds < 10)
    {
        second.push_front("0");
    }

    return minute + ":" + second;
}

//获得最近的刻度坐标，时间精确到秒
qreal TimeScaleItem::GetTimePos(qint64 time)
{
    qint64 frames = time * fps_;
    return GetFramePos(frames);
}

qreal TimeScaleItem::GetFramePos(qint64 frame)
{
    qint64 mark_num;
    qint64 seconds = frame / fps_;
    int temp = frame - seconds * fps_;

    int mark_per_second = mark_per_sencond_;
    if (mark_per_second != -1)
    {
        mark_num = mark_per_second * seconds;
        int more_num = temp / frame_per_mark_;
        if ((temp - more_num * frame_per_mark_) > frame_per_mark_ / 2)
        {
            more_num += 1;
        }

        mark_num += more_num;

        return mark_num * MINMARKWIDTH + GetZeroX();
    }
    else
    {
        mark_num = frame / frame_per_mark_;
        if (mark_num * frame_per_mark_ < frame)
        {
            mark_num += 1;
        }
    }

    return mark_num * MINMARKWIDTH + GetZeroX();
}

//获取x坐标最近的一个刻度的坐标
qreal TimeScaleItem::GetNearestPos(qreal x)
{
    x -= GetZeroX();
    qint64 mark_num = x / MINMARKWIDTH;
    qreal temp = x - mark_num * MINMARKWIDTH;

    //如果余数大于刻度宽度的一半，定位到后面的一个刻度线
    if (temp >= MINMARKWIDTH / 2)
    {
        mark_num += 1;
    }

    return mark_num * MINMARKWIDTH + GetZeroX();
}

//精确到秒
qint64 TimeScaleItem::GetTimeByPosX(qreal x)
{
    int mark_per_sencond = mark_per_sencond_;

    //传入的x肯定是某一个刻度线的x
    qint64 mark_num = (x - GetZeroX()) / MINMARKWIDTH;
    qint64 seconds;

    if (mark_per_sencond != -1)
    {
        seconds = mark_num / mark_per_sencond;
        int temp_mark = mark_num - seconds * mark_per_sencond;
        if (temp_mark > mark_per_sencond / 2)
        {
            seconds += 1;
        }
    }
    else
    {
        seconds = mark_num * frame_per_mark_ / fps_; //肯定能整除
    }    

    if (seconds > duration_)
    {
        seconds = duration_;
    }
    return seconds;
}

qint64 TimeScaleItem::GetFrameIndexByPosX(qreal x)
{
    int mark_per_sencond = mark_per_sencond_;

    //传入的x肯定是某一个刻度线的x
    qint64 mark_num = (x - GetZeroX()) / MINMARKWIDTH;
    qint64 frames;

    if (mark_per_sencond != -1)
    {
        qint64 seconds = mark_num / mark_per_sencond;
        int temp_mark = mark_num - seconds * mark_per_sencond;
        frames = seconds * fps_ + temp_mark * frame_per_mark_;        
    }
    else
    {
        qint64 seconds = mark_num * frame_per_mark_ / fps_; //肯定能整除
        frames = seconds * fps_;
    }    

    if (frames > total_frames_)
    {
        frames = total_frames_;
    }
    return frames;
}

//返回可绘制刻度的宽度
qreal TimeScaleItem::GetDrawScaleWidth()
{
    return GetLastX() - GetZeroX();     //左右各留一个刻度宽度
}

//返回0刻度线的x坐标
qreal TimeScaleItem::GetZeroX()
{
    return MINMARKWIDTH;
}

qreal TimeScaleItem::GetLastX()
{
    return scene()->width() - MINMARKWIDTH;
}

//获取所有刻度个数
qint64 TimeScaleItem::GetTotalMarkNum()
{
    return total_mark_num_;
}

//获取一秒内有多少个刻度，不包含开始刻度，既线段个数
int TimeScaleItem::GetMarkNumPerSecond()
{
    if (frame_per_mark_ > fps_)
    {
        mark_per_sencond_ = -1;
        return mark_per_sencond_;
    }

    int mark_per_second = fps_ / frame_per_mark_;      //每一秒的范围内有多少刻度，不包含这一秒开始的刻度
    if (mark_per_second * frame_per_mark_ < fps_)
    {
        //一秒内不能整除帧的，保留余数到最后一个刻度
        mark_per_second += 1;
    }

    mark_per_sencond_ = mark_per_second;
    return mark_per_sencond_;
}

void TimeScaleItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    
}

void TimeScaleItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (view_ == NULL)
    {
        return;
    }

    view_->SetCurrentTimePosByClick(GetNearestPos(event->scenePos().x()));
}

void TimeScaleItem::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    return;
}

void TimeScaleItem::CalculateMarkNum()
{
    total_mark_num_ = 0;
    time_mark_num_ = 0;
    time_only_ = false;

    if (frame_per_mark_ >= fps_)
    {
        //只有时间
        int time_per_mark = frame_per_mark_ / fps_;
        time_mark_num_ = duration_ / time_per_mark;
        if (time_mark_num_ * time_per_mark < duration_)
        {
            //最后时间不够一个刻度的，保留最后一个刻度
            time_mark_num_ += 1;
        }

        total_mark_num_ = time_mark_num_ + 1;
        time_only_ = true;
        return;
    }
    else
    {
        //既有帧又有时间，时间以秒为单位
        time_mark_num_ = duration_;       //用于显示时间的刻度数，第一个刻度显示00f，不显示时间
        int mark_per_second = mark_per_sencond_;     //每一秒的范围内有多少刻度，不包含这一秒开始的刻度

        qint64 frames = mark_per_second * duration_ + 1;
        total_mark_num_ = frames;
    }
}
