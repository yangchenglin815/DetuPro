#include <QtWidgets>
#include <QtGui>
#include <QtCore>
#include "CurrentLineItem.h"
#include "TimeScaleDrawWidget.h"
#include "TimeScaleItem.h"

CurrentLineItem::CurrentLineItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , type_(Main)
    , is_press_(false)
    , scale_item_(NULL)
    , view_(NULL)
{
    
    setFlag( QGraphicsItem::ItemClipsToShape, false);
    setCacheMode(QGraphicsItem::DeviceCoordinateCache);
}

CurrentLineItem::~CurrentLineItem()
{
}

void CurrentLineItem::SetType(ControlType type, QString& tooltip)
{
    type_ = type;
    setToolTip(tooltip);

    if (type_ == Main)
    {
        setFlag(QGraphicsItem::ItemIsMovable, true);
        setCursor(Qt::SplitHCursor);
    }
    else
    {
        setFlag(QGraphicsItem::ItemIsMovable, false);
    }
}

void CurrentLineItem::SetPos(qreal ax, qreal ay)
{
    setPos(ax, ay);

    //所有从item都跟着动，从item在其他scene上
    if (type_ == Main)
    {
        for each (CurrentLineItem* item in attendant_items_)
        {
            if (item == NULL)
            {
                continue;
            }
            item->SetPosWithMainItem(this);
        }
    }
}

void CurrentLineItem::SetPosWithMainItem(CurrentLineItem* main_item)
{
    if (type_ != Attendant || main_item == NULL)
    {
        return;
    }

    qreal main_x = mapFromItem(main_item, 0, 0).x();
    qreal real_x = mapToScene(QPointF(main_x, 0)).x();
    setPos(real_x, y());
    update();
}

//添加从item，当前item跟随主item显示
void CurrentLineItem::AddAttendantItem(CurrentLineItem* item)
{
    if (item == NULL || type_ != Main)
    {
        return;
    }

    if (!attendant_items_.contains(item))
    {
        attendant_items_.append(item);

    }
}

void CurrentLineItem::RemoveAttendantItem(CurrentLineItem* item)
{
    if (item == NULL || type_ != Main)
    {
        return;
    }

    attendant_items_.removeOne(item);
}

QRectF CurrentLineItem::boundingRect() const
{
    qreal adjust = 5;
    if (type_ == Main)
    {
        return QRectF(0 - adjust, 0 - SCALEITEMHEIGHT - 3,
            2 * adjust, SCALEITEMHEIGHT + 3);
    }
    
    return QRectF(0 - adjust, 0 - SCALEITEMHEIGHT - 3,
        2 * adjust, SCALEITEMHEIGHT + 3);
}

void CurrentLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (type_ == Main)
    {
        //开始结束标志
        QPen pen(QColor(255, 226, 0));
        pen.setWidth(1);
        painter->setPen(pen);

        //画一条线
        painter->drawLine(0, 1, 0, 0 - SCALEITEMHEIGHT);

        //画一个三角形
        QBrush brush(QColor(255, 226, 0));
        brush.setStyle(Qt::SolidPattern);

        QPainterPath path(QPointF(-5, 0 - SCALEITEMHEIGHT));
        path.lineTo(QPointF(5, 0 - SCALEITEMHEIGHT));
        path.lineTo(QPointF(0, 5 - SCALEITEMHEIGHT));
        path.lineTo(QPointF(-5, 0 - SCALEITEMHEIGHT));
        painter->fillPath(path, brush);
    }
    else
    {
        //开始结束标志
        QPen pen(QColor(255, 226, 0));
        pen.setWidth(1);
        painter->setPen(pen);

        //画一条线
        painter->drawLine(0, 3, 0, 0 - SCALEITEMHEIGHT - 4);
    }
}

void CurrentLineItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (is_press_ && type_ == Main)
    {
        qreal x = event->scenePos().x();
        if (x < MINMARKWIDTH)
        {
            x = MINMARKWIDTH;
        }
        if (x > scene()->width() - MINMARKWIDTH)
        {
            x = scene()->width() - MINMARKWIDTH;
        }

        SetPos(x, y());
    }

    event->accept();
}

void CurrentLineItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (type_ == Main)
    {
        is_press_ = true;
    }
    
    return QGraphicsItem::mousePressEvent(event);
}

void CurrentLineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (type_ == Main)
    {
        is_press_ = false;

        //将位置移至最近的刻度
        int old_x = x();
        if (scale_item_ != NULL)
        {
            SetPos(scale_item_->GetNearestPos(x()), y());
            /*QPoint mouse_pos = QCursor::pos();
            QCursor::setPos(QPoint(mouse_pos.x() - (event->scenePos().x() - x()), mouse_pos.y()));*/
            if (view_ != NULL)
            {
                view_->OnCurrentItemPosChanged(scale_item_->GetNearestPos(old_x));
            }
        }
    }
    
    event->accept();
}
