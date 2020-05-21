#include "systemSettingDlg.h"
#include "DetuPVMSIni.h"
#include "APIProtocol.h"
#include "logging.hpp"
#include "response.hpp"
#include "TcpDataManager.hpp"
#include "dmconnection.hpp"
#include "SocketManager.h"
#include "feedback.h"
#include "constStruct.h"
#include "socketRequest.h"
#include "SetAdminMananger.h"

#include <QFileDialog>
using namespace dm::server;
systemSettingDlg::systemSettingDlg(QDialog *parent)
: QDialog(parent)
, scrollBar_(NULL)
, isDraggingWindow_(false)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint/* | Qt::WindowStaysOnTopHint*/);
	setModal(true);
	setAttribute(Qt::WA_TranslucentBackground);
	init();
	initConnect();
}

systemSettingDlg::~systemSettingDlg()
{

}

bool systemSettingDlg::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui.systemSettingBtn)
    {
		if (event->type() == QEvent::MouseButtonPress)
		{
			ui.systemSettingLbl->setStyleSheet("background-color:#eeeeee;");
			ui.decodeLbl->setStyleSheet(QString("#decodeLbl{color:#666666;font - family:%1;font - size:12px;line - height:12px;text - align:right;}#decodeLbl:hover{background-color:#F5F5F5;}").arg("Î¢ÈíÑÅºÚ"));
	//		ui.bitStreamLbl->setStyleSheet(QString("#bitStreamLbl{color:#666666;font - family:%1;font - size:12px;line - height:12px;text - align:right;}#bitStreamLbl:hover{background-color:#F5F5F5;}").arg("Î¢ÈíÑÅºÚ"));
			ui.fileSaveLbl->setStyleSheet(QString("#fileSaveLbl{color:#666666;font - family:%1;font - size:12px;line - height:12px;text - align:right;}#fileSaveLbl:hover{background-color:#F5F5F5;}").arg("Î¢ÈíÑÅºÚ"));
			scrollBar_->setValue(0);
			ui.resetTCSBtn->setChecked(false);
		}
    }
	if (watched == ui.decodeBtn)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			ui.decodeLbl->setStyleSheet("background-color:#eeeeee;");
			ui.systemSettingLbl->setStyleSheet(QString("#systemSettingLbl{color:#666666;font - family:%1;font - size:12px;line - height:12px;text - align:right;}#systemSettingLbl:hover{background-color:#F5F5F5;}").arg("Î¢ÈíÑÅºÚ"));
		//	ui.bitStreamLbl->setStyleSheet(QString("#bitStreamLbl{color:#666666;font - family:%1;font - size:12px;line - height:12px;text - align:right;}#bitStreamLbl:hover{background-color:#F5F5F5;}").arg("Î¢ÈíÑÅºÚ"));
			ui.fileSaveLbl->setStyleSheet(QString("#fileSaveLbl{color:#666666;font - family:%1;font - size:12px;line - height:12px;text - align:right;}#fileSaveLbl:hover{background-color:#F5F5F5;}").arg("Î¢ÈíÑÅºÚ"));
			scrollBar_->setValue(ui.label_12->pos().y() - 10);
			ui.resetTCSBtn->setChecked(false);
		}
	}
// 	if (watched == ui.bitStreamBtn)
// 	{
// 		if (event->type() == QEvent::MouseButtonPress)
// 		{
// 			ui.bitStreamLbl->setStyleSheet("background-color:#eeeeee;");
// 			ui.systemSettingLbl->setStyleSheet(QString("#systemSettingLbl{color:#666666;font - family:%1;font - size:12px;line - height:12px;text - align:right;}#systemSettingLbl:hover{background-color:#F5F5F5;}").arg("Î¢ÈíÑÅºÚ"));
// 			ui.decodeLbl->setStyleSheet(QString("#decodeLbl{color:#666666;font - family:%1;font - size:12px;line - height:12px;text - align:right;}#decodeLbl:hover{background-color:#F5F5F5;}").arg("Î¢ÈíÑÅºÚ"));
// 			ui.fileSaveLbl->setStyleSheet(QString("#fileSaveLbl{color:#666666;font - family:%1;font - size:12px;line - height:12px;text - align:right;}#fileSaveLbl:hover{background-color:#F5F5F5;}").arg("Î¢ÈíÑÅºÚ"));
// 			scrollBar->setValue(ui.label_12->pos().y() - 10);
// 		}
// 	}
	if (watched == ui.fileSaveBtn)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			ui.fileSaveLbl->setStyleSheet("background-color:#eeeeee;");
			ui.systemSettingLbl->setStyleSheet(QString("#systemSettingLbl{color:#666666;font - family:%1;font - size:12px;line - height:12px;text - align:right;}#systemSettingLbl:hover{background-color:#F5F5F5;}").arg("Î¢ÈíÑÅºÚ"));
		//	ui.bitStreamLbl->setStyleSheet(QString("#bitStreamLbl{color:#666666;font - family:%1;font - size:12px;line - height:12px;text - align:right;}#bitStreamLbl:hover{background-color:#F5F5F5;}").arg("Î¢ÈíÑÅºÚ"));
			ui.decodeLbl->setStyleSheet(QString("#decodeLbl{color:#666666;font - family:%1;font - size:12px;line - height:12px;text - align:right;}#decodeLbl:hover{background-color:#F5F5F5;}").arg("Î¢ÈíÑÅºÚ"));
			scrollBar_->setValue(ui.label_12->pos().y() - 10);
			ui.resetTCSBtn->setChecked(false);
		}
	}
	if (watched == ui.AdminLabel)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{

		}
	}
	return true;
}

