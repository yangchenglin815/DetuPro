#include "detuTittleWgt.h"
#include "ui_detuTittleWgt.h"
#include <QDebug>

detuTittleWgt::detuTittleWgt(QWidget *parent) :
QWidget(parent),
ui(new Ui::detuTittleWgt)
, nXPos_(-1)
, nYPos_(-1)
{
	ui->setupUi(this);
	initConnect();
	init();
}

detuTittleWgt::~detuTittleWgt()
{

}

bool detuTittleWgt::eventFilter(QObject *watched, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonDblClick)
	{
		emit sigOnDbClickTitle();
	}
	return QWidget::eventFilter(watched, event);
}

void detuTittleWgt::showEvent(QShowEvent *event)
{
	QPoint pos_ = ui->helpBtn->pos();
	QPoint pos = this->mapToGlobal(this->pos());
	int nOffx = 107 / 2 - 10;
	nXPos_ = pos_.x() - nOffx;
	nYPos_ = pos_.y() + ui->helpBtn->height();
	emit sigonHelpPos(nXPos_, nYPos_);
}

void detuTittleWgt::initConnect()
{
	connect(ui->closeBtn, SIGNAL(clicked()), this, SIGNAL(sigonCloseClient()));
	connect(ui->minimizeBtn, SIGNAL(clicked()), this, SIGNAL(sigonMinimized()));
	connect(ui->maxmizeBtn, SIGNAL(clicked()), this, SIGNAL(sigonMaxminzed()));
	connect(ui->unlockBtn, SIGNAL(clicked()), this, SIGNAL(sigonUnlock()));
	connect(ui->helpBtn, SIGNAL(clicked()), this, SIGNAL(sigonCloseHelp()));
	connect(ui->settingBtn, SIGNAL(clicked()), this, SIGNAL(sigOnShowSettingDlg()));
}

void detuTittleWgt::init()
{
    // ui->helpBtn->installEventFilter(this);
// 	this->setMouseTracking(true);
// 	ui->widget->setMouseTracking(true);
// 	ui->helpBtn->setMouseTracking(true);

	installEventFilter(this);
}

void detuTittleWgt::setTimeShow(QString time)
{
	ui->timeLabel->setText(time);
}

void detuTittleWgt::setMaxBtnStatus(bool max)
{
	if (!max)
	{
		ui->maxmizeBtn->setStyleSheet("#maxmizeBtn{border-image:url(:/image/image/windowre.png);}#maxmizeBtn:pressed{margin:1px;}#maxmizeBtn:hover{border-image:url(:/image/image/windowreb.png);}");
	}
	else
	{
		ui->maxmizeBtn->setStyleSheet("#maxmizeBtn{border-image:url(:/image/image/windowbiger.png);}#maxmizeBtn:pressed{margin:1px;}#maxmizeBtn:hover{border-image:url(:/image/image/windowbigerb.png);}");
	}
}

void detuTittleWgt::setLockStyleSheet(bool lock)
{
	if (lock)
	{
		ui->unlockBtn->setStyleSheet("#unlockBtn{\nborder-image:url(:/image/image/lock.png);}#unlockBtn:pressed{margin:1px;}#unlockBtn:hover{border-image:url(:/image/image/lockb.png);}");
	}
	else
	{
		ui->unlockBtn->setStyleSheet("#unlockBtn{\nborder-image:url(:/image/image/unlock.png);}#unlockBtn:pressed{margin:1px;}#unlockBtn:hover{border-image:url(:/image/image/unlockb.png);}");
	}
}

void detuTittleWgt::getShowPos()
{
	QPoint pos_ = ui->helpBtn->pos();
	QPoint pos = this->mapToGlobal(this->pos());
	int nOffx = 107 / 2 - 10;
	nXPos_ = pos_.x() - nOffx;
	nYPos_ = pos_.y() + ui->helpBtn->height();
	emit sigonHelpPos(nXPos_, nYPos_);
}

