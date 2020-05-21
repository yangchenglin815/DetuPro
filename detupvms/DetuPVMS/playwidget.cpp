#include <QMouseEvent> 
#include <QDebug>
#include <QDateTime>
#include <QGraphicsOpacityEffect>
#include <QTimer>


#include "playwidget.h"

#include "ui_playwidget.h"
#include "HttpClient.h"
#include "imgproc/imp_lib.h"

#include "DetuPVMSIni.h"

#include "feedback.h"

//全局控制器
#include "MessageManager.h"
#include "SocketManager.h"
#include "TcpDataManager.hpp"
#include "ListAndGLWindowManager.h"
#include "PVMSEventManager.h"

#include "Preview/deviceChildItemWidget.h"
#include "Preview/deviceItemWidget.h"
#include "ViewSignal.h"


using namespace dm::server;

playWidget::playWidget(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::playWidget),
	current_select_GLWindow_(GL1),
	m_selectId(-1),
	is_ball_cam_open_(false),
	is_four_channel_playing_(false),
	is_full_screenm_(false),
	singleMode_(false),
	currentPlayMode_(PanoViewMode::PanoViewMode_FLAT),
	m_online_(false),
	fourFullScreen_(false)
{
	ui->setupUi(this);
	init();
	initConnect();
}

playWidget::~playWidget()
{

}

bool playWidget::IsInitPlayingOK(int glwindow_num)
{
	if (glwindow_num >= GL0 && glwindow_num <= GL4)
	{
		if (glwindow_num == GL0)
		{
			return false;
		}
		if (windowMap_[glwindow_num]->isStitchFileOk())
		{
			return true;
		}
	}
	return false;
}

void playWidget::ClosePlaySourse(int glwindow_num)
{
	if (glwindow_num >= GL0 && glwindow_num <= GL4)
	{
		if (glwindow_num == GL0)
		{
			return;
		}
		if (windowMap_[glwindow_num]->isPlaying())
		{
			windowMap_[glwindow_num]->closeStream();
			windowMap_[glwindow_num]->closeShowTime();
			windowMap_[glwindow_num]->closePTZ();
			windowMap_[glwindow_num]->closeUI();
		}
		//每次设置都更新四个窗口是否都在播放
		UpdateIsFourChannelPlaying();
	}
}

void playWidget::ClosePlayer()
{
	Log::Info("homeWidget closeplayer");
	QMap<int, playModeWgt*>::const_iterator i = windowMap_.constBegin();
	int index = 1;
	while (i != windowMap_.constEnd()) {
		if (windowMap_[index]->isPlaying())
		{
			windowMap_[index]->closePlayer();
		}
		++index;
		++i;
	}
	ListAndGLWindowManagerIns.ClearMap();
}

void playWidget::InitData(const QList<deviceInfo> &itemInfoList)
{
	GenerateUI();
}

void playWidget::GetSelectId(int selectId)
{
	m_selectId = selectId;
}

//更新列表
void playWidget::UpdateListSlot(QList<deviceInfo> deviceList)
{
	InfoList_ = deviceList;
	InitData(InfoList_);
}

void playWidget::ResetPlayerStatus()
{
	QMap<int, playModeWgt*>::const_iterator i = windowMap_.constBegin();
	int index = 1;
	while (i != windowMap_.constEnd()) {
		if (windowMap_[index]->isPlaying())
		{
			windowMap_[index]->close();

		}
		++index;
		++i;
	}
	ListAndGLWindowManagerIns.ClearMap();
}

void playWidget::setPosMove()
{
	QMap<int, playModeWgt*>::const_iterator i = windowMap_.constBegin();
	int index = 1;
	while (i != windowMap_.constEnd()) {
		windowMap_[index]->setPosMove();
		++index;
		++i;
	}
}

void playWidget::setTimePos()
{
	QMap<int, playModeWgt*>::const_iterator i = windowMap_.constBegin();
	int index = 1;
	while (i != windowMap_.constEnd()) {
		windowMap_[index]->setTimePos(0);
		++index;
		++i;
	}
}

void playWidget::setHiddenCtrl(bool visible)
{
	if (!visible)
	{
		QMap<int, playModeWgt*>::const_iterator i = windowMap_.constBegin();
		int index = 1;
		while (i != windowMap_.constEnd()) {
			windowMap_[index]->setGLWindowMax(false);
			windowMap_[index]->setHiddenCtrl(visible);
			++index;
			++i;
		}
	}
	else
	{
		QMap<int, playModeWgt*>::const_iterator i = windowMap_.constBegin();
		int index = 1;
		while (i != windowMap_.constEnd()) {
			windowMap_[index]->setGLWindowMax(true);
			bool ret = windowMap_[index]->isPlaying();
			windowMap_[index]->setHiddenCtrl(ret);
			++index;
			++i;
		}
	}
}

void playWidget::setStatusShowLabel(PLAY_STATUS play_status)
{
	QMap<int, playModeWgt*>::const_iterator i = windowMap_.constBegin();
	int index = 1;
	while (i != windowMap_.constEnd()) {
		if (windowMap_[index]->isPlaying())
		{
			windowMap_[index]->onSetGlLabelSlot(play_status);
		}
		++index;
		++i;
	}
}

