#include "commonDlg.h"
#include "ui_commonDlg.h"
#include <QDebug>

commonDlg::commonDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::commonDlg)
	, isDraggingWindow_(false)
{
    ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
    ui->stackedWidget->setCurrentWidget(ui->serverSettingsPage);
    initConnect();
	init();
}

commonDlg::~commonDlg()
{

}

void commonDlg::setTitleLabel(QString str)
{
    ui->tittleWgt->setLabelText(str);
}

void commonDlg::setLoginDlg()
{
	ui->stackedWidget->setCurrentWidget(ui->loginPage);
}

void commonDlg::setCloseBtn(bool isHidden)
{
	ui->tittleWgt->setHideCloseBtn(isHidden);
}

void commonDlg::setBtnState()
{
	ui->unlockPage->setBtnState();
}

void commonDlg::clearPasswd()
{
	ui->unlockPage->clearPasswd();
}

void commonDlg::setUnlockDlg()
{
	ui->stackedWidget->setCurrentWidget(ui->unlockPage);
}

void commonDlg::setAboutDlg()
{
	ui->stackedWidget->setCurrentWidget(ui->aboutPage);
}

void commonDlg::setSettingDlg()
{
	ui->stackedWidget->setCurrentWidget(ui->settingPage);
}

void commonDlg::setServerSettingDlg()
{
	setTitleLabel(QStringLiteral("×¢²áÕËºÅ"));
	ui->stackedWidget->setCurrentWidget(ui->setAdminPage);
}

void commonDlg::serverConnectFailed()
{
	ui->serverSettingsPage->serverConnectFailed();
}

void commonDlg::setUserName()
{
	ui->unlockPage->getUserName();
}

void commonDlg::slotOnSetDlgModal(bool modal)
{
	setModal(modal);
}

void commonDlg::slot_dlgClose()
{
	if (ui->stackedWidget->currentWidget() == ui->loginPage){
		ui->loginPage->closeBubble();
	}
	close();
}

void commonDlg::mouseMoveEvent(QMouseEvent *event)
{
	if (isDraggingWindow_) {
		this->move(event->globalPos() - lastMousePos_);
	}
}

void commonDlg::mousePressEvent(QMouseEvent *event)
{
	// current
	int x = event->pos().x();
	int y = event->pos().y();

	// top left
	int x1 = ui->tittleWgt->pos().x();
	int y1 = ui->tittleWgt->pos().y();

	// bottom right
	int x2 = x1 + ui->tittleWgt->width();
	int y2 = y1 + ui->tittleWgt->height();

	if (x > x1 && x < x2 && y > y1 && y < y2) {
		lastMousePos_ = event->pos();
		isDraggingWindow_ = true;
	}
}

void commonDlg::mouseReleaseEvent(QMouseEvent *event)
{
	isDraggingWindow_ = false;
}

void commonDlg::init()
{
	setModal(true);
}

void commonDlg::initConnect()
{
	 connect(ui->tittleWgt, SIGNAL(sigonClose()), this, SLOT(slot_dlgClose()));
	 connect(ui->setAdminPage, SIGNAL(sigonClose()), this, SLOT(close()));
	 connect(ui->setAdminPage, SIGNAL(sigonConfirm()), this, SIGNAL(sigOnFirstFinish()));
	 connect(ui->loginPage, SIGNAL(sigOnClose()), this, SLOT(slot_dlgClose()));
	 connect(ui->loginPage, SIGNAL(sigOnLogin()), this, SIGNAL(sigOnLogin()));
	 connect(ui->loginPage, SIGNAL(setModel(bool)), this, SLOT(setModel(bool)));
	 connect(ui->unlockPage, SIGNAL(sigOnClose()), this, SIGNAL(sigOnReturnLock()));
	 connect(ui->unlockPage, SIGNAL(sigOnUnlock()), this, SIGNAL(sigOnCloseUnlock()));
	 connect(ui->unlockPage, SIGNAL(sigOnModel(bool)), this, SLOT(setModel(bool)));
	 connect(ui->settingPage, SIGNAL(sigOnCloseDlg()), this, SLOT(close()));
	 connect(ui->serverSettingsPage, SIGNAL(sigOnCancel()), this, SLOT(close()));
	 connect(ui->serverSettingsPage, SIGNAL(sigOnConfirm()), this, SIGNAL(sigOnServerFinished()));
}

