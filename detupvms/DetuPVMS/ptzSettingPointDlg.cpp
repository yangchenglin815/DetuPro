#include "ptzSettingPointDlg.h"
#include "feedback.h"

#include <QDebug>

ptzSettingPointDlg::ptzSettingPointDlg(QWidget *parent)
	: QDialog(parent),
	ctrlWgt_(NULL),
	ballWgt_(NULL)
{
	ui.setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

	init();
	initConnect();
}

ptzSettingPointDlg::~ptzSettingPointDlg()
{

}

void ptzSettingPointDlg::setTitleText(const PtzInfo &curr_info)
{
	m_curr_ptzInfo = curr_info;
	QString title = QStringLiteral("球机") + m_curr_ptzInfo.sIP;
	ui.titleLabel->setText(title);

	ui.label->setScaledContents(true);
	QImage image;
	image.load(QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/pts") + "/" + m_curr_ptzInfo.m1Id + "/pano.jpg");
	QPalette palette;
	palette.setBrush(this->backgroundRole(), QBrush(image));
	ui.label->setPixmap(QPixmap::fromImage(image));
}


void ptzSettingPointDlg::setPosSet(int x, int y)
{
	if (ballWgt_ != NULL)
	{
		ballWgt_->play(m_curr_ptzInfo);
		ballWgt_->move(x + ui.widget->width() + 4, y + ui.titleWidget->height());
		ballWgt_->show();
		ballWgt_->setExchangeBtnVisible(true);
		ballWgt_->setSavePresetBtnVisible(true);
	}
}

void ptzSettingPointDlg::init()
{

	if (ctrlWgt_ == NULL)
	{
		ctrlWgt_ = new ptzPointCtrlWidget;
		connect(ctrlWgt_, SIGNAL(sigOnClicked(bool, int)), this, SLOT(slotOnPanoPrePointClicked(bool, int)));
		connect(ctrlWgt_, SIGNAL(sigOnStepOnPoint(int)), this, SLOT(slotOnPanoPrePointClicked(bool,int)));
		Log::Info("ctrlWgt_->setParent(ui.widget);");
		ctrlWgt_->setParent(ui.widget);
	}

	if (ballWgt_ ==NULL)
	{
		ballWgt_ = new ballCamWgt(ui.ptzWidget);
	}
	ballWgt_->resize(300, 200);
	ballWgt_->hide();
}

void ptzSettingPointDlg::initConnect()
{
	connect(ui.cancelBtn, SIGNAL(clicked()), this, SLOT(slotOnCancel()));
	connect(ui.confirmBtn, SIGNAL(clicked()), this, SLOT(slotOnConfirm()));
	connect(this, SIGNAL(SignalToTrigBallCamLinkage(int, int)), ballWgt_, SLOT(SlotToTrigBallCamLinkage(int, int)));
}

void ptzSettingPointDlg::slotOnConfirm()
{
	if (ctrlWgt_ != NULL)
	{
		//ctrlWgt_->getPointStatus(m_curr_ptzInfo.sIP);
		ballWgt_->closePlay();
	}
	this->hide();

	Feedback::instance()->maskUI(SET_PRE_POINT_OK);
}

void ptzSettingPointDlg::slotOnCancel()
{
	ballWgt_->closePlay();
	this->hide();
}

void ptzSettingPointDlg::slotOnPanoPrePointClicked(bool checked, int num)
{
	//8代表设置
	emit SignalToTrigBallCamLinkage(num, 39);
}

