#include "setAdminWgt.h"
#include "ui_setAdminWgt.h"
#include "DetuPVMSIni.h"
#include "socketRequest.h"
#include <QDebug>

#include "DetuPVMSIni.h"
#include "SetAdminMananger.h"
#include "TcpDataManager.hpp"
#include <QMessageBox>

setAdminWgt::setAdminWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setAdminWgt)
{
    ui->setupUi(this);
	initConnect();
	init();
}

setAdminWgt::~setAdminWgt()
{

}

void setAdminWgt::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter){
		slot_saveAdmin();
	}
}

bool setAdminWgt::eventFilter(QObject *watched, QEvent *event)
{
	if (watched == ui->usernameLineEdit){
		if (ui->usernameLineEdit->getText().isEmpty()){
			ui->usernameLineEdit->setShowClose(true);
		}
		else
		{
			ui->usernameLineEdit->setShowClose(false);
		}
	}
	return QWidget::eventFilter(watched, event);
}

void setAdminWgt::showEvent(QShowEvent *event)
{
	ui->usernameLineEdit->setFocusLineEdit();
}

void setAdminWgt::slot_saveAdmin()
{
	ui->hintLabel->setText("");
	if (ui->usernameLineEdit->getText().isEmpty()){
			ui->usernameLineEdit->setFocus();
			ui->usernameLineEdit->setFocusLineEdit();
			ui->hintLabel->setText(QStringLiteral("请输入用户名！"));
			return;
	}
	else if (ui->passwdLineEdit->text().isEmpty()){
		ui->passwdLineEdit->setFocus();
		ui->hintLabel->setText(QStringLiteral("请输入密码！"));
		return;
	}
	else if (ui->passwdLineEdit->text().size () < 8){
		ui->passwdLineEdit->setFocus();
		ui->hintLabel->setText(QStringLiteral("请输入8位以上的密码！"));
		return;
	}
	else if (ui->confirmPasswdLineEdit->text().isEmpty()){
		ui->confirmPasswdLineEdit->setFocus();
		ui->hintLabel->setText(QStringLiteral("请确认密码！"));
		return;
	}
	else if (ui->passwdLineEdit->text() != ui->confirmPasswdLineEdit->text()){
		ui->confirmPasswdLineEdit->setFocus();
		ui->hintLabel->setText(QStringLiteral("密码不一致，请重新输入！"));
		return;
	}
	ui->hintLabel->setText(QStringLiteral("提交中..."));

	QString username = ui->usernameLineEdit->getText();
	QString passwd = ui->passwdLineEdit->text();
	socketRequest::instance()->requestOnRegisterUser(username, passwd);

// 	DetuPVMSIni::setAdminUser(username);
// 	DetuPVMSIni::setAdminPasswd(passwd);
// 	SetAdminManangerIns.setAdmin(DetuPVMSIni::getIsAdminUser());
	//emit sigonConfirm();
}

void setAdminWgt::slotOnRegisterUser(std::string user, std::string passwd, std::string cUuid, short result)
{
	switch (result)
	{
	case HAVE_BEEN_REGISTERED:
		QMessageBox::warning(this, QStringLiteral("提示"), QStringLiteral("该用户已被注册！"));
		ui->hintLabel->setText(QStringLiteral("该用户已被注册！"));
		ui->usernameLineEdit->setFocus();
		break;
	case REGISTER_SUCCESSFUL:
		QMessageBox::warning(this, QStringLiteral("提示"), QStringLiteral("注册成功！"));
		DetuPVMSIni::setAdminUser(QString::fromLocal8Bit(user.c_str()));
		DetuPVMSIni::setAdminPasswd(QString::fromLocal8Bit(passwd.c_str()));
		DetuPVMSIni::setClientUUID(QString::fromLocal8Bit(cUuid.c_str()));
		SetAdminManangerIns.setAdmin(DetuPVMSIni::getIsAdminUser());
		emit sigonConfirm();
		break;
	default:
		break;
	}
}

void setAdminWgt::initConnect()
{
	connect(ui->cancelBtn, SIGNAL(clicked()), this, SIGNAL(sigonClose()));
	connect(ui->confirmBtn, SIGNAL(clicked()), this, SLOT(slot_saveAdmin()));
	connect(&TcpDataManagerIns, SIGNAL(sigOnRegisterUser(std::string, std::string, std::string, short)), this, SLOT(slotOnRegisterUser(std::string, std::string, std::string, short)));
}

void setAdminWgt::init()
{
	setTabOrder(ui->usernameLineEdit, ui->passwdLineEdit);
	setTabOrder(ui->passwdLineEdit, ui->confirmPasswdLineEdit);
	setTabOrder(ui->confirmPasswdLineEdit, ui->confirmBtn);
	setTabOrder(ui->confirmBtn, ui->cancelBtn);
	ui->usernameLineEdit->setHintText(QStringLiteral("请输入30个字符以内的用户名"));
	ui->passwdLineEdit->setPlaceholderText(QStringLiteral("请输入8-16个字符密码"));
	ui->confirmPasswdLineEdit->setPlaceholderText(QStringLiteral("请再次输入密码"));
	ui->usernameLineEdit->setMaxLength(30);
	ui->passwdLineEdit->setMaxLength(20);
	ui->confirmPasswdLineEdit->setMaxLength(20);
	QRegExp regx("[a-zA-Z0-9]*");
	QRegExpValidator *validator = new QRegExpValidator(regx, this);
	ui->usernameLineEdit->setValidator(validator);
	ui->passwdLineEdit->setValidator(validator);
	ui->confirmPasswdLineEdit->setValidator(validator);
	ui->passwdLineEdit->setEchoMode(QLineEdit::Password);
	ui->confirmPasswdLineEdit->setEchoMode(QLineEdit::Password);
}
