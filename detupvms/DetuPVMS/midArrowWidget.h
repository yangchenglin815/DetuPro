/************************************************
* \file midArrowWidget.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* ����֧��������
************************************************/
#ifndef MIDARROWWIDGET_H
#define MIDARROWWIDGET_H

#include <QWidget>

class midArrowWidget : public QWidget
{
	Q_OBJECT

public:
explicit	midArrowWidget(QWidget *parent = 0);
	~midArrowWidget();
protected:
	void paintEvent(QPaintEvent *event);	
};

#endif // MIDARROWWIDGET_H
