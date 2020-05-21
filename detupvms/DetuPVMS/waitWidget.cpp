#include "waitWidget.h"

waitWidget::waitWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	setAttribute(Qt::WA_TranslucentBackground);
}

waitWidget::~waitWidget()
{

}
