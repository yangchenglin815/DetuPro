#include "ptzPointCtrlWidget.h"
#include <QGridLayout>
#include "paneWidget.h"
#include "socketRequest.h"
#include "TcpDataManager.hpp"

ptzPointCtrlWidget::ptzPointCtrlWidget(QWidget *parent)
	: QWidget(parent)
	, m_row(4)
	, m_column(4)
{
	ui.setupUi(this);
	connect(&TcpDataManagerIns, SIGNAL(sigOnGetPtzPoint(QString, QString)), this, SLOT(slotOnGetPtzPoint(QString, QString)));
	init();
}

ptzPointCtrlWidget::~ptzPointCtrlWidget()
{

}

void ptzPointCtrlWidget::getPointStatus(QString ip)
{
	pointStatus = "";
	for (int i = 0; i < widgetList.size(); ++i)
	{
		pointStatus.append(QString::number(widgetList[i]->getButtonStatus()));
	}
	socketRequest::instance()->requestOnSavePTZPoint(ip, pointStatus);
}

void ptzPointCtrlWidget::init()
{
	QGridLayout *playout = new QGridLayout;
	int index = 0;
	for (int i = 0; i < m_row; ++i){
		for (int j = 0; j < m_column; ++j){
			paneWidget *pane = new paneWidget;
			widgetList.append(pane);
			//全景画面预置点按钮的点击事件传出去
			connect(pane, SIGNAL(sigOnClicked(bool, int)), this, SLOT(slotOnClicked(bool, int)));
			connect(pane, SIGNAL(sigOnStepOnPoint(int)), this, SLOT(sigOnStepOnPoint(int)));
			playout->addWidget(pane, i, j);
			pane->setButtonNum(++index);
		}
	}
	playout->setHorizontalSpacing(0);
	playout->setVerticalSpacing(0);
	playout->setContentsMargins(0, 0, 0, 0);
	setLayout(playout);

	if (widgetList.size() > 0)
	{
		for (int i = 0; i < 4; ++i)
		{
			widgetList[i]->setButtonEnabled(false);
		}
	}
}

void ptzPointCtrlWidget::slotOnGetPtzPoint(QString ip, QString point)
{
	if (widgetList.size() != point.length())
	{
		int j = widgetList.size();
		int k = point.length();
		Log::Error("widgetList size not equal point size");
		return;
	}
	for (int i = 0; i < widgetList.size(); ++i)
	{
		QString curr_point = QString(point.at(i));
		widgetList[i]->setButtonStatus(curr_point.toInt());
	}
}

void ptzPointCtrlWidget::slotOnClicked(bool checked, int num)
{
	for (int i = 0; i < widgetList.size(); ++i)
	{
		if (num -1 != i)
		{
			widgetList[i]->setButtonStatus(false);
		}
	}
	emit sigOnClicked(checked, num);
}
