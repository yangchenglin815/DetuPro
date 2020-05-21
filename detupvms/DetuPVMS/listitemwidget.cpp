#include "listitemwidget.h"

ListItemWidget::ListItemWidget(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::ListItemWidget)
{
	ui->setupUi(this);
	ui->checkBox->setVisible(false);
	connect(ui->checkBox, SIGNAL(stateChanged(int)), this, SIGNAL(onStateChanged(int)));
    connect(ui->checkBox, SIGNAL(stateChanged(int)), this, SLOT(onStateChangedSlot(int)));
}

ListItemWidget::~ListItemWidget()
{

}

void ListItemWidget::setCheckState(bool state)
{
	ui->checkBox->setChecked(state);
}

bool ListItemWidget::getCheckState()
{
	if (ui->checkBox->checkState() == Qt::Checked)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ListItemWidget::onStateChangedSlot(int state)
{
    emit setSelectItemIDeviceName(ui->devicelabel_->text());
}

void ListItemWidget::setDveiceName(QString devicename)
{
	ui->devicelabel_->setText(devicename);
}

void ListItemWidget::setDeviceStatus(QString status)
{
	ui->statuslabel_->setText(status);
}

void ListItemWidget::setCheckBoxVisable(bool check_box_visable)
{
	if (check_box_visable)
	{
		ui->checkBox->setVisible(true);
	}
}

void ListItemWidget::setOnline(bool online)
{
	if (online)
	{
		setStyleSheet("QLabel{color:#dddddd;}");
	}
	else
	{
		setStyleSheet("QLabel{color:#868989;}");
	}
}
