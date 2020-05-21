#include "setDateWidget.h"
#include <QDateTime>
#include <QApplication>

setDateWidget::setDateWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.dateBtn, SIGNAL(clicked()), this, SIGNAL(sigOnShowCalendar()));
	init();
}

setDateWidget::~setDateWidget()
{

}

void setDateWidget::setSelectedDate(QString date)
{
	m_date = date;
	ui.lineEdit->setText(date);
}

QString setDateWidget::getSelectedDate()
{
	return m_date;
}

void setDateWidget::initStyleSheet()
{
	setStyleSheet(QString("#widget{border: 1px solid #868989;border-radius:15px;bcakground-color:#868989;}QLineEdit{font-family:%1;font-size:12px;"
	"color:#868989;background-color:#1f2020;line-height:12px;text-align:left;}#dateBtn{border-image:url(:/image/image/timechosen.png);}").arg(QStringLiteral("Î¢ÈíÑÅºÚ")));
}

void setDateWidget::enterEvent(QEvent *event)
{
	setCursor(Qt::PointingHandCursor);
	setStyleSheet(QString("#widget{border:1px solid #cccccc;border-radius:15px;bcakground-color:#4e5050;}QLineEdit{font-family:%1;font-size:12px;color:#cccccc;background-color:#1f2020;line-height:12px;text-align:left;}#dateBtn{border-image:url(:/image/image/timechosenb.png);}").arg(QStringLiteral("Î¢ÈíÑÅºÚ")));
}

void setDateWidget::leaveEvent(QEvent *event)
{
	setCursor(Qt::ArrowCursor);
	setStyleSheet(QString("#widget{border: 1px solid #868989;border-radius:15px;bcakground-color:#868989;}QLineEdit{font-family:%1;font-size:12px;color:#868989;background-color:#1f2020;line-height:12px;text-align:left;}#dateBtn{border-image:url(:/image/image/timechosen.png);}").arg(QStringLiteral("Î¢ÈíÑÅºÚ")));
}

void setDateWidget::mousePressEvent(QMouseEvent *event)
{
	emit sigOnShowCalendar();
}

void setDateWidget::init()
{
	QDate date = QDate::currentDate();
	m_date = date.toString("yyyy-MM-dd");
	ui.lineEdit->setText(m_date);
}