void systemSettingDlg::mouseMoveEvent(QMouseEvent *event)
{
	if (isDraggingWindow_) {
		this->move(event->globalPos() - lastMousePos_);
	}
}

void systemSettingDlg::mousePressEvent(QMouseEvent *event)
{
	// current
	int x = event->pos().x();
	int y = event->pos().y();

	// top left
	int x1 = ui.topWidget->pos().x();
	int y1 = ui.topWidget->pos().y();

	// bottom right
	int x2 = x1 + ui.topWidget->width();
	int y2 = y1 + ui.topWidget->height();

	if (x > x1 && x < x2 && y > y1 && y < y2) {
		lastMousePos_ = event->pos();
		isDraggingWindow_ = true;
	}
}

void systemSettingDlg::mouseReleaseEvent(QMouseEvent *event)
{
	isDraggingWindow_ = false;
}

void systemSettingDlg::slotOnSave()
{
	saveSystemSettings();
	saveDecodeSettings();
	saveBitStreamSettings();
	saveCaptureSettings();
	this->close();
	Feedback::instance()->maskUI(SETTINGS_SUCCESS);
}

void systemSettingDlg::slotOnSetCapturePath()
{
	QString save_path = QFileDialog::getExistingDirectory(this, QStringLiteral("ÇëÑ¡Ôñ´æ´¢Ä¿Â¼"), QApplication::applicationDirPath());
	if (save_path.isEmpty())
	{
		return;
	}
	ui.fileSaveLineEdit->setText(save_path);
}

void systemSettingDlg::slotOnStepOnReset()
{
	ui.systemSettingLbl->setStyleSheet(QString("#systemSettingLbl{color:#666666;font - family:%1;font - size:12px;line - height:12px;text - align:right;}#systemSettingLbl:hover{background-color:#F5F5F5;}").arg("Î¢ÈíÑÅºÚ"));
	ui.decodeLbl->setStyleSheet(QString("#decodeLbl{color:#666666;font - family:%1;font - size:12px;line - height:12px;text - align:right;}#decodeLbl:hover{background-color:#F5F5F5;}").arg("Î¢ÈíÑÅºÚ"));
	ui.fileSaveLbl->setStyleSheet(QString("#fileSaveLbl{color:#666666;font - family:%1;font - size:12px;line - height:12px;text - align:right;}#fileSaveLbl:hover{background-color:#F5F5F5;}").arg("Î¢ÈíÑÅºÚ"));
	scrollBar_->setValue(ui.label_12->pos().y());
}

void systemSettingDlg::slotOnResetTCSConfig()
{
	socketRequest::instance()->requestOnResetTCSConfig();
}

void systemSettingDlg::slotOnSetAdmin()
{
	//ÉèÖÃ±¾µØÅäÖÃÎÄ¼þ£¬ÊÇ·ñÎª¹ÜÀíÔ±ÕË»§
	if (DetuPVMSIni::getIsAdminUser())
	{
		SetAdminManangerIns.setAdmin(false);
		DetuPVMSIni::setIsAdminUser(false);
		Feedback::instance()->maskUI(SET_NOT_ADMIN);
	}
	else
	{
		SetAdminManangerIns.setAdmin(true);
		DetuPVMSIni::setIsAdminUser(true);
		Feedback::instance()->maskUI(SET_ADMIN);
	}

	//Í¨Öª·þÎñÆ÷£¬¸üÐÂÊý¾Ý¿â
}

void systemSettingDlg::init()
{
	QRegExp regx("[1-9][0-9]+$");
	QValidator *validator = new QRegExpValidator(regx, this);
	ui.portLineEdit->setValidator(validator);
	ui.portLineEdit->setMaxLength(5);
	ui.heartLineEdit->setValidator(new QIntValidator(3, 86400, this));
	scrollBar_ = ui.scrollArea->verticalScrollBar();
	ui.systemSettingBtn->installEventFilter(this);
	ui.decodeBtn->installEventFilter(this);
	ui.fileSaveBtn->installEventFilter(this);
	QButtonGroup *decodeGroup = new QButtonGroup(this);
	decodeGroup->addButton(ui.hardDecodeBtn);
	decodeGroup->addButton(ui.sorfDecodeBtn);
	QButtonGroup *subDecodeGroup = new QButtonGroup(this);
	subDecodeGroup->addButton(ui.subHardDecodeBtn);
	subDecodeGroup->addButton(ui.subSoftDecodeBtn);

	ui.AdminBtn->setVisible(false);
	ui.AdminLabel->setVisible(false);
}

