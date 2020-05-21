#include "paneWidget.h"

paneWidget::paneWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked(bool)), this, SLOT(slotOnClicked(bool)));
}

paneWidget::~paneWidget()
{

}

void paneWidget::setButtonNum(int num)
{
	ui.pushButton->setText(QString::number(num));
}

int paneWidget::getButtonStatus()
{
	return ui.pushButton->isChecked();
}

void paneWidget::setButtonStatus(bool checked)
{
	ui.pushButton->setChecked(checked);
}

void paneWidget::setButtonEnabled(bool enabled)
{
	ui.pushButton->setEnabled(enabled);
}

void paneWidget::slotOnClicked(bool checked)
{
	int num = ui.pushButton->text().toInt();
	emit sigOnClicked(checked, num);
	if (!checked)
	{
		ui.pushButton->setChecked(true);
		return;
	}
}
