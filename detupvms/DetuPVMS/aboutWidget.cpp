#include "aboutWidget.h"
#include "constStruct.h"

aboutWidget::aboutWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	init();
}

aboutWidget::~aboutWidget()
{

}

void aboutWidget::init()
{
	ui.versionLabel->setText(QStringLiteral("£¨%1£©").arg(CLIENT_VERSION_NO));
	ui.urlLabel->setOpenExternalLinks(true);
	ui.urlLabel->setText(tr("<a  style='color:#666666;' href=\"http://www.detu.com/\">www.detu.com"));
	//ui.dateLabel->setText(QStringLiteral("%1").arg(VERSION_CREATETIME));
}
