#include "VRMapAddDlgTitleWidget.h"

VRMapAddDlgTitleWidget::VRMapAddDlgTitleWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	connect(ui.checkBox, SIGNAL(stateChanged(int)), this, SIGNAL(stateChanged(int)));
}

VRMapAddDlgTitleWidget::~VRMapAddDlgTitleWidget()
{

}

void VRMapAddDlgTitleWidget::setTitleText(QString text_1, QString text_2)
{
	ui.label->setText(text_1);
	ui.label_2->setText(text_2);
}

void VRMapAddDlgTitleWidget::setCheckBoxChecked(bool checked)
{
	ui.checkBox->setChecked(checked);
}
