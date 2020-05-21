#include "commonPushButton.h"

commonPushButton::commonPushButton(QWidget *parent)
	: QPushButton(parent)
{

}

commonPushButton::~commonPushButton()
{

}

void commonPushButton::enterEvent(QEvent *event)
{
	setCursor(Qt::PointingHandCursor);
}

void commonPushButton::leaveEvent(QEvent *event)
{
	setCursor(Qt::ArrowCursor);
}
