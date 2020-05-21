#include "ReplayCtrWgt.h"

ReplayCtrWgt::ReplayCtrWgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

ReplayCtrWgt::~ReplayCtrWgt()
{

}

void ReplayCtrWgt::setSpeedPos(int width)
{
	ui.prograssBarWgt->setSpeedPos(width);
}

int ReplayCtrWgt::getDurationBySlider()
{
	return ui.prograssBarWgt->getDurationBySlider();
}

void ReplayCtrWgt::initData(QList<m_replayInfoList> infoList)
{
	ui.prograssBarWgt->initData(infoList);
}

QString ReplayCtrWgt::getSelectedDate()
{
	return ui.dateWidget_->getSelectedDate();
}