void playWidget::slotOnSingleModeSelected()
{
	if (is_ball_cam_open_)
	{
		return;
	}
	singleMode_ = true;
	initModeBtn();
	initSingleFunction();
	initDecodeStatus(1);
	QTimer::singleShot(20, this, SLOT(slotOnUpdate()));
}

void playWidget::slotOnFourModeSelected()
{
	if (is_ball_cam_open_)
	{
		return;
	}
	singleMode_ = false;
	initModeBtn();
	initSingleFunction();
	initDecodeStatus(0);
	QTimer::singleShot(20, this, SLOT(slotOnUpdate()));
}

void playWidget::slotOnSwitchBallCam(bool is_ball_cam_open)
{
	is_ball_cam_open_ = is_ball_cam_open;
	if (is_ball_cam_open)
	{
		//切换到球模式，球机联动必须用球模式
		if (currentPlayMode_ != PanoViewMode::PanoViewMode_DEFAULT)
		{
			currentPlayMode_ = PanoViewMode::PanoViewMode_DEFAULT;
			initModeBtn();
			emit sigOnSwitchViewMode(PanoViewMode::PanoViewMode_DEFAULT);
		}

		singleMode_ = true;
		initModeBtn();
		initSingleFunction();
	}
	else
	{
		singleMode_ = false;
		initModeBtn();
		initSingleFunction();
	}
}

void playWidget::slotOnOriginModeSelected()
{
	if (is_ball_cam_open_)
	{
		return;
	}
	if (currentPlayMode_ == PanoViewMode::PanoViewMode_FLAT)
	{
		return;
	}
	currentPlayMode_ = PanoViewMode::PanoViewMode_FLAT;
	initModeBtn();
	emit sigOnSwitchViewMode(PanoViewMode::PanoViewMode_FLAT);
}

void playWidget::slotOnPanoModeSelected()
{
	if (is_ball_cam_open_)
	{
		return;
	}
	if (currentPlayMode_ == PanoViewMode::PanoViewMode_DEFAULT)
	{
		return;
	}
	currentPlayMode_ = PanoViewMode::PanoViewMode_DEFAULT;
	initModeBtn();
	emit sigOnSwitchViewMode(PanoViewMode::PanoViewMode_DEFAULT);
}

void playWidget::slot_fullOfScreenMode()
{
	if (current_select_GLWindow_ >= GL0 && current_select_GLWindow_ <= GL4)
	{
		if (current_select_GLWindow_ == GL0)
		{
			ui->gidWidget->setWindowFlags(Qt::Window);
			ui->gidWidget->showFullScreen();
			fourFullScreen_ = true;
		}
		else
		{
			windowMap_[current_select_GLWindow_]->setWindowFlags(Qt::Window);
			windowMap_[current_select_GLWindow_]->showFullScreen();
		}
		QTimer::singleShot(20, this, SLOT(slotOnUpdate()));
	}
}

void playWidget::slotOnResetStatus(int item_num)
{
	if (item_num == 0 || InfoList_.size() == 0)		//坑
	{
		return;
	}
	if (current_select_GLWindow_ >= GL0 && current_select_GLWindow_ <= GL4)
	{
		if (current_select_GLWindow_ == GL0)
		{
			windowMap_[GL1]->closeShowTime();
		}
		else
		{
			windowMap_[current_select_GLWindow_]->closeShowTime();
		}
	}
	InfoList_[item_num-1].bClicked = false;
	InitData(InfoList_);
	emit sigOnTransportList(InfoList_);

}

void playWidget::slotOnCloseSubStreamClearPlayer(int id)
{
	if (windowMap_[id]->isPlaying())
	{
		windowMap_[id]->clearPlay();
	}
}

void playWidget::slotOnPlaywgtSelected(int index)
{
	//默认预览index是2
	if (index == 2)
	{
		emit sigOnSwitchPlayFlag(true);
	}
	else
	{
		emit sigOnSwitchPlayFlag(false);
	}
}

void playWidget::slotOnGetRecordTime(int time)
{
	time -= 28800;
	QString time_ = QDateTime::fromTime_t(time).toString("yyyy-MM-dd hh:mm:ss");
	QMap<int, playModeWgt*>::const_iterator i = windowMap_.constBegin();
	int index = 1;
	while (i != windowMap_.constEnd()) {
		if (sender() == windowMap_[index])
		{
			if (time > oriTimeList_[index])
			{
				windowMap_[index]->setShowTime(time_, 0);
				windowMap_[index]->setShowStreamInfo();
			}
			oriTimeList_[index] = time;
		}
		++index;
		++i;
	}
}

void playWidget::slotOnUpdate()
{
	if (current_select_GLWindow_ >= GL0 && current_select_GLWindow_ <= GL4)
	{
		if (current_select_GLWindow_ == GL0)
		{
			windowMap_[GL1]->setTimePos(0);
		}
		else
		{
			windowMap_[current_select_GLWindow_]->setTimePos(0);
		}
	}
}

