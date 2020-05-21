#include "bubbleWidget.h"
#include "ui_bubbleWidget.h"
#include <QPainter>

bubbleWidget::bubbleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bubbleWidget)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	setAttribute(Qt::WA_TranslucentBackground);
}

bubbleWidget::~bubbleWidget()
{

}

