#include "commonButton.h"

commonButton::commonButton(QWidget *parent)
	: QPushButton(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_TranslucentBackground);
}

commonButton::~commonButton()
{

}

void commonButton::initStyleSheet(QString style, QString hover_style)
{
	m_common_style = style;
	m_hover_style = hover_style;

	setStyleSheet(m_common_style);
}

void commonButton::setButtonName(QString name)
{
	ui.textLabel->setText(name);
}

void commonButton::setButtonSize(int width, int height)
{
	ui.iconLabel->setFixedSize(width, height);
}

void commonButton::enterEvent(QEvent *event)
{
	setCursor(Qt::PointingHandCursor);
	setStyleSheet(m_hover_style);
}

void commonButton::leaveEvent(QEvent *event)
{
	setCursor(Qt::ArrowCursor);
	setStyleSheet(m_common_style);
}

void commonButton::mousePressEvent(QMouseEvent *e)
{

}

void commonButton::mouseReleaseEvent(QMouseEvent *e)
{

}
