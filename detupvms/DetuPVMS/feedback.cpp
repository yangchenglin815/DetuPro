#pragma once
#pragma execution_character_set("utf-8")


#include <QWidget>
#include <QPainter>
#include <QtEvents>
#include <QDesktopServices>
#include <QBitmap>
#include <QTimer>

#include "constStruct.h"
#include "DetuPVMSIni.h"
#include "feedback.h"
#include "ui_feedback.h"
#include "logging.hpp"

Feedback* Feedback::m_pInstance = NULL;

Feedback::Feedback(QWidget *parent)
: QDialog(parent)
, ui(new Ui::feedback)
{

	ui->setupUi(this);
	setWindowFlags(/*Qt::Popup | */Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	setAttribute(Qt::WA_TranslucentBackground);
	initConnect();
}

Feedback::~Feedback()
{
	delete ui;
}

Feedback* Feedback::instance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new Feedback;
	}
	return m_pInstance;
}

void Feedback::maskUI(int type)
{
	QString path, str;
	setTipContent(type, path, str);
	Log::Info("feedback maskUI type : %d, tips : %s", type, str.toLocal8Bit().data());
	ui->imageLabel_->setStyleSheet(path);
	ui->tipLabel_->setText(str);
	QStringList list = DetuPVMSIni::getClientPos();
	if (list.size() == 4)
	{
		int n_Width = list.at(0).toInt();
		int n_Height = list.at(1).toInt();
		int n_XPos = list.at(2).toInt();
		int n_YPos = list.at(3).toInt();
		int nX = (n_Width - this->width() + n_XPos) / 2;
		int nY =  n_YPos / 2 + 36 + 30;
		move(nX, nY);
	}
	setWindowState((windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
	this->raise();
	activateWindow();
	show();
	QTimer::singleShot(2000, this, SLOT(close()));
}

void Feedback::tipsUI(short errCode, std::string PVSId, unsigned char streamId)
{
	QString path = "border-image:url(:/image/image/caesura.png)";
	QString stream = streamId ? QStringLiteral("子码流") : QStringLiteral("主码流");
	QString tips;
	setReportContent(errCode, tips, stream, PVSId);
	Log::Info("feedback tipsUI code : %d, tips : %s", errCode, tips.toLocal8Bit().data());
	ui->imageLabel_->setStyleSheet(path);
	ui->tipLabel_->setText(tips);
	QStringList list = DetuPVMSIni::getClientPos();
	if (list.size() == 4)
	{
		int n_Width = list.at(0).toInt();
		int n_Height = list.at(1).toInt();
		int n_XPos = list.at(2).toInt();
		int n_YPos = list.at(3).toInt();
		int nX = (n_Width - this->width() + n_XPos) / 2;
		int nY = n_YPos / 2 + 36 + 30;
		move(nX, nY);
	}
	setWindowState((windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
	this->raise();
	activateWindow();
	show();
	QTimer::singleShot(2000, this, SLOT(close()));
}

void Feedback::setContent(QString path, QString str)
{
	ui->imageLabel_->setStyleSheet(path);
	ui->tipLabel_->setText(str);
}

void Feedback::setTipContent(int code, QString &path, QString &str)
{
	switch (code)
	{
	case SERVER_UNCONNECT:
		path = "border-image:url(:/image/image/caesura.png)";
		str = QStringLiteral("服务器无响应");
		break;
	case PDF_NOTFOUND:
		path = "border-image:url(:/image/image/caesura.png)";
		str = QStringLiteral("您还未安装PDF阅读器");
		break;
	case IMAGE_SAVE_SUCCESS:
		path = "border-image:url(:/image/image/save_suc.png)";
		str = QStringLiteral("图像保存成功");
		break;
	case IMAGE_SAVE_FAILED:
		path = "border-image:url(:/image/image/save_fail.png)";
		str = QStringLiteral("图像保存失败");
		break;
	case PLAY_REQUEST_FAILED:
		path = "border-image:url(:/image/image/caesura.png)";
		str = QStringLiteral("请求视频失败");
		break;
	case REPLAY_REQUEST_FAILED:
		path = "border-image:url(:/image/image/caesura.png)";
		str = QStringLiteral("当前时间没有视频");
		break;
	case CAPTURE_SUCCESS:
		path = "border-image:url(:/image/image/save_suc.png)";
		str = QStringLiteral("图像保存成功");
		break;
	case CAPTURE_FAILED:
		path = "border-image:url(:/image/image/save_fail.png)";
		str = QStringLiteral("图像保存失败");
		break;
	case SETTINGS_SUCCESS:
		path = "border-image:url(:/image/image/save_suc.png)";
		str = QStringLiteral("配置保存成功");
		break;
	case SETTINGS_FAILED:
		path = "border-image:url(:/image/image/save_fail.png)";
		str = QStringLiteral("配置保存失败");
		break;
	case FORMAT_SUCCESS:
		path = "border-image:url(:/image/image/save_suc.png)";
		str = QStringLiteral("格式化成功");
		break;
	case FORMAT_FAILED:
		path = "border-image:url(:/image/image/save_fail.png)";
		str = QStringLiteral("格式化失败");
		break;
	case WARN_BITRATE:
		path = "border-image:url(:/image/image/save_fail.png)";
		str = QStringLiteral("输入的码率越界");
		break;
	case FORMAT_NULL:
		path = "border-image:url(:/image/image/save_fail.png)";
		str = QStringLiteral("请选择需要格式化的设备");
		break;
	case NULL_SELECTED:
		path = "border-image:url(:/image/image/save_fail.png)";
		str = QStringLiteral("请选择需要操作的设备");
		break;
	case PTZ_BIND_SUCCESS:
		path = "border-image:url(:/image/image/save_suc.png)";
		str = QStringLiteral("球机绑定/解绑成功");
		break;
	case PTZ_BIND_FAILED:
		path = "border-image:url(:/image/image/save_fail.png)";
		str = QStringLiteral("球机绑定/解绑失败");
		break;
	case SPY_BIND_SUCCESS:
		path = "border-image:url(:/image/image/save_suc.png)";
		str = QStringLiteral("枪机绑定/解绑成功");
		break;
	case SPY_BIND_FAILED:
		path = "border-image:url(:/image/image/save_fail.png)";
		str = QStringLiteral("枪机绑定/解绑失败");
		break;
	case PTZ_NO_BIND:
		path = "border-image:url(:/image/image/save_fail.png)";
		str = QStringLiteral("未绑定球机，请先绑定球机");
		break;
	case SPY_NO_BIND:
		path = "border-image:url(:/image/image/save_fail.png)";
		str = QStringLiteral("未绑定枪机，请先绑定球机");
		break;
	case STREAM_HANDLE_FAILED:
		path = "border-image:url(:/image/image/save_fail.png)";
		str = QStringLiteral("流处理失败");
		break;
	case REBOOT_M1_FAILED:
		path = "border-image:url(:/image/image/save_fail.png)";
		str = QStringLiteral("M1重启请求失败");
		break;
	case OPT_MIZE_SUCCESS:
		path = "border-image:url(:/image/image/save_suc.png)";
		str = QStringLiteral("模板优化成功");
		break;
	case SRS_ERROR:
		path = "border-image:url(:/image/image/save_fail.png)";
		str = QStringLiteral("SRS推流异常");
		break;
	case WAIT_PLAY:
		path = "border-image:url(:/image/image/save_fail.png)";
		str = QStringLiteral("请耐心等待播放器初始化");
		break;
	case STREAM_ERR:
		path = "border-image:url(:/image/image/save_fail.png)";
		str = QStringLiteral("拉流失败，请重新请求视频源");
		break;
	case M1_WARNING:
		path = "border-image:url(:/image/image/save_fail.png)";
		str = QStringLiteral("相机异常，请重启相机后再尝试");
		break;
	case CALIBRATION_LOW_SCORE:
		path = "border-image:url(:/image/image/save_fail.png)";
		str = QStringLiteral("客户端标定评分过低，请重试或更新场景");
		break;
	case SRS_NO_RESPONSE:
		path = "border-image:url(:/image/image/save_fail.png)";
		str = QStringLiteral("SRS推流服务无响应，请检查服务是否开启");
		break;
	case CREATE_PTS_FILE_FAILED:
		path = "border-image:url(:/image/image/save_fail.png)";
		str = QStringLiteral("生成PTS文件夾失敗，请重試");
		break;
	case DELETE_PTZ_SUCCESS:
		path = "border-image:url(:/image/image/save_suc.png)";
		str = QStringLiteral("删除球机成功");
		break;
	case DELETE_SPY_SUCCESS:
		path = "border-image:url(:/image/image/save_suc.png)";
		str = QStringLiteral("删除枪机成功");
		break;
	case DELETE_PTZ_FAILED:
		path = "border-image:url(:/image/image/save_fail.png)";
		str = QStringLiteral("删除球机失败");
		break;
	case DELETE_SPY_FAILED:
		path = "border-image:url(:/image/image/save_fail.png)";
		str = QStringLiteral("删除枪机失败");
		break;
	case DEVICE_INFO_ERROR:
		path = "border-image:url(:/image/image/save_fail.png)";
		str = QStringLiteral("设备登录信息错误");
		break;
	case SET_PRE_POINT_OK:
		path = "border-image:url(:/image/image/save_suc.png)";
		str = QStringLiteral("球机预置点设置成功，请重新加载播放");
		break;
	case SET_GUN_CAM_POINT_OK:
		path = "border-image:url(:/image/image/save_suc.png)";
		str = QStringLiteral("枪机位置设置成功，请重新加载播放");
		break;
	case WARN_ONE_STREAM:
		path = "border-image:url(:/image/image/caesura.png)";
		str = QStringLiteral("仅有一路设备可推送主码流");
		break;
	case DEVICE_OFFLINE:
		path = "border-image:url(:/image/image/caesura.png)";
		str = QStringLiteral("该设备已离线，无法播放");
		break;
	case WARN_SUBSTREAM_DELETED:
		path = "border-image:url(:/image/image/caesura.png)";
		str = QStringLiteral("该设备子码流已被关闭，无法切换");
		break;
	case NO_NEXT_POINT:
		path = "border-image:url(:/image/image/caesura.png)";
		str = QStringLiteral("当前地图点没有后向路径");
		break;
	case NO_PREV_POINT:
		path = "border-image:url(:/image/image/caesura.png)";
		str = QStringLiteral("当前地图点没有前向路径");
		break;
	case OFF_LINE_NO_PLAY:
		path = "border-image:url(:/image/image/caesura.png)";
		str = QStringLiteral("无法预览离线设备");
		break;
	case ROTATING_NO_SWITCH:
		path = "border-image:url(:/image/image/caesura.png)";
		str = QStringLiteral("旋转过程中无法切换");
		break;		
	case MAP_SAVE_OK:
		path = "border-image:url(:/image/image/caesura.png)";
		str = QStringLiteral("地图数据保存成功");
		break;
	case NOT_ADMIN:
		path = "border-image:url(:/image/image/caesura.png)";
		str = QStringLiteral("当前账户没有访问权限");
		break;
	case SET_ADMIN:
		path = "border-image:url(:/image/image/caesura.png)";
		str = QStringLiteral("设置管理员帐号成功");
		break;
	case SET_NOT_ADMIN:
		path = "border-image:url(:/image/image/caesura.png)";
		str = QStringLiteral("取消管理员帐号成功");
		break;
	case VERSION_CHECK_FAILED:
		path = "border-image:url(:/image/image/caesura.png)";
		str = QStringLiteral("客户端与服务器版本不匹配！");
		break;
	case RFID_DETECTED:
		path = "border-image:url(:/image/image/caesura.png)";
		str = QStringLiteral("检测到RFID标签！");
		break;
	default:
		break;
	}
}

void Feedback::setReportContent(int errCode, QString &tips, QString stream, std::string PVSId)
{
	switch (errCode)
	{
	case RESULT_NOTSUPPORT:
		tips = QStringLiteral("设备%1 : 该设备暂不支持").arg(QString::fromStdString(PVSId));
		break;
	case RESULT_UNKNOWCMD:
		tips = QStringLiteral("设备%1 : 未知指令").arg(QString::fromStdString(PVSId));
		break;
	case RESULT_NODATA:
		tips = QStringLiteral("设备%1 : 无数据").arg(QString::fromStdString(PVSId));
		break;
	case RESULT_NOTREGISTER:
		tips = QStringLiteral("设备%1 : 未注册").arg(QString::fromStdString(PVSId));
		break;
	case RESULT_PARAM_ERR:
		tips = QStringLiteral("设备%1 : 请求参数错误").arg(QString::fromStdString(PVSId));
		break;
	case RESULT_SYNC_ERR:
		tips = QStringLiteral("设备%1 : %2同步失败").arg(QString::fromStdString(PVSId)).arg(stream);
		break;
	case  RESULT_ONLINE_ERR:
		tips = QStringLiteral("设备%1 : M1一路或多路不在线").arg(QString::fromStdString(PVSId));
		break;
	case RESULT_SEND_ERR:
		tips = QStringLiteral("设备%1 : 发送数据失败").arg(QString::fromStdString(PVSId));
		break;
	case RESULT_CONNECT_ERR:
		tips = QStringLiteral("设备%1 : 连接流媒体服务器失败").arg(QString::fromStdString(PVSId));
		break;
	case RESULT_USERNAMEERR:
		tips = QStringLiteral("设备%1 : 用户名错误").arg(QString::fromStdString(PVSId));
		break;
	case RESULT_PWDERR:
		tips = QStringLiteral("设备%1 : 密码错误").arg(QString::fromStdString(PVSId));
		break;
	case RESULT_REDEVICEID:
		tips = QStringLiteral("设备%1 : 设备ID重复").arg(QString::fromStdString(PVSId));
		break;
	case RESULT_CALIBRATIONERR:
		tips = QStringLiteral("设备%1 : 标定信息错误").arg(QString::fromStdString(PVSId));
		break;
	case RESULT_SYNC_OK:
		tips = QStringLiteral("设备%1 : %2同步成功").arg(QString::fromStdString(PVSId)).arg(stream);
		break;
	case RESULT_ONLINE_OK:
		tips = QStringLiteral("设备%1 :  M1四个通道都在线").arg(QString::fromStdString(PVSId));
		break;
	case TCS_SERVER_DISCONNECT_ERROR:
		tips = QStringLiteral("设备%1：转码推流异常断开").arg(QString::fromStdString(PVSId));
		break;
	case TCS_SERVER_OFFLINE:
		tips = QStringLiteral("转码服务%1 : 已离线").arg(QString::fromStdString(PVSId));
		break;
	case TCS_TRANSCODE_SUCCESS:
		tips = QStringLiteral("转码服务%1 : 已启动").arg(QString::fromStdString(PVSId));
		break;
	case TCS_CLOSE_TRANSCODE_SUCCESS:
		tips = QStringLiteral("转码服务%1 : 关闭成功").arg(QString::fromStdString(PVSId));
		break;
	case TCS_PULL_RTMP_ERROR:
		tips = QStringLiteral("转码服务%1 : RTMP拉流失败").arg(QString::fromStdString(PVSId));
		break;
	case TCS_PUSH_RTMP_ERROR:
		tips = QStringLiteral("转码服务%1 : RTMP推流失败").arg(QString::fromStdString(PVSId));
		break;
	default:
		return;
	}
}

void Feedback::initConnect()
{
	connect(ui->closeButton_, SIGNAL(clicked()), this, SLOT(close()));
}