void playWidget::slotOnGetBitRate(unsigned char streamId, api_detu_client_av_param_t* res)
{
	if (current_select_GLWindow_ > GL0 && current_select_GLWindow_ <= GL4 && !DetuPVMSIni::getGlobalSettingGet())
	{
		windowMap_[current_select_GLWindow_]->setStreamInfo(QString("%1x%2").arg(res->nVideoWidth).arg(res->nVideoHeight), res->nFrameRate, res->nBitRate);
	}
}

void playWidget::slotOnRebootM1ResetPlayer(int id)
{
	if (windowMap_[id]->isPlaying())
	{
		windowMap_[id]->close();
	}
}

void playWidget::slotOnPlayRequestSucceed()
{
	current_select_playmodewgt_->setStitchStatus(StitchStatus::STITCH_STATUS_GET_SRS);
}

void playWidget::slotOnSetFullScreen(bool is_full_screen)
{
	ui->leftWidget_->setVisible(is_full_screen);
	ui->widget_2->setVisible(is_full_screen);
	ui->bottomWidget_->setVisible(is_full_screen);
}

playModeWgt* playWidget::SetPlayModelWgt()
{
	//如果四个窗口没有同时播放，选择未播的窗口播放
	if (!is_four_channel_playing_)
	{
		QMap<int, playModeWgt*>::const_iterator i = windowMap_.constBegin();
		int index = 1;
		while (i != windowMap_.constEnd()) {
			if (!windowMap_[index]->isPlaying())
			{
				ListAndGLWindowManagerIns.UpdateMap(current_select_item_info_.id, index);
				current_select_GLWindow_ = (CurrentSelectGLWindow)index;
				//每次设置都更新四个窗口是否都在播放
				UpdateIsFourChannelPlaying();
				return windowMap_[index];
			}
			++index;
			++i;
		}
		return NULL;
	}
	//如果四个窗口都在播放，选择选中的窗口播放
	else
	{
		if (current_select_GLWindow_ > GL0 && current_select_GLWindow_ <= GL4)
		{
			ListAndGLWindowManagerIns.UpdateMap(current_select_item_info_.id, current_select_GLWindow_);
			//更新四个窗口是否都在播放
			UpdateIsFourChannelPlaying();
			return windowMap_[current_select_GLWindow_];
		}
		return NULL;
	}
}

playModeWgt* playWidget::GetPlayModelWgt(int list_item_num)
{
	int index = (CurrentSelectGLWindow)ListAndGLWindowManagerIns.GetGLValue(list_item_num);
	if (index > 0 && index <= GLWINDOW_NUM)
	{
		return windowMap_[index];
	}
	return NULL;
}

void playWidget::UpdateIsFourChannelPlaying()
{
 	if (windowMap_[GL1]->isPlaying() && windowMap_[GL2]->isPlaying() && windowMap_[GL3]->isPlaying() && windowMap_[GL4]->isPlaying())
 		is_four_channel_playing_ = true;
	else
 		is_four_channel_playing_ = false;
}



void playWidget::closeSelectedGLWindow(CurrentSelectGLWindow current_select_GLWindow_)
{
	if (!IsInitPlayingOK(current_select_GLWindow_))
	{
		return;
	}
	else
	{
		InfoList_[ListAndGLWindowManagerIns.GetItemValue(current_select_GLWindow_)-1].bClicked = !InfoList_[ListAndGLWindowManagerIns.GetItemValue(current_select_GLWindow_)-1].bClicked;
	}

	InitData(InfoList_);
	ClosePlaySourse(current_select_GLWindow_);

	ListAndGLWindowManagerIns.RemoveMap(ListAndGLWindowManagerIns.GetItemValue(current_select_GLWindow_), current_select_GLWindow_);
	emit sigOnTransportList(InfoList_);
}

