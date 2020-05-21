#include <QtWidgets>
#include <QtGui>
#include <QtCore>
#include "TimeScaleDrawWidget.h"
#include "TimeScaleItem.h"
#include "CurrentLineItem.h"

TimeScaleDrawWidget::TimeScaleDrawWidget(QWidget *parent)
    : QGraphicsView(parent)
    , fps_(30)
    , frame_per_mark_(1)
    , current_time_(0)
    , current_frame_(0)
    , duration_(0)
    , scroll_bar_(NULL)
{
    setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    InitScene();    
    connect(horizontalScrollBar(), SIGNAL(rangeChanged(int, int)), this, SLOT(OnScrollBarRangeChanged(int, int)));
    connect(horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(OnScrollBarValueChanged(int)));
}

TimeScaleDrawWidget::~TimeScaleDrawWidget()
{

}

void TimeScaleDrawWidget::InitScene()
{
    scene_ = new QGraphicsScene();
    setScene(scene_);
    setAlignment(Qt::AlignLeft);

    //添加刻度
    scale_item_ = new TimeScaleItem();
    scale_item_->setZValue(0);
    scale_item_->SetView(this);
    scale_item_->setPos(0, SCALEITEMHEIGHT);
    scale_item_->SetMinimumFrame(frame_per_mark_);
    scene_->addItem(scale_item_);

    current_item_ = new CurrentLineItem();
    current_item_->setZValue(1);
    current_item_->SetScaleItem(scale_item_);
    current_item_->SetView(this);
    current_item_->SetType(CurrentLineItem::Main, tr("Current Time"));
    //current_item_->SetPixmap(new QPixmap(":/images/Resources/line.png"));
    //current_item_->setPos(scale_item_->GetTimePos(current_time_), height() / 2);
    scene_->addItem(current_item_);

    scene_->setSceneRect(QRectF(rect()));
    setSceneRect(QRectF(rect()));
}

void TimeScaleDrawWidget::SetDurationAndFPS(qint64 duration, int fps)
{
    //根据时长设置scene范围
    scale_item_->SetDurationAndFps(duration, fps);
    duration_ = duration;
    fps_ = fps;
    
    current_time_ = 10;
    current_item_->SetPos(scale_item_->GetZeroX(), SCALEITEMHEIGHT + 2);
    current_frame_ = scale_item_->GetFrameIndexByPosX(current_item_->x());
    centerOn(current_item_);

    ResizeScence();
}

//重新调整scence宽度和item位置
void TimeScaleDrawWidget::ResizeScence()
{
    qint64 mark_num = scale_item_->GetTotalMarkNum();

    //重新调整scene宽度
    int width = MINMARKWIDTH * (mark_num - 1) + MINMARKWIDTH * 2;
    scene_->setSceneRect(QRectF(0, 0, width, height()));
    setSceneRect(QRectF(0, 0, width, height()));
    emit SceneWidthChanged(width);

    scale_item_->setPos(0, SCALEITEMHEIGHT);
    current_item_->SetPos(scale_item_->GetFramePos(current_frame_), SCALEITEMHEIGHT + 2);
    current_time_ = scale_item_->GetTimeByPosX(current_item_->x());
    qint64 temp_current_frame = current_frame_;
    current_frame_ = scale_item_->GetFrameIndexByPosX(current_item_->x());
    if (current_frame_ != temp_current_frame)
    {
        if (current_frame_ == duration_ * fps_)
        {
            emit CurrentFrameChanged(current_frame_ - 1);
        }
        else
        {
            emit CurrentFrameChanged(current_frame_);
        }
    }
    update();
    scale_item_->hide();
    scale_item_->show();
    centerOn(current_item_);

    ResetScrollBar();
}

void TimeScaleDrawWidget::SetCurrentTime(qint64 current)
{
    current_time_ = current;
    current_item_->SetPos(scale_item_->GetTimePos(current_time_), SCALEITEMHEIGHT + 2);
}

