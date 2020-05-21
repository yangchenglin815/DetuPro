#include "deviceItemWidget.h"
#include "ui_deviceItemWidget.h"

deviceItemWidget::deviceItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::deviceItemWidget)
{
    ui->setupUi(this);
}

deviceItemWidget::~deviceItemWidget()
{
    delete ui;
}

void deviceItemWidget::initData(deviceInfo pvsList, int type)
{
     ui->deviceLabel->setText(pvsList.name);
	 bool click_status = type ? pvsList.RbClicked : pvsList.bClicked;
	 if (pvsList.status)
	 {
		 if (click_status){
			 ui->stateLabel->setText(tr("loading"));
			 ui->iconLabel->setStyleSheet("background:#ffd500;border-radius:4px;");
			 ui->deviceLabel->setStyleSheet(QString("font-family:%1;font-size:12px;color:#CCCCCC;").arg("微软雅黑"));
			 ui->stateLabel->setStyleSheet(QString("font-family:%1;font-size:12px;color:#ffd500;").arg("微软雅黑"));
		 }
		 else
		 {
			 ui->stateLabel->setText(tr("online"));
			 ui->iconLabel->setStyleSheet("background:#ffd500;border-radius:4px;");
			 ui->deviceLabel->setStyleSheet(QString("font-family:%1;font-size:12px;color:#CCCCCC;").arg("微软雅黑"));
			 ui->stateLabel->setStyleSheet(QString("font-family:%1;font-size:12px;color:#CCCCCC;").arg("微软雅黑"));
		 }
	 }
	 else
	 {
		 ui->stateLabel->setText(tr("offline"));
		 ui->iconLabel->setStyleSheet("background:#666666;border-radius:4px;");
		 ui->deviceLabel->setStyleSheet(QString("font-family:%1;font-size:12px;color:#666666;").arg("微软雅黑"));
		 ui->stateLabel->setStyleSheet(QString("font-family:%1;font-size:12px;color:#666666;").arg("微软雅黑"));
	 }
}
