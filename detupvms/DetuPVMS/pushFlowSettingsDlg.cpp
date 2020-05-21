#include "pushFlowSettingsDlg.h"
#include "ui_pushFlowSettingsDlg.h"
#include "ItemDelegate.h"
#include "FramelessHelper.h"
#include "socketRequest.h"
#include "TcpDataManager.hpp"
#include "QTSocketManage.h"
#include "commonFun.h"
#include "QTimerManage.h"
#include "ViewSignal.h"
#include "feedback.h"

#include <QTimer>
#include <QClipboard>
#include <QMessageBox>

pushFlowSettingsDlg::pushFlowSettingsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pushFlowSettingsDlg),
	m_pushFlowPort(0)
{
    ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);

	FramelessHelper *helper = new FramelessHelper;
	helper->activateOn(this);
	helper->setDbClickOn(false);
	helper->setWidgetResizable(false);

	initPushFlowPage();

    m_lineEdit = ui->comboBox->lineEdit();
    m_lineEdit->setPlaceholderText(tr("down pull to show history url"));
    connect(m_lineEdit, &QLineEdit::textChanged, this, &pushFlowSettingsDlg::updateLineEditStyleSheet);

    ItemDelegate *pDelegate = new ItemDelegate(this);
    ui->comboBox->setItemDelegate(pDelegate);
    connect(pDelegate, SIGNAL(deleteItem(QModelIndex)), this, SLOT(slotOnDeleteItem(QModelIndex)));

    connect(ui->startBtn, SIGNAL(clicked()), this, SLOT(slotOnStartPushFlow()));
	connect(ui->cancelBtn, SIGNAL(clicked()), this, SLOT(slotOnClose()));
	connect(ui->closeBtn, SIGNAL(clicked()), this, SLOT(slotOnClose()));
	connect(ui->confirmBtn, SIGNAL(clicked()), this, SLOT(slotOnClose()));
	connect(ui->disconnectedBtn, SIGNAL(clicked()), this, SLOT(slotOnDisConnected()));
	connect(ui->copyUrlBtn, SIGNAL(clicked()), this, SLOT(slotOnCopyUrl()));

	connect(QTSocketManage::instance(), SIGNAL(sigOnPushFlowSuccess()), this, SLOT(slotOnPushFlowSuccess()));
	connect(QTSocketManage::instance(), SIGNAL(sigOnPushFlowFailed()), this, SLOT(slotOnPushFlowFailed()));
	connect(QTSocketManage::instance(), SIGNAL(sigOnCloseTranscode()), this, SLOT(slotOnCloseTranscode()));

	connect(ViewSignal::instance(), SIGNAL(sigOnReportTCSDisconnectError(std::string)), this, SLOT(slotOnReportTCSDisconnectError(std::string)));
	connect(ViewSignal::instance(), SIGNAL(sigOnReportTCSOffLine(int)), this, SLOT(slotOnReportTCSOffLine(int)));

	qRegisterMetaType<api_detu_client_av_param_t>("api_detu_client_av_param_t");
	connect(&TcpDataManagerIns, SIGNAL(sigOnGetBitRate(unsigned char, api_detu_client_av_param_t*)), this, SLOT(slotOnGetBitRate(unsigned char, api_detu_client_av_param_t*)));

	connect(QTimerManage::instance(), SIGNAL(sigOnUpdateTimer(int, QString)), this, SLOT(slotOnUpdateTimer(int, QString)));
}

pushFlowSettingsDlg::~pushFlowSettingsDlg()
{
    delete ui;
}

void pushFlowSettingsDlg::initData(const deviceInfo &info)
{
	m_deviceInfo = info;

	socketRequest::instance()->requestOnAskForStreamInfo(1, m_deviceInfo);
}

void pushFlowSettingsDlg::initTCSList(QList<TCSManageInfo> TCSManageInfoList)
{
	m_TCSManageInfoList = TCSManageInfoList;
}

void pushFlowSettingsDlg::syncConnection(bool flag)
{
	if (flag)
	{
		connect(&TcpDataManagerIns, SIGNAL(sigOnGetBitRate(unsigned char, api_detu_client_av_param_t*)), this, SLOT(slotOnGetBitRate(unsigned char, api_detu_client_av_param_t*)));
	}
	else
	{
		disconnect(&TcpDataManagerIns, SIGNAL(sigOnGetBitRate(unsigned char, api_detu_client_av_param_t*)), this, SLOT(slotOnGetBitRate(unsigned char, api_detu_client_av_param_t*)));
	}
}

void pushFlowSettingsDlg::initPushFlowPage()
{
	ui->titleLabel->setText(tr("pushFlow settings"));
	ui->startBtn->setEnabled(true);
	ui->stackedWidget->setCurrentWidget(ui->pushFlowPage);
}

