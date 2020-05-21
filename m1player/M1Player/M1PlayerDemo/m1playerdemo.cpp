#pragma execution_character_set("utf-8")
#include "m1playerdemo.h"
#include "ui_m1playerdemo.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QRadioButton> 
#include <QInputDialog> 
#include <sstream>
#include <qthread.h>
#include <thread>
#include <string>
#include "GetResult.h"

extern "C" {
#include "media_meta.h"
}

#include "MessageQueue.h"
#include "logging.h"

#define MAX_VIEW_MODE_COUNT 8

#define MAX_CODEC_COUNT 3

#define SHOW_FOV_VALUE false

QtM1PlayerDemo::QtM1PlayerDemo(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->fov = 0;

	panoPlayer = new PixelPanoPlayer;
	glWidget_ = new GLSurfaceWidget(panoPlayer);
	ui.horizontalLayout_2->addWidget(glWidget_);
	//glWidget_->setVisible(false);
	panoPlayer->setPanoPlayerPluginListener(this);
	panoPlayer->setPanoPlayerListener(this);
	ui.btSelectFile->setVisible(false);
	ui.btScreenShot->setVisible(false);
	ui.pbProgress->setVisible(false);
	ui.btPlay->setVisible(true);

	//add by chenliang
	m_first_frames = true;
	m_audio_pause_on = false;
	m_vcodec_type = 3;
	m_m1_player = NULL;
	m_pixelPlugin = panoPlayer->getPixelPlugin();
	CMessageQueue::GetInstance().Register(std::bind(&QtM1PlayerDemo::onSigaction, this, std::placeholders::_1, std::placeholders::_2), m_signal_id);
	

	if (SHOW_FOV_VALUE) {
		//panoPlayer->setPanoPlayerRenderEventListener(this);
	}

	const char* viewModeStrs[MAX_VIEW_MODE_COUNT] = { "全景", "鱼眼", "VR_左右", "VR_上下", "平面", "展开2:1", "小行星", "曲面" };
	rgViewMode = new QButtonGroup(this);
	for (int i = 0; i < MAX_VIEW_MODE_COUNT; i++) {
		QRadioButton* radioButton = new QRadioButton(tr(viewModeStrs[i]));
		if (i == 0) {
			radioButton->setChecked(true);
		}
		rgViewMode->addButton(radioButton, i + 1);
		ui.llViewMode->addWidget(radioButton);
	}

	const char* viewModeCodec[MAX_CODEC_COUNT] = { "软解", "硬解QSV", "硬解CUDA" };
	rgCodec = new QButtonGroup(this);
	for (int i = 0; i < MAX_CODEC_COUNT; i++) {
		QRadioButton* radioButton = new QRadioButton(tr(viewModeCodec[i]));
		//默认选择cuda
		if (i == 2) {
			radioButton->setChecked(true);
		}
		rgCodec->addButton(radioButton, i + 1);
		ui.horizontalLayout_4->addWidget(radioButton);
	}

	connect(this, SIGNAL(updateSig(long, long)), this, SLOT(updateUI(long, long)));
	connect(this, SIGNAL(updateMediaInfoSig(PluginMetaData*)), this, SLOT(updateMediaInfoUI(PluginMetaData*)));
	connect(ui.btPlay, SIGNAL(clicked()), this, SLOT(onBtPlayButtonClicked()));
	connect(ui.btScreenShot, SIGNAL(clicked()), this, SLOT(onBtScreenShotButtonClicked()));

	connect(ui.btAudio, SIGNAL(clicked()), this, SLOT(onBtAudioButtonClicked()));

	connect(ui.btSelectFile, SIGNAL(clicked()), this, SLOT(onBtSelectFileButtonClicked()));

	connect(ui.btReverse, SIGNAL(clicked()), this, SLOT(onBtReverseButtonClicked()));

	connect(ui.btInput, SIGNAL(clicked()), this, SLOT(onBtInputUrlButtonClicked()));
	connect(rgViewMode, SIGNAL(buttonToggled(int, bool)), this, SLOT(onViewModeGroupButtonChecked(int, bool)));
	connect(rgCodec, SIGNAL(buttonToggled(int, bool)), this, SLOT(onCodecGroupButtonChecked(int, bool)));

	QLabel *label = new QLabel;
	label->setText("0000-00-00 00:00:00");
	label->resize(100, 20);
}