void TimeScaleDrawWidget::SetCurrentFrame(qint64 frame)
{
    current_frame_ = frame;
    current_item_->SetPos(scale_item_->GetFramePos(current_frame_), SCALEITEMHEIGHT + 2);
    current_time_ = scale_item_->GetTimeByPosX(current_item_->x());
    centerOn(current_item_);
    if (current_frame_ == duration_ * fps_)
    {
        emit CurrentFrameChanged(current_frame_ - 1);
    }
    else
    {
        emit CurrentFrameChanged(current_frame_);
    }
    update();
}

void TimeScaleDrawWidget::SetCurrentTimePosByClick(qreal x)
{
    if (x > scale_item_->GetLastX())
    {
        x = scale_item_->GetLastX();
    }

    if (x < scale_item_->GetZeroX())
    {
        x = scale_item_->GetZeroX();
    }

    current_item_->SetPos(x, SCALEITEMHEIGHT + 2);
    current_time_ = scale_item_->GetTimeByPosX(x);
    current_frame_ = scale_item_->GetFrameIndexByPosX(x);

    //传最后一帧出去会有问题
    if (current_frame_ == duration_ * fps_)
    {
        emit CurrentFrameChanged(current_frame_ - 1);
    }
    else
    {
        emit CurrentFrameChanged(current_frame_);
    }    
}

qreal TimeScaleDrawWidget::GetCurrentItemX()
{
    return current_item_->x();
}

//设置外部滚动条
void TimeScaleDrawWidget::SetScrollBar(QScrollBar* scroll_bar)
{
    if (scroll_bar == NULL)
    {
        return;
    }

    scroll_bar_ = scroll_bar;
    scroll_bar_->setMinimum(0);
    scroll_bar_->setPageStep(viewport()->width());
    scroll_bar_->setSingleStep(300);

    connect(scroll_bar_, SIGNAL(valueChanged(int)), horizontalScrollBar(), SLOT(setValue(int)));
}

//计算当前宽度下可显示所有帧数的精度
qint64 TimeScaleDrawWidget::CalculateMaxFramePerMark()
{
    int width = viewport()->width();
    int mark_num = (viewport()->width() - MINMARKWIDTH - 14) / MINMARKWIDTH;
    qint64 max_frame_per_mark = duration_ * fps_ / mark_num;

    if (max_frame_per_mark == 0)
    {
        return 1;
    }

    if (duration_ * fps_ > max_frame_per_mark * mark_num)
    {
        max_frame_per_mark += 1;
    }

    if (max_frame_per_mark > fps_ && max_frame_per_mark % fps_ != 0)
    {
        max_frame_per_mark = (max_frame_per_mark / fps_ + 1) * fps_;
    }
    else if (max_frame_per_mark < fps_ && fps_ % max_frame_per_mark != 0)
    {
        max_frame_per_mark = fps_ / (fps_ / max_frame_per_mark);
    }

    return max_frame_per_mark;
}

//重置外部滚动条
void TimeScaleDrawWidget::ResetScrollBar()
{
    if (scroll_bar_ == NULL)
    {
        return;
    }

    scroll_bar_->setPageStep(viewport()->width());
    scroll_bar_->setMaximum(horizontalScrollBar()->maximum());
    scroll_bar_->setValue(horizontalScrollBar()->value());
}

//精度改变
void TimeScaleDrawWidget::OnMarkFrameChanged(int frame_per_mark)
{
    if (frame_per_mark_ == frame_per_mark)
    {
        return;
    }

    frame_per_mark_ = frame_per_mark;
    scale_item_->SetMinimumFrame(frame_per_mark_);
    ResizeScence();

    update();
}

