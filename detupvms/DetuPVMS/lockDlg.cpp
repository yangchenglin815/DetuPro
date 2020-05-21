#include "lockDlg.h"
#include <QDebug>
#include <QPainter>

lockDlg::lockDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
	setModal(true);
    ui.imageLabel->setStyleSheet("border-image:url(:/image/image/caesura.png);");
    this->setMouseTracking(true);      //设置为不按下鼠标键触发moveEvent
}

lockDlg::~lockDlg()
{

}

bool lockDlg::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == this)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            emit sigOnUnlock();
        }
    }
    return true;
}

void lockDlg::mouseMoveEvent(QMouseEvent *event)
{
	QPoint mousepos = event->pos();
	if (mousepos.rx() > 0 && mousepos.rx() < this->width() && mousepos.ry() > 0 && mousepos.ry() < this->height())
	{
		setCursor(Qt::PointingHandCursor);
	}
	else
	{
		setCursor(Qt::ArrowCursor);
	}
}

void lockDlg::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    painter.setBrush(QBrush("#eeeeee"));
    painter.setPen(Qt::transparent);
    QRect rect = this->rect();
    rect.setWidth(rect.width() - 1);
    rect.setHeight(rect.height() - 1);
    painter.drawRoundedRect(rect, 5, 5);
    QWidget::paintEvent(event);
}

void lockDlg::mousePressEvent(QMouseEvent *event)
{
	if (event->buttons() == Qt::LeftButton)
	{
		emit sigOnUnlock();
	}
}

void lockDlg::closeEvent(QCloseEvent *event)
{
	event->ignore();
}
