/************************************************
* \file deviceTittleWgt.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* 设备管理标题栏
************************************************/
#ifndef DEVICETITTLEWGT_H
#define DEVICETITTLEWGT_H

#include <QWidget>

class deviceTittleWgt : public QWidget
{
	Q_OBJECT

public:
explicit	deviceTittleWgt(QWidget *parent=0);
	~deviceTittleWgt();
	void setCurrentPage(int index);
private:
	void paintHomePage(QPainter &painter, int nHeight);
	void paintPtzPage(QPainter &painter, int nHeight);
protected:
	void paintEvent(QPaintEvent *event);
private:
	int m_currentIndex;
};

#endif // DEVICETITTLEWGT_H
