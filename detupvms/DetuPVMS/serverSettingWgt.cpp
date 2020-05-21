#include "serverSettingWgt.h"
#include "DetuPVMSIni.h"
#include "logging.hpp"

serverSettingWgt::serverSettingWgt(QWidget *parent)
	: QWidget(parent)
	, mov_(NULL)
{
	ui.setupUi(this);
	initConnect();
	init();
}

serverSettingWgt::~serverSettingWgt()
{
	if (mov_ != NULL)
	{
		mov_->deleteLater();
		mov_ = NULL;
	}
}

void serverSettingWgt::serverConnectFailed()
{
	mov_->stop();
	ui.stackedWidget->setCurrentWidget(ui.tipPage);
	QString ip = DetuPVMSIni::getServerIP();
	QString port = DetuPVMSIni::getServerPort();
	ui.tipLabel->setText(QStringLiteral("�޷����ӵ�������%1:%2��ȷ�Ϸ������Ƿ�������").arg(ip).arg(port));
}

void serverSettingWgt::slotOnConfirm()
{
	Log::Debug("connect to server!");
	QString text = ui.ipLineEdit->text();
	if (!ui.ipLineEdit->getText())
    {
		ui.ipLineEdit->setFocus();
		ui.warnLabel->setText(QStringLiteral("ip����Ϊ��"));
		return;
    }
	else if (ui.portLineEdit->text().isEmpty())
	{
		ui.portLineEdit->setFocus();
		ui.warnLabel->setText(QStringLiteral("�˿ڲ���Ϊ��"));
		return;
	}
	else
	{
		ui.warnLabel->setText("");
		DetuPVMSIni::setServerPort(ui.portLineEdit->text());
		DetuPVMSIni::setServerIP(ui.ipLineEdit->text());
		emit sigOnConfirm();
		mov_->start();
		ui.stackedWidget->setCurrentWidget(ui.progressPage);
	}
}

void serverSettingWgt::slotONReconnect()
{
	Log::Debug("reconnect to server!");
	ui.stackedWidget->setCurrentWidget(ui.progressPage);
	mov_->start();
	emit sigOnConfirm();
}

void serverSettingWgt::slotModifyIP()
{
	ui.stackedWidget->setCurrentWidget(ui.settingsPage);
}

void serverSettingWgt::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter){
		slotOnConfirm();
	}
}

void serverSettingWgt::initConnect()
{
	connect(ui.confirmBtn, SIGNAL(clicked()), this, SLOT(slotOnConfirm()));
	connect(ui.cancelBtn, SIGNAL(clicked()), this, SIGNAL(sigOnCancel()));
	connect(ui.reconnectBtn, SIGNAL(clicked()), this, SLOT(slotONReconnect()));
	connect(ui.modifyBtn, SIGNAL(clicked()), this, SLOT(slotModifyIP()));
}

void serverSettingWgt::init()
{
	ui.stackedWidget->setCurrentWidget(ui.settingsPage);
	ui.portLineEdit->setMaxLength(5);
	QRegExp regx("[1-9][0-9]+$");
	QValidator *validator = new QRegExpValidator(regx, this);
	ui.portLineEdit->setValidator(validator);
	setTabOrder(ui.ipLineEdit, ui.portLineEdit);
	setTabOrder(ui.portLineEdit, ui.confirmBtn);
	setTabOrder(ui.confirmBtn, ui.cancelBtn);
	if (mov_ == NULL)
	{
		mov_ = new QMovie(":/image/image/loading.gif");
		mov_->setSpeed(50);
		ui.imageLabel->setMovie(mov_);
	}
	//ʹ��������ʽʵ��IP��ַ����ؼ�
// 	QRegExp rx("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
// 	QRegExpValidator v(rx, 0);
// 
// 	ui.ipLineEdit->setValidator(&v);
// 	ui.ipLineEdit->setInputMask("000.000.000.000");
}