//void TimeScaleDrawWidget::OnToEndBtnClicked()
//{
//    qint64 total_frames = fps_ * duration_;
//    if (current_frame_ == total_frames)
//    {
//        return;
//    }
//
//    current_time_ = duration_;
//    current_item_->SetPos(scale_item_->GetLastX(), SCALEITEMHEIGHT + 2);
//    current_frame_ = scale_item_->GetFrameIndexByPosX(current_item_->x());
//    centerOn(current_item_);
//
//    //TODO 传最后一帧出去会不会有问题？
//    emit CurrentFrameChanged(current_frame_);
//}
//
//void TimeScaleDrawWidget::OnToBeginBtnClicked()
//{
//    if (current_frame_ == 0)
//    {
//        return;
//    }
//
//    current_time_ = 0;
//    current_item_->SetPos(scale_item_->GetZeroX(), SCALEITEMHEIGHT + 2);
//    current_frame_ = scale_item_->GetFrameIndexByPosX(current_item_->x());
//    centerOn(current_item_);
//
//    //TODO 传最后一帧出去会不会有问题？
//    emit CurrentFrameChanged(current_frame_);
//}
//
//void TimeScaleDrawWidget::OnForwardBtnClicked()
//{
//    qint64 total_frames = fps_ * duration_;
//    if (current_frame_ == total_frames)
//    {
//        return;
//    }
//
//    current_frame_ += frame_per_mark_;
//    if (current_frame_ > total_frames)
//    {
//        current_frame_ = total_frames;
//    }
//
//    current_item_->SetPos(scale_item_->GetFramePos(current_frame_), SCALEITEMHEIGHT + 2);
//    current_time_ = scale_item_->GetTimeByPosX(current_item_->x());
//    centerOn(current_item_);
//    emit CurrentFrameChanged(current_frame_);
//    update();
//}
//
//void TimeScaleDrawWidget::OnBackwardBtnClicked()
//{
//    if (current_frame_ == 0)
//    {
//        return;
//    }
//
//    current_frame_  -= frame_per_mark_;
//    if (current_frame_ < 0)
//    {
//        current_frame_ = 0;
//    }
//
//    current_item_->SetPos(scale_item_->GetFramePos(current_frame_), SCALEITEMHEIGHT + 2);
//    current_time_ = scale_item_->GetTimeByPosX(current_item_->x());
//    centerOn(current_item_);
//    emit CurrentFrameChanged(current_frame_);
//    update();
//}

void TimeScaleDrawWidget::OnCurrentItemPosChanged(qreal x)
{
    current_time_ = scale_item_->GetTimeByPosX(current_item_->x());
    qint64 temp_current_frame = current_frame_;
    current_frame_ = scale_item_->GetFrameIndexByPosX(current_item_->x());
    if (current_frame_ != temp_current_frame)
    {
        if (current_frame_ == duration_ * fps_)
        {
            emit CurrentFrameChanged(current_frame_ - 1);
        }
        else
        {
            emit CurrentFrameChanged(current_frame_);
        }
    }
}

//同步滚动条变化
void TimeScaleDrawWidget::OnScrollBarRangeChanged(int min, int max)
{
    if (scroll_bar_ == NULL)
    {
        return;
    }

    scroll_bar_->setMinimum(horizontalScrollBar()->minimum());
    scroll_bar_->setMaximum(horizontalScrollBar()->maximum());
}

// 同步滚动条变化
void TimeScaleDrawWidget::OnScrollBarValueChanged(int value)
{
    if (scroll_bar_ == NULL)
    {
        return;
    }

    scroll_bar_->setValue(value);
}

//调整scene大小和item位置
void TimeScaleDrawWidget::resizeEvent(QResizeEvent *event)
{
    if (duration_ == 0)
    {
        return;
    }
    CalculateMaxFramePerMark();
    ResizeScence();
    return QGraphicsView::resizeEvent(event);
}

void TimeScaleDrawWidget::wheelEvent(QWheelEvent * event)
{
    QPoint numDegrees = event->angleDelta() / 8;

    if (numDegrees.y() < 0)
    {
        emit WheelValueAdd();
    }
    else
    {
        emit WheelValueSub();
    }

    return QGraphicsView::wheelEvent(event);
}
