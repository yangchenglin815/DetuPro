/************************************************
* \file directionArrowWgt.h
*
* \author yangchenglin
* \date 20170118
* 地图界面列表
************************************************/

#ifndef PANORAMAITEMWIDGET_H
#define PANORAMAITEMWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include "ui_panoramaItemWidget.h"
#include "constStruct.h"

class panoramaItemWidget : public QWidget
{
	Q_OBJECT

public:
	explicit panoramaItemWidget(QWidget *parent = 0);
	~panoramaItemWidget();
	void  initData(PanoMapPointInfo_t info_t);
	void  getItemData(PanoMapPointInfo_t &info_t);
	void  setItemData(PanoMapPointInfo_t &info_t);
	void setDeleteChecked(bool checked);
	void setNewHidden(bool hidden);
	bool getNewHidden();
	void removeId(int id);
signals:
	void sigOnDeleteItem();
protected:
	void enterEvent(QEvent *event);
	void leaveEvent(QEvent *event);
private:
	Ui::panoramaItemWidget ui;
	PanoMapPointInfo_t m_panoramaInfo;
	QPushButton *m_deleteBtn;
};

#endif // PANORAMAITEMWIDGET_H
