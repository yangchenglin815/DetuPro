#include "myTimer.h"
#include "ui_myTimer.h"
#include "logging.hpp"
#include <QPushButton>
#include <QTimer>
#include <QDebug>

myTimer::myTimer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myTimer)
  , durationWgt_(NULL)
  , scrollBar_(NULL)
  , currXpos_(-1)
{
    ui->setupUi(this);
	init();
    initConnect();
// 	m_replayInfo *info = NULL;
// 	info = new m_replayInfo;
// 	info->startTime = 1497845560;
// 	info->endTime = 1497865560;
 	info_.id = 0;
 	info_.duration = DURATION_HOUR;
	//info_.m_infoList.append(*info);
 	ui->widget->initData(info_);
}

myTimer::~myTimer()
{
    delete ui;
}

void myTimer::initData(QList<m_replayInfoList> infoList)
{
	if (infoList.size() > 0){
		info_ = infoList.at(0);
		ui->widget->initData(info_);
		return;
    }
	info_.m_infoList.clear();
	ui->widget->initData(info_);
}

void myTimer::setRecoderPos(int time)
{
	ui->widget->setRecoderPos(time);
}

void myTimer::resetRadition()
{
	if (durationWgt_ != NULL)
	{
		durationWgt_->resetDuration();
	}
	ui->widget->resetRadition();
	scrollBar_->setValue(0);
}

void myTimer::setSpeedPos(int w)
{
	if (durationWgt_ != NULL)
	{
		w -= 1;
		durationWgt_->move(w - durationWgt_->width(), this->height() - durationWgt_->height());
		ui->widget->setWidth(w);
		ui->widget->initData(info_);
	}
}

int myTimer::getDurationBySlider()
{
	if (durationWgt_ != NULL)
	{
		return durationWgt_->getDurationBySlider();
	}
	return DURATION_HOUR;
}

void myTimer::setMoveEnabled(bool enable)
{
	ui->widget->setMoveEnabled(enable);
}

void myTimer::initConnect()
{
     connect(ui->widget, SIGNAL(sigOnAddDuration()), this, SLOT(slotOnAddDuration()));
     connect(ui->widget, SIGNAL(sigOnDecreaseDuration()), this, SLOT(slotOnDecreaseDuration()));
	 connect(ui->widget, SIGNAL(sigOnRequestReplayRadio(int, int)), SIGNAL(sigOnRequestReplayRadio(int , int)));
	 connect(ui->widget, SIGNAL(sigOnUpdateSlider(int)), this, SLOT(slotOnUpdateSlider(int)));
}

void myTimer::init()
{
	ui->widget->setWidth(this->width());
	if (durationWgt_ == NULL)
	{
		durationWgt_ = new durationWidget;
		Log::Info("	durationWgt_->setParent(this);");
		durationWgt_->setParent(this);
		connect(durationWgt_, SIGNAL(sigOnValueChanged(int)), this, SLOT(slotOnValueChanged(int)));
		connect(durationWgt_, SIGNAL(sigOnGetCurrentX(int)), this, SLOT(slotOnGetCurrentX(int)));
	}
	durationWgt_->move(this->width() - durationWgt_->width() - 16, this->height() - durationWgt_->height());
	scrollBar_ = ui->scrollArea->horizontalScrollBar();
}

void myTimer::slotOnValueChanged(int value)
{
     switch(value)
     {
     case 0:
         info_.duration = DURATION_HOUR;
         break;
     case 1:
         info_.duration = DURATION_HALF_HOUR;
         break;
     case 2:
         info_.duration = DURATION_TEN_MIN;
         break;
     case 3:
         info_.duration = DURATION_MIN;
         break;
     case 4:
         info_.duration = DURATION_TEN_SECOND;
         break;
     case 5:
         info_.duration = DURATION_SECOND;
         break;
     }
	 ui->widget->updateSliderPos(info_.duration);
     ui->widget->initData(info_);
}

void myTimer::slotOnAddDuration()
{
    if(durationWgt_ != NULL){
         durationWgt_->slotOnAddDuration();
    }
}

void myTimer::slotOnDecreaseDuration()
{
    if(durationWgt_ != NULL){
         durationWgt_->slotOnDecreaseDuration();
    }
}

void myTimer::slotOnGetCurrentX(int x)
{
    scrollBar_->setValue(x);
}

void myTimer::slotOnUpdateSlider(int x)
{
	currXpos_ = x;
	QTimer::singleShot(600, this, SLOT(updateSlider()));
}

void myTimer::updateSlider()
{
	int pagestep = scrollBar_->pageStep();
	scrollBar_->setValue(currXpos_ - pagestep / 2);
}
