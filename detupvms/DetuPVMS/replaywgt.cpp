#include "replaywgt.h"
#include "commonFun.h"
#include <QDebug>
#include <QMessageBox>

#include "HttpSignal.h"
#include "HttpClient.h"

//全局控制器
#include "MessageManager.h"
#include "SocketManager.h"
#include "TcpDataManager.hpp"
#include "ListAndGLWindowManager.h"
#include "PVMSEventManager.h"

#include "Preview/deviceChildItemWidget.h"

#include "logging.hpp"
#include "DetuPVMSIni.h"
#include "feedback.h"
#include "ViewSignal.h"

using namespace dm::server;

replayWgt::replayWgt(QWidget *parent)
: QWidget(parent)
, ui(new Ui::replayWgt)
, replay_is_four_channel_playing_(false)
, isShowCalendar_(false)
, isPlay_(false)
, isPause_(false)
, singleMode_(false)
, replay_is_full_screenm_(false)
, m_online(false)
, fourFullScreen_(false)
, m_load_state_(false)
, calendar_(NULL)
, updateTimer_(NULL)
, nPosX_(-1)
, nPosY_(-1)
, oriTime_(0)
, m_selectId_(-1)
, request_time(0)
, srs_http_no_response(0)
, current_request_time_(-1)
, current_duration_(-1)
, speed_(PLAY_FOR_NORMAL)
, replay_net_no_response_(true)
, replay_server_no_response_(true)
,currentPlayMode_(PanoViewMode::PanoViewMode_FLAT)
{
	ui->setupUi(this);
	init();
	initConnect();
}

replayWgt::~replayWgt()
{
	if (calendar_ != NULL)
	{
		calendar_->deleteLater();
		calendar_ = NULL;
	}
	if (updateTimer_ != NULL)
	{
		updateTimer_->deleteLater();
		updateTimer_ = NULL;
	}
}

void replayWgt::RePlayUpdateListSlot(QList<deviceInfo> deviceList)
{
	InfoList_ = deviceList;
	initData(InfoList_);
}

void replayWgt::setSpeedPos(int w)
{
	ui->prograssBarWgt->setSpeedPos(w);
}

void replayWgt::clearPlayerStatus()
{
	restoreUi();
	//关闭实时定时器
	if (updateTimer_ != NULL && updateTimer_->isActive())
	{
		updateTimer_->stop();
		Log::Debug("replay request timer stop!");
	}
}

void replayWgt::setPosMove()
{
	ui->playWidget1_->setPosMove();
}

void replayWgt::setTimePos()
{
	ui->playWidget1_->setTimePos(1);
}

void replayWgt::setHiddenTime(bool visible)
{
	if (!visible)
	{
		ui->playWidget1_->setGLWindowMax(false);
		ui->playWidget1_->setHiddenTime(visible);
	}
	else
	{
		ui->playWidget1_->setGLWindowMax(true);
		ui->playWidget1_->setHiddenTime(ui->playWidget1_->isPlaying() ? 1 : 0);
	}
}

void replayWgt::closePlayer()
{
	if (ui->playWidget1_->isPlaying())
	{
		ui->playWidget1_->closePlayer();
	}
}

void replayWgt::setMoveEnabled(bool enable)
{
	ui->prograssBarWgt->setMoveEnabled(enable);
}

void replayWgt::setReplayStatusShowLabel(PLAY_STATUS play_status)
{
	if (!ui->playWidget1_->isPlaying())
	{
		ui->playWidget1_->onSetGlLabelSlot(play_status);
	}
	else if (!ui->playWidget2_->isPlaying())
	{
		ui->playWidget2_->onSetGlLabelSlot(play_status);
	}
	else if (!ui->playWidget3_->isPlaying())
	{
		ui->playWidget3_->onSetGlLabelSlot(play_status);
	}
	else if (!ui->playWidget4_->isPlaying())
	{
		ui->playWidget4_->onSetGlLabelSlot(play_status);
	}
}

void replayWgt::RePlayRecordTimeSlot()
{
	query_list_.clear();
    query_list_ = TcpDataManagerIns.GetRecordTime();
	replay_server_no_response_ = false;
    m_replayInfoList *info_ = NULL;
    info_ = new m_replayInfoList;
	if (query_list_.size() > 0){
		m_load_state_ = true;
		for (std::vector<api_record_query_respond>::iterator iter = query_list_.begin(); iter != query_list_.end(); iter++)
		{
			m_replayInfo *info = NULL;
			info = new m_replayInfo;
			info->id = iter->nCurRecordSegmentNum;
			//时区转换，减8个小时
			info->startTime = iter->nStartTime - 28800;
			info->endTime = iter->nEndTime - 28800;
			info_->m_infoList.append(*info);
		}
		info_->id = 1;
		info_->duration = ui->prograssBarWgt->getDurationBySlider();
		m_replay_infoList_.clear();
		m_replay_infoList_.append(*info_);
     	ui->prograssBarWgt->initData(m_replay_infoList_);

		//请求回放时间域成功，启动定时器实时获取
		if (updateTimer_ == NULL)
		{
			updateTimer_ = new QTimer;
			updateTimer_->setInterval(60000);
			connect(updateTimer_, SIGNAL(timeout()), this, SLOT(slotOnRequestReplayTimer()));
		}
		if (!updateTimer_->isActive())
		{
			updateTimer_->start();
			Log::Debug("replay request timer start!");
		}
	}
	else{
		m_load_state_ = false;
		Feedback::instance()->maskUI(REPLAY_REQUEST_FAILED);
		InfoList_[replay_current_select_item_info_.id - 1].RbClicked = !InfoList_[replay_current_select_item_info_.id - 1].RbClicked;
		initData(InfoList_);
		sigOnTransportList(InfoList_);
		restoreUi();
	}
	Log::Debug("Get %d time staff", info_->m_infoList.length());
}

