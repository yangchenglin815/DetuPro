#include "deviceSettingDlg.h"
#include "dmconnection.hpp"
#include "SocketManager.h"
#include "DetuPVMSIni.h"
#include "TcpDataManager.hpp"
#include "feedback.h"
#include "ViewSignal.h"

#include <QListView>
#include <QScrollBar>
#include <QMessageBox>

deviceSettingDlg::deviceSettingDlg(QWidget *parent)
	: QDialog(parent)
	, isDraggingWindow_(false)
	, isAutoRotate_(false)
	, setBitRateCount_(0)
	, direction_(0)
	, tipDlg(NULL)
{
	ui.setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	setModal(true);
	init();
	initConnect();
}

deviceSettingDlg::~deviceSettingDlg()
{

}

/*************************************************
������:    	initData
��������:	��ʼ��������Ϣ
�������:    info����ǰ�豸������Ϣ
�������:
����ֵ:
**************************************************/
void deviceSettingDlg::initData(deviceInfo info)
{
	m_info = info;
	ui.upBtn->setChecked(true);
	ui.vbrBtn->setChecked(true);
	ui.subVbrBtn->setChecked(true);
	ui.titleLabel->setText(info.serialNo);
	ui.nameLineEdit->setText(info.name);
	ui.subBitrateBox->setChecked(DetuPVMSIni::getStartSubBitRate());
	ui.resolutionBox->setCurrentIndex(0);
	ui.subResolutionBox->setCurrentIndex(1);
	ui.framerateBox->setCurrentIndex(1);
	ui.subFramerateBox->setText("25 fps");
	if (SocketManagerIns.isConnected()){
		getBitRate(1);
		if (ui.subBitrateBox->isChecked())
		{
			Sleep(500);
			getBitRate(2);
		}
		if (get_stream_thread_ && get_stream_thread_->joinable())
		{
			get_stream_thread_->join();
		}
		get_stream_thread_.reset(new boost::thread(&deviceSettingDlg::getStream, this));
	}
}

