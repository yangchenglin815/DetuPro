/************************************************
 * \file TimeScaleItem.h
 *
 * \author LiChangLing
 * \date 2017
 * 刻度控件
 ************************************************/
#ifndef SCALEITEM_H
#define SCALEITEM_H

#include <QGraphicsItem>

#define MARKHEIGHT 8                           //刻度线高度
#define MINMARKWIDTH 32                    //最小一刻度宽度
#define SCALEITEMHEIGHT 28              //刻度控件高度
#define TIMETEXTWIDTH 26                   //时间文字宽度
#define FRAMETEXTWIDTH 16              //帧文字宽度
#define TEXTHEIGHT 18                          //文字高度

class TimeScaleDrawWidget;


//刻度规则，每一个刻度的宽度不变，每一个刻度代表的帧数可设置
//当一个刻度代表的帧数大于等于fps时，只显示时间刻度，最后的一个刻度代表的时间是视频总时间
//当一个刻度代表的帧数小于fps时，既显示时间又显示帧，时间以s为单位，s刻度之前的那一段距离代表的帧数可能小于每一个刻度代表的帧数（因为余数）,
//开始刻度显示00f，结束刻度显示视频总时间
class TimeScaleItem : public QGraphicsItem
{
public:
    TimeScaleItem(QGraphicsItem *parent = 0);
    ~TimeScaleItem();

    //设置时长，单位秒
    void SetDurationAndFps(qint64 duration, int fps);

    //设置刻度帧数
    void SetMinimumFrame(qint64 frame_per_mark);

    void SetView(TimeScaleDrawWidget* view) { view_ = view; }

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
        QWidget *widget) Q_DECL_OVERRIDE;

    QString TimeToString(qint64 time);
    QString FramesToString(qint64 frames);

    qreal GetTimePos(qint64 time);
    qreal GetFramePos(qint64 frame);
    qint64 GetFramePerMark() { return frame_per_mark_; }

    qreal GetNearestPos(qreal x);

    qint64 GetTimeByPosX(qreal x);
    qint64 GetFrameIndexByPosX(qreal x);

    //获取可绘制刻度的宽度
    qreal GetDrawScaleWidth();
    //返回0刻度线的x坐标
    qreal GetZeroX();
    //返回最后一个刻度线x坐标
    qreal GetLastX();

    //获取所有刻度个数和时间刻度个数
    qint64 GetTotalMarkNum();
    //获取一秒内有多少个刻度，不包含开始刻度，既线段个数
    int GetMarkNumPerSecond();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void wheelEvent(QGraphicsSceneWheelEvent *event);

private:
    void CalculateMarkNum();

private:
    qint64 frame_per_mark_;      //一个刻度多少帧
    qint64 duration_;       //总时长
    int fps_;           //1s多少帧
    qint64 total_frames_;          //总帧数
    TimeScaleDrawWidget* view_;
    int mark_per_sencond_;
    qint64 total_mark_num_;
    qint64 time_mark_num_;
    bool time_only_;
};

#endif // SCALEITEM_H
