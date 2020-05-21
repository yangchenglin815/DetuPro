#include "ballcamctrl.h"

ballCamCtrl::ballCamCtrl(QWidget *parent)
	: QWidget(parent)
	, curr_type(-1)
{
	ui.setupUi(this);
	ui.savePresetBtn_->setVisible(false);

	setWindowFlags(Qt::Tool | Qt::FramelessWindowHint); //Qt::Popup | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint
	setAttribute(Qt::WA_TranslucentBackground, true);

	QButtonGroup *group = new QButtonGroup(this);
	group->setExclusive(true);
	connect(group, SIGNAL(buttonPressed(int)), this, SIGNAL(buttonPressed(int)));
	connect(group, SIGNAL(buttonReleased(int)), this, SIGNAL(buttonReleased(int)));
	connect(ui.savePresetBtn_, SIGNAL(clicked()), this, SLOT(slotOnClicked()));

	group->addButton(ui.up_, TILT_UP);
	group->addButton(ui.left_, PAN_LEFT);
	group->addButton(ui.right_, PAN_RIGHT);
	group->addButton(ui.down_, TILT_DOWN);

	group->addButton(ui.bigger_, ZOOM_IN);
	group->addButton(ui.smaller_, ZOOM_OUT);
}

ballCamCtrl::~ballCamCtrl()
{

}

void ballCamCtrl::setButtonText(QString text, int type)
{
	curr_point = text;
	curr_type = type;
	if (curr_type == 8)
	{
		ui.savePresetBtn_->setText(QStringLiteral("±£´æÎªÔ¤ÖÃµã") + curr_point);
		ui.savePresetBtn_->setStyleSheet(QString("font-family:%1;font-size:12px;background:#ffd500;border-radius:12px;color:#333333;").arg(QStringLiteral("Î¢ÈíÑÅºÚ")));
	}
}

void ballCamCtrl::setSavePresetBtnVisible(bool visible)
{
	ui.savePresetBtn_->setVisible(visible);
}

void ballCamCtrl::setExchangeBtnVisible(bool visible)
{
	//ui.exchange_->setVisible(visible);
}

void ballCamCtrl::slotOnClicked()
{
	//ui.savePresetBtn_->setText(QStringLiteral("ÒÑ±£´æÎªÔ¤ÖÃµã") + curr_point);
	//ui.savePresetBtn_->setStyleSheet(QString("font-family:%1;font-size:12px;background:rgb(203, 205, 204);border-radius:12px;color:#333333;").arg(QStringLiteral("Î¢ÈíÑÅºÚ")));
	emit sigOnSavePoint();

}
