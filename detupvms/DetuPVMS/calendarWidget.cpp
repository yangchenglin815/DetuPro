#include "calendarWidget.h"

calendarWidget::calendarWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	init();
}

calendarWidget::~calendarWidget()
{

}

void calendarWidget::slot_setDate()
{
	QDate date = ui.calendar->selectedDate();
	QString curDate = date.toString("yyyy-MM-dd");
	emit sigOnSetDate(curDate);
	this->hide();
}

void calendarWidget::init()
{
	connect(ui.calendar, SIGNAL(clicked(const QDate &)), this, SLOT(slot_setDate()));
}