bool playWidget::eventFilter(QObject *watched, QEvent *event)
{
	if (watched == ui->playWidget1_)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			ui->playWidget1_->setTopWgtVisable(true);
			ui->playWidget2_->setTopWgtVisable(false);
			ui->playWidget3_->setTopWgtVisable(false);
			ui->playWidget4_->setTopWgtVisable(false);
			ui->singleBtn_->setEnabled(true);
			current_select_GLWindow_ = GL1;
			return true;
		}
		if (event->type() == QEvent::MouseButtonDblClick)
		{
			if (!fourFullScreen_)
			{
				if (!is_full_screenm_)
				{
					ui->playWidget2_->hide();
					ui->playWidget3_->hide();
					ui->playWidget4_->hide();
					ui->playWidget2_->OnSwitchPlatFlagSlot(false);
					ui->playWidget3_->OnSwitchPlatFlagSlot(false);
					ui->playWidget4_->OnSwitchPlatFlagSlot(false);
					ui->playWidget2_->setHiddenCtrl(false);
					ui->playWidget3_->setHiddenCtrl(false);
					ui->playWidget4_->setHiddenCtrl(false);
					singleMode_ = true;
					is_full_screenm_ = true;


					emit PVMSEventManagerManagerIns.sigOnSetFullScreen(false);

				}
				else
				{
					ui->playWidget1_->show();
					ui->playWidget2_->show();
					ui->playWidget3_->show();
					ui->playWidget4_->show();
					ui->playWidget2_->OnSwitchPlatFlagSlot(ui->playWidget2_->isPlaying() ? 1 : 0);
					ui->playWidget3_->OnSwitchPlatFlagSlot(ui->playWidget3_->isPlaying() ? 1 : 0);
					ui->playWidget4_->OnSwitchPlatFlagSlot(ui->playWidget4_->isPlaying() ? 1 : 0);
					ui->playWidget2_->setHiddenCtrl(ui->playWidget2_->isPlaying() ? 1 : 0);
					ui->playWidget3_->setHiddenCtrl(ui->playWidget3_->isPlaying() ? 1 : 0);
					ui->playWidget4_->setHiddenCtrl(ui->playWidget4_->isPlaying() ? 1 : 0);
					singleMode_ = false;
					is_full_screenm_ = false;

					emit PVMSEventManagerManagerIns.sigOnSetFullScreen(true);

				}
				QTimer::singleShot(20, this, SLOT(slotOnUpdate()));
				initModeBtn();
				return true;
			}
		}
		if (event->type() == QEvent::KeyPress){
			QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
			if (keyEvent->key() == Qt::Key_Escape){
				if (ui->playWidget1_->isFullScreen()){
					ui->playWidget1_->setWindowFlags(Qt::SubWindow);
					ui->playWidget1_->showNormal();
					QTimer::singleShot(20, this, SLOT(slotOnUpdate()));
				}
				if (fourFullScreen_)
				{
					if (ui->gidWidget->isFullScreen()){
						ui->gidWidget->setWindowFlags(Qt::SubWindow);
						ui->gidWidget->showNormal();
						fourFullScreen_ = false;
					}
				}
				return true;
			}
		}
	}

	else if (watched == ui->playWidget2_)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			ui->playWidget1_->setTopWgtVisable(false);
			ui->playWidget2_->setTopWgtVisable(true);
			ui->playWidget3_->setTopWgtVisable(false);
			ui->playWidget4_->setTopWgtVisable(false);
			ui->singleBtn_->setEnabled(true);
			current_select_GLWindow_ = GL2;
			return true;
		}
		if (event->type() == QEvent::MouseButtonDblClick)
		{
			if (!fourFullScreen_)
			{
				if (!is_full_screenm_)
				{
					ui->playWidget1_->hide();
					ui->playWidget3_->hide();
					ui->playWidget4_->hide();
					ui->playWidget1_->OnSwitchPlatFlagSlot(false);
					ui->playWidget3_->OnSwitchPlatFlagSlot(false);
					ui->playWidget4_->OnSwitchPlatFlagSlot(false);
					ui->playWidget1_->setHiddenCtrl(false);
					ui->playWidget3_->setHiddenCtrl(false);
					ui->playWidget4_->setHiddenCtrl(false);
					singleMode_ = true;
					is_full_screenm_ = true;

					emit PVMSEventManagerManagerIns.sigOnSetFullScreen(false);
				}
				else
				{
					ui->playWidget1_->show();
					ui->playWidget2_->show();
					ui->playWidget3_->show();
					ui->playWidget4_->show();
					ui->playWidget1_->OnSwitchPlatFlagSlot(ui->playWidget1_->isPlaying() ? 1 : 0);
					ui->playWidget3_->OnSwitchPlatFlagSlot(ui->playWidget3_->isPlaying() ? 1 : 0);
					ui->playWidget4_->OnSwitchPlatFlagSlot(ui->playWidget4_->isPlaying() ? 1 : 0);
					ui->playWidget1_->setHiddenCtrl(ui->playWidget1_->isPlaying() ? 1 : 0);
					ui->playWidget3_->setHiddenCtrl(ui->playWidget3_->isPlaying() ? 1 : 0);
					ui->playWidget4_->setHiddenCtrl(ui->playWidget4_->isPlaying() ? 1 : 0);
					singleMode_ = false;
					is_full_screenm_ = false;

					emit PVMSEventManagerManagerIns.sigOnSetFullScreen(true);
				}
				QTimer::singleShot(20, this, SLOT(slotOnUpdate()));
				initModeBtn();
				return true;
			}
		}
		if (event->type() == QEvent::KeyPress){
			QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
			if (keyEvent->key() == Qt::Key_Escape){
				if (ui->playWidget2_->isFullScreen()){
					ui->playWidget2_->setWindowFlags(Qt::SubWindow);
					ui->playWidget2_->showNormal();
				}
				if (fourFullScreen_)
				{
					if (ui->gidWidget->isFullScreen()){
						ui->gidWidget->setWindowFlags(Qt::SubWindow);
						ui->gidWidget->showNormal();
						fourFullScreen_ = false;
					}
				}
				return true;
			}
		}
	}
	else if (watched == ui->playWidget3_)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			ui->playWidget1_->setTopWgtVisable(false);
			ui->playWidget2_->setTopWgtVisable(false);
			ui->playWidget3_->setTopWgtVisable(true);
			ui->playWidget4_->setTopWgtVisable(false);
			ui->singleBtn_->setEnabled(true);
			current_select_GLWindow_ = GL3;
			return true;
		}
		if (event->type() == QEvent::MouseButtonDblClick)
		{
			if (!fourFullScreen_)
			{
				if (!is_full_screenm_)
				{
					ui->playWidget1_->hide();
					ui->playWidget2_->hide();
					ui->playWidget4_->hide();
					ui->playWidget1_->OnSwitchPlatFlagSlot(false);
					ui->playWidget2_->OnSwitchPlatFlagSlot(false);
					ui->playWidget4_->OnSwitchPlatFlagSlot(false);
					ui->playWidget1_->setHiddenCtrl(false);
					ui->playWidget2_->setHiddenCtrl(false);
					ui->playWidget4_->setHiddenCtrl(false);
					singleMode_ = true;
					is_full_screenm_ = true;

					emit PVMSEventManagerManagerIns.sigOnSetFullScreen(false);
				}
				else
				{
					ui->playWidget1_->show();
					ui->playWidget2_->show();
					ui->playWidget3_->show();
					ui->playWidget4_->show();
					ui->playWidget1_->OnSwitchPlatFlagSlot(ui->playWidget1_->isPlaying() ? 1 : 0);
					ui->playWidget2_->OnSwitchPlatFlagSlot(ui->playWidget2_->isPlaying() ? 1 : 0);
					ui->playWidget4_->OnSwitchPlatFlagSlot(ui->playWidget4_->isPlaying() ? 1 : 0);
					ui->playWidget1_->setHiddenCtrl(ui->playWidget1_->isPlaying() ? 1 : 0);
					ui->playWidget2_->setHiddenCtrl(ui->playWidget2_->isPlaying() ? 1 : 0);
					ui->playWidget4_->setHiddenCtrl(ui->playWidget4_->isPlaying() ? 1 : 0);
					singleMode_ = false;
					is_full_screenm_ = false;

					emit PVMSEventManagerManagerIns.sigOnSetFullScreen(true);
				}
				QTimer::singleShot(20, this, SLOT(slotOnUpdate()));
				initModeBtn();
				return true;
			}
		}
		if (event->type() == QEvent::KeyPress){
			QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
			if (keyEvent->key() == Qt::Key_Escape){
				if (ui->playWidget3_->isFullScreen()){
					ui->playWidget3_->setWindowFlags(Qt::SubWindow);
					ui->playWidget3_->showNormal();
				}
				if (fourFullScreen_)
				{
					if (ui->gidWidget->isFullScreen()){
						ui->gidWidget->setWindowFlags(Qt::SubWindow);
						ui->gidWidget->showNormal();
						fourFullScreen_ = false;
					}
				}
			}
			return true;
		}
	}
	else if (watched == ui->playWidget4_)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			ui->playWidget1_->setTopWgtVisable(false);
			ui->playWidget2_->setTopWgtVisable(false);
			ui->playWidget3_->setTopWgtVisable(false);
			ui->playWidget4_->setTopWgtVisable(true);
			ui->singleBtn_->setEnabled(true);
			current_select_GLWindow_ = GL4;
			return true;
		}
		if (event->type() == QEvent::MouseButtonDblClick)
		{
			if (!fourFullScreen_)
			{
				if (!is_full_screenm_)
				{
					ui->playWidget1_->hide();
					ui->playWidget3_->hide();
					ui->playWidget2_->hide();
					ui->playWidget1_->OnSwitchPlatFlagSlot(false);
					ui->playWidget2_->OnSwitchPlatFlagSlot(false);
					ui->playWidget3_->OnSwitchPlatFlagSlot(false);
					ui->playWidget1_->setHiddenCtrl(false);
					ui->playWidget2_->setHiddenCtrl(false);
					ui->playWidget3_->setHiddenCtrl(false);
					singleMode_ = true;
					is_full_screenm_ = true;

					emit PVMSEventManagerManagerIns.sigOnSetFullScreen(false);
				}
				else
				{
					ui->playWidget1_->show();
					ui->playWidget2_->show();
					ui->playWidget3_->show();
					ui->playWidget4_->show();
					ui->playWidget1_->OnSwitchPlatFlagSlot(ui->playWidget1_->isPlaying() ? 1 : 0);
					ui->playWidget2_->OnSwitchPlatFlagSlot(ui->playWidget2_->isPlaying() ? 1 : 0);
					ui->playWidget3_->OnSwitchPlatFlagSlot(ui->playWidget3_->isPlaying() ? 1 : 0);
					ui->playWidget1_->setHiddenCtrl(ui->playWidget1_->isPlaying() ? 1 : 0);
					ui->playWidget2_->setHiddenCtrl(ui->playWidget2_->isPlaying() ? 1 : 0);
					ui->playWidget3_->setHiddenCtrl(ui->playWidget3_->isPlaying() ? 1 : 0);
					singleMode_ = false;
					is_full_screenm_ = false;

					emit PVMSEventManagerManagerIns.sigOnSetFullScreen(true);
				}
				QTimer::singleShot(20, this, SLOT(slotOnUpdate()));
				initModeBtn();
				return true;
			}
		}
		if (event->type() == QEvent::KeyPress){
			QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
			if (keyEvent->key() == Qt::Key_Escape){
				if (ui->playWidget4_->isFullScreen()){
					ui->playWidget4_->setWindowFlags(Qt::SubWindow);
					ui->playWidget4_->showNormal();
				}
				if (fourFullScreen_)
				{
					if (ui->gidWidget->isFullScreen()){
						ui->gidWidget->setWindowFlags(Qt::SubWindow);
						ui->gidWidget->showNormal();
						fourFullScreen_ = false;
					}
				}
			}
			return true;
		}
	}
	else if (watched == ui->gidWidget)
	{
		if (event->type() == QEvent::KeyPress){
			QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
			if (keyEvent->key() == Qt::Key_Escape){
				if (ui->gidWidget->isFullScreen()){
					ui->gidWidget->setWindowFlags(Qt::SubWindow);
					ui->gidWidget->showNormal();
					fourFullScreen_ = false;
					QTimer::singleShot(20, this, SLOT(slotOnUpdate()));
					return true;
				}
			}
		}
		if (event->type() == QEvent::MouseButtonPress)
		{
			ui->playWidget1_->setTopWgtVisable(false);
			ui->playWidget2_->setTopWgtVisable(false);
			ui->playWidget3_->setTopWgtVisable(false);
			ui->playWidget4_->setTopWgtVisable(false);
			if (!singleMode_)
			{
				current_select_GLWindow_ = GL0;
			}
			return true;
		}
	}
	else if (watched == ui->bottomWidget_)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			ui->playWidget1_->setTopWgtVisable(false);
			ui->playWidget2_->setTopWgtVisable(false);
			ui->playWidget3_->setTopWgtVisable(false);
			ui->playWidget4_->setTopWgtVisable(false);
			if (!singleMode_)
			{
				current_select_GLWindow_ = GL0;
			}
			return true;
		}
	}
	return QWidget::eventFilter(watched, event);
}