void systemSettingDlg::initConnect()
{
	connect(ui.closeBtn, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.cancelBtn, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.saveBtn, SIGNAL(clicked()), this, SLOT(slotOnSave()));
	connect(ui.scanBtn, SIGNAL(clicked()), this, SLOT(slotOnSetCapturePath()));
	connect(ui.resetTCSBtn, SIGNAL(clicked()), this, SLOT(slotOnStepOnReset()));
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(slotOnResetTCSConfig()));
	connect(ui.AdminBtn, SIGNAL(clicked()), this, SLOT(slotOnSetAdmin()));

}

void systemSettingDlg::initData()
{
	ui.systemSettingLbl->setStyleSheet("background-color:#eeeeee;");
	initSystemSettings();
	initDecodeSettings();
	initCaptureSettings();
	initAdminSettings();
}

void systemSettingDlg::initSystemSettings()
{
	ui.ipLineEdit->setText(DetuPVMSIni::getServerIP());
	ui.portLineEdit->setText(DetuPVMSIni::getServerPort());
	ui.heartLineEdit->setText(QString::number(DetuPVMSIni::getHeartBeat()));
}

void systemSettingDlg::initDecodeSettings()
{
	if (DetuPVMSIni::getDecodeMode())
	{
		ui.hardDecodeBtn->setChecked(true);
		ui.sorfDecodeBtn->setChecked(false);
	}
	else
	{
		ui.hardDecodeBtn->setChecked(false);
		ui.sorfDecodeBtn->setChecked(true);
	}
	if (DetuPVMSIni::getSubDecodeMode())
	{
		ui.subHardDecodeBtn->setChecked(true);
		ui.subSoftDecodeBtn->setChecked(false);
	}
	else
	{
		ui.subHardDecodeBtn->setChecked(false);
		ui.subSoftDecodeBtn->setChecked(true);
	}
}

void systemSettingDlg::initCaptureSettings()
{
	ui.fileSaveLineEdit->setText(DetuPVMSIni::getCapturePath());
	TcpDataManagerIns.setCapturePath(DetuPVMSIni::getCapturePath());
}

void systemSettingDlg::initAdminSettings()
{
	if (DetuPVMSIni::getIsAdminUser())
	{
		ui.AdminBtn->setText(QStringLiteral("ÉèÖÃµ±Ç°ÕË»§Îª·Ç¹ÜÀíÔ±"));
	}
	else
	{
		ui.AdminBtn->setText(QStringLiteral("ÉèÖÃµ±Ç°ÕË»§Îª¹ÜÀíÔ±"));
	}
}

void systemSettingDlg::saveSystemSettings()
{
	if (!ui.ipLineEdit->text().isEmpty())
	{
		DetuPVMSIni::setServerIP(ui.ipLineEdit->text());
	}
	if (!ui.portLineEdit->text().isEmpty())
	{
		DetuPVMSIni::setServerPort(ui.portLineEdit->text());
	}
	if (!ui.heartLineEdit->text().isEmpty())
	{
		DetuPVMSIni::setHeartBeat(ui.heartLineEdit->text().toInt());
	}
}

void systemSettingDlg::saveDecodeSettings()
{
	if (ui.hardDecodeBtn->isChecked())
	{
		DetuPVMSIni::setDecodeMode(true);
	}
	if (ui.sorfDecodeBtn->isChecked())
	{
		DetuPVMSIni::setDecodeMode(false);
	}
	if (ui.subHardDecodeBtn->isChecked())
	{
		DetuPVMSIni::setSubDecodeMode(true);
	}
	if (ui.subSoftDecodeBtn->isChecked())
	{
		DetuPVMSIni::setSubDecodeMode(false);
	}
}

void systemSettingDlg::saveBitStreamSettings()
{
// 	if (ui.playBitStreamBtn->isChecked())
// 	{
// 		DetuPVMSIni::setPlayRtmpUrl("0");
// 	}
// 	if (ui.subPlayBitStreamBtn->isChecked())
// 	{
// 		DetuPVMSIni::setPlayRtmpUrl("1");
// 	}
// 	if (ui.replayBitStreamBtn->isChecked())
// 	{
// 		DetuPVMSIni::setReplayRtmpUrl("2");
// 	}
// 	if (ui.subReplayBitStreamBtn->isChecked())
// 	{
// 		DetuPVMSIni::setReplayRtmpUrl("3");
// 	}
}

void systemSettingDlg::saveCaptureSettings()
{
	if (!ui.fileSaveLineEdit->text().isEmpty())
	{
		DetuPVMSIni::setCapturePath(ui.fileSaveLineEdit->text());
		TcpDataManagerIns.setCapturePath(ui.fileSaveLineEdit->text());
	}
}