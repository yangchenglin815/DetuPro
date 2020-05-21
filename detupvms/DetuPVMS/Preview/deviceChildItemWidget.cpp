#include "deviceChildItemWidget.h"
#include "ui_deviceChildItemWidget.h"

deviceChildItemWidget::deviceChildItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::deviceChildItemWidget)
{
    ui->setupUi(this);
}

deviceChildItemWidget::~deviceChildItemWidget()
{
    delete ui;
}

void deviceChildItemWidget::setIsFinal(bool isFinal)
{
    ui->widget->setIsFinal(isFinal);
}

void deviceChildItemWidget::setLabelText(QString text)
{
	ui->deviceLabel->setText(text);
}
