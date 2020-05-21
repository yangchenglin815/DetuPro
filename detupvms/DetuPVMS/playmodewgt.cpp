#include "playmodewgt.h"
#include "ui_playmodewgt.h"

#include <QTimer>
#include <QGraphicsOpacityEffect>
#include <QMovie>

#include "SequencerWgt.h"
#include "SequencerTipWgt.h"

#include "VRView\directionArrowWgt.h"

#include "constStruct.h"
#include "APIProtocol.h"
#include "DetuPVMSIni.h"

#include "HttpClient.h"
#include "HttpSignal.h"
#include "commonFun.h"
#include "m1player/header/MessageQueue.h"

#include "RoamFragment.h"

//全局控制器
#include "PVMSEventManager.h"
#include "BallCamLinkageManager.h"
#include "MessageManager.h"
#include "SocketManager.h"
#include "TcpDataManager.hpp"
#include "ListAndGLWindowManager.h"
#include "MapPointListManager.h"
#include "SequencerManager.h"
#include "MyMd5.h"
#include "RFIDDataManager.h"

#include "MinimapWgt.h"
#include "ballCamWgt.h"
#include "gunCamWgt.h"
#include "mapToolWidget.h"
#include "feedback.h"
#include "socketRequest.h"
#include "ViewSignal.h"
#include "RfidReader.h"
#include "DoorManager.h"
#include "weather_peopleflow.h"

//截图
#include "PanoCalibraterAndCapturer.h"
using namespace dm::server;


playModeWgt::playModeWgt(QWidget *parent) :playModeWgt(parent, false)
{

}

playModeWgt::playModeWgt(QWidget *parent, bool is_map_available)
: QWidget(parent),
ui(new Ui::playModeWgt),
is_map_available_(is_map_available),
is_map_opened_(false),
is_full_screen_(true),
is_htc_open_(false),
is_ball_cam_open_(false),
is_playing_(false),
is_replaying_(false),
is_rotating_(false),
is_stitch_file_ok_(true),
is_init_caprure_(true),
is_optimize_capture_(false),
is_optimize_ok_(true),
m_play_thread_return_(false),
ballwgt_(NULL),
gunwgt_(NULL),
timeLbl_(NULL),
streamInfoLbl_(NULL),
current_stream_info_(""),
current_stitch_status_(STITCH_STATUS_START),
is_exchange_(false),
select_pvs_device_(""),
net_no_response_(true),
play_window_type_(-1),
replay_request_time_(-1),
gl_view_screen_(NULL),
m1_pixel_pano_player_(NULL),
m1_player_(NULL),
first_frames_(true),
m_pixelPlugin(NULL),
m_signal_id_(0),
vcodec_type_(1),
m_global_video_time_(-1),
m_first_frames(true),
m_preview_stream_type(1),
m_replay_stream_type(3),
m_map_preview_stream_type(4),
m_map_replay_stream_type(7),
m_panoViewMode(PanoViewMode_FLAT),
m_subStream_open(true),
sequencer_wgt_(NULL),
sequencer_tip_wgt_(NULL),
is_sequencer_play_(false),
miniMap_(NULL),
sequencer_angle_(0.0),
m_mapToolWgt(NULL),
calibrater_and_capturer_(NULL),
rfid_reader_(NULL),
door_manager_(NULL),
weather_peopleflow_(NULL)
{
	ui->setupUi(this);

	//默认显示选择页面
	ui->scrollArea_->setVisible(false);
	//设置滑动区域不现实边框
	ui->scrollArea_->setFrameStyle(QFrame::NoFrame);

	ui->optimize_->setVisible(false);
	ui->ballBtn_->setVisible(false);
	ui->htcBtn_->setVisible(false);
	ui->switchStreamBtn_->setVisible(true);

	//地图界面按钮
	ui->MapBtn_->setVisible(is_map_available_);
	ui->topWidget_->setVisible(is_map_available_);
	ui->ReplayBtn_->setVisible(false);
	ui->hotPointBtn_->setVisible(false);

	//图组打开按钮
	picGroupBtn_ = new QPushButton(this);
	connect(picGroupBtn_, SIGNAL(clicked(bool)), this, SLOT(slotOnPicGroupClicked(bool)));
	picGroupBtn_->setCheckable(true);
	picGroupBtn_->setFixedSize(18, 18);
	picGroupBtn_->setToolTip(QStringLiteral("组图"));
	picGroupBtn_->setStyleSheet("QPushButton{border-image:url(:/image/image/picGroupb.png);}QPushButton:pressed{margin:1px;}" \
		"QPushButton:hover{border-image:url(:/image/image/picGroup.png);}QPushButton:checked{border-image:url(:/image/image/picGroup.png);}");
	ui->topWidget_->layout()->addWidget(picGroupBtn_);
	picGroupBtn_->setVisible(false);


	//关闭按钮初始化
	QPushButton *closeBtn = new QPushButton(this);
	connect(closeBtn, SIGNAL(clicked()), this, SLOT(onClosePlaySlot()));
	closeBtn->setFixedSize(18, 18);
	closeBtn->setToolTip(QStringLiteral("关闭"));
	closeBtn->setStyleSheet("QPushButton{border-image:url(:/image/image/close.png);}QPushButton:pressed{margin:1px;}" \
         "QPushButton:hover{border-image:url(:/image/image/closeb.png);}");
	ui->topWidget_->layout()->addWidget(closeBtn);

	QGridLayout *playout = new QGridLayout;
	m1_pixel_pano_player_ = new M1PixelPanoPlayer();
	m1_pixel_pano_player_->setPanoPlayerListener(this);
	m1_pixel_pano_player_->setPanoPlayerPluginListener(this);
	gl_view_screen_ = new GLSurfaceWidget(NULL);

	decorFragment_ = new RoamFragment(this);
	qRegisterMetaType<SpyInfo_t >("SpyInfo_t");
	connect(decorFragment_, SIGNAL(sigOnOpenGunCam(SpyInfo_t)), this, SLOT(slotOnOpenGunCam(SpyInfo_t)), Qt::QueuedConnection);
	connect(decorFragment_, SIGNAL(sigOnOpenHotPic(QString)), this, SLOT(slotOnOpenHotPic(QString)), Qt::QueuedConnection);

	//decorFragment_->setv

	m1_pixel_pano_player_->setFragment(decorFragment_);

	connect(gl_view_screen_, SIGNAL(SignalToTrigBallCamData(double, double)), &BallCamLinkageManagerIns, SLOT(SlotToTrigBallCamData(double, double)), Qt::QueuedConnection);
	connect(gl_view_screen_, SIGNAL(SignalToTrigBallCamData(double, double)), &SequencerManagerIns, SLOT(SlotToTrigSequencer(double, double)), Qt::QueuedConnection);
	//connect(gl_view_screen_, SIGNAL(SignalToTrigBallCamData(double, double)), this, SLOT(SlotToGetLastPos(double, double)), Qt::QueuedConnection);
	
	gl_view_screen_->setRender(m1_pixel_pano_player_);
	
	playout->addWidget(gl_view_screen_);	

	playout->setHorizontalSpacing(0);
	playout->setVerticalSpacing(0);
	playout->setContentsMargins(0, 0, 0, 0);
	ui->scrollArea_->setLayout(playout);
	m_pixelPlugin = m1_pixel_pano_player_->getPixelPlugin();
	CMessageQueue::GetInstance().Register(std::bind(&playModeWgt::onSigaction, this, std::placeholders::_1, std::placeholders::_2), m_signal_id_);

	connect(ui->autoCircleBtn_, SIGNAL(clicked()), this, SLOT(onSetAutoRotateSlot()));
	connect(ui->captureBtn_, SIGNAL(clicked()), this, SLOT(onCaptureSlot()));
	connect(ui->htcBtn_, SIGNAL(clicked()), this, SLOT(onOpenHtcViveSlot()));
	connect(ui->ballBtn_, SIGNAL(clicked()), this, SLOT(onOpenBallCamSlot()));
	connect(ui->optimize_, SIGNAL(clicked()), this, SLOT(onOpenOptimizeSlot()));
	connect(ui->bandWidthBtn, SIGNAL(clicked()), this, SLOT(slotOnRequestGetBandWidth()));
	connect(ui->switchStreamBtn_, SIGNAL(clicked(bool)), this, SLOT(OnSwitchStreamSlot(bool)));

	//地图界面按钮响应事件
	connect(ui->MapBtn_, SIGNAL(clicked(bool)), this, SLOT(OnOpenPanoMapSlot(bool)));
	connect(ui->ReplayBtn_, SIGNAL(clicked()), this, SLOT(OnOpenMapReplaySlot()));

	connect(this, SIGNAL(SignalToShowGlWindow()), this, SLOT(onShowGlWindowSlot()));

	qRegisterMetaType<PLAY_STATUS >("PLAY_STATUS");
	connect(this, SIGNAL(sigOnReportUI(PLAY_STATUS, int)), this, SLOT(slotOnReportUI(PLAY_STATUS, int)), Qt::DirectConnection);

	connect(this, SIGNAL(SignalToSetGlLabel(PLAY_STATUS)), this, SLOT(onSetGlLabelSlot(PLAY_STATUS)), Qt::DirectConnection);
	connect(ViewSignal::instance(), SIGNAL(sigOnControlPlayerRecordFlv()), this, SLOT(slotOnControlPlayerRecordFlv()));
	connect(ViewSignal::instance(), SIGNAL(sigOnHandleSubStreamMessage(bool, QString, int)), this, SLOT(slotOnHandleSubStreamMessage(bool, QString, int)));

	QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
	if (!is_map_available_)
	{
		ui->topWidget_->setGraphicsEffect(opacityEffect);
 		opacityEffect->setOpacity(0.7);
	}


}


playModeWgt::~playModeWgt()
{
// 	if (calibrater_and_capturer_ != NULL)
// 	{
// 		free(calibrater_and_capturer_);
// 		calibrater_and_capturer_ = NULL;
// 	}
// 
// 	if (decorFragment_ != NULL)
// 	{
// 		free(decorFragment_);
// 		decorFragment_ = NULL;
// 	}
// 
// 	if (m1_pixel_pano_player_ != NULL)
// 	{
// 		free(m1_pixel_pano_player_);
// 		m1_pixel_pano_player_ = NULL;
// 	}

}

void playModeWgt::setBtnVisible(bool visible)
{
	ui->ballBtn_->setVisible(visible);
}

//  mode :     0:预览     1:回放
void playModeWgt::setShowTime(QString time, int mode)
{
	if (timeLbl_ == NULL)
	{
		timeLbl_ = new timeLabel(this);
	}
	timeLbl_->resize(170, 26);
	timeLbl_->setShowTime(time);
	switch (mode)
	{
	case 0:
		timeLbl_->move(0, this->height() - 50);
		//QTimer::singleShot(20, this, SLOT(slotOnUpdate()));
		break;
	case 1:
		timeLbl_->move(0, this->height() - 30);
		//timeLbl_->move(mapToGlobal(QPoint(0, 0)).rx(), mapToGlobal(QPoint(0, 0)).ry() + (height() - timeLbl_->height()));
		break;
	}
	timeLbl_->show();
}

void playModeWgt::setShowStreamInfo()
{
		if (streamInfoLbl_ == NULL)
		{
			streamInfoLbl_ = new timeLabel(this);
		}
		streamInfoLbl_->resize(220, 26);
		streamInfoLbl_->setShowTime(current_stream_info_);
		streamInfoLbl_->move(0, this->height() - 30);
		streamInfoLbl_->show();

}

