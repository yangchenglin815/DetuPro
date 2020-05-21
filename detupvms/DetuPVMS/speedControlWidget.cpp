#include "speedControlWidget.h"

speedControlWidget::speedControlWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_TranslucentBackground);
	init();
	initConnect();
}

speedControlWidget::~speedControlWidget()
{

}

void speedControlWidget::setFastBtnEnable(bool enable)
{
	ui.fastBtn->setEnabled(enable);
}

void speedControlWidget::setSlowBtnEnable(bool enable)
{
	ui.slowBtn->setEnabled(enable);
}

void speedControlWidget::setSpeedLabel(QString speed)
{
	ui.label->setText(speed);
}

void speedControlWidget::init()
{
	setSpeedLabel("1x");
}

void speedControlWidget::initConnect()
{
	connect(ui.fastBtn, SIGNAL(clicked()), this, SIGNAL(sigOnFastPlay()));
	connect(ui.slowBtn, SIGNAL(clicked()), this, SIGNAL(sigOnSlowPlay()));
}
