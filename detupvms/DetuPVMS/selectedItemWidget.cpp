#include "selectedItemWidget.h"

selectedItemWidget::selectedItemWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

selectedItemWidget::~selectedItemWidget()
{

}

void selectedItemWidget::initPTZData(const PtzInfo &info)
{
	m_ptzInfo = info;
	ui.ipLabel->setText(info.sIP);
	ui.portLabel->setText(QString::number(info.wPort));
}

void selectedItemWidget::initSPYData(const SpyInfo &info)
{
	m_spyInfo = info;
	ui.ipLabel->setText(info.sIP);
	ui.portLabel->setText(QString::number(info.wPort));
}

void selectedItemWidget::setChecked()
{
	ui.pushButton->setChecked(!ui.pushButton->isChecked());
}

void selectedItemWidget::getPTZData(PtzInfo &info)
{
	info = m_ptzInfo;
}

void selectedItemWidget::getSPYData(SpyInfo &info)
{
	info = m_spyInfo;
}
