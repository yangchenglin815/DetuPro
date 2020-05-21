#include "unlockWgt.h"
#include "DetuPVMSIni.h"

unlockWgt::unlockWgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initConnect();
	init();
}

unlockWgt::~unlockWgt()
{

}

void unlockWgt::clearPasswd()
{
	ui.passwdLineEdit->clear();
	ui.hintLabel->setText("");
}

void unlockWgt::setBtnState()
{
	if (ui.passwdLineEdit->text().isEmpty()){
	      ui.confirmBtn->setDisabled(true);
    }
	else
	{
		ui.confirmBtn->setDisabled(false);
	}
}

void unlockWgt::getUserName()
{
	QString user = DetuPVMSIni::getAdminUser();
	ui.usernameHintLabel->setText(user);
}

void unlockWgt::slot_unlock()
{
	ui.hintLabel->setText("");
	QString passwd = DetuPVMSIni::getAdminPasswd();
	if (ui.passwdLineEdit->text().isEmpty() || ui.passwdLineEdit->text() != passwd){
		ui.passwdLineEdit->setFocus();
		ui.hintLabel->setText(QStringLiteral("ÃÜÂë´íÎó"));
		return;
	}
	DetuPVMSIni::setUnlockState(true);
	emit sigOnUnlock();
}

void unlockWgt::init()
{
	ui.passwdLineEdit->installEventFilter(this);
	ui.passwdLineEdit->setPlaceholderText(QStringLiteral("ÊäÈëµÇÂ¼ÃÜÂë¼´¿É½âËø"));
	ui.passwdLineEdit->setMaxLength(20);
	QRegExp regx("[a-zA-Z0-9]*");
	QRegExpValidator *validator = new QRegExpValidator(regx, this);
	ui.passwdLineEdit->setValidator(validator);
	ui.passwdLineEdit->setEchoMode(QLineEdit::Password);
	setBtnState();
	emit sigOnModel(true);
}

void unlockWgt::initConnect()
{
	connect(ui.cancelBtn, SIGNAL(clicked()), this, SIGNAL(sigOnClose()));
	connect(ui.confirmBtn, SIGNAL(clicked()), this, SLOT(slot_unlock()));
}

void unlockWgt::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter){
		slot_unlock();
	}
}

bool unlockWgt::eventFilter(QObject *watched, QEvent *event)
{
	if (watched == ui.passwdLineEdit){
		setBtnState();
	}
	return QWidget::eventFilter(watched, event);
}
