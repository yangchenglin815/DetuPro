#ifndef SELECTEDITEMWIDGET_H
#define SELECTEDITEMWIDGET_H

#include <QWidget>
#include "ui_selectedItemWidget.h"
#include "constStruct.h"

class selectedItemWidget : public QWidget
{
	Q_OBJECT

public:
	selectedItemWidget(QWidget *parent = 0);
	~selectedItemWidget();
	void initPTZData(const PtzInfo &info);
	void initSPYData(const SpyInfo &info);
	void setChecked();
    void getPTZData(PtzInfo &info);
	void getSPYData(SpyInfo &info);
private:
	Ui::selectedItemWidget ui;
	PtzInfo m_ptzInfo;
	SpyInfo m_spyInfo;
};

#endif // SELECTEDITEMWIDGET_H
