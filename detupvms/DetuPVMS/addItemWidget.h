#ifndef ADDITEMWIDGET_H
#define ADDITEMWIDGET_H

#include <QWidget>

#include "ui_addItemWidget.h"
#include "constStruct.h"

class addItemWidget : public QWidget
{
	Q_OBJECT

public:
	addItemWidget(QWidget *parent = 0);
	~addItemWidget();
	void initPtzData(const PtzInfo &ptzInfo);     //初始化球机列表
	void initSpyData(const SpyInfo &spyInfo);    //初始化枪机列表
	void getPtzData(PtzInfo &info);
	void getSpyData(SpyInfo &info);
private slots:
	void slotOnSettingsClicked();
	void slotOnUnbindClicked();
signals:
	void sigOnSettings(PtzInfo pInfo, SpyInfo sInfo);
	void sigOnUnbind(PtzInfo pInfo, SpyInfo sInfo);
private:
	void initConnect();
private:
	Ui::addItemWidget ui;
	PtzInfo m_curr_ptzInfo;
	SpyInfo m_curr_spyInfo;
};

#endif // ADDITEMWIDGET_H
