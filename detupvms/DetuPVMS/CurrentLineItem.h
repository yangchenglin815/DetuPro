/************************************************
 * \file CurrentLineItem.h
 *
 * \author LiChangLing
 * \date 2017
 * ��ǰʱ��item
 ************************************************/
#ifndef CONTROLLINEITEM_H
#define CONTROLLINEITEM_H

#include <QGraphicsItem>

class TimeScaleItem;
class TimeScaleDrawWidget;
class progressListView;

class CurrentLineItem : public QGraphicsItem
{
public:

    enum ControlType
    {
        Main = 0,       //�����ƣ����϶�
        Attendant       //����ߣ������϶�
    };

    CurrentLineItem(QGraphicsItem *parent = 0);
    ~CurrentLineItem();

    void SetType(ControlType type, QString& tooltip);
    void SetScaleItem(TimeScaleItem* item) { scale_item_ = item; }
    void SetView(TimeScaleDrawWidget* view) { view_ = view; }
    void SetPos(qreal ax, qreal ay);
    void SetPosWithMainItem(CurrentLineItem* main_item);

    //��Ӵ�item����ǰitem������item��ʾ
    void AddAttendantItem(CurrentLineItem* item);
    void RemoveAttendantItem(CurrentLineItem* item);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
        QWidget *widget) Q_DECL_OVERRIDE;

protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    ControlType type_;
    bool is_press_;
    TimeScaleItem* scale_item_;
    TimeScaleDrawWidget* view_;
    QList<CurrentLineItem*> attendant_items_;
};

#endif // CONTROLLINEITEM_H