QtM1PlayerDemo::~QtM1PlayerDemo()
{
	if (glWidget_ != NULL) {
		delete glWidget_;
	}
	if (rgViewMode != NULL) {
		//rgViewMode->buttons();
	}
	if (m_m1_player) {
		m_m1_player->Close();
		delete m_m1_player;
		m_m1_player = NULL;
	}
}


void QtM1PlayerDemo::updateUI(long process, long duration)
{
	ui.pbProgress->setValue(process);
	long playTime = process * 1.0 / 100 * duration;
	QString string = QString("%1/%2").arg(QString::number(playTime), QString::number(duration));
	ui.tvTime->setText(string);
}

void QtM1PlayerDemo::updateMediaInfoUI(PluginMetaData* mediaMeta)
{
	if (mediaMeta == NULL) {
		return;
	}
	string tip;
	ostringstream s1;
	if (!SHOW_FOV_VALUE) {
		switch (mediaMeta->mediaType) {
		case PluginMediaType_VIDEO:
			s1 << "媒体信息:" << "width:" << mediaMeta->width << ",height:"
				<< mediaMeta->height << ",duaration:" << mediaMeta->duration << ",vbitrate:" << mediaMeta->videoBitRate << ",vFrameRate:" << mediaMeta->videoFrameRate
				<< ",aBitrate:" << mediaMeta->audioBitRate << ",aSampleRate:" << mediaMeta->audioSampleRate << endl;
			tip = s1.str();
			break;
		case PluginMediaType_PIC:
			s1 << "媒体信息:" << "width:" << mediaMeta->width << ",height:"
				<< mediaMeta->height << endl;
			tip = s1.str();
			break;
		}
		ui.tvInfo->setText(tip.c_str());
	} else {
		s1 << "fov:" << this->fov;
		tip = s1.str();
	}
	ui.tvInfo->setText(tip.c_str());
}

void QtM1PlayerDemo::onPanoPlayerPluginStatusChanged(PanoPluginStatus status, string tip)
{
	qDebug("plugin state %s", tip.c_str());
}

void QtM1PlayerDemo::onPanoPlayerPluginProgressChanged(long playProgress, long bufferProgress, long duration)
{
	emit updateSig(playProgress, duration);
}

void QtM1PlayerDemo::onScreenShotFinished(ScreenShot* screenShot)
{
	qDebug("-----------------------------------------------");
	const int width = screenShot->width;
	const int height = screenShot->height;
	QImage image(screenShot->data, width, height, QImage::Format_RGBA8888);
	bool ret = image.save("C:\\Users\\zj\\Desktop\\screenShot.jpg", "JPG");
	if (ret) {
		qDebug("write the screen shot jpg file success!");
	} else {
		qDebug("write the screen shot jpg file failure!");
	}
}

void QtM1PlayerDemo::onPanoPlayerLoading()
{
}

void QtM1PlayerDemo::onPanoPlayerLoaded()
{
	Plugin* plugin = panoPlayer->getPlugin();
	if (plugin != NULL) {
		this->pluginMetaDatas = plugin->getPluginMetaDatas();
		emit updateMediaInfoSig(&this->pluginMetaDatas[0]);
	}

	std::vector<std::string> weight_path;
	weight_path.push_back("wt0.jpg");
	weight_path.push_back("wt1.jpg");
	weight_path.push_back("wt2.jpg");
	weight_path.push_back("wt3.jpg");
	panoPlayer->setweight(weight_path);
}

void QtM1PlayerDemo::onPanoPlayerError(PanoPlayerErrorCode errorCode)
{

}


void QtM1PlayerDemo::onPanoPlayerRenderBefore() 
{

}

void QtM1PlayerDemo::onPanoPlayerRenderAfter()
{

}

void  QtM1PlayerDemo::fovGetThreadFunc()
{

	unsigned long sleepTime = (unsigned long)(1000 * 1.0 / 30);
	while (true) {
		GestureData* gestureData = panoPlayer->getcurrentGestureData();
		if (gestureData != NULL) {
			this->fov = gestureData->fov;
			PluginMetaData metaData;
			memset(&metaData, 0, sizeof(metaData));
			emit this->updateMediaInfoSig(&metaData);
		}
		QThread::msleep(sleepTime);

	}
}

