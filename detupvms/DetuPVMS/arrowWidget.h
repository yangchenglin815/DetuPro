/************************************************
* \file arrowWidget.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* �ط�ҳ�������λ���
************************************************/
#ifndef ARROWWIDGET_H
#define ARROWWIDGET_H

#include <QWidget>

class arrowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit arrowWidget(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // ARROWWIDGET_H
