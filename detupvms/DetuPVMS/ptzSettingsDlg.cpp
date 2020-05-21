#include "ptzSettingsDlg.h"

ptzSettingsDlg::ptzSettingsDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
 	setAttribute(Qt::WA_TranslucentBackground);
	init();
	initConnect();
}

ptzSettingsDlg::~ptzSettingsDlg()
{

}

/*************************************************
������:    	setCurrData
��������:	���õ�ǰѡ���豸�������Ϣ
�������:
�������:
����ֵ:
**************************************************/
void ptzSettingsDlg::setCurrData(QString IP, int port, QString user, QString passwd)
{

    ui.ipLineEdit->setText(IP);
	if (user.isEmpty())
	{
		ui.portLineEdit->setText("");
	}
	else
	{
		ui.portLineEdit->setText(QString::number(port));
	}
	ui.userLineEdit->setText(user);
	ui.passwdLineEdit->setText(passwd);
}

/*************************************************
������:    	slotOnBindPtz
��������:	�Ի���󶨰�ť�ۺ���
�������:
�������:
����ֵ:
**************************************************/
void ptzSettingsDlg::slotOnBindPtz()
{
	ui.hintLabel->setText("");
	if (ui.ipLineEdit->text().isEmpty()){
		ui.ipLineEdit->setFocus();
		ui.hintLabel->setText(QStringLiteral("IP��ַ����Ϊ��"));
		return;
	}
	else if (ui.portLineEdit->text().isEmpty())
	{
		ui.portLineEdit->setFocus();
		ui.hintLabel->setText(QStringLiteral("�˿ڲ���Ϊ��"));
		return;
	}
	else if (ui.userLineEdit->text().isEmpty())
	{
		ui.userLineEdit->setFocus();
		ui.hintLabel->setText(QStringLiteral("�û�������Ϊ��"));
		return;
	}
	else if (ui.passwdLineEdit->text().isEmpty())
	{
		ui.passwdLineEdit->setFocus();
		ui.hintLabel->setText(QStringLiteral("���벻��Ϊ��"));
		return;
	}
	else
	{
		QString IP = ui.ipLineEdit->text();
		int port = ui.portLineEdit->text().toInt();
		QString userName = ui.userLineEdit->text();
		QString passwd = ui.passwdLineEdit->text();
		emit sigOnBindPtz(IP, port, userName, passwd);
	}
}

void ptzSettingsDlg::initConnect()
{
	connect(ui.cancelBtn, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.confirmBtn, SIGNAL(clicked()), this, SLOT(slotOnBindPtz()));
}

void ptzSettingsDlg::init()
{
	ui.userLineEdit->setMaxLength(30);
	ui.passwdLineEdit->setMaxLength(20);
	QRegExp regx("[a-zA-Z0-9]*");
	QRegExpValidator *validator = new QRegExpValidator(regx, this);
	ui.userLineEdit->setValidator(validator);
	ui.passwdLineEdit->setValidator(validator);
	ui.passwdLineEdit->setEchoMode(QLineEdit::Password);
	QRegExp regx_("[1-9][0-9]+$");
	QValidator *validator_ = new QRegExpValidator(regx_, this);
	ui.portLineEdit->setValidator(validator_);
	ui.portLineEdit->setMaxLength(5);
}

void ptzSettingsDlg::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter){
		slotOnBindPtz();
	}
}