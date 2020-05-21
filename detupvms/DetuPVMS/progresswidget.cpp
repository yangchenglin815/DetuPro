#include "progresswidget.h"
#include "ui_progresswidget.h"
#include "commonFun.h"

progressWidget::progressWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::progressWidget)
	,  m_selectId(-1)
	, current_item_(NULL)
{
    ui->setupUi(this);
	initConnect();
// 	m_replayInfo *info = NULL;
// 	info = new m_replayInfo;
// 	info->startTime = 1497845560;
// 	info->endTime = 1497865560;
// 	m_replayInfo *info1 = NULL;
// 	info1 = new m_replayInfo;
// 	info1->startTime = 1497957452;
// 	info1->endTime = 1497974340;
// 	m_replayInfoList *info_ = NULL;
// 	info_ = new m_replayInfoList;
// 	info_->id = 1;
// 	info_->m_infoList.append(*info);
// 	info_->m_infoList.append(*info1);
// 	m_InfoList.append(*info_);
// 	initData(m_InfoList);
}

progressWidget::~progressWidget()
{

}

void progressWidget::initData(QList<m_replayInfoList> &m_infoList)
{
	m_InfoList = m_infoList;
	generateUI();
}

void progressWidget::getSelectId(int selectId)
{
	m_selectId = selectId;
}

void progressWidget::resetRadation()
{
	ui->widget_3->resetRadition();
}

void progressWidget::setRecoderPos(int time)
{
	ui->widget_3->setRecoderPos(time);
}

void progressWidget::generateUI()
{
	ui->listView->clearItems();
	int count = m_InfoList.length();
	for (int i = 0; i < count; i++) {
		//m_InfoList[i].id = i + 1;
	     ui->listView->appendItem(m_InfoList[i]);
    }
}

void progressWidget::initConnect()
{
	connect(ui->widget_3, SIGNAL(sigOnRequestReplayRadio(int)), this, SIGNAL(sigOnRequestReplayRadio(int)));
}
