#include "loginWidget.h"
#include "DetuPVMSIni.h"
#include <QDebug>

#include "SetAdminMananger.h"
#include "socketRequest.h"
#include "TcpDataManager.hpp"
#include <QMessageBox>

loginWidget::loginWidget(QWidget *parent)
	: QWidget(parent)
	, bubble_(NULL)
	, nXPos_(-1)
	, nYPos_(-1)
{
	ui.setupUi(this);
	initConnect();
	init();
}

loginWidget::~loginWidget()
{

}

void loginWidget::closeBubble()
{
	if (bubble_ != NULL){
		bubble_->close();
	}
}

void loginWidget::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter){
		slot_loginDetu();
	}
}

void loginWidget::mousePressEvent(QMouseEvent *event)
{
	if (Qt::LeftButton == event->button() ){
		int x = event->pos().x();
		int y = event->pos().y();
		int x1 = ui.forgetBtn->pos().x();
		int y1 = ui.forgetBtn->pos().y();
		int x2 = x1 + ui.forgetBtn->width();
		int y2 = y1 + ui.forgetBtn->height();
		if (x>x1 && x< x2 && y>y1 && y<y2){
			ui.forgetBtn->setStyleSheet("#forgetBtn{color:#bcbcbc;} #forgetBtn::hover{color: #343434;}");
			if (ui.hintLabel->text().isEmpty()){
				//ui.hintLabel->setText(QStringLiteral("请联系技术支持获取密码！"));
				if (bubble_ == NULL){
					bubble_ = new bubbleWidget;
				}
				QPoint pos = this->mapToGlobal(this->pos());
				QPoint pos_ = ui.forgetBtn->pos();
				nXPos_ = pos.x() + pos_.x();
				nYPos_ = pos.y() + pos_.y() + ui.forgetBtn->height();
				bubble_->move(nXPos_, nYPos_);
				bubble_->activateWindow();
				bubble_->show();
			}
			else{
				ui.hintLabel->setText("");
				bubble_->close();
			}
		}
	}
}

bool loginWidget::eventFilter(QObject *watched, QEvent *event)
{
	if (watched == ui.userLineEdit){
		if (ui.userLineEdit->getText().isEmpty()){
			ui.userLineEdit->setShowClose(true);
		}
		else
		{
			ui.userLineEdit->setShowClose(false);
		}
	}
	return QWidget::eventFilter(watched, event);
}

void loginWidget::slot_loginDetu()
{
	SetAdminManangerIns.setAdmin(DetuPVMSIni::getIsAdminUser());

	ui.hintLabel->setText("");
	QString user = DetuPVMSIni::getAdminUser();
	QString passwd = DetuPVMSIni::getAdminPasswd();

	if (ui.userLineEdit->getText().isEmpty()){
		ui.userLineEdit->setFocusLineEdit();
		ui.hintLabel->setText(QStringLiteral("请输入用户名！"));
		return;
	}
	else if (ui.passwdLineEdit->text().isEmpty()){
		ui.passwdLineEdit->setFocus();
		ui.hintLabel->setText(QStringLiteral("请输入密码！"));
		return;
	}
	else if (ui.passwdLineEdit->text().size() < 8){
		ui.passwdLineEdit->setFocus();
		ui.hintLabel->setText(QStringLiteral("请输入8位以上的密码！"));
		return;
	}
	else /*if (ui.userLineEdit->getText() == user && ui.passwdLineEdit->text() == passwd)*/{
		ui.hintLabel->setText(QStringLiteral("提交中..."));
		bool isAutoLogin = ui.autoLoginBtn->isChecked();
		DetuPVMSIni::setAutoLogin(isAutoLogin);

		socketRequest::instance()->requestOnLoginChecked(ui.userLineEdit->getText(), ui.passwdLineEdit->text(), DetuPVMSIni::getClienUUID());
		/*emit sigOnLogin();*/
		return;
	}
	
	//处理用户名密码不同
	ui.hintLabel->setText(QStringLiteral("用户名密码错误，请重新输入！"));
}

void loginWidget::slotOnLoginChecked(std::string cuuid, short result)
{
	switch (result)
	{
	case USERNAME_ERR:
		QMessageBox::warning(this, QStringLiteral("提示"), QStringLiteral("用户名错误！"));
		ui.hintLabel->setText(QStringLiteral("用户名错误！"));
		ui.userLineEdit->setFocusLineEdit();
		break;
	case PASSWD_ERR:
		QMessageBox::warning(this, QStringLiteral("提示"), QStringLiteral("密码错误！"));
		ui.hintLabel->setText(QStringLiteral("密码错误！"));
		ui.passwdLineEdit->setFocus();
		break;
	case MUTI_CLIENT_ERR:
		QMessageBox::warning(this, QStringLiteral("提示"), QStringLiteral("该用户已在其他设备登录！"));
		ui.hintLabel->setText(QStringLiteral(""));
		break;
	case CHECK_FINISHED:
		DetuPVMSIni::setClientUUID(QString::fromUtf8(cuuid.c_str()));
		ui.hintLabel->setText(QStringLiteral("提交中..."));
		emit sigOnLogin();
		break;
	default:
		break;
	}
}

void loginWidget::initConnect()
{
	connect(ui.cancelBtn, SIGNAL(clicked()), this, SIGNAL(sigOnClose()));
	connect(ui.confirmBtn, SIGNAL(clicked()), this, SLOT(slot_loginDetu()));
	connect(&TcpDataManagerIns, SIGNAL(sigOnLoginChecked(std::string, short)), this, SLOT(slotOnLoginChecked(std::string, short)));
}

void loginWidget::init()
{
	ui.userLineEdit->installEventFilter(this);
	ui.userLineEdit->setHintText(QStringLiteral("请输入用户名"));
	ui.passwdLineEdit->setPlaceholderText(QStringLiteral("请输入8-16个字符密码"));
	ui.userLineEdit->setMaxLength(30);
	ui.passwdLineEdit->setMaxLength(20);
	QRegExp regx("[a-zA-Z0-9]*");
	QRegExpValidator *validator = new QRegExpValidator(regx, this);
	ui.userLineEdit->setValidator(validator);
	ui.passwdLineEdit->setValidator(validator);
	ui.passwdLineEdit->setEchoMode(QLineEdit::Password);
	setMouseTracking(true);
	emit sigOnSetDlgModal(false);
}
