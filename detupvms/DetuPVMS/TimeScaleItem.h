/************************************************
 * \file TimeScaleItem.h
 *
 * \author LiChangLing
 * \date 2017
 * �̶ȿؼ�
 ************************************************/
#ifndef SCALEITEM_H
#define SCALEITEM_H

#include <QGraphicsItem>

#define MARKHEIGHT 8                           //�̶��߸߶�
#define MINMARKWIDTH 32                    //��Сһ�̶ȿ��
#define SCALEITEMHEIGHT 28              //�̶ȿؼ��߶�
#define TIMETEXTWIDTH 26                   //ʱ�����ֿ��
#define FRAMETEXTWIDTH 16              //֡���ֿ��
#define TEXTHEIGHT 18                          //���ָ߶�

class TimeScaleDrawWidget;


//�̶ȹ���ÿһ���̶ȵĿ�Ȳ��䣬ÿһ���̶ȴ����֡��������
//��һ���̶ȴ����֡�����ڵ���fpsʱ��ֻ��ʾʱ��̶ȣ�����һ���̶ȴ����ʱ������Ƶ��ʱ��
//��һ���̶ȴ����֡��С��fpsʱ������ʾʱ������ʾ֡��ʱ����sΪ��λ��s�̶�֮ǰ����һ�ξ�������֡������С��ÿһ���̶ȴ����֡������Ϊ������,
//��ʼ�̶���ʾ00f�������̶���ʾ��Ƶ��ʱ��
class TimeScaleItem : public QGraphicsItem
{
public:
    TimeScaleItem(QGraphicsItem *parent = 0);
    ~TimeScaleItem();

    //����ʱ������λ��
    void SetDurationAndFps(qint64 duration, int fps);

    //���ÿ̶�֡��
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

    //��ȡ�ɻ��ƿ̶ȵĿ��
    qreal GetDrawScaleWidth();
    //����0�̶��ߵ�x����
    qreal GetZeroX();
    //�������һ���̶���x����
    qreal GetLastX();

    //��ȡ���п̶ȸ�����ʱ��̶ȸ���
    qint64 GetTotalMarkNum();
    //��ȡһ�����ж��ٸ��̶ȣ���������ʼ�̶ȣ����߶θ���
    int GetMarkNumPerSecond();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void wheelEvent(QGraphicsSceneWheelEvent *event);

private:
    void CalculateMarkNum();

private:
    qint64 frame_per_mark_;      //һ���̶ȶ���֡
    qint64 duration_;       //��ʱ��
    int fps_;           //1s����֡
    qint64 total_frames_;          //��֡��
    TimeScaleDrawWidget* view_;
    int mark_per_sencond_;
    qint64 total_mark_num_;
    qint64 time_mark_num_;
    bool time_only_;
};

#endif // SCALEITEM_H
