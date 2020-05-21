#include "settingWidget.h"

settingWidget::settingWidget(QWidget *parent)
	: QWidget(parent)
	, isAuto_(false)
{
	ui.setupUi(this);
	init();
	initConnect();
}

settingWidget::~settingWidget()
{

}

void settingWidget::init()
{
	ui.deviceName->installEventFilter(this);
	ui.deviceName->setMaxLength(30);
	ui.deviceName->setHintText(QStringLiteral("此处为别名，限制30字符"));
}

void settingWidget::initConnect()
{
	connect(ui.autoBtn, SIGNAL(clicked()), this, SLOT(slot_autoClicked()));
	connect(ui.cancelBtn, SIGNAL(clicked()), this, SIGNAL(sigOnCloseDlg()));
}

bool settingWidget::eventFilter(QObject *watched, QEvent *event)
{
	if (watched == ui.deviceName){
		if (ui.deviceName->getText().isEmpty()){
			ui.deviceName->setShowClose(true);
		}
		else
		{
			ui.deviceName->setShowClose(false);
		}
	}
	return QWidget::eventFilter(watched, event);
}

void settingWidget::slot_autoClicked()
{
	isAuto_ = !isAuto_;
	if (isAuto_){
		//自动旋转
		ui.autoBtn->setStyleSheet("border-image:url(:/image/image/effectsb.png); ");
	}
	else
	{
		ui.autoBtn->setStyleSheet("border-image:url(:/image/image/effects.png); ");
	}
}