void playModeWgt::closeShowTime()
{
	QTimer::singleShot(50, this, [&](){
		if (timeLbl_ != NULL)
		{
			timeLbl_->close();
			timeLbl_->deleteLater();
			timeLbl_ = NULL;
		}
		if (streamInfoLbl_ != NULL)
		{
			streamInfoLbl_->close();
			streamInfoLbl_->deleteLater();
			streamInfoLbl_ = NULL;
		}
	});
}

void playModeWgt::setTimeLabelHeight(int nHeight)
{
	if (timeLbl_ != NULL)
	{
		timeLbl_->move(mapToGlobal(QPoint(0, 0)).rx(), mapToGlobal(QPoint(0, 0)).ry() + (height() - timeLbl_->height()) - nHeight);
	}
}

void playModeWgt::SetPlayWindowNum(int play_window_num)
{
	play_window_num_ = play_window_num;
}

void playModeWgt::setTopWgtVisable(bool chosen)
{
	ui->topWidget_->setVisible(chosen);
}

void playModeWgt::setIsPlaying(bool is_playing)
{
	is_playing_ = is_playing;
}


void playModeWgt::CreatStitchFiles(int type, int requestTime)
{
	play_window_type_ = type;
	replay_request_time_ = requestTime;
	if (creatStitchFilesThread_ && creatStitchFilesThread_->joinable())
	{
		creatStitchFilesThread_->join();
	}
	creatStitchFilesThread_.reset(new boost::thread(&playModeWgt::CreatStitchFilesThread, this));
}

void playModeWgt::CreatStitchFilesThread()
{
	if (current_stitch_status_ != STITCH_STATUS_START)
	{
		Log::Error(" current_stitch_status_ != STITCH_STATUS_START  %s %d", __FUNCTION__, __LINE__);
		return;
	}
	else
	{
		current_stitch_status_ = STITCH_STATUS_COMMUNICATION;
		this->StitchStatusMachine();
	}
}

void playModeWgt::play()
{
	if (playThread_ && playThread_->joinable())
	{
		playThread_->join();
	}
	playThread_.reset(new boost::thread(&playModeWgt::thread_play, this));


}

void playModeWgt::close()
{
	closeStream();
	closeShowTime();
	closePTZ();
	closeUI();

	//同步更新列表状态
	int item_num = ListAndGLWindowManagerIns.GetItemValue(play_window_num_);
	ListAndGLWindowManagerIns.RemoveMap(ListAndGLWindowManagerIns.GetItemValue(play_window_num_), play_window_num_);
	emit sigOnResetStatus(item_num);

	if (is_ball_cam_open_)
	{
		onOpenBallCamSlot();
	}
	ui->label_2->setText(tr("未加载视频源"));

	if (is_map_available_)
	{
		DetuPVMSIni::setGlobalStreamType(false);
	}
}

void playModeWgt::clearPlay()
{
	switch (play_window_type_)
	{
	case PREVIEW:
		if (m_preview_stream_type == 1)
		{
			this->close();
		}
		break;
	case REPLAY:
		if (m_replay_stream_type == 3)
		{
			this->close();
		}
		break;
	case MAP_PLAY:
		if (m_map_preview_stream_type == 5)
		{
			this->close();
		}
		break;
	case MAP_REPLAY:
		if (m_map_replay_stream_type == 7)
		{
			this->close();
		}
		break;
	default:
		break;
	}
}

void playModeWgt::thread_close_stream()
{
	Log::Debug("playModeWgt::CMD_DETU_CLIENT_CLOSE_VIDEO!");

	protocol_head_t api_head;
	api_detu_client_close_video_t api_detu;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_CLIENT_CLOSE_VIDEO;
	api_head.nDataLen = api_detu.get_size();
	api_head.nResult = 0;
	QString url_ = RTMP_URL_[RTMP_URL_.length() - 1];
	api_head.nStreamId = url_.toInt();
	//api_head.nReserver = 0x01;        //预留位
	api_head.nEndFlags = 0xFA;

	memcpy(api_detu.szDeviceId, select_pvs_device_.toLocal8Bit().data(), API_ARRAY_LEN);

	response res(api_head.get_size() + api_detu.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
	response_add_resprotocol<api_detu_client_close_video_t>(res, &api_detu);
	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}

}
void playModeWgt::closeUI()
{
	Log::Info("closeUI closeplayer");
	this->closePlayer();

	if (ui->switchStreamBtn_->isChecked()) 
	{
		ui->switchStreamBtn_->setChecked(false);
		DetuPVMSIni::setGlobalStreamType(false);
	}

	if (sequencer_tip_wgt_ != NULL)
	{
		sequencer_tip_wgt_->deleteLater();
		sequencer_tip_wgt_ = NULL;
	}
	if (sequencer_wgt_ != NULL)
	{
		sequencer_wgt_->deleteLater();
		sequencer_wgt_ = NULL;
	}
	current_stitch_status_ = STITCH_STATUS_START;
	QTimer::singleShot(50, this, [&](){
		ui->scrollArea_->setVisible(false);
		ui->initWidget->setVisible(true);
		ui->label_2->setText(tr("未加载视频源"));
		ui->label->setText("");

		is_exchange_ = false;
		is_playing_ = false;
		is_rotating_ = false;
	});
}

void playModeWgt::handshakeFailed()
{
	Log::Info("handshakeFailed closeplayer");
	closeStream();
	closePTZ();
	closePlayer();
	is_playing_ = false;
	ui->scrollArea_->setVisible(false);
	ui->initWidget->setVisible(true);

	//同步更新列表状态
	int item_num = ListAndGLWindowManagerIns.GetItemValue(play_window_num_);
	ListAndGLWindowManagerIns.RemoveMap(ListAndGLWindowManagerIns.GetItemValue(play_window_num_), play_window_num_);
	emit sigOnResetStatus(item_num);
}

void playModeWgt::switchStream()
{
	Log::Info("switchStream closeplayer");

	closeStream();
	closeShowTime();
	closePTZ();
	this->closePlayer();
	QTimer::singleShot(50, this, [&](){
		ui->scrollArea_->setVisible(false);
		ui->initWidget->setVisible(true);
		ui->label_2->setText(tr("码流切换中..."));
		ui->label->setText("");
	});
}

void playModeWgt::sequencer()
{
	Log::Info("sequencer");

	//设置过场loading效果
	if (sequencer_tip_wgt_ != NULL)
	{
		sequencer_tip_wgt_->deleteLater();
		sequencer_tip_wgt_ = NULL;
	}
	sequencer_tip_wgt_ = new SequencerTipWgt(this);
	sequencer_tip_wgt_->move((width() - sequencer_tip_wgt_->width()) / 2, (height() - sequencer_tip_wgt_->height()) / 2);
	sequencer_tip_wgt_->setGif(":/image/image/jzc.gif");
	sequencer_tip_wgt_->show();

	if (is_map_available_)
	{
		//关闭小箭头
		if (sequencer_wgt_ != NULL)
		{
			sequencer_wgt_->deleteLater();
			sequencer_wgt_ = NULL;
		}
	}

	closeStream();
	closePTZ();
	this->closePlayer();


}

void playModeWgt::pauseUI(bool reset)
{
	Log::Info("pauseUI closeplayer");
	this->closePlayer();
	if (reset)
	{
		ui->scrollArea_->setVisible(false);
		ui->initWidget->setVisible(true);
		ui->label_2->setText(tr("未加载视频源"));
	}
}

void playModeWgt::exchangeUI()
{
	is_exchange_ = true;
	is_playing_ = false;
	ui->scrollArea_->setVisible(false);
	ui->initWidget->setVisible(true);
}

void playModeWgt::closeStream()
{
	if (closeStreamThread_ && closeStreamThread_->joinable())
	{
		closeStreamThread_->join();
	}
	closeStreamThread_.reset(new boost::thread(&playModeWgt::thread_close_stream, this));
}

void playModeWgt::closePlayer()
{
	if (closePlayerThread_ && closePlayerThread_->joinable())
	{
		closePlayerThread_->join();
	}
	closePlayerThread_.reset(new boost::thread(&playModeWgt::thread_close_player, this));
}


void playModeWgt::thread_close_player()
{
	mutex_protected_player_.lock();
	if (m1_player_ != NULL)
	{
		m_pixelPlugin->notifyStateChanged(PluginState_ERROR, "m1 player error");
		is_exchange_ = false;
		m1_player_->Close();
		m1_player_ = NULL;
	}
	m_first_frames = true;
	mutex_protected_player_.unlock();
}


void playModeWgt::setStreamInfo(QString resolution, int framerate, int bitrate)
{
	current_stream_info_ = QString("%1@%2fps / %3kbps").arg(resolution).arg(framerate).arg(bitrate);
	Log::Info("current stream info : %s", current_stream_info_.toLocal8Bit().data());
}

