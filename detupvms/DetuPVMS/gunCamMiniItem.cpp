#include <QEvent> 
#include <QMouseEvent> 
#include <QFileDialog>

#include "gunCamMiniItem.h"

gunCamMiniItem::gunCamMiniItem(QWidget *parent)
	: QWidget(parent),
	hotpic_("")
{
	ui.setupUi(this);

	setFixedSize(30, 30);

	QPixmap map(":/image/image/PVMSlogo.png");
	setAutoFillBackground(true);
	QPalette palette;
	QSize temp;
	palette.setBrush(this->backgroundRole(), QBrush(map.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
	setPalette(palette);

	is_hot_pic_chosen_ = false;
}

gunCamMiniItem::~gunCamMiniItem()
{

}

void gunCamMiniItem::mousePressEvent(QMouseEvent *event)
{
	if (event->type() == QEvent::MouseButtonDblClick)
	{
		hotpic_ = QFileDialog::getOpenFileName(this, tr("Open Weather"), QDir::homePath() + "/AppData/Local/Pano-VMS/Map/hotPic", tr("Image Files (*.png *.jpg *.bmp)"));
	}

	QWidget::mousePressEvent(event);

}

void gunCamMiniItem::mouseMoveEvent(QMouseEvent *event)
{
	QWidget::mouseMoveEvent(event);
}

void gunCamMiniItem::mouseReleaseEvent(QMouseEvent *event)
{
	QWidget::mouseReleaseEvent(event);
}
