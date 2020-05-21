#include <QMouseEvent> 

#include "consoletabwidget.h"

consoleTabWidget::consoleTabWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//setAttribute(Qt::WA_TranslucentBackground);
}

consoleTabWidget::~consoleTabWidget()
{

}

void consoleTabWidget::setSelectedStatus(bool selected)
{
	if (selected)
	{
		ui.widget->setStyleSheet("#widget{background:#2a2b2b;border:1px solid #000000;border-left:none;}");
	}
	else
	{
		ui.widget->setStyleSheet("#widget{background:#323232;border:1px solid #000000;border-left:none;}");
	}
}

void consoleTabWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		emit TrigTabConsoleButtonClicked();
	}
}
