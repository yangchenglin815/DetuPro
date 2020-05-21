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
			ui->hintLabel->setText(QStringLiteral("�������û�����"));
			return;
	}
	else if (ui->passwdLineEdit->text().isEmpty()){
		ui->passwdLineEdit->setFocus();
		ui->hintLabel->setText(QStringLiteral("���������룡"));
		return;
	}
	else if (ui->passwdLineEdit->text().size () < 8){
		ui->passwdLineEdit->setFocus();
		ui->hintLabel->setText(QStringLiteral("������8λ���ϵ����룡"));
		return;
	}
	else if (ui->confirmPasswdLineEdit->text().isEmpty()){
		ui->confirmPasswdLineEdit->setFocus();
		ui->hintLabel->setText(QStringLiteral("��ȷ�����룡"));
		return;
	}
	else if (ui->passwdLineEdit->text() != ui->confirmPasswdLineEdit->text()){
		ui->confirmPasswdLineEdit->setFocus();
		ui->hintLabel->setText(QStringLiteral("���벻һ�£����������룡"));
		return;
	}
	ui->hintLabel->setText(QStringLiteral("�ύ��..."));

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
		QMessageBox::warning(this, QStringLiteral("��ʾ"), QStringLiteral("���û��ѱ�ע�ᣡ"));
		ui->hintLabel->setText(QStringLiteral("���û��ѱ�ע�ᣡ"));
		ui->usernameLineEdit->setFocus();
		break;
	case REGISTER_SUCCESSFUL:
		QMessageBox::warning(this, QStringLiteral("��ʾ"), QStringLiteral("ע��ɹ���"));
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
	ui->usernameLineEdit->setHintText(QStringLiteral("������30���ַ����ڵ��û���"));
	ui->passwdLineEdit->setPlaceholderText(QStringLiteral("������8-16���ַ�����"));
	ui->confirmPasswdLineEdit->setPlaceholderText(QStringLiteral("���ٴ���������"));
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