void playWidget::init()
{
	QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
	ui->bottomWidget_->setGraphicsEffect(opacityEffect);
	opacityEffect->setOpacity(0.7);

	ui->bottomWidget_->installEventFilter(this);
	ui->gidWidget->installEventFilter(this);
	ui->gidWidget->setAttribute(Qt::WA_TranslucentBackground);

	windowMap_.insert(1, ui->playWidget1_);
	windowMap_.insert(2, ui->playWidget2_);
	windowMap_.insert(3, ui->playWidget3_);
	windowMap_.insert(4, ui->playWidget4_);

	QMap<int, playModeWgt*>::const_iterator i = windowMap_.constBegin();
	int index = 1;
	while (i != windowMap_.constEnd())
	{
		windowMap_[index]->SetPlayWindowNum(index);
		windowMap_[index]->installEventFilter(this);
		windowMap_[index]->initWindow(PREVIEW);
		++index;
		++i;
	}

	for (int i = 0; i < GLWINDOW_NUM; ++i)
	{
		oriTimeList_.append(0);
	}

	ui->singleBtn_->setEnabled(false);
	ui->treeWidget_->setRootIsDecorated(false);
	ui->treeWidget_->setFrameStyle(QFrame::NoFrame);
	ui->treeWidget_->setFocusPolicy(Qt::NoFocus);

	initModeBtn();
}

