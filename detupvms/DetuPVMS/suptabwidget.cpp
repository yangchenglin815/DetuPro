#include <QMouseEvent> 

#include "suptabwidget.h"
#include "ui_suptabwidget.h"
#include <QDebug>

supTabWidget::supTabWidget(QWidget *parent)
: QWidget(parent),
ui(new Ui::supTabWidget)
{
	ui->setupUi(this);
	connect(ui->closeBtn, SIGNAL(clicked()), this, SLOT(slot_closeTab()));


}

supTabWidget::~supTabWidget()
{

}

void supTabWidget::setTittle(QString tittle, supTabWgtButton type)
{
	type_ = type;
	ui->label->setText(tittle);
}

void supTabWidget::setSelectedStatus(bool selected)
{
	if (selected)
	{
		ui->widget->setStyleSheet("#widget{background:#2a2b2b;border:1px solid #000000;border-left:none;}");
	}
	else
	{
		ui->widget->setStyleSheet("#widget{background:#323232;border:1px solid #000000;border-left:none;}");
	}
}

void supTabWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		emit TrigSupTabButtonClicked(type_);
	}
}

void supTabWidget::slot_closeTab()
{
	emit sigOnTabClose(type_);
}
