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
    setCacheMode(QGraphicsItem::DeviceCoordinateCache);     //���û��棬���������ٶ�
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
    //�Ȼ��̶�
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
    //֡�̶��ߺ���̶�����ʽ��һ��
    for (qint64 i = 0; i < total_mark_num_; i++)
    {
        //����֡��ʱ��
        if (time_only_)
        {
            //ֻ����ʱ��
            painter->setPen(time_mark_pen);
            painter->drawLine(line_x, -2, line_x, 0 - MARKHEIGHT);

            painter->setPen(time_text_Pen);
            qint64 time = i * frame_per_mark_ / fps_;          //һ������������λ��
            QString time_str = TimeToString(time);
            if (i == total_mark_num_ - 1)
            {
                //���ʱ��
                time_str = TimeToString(duration_);
            }

            painter->drawText(line_x - TIMETEXTWIDTH / 2 - 1, 0 - 2 - MARKHEIGHT, time_str);
        }
               else if (i == 0)
               {
                   //��������0�̶�
                   painter->setPen(time_mark_pen);
                   painter->drawLine(line_x, -2, line_x, 0 - MARKHEIGHT);
                   painter->setPen(time_text_Pen);
                   painter->drawText(line_x - FRAMETEXTWIDTH / 2 - 1, 0 - 2 - MARKHEIGHT, QString("00:00(hr)"));
               }
               else
               {
                   //����֡��ʱ��
                   int mark_per_second = mark_per_sencond_;
                   qint64 seconds = i / mark_per_second;
                   int more_mark = i - seconds * mark_per_second;
                   if (more_mark == 0)
                   {
                       //ʱ��̶�
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
                       //֡�̶�
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

//ʱ��ת�����ַ���mm:ss
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

//ʱ��ת�����ַ���mm:ss
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

//�������Ŀ̶����꣬ʱ�侫ȷ����
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

//��ȡx���������һ���̶ȵ�����
qreal TimeScaleItem::GetNearestPos(qreal x)
{
    x -= GetZeroX();
    qint64 mark_num = x / MINMARKWIDTH;
    qreal temp = x - mark_num * MINMARKWIDTH;

    //����������ڿ̶ȿ�ȵ�һ�룬��λ�������һ���̶���
    if (temp >= MINMARKWIDTH / 2)
    {
        mark_num += 1;
    }

    return mark_num * MINMARKWIDTH + GetZeroX();
}

//��ȷ����
qint64 TimeScaleItem::GetTimeByPosX(qreal x)
{
    int mark_per_sencond = mark_per_sencond_;

    //�����x�϶���ĳһ���̶��ߵ�x
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
        seconds = mark_num * frame_per_mark_ / fps_; //�϶�������
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

    //�����x�϶���ĳһ���̶��ߵ�x
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
        qint64 seconds = mark_num * frame_per_mark_ / fps_; //�϶�������
        frames = seconds * fps_;
    }    

    if (frames > total_frames_)
    {
        frames = total_frames_;
    }
    return frames;
}

//���ؿɻ��ƿ̶ȵĿ��
qreal TimeScaleItem::GetDrawScaleWidth()
{
    return GetLastX() - GetZeroX();     //���Ҹ���һ���̶ȿ��
}

//����0�̶��ߵ�x����
qreal TimeScaleItem::GetZeroX()
{
    return MINMARKWIDTH;
}

qreal TimeScaleItem::GetLastX()
{
    return scene()->width() - MINMARKWIDTH;
}

//��ȡ���п̶ȸ���
qint64 TimeScaleItem::GetTotalMarkNum()
{
    return total_mark_num_;
}

//��ȡһ�����ж��ٸ��̶ȣ���������ʼ�̶ȣ����߶θ���
int TimeScaleItem::GetMarkNumPerSecond()
{
    if (frame_per_mark_ > fps_)
    {
        mark_per_sencond_ = -1;
        return mark_per_sencond_;
    }

    int mark_per_second = fps_ / frame_per_mark_;      //ÿһ��ķ�Χ���ж��ٿ̶ȣ���������һ�뿪ʼ�Ŀ̶�
    if (mark_per_second * frame_per_mark_ < fps_)
    {
        //һ���ڲ�������֡�ģ��������������һ���̶�
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
        //ֻ��ʱ��
        int time_per_mark = frame_per_mark_ / fps_;
        time_mark_num_ = duration_ / time_per_mark;
        if (time_mark_num_ * time_per_mark < duration_)
        {
            //���ʱ�䲻��һ���̶ȵģ��������һ���̶�
            time_mark_num_ += 1;
        }

        total_mark_num_ = time_mark_num_ + 1;
        time_only_ = true;
        return;
    }
    else
    {
        //����֡����ʱ�䣬ʱ������Ϊ��λ
        time_mark_num_ = duration_;       //������ʾʱ��Ŀ̶�������һ���̶���ʾ00f������ʾʱ��
        int mark_per_second = mark_per_sencond_;     //ÿһ��ķ�Χ���ж��ٿ̶ȣ���������һ�뿪ʼ�Ŀ̶�

        qint64 frames = mark_per_second * duration_ + 1;
        total_mark_num_ = frames;
    }
}