//add by chenliang
void QtM1PlayerDemo::onSigaction(int message_type, long attach)
{
	Log::Info("message:%d from m1 player.", message_type);
	switch (message_type)
	{
	case ERROR_SOCKET_READ:
		if (m_m1_player) {
			m_m1_player->RePlay();
		}
		break;
	case ERROR_SYSTEM_TIMER:
		m_pixelPlugin->notifyStateChanged(PluginState_COMPLETED, "m1 player close");
		if (m_m1_player) {
			m_m1_player->Close();
			delete m_m1_player;
			m_m1_player = NULL;
			m_first_frames = true;
		}
		break;
	default:
		break;
	}
}

void QtM1PlayerDemo::onVideoFrames(m1_video_frame_s** av_frame_sync_list_, int index, unsigned int timestamp)
{
	if (m_first_frames) {
		m_first_frames = false;

		PluginMetaData metadata;
		metadata.height = av_frame_sync_list_[0]->h;
		metadata.width = av_frame_sync_list_[0]->w;
		for (int i = 0; i < PLUGIN_MAX_PLANE; i++) {
			metadata.lineSize[i] = av_frame_sync_list_[0]->linesize[i];
		}

		if (av_frame_sync_list_[0]->format == PIX_FMT_YUV420P) {
			metadata.pluginFormat = PluginColorFormat_YUV420P;
		}
		else if (av_frame_sync_list_[0]->format == PIX_FMT_NV12) {
			metadata.pluginFormat = PluginColorFormat_NV12;
		}
		vector<PluginMetaData> metadata_vector;
		metadata_vector.push_back(metadata);
		m_pixelPlugin->notifyMetaDatas(metadata_vector);

		m_pixelPlugin->notifyStateChanged(PluginState_PREPARED, "m1 player ready.");
	}

	for (int i = 0; i < PLUGIN_MAX_PLANE; i++) {
		if (av_frame_sync_list_[i]->format == PIX_FMT_YUV420P) {
			m_frames[i].colorFormat = PluginColorFormat_YUV420P;
			m_frames[i].planes = 3;
		}
		else if (av_frame_sync_list_[i]->format == PIX_FMT_NV12) {
			m_frames[i].colorFormat = PluginColorFormat_NV12;
			m_frames[i].planes = 2;
		}

		for (int j = 0; j < PLUGIN_MAX_PLANE; j++) {
			m_frames[i].data[j] = av_frame_sync_list_[i]->data[j];
		}
	}

	m_pixelPlugin->notifyFramesChanged((PluginFrame*)m_frames, 4);
}