void playModeWgt::thread_play()
{
	QString path;
	switch (play_window_type_)
	{
	case PREVIEW:
		path = QDir::homePath() + "/AppData/Local/Pano-VMS/flv/PREVIEW/" + current_select_item_info_.serialNo + "/";
		break;
	case REPLAY:
		path = QDir::homePath() + "/AppData/Local/Pano-VMS/flv/REPLAY/" + current_select_item_info_.serialNo + "/";
		break;
	case MAP_PLAY:
		path = QDir::homePath() + "/AppData/Local/Pano-VMS/flv/PREVIEW/" + m_panoPointInfo.cameraInfo.serialNo + "/";
		break;
	case MAP_REPLAY:
		path = QDir::homePath() + "/AppData/Local/Pano-VMS/flv/REPLAY/" + m_panoPointInfo.cameraInfo.serialNo + "/";
		break;
	default:
		break;
	}

	
	QDir dir(path);
	if (!dir.exists())
	{
		bool ret = dir.mkdir(path);
	}
	if (play_window_num_ == 1)
	{
		m1_player_.reset(new CM1Player(false));
	}
	else
	{
		m1_player_.reset(new CM1Player(false));
	}

	m1_player_->SetDisplayFps(30);
	m1_player_->SetDisplayTag(true);
	m1_player_->SetRecordPath(path.toLocal8Bit().data());
	m1_player_->SetRecordTag(DetuPVMSIni::getSaveFlvTag());
	m1_player_->SetStreamType(StreamTypeRtmp);
	m1_player_->SetOnwer(m_signal_id_);

	int m_stream_type = QString(RTMP_URL_.at(RTMP_URL_.length() - 1)).toInt();
	if (m_stream_type)
	{
		//子码流
		vcodec_type_ = DetuPVMSIni::getSubDecodeMode() ? 3 : 1;
	}
	else
	{
		//主码流
		vcodec_type_ = DetuPVMSIni::getDecodeMode() ? 3 : 1;
	}
	if (vcodec_type_ != 1) {
		if (vcodec_type_ == 2) {
			m1_player_->SetDeocdeType(DecodeTypeIntel);
		}
		else if (vcodec_type_ == 3) {
			m1_player_->SetDeocdeType(DecodeTypeCuda);
		}
	}

	struct m1_player_config_s config;
	config.videoproc = std::bind(&playModeWgt::OnVideoData, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	config.url = RTMP_URL_.toStdString();
	Log::Debug("PLAY RTMP_URL:%s", config.url.c_str());
	config.messageproc = nullptr;



	int ret = m1_player_->Init(config);
	if (ret != 0)
	{
		emit sigOnReportUI((PLAY_STATUS)ret, PLAY_ERROR);
		Log::Error("m1 player init error.");
		return;
	}
	m1_player_->Play();
	Log::Info("m1 player init success.");
}




void playModeWgt::OnVideoData(m1_video_frame_s** av_frame_sync_list, int index, unsigned int timestamp)
{
	m_av_frame_sync_list_ = av_frame_sync_list;

	m_global_video_time_ = timestamp;
	//实时优化抓图
	if (is_optimize_capture_)
	{
		calibrater_and_capturer_->InitRealTimeCapture(av_frame_sync_list);
		is_init_caprure_ = true;
		is_optimize_capture_ = false;
	}
	//初次播放抓图
	if (!is_init_caprure_)
	{
		calibrater_and_capturer_->InitRealTimeCapture(av_frame_sync_list);
		is_init_caprure_ = true;
	}
	if (!is_stitch_file_ok_)
		return;

	double start_t = 0.0;
	double diff=0.0;
	if (m_first_frames) {

		emit SignalToShowGlWindow();
		emit sigOnPlayStatus();

		m_first_frames = false;
		PluginMetaData metadata;
		metadata.height = av_frame_sync_list[0]->h;
		metadata.width = av_frame_sync_list[0]->w;
		for (int i = 0; i < PLUGIN_MAX_PLANE; i++) {
			metadata.lineSize[i] = av_frame_sync_list[0]->linesize[i];
		}
		if (av_frame_sync_list[0]->format == PIX_FMT_YUV420P) {
			metadata.pluginFormat = PluginColorFormat_YUV420P;
		}
		else if (av_frame_sync_list[0]->format == PIX_FMT_NV12) {
			metadata.pluginFormat = PluginColorFormat_NV12;
		}

 		this->setCailbration();


		vector<PluginMetaData> metadata_vector;
		metadata_vector.push_back(metadata);
		m_pixelPlugin->notifyMetaDatas(metadata_vector);
		m_pixelPlugin->notifyStateChanged(PluginState_PREPARED, "m1 player ready.");


	}
	for (int i = 0; i < PLUGIN_MAX_PLANE; i++) {
		if (av_frame_sync_list[i]->format == PIX_FMT_YUV420P) {
			m_frames[i].colorFormat = PluginColorFormat_YUV420P;
			m_frames[i].planes = 3;
		}
		else if (av_frame_sync_list[i]->format == PIX_FMT_NV12) {
			m_frames[i].colorFormat = PluginColorFormat_NV12;
			m_frames[i].planes = 2;
		}
		for (int j = 0; j < PLUGIN_MAX_PLANE; j++) {
			m_frames[i].data[j] = av_frame_sync_list[i]->data[j];
		}
	}
	m_pixelPlugin->notifyFramesChanged((PluginFrame*)m_frames, 4);
	//emit sigOnGetRecordTime(timestamp);
}

void playModeWgt::setCailbration()
{
	PanoramaData panoData;
	PanoNodeImage imageData;
	imageData.isProcess2_1 = true;
	imageData.panoResourceType = PanoResourceType_VIDEO;
	vector<string> urls;
	urls.push_back(RTMP_URL_.toLocal8Bit().data());
	imageData.urls = urls;

	char biaoding[512] = { 0 };


	QString biaoding_path = QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/pts") + "/" + select_m1_device_ + "/biaoding.txt";
	FILE* biaoding_txt = fopen(biaoding_path.toLocal8Bit(), "rb");
	int pts_length;
	if (biaoding_txt)
	{
		fseek(biaoding_txt, 0, SEEK_END);
		pts_length = ftell(biaoding_txt);
		fseek(biaoding_txt, 0, SEEK_SET);
		int sts = fread(biaoding, 1, pts_length, biaoding_txt);
		fclose(biaoding_txt);
	}

	imageData.calibration = biaoding;
	imageData.panoDeviceId = PanoDeviceId_SPHERE_DETU_M1;
	panoData.nodeImage = imageData;
	PanoNodeView viewData;
	viewData.curfov = viewData.deffov;

	viewData.vLookAt = 0;

	//切换的时候角度跟随
	if (is_sequencer_play_)
	{
		viewData.hLookAt = m_panoPointInfo.initial_angle + sequencer_angle_;
		is_sequencer_play_ = false;
	}
	else
	{
		viewData.hLookAt = m_panoPointInfo.initial_angle;
	}


	viewData.viewMode = static_cast<PanoViewMode>(m_panoViewMode);
	panoData.nodeView = viewData;

	PlayerOption option1;
	option1.type = PlayerOptionType_Codec;
	option1.key = PLAYER_OPTION_DETU_KEY_DECODER;
	option1.value = "cuda";
	vector<PlayerOption> options;
	options.push_back(option1);
	m1_pixel_pano_player_->play(panoData, options);
	m1_pixel_pano_player_->setAutoRotate(false, 0.1f);

}

void playModeWgt::thread_capture()
{
	int count = 0;
	while (!is_init_caprure_)
	{
		//等待截图成功
		Sleep(100);
		count++;
		if (count > 200)
		{
			emit SignalToSetGlLabel(PLAY_STATUS_CAPTURE_ERROR);
			current_stitch_status_ = STITCH_STATUS_START;
			return;
		}
	}
	for (int i = 0; i < TcpDataManagerIns.GetList()->numlist; i++)
	{
		QString devicename((char*)(TcpDataManagerIns.GetList()->nvrList[i].szDeviceId));
		if (select_pvs_device_ == devicename)
		{
			Log::Info("Creat PTS and WT file, select_device：%s", select_m1_device_);

			//先保存一个md5文件
			QFile md5_txt(QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/pts") + "/" + select_m1_device_ + "/md5.txt");
			if (!md5_txt.exists())
			{
				md5_txt.open(QIODevice::ReadWrite);
				md5_txt.close();
			}

			//来不及搞，先写文件
			QString pts_path = QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/pts") + "/" + select_m1_device_ + "/pat.pts";
			FILE* pts = fopen(pts_path.toLocal8Bit(), "wb+");

			Log::Info("TcpDataManagerIns.GetList()->nvrList[i].pts.nPtsLen:  %d", TcpDataManagerIns.GetList()->nvrList[i].pts.nPtsLen);
			Log::Info("strlen((const char*)TcpDataManagerIns.GetList()->nvrList[i].pts.pts_data):  %d", strlen((const char*)TcpDataManagerIns.GetList()->nvrList[i].pts.pts_data));
			//判断标定参数是否为空
			if (strlen((const char*)TcpDataManagerIns.GetList()->nvrList[i].pts.pts_data) == 0)
			{
				//emit SignalToSetGlLabel(PLAY_STATUS_PTS_WT_PTS_ERROR);
				//return; 
			}
			else
			{
				int pts_length = strlen((const char*)TcpDataManagerIns.GetList()->nvrList[i].pts.pts_data);
				fwrite(TcpDataManagerIns.GetList()->nvrList[i].pts.pts_data, 1, pts_length, pts);
			}
			fclose(pts);

			current_stitch_status_ = STITCH_STATUS_OPTIMIZE;
			this->StitchStatusMachine();
		}
	}


}


void playModeWgt::thread_optimize_pts()
{
	ui->tipLabel->setText(QStringLiteral("正在优化模板"));
	is_optimize_capture_ = true;
	//等待抓图成功
	while (is_optimize_capture_)
	{
		Sleep(1);
	}

	//待定
	calibrater_and_capturer_->OptimizePts();

	is_optimize_ok_ = true;
	emit sigOnOptMizeSuccess();
	ui->tipLabel->setText("");
}

void playModeWgt::updatePlayListStatus()
{
	Log::Info("updatePlayListStatus closeplayer");
	closeStream();
	closeUI();
	closePlayer();

	//同步更新列表状态
	emit sigOnResetStatus(ListAndGLWindowManagerIns.GetItemValue(play_window_num_));
	is_playing_ = false;
	is_stitch_file_ok_ = false;
	is_init_caprure_ = false;
	current_stitch_status_ = STITCH_STATUS_START;
	//删除列表要放在最后，否则会导致item0，  超级dabug
	ListAndGLWindowManagerIns.RemoveMap(ListAndGLWindowManagerIns.GetItemValue(play_window_num_), play_window_num_);
}

void playModeWgt::setPosMove()
{
	if (ballwgt_ != NULL)
	{
		ballwgt_->resize(320, 180);
		ballwgt_->move(mapToGlobal(QPoint(0, 0)).rx() + (width() - ballwgt_->width()), mapToGlobal(QPoint(0, 0)).ry() + (height() - ballwgt_->height()));
		ballwgt_->setPosMove();
	}

	if (m_mapToolWgt != NULL)
	{
		m_mapToolWgt->move(this->width() - 320, 32);

		m_mapToolWgt->resize(320, height());
	}


	if (weather_peopleflow_ != NULL)
	{
		weather_peopleflow_->move(this->width() - 300, 32);
	}

}

void playModeWgt::setTimePos(int mode)
{
	if (timeLbl_ != NULL)
	{
		switch (mode)
		{
		case 0:
			timeLbl_->move(0, this->height() - 50);
			break;
		case 1:
			timeLbl_->move(0, this->height() - 30);
			break;
		}
	}
	if (streamInfoLbl_ != NULL)
	{
		streamInfoLbl_->move(0, this->height() - 30);
	}
}

void playModeWgt::setHiddenCtrl(bool visible)
{
	if (ballwgt_ != NULL)
	{
		ballwgt_->setHiddenCtrl(visible);
	}
}

void playModeWgt::setHiddenTime(bool visible)
{
	if (timeLbl_ != NULL)
	{
		timeLbl_->setVisible(visible);
	}
}


void playModeWgt::closePTZ()
{
	if (is_ball_cam_open_)
	{
		onOpenBallCamSlot();
	}
}

void playModeWgt::initWindow(int window_type)
{
	switch (window_type)
	{
	case PREVIEW:
		if (m_preview_stream_type == 0)
		{
			ui->switchStreamBtn_->setChecked(true);
		}
		else if (m_preview_stream_type == 1)
		{
			ui->switchStreamBtn_->setChecked(false);
		}
		break;
	case REPLAY:
		if (m_replay_stream_type == 2)
		{
			ui->switchStreamBtn_->setChecked(true);
		}
		else if (m_replay_stream_type == 3)
		{
			ui->switchStreamBtn_->setChecked(false);
		}
		break;
	case MAP_PLAY:
		if (m_map_preview_stream_type == 4)
		{
			ui->switchStreamBtn_->setChecked(true);
		}
		else if (m_map_preview_stream_type == 5)
		{
			ui->switchStreamBtn_->setChecked(false);
		}
		break;
	case MAP_REPLAY:
		if (m_map_replay_stream_type == 6)
		{
			ui->switchStreamBtn_->setChecked(true);
		}
		else if (m_map_replay_stream_type == 7)
		{
			ui->switchStreamBtn_->setChecked(false);
		}
		break;
	default:
		break;
	}
}

void playModeWgt::setGLWindowMax(bool is_max)
{
	//is_full_screen_ = is_max;
}

void playModeWgt::onSigaction(int message_type, long attach)
{
	Log::Info("message:%d from m1 player.", message_type);
	if (message_type == ERROR_SOCKET_READ)
	{
		if (m1_player_)
		{
			int ret = m1_player_->RePlay();
			if (ret == ERROR_RTMP_HANDSHAKE || ret == ERROR_RTMP_CONNECT_STREAM)
			{
				onSetGlLabelSlot(PLAY_STATUS_M1_PLAYER_SERVER_TYPE);
				Feedback::instance()->maskUI(STREAM_ERR);
				handshakeFailed();
			}
		}
	}
}

void playModeWgt::setPlayConfig(deviceInfo current_select_item_info/*, PlayModelType isOrigin*/)
{
	//设置热点

	decorFragment_->setPointInfo(current_select_item_info.m_SpyInfoList);

	if (is_map_available_)
	{
		m_panoViewMode = PanoViewMode_DEFAULT;
		connect(ViewSignal::instance(), SIGNAL(sigOnArrowClicked(int)), this, SLOT(slotOnSequencer(int)));
	}

	current_select_item_info_ = current_select_item_info;
	select_pvs_device_ = current_select_item_info.serialNo;
	Log::Debug("Get preview deviceInfo:%s RTMP_URL:%s", current_select_item_info_.serialNo.toLocal8Bit().data(), RTMP_URL_.toLocal8Bit().data());


	if (current_select_item_info_.m1DeviceId == "default")
	{
		select_m1_device_ = select_pvs_device_;

	}
	else
	{
		select_m1_device_ = current_select_item_info.m1DeviceId;

	}

	//设备名称传入
	if (calibrater_and_capturer_!=NULL)
	{
		free(calibrater_and_capturer_);
		calibrater_and_capturer_ = NULL;
	}
	calibrater_and_capturer_ = new PanoCalibraterAndCapturer();
	calibrater_and_capturer_->setDevice(select_m1_device_);

	ui->label->setText(current_select_item_info.name);
}

void playModeWgt::setReplayConfig(QString url, deviceInfo current_select_item_info)
{
	//设置热点
	decorFragment_->setPointInfo(current_select_item_info.m_SpyInfoList);

	if (is_map_available_)
	{
		m_panoViewMode = PanoViewMode_DEFAULT;
		connect(ViewSignal::instance(), SIGNAL(sigOnArrowClicked(int)), this, SLOT(slotOnSequencer(int)));
	}

	current_select_item_info_ = current_select_item_info;
	Log::Debug("Get replay deviceInfo:%s RTMP_URL:%s", current_select_item_info_.serialNo.toLocal8Bit().data(), RTMP_URL_.toLocal8Bit().data());
	select_pvs_device_ = current_select_item_info.serialNo;
	if (current_select_item_info.m1DeviceId == "default")
	{
		select_m1_device_ = select_pvs_device_;
	}
	else
	{
		select_m1_device_ = current_select_item_info.m1DeviceId;
	}

	//设备名称传入
	if (calibrater_and_capturer_ != NULL)
	{
		free(calibrater_and_capturer_);
		calibrater_and_capturer_ = NULL;
	}
	calibrater_and_capturer_ = new PanoCalibraterAndCapturer();
	calibrater_and_capturer_->setDevice(select_m1_device_);

	RTMP_URL_ = url;
	ui->label->setText(current_select_item_info.name);
}



void playModeWgt::setMapPlayConfig(PanoMapPointInfo_t panoMapInfo)
{
	//播放视频时，打开相关按钮
	ui->ballBtn_->setVisible(true);
	ui->captureBtn_->setVisible(true);
	ui->MapBtn_->setVisible(true);
	ui->optimize_->setVisible(false);
	ui->switchStreamBtn_->setVisible(true);;
	ui->ReplayBtn_->setVisible(false);
	ui->bandWidthBtn->setVisible(true);
	picGroupBtn_->setVisible(false);
	
	m_panoPointInfo = panoMapInfo;


	//设置热点
	decorFragment_->setPointInfo(m_panoPointInfo.cameraInfo.m_SpyInfoList);

	if (is_map_available_)
	{
		m_panoViewMode = PanoViewMode_DEFAULT;
		decorFragment_->setMapAvailable(false);
		connect(ViewSignal::instance(), SIGNAL(sigOnArrowClicked(int)), this, SLOT(slotOnSequencer(int)));
	}

	if (m_panoPointInfo.map_point_type == DEVICE_OFF_LINE || m_panoPointInfo.map_point_type == DEVICE_ON_LINE)
	{
		Log::Debug("Get VR MapPlay deviceInfo:%s RTMP_URL:%s", panoMapInfo.cameraInfo.serialNo.toLocal8Bit().data(), RTMP_URL_.toLocal8Bit().data());
		select_pvs_device_ = panoMapInfo.cameraInfo.serialNo;
		if (panoMapInfo.cameraInfo.m1DeviceId == "default")
		{
			select_m1_device_ = select_pvs_device_;
		}
		else
		{
			select_m1_device_ = panoMapInfo.cameraInfo.m1DeviceId;
		}
		ui->label->setText(panoMapInfo.cameraInfo.name);
	}

	//设备名称传入
	if (calibrater_and_capturer_ != NULL)
	{
		free(calibrater_and_capturer_);
		calibrater_and_capturer_ = NULL;
	}
	calibrater_and_capturer_ = new PanoCalibraterAndCapturer();
	calibrater_and_capturer_->setDevice(select_m1_device_);
}

void playModeWgt::setMapScenePlayConfig(PanoMapPointInfo_t panoMapInfo)
{
	//播放图片时，关闭相关按钮
	ui->ballBtn_->setVisible(false);
	ui->captureBtn_->setVisible(false);
	ui->optimize_->setVisible(false);
	ui->switchStreamBtn_->setVisible(false);
	ui->ReplayBtn_->setVisible(false);
	ui->bandWidthBtn->setVisible(false);
	picGroupBtn_->setVisible(true);

	m_panoPointInfo = panoMapInfo;

	if (is_map_available_)
	{
		m_panoViewMode = PanoViewMode_DEFAULT;
		decorFragment_->setMapAvailable(true);
		connect(ViewSignal::instance(), SIGNAL(sigOnArrowClicked(int)), this, SLOT(slotOnSequencer(int)));
	}

	Log::Debug("Get VR MapPlay deviceInfo:%s RTMP_URL:%s", panoMapInfo.sceneInfo.name.toStdString().c_str(), panoMapInfo.sceneInfo.sceneList[panoMapInfo.sceneInfo.currPicIndex].Path.toStdString().c_str());
	ui->label->setText(panoMapInfo.sceneInfo.name);

	PanoramaData panoData;
	PanoNodeImage imageData;
	imageData.isProcess2_1 = true;
	imageData.panoResourceType = PanoResourceType_SPHERE;
	vector<string> urls;
	urls.push_back(panoMapInfo.sceneInfo.sceneList[panoMapInfo.sceneInfo.currPicIndex].Path.toStdString());
	imageData.urls = urls;
	//imageData.calibration = weightdata.biaoding;
	imageData.panoDeviceId = PanoDeviceId_2_1;


	panoData.nodeImage = imageData;
	PanoNodeView viewData;
	viewData.curfov = viewData.deffov;
	viewData.vLookAt = 0;

	//切换的时候角度跟随
	if (is_sequencer_play_)
	{
		viewData.hLookAt = m_panoPointInfo.initial_angle + sequencer_angle_;
		is_sequencer_play_ = false;
	}
	else
	{
		viewData.hLookAt = m_panoPointInfo.initial_angle;
	}


	viewData.viewMode = static_cast<PanoViewMode>(m_panoViewMode);
	panoData.nodeView = viewData;

	//m1_pixel_pano_player_->close();
	m1_pixel_pano_player_->play(panoData);
	
	emit SignalToShowGlWindow();
}


void playModeWgt::resizeMapControl()
{
	if (m_mapToolWgt != NULL)
	{
		m_mapToolWgt->move(this->width() - 320, 32);

		m_mapToolWgt->resize(320, height());
	}


	if (weather_peopleflow_!=NULL)
	{
		weather_peopleflow_->move(this->width() - 300, 32);
	}
}

void playModeWgt::onClosePlaySlot()
{
	close();	
	if (is_map_available_)
	{
		emit sigOnResetMapStatus();
		emit sigOnRePaintMap();
		this->hide();
	}
}

void playModeWgt::slotOnPicGroupClicked(bool checked)
{
	if (checked)
	{
		if (m_panoPointInfo.map_point_type != PANOSCENE_ON_LINE)
		{
			return;
		}

		if (m_mapToolWgt == NULL)
		{
			m_mapToolWgt = new mapToolWidget(this);
		}

		m_mapToolWgt->initData(m_panoPointInfo.sceneInfo);

		m_mapToolWgt->resize(320, height() - 180);

		m_mapToolWgt->move(this->width() - 320, 32);
		m_mapToolWgt->show();
		m_mapToolWgt->setMiniMapPage(ui->MapBtn_->isChecked());
	}
	else
	{
		m_mapToolWgt->slotOnHiddenPicGroup();
	}
}

void playModeWgt::onShowGlWindowSlot()
{
	//切换opengl画面
	ui->scrollArea_->setVisible(true);
	ui->initWidget->setVisible(false);


	if (sequencer_tip_wgt_ != NULL)
	{
		sequencer_tip_wgt_->deleteLater();
		sequencer_tip_wgt_ = NULL;
	}

	if (is_map_available_)
	{
		if (sequencer_wgt_ != NULL)
		{
			sequencer_wgt_->deleteLater();
			sequencer_wgt_ = NULL;
		}

		sequencer_wgt_ = new directionArrowWgt(this);
		sequencer_wgt_->resize(200, 200);
		sequencer_wgt_->move(width() / 2 - 100, height() - 200);
		sequencer_wgt_->setArrow(m_panoPointInfo);
		//消除场景切换的闪烁
		QTimer::singleShot(200, this, [&](){
			sequencer_wgt_->show();
		});
		connect(ViewSignal::instance(), SIGNAL(sigOnResizeMap()), this, SLOT(slotOnMoveSequencer()));
		connect(&SequencerManagerIns, SIGNAL(SignalToTrigArrowRotate(double, double)), sequencer_wgt_, SLOT(slotToTrigArrowRotate(double, double)), Qt::QueuedConnection);
	}

}

void playModeWgt::onCaptureSlot()
{
	if (is_playing_)
	{
		if (captureThread_ && captureThread_->joinable())
		{
			captureThread_->join();
		}
		captureThread_.reset(new boost::thread(&playModeWgt::CaptureThreadFunc, this));
		Feedback::instance()->maskUI(CAPTURE_SUCCESS);
	}
	else
	{
		//弹框
		Feedback::instance()->maskUI(CAPTURE_FAILED);
	}
}

void playModeWgt::onSetAutoRotateSlot()
{
	if (is_playing_)
	{
		if (!is_rotating_)
		{
			is_rotating_ = true;
			m1_pixel_pano_player_->setAutoRotate(true, 0.1);
			ui->autoCircleBtn_->setStyleSheet("#autoCircleBtn_{border-image:url(:/image/image/rotatec.png);}#autoCircleBtn_:pressed{margin:1px;}");
		}
		else
		{
			is_rotating_ = false;
			m1_pixel_pano_player_->setAutoRotate(false, 0.1);		
			ui->autoCircleBtn_->setStyleSheet("#autoCircleBtn_{border-image:url(:/image/image/rotate.png);}#autoCircleBtn_:pressed{margin:1px;}#autoCircleBtn_:hover{border-image:url(:/image/image/rotateb.png);}");

		
		}
	}

}

void playModeWgt::onOpenHtcViveSlot()
{
	if (!is_playing_)
	{
		return;
	}
	if (!is_htc_open_)
	{
		mutex_open_htc_.lock();
		is_htc_open_ = true;
		mutex_open_htc_.unlock();
	}
	else
	{
		mutex_open_htc_.lock();
		is_htc_open_ = false;
		mutex_open_htc_.unlock();
	}
}

void playModeWgt::slotOnOpenGunCam(SpyInfo_t spy_info)
{
	if (gunwgt_!=NULL)
	{
		gunwgt_->deleteLater();
		gunwgt_ = NULL;
	}
	gunwgt_ = new gunCamWgt();

	gunwgt_->move(mapToGlobal(QPoint(0, 0)).rx() + (width() - gunwgt_->width()) / 2, mapToGlobal(QPoint(0, 0)).ry() + (height() - gunwgt_->height()) / 2);
	gunwgt_->show();

	if (is_map_available_)
	{
		gunwgt_->play(spy_info);
	}
	else
	{
		gunwgt_->play(spy_info);
	}

}

void playModeWgt::slotOnOpenHotPic(QString path)
{
	if (gunwgt_ != NULL)
	{
		gunwgt_->deleteLater();
		gunwgt_ = NULL;
	}
	gunwgt_ = new gunCamWgt();

	gunwgt_->move(mapToGlobal(QPoint(0, 0)).rx() + (width() - gunwgt_->width()) / 2, mapToGlobal(QPoint(0, 0)).ry() + (height() - gunwgt_->height()) / 2);
	gunwgt_->show();

	gunwgt_->play(path);
}

void playModeWgt::onOpenBallCamSlot()
{
	if (!is_playing_)
	{
		return;
	}
	if (is_map_available_)
	{
		if (m_panoPointInfo.cameraInfo.m_PtzInfoList.size() == 0)
		{
			Log::Info("please bind ptz at first!");
			Feedback::instance()->maskUI(PTZ_NO_BIND);
			return;
		}
	}
	else
	{
		if (current_select_item_info_.m_PtzInfoList.size() == 0)
		{
			Log::Info("please bind ptz at first!");
			Feedback::instance()->maskUI(PTZ_NO_BIND);
			return;
		}
	}

	if (ballwgt_ == NULL)
	{
		ballwgt_ = new ballCamWgt(gl_view_screen_);//要继承glview，坑啊
		ballwgt_->setExchangeBtnVisible(false);
		ballwgt_->setSavePresetBtnVisible(false);

		connect(ballwgt_, SIGNAL(sigOnPTZPlayStatus(bool)), this, SLOT(slotOnPTZPlayStatus(bool)));
		connect(ballwgt_, SIGNAL(sigOnBindPTZWarning()), this, SLOT(slotOnBindPTZWarning()));
	}
	ballwgt_->setStyleSheet("background-color:#121212;");
	ballwgt_->resize(320, 180);
	ballwgt_->move(mapToGlobal(QPoint(0, 0)).rx() + (width() - ballwgt_->width()), mapToGlobal(QPoint(0, 0)).ry() + (height() - ballwgt_->height()));
	ballwgt_->show();

	if (is_map_available_)
	{
		ballwgt_->play(m_panoPointInfo.cameraInfo.m_PtzInfoList[0]);
	}
	else
	{
		ballwgt_->play(current_select_item_info_.m_PtzInfoList[0]);
	}


}

void playModeWgt::onOpenOptimizeSlot()
{
	if (!is_optimize_ok_)
	{
		return;
	}
	if (!is_playing_)
	{
		return;
	}
	is_optimize_ok_ = false;
	if (optimizePtsThread_ && optimizePtsThread_->joinable())
	{
		optimizePtsThread_->join();
	}
	optimizePtsThread_.reset(new boost::thread(&playModeWgt::thread_optimize_pts, this));
}

void playModeWgt::onSetGlLabelSlot(PLAY_STATUS play_status)
{
	switch (play_status)
	{
	case 	PLAY_STATUS_PTS_WT_CREATING:
	{
		ui->label_2->setText(tr("初次播放，正在生成拼接参数，请等待！"));
		break;
	}
	case PLAY_STATUS_CAPTURE_ERROR:
	{
		updatePlayListStatus();
		ui->label_2->setText(tr("抓图失败，请重试！"));
		emit sigOnReplayResetSlider();
		break;
	}
	case	PLAY_STATUS_PTS_WT_CREAT_FILE_ERROR:
	{		
		updatePlayListStatus();
		ui->label_2->setText(tr("拼接参数文件夹生成失败，请重试！"));
		break;
	}
	case	PLAY_STATUS_PTS_WT_PTS_ERROR:
	{
		ui->label_2->setText(tr("拼接参数生成失败，请确认相机是否标定，或重启服务器！"));
		break;
	}
	case	PLAY_STATUS_M1_PLAYER_SERVER_TYPE:
	{
		ui->label_2->setText(tr("播放器链接流媒体服务器失败，请检查服务器情况！"));
		break;
	}
	case	PLAY_STATUS_M1_PLAYER_STREAM_TYPE:
	{
		ui->label_2->setText(tr("播放器链加载流失败，请检查推流情况、重新打开！"));
		break;
	}
	case	PLAY_STATUS_M1_PLAYER_INIT_FFMPEG_TYPE:
	{
		ui->label_2->setText(tr("播放器初始化失败，请重试！"));
		break;
	}
	case PLAY_STATUS_REPUEST_SRS_STREAM:
	{
		ui->label_2->setText(QStringLiteral("正在向SRS请求数据！"));
		break;
	}
	case PLAY_STATUS_GET_SRS_STREAM_ERR:
	{
		ui->label_2->setText(QStringLiteral("播放器拉流失败，请重新请求！"));
		break;
	}
	case PLAY_STATUS_CALIBRATION_LOW_SCORE:
	{
		ui->label_2->setText(QStringLiteral("客户端标定评分过低，请重试或更新场景！"));
		break;
	}
	case PLAY_STATUS_CREATE_PTS_FAILED:
	{
		emit sigOnReplayResetSlider();
		updatePlayListStatus();
		ui->label_2->setText(QStringLiteral("生成拼接模板失败，请重新请求"));
		break;
	}
	case PLAY_STATUS_M1_ERROR:
	{
		emit sigOnReplayResetSlider();
		updatePlayListStatus();
		Feedback::instance()->maskUI(M1_WARNING);
		ui->label_2->setText(QStringLiteral("M1相机异常，请重启相机"));
		break;
	}
	case PLAY_STATUS_REQUEST_SRS_ERROR:
	{
		emit sigOnReplayResetSlider();
		updatePlayListStatus();
		ui->label_2->setText(QStringLiteral("SRS推流服务器异常，请重新请求"));
		break;
	}
	case PLAY_STATUS_SRS_NO_RESPONSE:
	{
		emit sigOnReplayResetSlider();
		updatePlayListStatus();
		ui->label_2->setText(QStringLiteral("SRS推流服务器无响应，请检查服务是否开启"));
		break;
	}
	case PLAY_STATUS_SOCKET_NO_RESPONSE:
	{
		emit sigOnReplayResetSlider();
		updatePlayListStatus();
		ui->label_2->setText(QStringLiteral("服务器无响应，请检查网络连接"));
		break;
	}
	case PLAY_STATUS_CHECK_STITCH_PARA:
	{
		ui->label_2->setText(QStringLiteral("正在校验本地拼接模板、参数"));
		break;
	}
	case PLAY_STATUS_CAPTURING:
	{
		ui->label_2->setText(QStringLiteral("正在抓取图片"));
		break;
	}
	case PLAY_STATUS_OPTIMIZE:
	{
		ui->label_2->setText(QStringLiteral("正在初次优化本地拼接模板"));
		break;
	}
	case PLAY_STATUS_CREAT_WT_MASK:
	{
		ui->label_2->setText(QStringLiteral("正在生成wt、mask图片"));
		break;
	}
	case PLAY_STATUS_CLIENT_CALIBRATION:
	{
		ui->label_2->setText(QStringLiteral("客户端重新标定中"));
		break;
	}
	case PLAY_STATUS_PVSID_ERROR:
	{
		ui->label_2->setText(QStringLiteral("设备异常，未检索到对应SRS的PVSID"));
		break;
	}
	case PLAY_STATUS_SERVER_ERROR:
	{
		ui->label_2->setText(QStringLiteral("通信服务器无响应，请检查服务器是否异常"));
		break;
	}
	default:
		break;
	}
}

void playModeWgt::OnSwitchPlatFlagSlot(bool play_flag)
{
	if (!is_playing_)
	{
		return;
	}
}


void playModeWgt::slotOnPTZPlayStatus(bool success)
{
	if (success)
	{
		is_ball_cam_open_ = true;
		ui->ballBtn_->setStyleSheet("#ballBtn_{border-image:url(:/image/image/ballc.png);}#ballBtn_:pressed{margin:1px};");
	}
	else
	{
		is_ball_cam_open_ = false;
		ui->ballBtn_->setStyleSheet("#ballBtn_{border-image:url(:/image/image/ball.png);}#ballBtn_:pressed{margin:1px;}#ballBtn_ :hover{border-image:url(:/image/image/ballb.png);}");
		ballwgt_->hide();
	}
	emit sigOnBallCamBtnClicked(is_ball_cam_open_);
	QTimer::singleShot(20, this, SLOT(updatePos()));
}


void playModeWgt::slotOnRequestGetBandWidth()
{
	if (select_pvs_device_.isEmpty())
	{
		Log::Info("current no stream is playing!");
		return;
	}

	PVSManageTable_t api_detu;
	memcpy(api_detu.pvsID, select_pvs_device_.toLocal8Bit().data(), API_ARRAY_LEN);
	api_detu.nInputBandWidth = 0;
	api_detu.nOuntputBandWidth = 0;
	api_detu.nStream1Status = 0;
	api_detu.nStream2Status = 0;

	protocol_head_t api_head;
	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_CLIENT_GET_BANDWIDTH;
	api_head.nDataLen = api_detu.get_size();
	api_head.nResult = 0x00;
	api_head.nStreamId = 0;
	api_head.nEndFlags = 0xFA;

	Log::Info("client request bandWidth for pvs : %s", select_pvs_device_.toLocal8Bit().data());
	response res(api_head.get_size() + api_detu.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
	response_add_resprotocol<PVSManageTable_t>(res, &api_detu);
	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}


void playModeWgt::OnSwitchStreamSlot(bool checked)
{
	if (is_rotating_)
	{
		Feedback::instance()->maskUI(ROTATING_NO_SWITCH);
		ui->switchStreamBtn_->setChecked(false);
		ui->switchStreamBtn_->setStyleSheet("#switchStreamBtn_{border-image:url(:/image/image/hdclose.png);}#switchStreamBtn_:pressed{margin:1px;}#switchStreamBtn_:checked{border-image:url(:/image/image/hdopen.png);}");
		return;
	}
	if (checked)
	{
		if (DetuPVMSIni::getGlobalStreamType())
		{
			ui->switchStreamBtn_->setChecked(false);
			Feedback::instance()->maskUI(WARN_ONE_STREAM);
			return;
		}
		switch (play_window_type_)
		{
		case PREVIEW:
			m_preview_stream_type = 0;
			break;
		case REPLAY:
			m_replay_stream_type = 2;
			break;
		case MAP_PLAY:
			m_map_preview_stream_type = 4;
			break;
		case MAP_REPLAY:
			m_map_replay_stream_type = 6;
			break;
		default:
			break;
		}
		DetuPVMSIni::setGlobalStreamType(true);
	}
	else
	{
		if (!m_subStream_open)
		{
			Log::Info("subStream has been closed!");
			ui->switchStreamBtn_->setChecked(true);
			Feedback::instance()->maskUI(WARN_SUBSTREAM_DELETED);
			return;
		}
		switch (play_window_type_)
		{
		case PREVIEW:
			m_preview_stream_type = 1;
			break;
		case REPLAY:
			m_replay_stream_type = 3;
			break;
		case MAP_PLAY:
			m_map_preview_stream_type = 5;
			break;
		case MAP_REPLAY:
			m_map_replay_stream_type = 7;
			break;
		default:
			break;
		}
		DetuPVMSIni::setGlobalStreamType(false);
	}
	if (!is_playing_)
	{
		Log::Info("playModeWgt::slotOnSwitchStream(): !is_playing_");
		return;
	}
	if (!is_stitch_file_ok_)
	{
		Log::Info("playModeWgt::slotOnSwitchStream(): !is_stitch_file_ok_");
		return;
	}
	sequencer();
   QTimer::singleShot(50, this, [&](){
	   switch (play_window_type_)
	   {
	   case PREVIEW:
		   CreatStitchFiles(PREVIEW, 0);
		   break;
	   case REPLAY:
		   CreatStitchFiles(REPLAY, m_global_video_time_);
		   break;
	   case MAP_PLAY:
		   CreatStitchFiles(MAP_PLAY, 0);
		   break;
	   case MAP_REPLAY:
		   CreatStitchFiles(MAP_REPLAY, m_global_video_time_);
		   break;
	   default:
		   break;
	   }
   
   });
}
void playModeWgt::OnOpenPanoMapSlot(bool checked)
{
	if (checked)
	{
// 		if (m_mapToolWgt == NULL)
// 		{
// 			m_mapToolWgt = new mapToolWidget(this);
// 			connect(m_mapToolWgt, SIGNAL(sigOnHiddenMiniMap()), this, SLOT(slotOnHiddenMiniMap()));
// 			connect(m_mapToolWgt, SIGNAL(sigOnHiddenPicGroup()), this, SLOT(slotOnHiddenPicGroup()));
// 
// 			connect(m_mapToolWgt, SIGNAL(SignalToSetSwtichScreen(int)), this, SLOT(slotOnSetSwtichScreen(int)));
// 		}
// 
// 		connect(ViewSignal::instance(), SIGNAL(sigOnMiniMapPointClicked(int)), this, SLOT(slotOnSequencer(int)));
// 		connect(&SequencerManagerIns, SIGNAL(SignalToTrigArrowRotate(double, double)), m_mapToolWgt, SLOT(slotToTrigArrowRotate(double, double)), Qt::QueuedConnection);
// 
// 
// 		m_mapToolWgt->resize(320, height());
// 
// 
// 		m_mapToolWgt->move(this->width() - 320, 32);
// 		m_mapToolWgt->show();
// 		m_mapToolWgt->setCurrPlayInfo(m_panoPointInfo);
// 		m_mapToolWgt->setBackground();
// 		m_mapToolWgt->setPicGroupPage(picGroupBtn_->isChecked());
// 
// 
// 		//启动rfid监听器
// 		if (rfid_reader_ != NULL)
// 		{
// 			rfid_reader_->close();
// 			rfid_reader_->deleteLater();
// 			rfid_reader_ = NULL;
// 		}
// 		rfid_reader_ = new RFIDReader();
// 		rfid_reader_->Open();
// 
// 		//启动门禁管理
// 		if (door_manager_ != NULL)
// 		{
// 			door_manager_->deleteLater();
// 			door_manager_ = NULL;
// 		}
// 		door_manager_ = new DoorManager();
// 
// 		connect(&PVMSEventManagerManagerIns, SIGNAL(sigOnCheckWarningBoard()), this, SLOT(slotOnCheckWarningBoard()));

		//启动天气人流假数据
		if (weather_peopleflow_ != NULL)
		{
			weather_peopleflow_->deleteLater();
			weather_peopleflow_ = NULL;
		}
		weather_peopleflow_ = new weather_peopleflow(this);
		weather_peopleflow_->move(this->width() - 300, 32);
		weather_peopleflow_->show();
	}
	else
	{

		weather_peopleflow_->hide();
		weather_peopleflow_->deleteLater();
		weather_peopleflow_ = NULL;

// 		m_mapToolWgt->hide();
// 		m_mapToolWgt->deleteLater();
// 		m_mapToolWgt = NULL;
// 
// 		//关闭rfid
// 		rfid_reader_->close();
// 		rfid_reader_->deleteLater();
// 		rfid_reader_ = NULL;
// 
// 		door_manager_->deleteLater();
// 		door_manager_ = NULL;

	}


}

void playModeWgt::OnOpenMapReplaySlot()
{
	if (!is_replaying_)
	{
		//设置标志位，关闭当前播放
		is_replaying_ = true;
		ui->ReplayBtn_->setStyleSheet("#ReplayBtn_{border-image:url(:/image/image/history.png);}#ReplayBtn_:pressed{margin:1px;}");
		close();

		//通知打开回放控制，并且查询回放
		emit sigOnOpenReplayCtrl();
	}
	else
	{
		is_replaying_ = false;
		ui->ReplayBtn_->setStyleSheet("#ReplayBtn_{border-image:url(:/image/image/history.png);}#ReplayBtn_:pressed{margin:1px;}#ReplayBtn_:hover{border-image:url(:/image/image/historyb.png);}");

		//关闭当前回放播放，播放原视频，或场景
		emit sigOnCloseReplayCtrl();
	}
}

void playModeWgt::slotOnHiddenMiniMap()
{
	ui->MapBtn_->setChecked(false);
}

void playModeWgt::slotOnHiddenPicGroup()
{
	picGroupBtn_->setChecked(false);
}

void playModeWgt::slotOnUpdate()
{
	if (timeLbl_ != NULL)
	{
		timeLbl_->move(mapToGlobal(QPoint(0, 0)).rx(), mapToGlobal(QPoint(0, 0)).ry() + (height() - timeLbl_->height()) - 26);
	}
}

void playModeWgt::slotOnUpdateStreamInfo()
{
	if (streamInfoLbl_ != NULL)
	{
		streamInfoLbl_->move(mapToGlobal(QPoint(0, 0)).rx(), mapToGlobal(QPoint(0, 0)).ry() + (height() - streamInfoLbl_->height() - 10));
	}
}

void playModeWgt::slotOnReportUI(PLAY_STATUS play_status, int errorNo)
{
	switch (errorNo)
	{
	case PLAY_ERROR:
	{
		updatePlayListStatus();
		onSetGlLabelSlot(play_status);
		break;
	}
	case PLAY_COMPLETE:
	{
		//更新GLWindow和UI
		emit SignalToSetGlStop();
		break;
	}
	case STREAM_ERROR:
	{
		updatePlayListStatus();
		onSetGlLabelSlot(play_status);
		Feedback::instance()->maskUI(STREAM_ERR);
		break;
	}
	case LOW_SCORE:
	{
		updatePlayListStatus();
		onSetGlLabelSlot(play_status);
		Feedback::instance()->maskUI(CALIBRATION_LOW_SCORE);
		emit sigOnReplayResetSlider();
		break;
	}
	case CREATE_FILE_FAILED:
	{
		updatePlayListStatus();
		onSetGlLabelSlot(play_status);
		Feedback::instance()->maskUI(CREATE_PTS_FILE_FAILED);
		emit sigOnReplayResetSlider();
		break;
	}
	default:
		break;
	}
}

void playModeWgt::srsConn()
{
	//不要在构造函数初始化连接，会乱窜
	switch (play_window_type_)
	{
	case PREVIEW:
		connect(HttpSignal::instance(), SIGNAL(sigOnGetSrsInfo(int, bool)), this, SLOT(slotOnGetSrsInfo(int, bool)));
		connect(HttpSignal::instance(), SIGNAL(sigOnNetWorkError(int)), this, SLOT(slotOnNetWorkError(int)));
		connect(HttpSignal::instance(), SIGNAL(sigOnRequestNetWork()), this, SLOT(slotOnRequestNetWork()));
		connect(HttpSignal::instance(), SIGNAL(sigOnPVSIDError()), this, SLOT(slotOnPVSIDError()));
		break;
	case REPLAY:
		connect(HttpSignal::instance(), SIGNAL(sigOnReplayGetSrsInfo(int, bool)), this, SLOT(slotOnGetSrsInfo(int, bool)));
		connect(HttpSignal::instance(), SIGNAL(sigOnReplayNetWorkError(int)), this, SLOT(slotOnNetWorkError(int)));
		connect(HttpSignal::instance(), SIGNAL(sigOnReplayRequestNetWork()), this, SLOT(slotOnRequestNetWork()));
		connect(HttpSignal::instance(), SIGNAL(sigOnReplayPVSIDError()), this, SLOT(slotOnPVSIDError()));
		break;
	case MAP_PLAY:
		connect(HttpSignal::instance(), SIGNAL(sigOnMapGetSrsInfo(int, bool)), this, SLOT(slotOnGetSrsInfo(int, bool)));
		connect(HttpSignal::instance(), SIGNAL(sigOnMapNetWorkError(int)), this, SLOT(slotOnNetWorkError(int)));
		connect(HttpSignal::instance(), SIGNAL(sigOnMapRequestNetWork()), this, SLOT(slotOnRequestNetWork()));
		connect(HttpSignal::instance(), SIGNAL(sigOnMapPVSIDError()), this, SLOT(slotOnPVSIDError()));
		break;
	case MAP_REPLAY:
		connect(HttpSignal::instance(), SIGNAL(sigOnMapBackGetSrsInfo(int, bool)), this, SLOT(slotOnGetSrsInfo(int, bool)));
		connect(HttpSignal::instance(), SIGNAL(sigOnMapBackNetWorkError(int)), this, SLOT(slotOnNetWorkError(int)));
		connect(HttpSignal::instance(), SIGNAL(sigOnMapBackRequestNetWork()), this, SLOT(slotOnRequestNetWork()));
		connect(HttpSignal::instance(), SIGNAL(sigOnMapBackPVSIDError()), this, SLOT(slotOnPVSIDError()));
		break;
	default:
		break;
	}
}

void playModeWgt::srsDisConn()
{
	switch (play_window_type_)
	{
	case PREVIEW:
		disconnect(HttpSignal::instance(), SIGNAL(sigOnGetSrsInfo(int, bool)), this, SLOT(slotOnGetSrsInfo(int, bool)));
		disconnect(HttpSignal::instance(), SIGNAL(sigOnNetWorkError(int)), this, SLOT(slotOnNetWorkError(int)));
		disconnect(HttpSignal::instance(), SIGNAL(sigOnRequestNetWork()), this, SLOT(slotOnRequestNetWork()));
		disconnect(HttpSignal::instance(), SIGNAL(sigOnPVSIDError()), this, SLOT(slotOnPVSIDError()));
		break;
	case REPLAY:
		disconnect(HttpSignal::instance(), SIGNAL(sigOnReplayGetSrsInfo(int, bool)), this, SLOT(slotOnGetSrsInfo(int, bool)));
		disconnect(HttpSignal::instance(), SIGNAL(sigOnReplayNetWorkError(int)), this, SLOT(slotOnNetWorkError(int)));
		disconnect(HttpSignal::instance(), SIGNAL(sigOnReplayRequestNetWork()), this, SLOT(slotOnRequestNetWork()));
		disconnect(HttpSignal::instance(), SIGNAL(sigOnReplayPVSIDError()), this, SLOT(slotOnPVSIDError()));
		break;
	case MAP_PLAY:
		disconnect(HttpSignal::instance(), SIGNAL(sigOnMapGetSrsInfo(int, bool)), this, SLOT(slotOnGetSrsInfo(int, bool)));
		disconnect(HttpSignal::instance(), SIGNAL(sigOnMapNetWorkError(int)), this, SLOT(slotOnNetWorkError(int)));
		disconnect(HttpSignal::instance(), SIGNAL(sigOnMapRequestNetWork()), this, SLOT(slotOnRequestNetWork()));
		disconnect(HttpSignal::instance(), SIGNAL(sigOnMapPVSIDError()), this, SLOT(slotOnPVSIDError()));
		break;
	case MAP_REPLAY:
		disconnect(HttpSignal::instance(), SIGNAL(sigOnMapBackGetSrsInfo(int, bool)), this, SLOT(slotOnGetSrsInfo(int, bool)));
		disconnect(HttpSignal::instance(), SIGNAL(sigOnMapBackNetWorkError(int)), this, SLOT(slotOnNetWorkError(int)));
		disconnect(HttpSignal::instance(), SIGNAL(sigOnMapBackRequestNetWork()), this, SLOT(slotOnRequestNetWork()));
		disconnect(HttpSignal::instance(), SIGNAL(sigOnMapBackPVSIDError()), this, SLOT(slotOnPVSIDError()));
		break;
	default:
		break;
	}
}

void playModeWgt::slotOnGetSrsInfo(int id, bool state)
{
	srsDisConn();			//关闭SRS请求链接
	if (state)
	{
		srs_http_no_response = 0;
		current_stitch_status_ = STITCH_STATUS_CHECK_PARA;
		this->StitchStatusMachine();
		//获取srs状态成功，可以播放
		this->play();
	}
	else
	{
		Feedback::instance()->maskUI(SRS_ERROR);
		emit SignalToSetGlLabel(PLAY_STATUS_REQUEST_SRS_ERROR);
		Log::Info("srs server no stream!");

		current_stitch_status_ = STITCH_STATUS_START;
		return;
	}

}

void playModeWgt::slotOnNetWorkError(int error)
{
	//网络异常通知
	switch (error)
	{
	case 0:
		Log::Debug("http network no response!");
		emit SignalToSetGlLabel(PLAY_STATUS_SRS_NO_RESPONSE);
		Feedback::instance()->maskUI(SRS_NO_RESPONSE);
		break;
	case 1:
		Log::Debug("http network return error!");
		emit SignalToSetGlLabel(PLAY_STATUS_REQUEST_SRS_ERROR);
		Feedback::instance()->maskUI(SRS_ERROR);
		break;
	}
	srsDisConn();			//关闭SRS请求链接
	current_stitch_status_ = STITCH_STATUS_START;
	return;
}

void playModeWgt::slotOnNetWorkResponse()
{
	QTimer::singleShot(5000, this, SLOT(slotOnNoResponseMessage()));
}

void playModeWgt::slotOnNoResponseMessage()
{
	//这里有个坑，信号乱窜了
	if (net_no_response_&&is_playing_)
	{
		Log::Info("socket net no response!");
		SignalToSetGlLabel(PLAY_STATUS_SOCKET_NO_RESPONSE);
		Feedback::instance()->maskUI(SRS_NO_RESPONSE);

		//将状态机置成初始状态
		srsDisConn();			//关闭SRS请求链接
		current_stitch_status_ = STITCH_STATUS_START;
		return;
	}
}

void playModeWgt::slotOnRequestNetWork()
{
	srs_http_no_response++;
	if (srs_http_no_response == 3)
	{
		Feedback::instance()->maskUI(SRS_ERROR);
		emit SignalToSetGlLabel(PLAY_STATUS_REQUEST_SRS_ERROR);

		//将状态机置成初始状态
		srsDisConn();			//关闭SRS请求链接
		current_stitch_status_ = STITCH_STATUS_START;

		return;
	}
	//状态机流转到获取SRS的回调
	current_stitch_status_ = STITCH_STATUS_GET_SRS;
	this->StitchStatusMachine();
}

void playModeWgt::slotOnPVSIDError()
{
	emit SignalToSetGlLabel(PLAY_STATUS_PVSID_ERROR);

	//将状态机置成初始状态
	current_stitch_status_ = STITCH_STATUS_START;
}

void playModeWgt::slotOnSwitchViewMode(PanoViewMode view_mode)
{
	if (!is_playing_)
	{
		return;
	}
	m_panoViewMode = view_mode;
	m1_pixel_pano_player_->setViewMode(view_mode);
}


void playModeWgt::slotOnSequencer(int id)
{
	if (id == m_panoPointInfo.curr_id)
	{
		return;
	}
	if (id == -1)
	{
		Log::Info("playModeWgt::slotOnSequencer(int id):-1");
		return;
	}
	PanoMapPointInfo_t temp_point;
	QList<PanoMap_t> temp_map_list;
	temp_map_list = MapPointListManagerIns.getMapList();

	for (int i = 0; i < temp_map_list[0].panoramaList.size(); ++i)
	{
		if (temp_map_list[0].panoramaList[i].curr_id == id)
		{
			temp_point = temp_map_list[0].panoramaList[i];
		}
	}

	if (temp_point.onMapFlag==false)
	{
		Feedback::instance()->maskUI(NO_PREV_POINT);
		return;
	}
	if (temp_point.map_point_type == DEVICE_ON_LINE)
	{
		if (temp_point.cameraInfo.status == 0)
		{
			Feedback::instance()->maskUI(OFF_LINE_NO_PLAY);
			return;
		}
	}

	sequencer();
	is_sequencer_play_ = true;

	//切换播放资源，切换当前设备信息
	m_panoPointInfo = temp_point;

	//开启动画效果
	if (m_panoPointInfo.map_point_type == DEVICE_ON_LINE || m_panoPointInfo.map_point_type == DEVICE_OFF_LINE)
	{
		m1_pixel_pano_player_->setanimationfov(15, 4, LinearEaseOuts);
	}
	else
	{
		m1_pixel_pano_player_->setanimationfov(15, 1, LinearEaseOuts);
	}
	//播放
	QTimer::singleShot(100, this, [&]()
	{
		if (m_panoPointInfo.map_point_type == DEVICE_ON_LINE || m_panoPointInfo.map_point_type == DEVICE_OFF_LINE)
		{
			setIsPlaying(true);
			setMapPlayConfig(m_panoPointInfo);
			CreatStitchFiles(MAP_PLAY, 0); 
		}
		else
		{
			setIsPlaying(true);
			setMapScenePlayConfig(m_panoPointInfo);
		}
	});
	if (miniMap_!=NULL)
	{
		miniMap_->setCurrPlayInfo(m_panoPointInfo);
		miniMap_->drawAllMiniPoint();
	}

}


void playModeWgt::slotOnMoveSequencer()
{
	if (sequencer_wgt_!=NULL)
	{
		sequencer_wgt_->move(width() / 2 - 100, height() - 200 - 136);
	}

	if (miniMap_ != NULL)
	{
		miniMap_->move(width() - miniMap_->width(), ui->topWidget_->height());
	}

	if (ballwgt_ != NULL)
	{
		ballwgt_->resize(320, 180);
		ballwgt_->move(mapToGlobal(QPoint(0, 0)).rx() + (width() - ballwgt_->width()), mapToGlobal(QPoint(0, 0)).ry() + (height() - ballwgt_->height()));
		ballwgt_->setPosMove();
	}
}



void playModeWgt::slotOnSetSwtichScreen(int button_num)
{
	switch (button_num)
	{
	case 1:
	{		//画面跳转
			  float fov;
			  float hlookat;
			  float vlookat;
			  m1_pixel_pano_player_->getClipsparam(&fov, &hlookat, &vlookat);//get clips param  167.914932 -31.5699749
			  m1_pixel_pano_player_->setClipsparam(fov, 167, -31, 0, 0);
			  break;
	}	
	case 2:
	{
			  //画面跳转
			  float fov;
			  float hlookat;
			  float vlookat;
			  m1_pixel_pano_player_->getClipsparam(&fov, &hlookat, &vlookat);//get clips param  6  -17
			  m1_pixel_pano_player_->setClipsparam(fov, 6, - 17, 0, 0);
			  break;
		break;
	}	
	case 3:
	{//画面跳转
			  float fov;
			  float hlookat;
			  float vlookat;
			  m1_pixel_pano_player_->getClipsparam(&fov, &hlookat, &vlookat);//get clips param  67 -14
			  m1_pixel_pano_player_->setClipsparam(fov, 67, -14, 0, 0);
			  break;
		break;
	}

	case 4:
	{//画面跳转
			  float fov;
			  float hlookat;
			  float vlookat;
			  m1_pixel_pano_player_->getClipsparam(&fov, &hlookat, &vlookat);//get clips param  -104 -19
			  m1_pixel_pano_player_->setClipsparam(fov, -104, -19, 0, 0);
			  break;
			  break;
	}
	default:
		break;
	}

}

void playModeWgt::slotOnCheckWarningBoard()
{
	//检测警告牌是否有异样
	if (is_playing_ && is_map_available_)
	{
		QString list_path = QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/Map/warning_board") + "/target.txt";
		calibrater_and_capturer_->readList(list_path);
		//MMD_RESULT res = calibrater_and_capturer_->CheckWarningBoard(m_av_frame_sync_list_);


		if (checkWarningBoradThread_ && checkWarningBoradThread_->joinable())
		{
			checkWarningBoradThread_->join();
		}
		checkWarningBoradThread_.reset(new boost::thread(&PanoCalibraterAndCapturer::CheckWarningBoard, calibrater_and_capturer_, m_av_frame_sync_list_));
	}
}


void playModeWgt::updatePos()
{
	setPosMove();
}

void playModeWgt::slotOnBindPTZWarning()
{
	emit sigOnBindPTZWarning();
	if (ballwgt_ != NULL)
	{
		ballwgt_->hide();
	}
}

void playModeWgt::slotOnControlPlayerRecordFlv()
{
	if (is_playing_ && m1_player_)
	{
		m1_player_->SetRecordTag(DetuPVMSIni::getSaveFlvTag());
	}
}

void playModeWgt::slotOnHandleSubStreamMessage(bool open, QString pvsId, int id)
{
	if (current_select_item_info_.serialNo ==pvsId)
	{
		m_subStream_open = open;
	}
}

void playModeWgt::setStitchStatus(StitchStatus stitch_status)
{
	m_first_frames = true;
	if (!play_window_type_)
	{
		socketRequest::instance()->requestOnAskForStreamInfo(m_preview_stream_type, current_select_item_info_);
	}
	RTMP_URL_ = QString::fromLocal8Bit((const char*)TcpDataManagerIns.GetRequestTime()->szRtmpURL);

	//状态机流转到获取SRS的回调
	net_no_response_ = false;
	current_stitch_status_ = stitch_status;
	this->StitchStatusMachine();
}

void playModeWgt::StitchStatusMachine()
{
	switch (current_stitch_status_)
	{
	case STITCH_STATUS_START:
	{
		break;
	}
	case STITCH_STATUS_COMMUNICATION:
	{		
		this->StitchStatusCommunication();
		break;
	}
	case STITCH_STATUS_GET_SRS:
	{
		emit SignalToSetGlLabel(PLAY_STATUS_REPUEST_SRS_STREAM);
		this->StitchStatusGetSrs();
		break;
	}
	case STITCH_STATUS_CHECK_PARA:
	{
		emit SignalToSetGlLabel(PLAY_STATUS_CHECK_STITCH_PARA);
		this->StitchStatueCheckStitchPara();
		break;
	}
	case STITCH_STATUS_CAPTURE:
	{
		emit SignalToSetGlLabel(PLAY_STATUS_CAPTURING);
		this->StitchStatusCapture();
		break;
	}
	case STITCH_STATUS_OPTIMIZE:
	{
		emit SignalToSetGlLabel(PLAY_STATUS_OPTIMIZE);
		this->StitchStatusOptimize();
		break;
	}
	case STITCH_STATUS_CREAT_WT:
	{
		emit SignalToSetGlLabel(PLAY_STATUS_CREAT_WT_MASK);
		this->StitchStatusCreatWt();
		break;
	}
	case STITCH_STATUS_CALIBRATION:
	{
		emit SignalToSetGlLabel(PLAY_STATUS_CLIENT_CALIBRATION);
		this->StitchStatusCalibration();
		break;
	}
	default:
		break;
	}
}

void playModeWgt::mousePressEvent(QMouseEvent *event)
{
	QWidget::mousePressEvent(event);
}

void playModeWgt::mouseMoveEvent(QMouseEvent *event)
{

	QWidget::mouseMoveEvent(event);
}

void playModeWgt::mouseReleaseEvent(QMouseEvent *event)
{
	if (is_map_available_)
	{
		sequencer_angle_ = BallCamLinkageManagerIns.getYaw() - m_panoPointInfo.initial_angle;
	}
	QWidget::mouseReleaseEvent(event);
}

void playModeWgt::StitchStatusCommunication()
{
	int streamid;
	switch (play_window_type_)
	{
	case PREVIEW:
		streamid = m_preview_stream_type;
		break;
	case REPLAY:
		streamid = m_replay_stream_type;
		break;
	case MAP_PLAY:
		streamid = m_map_preview_stream_type;
		break;
	case MAP_REPLAY:
		streamid = m_map_replay_stream_type;
		break;
	}

	if (is_map_available_)
	{	
		//初始化视屏请求线程
		socketRequest::instance()->requestOnAskFroVideo(play_window_type_, replay_request_time_, m_panoPointInfo, streamid);
	}
	else
	{
		//初始化视屏请求线程
		socketRequest::instance()->requestOnAskFroVideo(play_window_type_, replay_request_time_, current_select_item_info_, streamid);
	}
	//超時等待
	connect(this, SIGNAL(sigOnNetWorkResponse()), this, SLOT(slotOnNetWorkResponse()));
	emit sigOnNetWorkResponse();
}

void playModeWgt::StitchStatusGetSrs()
{
	srsConn();			//打开SRShttp请求连接
	//500毫秒后开启，不能客户端sleep500，会卡住动画效果，坑
	QTimer::singleShot(500, this, [&](){
		QString sUrl = QString("http://%1:1985/api/v1/streams/").arg(DetuPVMSIni::getServerIP());
		QString streamType;
		QString pvsId;
		switch (play_window_type_)
		{
		case PREVIEW:
			streamType = QString::number(m_preview_stream_type);
			pvsId = current_select_item_info_.serialNo + "_" + streamType;
			break;
		case REPLAY:
			streamType = QString::number(m_replay_stream_type);
			pvsId = current_select_item_info_.serialNo + "_" + streamType;
			break;
		case MAP_PLAY:
			if (m_map_preview_stream_type == 4)
			{
				streamType = "0";
			}
			else if (m_map_preview_stream_type == 5)
			{
				streamType = "1";
			}
			pvsId = m_panoPointInfo.cameraInfo.serialNo + "_" + QString::number(m_map_preview_stream_type);
			break;
		case MAP_REPLAY:
			if (m_map_replay_stream_type == 6)
			{
				streamType = "0";
			}
			else if (m_map_replay_stream_type == 7)
			{
				streamType = "1";
			}
			pvsId = m_panoPointInfo.cameraInfo.serialNo + "_" + QString::number(m_map_replay_stream_type);
			break;
		default:
			break;
		}
		Log::Info("Http request sUrl:%s and streamType : %s pvsid : %s", sUrl.toLocal8Bit().data(), streamType.toLocal8Bit().data(), pvsId.toLocal8Bit().data());
		HttpClient::instance()->getSrsStreamRequest(sUrl, play_window_type_, pvsId, streamType);
	});

}

VOID playModeWgt::StitchStatueCheckStitchPara()
{
	QString initFilePath = QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/pts/" + select_m1_device_);
	QDir dir(initFilePath);
	QFile pat_pts(initFilePath + "/pat.pts");

	dir.setFilter(QDir::Files | QDir::NoSymLinks);
	QFileInfoList list = dir.entryInfoList();

	is_stitch_file_ok_ = false;
	is_init_caprure_ = false;
	/************************************************************************/
	/*
	1.判断PTS文件大小是否 > 0
	2.假设PTS == 0 或者不存在，则   STITCH_STATUS_CAPTURE
	3.假设PTS > 0，则   Md5校验
	4.校验PASS    PLAY
	5.校验Reject  build Weight Mask
	/************************************************************************/
	if (!pat_pts.exists() || pat_pts.size() == 0)
	{
		Log::Info("StitchStatueCheckStitchPara Files not exists!");
		emit SignalToSetGlLabel(PLAY_STATUS_PTS_WT_CREATING);
		if (!dir.mkpath(initFilePath))
		{
			emit sigOnReportUI((PLAY_STATUS)PLAY_STATUS_PTS_WT_CREAT_FILE_ERROR, CREATE_FILE_FAILED);
			current_stitch_status_ = STITCH_STATUS_START;
			return;
		}
		current_stitch_status_ = STITCH_STATUS_CAPTURE;
		this->StitchStatusMachine();
	}
	else
	{
		Log::Info("StitchStatueCheckStitchPara Files exists and 16!");
		QString pts_path = initFilePath + "/pat.pts";
		QString md5_path = initFilePath + "/md5.txt";

		//先保存一个md5文件
		QFile md5_txt(md5_path);
		if (!md5_txt.exists())
		{
			md5_txt.open(QIODevice::ReadWrite);
			md5_txt.close();
		}

		//校验通过
		if (MyMd5Ins.CheckMd5(pts_path, md5_path))
		{
			Log::Info("StitchStatueCheckStitchPara OK!");
			current_stitch_status_ = STITCH_STATUS_START;
			is_stitch_file_ok_ = true;
			is_init_caprure_ = true;
			return;
		}
		else
		{
			Log::Info("StitchStatueCheckStitchPara Failed!");
			current_stitch_status_ = STITCH_STATUS_CREAT_WT;
			this->StitchStatusMachine();
		}
	}
}

void playModeWgt::StitchStatusCapture()
{
	if (creatPtsThread_ && creatPtsThread_->joinable())
	{
		creatPtsThread_->join();
	}
	creatPtsThread_.reset(new boost::thread(&playModeWgt::thread_capture, this));
}

void playModeWgt::StitchStatusCreatWt()
{
	int sts = calibrater_and_capturer_->CreatMaskAndWeight();
	current_stitch_status_ = STITCH_STATUS_START;

	if (sts != PLAY_STATUS_PTS_WT_OK)
	{
		emit SignalToSetGlLabel(PLAY_STATUS_CREATE_PTS_FAILED);
		current_stitch_status_ = STITCH_STATUS_START;
		return;
	}
	mutex_stitch_ok_.lock();
	is_stitch_file_ok_ = true;
	//更新GLWindow和UI
	current_stitch_status_ = STITCH_STATUS_START;
	mutex_stitch_ok_.unlock();
}

void playModeWgt::StitchStatusOptimize()
{
	PLAY_STATUS sts=(PLAY_STATUS) calibrater_and_capturer_->OptimizePts();
	switch (sts)
	{
	case PLAY_STATUS_PTS_WT_PTS_ERROR:
	{
		emit SignalToSetGlLabel(PLAY_STATUS_M1_ERROR);
		current_stitch_status_ = STITCH_STATUS_START;
		break;
	}
	case PLAY_STATUS_OPTIMIZE_HIGH_SCORE:
	{
		current_stitch_status_ = STITCH_STATUS_CREAT_WT;
		this->StitchStatusMachine();
		break;
	}
	case PLAY_STATUS_OPTIMIZE_LOW_SCORE:
	{		
		current_stitch_status_ = STITCH_STATUS_CALIBRATION;
		this->StitchStatusMachine();
		break;
	}
	default:
		break;
	}

}

void playModeWgt::StitchStatusCalibration()
{
	PLAY_STATUS sts = (PLAY_STATUS)calibrater_and_capturer_->Calibration();
	switch (sts)
	{
	case 	PLAY_STATUS_CALIBRATION_HIGH_SCORE:			// 客户端标定评分ok
	{
		current_stitch_status_ = STITCH_STATUS_CREAT_WT;
		this->StitchStatusMachine();
		break;
	}
	case	PLAY_STATUS_CALIBRATION_LOW_SCORE:				// 客户端标定评分过低，请重试或更新场景
	{
		emit sigOnReportUI((PLAY_STATUS)PLAY_STATUS_CALIBRATION_LOW_SCORE, LOW_SCORE);
		current_stitch_status_ = STITCH_STATUS_START;
		break;
	}
	case	PLAY_STATUS_CALIBRATION_ERROR:				// 客户端标定评分出错
	{
		current_stitch_status_ = STITCH_STATUS_START;
		updatePlayListStatus();
		emit sigOnReplayResetSlider();		
		break;
	}
	default:
		break;
	}
}

void playModeWgt::onPanoPlayerLoading()
{

}

void playModeWgt::onPanoPlayerLoaded()
{
	std::vector<std::string>weight_path;
	weight_path.resize(4);
	weight_path[0] = (QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/pts") + "/" + select_m1_device_ + "/wt0.jpg").toStdString();
	weight_path[1] = (QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/pts") + "/" + select_m1_device_ + "/wt1.jpg").toStdString();
	weight_path[2] = (QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/pts") + "/" + select_m1_device_ + "/wt2.jpg").toStdString();
	weight_path[3] = (QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/pts") + "/" + select_m1_device_ + "/wt3.jpg").toStdString();

	m1_pixel_pano_player_->setweight(weight_path);
	//判断相机安装方向
	m1_pixel_pano_player_->setreverse(current_select_item_info_.is_up_down);

	//地图模式
	if (is_map_available_)
	{
		if (m_panoPointInfo.map_point_type == PANOSCENE_ON_LINE || m_panoPointInfo.map_point_type == PANOSCENE_OFF_LINE)
		{
			m1_pixel_pano_player_->setreverse(!m_panoPointInfo.sceneInfo.is_up_down);
		}
		else
		{
			m1_pixel_pano_player_->setreverse(!m_panoPointInfo.cameraInfo.is_up_down);
		}

	}
}

void playModeWgt::onPanoPlayerError(PanoPlayerErrorCode errorCode)
{

}

void playModeWgt::onPanoPlayerPluginStatusChanged(PanoPluginStatus status, string tip)
{

}

void playModeWgt::onPanoPlayerPluginProgressChanged(long playProgress, long bufferProgress, long duration)
{

}

void playModeWgt::onPanoPlayerPluginStatisticsDataChanged(PanoPluginStatisticsData* statisticsData)
{

}

void playModeWgt::onScreenShotFinished(ScreenShot* screenShot)
{

}

void playModeWgt::onPanoPlayerRenderBefore()
{

}

void playModeWgt::onPanoPlayerRenderAfter()
{

}

void playModeWgt::CaptureThreadFunc()
{
	calibrater_and_capturer_->RealTimeCapture(m_av_frame_sync_list_);
}
