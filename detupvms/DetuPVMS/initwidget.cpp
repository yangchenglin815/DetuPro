#include "initwidget.h"

initWidget::initWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

initWidget::~initWidget()
{

}

void initWidget::setLabelText(QString text)
{
	ui.label_->setText(text);
}
