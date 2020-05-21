#include "durationWidget.h"
#include "ui_durationWidget.h"

const int nMin = 0;
const int nMax = 5;

durationWidget::durationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::durationWidget)
{
    ui->setupUi(this);
    init();
    initConnect();
}

durationWidget::~durationWidget()
{
    delete ui;
}

int durationWidget::getDurationBySlider()
{
	return ui->horizontalSlider->value() + 1;
}

void durationWidget::resetDuration()
{
	ui->horizontalSlider->setValue(0);
}

void durationWidget::slotOnAddDuration()
{
     int currentValue = ui->horizontalSlider->value();
     if(currentValue < 5)
     {
         currentValue ++;
         ui->horizontalSlider->setValue(currentValue);
     }
}

void durationWidget::slotOnDecreaseDuration()
{
    int currentValue = ui->horizontalSlider->value();
    if(currentValue > 0)
    {
        currentValue --;
        ui->horizontalSlider->setValue(currentValue);
    }
}

void durationWidget::slotOnValueChanged(int value)
{
    emit sigOnValueChanged(value);
    if(value == 0)
    {
        ui->decreaseBtn->setEnabled(false);
        ui->addBtn->setEnabled(true);
    }
    else if(value == 5)
    {
        ui->addBtn->setEnabled(false);
        ui->decreaseBtn->setEnabled(true);
    }
    else
    {
        ui->addBtn->setEnabled(true);
        ui->decreaseBtn->setEnabled(true);
    }
}

void durationWidget::init()
{
    ui->horizontalSlider->setMinimum(nMin);
    ui->horizontalSlider->setMaximum(nMax);
    ui->horizontalSlider->setValue(0);
    ui->decreaseBtn->setEnabled(false);
}

void durationWidget::initConnect()
{
   connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(slotOnValueChanged(int)));
   connect(ui->addBtn, SIGNAL(clicked()), this, SLOT(slotOnAddDuration()));
   connect(ui->decreaseBtn, SIGNAL(clicked()), this, SLOT(slotOnDecreaseDuration()));
}
