/************************************************
* \file progresswidget.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* 进度条窗口
************************************************/
#ifndef PROGRESSWIDGET_H
#define PROGRESSWIDGET_H

#include <QWidget>
#include "constStruct.h"
#include "CurrentLineItem.h"

namespace Ui {
class progressWidget;
}

class progressWidget : public QWidget
{
    Q_OBJECT

public:
    explicit progressWidget(QWidget *parent = 0);
    ~progressWidget();
	void initData(QList<m_replayInfoList> &m_infoList);
	void getSelectId(int selectId);
	void resetRadation();
	void setRecoderPos(int time);
signals:
	void sigOnRequestReplayRadio(int time);
private:
	void generateUI();
	void initConnect();
private:
    Ui::progressWidget *ui;
	int m_nCurPage;
	int m_selectId;
	QList<m_replayInfoList> m_InfoList;
	CurrentLineItem *current_item_;
	int m_time;
};

#endif // PROGRESSWIDGET_H