void pushFlowSettingsDlg::initPushFlowInfoPage()
{
	ui->titleLabel->setText(tr("pushFlowing"));
	ui->urlLabel->setText(m_deviceInfo.szPushFlowUrl);
	ui->disconnectedBtn->setEnabled(true);

	QString resolution = QString("%1x%2").arg(m_deviceInfo.av_param_t.nVideoWidth).arg(m_deviceInfo.av_param_t.nVideoHeight);
	QString frameRate = QString::number(m_deviceInfo.av_param_t.nFrameRate);
	QString bitRate = QString::number(m_deviceInfo.av_param_t.nBitRate);
	ui->infoLabel->setText(QString(tr("resolution") + "%1 @%2fps " + tr("bitRate") + "%3kbps").arg(resolution).arg(frameRate).arg(bitRate));

	ui->stackedWidget->setCurrentWidget(ui->pushFlowInfoPage);
}

void pushFlowSettingsDlg::slotOnDeleteItem(const QModelIndex &index)
{
    if (QMessageBox::question(this, tr("tips"), tr("confirm that you can delete the item you selected ?"),
                              QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes)
    {
        ui->comboBox->removeItem(index.row());
    }
}

void pushFlowSettingsDlg::slotOnStartPushFlow()
{
		ui->startBtn->setEnabled(false);
		QString pushFlowUrl = ui->comboBox->lineEdit()->text();
		Log::Info("current pushFlow LineText is : %s", pushFlowUrl.toStdString().c_str());
		if (pushFlowUrl.isEmpty())
		{
			ui->startBtn->setEnabled(true);
			QMessageBox::warning(this, tr("warning"), tr("url is null !"));
			return;
		}
		else
		{
			//推流
			for (int i = 0; i < m_TCSManageInfoList.size(); ++i)
			{
				if (m_TCSManageInfoList[i].nCAU == 0)
				{
					m_pushFlowIP = m_TCSManageInfoList[i].szTcsIp;
					m_pushFlowPort = m_TCSManageInfoList[i].nPort;
					m_currServerID = m_TCSManageInfoList[i].nServerId;
					break;
				}
			}

			if (m_pushFlowIP != NULL && m_pushFlowPort != 0)
			{
				QTSocketManage::instance()->initSocket(m_pushFlowIP, m_pushFlowPort);
				QString data;
				if (m_deviceInfo.m1DeviceId == "default")
				{
					data = commonFun::readPTSData(m_deviceInfo.serialNo);
				}
				else
				{
					data = commonFun::readPTSData(m_deviceInfo.m1DeviceId);
				}

				if (data.isEmpty())
				{
					ui->startBtn->setEnabled(true);
					QMessageBox::warning(this, tr("warning"), tr("pts file is null !"));
					return;
				}

				api_detu_tcs_transcode api_detu;
				memcpy(api_detu.szRtmpURL, pushFlowUrl.toLocal8Bit().data(), API_URL_LEN);
				memcpy(api_detu.szDeviceId, m_deviceInfo.serialNo.toLocal8Bit().data(), API_ARRAY_LEN);
				api_detu.nDeviceId = 1;
				api_detu.nStreamType = 1;
				api_detu.nFps = m_deviceInfo.av_param_t.nFrameRate;
				api_detu.nbitrate = 2500;
				api_detu.nWidth = 1920;
				api_detu.nHeight = 960;
				api_detu.nPtsLen = data.length();
				Log::Info("start to copy pts file");
				memcpy(api_detu.pts_data, data.toStdString().c_str(), API_PTS_LEN);
				Log::Info("start to copy pts file finished");

				m_deviceInfo.av_param_t.nBitRate = api_detu.nbitrate;
				m_deviceInfo.av_param_t.nVideoWidth = api_detu.nWidth;
				m_deviceInfo.av_param_t.nVideoHeight = api_detu.nHeight;
				emit sigOnSyncData(m_deviceInfo);

				QTSocketManage::instance()->requestOnTCSVideo(api_detu);

				QTimer::singleShot(5000, this, [&](){
					ui->startBtn->setEnabled(true);
				});
			}
			else
			{
				ui->startBtn->setEnabled(true);
				QMessageBox::warning(this, tr("warning"), tr("not find TCS server !"));
				return;
			}
		}
}

void pushFlowSettingsDlg::slotOnDisConnected()
{
	//关闭推流
	ui->disconnectedBtn->setEnabled(false);
	QTSocketManage::instance()->requestOnCloseVideo(m_deviceInfo.serialNo);
	QTimer::singleShot(5000, this, [&](){
		ui->disconnectedBtn->setEnabled(true);
	});
}

void pushFlowSettingsDlg::slotOnCopyUrl()
{
	QString pushFlowUrl = ui->urlLabel->text();

	if (pushFlowUrl.isEmpty())
	{
		QMessageBox::warning(this, tr("warning"), tr("url is null !"));
	}
	else
	{
		QClipboard *board = QApplication::clipboard();
		board->setText(pushFlowUrl);
	}
}

void pushFlowSettingsDlg::updateLineEditStyleSheet()
{
    if (m_lineEdit->text().isEmpty())
    {
        m_lineEdit->setStyleSheet("QLineEdit { color: rgba(180,180,180,1);}");
    }
    else
    {
        m_lineEdit->setStyleSheet("QLineEdit { color: black;}");
    }
}

void pushFlowSettingsDlg::slotOnGetBitRate(unsigned char streamId, api_detu_client_av_param_t *res)
{
	if (streamId == 2){
		m_deviceInfo.av_param_t.nBitRate = res->nBitRate;
		m_deviceInfo.av_param_t.nFrameRate = res->nFrameRate;
		m_deviceInfo.av_param_t.nVideoHeight = res->nVideoHeight;
		m_deviceInfo.av_param_t.nVideoWidth = res->nVideoWidth;

		m_deviceInfo.av_param_t.nAudioEncoderType = res->nAudioEncoderType;
		m_deviceInfo.av_param_t.nBitRateType = res->nBitRateType;
		m_deviceInfo.av_param_t.nIFrameInterval = res->nIFrameInterval;
		m_deviceInfo.av_param_t.nIFrameIntervalUnit = res->nIFrameIntervalUnit;
		m_deviceInfo.av_param_t.nQuality = res->nQuality;
		m_deviceInfo.av_param_t.nVideoEncodeLevel = res->nVideoEncodeLevel;
		m_deviceInfo.av_param_t.nVideoEncoderType = res->nVideoEncoderType;
	}
}

void pushFlowSettingsDlg::slotOnClose()
{
	close();

	syncConnection(false);
}

void pushFlowSettingsDlg::slotOnPushFlowSuccess()
{
	ui->startBtn->setEnabled(true);

	QTimerManage::instance()->initTimer(m_deviceInfo.serialNo);

	//缓存推流地址
	QString pushFlowUrl = ui->comboBox->lineEdit()->text();
	int index = ui->comboBox->findText(pushFlowUrl);
	if (index != -1)
	{
		ui->comboBox->removeItem(index);
	}
	ui->comboBox->addItem(pushFlowUrl);

	m_deviceInfo.nServerId = m_currServerID;
	m_deviceInfo.isPushFlow = true;
	m_deviceInfo.szPushFlowUrl = pushFlowUrl;
	emit sigOnSyncData(m_deviceInfo);

	Feedback::instance()->tipsUI(TCS_TRANSCODE_SUCCESS, m_currServerID.toStdString(), 0);
	initPushFlowInfoPage();
}

void pushFlowSettingsDlg::slotOnPushFlowFailed()
{
	ui->startBtn->setEnabled(true);
	QTSocketManage::instance()->closeSocket();
	QMessageBox::warning(this, tr("warning"), tr("request on transcode failed !"));
}

void pushFlowSettingsDlg::slotOnCloseTranscode()
{
	ui->disconnectedBtn->setEnabled(true);

	QTimerManage::instance()->closeTimer(m_deviceInfo.serialNo);

	m_deviceInfo.isPushFlow = false;
	m_deviceInfo.szPushFlowUrl = "";
	emit sigOnSyncData(m_deviceInfo);

	QTSocketManage::instance()->closeSocket();
	Feedback::instance()->tipsUI(TCS_CLOSE_TRANSCODE_SUCCESS, m_currServerID.toStdString(), 0);

	initPushFlowPage();
}

void pushFlowSettingsDlg::slotOnReportTCSDisconnectError(std::string deviceID)
{
	ui->disconnectedBtn->setEnabled(true);

	QTimerManage::instance()->closeTimer(m_deviceInfo.serialNo);

	m_deviceInfo.isPushFlow = false;
	m_deviceInfo.szPushFlowUrl = "";
	emit sigOnSyncData(m_deviceInfo);

	QTSocketManage::instance()->closeSocket();
	initPushFlowPage();
}

void pushFlowSettingsDlg::slotOnReportTCSOffLine(int serverId)
{
	slotOnReportTCSDisconnectError("");
	int index = -1;
	for (int i = 0; i < m_TCSManageInfoList.size(); ++i)
	{
		if (m_TCSManageInfoList[i].nServerId.toInt() == serverId)
		{
			index = i;
		}
	}

	if (index > -1)
	{
		m_TCSManageInfoList.removeAt(index);
	}
}

void pushFlowSettingsDlg::slotOnUpdateTimer(int val, QString deviceID)
{
	if (deviceID == m_deviceInfo.serialNo)
	{
		QString time = commonFun::fomatFromSecond(val);
		ui->timeLabel->setText(QString(tr("time") + ":  %1").arg(time));
	}
}