void playWidget::initConnect()
{
	qRegisterMetaType<PanoViewMode >("PanoViewMode");
	QMap<int, playModeWgt*>::const_iterator i = windowMap_.constBegin();
	int index = 1;
	while (i != windowMap_.constEnd()) {
		connect(this, SIGNAL(sigOnSwitchPlayFlag(bool)), windowMap_[index], SLOT(OnSwitchPlatFlagSlot(bool)));
		connect(windowMap_[index], SIGNAL(sigOnResetStatus(int)), this, SLOT(slotOnResetStatus(int)));
		connect(windowMap_[index], SIGNAL(sigOnBindPTZWarning()), this, SIGNAL(sigOnBindPTZWarning()));
		connect(windowMap_[index], SIGNAL(sigOnOptMizeSuccess()), this, SIGNAL(sigOnOptMizeSuccess()));
		connect(windowMap_[index], SIGNAL(sigOnBallCamBtnClicked(bool)), this, SLOT(slotOnSwitchBallCam(bool)));
		connect(windowMap_[index], SIGNAL(sigOnGetRecordTime(int)), this, SLOT(slotOnGetRecordTime(int)));
		connect(this, SIGNAL(sigOnSwitchViewMode(PanoViewMode)), windowMap_[index], SLOT(slotOnSwitchViewMode(PanoViewMode)));
		++index;
		++i;
	}

	connect(ui->treeWidget_, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(onListItemDoubleClickedSlot(QTreeWidgetItem*, int)));
	connect(ui->singleBtn_, SIGNAL(clicked()), this, SLOT(slotOnSingleModeSelected()));
	connect(ui->fourBtn_, SIGNAL(clicked()), this, SLOT(slotOnFourModeSelected()));
	connect(ui->originBtn_, SIGNAL(clicked()), this, SLOT(slotOnOriginModeSelected()));
	connect(ui->defaultBtn_, SIGNAL(clicked()), this, SLOT(slotOnPanoModeSelected()));

	ui->fullscreemBtn_->setVisible(false);
	connect(ui->fullscreemBtn_, SIGNAL(clicked()), this, SLOT(slot_fullOfScreenMode()));

	connect(ViewSignal::instance(), SIGNAL(sigOnCloseSubStreamClearPlayer(int)), this, SLOT(slotOnCloseSubStreamClearPlayer(int)));
	connect(ViewSignal::instance(), SIGNAL(sigOnRebootM1ResetPlayer(int)), this, SLOT(slotOnRebootM1ResetPlayer(int)));

	qRegisterMetaType<api_detu_client_av_param_t>("api_detu_client_av_param_t");
	connect(&TcpDataManagerIns, SIGNAL(playRequestSucceed()), this, SLOT(slotOnPlayRequestSucceed()));
	connect(&TcpDataManagerIns, SIGNAL(sigOnGetBitRate(unsigned char, api_detu_client_av_param_t*)), this, SLOT(slotOnGetBitRate(unsigned char, api_detu_client_av_param_t*)));
	
	connect(&PVMSEventManagerManagerIns, SIGNAL(sigOnSetFullScreen(bool)), this, SLOT(slotOnSetFullScreen(bool)), Qt::AutoConnection);
}

