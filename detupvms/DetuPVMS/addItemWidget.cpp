#include "addItemWidget.h"

addItemWidget::addItemWidget(QWidget *parent)
: QWidget(parent)
{
	ui.setupUi(this);
	initConnect();
}

addItemWidget::~addItemWidget()
{

}

void addItemWidget::initPtzData(const PtzInfo &ptzInfo)
{
	m_curr_ptzInfo = ptzInfo;
	ui.ipLabel->setText(ptzInfo.sIP);
	ui.portLabel->setText(QString::number(ptzInfo.wPort));
}

void addItemWidget::initSpyData(const SpyInfo &spyInfo)
{
	m_curr_spyInfo = spyInfo;
	ui.ipLabel->setText(spyInfo.sIP);
	ui.portLabel->setText(QString::number(spyInfo.wPort));
}

void addItemWidget::getPtzData(PtzInfo &info)
{
	info = m_curr_ptzInfo;
}

void addItemWidget::getSpyData(SpyInfo &info)
{
	info = m_curr_spyInfo;
}

void addItemWidget::slotOnSettingsClicked()
{
	emit sigOnSettings( m_curr_ptzInfo, m_curr_spyInfo);
}

void addItemWidget::slotOnUnbindClicked()
{
	emit sigOnUnbind(m_curr_ptzInfo, m_curr_spyInfo);
}

void addItemWidget::initConnect()
{
	connect(ui.settingsBtn, SIGNAL(clicked()), this, SLOT(slotOnSettingsClicked()));
	connect(ui.unbindBtn, SIGNAL(clicked()), this, SLOT(slotOnUnbindClicked()));
}
