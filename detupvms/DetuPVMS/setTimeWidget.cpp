#include "setTimeWidget.h"
#include "logging.hpp"

setTimeWidget::setTimeWidget(QWidget *parent)
	: QWidget(parent)
	, last_request_time("")
{
	ui.setupUi(this);
	initConnect();
}

setTimeWidget::~setTimeWidget()
{

}

void setTimeWidget::initStyleSheet()
{
	setStyleSheet(QString("#widget{border:1px solid #868989;border-radius:15px;background:#1f2020;}#timeEdit{background:#1f2020;border:none;" \
		"font-family:%1;font-size:12px;color:#868989;}#pushButton{border-image:url(:/image/image/timeSelected.png);}").arg(QStringLiteral("Î¢ÈíÑÅºÚ")));
}

void setTimeWidget::enterEvent(QEvent *event)
{
	setCursor(Qt::PointingHandCursor);
	setStyleSheet(QString("#widget{border:1px solid #CCCCCC;border-radius:15px;background:#1f2020;}#timeEdit{background:#1f2020;border:none;" \
		"font-family:%1;font-size:12px;color:#CCCCCC;}#pushButton{border-image:url(:/image/image/timeSelected.png);}").arg(QStringLiteral("Î¢ÈíÑÅºÚ")));
}

void setTimeWidget::leaveEvent(QEvent *event)
{
	setCursor(Qt::ArrowCursor);
	setStyleSheet(QString("#widget{border:1px solid #868989;border-radius:15px;background:#1f2020;}#timeEdit{background:#1f2020;border:none;" \
		"font-family:%1;font-size:12px;color:#868989;}#pushButton{border-image:url(:/image/image/timeSelected.png);}").arg(QStringLiteral("Î¢ÈíÑÅºÚ")));
}

void setTimeWidget::slotOnClicked()
{
	ui.timeEdit->setSelectedSection(QDateTimeEdit::HourSection);
}

void setTimeWidget::slotOnEditFinished()
{
	ui.timeEdit->clearFocus();
	QString curr_time = ui.timeEdit->text();
	Log::Info("curr edit time : %s", curr_time.toLocal8Bit().data());
	if (last_request_time != curr_time)
	{
		last_request_time = curr_time;
		emit sigOnEditFinished(curr_time);
	}
}

void setTimeWidget::initConnect()
{
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(slotOnClicked()));
	connect(ui.timeEdit, SIGNAL(editingFinished()), this, SLOT(slotOnEditFinished()));
}
