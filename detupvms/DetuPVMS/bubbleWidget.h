/************************************************
* \file bubbleWidget.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* 技术支持tips
************************************************/
#ifndef BUBBLEWIDGET_H
#define BUBBLEWIDGET_H

#include <QWidget>

namespace Ui {
class bubbleWidget;
}

class bubbleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit bubbleWidget(QWidget *parent = 0);
    ~bubbleWidget();
private:
    Ui::bubbleWidget *ui;
};

#endif // BUBBLEWIDGET_H