/*************************************************
������:    	getBitRate
��������:	��ȡ���ʵ���Ϣ����
�������:    streamId��1���������� 2����������
�������:
����ֵ:
**************************************************/
void deviceSettingDlg::getBitRate(int streamId)
{
	protocol_head_t api_head;
	api_detu_client_av_param_t api_detu;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_CLIENT_GET_AVPARAM;
	api_head.nDataLen = api_detu.get_size();
	api_head.nResult = 0x00;
	api_head.nStreamId = streamId;
	//api_head.nReserver = 0x01;        //Ԥ��λ
	api_head.nEndFlags = 0xFA;

	QString selectDevice = ui.titleLabel->text();
	memcpy(api_detu.szDeviceId, selectDevice.toLocal8Bit().data(), API_ARRAY_LEN);
	Log::Debug("Get BitRate: cmd:%d streamid:%d deviceId:%s", api_head.nCmd, api_head.nStreamId, selectDevice.toLocal8Bit().data());

	response res(api_head.get_size() + api_detu.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
	response_add_resprotocol<api_detu_client_av_param_t>(res, &api_detu);

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

/*************************************************
������:    	setBitRate
��������:	�������ʵ���Ϣ����
�������:    streamId��1���������� 2����������    bitRate������
�������:
����ֵ:
**************************************************/
void deviceSettingDlg::setBitRate(int streamId, QString bitRate)
{
	protocol_head_t api_head;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_CLIENT_SET_AVPARAM;
	api_head.nDataLen = av_param_1t_.get_size();
	api_head.nResult = 0x00;
	api_head.nStreamId = streamId;
	//api_head.nReserver = 0x01;        //Ԥ��λ
	api_head.nEndFlags = 0xFA;

	QStringList list;
	QString selectDevice = ui.titleLabel->text();
	if (streamId == 1)
	{
		av_param_1t_.nBitRate = bitRate.toInt();
		memcpy(av_param_1t_.szDeviceId, selectDevice.toLocal8Bit().data(), API_ARRAY_LEN);
		list = ui.resolutionBox->currentText().split("*");
		if (list.size() > 0)
		{
			av_param_1t_.nVideoWidth = list.at(0).toInt();
			av_param_1t_.nVideoHeight = list.at(1).toInt();
		}
		av_param_1t_.nFrameRate = ui.framerateBox->currentText().toInt();
		if (ui.vbrBtn->isChecked())
		{
			av_param_1t_.nBitRateType = 2;
		}
		if (ui.cbrBtn->isChecked())
		{
			av_param_1t_.nBitRateType = 1;
		}
		Log::Debug("Set BitRate: cmd:%d streamid:%d resolution:%d*%d frameRate:%d bitRateType:%d deviceId:%s", api_head.nCmd, api_head.nStreamId, av_param_1t_.nVideoWidth,
			av_param_1t_.nVideoHeight, av_param_1t_.nFrameRate, av_param_1t_.nBitRateType, selectDevice.toLocal8Bit().data());
	}
	else if (streamId == 2)
	{
		av_param_2t_.nBitRate = bitRate.toInt();
		memcpy(av_param_2t_.szDeviceId, selectDevice.toLocal8Bit().data(), API_ARRAY_LEN);
		list = ui.subResolutionBox->currentText().split("*");
		if (list.size() > 0)
		{
			av_param_2t_.nVideoWidth = list.at(0).toInt();
			av_param_2t_.nVideoHeight = list.at(1).toInt();
		}
		av_param_2t_.nFrameRate = ui.framerateBox->currentText().toInt();
		if (ui.subVbrBtn->isChecked())
		{
			av_param_2t_.nBitRateType = 2;
		}
		if (ui.subCbrBtn->isChecked())
		{
			av_param_2t_.nBitRateType = 1;
		}
		Log::Debug("Set BitRate: cmd:%d streamid:%d resolution:%d*%d frameRate:%d bitRateType:%d deviceId:%s", api_head.nCmd, api_head.nStreamId, av_param_2t_.nVideoWidth,
			av_param_2t_.nVideoHeight, av_param_2t_.nFrameRate, av_param_2t_.nBitRateType, selectDevice.toLocal8Bit().data());
	}

	response res(api_head.get_size() + av_param_1t_.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
	if (streamId == 1)
	{
		response_add_resprotocol<api_detu_client_av_param_t>(res, &av_param_1t_);
	}
	else if (streamId == 2)
	{
		response_add_resprotocol<api_detu_client_av_param_t>(res, &av_param_2t_);
	}

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

/*************************************************
������:    	initDirection
��������:	��ʼ���������
�������:    direction��1�����ϣ� 2�����£�
�������:
����ֵ:
**************************************************/
void deviceSettingDlg::initDirection(int direction)
{
	if (direction == 0)
	{
		ui.upBtn->setChecked(true);
		ui.downBtn->setChecked(false);
	}
	else if (direction == 1)
	{
		ui.upBtn->setChecked(false);
		ui.downBtn->setChecked(true);
	}
}

/*************************************************
������:    	getStream
��������:	��ȡ������
�������:
�������:
����ֵ:
**************************************************/
void deviceSettingDlg::getStream()
{
	protocol_head_t api_head;
	api_detu_client_av_param_t api_detu;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_CLIENT_GET_STREAM;
	api_head.nDataLen = api_detu.get_size();
	api_head.nResult = 0x00;
	api_head.nStreamId = 0;
	//api_head.nReserver = 0x01;        //Ԥ��λ
	api_head.nEndFlags = 0xFA;

	QString selectDevice = ui.titleLabel->text();
	memcpy(api_detu.szDeviceId, selectDevice.toLocal8Bit().data(), API_ARRAY_LEN);
	Log::Debug("Get BitRate: cmd:%d streamid:%d deviceId:%s", api_head.nCmd, api_head.nStreamId, selectDevice.toLocal8Bit().data());

	response res(api_head.get_size() + api_detu.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
	response_add_resprotocol<api_detu_client_av_param_t>(res, &api_detu);

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

/*************************************************
������:    	delStream
��������:	ɾ��������
�������:
�������:
����ֵ:
**************************************************/
void deviceSettingDlg::delStream()
{
	protocol_head_t api_head;
	api_detu_client_av_param_t api_detu;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_CLIENT_DEL_STREAM;
	api_head.nDataLen = api_detu.get_size();
	api_head.nResult = 0x00;
	api_head.nStreamId = 2;
	//api_head.nReserver = 0x01;        //Ԥ��λ
	api_head.nEndFlags = 0xFA;

	QString selectDevice = ui.titleLabel->text();
	memcpy(api_detu.szDeviceId, selectDevice.toLocal8Bit().data(), API_ARRAY_LEN);
	Log::Debug("Get BitRate: cmd:%d streamid:%d deviceId:%s", api_head.nCmd, api_head.nStreamId, selectDevice.toLocal8Bit().data());

	response res(api_head.get_size() + api_detu.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
	response_add_resprotocol<api_detu_client_av_param_t>(res, &api_detu);

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

/*************************************************
������:    	addStream
��������:	����������
�������:
�������:
����ֵ:
**************************************************/
void deviceSettingDlg::addStream()
{
	protocol_head_t api_head;
	api_detu_client_av_param_t api_detu;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_CLIENT_ADD_STREAM;
	api_head.nDataLen = api_detu.get_size();
	api_head.nResult = 0x00;
	api_head.nStreamId = 2;
	//api_head.nReserver = 0x01;        //Ԥ��λ
	api_head.nEndFlags = 0xFA;

	QString selectDevice = ui.titleLabel->text();
	memcpy(api_detu.szDeviceId, selectDevice.toLocal8Bit().data(), API_ARRAY_LEN);
	Log::Debug("Get BitRate: cmd:%d streamid:%d deviceId:%s", api_head.nCmd, api_head.nStreamId, selectDevice.toLocal8Bit().data());

	response res(api_head.get_size() + api_detu.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
	response_add_resprotocol<api_detu_client_av_param_t>(res, &api_detu);

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

/*************************************************
������:    	rebootM1Request
��������:	�����豸����
�������:
�������:
����ֵ:
**************************************************/
void deviceSettingDlg::rebootM1Request()
{
	protocol_head_t api_head;
	api_detu_client_av_param_t api_detu;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_CLIENT_DEVICE_REBOOT;
	api_head.nDataLen = api_detu.get_size();
	api_head.nResult = 0x00;
	api_head.nStreamId = 1;
	//api_head.nReserver = 0x01;        //Ԥ��λ
	api_head.nEndFlags = 0xFA;

	QString selectDevice = ui.titleLabel->text();
	memcpy(api_detu.szDeviceId, selectDevice.toLocal8Bit().data(), API_ARRAY_LEN);
	Log::Debug("Reboot Device: cmd:%d streamid:%d deviceId:%s", api_head.nCmd, api_head.nStreamId, selectDevice.toLocal8Bit().data());

	response res(api_head.get_size() + api_detu.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
	response_add_resprotocol<api_detu_client_av_param_t>(res, &api_detu);

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

void deviceSettingDlg::mouseMoveEvent(QMouseEvent *event)
{
	if (isDraggingWindow_) {
		this->move(event->globalPos() - lastMousePos_);
	}
}

void deviceSettingDlg::mousePressEvent(QMouseEvent *event)
{
	// current
	int x = event->pos().x();
	int y = event->pos().y();

	// top left
	int x1 = ui.titleWidget->pos().x();
	int y1 = ui.titleWidget->pos().y();

	// bottom right
	int x2 = x1 + ui.titleWidget->width();
	int y2 = y1 + ui.titleWidget->height();

	if (x > x1 && x < x2 && y > y1 && y < y2) {
		lastMousePos_ = event->pos();
		isDraggingWindow_ = true;
	}
}

void deviceSettingDlg::mouseReleaseEvent(QMouseEvent *event)
{
	isDraggingWindow_ = false;
}

/*************************************************
������:    	slotOnSave
��������:	���水�������ۺ���
�������:    
�������:
����ֵ:
**************************************************/
void deviceSettingDlg::slotOnSave()
{
	if (ui.nameLineEdit->text().isEmpty())
	{
		ui.nameLineEdit->setFocus();
		QMessageBox::warning(this, QStringLiteral("����"), QStringLiteral("��������Ϊ��"));
		return;
	}
	else if (ui.bitRateLineEdit->text().isEmpty())
	{
		ui.bitRateLineEdit->setFocus();
		QMessageBox::warning(this, QStringLiteral("����"), QStringLiteral("���ʲ���Ϊ��"));
		return;
	}
	else if (ui.subBitRateLineEdit->text().isEmpty())
	{
		ui.subBitRateLineEdit->setFocus();
		QMessageBox::warning(this, QStringLiteral("����"), QStringLiteral("���ʲ���Ϊ��"));
		return;
	}
	else
	{
		m_info.name = ui.nameLineEdit->text();
		if (ui.upBtn->isChecked())
		{
			direction_ = DIRECTION_TO_UP;
		}
		if (ui.downBtn->isChecked())
		{
			direction_ = DIRECTION_TO_DOWN;
		}
		m_info.is_up_down = direction_;
		emit sigOnSave(m_info);
		if (SocketManagerIns.isConnected()){
			switch (ui.resolutionBox->currentIndex())
			{
			case 0:
			case 1:
			case 2:
				checkoutBitRate(2048, 8192);
				break;
			case 3:
				checkoutBitRate(1024, 6144);
				break;
			case 4:
				checkoutBitRate(1024, 4096);
				break;
			default:
				break;
			}
		}
	}
}

void deviceSettingDlg::slotOnCancel()
{
	this->close();
	DetuPVMSIni::setGlobalSettingGet(false);
}

/*************************************************
������:    	slotOnGetBitRate
��������:	�������ʵȷ��زۺ���
�������:    streamId����ID��1��������  2����������    res����������
�������:
����ֵ:
**************************************************/
void deviceSettingDlg::slotOnGetBitRate(unsigned char streamId, api_detu_client_av_param_t* res)
{
	Log::Debug("get bitRate:%d resolution:%d*%d frameRate:%d bitRateType:%d streamId:%d", res->nBitRate, res->nVideoWidth, res->nVideoHeight, 
		res->nFrameRate, res->nBitRateType, streamId);
	if (streamId == 1)
	{
		ui.bitRateLineEdit->setText(QString::number(res->nBitRate));
		ui.resolutionBox->setCurrentText(QString("%1*%2").arg(res->nVideoWidth).arg(res->nVideoHeight));
		ui.framerateBox->setCurrentText(QString("%1").arg(res->nFrameRate));
		slotOnTipBitrate(ui.resolutionBox->currentIndex());
		if (res->nBitRateType == 2)
		{
			ui.vbrBtn->setChecked(true);
		}
		else
		{
			ui.cbrBtn->setChecked(true);
		}
		av_param_1t_.nAudioEncoderType = res->nAudioEncoderType;
		av_param_1t_.nBitRate = res->nBitRate;
		av_param_1t_.nBitRateType = res->nBitRateType;
		av_param_1t_.nFrameRate = res->nFrameRate;
		av_param_1t_.nIFrameInterval = res->nIFrameInterval;
		av_param_1t_.nIFrameIntervalUnit = res->nIFrameIntervalUnit;
		av_param_1t_.nQuality = res->nQuality;
		av_param_1t_.nVideoEncodeLevel = res->nVideoEncodeLevel;
		av_param_1t_.nVideoEncoderType = res->nVideoEncoderType;
		av_param_1t_.nVideoHeight = res->nVideoHeight;
		av_param_1t_.nVideoWidth = res->nVideoWidth;
	}
	else if (streamId == 2)
	{
		ui.subBitRateLineEdit->setText(QString::number(res->nBitRate));
		ui.subResolutionBox->setCurrentText(QString("%1*%2").arg(res->nVideoWidth).arg(res->nVideoHeight));
		ui.subFramerateBox->setText(QString("%1 fps").arg(res->nFrameRate));
		if (res->nBitRateType == 2)
		{
			ui.subVbrBtn->setChecked(true);
		}
		else
		{
			ui.subCbrBtn->setChecked(true);
		}
		av_param_2t_.nAudioEncoderType = res->nAudioEncoderType;
		av_param_2t_.nBitRate = res->nBitRate;
		av_param_2t_.nBitRateType = res->nBitRateType;
		av_param_2t_.nFrameRate = res->nFrameRate;
		av_param_2t_.nIFrameInterval = res->nIFrameInterval;
		av_param_2t_.nIFrameIntervalUnit = res->nIFrameIntervalUnit;
		av_param_2t_.nQuality = res->nQuality;
		av_param_2t_.nVideoEncodeLevel = res->nVideoEncodeLevel;
		av_param_2t_.nVideoEncoderType = res->nVideoEncoderType;
		av_param_2t_.nVideoHeight = res->nVideoHeight;
		av_param_2t_.nVideoWidth = res->nVideoWidth;
	}
	//���汾�εķֱ��ʺ�֡���Ա��ڱ���ʱУ��
	mResolution = ui.resolutionBox->currentText();
	mFramerate = ui.framerateBox->currentText();
	mSubResolution = ui.subResolutionBox->currentText();
	mSubFramerate = ui.framerateBox->currentText();
}

/*************************************************
������:    	slotOnSetBitRate
��������:	�������ʵȷ��زۺ���
�������:    streamId����ID��1��������  2����������    is_ok������ɹ���־λ
�������: 
����ֵ:
**************************************************/
void deviceSettingDlg::slotOnSetBitRate(unsigned char streamId, bool is_ok)
{
	if (is_ok)
	{
		if (ui.subBitrateBox->isChecked())
		{
			if (streamId == 2)
			{
				Feedback::instance()->maskUI(SETTINGS_SUCCESS);
				checkout(true);
			}
		}
		else
		{
			if (streamId == 1)
			{
				Feedback::instance()->maskUI(SETTINGS_SUCCESS);
				checkout(false);
			}
		}
	}
	else
	{
		if (ui.subBitrateBox->isChecked())
		{
			if (streamId == 2)
			{
				Feedback::instance()->maskUI(SETTINGS_FAILED);
			}
		}
		else
		{
			if (streamId == 1)
			{
				Feedback::instance()->maskUI(SETTINGS_FAILED);
			}
		}
	}
}

void deviceSettingDlg::slotOnSetAutoCircle()
{
// 	isAutoRotate = !isAutoRotate;
// 	if (isAutoRotate)
// 	{
// 		ui.autoCircleBtn->setStyleSheet("border-image:url(:/image/image/effectsb.png);");
// 	}
// 	else
// 	{
// 		ui.autoCircleBtn->setStyleSheet("border-image:url(:/image/image/effects.png);");
// 	}
// 	QString deviceId = ui.titleLabel->text();
// 	emit sigOnSetAutoCircle(isAutoRotate, deviceId);
}

/*************************************************
������:    	slotOnScrollMove
��������:	�������ƶ��ۺ���
�������:    
�������:
����ֵ:
**************************************************/
void deviceSettingDlg::slotOnScrollMove()
{
	QScrollBar *scrollBar = ui.scrollArea->verticalScrollBar();
	if (sender() == ui.settingsBtn)
	{
		scrollBar->setValue(0);
	}
	else if (sender() == ui.bitSettingsBtn)
	{
		scrollBar->setValue(ui.label_4->pos().y() - 10);
	}
	else if (sender() == ui.subBitSettingsBtn)
	{
		scrollBar->setValue(ui.label_11->pos().y() - 10);
	}
}

/*************************************************
������:    	slotOnStartSubBit
��������:	�����������رղۺ���
�������:    chceked��������������־λ
�������:
����ֵ:
**************************************************/
void deviceSettingDlg::slotOnStartSubBit(bool chceked)
{
	if (chceked)
	{
		ui.widget->setVisible(true);
		if (SocketManagerIns.isConnected())
		{
			addStream();
		}
	}
	else
	{
		ui.widget->setVisible(false);
		if (SocketManagerIns.isConnected())
		{
			delStream();
		}
	}
}

/*************************************************
������:    	slotOnHandleStreamSuccess
��������:	������ɹ����زۺ���
�������:    streamId����ID ��1��������  2��������  3��������+��������
�������:
����ֵ:
**************************************************/
void deviceSettingDlg::slotOnHandleStreamSuccess(unsigned char streamId)
{
	switch (streamId)
	{
	case 1:
		ui.widget->setVisible(false);
		ui.subBitrateBox->setChecked(false);
		break;
	case 3:
		ui.widget->setVisible(true);
		ui.subBitrateBox->setChecked(true);
	    break;
	}
}

/*************************************************
������:    	slotOnRebootM1
��������:	ȷ������M1�ۺ���
�������:
�������:
����ֵ:
**************************************************/
void deviceSettingDlg::slotOnRebootM1()
{
	if (tipDlg != NULL)
	{
		tipDlg->close();
	}
	if (reboot_device_thread_ && reboot_device_thread_->joinable())
	{
		reboot_device_thread_->join();
	}
	reboot_device_thread_.reset(new boost::thread(&deviceSettingDlg::rebootM1Request, this));
	ViewSignal::instance()->sigOnRebootM1ResetPlayer(m_info.id);
}

/*************************************************
������:    	slotOnRebootDeviceSuccess
��������:	�豸�����ɹ����زۺ���
�������:    streamId��1��M1��   2��NVR��
�������:
����ֵ:
**************************************************/
void deviceSettingDlg::slotOnRebootDeviceSuccess(unsigned char streamId)
{
	if (streamId == 1)
	{
		if (tipDlg != NULL)
		{
               //����ȴ�����г�ʱ�ȴ�M1�������
		}
	}
}

/*************************************************
������:    	slotOnResetFramerate
��������:	����������֡��
�������:    framerate����Ӧ���ݵ��������޸ĺ��֡��
�������:
����ֵ:
**************************************************/
void deviceSettingDlg::slotOnResetFramerate(QString framerate)
{
	ui.subFramerateBox->setText(QString("%1 fps").arg(framerate));
}

/*************************************************
������:    	slotOnTipBitrate
��������:	��ע��ѡ�ֱ��ʵ����ʷ�Χ
�������:    index����ѡ�ֱ��ʵ�����
�������:
����ֵ:
**************************************************/
void deviceSettingDlg::slotOnTipBitrate(int index)
{
	switch (index)
	{
	case 0:
	case 1:
	case 2:
		ui.showLabbel->setText(QStringLiteral("kbps  ��2048~8192��"));
		break;
	case 3:
		ui.showLabbel->setText(QStringLiteral("kbps  ��1024~6144��"));
		break;
	case 4:
		ui.showLabbel->setText(QStringLiteral("kbps  ��1024~4096��"));
		break;
	default:
		break;
	}
}

/*************************************************
������:    	init
��������:	��ʼ������
�������:
�������:
����ֵ:
**************************************************/
void deviceSettingDlg::init()
{
	QButtonGroup *installModeGroup = new QButtonGroup(this);
	installModeGroup->addButton(ui.upBtn);
	installModeGroup->addButton(ui.downBtn);
	QButtonGroup *decodeModeGroup = new QButtonGroup(this);
	decodeModeGroup->addButton(ui.vbrBtn);
	decodeModeGroup->addButton(ui.cbrBtn);
	QButtonGroup *subDecodeModeGroup = new QButtonGroup(this);
	subDecodeModeGroup->addButton(ui.subVbrBtn);
	subDecodeModeGroup->addButton(ui.subCbrBtn);
	QButtonGroup *ctrlGroup = new QButtonGroup(this);
	ctrlGroup->addButton(ui.settingsBtn);
	ctrlGroup->addButton(ui.bitSettingsBtn);
	ctrlGroup->addButton(ui.subBitSettingsBtn);
	
	//�������ֱ����б�
	QStringList resolutionItemsList = QStringList()
		<< "3072*2048"       //Ĭ��
		<< "2640*1760"
		<< "2400*1600"
		<< "2160*1440"
		<< "1536*1024";
	ui.resolutionBox->addItems(resolutionItemsList);
	ui.resolutionBox->setView(new QListView());
	//�������ֱ����б�
	QStringList subResolutionItemsList = QStringList()
		<< "1440*960"
		<< "1104*736"    //Ĭ��
		<< "960*640"
		<< "720*480";
	ui.subResolutionBox->addItems(subResolutionItemsList);
	ui.subResolutionBox->setView(new QListView());
	//֡���б�
	QStringList framerateItemsList = QStringList()
		<< "20"
		<< "25"    //Ĭ��
		<< "30";
	ui.framerateBox->addItems(framerateItemsList);
	ui.framerateBox->setView(new QListView());
}

/*************************************************
������:    	initConnect
��������:	��ʼ���źŲ�
�������:
�������:
����ֵ:
**************************************************/
void deviceSettingDlg::initConnect()
{
	connect(ui.cancelBtn, SIGNAL(clicked()), this, SLOT(slotOnCancel()));
	connect(ui.saveBtn, SIGNAL(clicked()), this, SLOT(slotOnSave()));
	connect(ui.settingsBtn, SIGNAL(clicked()), this, SLOT(slotOnScrollMove()));
	connect(ui.bitSettingsBtn, SIGNAL(clicked()), this, SLOT(slotOnScrollMove()));
	connect(ui.subBitSettingsBtn, SIGNAL(clicked()), this, SLOT(slotOnScrollMove()));
	connect(ui.subBitrateBox, SIGNAL(clicked(bool)), this, SLOT(slotOnStartSubBit(bool)));
	connect(ui.framerateBox, SIGNAL(activated(QString)), this, SLOT(slotOnResetFramerate(QString)));
	connect(ui.resolutionBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotOnTipBitrate(int)));
	//connect(ui.autoCircleBtn, SIGNAL(clicked()), this, SLOT(slotOnSetAutoCircle()));
	qRegisterMetaType<api_detu_client_av_param_t>("api_detu_client_av_param_t");
	connect(&TcpDataManagerIns, SIGNAL(sigOnGetBitRate(unsigned char, api_detu_client_av_param_t*)), this, SLOT(slotOnGetBitRate(unsigned char, api_detu_client_av_param_t*)));
	connect(&TcpDataManagerIns, SIGNAL(sigOnSetBitRate(unsigned char, bool)), this, SLOT(slotOnSetBitRate(unsigned char, bool)));
	connect(&TcpDataManagerIns, SIGNAL(sigOnHandleStreamSuccess(unsigned char)), this, SLOT(slotOnHandleStreamSuccess(unsigned char)));
	connect(&TcpDataManagerIns, SIGNAL(sigOnRebootDeviceSuccess(unsigned char)), this, SLOT(slotOnRebootDeviceSuccess(unsigned char)));
}

/*************************************************
������:    	reportDeviceName
��������:	�ϱ���Ӧnvr ID�ı���
�������:    name���豸����      deviceId���豸ID
�������:
����ֵ:
**************************************************/
void deviceSettingDlg::reportDeviceName(QString name, QString deviceId)
{
	protocol_head_t api_head;
	api_detu_client_register_res_t api_detu;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_REPORT_NAME;
	api_head.nDataLen = api_detu.get_size();
	api_head.nResult = 0x00;
	api_head.nStreamId = 0;
	//api_head.nReserver = 0x01;        //Ԥ��λ
	api_head.nEndFlags = 0xFA;

	memcpy(api_detu.szDeviceId, deviceId.toLocal8Bit().data(), API_ARRAY_LEN);
 	memcpy(api_detu.szName, name.toLocal8Bit().data(), API_ARRAY_LEN);
	api_detu.szUpDown = direction_;
	Log::Debug("report deviceId:%s name:%s to server", deviceId.toLocal8Bit().data(), name.toLocal8Bit().data());
	
	response res(api_head.get_size() + api_detu.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
	response_add_resprotocol<api_detu_client_register_res_t>(res, &api_detu);

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

/*************************************************
������:    	checkout
��������:	У���Ƿ���Ҫ����M1
�������:    subChecked���������򿪱�־λ
�������:
����ֵ:
**************************************************/
void deviceSettingDlg::checkout(bool subChecked)
{
	if (subChecked)
	{
		if (mResolution == ui.resolutionBox->currentText() && mFramerate == ui.framerateBox->currentText()
			&& mSubResolution == ui.subResolutionBox->currentText() && mSubFramerate == ui.framerateBox->currentText())
		{
			return;
		}
		else
		{
			//���������ʾ
			rebootM1Tip();
		}
	}
	else
	{
		if (mResolution == ui.resolutionBox->currentText() && mFramerate == ui.framerateBox->currentText())
		{
			return;
		}
		else
		{
			//���������ʾ
			rebootM1Tip();
		}
	}
}

/*************************************************
������:    	rebootM1Tip
��������:	����M1��ʾ��
�������:  
�������:
����ֵ:
**************************************************/
void deviceSettingDlg::rebootM1Tip()
{
	if (tipDlg == NULL)
	{
		tipDlg = new commonTipDlg;
		connect(tipDlg, SIGNAL(sigOnConfirm()), this, SLOT(slotOnRebootM1()));
	}
	tipDlg->setTitleLabelText(QStringLiteral("M1������ʾ"));
	tipDlg->setTipText(QStringLiteral("M1���������÷ֱ���/֡����Ч���Ƿ�Ҫ����M1��"));
	tipDlg->activateWindow();
	QPoint point = this->mapToGlobal(this->pos());
	int x = point.x();
	int y = point.y();
	int xx = this->width();
	int yy = tipDlg->width();
	int nX = (this->width() - tipDlg->width() + x) / 2;
	int nY = (this->height() - tipDlg->height() + y) / 2;
	tipDlg->move(nX, nY);
	tipDlg->exec();
}

/*************************************************
������:    	checkoutBitRate
��������:	У������
�������:    min����С����    max���������
�������:
����ֵ:
**************************************************/
void deviceSettingDlg::checkoutBitRate(int min, int max)
{
	int bitRate = ui.bitRateLineEdit->text().toInt();
	int subBitRate = ui.subBitRateLineEdit->text().toInt();
	QString name = ui.nameLineEdit->text();
	QString deviceId = ui.titleLabel->text();
	if (bitRate >= min && bitRate <= max && subBitRate >= 500 && subBitRate <= 3000)
	{
		setBitRate(1, ui.bitRateLineEdit->text());
		if (ui.subBitrateBox->isChecked())
		{
			Sleep(500);
			setBitRate(2, ui.subBitRateLineEdit->text());
			ViewSignal::instance()->sigOnHandleSubStreamMessage(true, m_info.serialNo, m_info.id);
		}
		else
		{
			//�ر�������ʱͬ���ر�������������Ϣ����
			ViewSignal::instance()->sigOnHandleSubStreamMessage(false, m_info.serialNo, m_info.id);
		}
		//�ϱ��豸����
		reportDeviceName(name, deviceId);
	}
	else
	{
		Feedback::instance()->maskUI(WARN_BITRATE);
	}
}