void playWidget::initModeBtn()
{
	if (singleMode_){
		ui->singleBtn_->setStyleSheet("#singleBtn_{border-image:url(:/image/image/singlechannelb.png);}");
		ui->fourBtn_->setStyleSheet("#fourBtn_{border-image:url(:/image/image/4channel.png);}#fourBtn_:hover{border-image:url(:/image/image/4channelc.png);}");
	}
	else
	{
		ui->singleBtn_->setStyleSheet("#singleBtn_{border-image:url(:/image/image/singlechannel.png);}#singleBtn_:hover{border-image:url(:/image/image/singlechannelc.png);}");
		ui->fourBtn_->setStyleSheet("#fourBtn_{border-image:url(:/image/image/4channelb.png);}");
	}
	if (currentPlayMode_ == PanoViewMode::PanoViewMode_FLAT){
		ui->originBtn_->setStyleSheet("#originBtn_{border-image:url(:/image/image/standardpanob.png);}");
		ui->defaultBtn_->setStyleSheet("#defaultBtn_{border-image:url(:/image/image/360.png);}#defaultBtn_:hover{border-image:url(:/image/image/360c.png);}");
	}
	else
	{
		ui->originBtn_->setStyleSheet("#originBtn_{border-image:url(:/image/image/standardpano.png);}#originBtn_:hover{border-image:url(:/image/image/standardpanoc.png);}");
		ui->defaultBtn_->setStyleSheet("#defaultBtn_{border-image:url(:/image/image/360b.png);}");
	}
}

void playWidget::initSingleFunction()
{
	if (current_select_GLWindow_ > GL0 && current_select_GLWindow_ <= GL4)
	{
		if (singleMode_){
			QMap<int, playModeWgt*>::const_iterator i = windowMap_.constBegin();
			int index = 1;
			while (i != windowMap_.constEnd()) {
				if (index != current_select_GLWindow_)
				{
					windowMap_[index]->setVisible(false);
					windowMap_[index]->setGLWindowMax(false);
					windowMap_[index]->setHiddenCtrl(false);
				}
				else
				{
					windowMap_[index]->setGLWindowMax(true);
				}
				++index;
				++i;
			}
		}
		else
		{
			QMap<int, playModeWgt*>::const_iterator i = windowMap_.constBegin();
			int index = 1;
			while (i != windowMap_.constEnd()) {
				windowMap_[index]->setVisible(true);
				windowMap_[index]->setGLWindowMax(true);
				bool ret = windowMap_[index]->isPlaying();
				windowMap_[index]->setHiddenCtrl(windowMap_[index]->isPlaying() ? 1 : 0);
				++index;
				++i;
			}
		}
	}
}