void replayWgt::QueryForVideo()
{
	protocol_head_t api_head;
	api_detu_client_record_query api_detu;
	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_CLIENT_RECORD_QUERY;
	api_head.nDataLen = api_detu.get_size();
	api_head.nResult = 0x00;
	api_head.nStreamId = DetuPVMSIni::getReplayRtmpUrl().toInt();			//获取主码流或者子码流，通过配置文件
	//api_head.nReserver = 0x01;        //预留位
	api_head.nEndFlags = 0xFA;

	memcpy(api_detu.szDeviceId, replay_current_select_item_info_.serialNo.toLocal8Bit(), API_ARRAY_LEN);
	QString m_date = ui->dateWidget->getSelectedDate();
	Log::Debug("current requested replayDate is %s", m_date.toLocal8Bit().data());
	api_detu.nStartTime = commonFun::getStartTime(m_date) + 28800;
	api_detu.nEndTime = commonFun::getEndTime(m_date) + 28800;

	response res(api_head.get_size() + api_detu.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
	response_add_resprotocol<api_detu_client_record_query>(res, &api_detu);

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

void replayWgt::slot_singleModeSelected()
{
	if (singleMode_)
	{
		return;
	}
	singleMode_ = true;
	initModeBtn();
	initSingleFunction();
}

void replayWgt::slot_fourModeSelected()
{
	if (!singleMode_)
	{
		return;
	}
	singleMode_ = false;
	initModeBtn();
	initSingleFunction();
}

void replayWgt::slot_openOneBallCam()
{

}

void replayWgt::slot_closeOneBallCam()
{

}

void replayWgt::slot_originModeSelected()
{
	if (currentPlayMode_ == PanoViewMode::PanoViewMode_FLAT)
	{
		return;
	}
	currentPlayMode_ = PanoViewMode::PanoViewMode_FLAT;
	initModeBtn();
	ui->playWidget1_->slotOnSwitchViewMode(PanoViewMode::PanoViewMode_FLAT);
	emit sigOnReplaySwitchViewMode(PanoViewMode::PanoViewMode_FLAT);
}

void replayWgt::slot_360ModeSelected()
{
	if (currentPlayMode_ == PanoViewMode::PanoViewMode_DEFAULT)
	{
		return;
	}
	currentPlayMode_ = PanoViewMode::PanoViewMode_DEFAULT;
	initModeBtn();
	ui->playWidget1_->slotOnSwitchViewMode(PanoViewMode::PanoViewMode_DEFAULT);
	emit sigOnReplaySwitchViewMode(PanoViewMode::PanoViewMode_DEFAULT);
}

void replayWgt::slot_fullOfScreen()
{
	initFullofScreen();
}

void replayWgt::initFullofScreen()
{
	switch (replay_current_select_GLWindow_)
	{
	case replayWgt::RePlayGL1:
		ui->playWidget1_->setWindowFlags(Qt::Window);
		ui->playWidget1_->showFullScreen();
		ui->playWidget1_->setTimePos(1);
		break;
	case replayWgt::RePlayGL2:
		ui->playWidget2_->setWindowFlags(Qt::Window);
		ui->playWidget2_->showFullScreen();
		break;
	case replayWgt::RePlayGL3:
		ui->playWidget3_->setWindowFlags(Qt::Window);
		ui->playWidget3_->showFullScreen();
		break;
	case replayWgt::RePlayGL4:
		ui->playWidget4_->setWindowFlags(Qt::Window);
		ui->playWidget4_->showFullScreen();
		break;
	default:
		ui->gidWidget->setWindowFlags(Qt::Window);
		ui->gidWidget->showFullScreen();
		ui->playWidget1_->setTimePos(1);
		fourFullScreen_ = true;
		break;
	}
}

void replayWgt::slotOnRequestReplayRadio(int time, int duration)
{
	current_request_time_ = time;
	current_duration_ = duration;

	replay_request_url_ = TcpDataManagerIns.GetRequestTime();
	RePlayDoubleClickToPlayStatusCommunication();
}

void replayWgt::slotOnGetRecordTime(int time)
{
	setMoveEnabled(true);
	request_time = time;
	time -= 28800;
	QString time_ = QDateTime::fromTime_t(time).toString("yyyy-MM-dd hh:mm:ss");
	if (time > oriTime_){
		//Log::Debug("time : %d-------oriTime : %d", time, oriTime);
		ui->prograssBarWgt->setRecoderPos(time);
		ui->playWidget1_->setShowTime(time_, 1);
	}
	oriTime_ = time;
}

void replayWgt::slotOnShowCalendar()
{
	if (m_load_state_)
	{
		QMessageBox::warning(this, tr("tips"), tr("please close reuqest at first , then open this !"));
		return;
	}
	isShowCalendar_ = !isShowCalendar_;
	showCalendar();
}

void replayWgt::slotOnResetStatus(int item_num)
{
	m_load_state_ = false;
	setMoveEnabled(true);
	m_replay_infoList_.clear();
    ui->prograssBarWgt->initData(m_replay_infoList_);
	ui->prograssBarWgt->resetRadition();
	ui->playWidget1_->closeShowTime();
	if (replay_current_select_item_info_.id != -1)
	{
		InfoList_[replay_current_select_item_info_.id - 1].RbClicked = false;
		initData(InfoList_);
		emit sigOnTransportList(InfoList_);
	}
	isPlay_ = false;
	speed_ = PLAY_FOR_NORMAL;
	ui->speedWidget->setSpeedLabel("1x");
	ui->speedWidget->setFastBtnEnable(true);
	ui->speedWidget->setSlowBtnEnable(true);
	ui->pauseBtn_->setStyleSheet("#pauseBtn_{border-image:url(:/image/image/play.png);}#pauseBtn_:hover{border-image:url(:/image/image/playb.png);}#pauseBtn_:pressed{margin:1px;}");
}

void replayWgt::slotOnPlayStatus()
{
	isPlay_ = true;
	ui->pauseBtn_->setStyleSheet("#pauseBtn_{border-image:url(:/image/image/pause.png);}#pauseBtn_:hover{border-image:url(:/image/image/pauseb.png);}#pauseBtn_:pressed{margin:1px;}");
	ui->playWidget1_->onShowGlWindowSlot();
}

void replayWgt::slotOnFastPlay()
{
	if (speed_ < PLAY_FOR_DOUBLE)
	{
		speed_ ++;
		playControlRequest(isPlay_, speed_);
		ui->speedWidget->setSpeedLabel(changeSpeedLabel(speed_));
		if (speed_ == PLAY_FOR_DOUBLE)
		{
			ui->speedWidget->setFastBtnEnable(false);
		}
		else
		{
			ui->speedWidget->setFastBtnEnable(true);
		}
		if (speed_ == PLAY_FOR_REDUCE_QUADRUPLE)
		{
			ui->speedWidget->setSlowBtnEnable(false);
		}
		else
		{
			ui->speedWidget->setSlowBtnEnable(true);
		}
	}
}

void replayWgt::slotOnSlowPlay()
{
	if (speed_ > PLAY_FOR_REDUCE_QUADRUPLE)
	{
		speed_--;
		playControlRequest(isPlay_, speed_);
		ui->speedWidget->setSpeedLabel(changeSpeedLabel(speed_));
		if (speed_ == PLAY_FOR_REDUCE_QUADRUPLE)
		{
			ui->speedWidget->setSlowBtnEnable(false);
		}
		else
		{
			ui->speedWidget->setSlowBtnEnable(true);
		}
		if (speed_ == PLAY_FOR_DOUBLE)
		{
			ui->speedWidget->setFastBtnEnable(false);
		}
		else
		{
			ui->speedWidget->setFastBtnEnable(true);
		}
	}
}

void replayWgt::slotOnGetPlaybackRes(bool is_ok)
{
	if (is_ok)
	{
		Log::Debug("playback control is ok!");
	}
	else
	{
		Log::Debug("playback control failed!");
	}
}

void replayWgt::slotOnRecordRequestFailed()
{
	Feedback::instance()->maskUI(PLAY_REQUEST_FAILED);
}

void replayWgt::slotOnCloseSubStreamClearPlayer(int id)
{
	if (ui->playWidget1_->isPlaying())
	{
		ui->playWidget1_->clearPlay();
	}
}

void replayWgt::slotOnRebootM1ResetPlayer(int id)
{
	if (ui->playWidget1_->isPlaying())
	{
		ui->playWidget1_->close();
	}
}

void replayWgt::slotOnRePlaywgtSelected(int index)
{
 	//默认回放index是3
	if (index == 3)
	{
		emit sigOnSwitchRePlayFlag(true);
	}
	else
	{
		emit sigOnSwitchRePlayFlag(false);
	}
}

void replayWgt::slotOnReplayResetSlider()
{
	setMoveEnabled(true);
}

void replayWgt::slotOnTimeEditFinished(QString request_time)
{
	if (query_list_.size() > 0)
	{
		int time = commonFun::timeExchange(request_time, 6);
		slotOnRequestReplayRadio(time, 6);
	}
}

void replayWgt::slotOnReplayOnSwitchViewMode(PanoViewMode view_mode)
{

}

void replayWgt::RePlaySetIsFourChannelPlaying()
{
	if (ui->playWidget1_->isPlaying() && ui->playWidget2_->isPlaying() && ui->playWidget3_->isPlaying() && ui->playWidget4_->isPlaying())
		replay_is_four_channel_playing_ = true;
	else
		replay_is_four_channel_playing_ = false;
}

void replayWgt::RePlayAskForVideo()
{
	protocol_head_t api_head;
	api_detu_client_request_video_t api_detu;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_CLIENT_REQUEST_VIDEO;
	api_head.nDataLen = api_detu.get_size();
	api_head.nResult = 0x00;
	api_head.nStreamId = DetuPVMSIni::getReplayRtmpUrl().toInt();
	//api_head.nReserver = 0x01;        //预留位
	api_head.nEndFlags = 0xFA;

	memcpy(api_detu.szDeviceId, replay_current_select_item_info_.serialNo.toLocal8Bit(), API_ARRAY_LEN);
	QString date = ui->dateWidget->getSelectedDate();
	if (!isPause_)
	{
		request_time = commonFun::getDateTime(curr_time_, date, curr_duration_) + 28800;
	}
	api_detu.nStartTime = request_time;
	api_detu.nEndTime = 0;
	Log::Debug("replay requested: cmd:%d steamid:%d requestTime:%s", api_head.nCmd, api_head.nStreamId, QDateTime::fromTime_t(api_detu.nStartTime).toString("hh:mm:ss").toLocal8Bit().data());

	response res(api_head.get_size() + api_detu.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
	response_add_resprotocol<api_detu_client_request_video_t>(res, &api_detu);

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}


bool replayWgt::eventFilter(QObject *watched, QEvent *event)
{
	if (watched == ui->playWidget1_)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			ui->playWidget1_->setTopWgtVisable(true);
			ui->playWidget2_->setTopWgtVisable(false);
			ui->playWidget3_->setTopWgtVisable(false);
			ui->playWidget4_->setTopWgtVisable(false);
			ui->singleBtn->setEnabled(true);
			replay_current_select_GLWindow_ = RePlayGL1;
		}
		if (event->type() == QEvent::MouseButtonDblClick)
		{
			if (!replay_is_full_screenm_)
			{
				ui->playWidget2_->setVisible(false);
				ui->playWidget3_->setVisible(false);
				ui->playWidget4_->setVisible(false);
				singleMode_ = true;
				replay_is_full_screenm_ = true;

				emit PVMSEventManagerManagerIns.sigOnReplaySetFullScreen(true);
			}
			else
			{
				ui->playWidget1_->setVisible(true);
				ui->playWidget2_->setVisible(true);
				ui->playWidget3_->setVisible(true);
				ui->playWidget4_->setVisible(true);
				singleMode_ = false;
				replay_is_full_screenm_ = false;

				emit PVMSEventManagerManagerIns.sigOnReplaySetFullScreen(false);
			}
			initModeBtn();
		}
		if (event->type() == QEvent::KeyPress){
			QKeyEvent *keyevent = static_cast<QKeyEvent*>(event);
			if (keyevent->key() == Qt::Key_Escape){
				if (ui->playWidget1_->isFullScreen()){
					ui->playWidget1_->setWindowFlags(Qt::SubWindow);
					ui->playWidget1_->showNormal();
					ui->playWidget1_->setTimePos(1);
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
			ui->singleBtn->setEnabled(true);
			replay_current_select_GLWindow_ = RePlayGL2;
		}
		if (event->type() == QEvent::MouseButtonDblClick)
		{
			if (!replay_is_full_screenm_)
			{
				ui->playWidget1_->setVisible(false);
				ui->playWidget3_->setVisible(false);
				ui->playWidget4_->setVisible(false);
				singleMode_ = true;
				replay_is_full_screenm_ = true;
			}
			else
			{
				ui->playWidget1_->setVisible(true);
				ui->playWidget2_->setVisible(true);
				ui->playWidget3_->setVisible(true);
				ui->playWidget4_->setVisible(true);
				singleMode_ = false;
				replay_is_full_screenm_ = false;
			}
			initModeBtn();
		}
		if (event->type() == QEvent::KeyPress){
			QKeyEvent *keyevent = static_cast<QKeyEvent*>(event);
			if (keyevent->key() == Qt::Key_Escape){
				if (ui->playWidget2_->isFullScreen()){
					ui->playWidget2_->setWindowFlags(Qt::SubWindow);
					ui->playWidget2_->showNormal();
				}
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
			ui->singleBtn->setEnabled(true);
			replay_current_select_GLWindow_ = RePlayGL3;
		}
		if (event->type() == QEvent::MouseButtonDblClick)
		{
			if (!replay_is_full_screenm_)
			{
				ui->playWidget2_->setVisible(false);
				ui->playWidget1_->setVisible(false);
				ui->playWidget4_->setVisible(false);
				singleMode_ = true;
				replay_is_full_screenm_ = true;
			}
			else
			{
				ui->playWidget1_->setVisible(true);
				ui->playWidget2_->setVisible(true);
				ui->playWidget3_->setVisible(true);
				ui->playWidget4_->setVisible(true);
				singleMode_ = false;
				replay_is_full_screenm_ = false;
			}
			initModeBtn();
		}
		if (event->type() == QEvent::KeyPress){
			QKeyEvent *keyevent = static_cast<QKeyEvent*>(event);
			if (keyevent->key() == Qt::Key_Escape){
				if (ui->playWidget3_->isFullScreen()){
					ui->playWidget3_->setWindowFlags(Qt::SubWindow);
					ui->playWidget3_->showNormal();
				}
			}
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
			ui->singleBtn->setEnabled(true);
			replay_current_select_GLWindow_ = RePlayGL4;
		}
		if (event->type() == QEvent::MouseButtonDblClick)
		{
			if (!replay_is_full_screenm_)
			{
				ui->playWidget2_->setVisible(false);
				ui->playWidget3_->setVisible(false);
				ui->playWidget1_->setVisible(false);
				singleMode_ = true;
				replay_is_full_screenm_ = true;
			}
			else
			{
				ui->playWidget1_->setVisible(true);
				ui->playWidget2_->setVisible(true);
				ui->playWidget3_->setVisible(true);
				ui->playWidget4_->setVisible(true);
				singleMode_ = false;
				replay_is_full_screenm_ = false;
			}
			initModeBtn();
		}
		if (event->type() == QEvent::KeyPress){
			QKeyEvent *keyevent = static_cast<QKeyEvent*>(event);
			if (keyevent->key() == Qt::Key_Escape){
				if (ui->playWidget4_->isFullScreen()){
					ui->playWidget4_->setWindowFlags(Qt::SubWindow);
					ui->playWidget4_->showNormal();
				}
			}
		}
	}
	if (watched == ui->gidWidget){
		if (event->type() == QEvent::KeyPress){
			QKeyEvent *keyevent = static_cast<QKeyEvent*>(event);
			if (keyevent->key() == Qt::Key_Escape){
				if (ui->gidWidget->isFullScreen()){
					ui->gidWidget->setWindowFlags(Qt::SubWindow);
					ui->gidWidget->showNormal();
					ui->playWidget1_->setTimePos(1);
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
				replay_current_select_GLWindow_ = RePlayGL0;
			}
		}
	}
	return true;
}


void replayWgt::init()
{
	//ui->pauseBtn_->setHidden(1);

	ui->gidWidget->setAttribute(Qt::WA_TranslucentBackground);

	ui->playWidget1_->setBtnVisible(false);
	ui->playWidget2_->setBtnVisible(false);
	ui->playWidget3_->setBtnVisible(false);
	ui->playWidget4_->setBtnVisible(false);


	ui->playWidget1_->SetPlayWindowNum(1);
	ui->playWidget2_->SetPlayWindowNum(2);
	ui->playWidget3_->SetPlayWindowNum(3);
	ui->playWidget4_->SetPlayWindowNum(4);

	ui->playWidget1_->installEventFilter(this);
	ui->playWidget2_->installEventFilter(this);
	ui->playWidget3_->installEventFilter(this);
	ui->playWidget4_->installEventFilter(this);
	ui->gidWidget->installEventFilter(this);

	ui->playWidget1_->initWindow(REPLAY);
	ui->playWidget2_->initWindow(REPLAY);
	ui->playWidget3_->initWindow(REPLAY);
	ui->playWidget4_->initWindow(REPLAY);

	ui->playWidget2_->setVisible(false);
	ui->playWidget3_->setVisible(false);
	ui->playWidget4_->setVisible(false);

	//一期屏蔽原图模式与360模式
// 	ui->originBtn->setHidden(true);
// 	ui->defaultBtn->setHidden(true);
	ui->singleBtn->setEnabled(false);
	ui->fourBtn->setHidden(true);
	ui->singleBtn->setHidden(true);
	//初始化模式按钮
	initModeBtn();
	ui->dateWidget->initStyleSheet();
	ui->timeWidget->initStyleSheet();

	ui->treeWidget_->setRootIsDecorated(false);
	ui->treeWidget_->setFrameStyle(QFrame::NoFrame);
	ui->treeWidget_->setFocusPolicy(Qt::NoFocus);
}

void replayWgt::initConnect()
{
	connect(ui->playWidget1_, SIGNAL(sigOnReplayResetSlider()), this, SLOT(slotOnReplayResetSlider()));

	connect(this, SIGNAL(sigOnSwitchRePlayFlag(bool)), ui->playWidget1_, SLOT(OnSwitchPlatFlagSlot(bool)));
	connect(this, SIGNAL(sigOnSwitchRePlayFlag(bool)), ui->playWidget2_, SLOT(OnSwitchPlatFlagSlot(bool)));
	connect(this, SIGNAL(sigOnSwitchRePlayFlag(bool)), ui->playWidget3_, SLOT(OnSwitchPlatFlagSlot(bool)));
	connect(this, SIGNAL(sigOnSwitchRePlayFlag(bool)), ui->playWidget4_, SLOT(OnSwitchPlatFlagSlot(bool)));

	connect(ui->playWidget1_, SIGNAL(sigOnResetStatus(int)), this, SLOT(slotOnResetStatus(int)));
	connect(ui->playWidget2_, SIGNAL(sigOnResetStatus(int)), this, SLOT(slotOnResetStatus(int)));
	connect(ui->playWidget3_, SIGNAL(sigOnResetStatus(int)), this, SLOT(slotOnResetStatus(int)));
	connect(ui->playWidget4_, SIGNAL(sigOnResetStatus(int)), this, SLOT(slotOnResetStatus(int)));

	connect(ui->playWidget1_, SIGNAL(sigOnPlayStatus()), this, SLOT(slotOnPlayStatus()));

	connect(ui->singleBtn, SIGNAL(clicked()), this, SLOT(slot_singleModeSelected()));
	connect(ui->fourBtn, SIGNAL(clicked()), this, SLOT(slot_fourModeSelected()));
	connect(ui->originBtn, SIGNAL(clicked()), this, SLOT(slot_originModeSelected()));
	connect(ui->defaultBtn, SIGNAL(clicked()), this, SLOT(slot_360ModeSelected()));
	ui->fullscreemBtn->setVisible(false);
	connect(ui->fullscreemBtn, SIGNAL(clicked()), this, SLOT(slot_fullOfScreen()));

	connect(ui->pauseBtn_, SIGNAL(clicked()), this, SLOT(slot_pause_play()));
	connect(ui->prograssBarWgt, SIGNAL(sigOnRequestReplayRadio(int, int)), this, SLOT(slotOnRequestReplayRadio(int, int)));
	connect(ui->dateWidget, SIGNAL(sigOnShowCalendar()), this, SLOT(slotOnShowCalendar()));
	connect(ui->speedWidget, SIGNAL(sigOnFastPlay()), this, SLOT(slotOnFastPlay()));
	connect(ui->speedWidget, SIGNAL(sigOnSlowPlay()), this, SLOT(slotOnSlowPlay()));
	connect(ui->timeWidget, SIGNAL(sigOnEditFinished(QString)), this, SLOT(slotOnTimeEditFinished(QString)));

	connect(ViewSignal::instance(), SIGNAL(sigOnRebootM1ResetPlayer(int)), this, SLOT(slotOnRebootM1ResetPlayer(int)));
	connect(ViewSignal::instance(), SIGNAL(sigOnCloseSubStreamClearPlayer(int)), this, SLOT(slotOnCloseSubStreamClearPlayer(int)));
	connect(&TcpDataManagerIns, SIGNAL(RecordRequestFailed()), this, SLOT(slotOnRecordRequestFailed()));
	connect(&TcpDataManagerIns, SIGNAL(RecordTimeReceived()), this, SLOT(RePlayRecordTimeSlot()), Qt::QueuedConnection);
	connect(&TcpDataManagerIns, SIGNAL(ReplayRequestSucceed()), this, SLOT(slotOnReplayRequestSucceed()), Qt::QueuedConnection);
	connect(&TcpDataManagerIns, SIGNAL(sigOnGetPlaybackRes(bool)), this, SLOT(slotOnGetPlaybackRes(bool)));
	//
    connect(ui->playWidget1_, SIGNAL(sigOnGetRecordTime(int)), this, SLOT(slotOnGetRecordTime(int)));
	connect(ui->playWidget1_, SIGNAL(sigOnOptMizeSuccess()), this, SIGNAL(sigOnOptMizeSuccess()));
	connect(ui->treeWidget_, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(onListItemDoubleClickedSlot(QTreeWidgetItem*, int)));

	qRegisterMetaType<PanoViewMode >("PanoViewMode");
	connect(this, SIGNAL(sigOnReplaySwitchViewMode(PanoViewMode)), ui->playWidget1_, SLOT(slotOnSwitchViewMode(PanoViewMode)));
	
	connect(&PVMSEventManagerManagerIns, SIGNAL(sigOnReplaySetFullScreen(bool)), this, SLOT(slotOnReplaySetFullScreen(bool)), Qt::AutoConnection);
}

void replayWgt::showCalendar()
{
	//创建日历对象
	if (calendar_ == NULL){
		calendar_ = new calendarWidget;
		calendar_->activateWindow();
		connect(calendar_, SIGNAL(sigOnSetDate(QString)), this, SLOT(slot_setSelectedDate(QString)));
		QPoint pos = this->mapToGlobal(this->pos());
		QPoint pos_ = ui->dateWidget->pos();
		nPosX_ = pos.x() + pos_.x() + ui->leftWidget->width();
		nPosY_ = pos.y() + pos_.y() + ui->gidWidget->height() - 210;
	}
	if (isShowCalendar_){
		calendar_->move(nPosX_, nPosY_);
		calendar_->show();
	}
	else
	{
		calendar_->close();
	}
}

void replayWgt::initModeBtn()
{
	if (singleMode_){
		ui->singleBtn->setStyleSheet("#singleBtn{border-image:url(:/image/image/singlechannelb.png);}");
		ui->fourBtn->setStyleSheet("#fourBtn{border-image:url(:/image/image/4channel.png);}#fourBtn:hover{border-image:url(:/image/image/4channelc.png);}");
	}
	else
	{
		ui->singleBtn->setStyleSheet("#singleBtn{border-image:url(:/image/image/singlechannel.png);}#singleBtn:hover{border-image:url(:/image/image/singlechannelc.png);}");
		ui->fourBtn->setStyleSheet("#fourBtn{border-image:url(:/image/image/4channelb.png);}");
	}
	if (currentPlayMode_ == PanoViewMode::PanoViewMode_FLAT)
	{
 		ui->originBtn->setStyleSheet("#originBtn{border-image:url(:/image/image/standardpanob.png);}");
		ui->defaultBtn->setStyleSheet("#defaultBtn{border-image:url(:/image/image/360.png);}#defaultBtn:hover{border-image:url(:/image/image/360c.png);}");
	}
	else
	{
		ui->originBtn->setStyleSheet("#originBtn{border-image:url(:/image/image/standardpano.png);}#originBtn:hover{border-image:url(:/image/image/standardpanoc.png);}");
		ui->defaultBtn->setStyleSheet("#defaultBtn{border-image:url(:/image/image/360b.png);}");
	}
}

void replayWgt::initSingleFunction()
{
	switch (replay_current_select_GLWindow_)
	{
	case replayWgt::RePlayGL1:
		if (singleMode_){
			ui->playWidget2_->setVisible(false);
			ui->playWidget3_->setVisible(false);
			ui->playWidget4_->setVisible(false);
		}
		else
		{
			ui->playWidget1_->setVisible(true);
			ui->playWidget2_->setVisible(true);
			ui->playWidget3_->setVisible(true);
			ui->playWidget4_->setVisible(true);
		}
		break;
	case replayWgt::RePlayGL2:
		if (singleMode_){
			ui->playWidget1_->setVisible(false);
			ui->playWidget3_->setVisible(false);
			ui->playWidget4_->setVisible(false);
		}
		else
		{
			ui->playWidget1_->setVisible(true);
			ui->playWidget2_->setVisible(true);
			ui->playWidget3_->setVisible(true);
			ui->playWidget4_->setVisible(true);
		}
		break;
	case replayWgt::RePlayGL3:
		if (singleMode_){
			ui->playWidget2_->setVisible(false);
			ui->playWidget1_->setVisible(false);
			ui->playWidget4_->setVisible(false);
		}
		else
		{
			ui->playWidget1_->setVisible(true);
			ui->playWidget2_->setVisible(true);
			ui->playWidget3_->setVisible(true);
			ui->playWidget4_->setVisible(true);
		}
		break;
	case replayWgt::RePlayGL4:
		if (singleMode_){
			ui->playWidget2_->setVisible(false);
			ui->playWidget3_->setVisible(false);
			ui->playWidget1_->setVisible(false);
		}
		else
		{
			ui->playWidget1_->setVisible(true);
			ui->playWidget2_->setVisible(true);
			ui->playWidget3_->setVisible(true);
			ui->playWidget4_->setVisible(true);
		}
		break;
	default:
		break;
	}
}

void replayWgt::generateUI()
{
//	ui->listView_->clearItems();
	ui->treeWidget_->clear();
	itemWidgetList_.clear();
	int count = InfoList_.length();
	for (int i = 0; i < count; i++)
	{
		InfoList_[i].id = i + 1;
		deviceItemWidget *itemWidget = new deviceItemWidget;
		itemWidget->initData(InfoList_[i], 1);
		itemWidgetList_.append(itemWidget);

		QTreeWidgetItem *m_item = new QTreeWidgetItem;
		ui->treeWidget_->addTopLevelItem(m_item);
		ui->treeWidget_->setItemWidget(m_item, 0, itemWidget);
		m_item->setExpanded(InfoList_[i].RbClicked);

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

void replayWgt::playControlRequest(bool m_isPlay, int m_speed)
{
	if (!SocketManagerIns.isConnected()){
		return;
	}
	protocol_head_t api_head;
	api_detu_client_replay_control_t api_detu;
	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_CLIENT_PLAYBACK_CONTROL;
	api_head.nDataLen = api_detu.get_size();
	api_head.nResult = 0x00;
	api_head.nStreamId = DetuPVMSIni::getReplayRtmpUrl().toInt();
	//api_head.nReserver = 0x01;        //预留位
	api_head.nEndFlags = 0xFA;

	memcpy(api_detu.szDeviceId, replay_current_select_item_info_.serialNo.toLocal8Bit(), API_ARRAY_LEN);
	api_detu.nControlType = m_isPlay ? 1 : 2;
	api_detu.nSpeed = changeSpeed(m_speed);
	Log::Debug("play control request : controlType:%d, speed : %d, rtmpStreamId : %d", api_detu.nControlType, api_detu.nSpeed, api_head.nStreamId);
	response res(api_head.get_size() + api_detu.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
	response_add_resprotocol<api_detu_client_replay_control_t>(res, &api_detu);

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

int replayWgt::changeSpeed(int m_speed)
{
	int speed_;
	switch (m_speed)
	{
	case PLAY_FOR_REDUCE_QUADRUPLE:
		speed_ = 5;
		break;
	case PLAY_FOR_REDUCE_DOUBLE:
		speed_ = 3;
		break;
	case PLAY_FOR_NORMAL:
		speed_ = 1;
		break;
	case PLAY_FOR_DOUBLE:
		speed_ = 2;
		break;
// 	case PLAY_FOR_QUADRUPLE:
// 		speed_ = 4;
// 		break;
	default:
		break;
	}
	return speed_;
}

QString replayWgt::changeSpeedLabel(int m_speed)
{
	QString text;
	switch (m_speed)
	{
	case PLAY_FOR_REDUCE_QUADRUPLE:
		text = "1/4x";
		break;
	case PLAY_FOR_REDUCE_DOUBLE:
		text = "1/2x";
		break;
	case PLAY_FOR_NORMAL:
		text = "1x";
		break;
	case PLAY_FOR_DOUBLE:
		text = "2x";
		break;
// 	case PLAY_FOR_QUADRUPLE:
// 		text = "4x";
// 		break;
	default:
		break;
	}
	return text;
}

void replayWgt::restoreUi()
{
	query_list_.clear();
	m_replay_infoList_.clear();
	ui->prograssBarWgt->initData(m_replay_infoList_);
	ui->prograssBarWgt->resetRadition();
	if (isPause_)
	{
		pausePlayer(1, true);
	}
	else
	{
		closeReplaySourse(1);
	}
	isPlay_ = false;
	speed_ = PLAY_FOR_NORMAL;
	ui->speedWidget->setSpeedLabel("1x");
	ui->speedWidget->setFastBtnEnable(true);
	ui->speedWidget->setSlowBtnEnable(true);
	ui->pauseBtn_->setStyleSheet("#pauseBtn_{border-image:url(:/image/image/play.png);}#pauseBtn_:hover{border-image:url(:/image/image/playb.png);}#pauseBtn_:pressed{margin:1px;}");
}

playModeWgt * replayWgt::SetPlayModelWgt()
{
	//如果四个窗口没有同时播放，选择未播的窗口播放
	if (!replay_is_four_channel_playing_)
	{
		if (!ui->playWidget1_->isPlaying())
		{

			ListAndGLWindowManagerIns.UpdateMap(replay_current_select_item_info_.id, 1);
			replay_current_select_GLWindow_ = RePlayGL1;
			//每次设置都更新四个窗口是否都在播放
			UpdateIsFourChannelPlaying();
			return ui->playWidget1_;
		}
		else if (!ui->playWidget2_->isPlaying())
		{

			ListAndGLWindowManagerIns.UpdateMap(replay_current_select_item_info_.id, 2);
			replay_current_select_GLWindow_ = RePlayGL2;

			//每次设置都更新四个窗口是否都在播放
			UpdateIsFourChannelPlaying();
			return ui->playWidget2_;
		}
		else if (!ui->playWidget3_->isPlaying())
		{

			ListAndGLWindowManagerIns.UpdateMap(replay_current_select_item_info_.id, 3);
			replay_current_select_GLWindow_ = RePlayGL3;

			//每次设置都更新四个窗口是否都在播放
			UpdateIsFourChannelPlaying();
			return ui->playWidget3_;
		}
		else if (!ui->playWidget4_->isPlaying())
		{

			ListAndGLWindowManagerIns.UpdateMap(replay_current_select_item_info_.id, 4);
			replay_current_select_GLWindow_ = RePlayGL4;

			//每次设置都更新四个窗口是否都在播放
			UpdateIsFourChannelPlaying();
			return ui->playWidget4_;
		}
		else
		{
			return NULL;
		}
	}
	//如果四个窗口都在播放，选择选中的窗口播放
	else
	{
		switch (replay_current_select_GLWindow_)
		{
		case replayWgt::RePlayGL1:
		{

								ListAndGLWindowManagerIns.UpdateMap(replay_current_select_item_info_.id, 1);
								//更新四个窗口是否都在播放
								UpdateIsFourChannelPlaying();
								return ui->playWidget1_;
		}
		case replayWgt::RePlayGL2:
		{

								ListAndGLWindowManagerIns.UpdateMap(replay_current_select_item_info_.id, 2);
								//更新四个窗口是否都在播放
								UpdateIsFourChannelPlaying();
								return ui->playWidget2_;
		}
		case replayWgt::RePlayGL3:
		{
								ListAndGLWindowManagerIns.UpdateMap(replay_current_select_item_info_.id, 3);
								//更新四个窗口是否都在播放
								UpdateIsFourChannelPlaying();
								return ui->playWidget3_;
		}
		case replayWgt::RePlayGL4:
		{

								ListAndGLWindowManagerIns.UpdateMap(replay_current_select_item_info_.id, 4);
								//更新四个窗口是否都在播放
								UpdateIsFourChannelPlaying();
								return ui->playWidget4_;
		}
		default:
			return NULL;
			break;
		}

	}
}

playModeWgt* replayWgt::GetPlayModelWgt(int list_item_num)
{
	switch ((RePlayCurrentSelectGLWindow)ListAndGLWindowManagerIns.GetGLValue(list_item_num))
	{
	case replayWgt::RePlayGL1:
	{
								 return ui->playWidget1_;
	}
	case replayWgt::RePlayGL2:
	{
								 return ui->playWidget2_;
	}
	case replayWgt::RePlayGL3:
	{
								 return ui->playWidget3_;
	}
	case replayWgt::RePlayGL4:
	{
								 return ui->playWidget4_;
	}
	default:
		return NULL;
		break;
	}
}

void replayWgt::UpdateIsFourChannelPlaying()
{
	if (ui->playWidget1_->isPlaying() && ui->playWidget2_->isPlaying() && ui->playWidget3_->isPlaying() && ui->playWidget4_->isPlaying())
		replay_is_four_channel_playing_ = true;
	else
		replay_is_four_channel_playing_ = false;
}

void replayWgt::closeReplaySourse(int glwindow_num)
{
	switch (glwindow_num)
	{
	case replayWgt::RePlayGL0:
		break;
	case replayWgt::RePlayGL1:
	{
							if (ui->playWidget1_->isPlaying())
							{
								ui->playWidget1_->close();

								return;
							}
							break;
	}

	default:
		break;
	}
}

void replayWgt::pausePlayer(int glwindow_num, bool reset)
{
	switch (glwindow_num)
	{
	case replayWgt::RePlayGL0:
		break;
	case replayWgt::RePlayGL1:
	{
		ui->playWidget1_->closeStream();
	    ui->playWidget1_->pauseUI(reset);
		break;
	}
	}
}

void replayWgt::initData(const QList<deviceInfo> &itemInfoList)
{
	generateUI();
}

void replayWgt::getSelectId(int selectId)
{
	m_selectId_ = selectId;
}



void replayWgt::slot_pause_play()
{
	if (!ui->playWidget1_->isPlaying())
	{
		return;
	}
	isPlay_ = !isPlay_;
	if (isPlay_){
		//播放
		ui->pauseBtn_->setStyleSheet("#pauseBtn_{border-image:url(:/image/image/pause.png);}#pauseBtn_:hover{border-image:url(:/image/image/pauseb.png);}#pauseBtn_:pressed{margin:1px;}");
		QString date = ui->dateWidget->getSelectedDate();
		if (!isPause_)
		{
			request_time = commonFun::getDateTime(curr_time_, date, curr_duration_) + 28800;
		}
		current_select_replaymodewgt_->CreatStitchFiles(REPLAY, request_time);
		isPause_ = false;
		//setMoveEnabled(true);
	}
	else
	{
		//暂停
		ui->pauseBtn_->setStyleSheet("#pauseBtn_{border-image:url(:/image/image/play.png);}#pauseBtn_:hover{border-image:url(:/image/image/playb.png);}#pauseBtn_:pressed{margin:1px;}");
		pausePlayer(1, false);
		isPause_ = true;
		//setMoveEnabled(false);
	}
	playControlRequest(isPlay_, speed_);
}

void replayWgt::slot_setSelectedDate(QString date)
{
	ui->dateWidget->setSelectedDate(date);
}

void replayWgt::slotOnReplayRequestSucceed()
{
	replay_net_no_response_ = false;
	replay_request_url_ = TcpDataManagerIns.GetRequestTime();
	setMoveEnabled(false);
	//状态机流转到获取SRS的回调
	current_select_replaymodewgt_->setStitchStatus(StitchStatus::STITCH_STATUS_GET_SRS);
}

void replayWgt::onListItemDoubleClickedSlot(QTreeWidgetItem* itemWidget, int column)
{

	deviceItemWidget *m_itemWidget = qobject_cast<deviceItemWidget*>(ui->treeWidget_->itemWidget(itemWidget, column));
	int index = -1;
	if (m_itemWidget){
		for (int i = 0; i < itemWidgetList_.size(); ++i)
		{
			if (m_itemWidget == itemWidgetList_[i])
			{
				index = i;
				initData(InfoList_);
				break;
			}
		}
	}

	if (index != -1)
	{
		if (!InfoList_[index].status)
		{
			Log::Info("device is offline, do not to open!");
			Feedback::instance()->maskUI(DEVICE_OFFLINE);
			setReplayStatusShowLabel(PLAY_STATUS_SERVER_ERROR);
			return;
		}
		//保存当前点击的item信息
		replay_current_select_item_info_ = InfoList_[index];
		Log::Info("current select deviceId : %s", InfoList_[index].serialNo.toLocal8Bit().data());

		for (int i = 0; i < InfoList_.length(); i++)
		{
			if (InfoList_[i].id == replay_current_select_item_info_.id)
			{
				InfoList_[i].RbClicked = !InfoList_[i].RbClicked;
			}
		}
		initData(InfoList_);
		//
		if (!replay_current_select_item_info_.RbClicked)
		{
			replay_net_no_response_ = true;
			for (int i = 0; i < InfoList_.length(); i++)
			{
				if (InfoList_[i].id != replay_current_select_item_info_.id)
				{
					InfoList_[i].RbClicked = false;
				}
			}
			initData(InfoList_);
			//设置当前点击的播放窗口
			current_select_replaymodewgt_ = SetPlayModelWgt();
			current_select_replaymodewgt_->setPlayConfig(replay_current_select_item_info_);
			if (SocketManagerIns.isConnected())
			{
				//查询回放接口
				if (query_video_thread_ && query_video_thread_->joinable())
				{
					query_video_thread_->join();
				}
				query_video_thread_.reset(new boost::thread(&replayWgt::QueryForVideo, this));
				replay_server_no_response_ = true;
				QTimer::singleShot(3000, this, SLOT(slotOnReplayServerNoResponse()));
			}
		}
		else
		{
			//获取当前列表设置的播放出口
			m_load_state_ = false;
			current_select_replaymodewgt_ = GetPlayModelWgt(replay_current_select_item_info_.id);
			if (current_select_replaymodewgt_->isStitchFileOk())
			{
				restoreUi();
				setMoveEnabled(true);
				//关闭实时定时器
				if (updateTimer_ != NULL && updateTimer_->isActive())
				{
					updateTimer_->stop();
					Log::Debug("replay request timer stop!");
				}
			}
			else
			{
				return;
			}
		}
		emit sigOnTransportList(InfoList_);
	}
}

void replayWgt::slotOnRequestReplayTimer()
{
	Log::Debug("request replay timer start by timer!");
	QueryForVideo();
}

void replayWgt::slotOnReplaySetFullScreen(bool is_full_screen)
{
	ui->playWidget2_->setVisible(false);
	ui->playWidget3_->setVisible(false);
	ui->playWidget4_->setVisible(false);

	ui->leftWidget->setVisible(is_full_screen);
	ui->line_2->setVisible(is_full_screen);
	ui->prograssBarWgt->setVisible(is_full_screen);
	ui->widget_3->setVisible(is_full_screen);
}

void replayWgt::RePlayDoubleClickToPlayStatusCommunication()
{
	//判断回放请求时间是否在时间域内
	bool request = false;
	srs_http_no_response = 0;
	QString date = ui->dateWidget->getSelectedDate();
	int m_time = commonFun::getDateTime(current_request_time_, date, current_duration_);
	for (int i = 0; i < m_replay_infoList_.size(); i++)
	{
		for (int j = 0; j < m_replay_infoList_[i].m_infoList.size(); j++)
		{
			Log::Debug("time:%d", m_time);
			Log::Debug("startTime:%d", m_replay_infoList_[i].m_infoList[j].startTime);
			Log::Debug("endTime:%d", m_replay_infoList_[i].m_infoList[j].endTime);
			if (m_time >= m_replay_infoList_[i].m_infoList[j].startTime && m_time <= m_replay_infoList_[i].m_infoList[j].endTime)
			{
				request = true;
				Log::Debug("replay requested time is OK");
			}
			else
			{
				Log::Debug("replay requested time is not in TIMESTAMP");
			}
		}
	}

	//满足条件再请求回放视频
	if (request)
	{
		Log::Debug("repalay info : getCheckState checked");
		//每次拖动把上次时间清零
		oriTime_ = 0;
		if (ui->playWidget1_->isPlaying())
		{
			ui->playWidget1_->exchangeUI();
		}

		curr_time_ = current_request_time_;
		curr_duration_ = current_duration_;
		isPause_ = false;
		QString date = ui->dateWidget->getSelectedDate();
		if (!isPause_)
		{
			request_time = commonFun::getDateTime(curr_time_, date, curr_duration_) + 28800;
		}
		setMoveEnabled(false);
		current_select_replaymodewgt_->setIsPlaying(true);
		current_select_replaymodewgt_->CreatStitchFiles(REPLAY, request_time);
	}
	else
	{
		isPause_ = true;
		Log::Debug("replay info : getCheckState unchecked");
		Feedback::instance()->maskUI(REPLAY_REQUEST_FAILED);
	}
}