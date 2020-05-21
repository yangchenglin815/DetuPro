/************************************************
 * \file TimeScaleDrawWidget.h
 *
 * \author LiChangLing
 * \date 2017
 * �̶Ȼ���view
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

    //����ʱ������λ��
    void SetDurationAndFPS(qint64 duration, int fps);
    void SetCurrentTime(qint64 current);
    void SetCurrentFrame(qint64 frame);
    void SetCurrentTimePosByClick(qreal x);

    qint64 GetCurrentTime()  { return current_time_; }
    qint64 GetCurrentFrame() { return current_frame_; }

    qreal GetCurrentItemX();

    void SetScrollBar(QScrollBar* scroll_bar);
    QScrollBar* GetScrollBar() { return scroll_bar_; }

    //���㵱ǰ����¿���ʾ����֡���ľ���
    qint64 CalculateMaxFramePerMark();

    TimeScaleItem* GetTimeItem() { return scale_item_; }
    CurrentLineItem* GetCurrentItem() { return current_item_; }

signals:
    //��ǰʱ��
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
    TimeScaleItem* scale_item_;     //�̶�item
    CurrentLineItem* current_item_;     //��ǰʱ�������

    QScrollBar* scroll_bar_;
};

#endif // TIMESLIDERDRAWWIDGET_H
