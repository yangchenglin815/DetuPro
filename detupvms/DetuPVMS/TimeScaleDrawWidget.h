/************************************************
 * \file TimeScaleDrawWidget.h
 *
 * \author LiChangLing
 * \date 2017
 * 刻度绘制view
 ************************************************/
#ifndef TIMESCALEDRAWWIDGET_H
#define TIMESCALEDRAWWIDGET_H

#include <QGraphicsView>

class TimeScaleItem;
class CurrentLineItem;

class TimeScaleDrawWidget : public QGraphicsView
{
    Q_OBJECT

public:
    TimeScaleDrawWidget(QWidget *parent = 0);
    ~TimeScaleDrawWidget();

    //设置时长，单位秒
    void SetDurationAndFPS(qint64 duration, int fps);
    void SetCurrentTime(qint64 current);
    void SetCurrentFrame(qint64 frame);
    void SetCurrentTimePosByClick(qreal x);

    qint64 GetCurrentTime()  { return current_time_; }
    qint64 GetCurrentFrame() { return current_frame_; }

    qreal GetCurrentItemX();

    void SetScrollBar(QScrollBar* scroll_bar);
    QScrollBar* GetScrollBar() { return scroll_bar_; }

    //计算当前宽度下可显示所有帧数的精度
    qint64 CalculateMaxFramePerMark();

    TimeScaleItem* GetTimeItem() { return scale_item_; }
    CurrentLineItem* GetCurrentItem() { return current_item_; }

signals:
    //当前时刻
    void CurrentTimeChanged(qint64 time);
    void CurrentFrameChanged(qint64 frame);
    void ClipDurationChanged(qint64 time);
    void WheelValueAdd();
    void WheelValueSub();
    void SceneWidthChanged(int width);

public slots:
    void OnMarkFrameChanged(int frame_per_mark);
    /*void OnToEndBtnClicked();
    void OnToBeginBtnClicked();
    void OnForwardBtnClicked();
    void OnBackwardBtnClicked();*/
    void OnCurrentItemPosChanged(qreal x);

private slots:
    void OnScrollBarRangeChanged(int min, int max);
    void OnScrollBarValueChanged(int value);

protected:
    virtual void resizeEvent(QResizeEvent *event);
    virtual void	wheelEvent(QWheelEvent * event);

private:
    void InitScene();
    void ResetScrollBar();
    void ResizeScence();

private:
    int fps_;
    qint64 frame_per_mark_;
    qint64 current_time_;
    qint64 current_frame_;
    qint64 duration_;

    QGraphicsScene* scene_;
    TimeScaleItem* scale_item_;     //刻度item
    CurrentLineItem* current_item_;     //当前时间控制条

    QScrollBar* scroll_bar_;
};

#endif // TIMESLIDERDRAWWIDGET_H