void playWidget::GenerateUI()
{
	ui->treeWidget_->clear();
	itemList_.clear();
	int count = InfoList_.length();
	for (int i = 0; i < count; i++)
	{
		InfoList_[i].id = i + 1;
		deviceItemWidget *itemWidget = new deviceItemWidget;
		itemWidget->initData(InfoList_[i], 0);
		itemList_.append(itemWidget);

		QTreeWidgetItem *m_item = new QTreeWidgetItem;
		ui->treeWidget_->addTopLevelItem(m_item);
		ui->treeWidget_->setItemWidget(m_item, 0, itemWidget);
		m_item->setExpanded(InfoList_[i].bClicked);

		QTreeWidgetItem *child;
		//球机
		for (int j = 0; j < InfoList_[i].m_PtzInfoList.size(); ++j)
		{
			InfoList_[i].m_PtzInfoList[j].id = j;
			QString key = tr("ptz");
			key += QString::number(j);

			child = new QTreeWidgetItem();
			m_item->addChild(child);
			deviceChildItemWidget *childItem = new deviceChildItemWidget;
			childItem->setLabelText(key);
			if ((j + 1) == InfoList_[i].m_PtzInfoList.size())
			{
				childItem->setIsFinal(true);
			}
			ui->treeWidget_->setItemWidget(child, 0, childItem);
		}

		//枪机
		for (int k = 0; k < InfoList_[i].m_SpyInfoList.size(); ++k)
		{
			InfoList_[i].m_SpyInfoList[k].id = k;
			QString key = tr("spy");
			key += QString::number(k);

			child = new QTreeWidgetItem();
			m_item->addChild(child);
			deviceChildItemWidget *childItem = new deviceChildItemWidget;
			childItem->setLabelText(key);
			if ((k + 1) == InfoList_[i].m_SpyInfoList.size())
			{
				childItem->setIsFinal(true);
			}
			ui->treeWidget_->setItemWidget(child, 0, childItem);
		}
		//	ui->listView_->appendItem(InfoList_[i]);
	}

}

void playWidget::initDecodeStatus(bool single)
{
	if (current_select_GLWindow_ > GL0 && current_select_GLWindow_ <=GL4)
	{
		if (single)
		{
			QMap<int, playModeWgt*>::const_iterator i = windowMap_.constBegin();
			int index = 1;
			while (i != windowMap_.constEnd()) {
				if (index  != current_select_GLWindow_)
				{
					windowMap_[index]->OnSwitchPlatFlagSlot(false);
				}
				++index;
				++i;
			}
		}
		else		
		{
			QMap<int, playModeWgt*>::const_iterator i = windowMap_.constBegin();
			int index = 1;
			while (i != windowMap_.constEnd()) {
				if (index != current_select_GLWindow_)
				{
					windowMap_[index]->OnSwitchPlatFlagSlot(windowMap_[index]->isPlaying() ? 1 : 0);
				}
				++index;
				++i;
			}
		}
		QMap<int, playModeWgt*>::const_iterator i = windowMap_.constBegin();
		int index = 1;
		while (i != windowMap_.constEnd()) {
			if (index != current_select_GLWindow_)
			{
				windowMap_[index]->setHiddenCtrl(false);
			}
			++index;
			++i;
		}
	}
}
void playWidget::onListItemDoubleClickedSlot(QTreeWidgetItem* itemWidget, int column)
{
	deviceItemWidget *m_itemWidget = qobject_cast<deviceItemWidget*>(ui->treeWidget_->itemWidget(itemWidget, column));
	int index = -1;
	if (m_itemWidget)
	{
		for (int i = 0; i < itemList_.size(); ++i)
		{
			if (m_itemWidget == itemList_[i])
			{
				index = i;
				InitData(InfoList_);
				break;
			}
		}
		if (index != -1)
		{
			if (!InfoList_[index].status)
			{
				Log::Info("device is offline, do not to open!");
				Feedback::instance()->maskUI(DEVICE_OFFLINE);
				return;
			}
		}
		//保存当前点击的item信息
		current_select_item_info_ = InfoList_[index];
		Log::Info("playWidget::onListItemDoubleClickedSlot: current select deviceId : %s", InfoList_[index].serialNo.toLocal8Bit().data());

		/*
		1、如果没被点击，请求播放；
		2、如果已经被点击，判断是否正在初始化；
		*/
		if (!current_select_item_info_.bClicked)
		{
			for (int i = 0; i < InfoList_.length(); i++)
			{
				if (InfoList_[i].id == current_select_item_info_.id)
				{
					InfoList_[i].bClicked = !InfoList_[i].bClicked;
				}
			}
			InitData(InfoList_);
			//设置当前点击的播放窗口
			current_select_playmodewgt_ = SetPlayModelWgt();
			current_select_playmodewgt_->setIsPlaying(true);
			current_select_playmodewgt_->setPlayConfig(current_select_item_info_);
			current_select_playmodewgt_->CreatStitchFiles(PREVIEW, 0);
		}
		else
		{
			InitData(InfoList_);
			//获取当前列表设置的播放出口
			current_select_playmodewgt_ = GetPlayModelWgt(current_select_item_info_.id);
			/*
			3、如果不在初始化已经播放，关闭；
			4、如果正在初始化, 什么都不做；
			*/
			if (current_select_playmodewgt_->isStitchFileOk())
			{
				//刷新列表状态
				for (int i = 0; i < InfoList_.length(); i++){
					if (InfoList_[i].id == current_select_item_info_.id){
						InfoList_[i].bClicked = !InfoList_[i].bClicked;
					}
				}
				//关闭播放
				current_select_playmodewgt_->close();
			}
			else
			{
				//直接跳出
				return;
			}
		}
		emit sigOnTransportList(InfoList_);
	}
}