void QtM1PlayerDemo::init_m1_player(string url)
{
	m_m1_player = new CM1Player;
	m_m1_player->SetDisplayFps(25);
	m_m1_player->SetDisplayTag(true);
	m_m1_player->SetRecordTag(false);
	m_m1_player->SetStreamType(StreamTypeRtmp);
	m_m1_player->SetOnwer(m_signal_id);
	if (m_vcodec_type == 2) {
		m_m1_player->SetDeocdeType(DecodeTypeIntel);
	} else if (m_vcodec_type == 3) {
		m_m1_player->SetDeocdeType(DecodeTypeCuda);
	}

	m1_player_config_s config;
	config.videoproc = std::bind(&QtM1PlayerDemo::onVideoFrames, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	config.messageproc = nullptr;
	config.url = url;

	int ret = m_m1_player->Init(config);
	if (ret != 0) {
		Log::Error("m1 player init error.");
	}
	m_m1_player->Play();
	Log::Info("m1 player init success.");
}

void QtM1PlayerDemo::play(const char* filePath, PanoResourceType resoureType, const char* calibration, PanoDeviceId deviceId)
{
	//add by chenliang
	init_m1_player(filePath);

	if (SHOW_FOV_VALUE) {
		//new std::thread(&QtM1PlayerDemo::fovGetThreadFunc, this);
	}

	PanoramaData panoData;
	qDebug("calibration:%s", calibration);
	PanoNodeImage imageData;
	imageData.panoResourceType = resoureType;
	vector<string> urls;
	urls.push_back(filePath);
	imageData.urls = urls;
	imageData.calibration = calibration;
	//if (deviceId == PanoDeviceId_SPHERE_DETU_TWINS) {
	//	imageData.calibration = "6_725_760_760_-180_0.0926538_-0.497061_725_2280_759_-0.156559_0.0939263_-0.50559_3040_1520_-1.63751_-1.3263_0_0_0_0_-0.0784645_0_0_-0.0675285_192_187";
	//}
	// if (deviceId==PanoDeviceId_SPHERE_DETU_F4){
	//	imageData.calibration ="f4_768_1104_-181_17_1118_1071_60_2_0.5_199.909_0_0_-0.038049_-20.1339_18.1223_0_0_768_1104_-155_14_1098_1052_150.495_-3.64108_1.03595_196.497_0_0_-0.031709_-10.8518_5.68707_0_0_768_1104_-176_25_1114_1067_-120.957_-5.27204_-3.6941_202.126_0_0_-0.026345_-24.9443_12.4067_0_0_768_1104_-183_-1_1126_1079_-30.8474_3.37513_-6.78084_202.557_0_0_-0.057554_-18.7966_5.76274_0_0_768_1104";
	//} 
	imageData.panoDeviceId = deviceId;
	panoData.nodeImage = imageData;
	PanoNodeView viewData;
	viewData.curfov = viewData.deffov;
	viewData.vLookAt = 0;
	viewData.hLookAt = 0;

	//GestureData *gesturdata = panoPlayer->getcurrentGestureData();
	//if (gesturdata != NULL) {
	//	viewData.curfov = gesturdata->fov;
	//	viewData.hLookAt = gesturdata->yaw * 180 / M_PI;
	//	viewData.vLookAt = gesturdata->pitch * 180 / M_PI;
	//}
	viewData.viewMode = static_cast<PanoViewMode>(PanoViewMode_FLAT);
	panoData.nodeView = viewData;
	PlayerOption option1;
	option1.type = PlayerOptionType_Codec;
	option1.key = PLAYER_OPTION_DETU_KEY_DECODER;
	option1.value = codecDes;
	vector<PlayerOption> options;
	options.push_back(option1);
	panoPlayer->play(panoData, options);
}

void QtM1PlayerDemo::onBtPlayButtonClicked()
{
	m_pixelPlugin->notifyStateChanged(PluginState_COMPLETED, "m1 player close");
	if (m_m1_player) {
		m_m1_player->Close();
		delete m_m1_player;
		m_m1_player = NULL;
		m_first_frames = true;
	}
}

void QtM1PlayerDemo::onBtAudioButtonClicked()
{
	if (m_m1_player){
		if (m_audio_pause_on){
			m_audio_pause_on = false;

			QString name = QStringLiteral("停止音频");
			ui.btAudio->setText(name);
		} else {
			m_audio_pause_on = true;

			QString name = QStringLiteral("播放音频");
			ui.btAudio->setText(name);
		}
		m_m1_player->PauseAudio(m_audio_pause_on);
	}
}

void QtM1PlayerDemo::onBtReverseButtonClicked() {
	if (reservedegree==0){
		reservedegree = 180;
		panoPlayer->setreverse(reservedegree);
	} else {
		reservedegree = 0;
		panoPlayer->setreverse(reservedegree);
	}
}

void QtM1PlayerDemo::onBtScreenShotButtonClicked()
{
	panoPlayer->getScreenShot(this);
}

void QtM1PlayerDemo::onBtSelectFileButtonClicked()
{
	QString path = QFileDialog::getOpenFileName(NULL, tr("请选择文件"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), "Videos&&Images(*.mp4 *.jpg *.png)");
	QByteArray array = path.toLocal8Bit();
	const char* filePath = NULL;
	filePath = array.data();
	qDebug("select file path:%s", filePath);
	CameraMediaInfo mediaInfo;
	memset(&mediaInfo, 0, sizeof(CameraMediaInfo));
	bool ret = mediaMetaGetCameraMediaInfo(filePath, &mediaInfo);
	PanoResourceType resourceType = PanoResourceType_VIDEO;


	if (path.toLower().lastIndexOf(".jpg") > -1 || path.toLower().lastIndexOf(".jpeg") > -1 || path.toLower().lastIndexOf(".png") > -1) {
		resourceType = PanoResourceType_SPHERE;
	}

	PanoDeviceId deviceId = PanoDeviceId_2_1;
	const char* calibration = "";
	if (ret) {
		switch (mediaInfo.mediaInfo.mediaType) {
		case MediaMetaMediaType_PIC:
			resourceType = PanoResourceType_SPHERE;
			break;
		case MediaMetaMediaType_VIDEO:
			resourceType = PanoResourceType_VIDEO;
			break;
		default:
			break;
		}

		switch (mediaInfo.mediaCameraId) {
		default:
		case UnKnow:
			deviceId = PanoDeviceId_2_1;
			break;
		case Sphere800:
		case SphereS:
		case OneFishEye:
			deviceId = PanoDeviceId_SPHERE_S;
			break;
		case TwoFishEye:
		case Twin_01:
		case Twin_02:
		case Twin_03:
			deviceId = PanoDeviceId_SPHERE_DETU_TWINS;
			break;
		}
		calibration = mediaInfo.calibration;
	}
	play(filePath, resourceType, calibration, deviceId);

}

void QtM1PlayerDemo::onBtInputUrlButtonClicked()
{
	bool ret = false;
	QString templateName = QInputDialog::getText(NULL, QObject::tr("url"), QObject::tr("请url地址："), QLineEdit::Normal, QString(), &ret);
	if (!ret) {
		return;
	}
	if (templateName == NULL || templateName == "") {
		templateName = "rtmp://101.37.134.32:1935/09CE96/1";
	}
	//play(templateName.toLatin1().data());
	std::vector<std::string> result_path;
	std::string wt0 = "wt0.jpg";
	std::string wt1 = "wt1.jpg";
	std::string wt2 = "wt2.jpg";
	std::string wt3 = "wt3.jpg";
	result_path.push_back(wt0);
	result_path.push_back(wt1);
	result_path.push_back(wt2);
	result_path.push_back(wt3);
	WeightAndMaskData weightdata;
	bool result = getResultwithpath("pat.pts", weightdata, result_path);
	//std::string path = templateName.toStdString();
	//std::string path = "rtmp://192.168.0.19:1935/09CE94_1/1";
	//std::string path = "rtmp://192.168.8.74:1935/0CD2DB_1/1";
	std::string path = "rtmp://192.168.8.56:1935//0CD2DB_1/1";
	play(path.c_str(), PanoResourceType_VIDEO, weightdata.biaoding, PanoDeviceId_SPHERE_DETU_F4);
}

void QtM1PlayerDemo::onViewModeGroupButtonChecked(int id, bool checked)
{
	// "全景", "鱼眼", "VR_左右", "VR_上下", "平面", "展开2:1", "小行星"
	if (!checked) {
		return;
	}
	qDebug("id:%d, checked:%d", id, checked);
	chooseviewmode = id;
	panoPlayer->setAnimationViewMode(static_cast<PanoViewMode>(id), 2, CubicEaseIns);
	//panoPlayer->setViewMode(static_cast<PanoViewMode>(id));
}

void QtM1PlayerDemo::onCodecGroupButtonChecked(int id, bool checked)
{
	//{"软解", "硬解QSV", "硬解CUDA"};
	if (!checked) {
		return;
	}
	qDebug("id:%d, checked:%d", id, checked);
	switch (id) {
	case 1:
		codecDes = "none";
		m_vcodec_type = 1;
		break;
	case 2:
		codecDes = "qsv";
		m_vcodec_type = 2;
		break;
	case 3:
		codecDes = "cuda";
		m_vcodec_type = 3;
		break;
	default:
		break;
	}
}

void QtM1PlayerDemo::closeEvent(QCloseEvent* event)
{
	m_pixelPlugin->notifyStateChanged(PluginState_ERROR, "m1 player error");
	if (m_m1_player){
		m_m1_player->Close();
		delete m_m1_player;
		m_m1_player = NULL;
	}
	
	if (glWidget_){
		glWidget_->close();
	}
	qDebug("this is the window close!");
}
