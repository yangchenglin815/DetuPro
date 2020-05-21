#include "mapToolWidget.h"
#include "MapPointListManager.h"

mapToolWidget::mapToolWidget(QWidget *parent)
: QWidget(parent)
{
	ui.setupUi(this);
	ui.miniMapPage->setAutoFillBackground(true);

	connect(ui.rfidPage, SIGNAL(SignalToSetSwtichScreen(int)), this, SIGNAL(SignalToSetSwtichScreen(int)));
}

mapToolWidget::~mapToolWidget()
{

}

void mapToolWidget::setCurrPlayInfo(PanoMapPointInfo_t info)
{
	ui.miniMapPage->setCurrPlayInfo(info);
}

void mapToolWidget::setBackground()
{
	QPixmap map(MapPointListManagerIns.getMap().mapPath);
	QPalette palette;
	palette.setBrush(ui.miniMapPage->backgroundRole(), QBrush(map.scaled(ui.miniMapPage->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
	ui.miniMapPage->setPalette(palette);
	ui.miniMapPage->drawAllMiniPoint();
	ui.miniMapPage->show();
}

void mapToolWidget::initData(PanoSceneInfo info)
{
	ui.pictureGroupPage->maskUI(QSize(140, 70), 6, true, info);
	ui.pictureGroupPage->show();
}

void mapToolWidget::setPicGroupPage(bool isChecked)
{
	if (isChecked)
	{
		ui.pictureGroupPage->show();
	}
	else
	{
		ui.pictureGroupPage->hide();
	}
}

void mapToolWidget::setMiniMapPage(bool isChecked)
{
	if (isChecked)
	{
		ui.miniMapPage->show();
	}
	else
	{
		ui.miniMapPage->hide();
	}
}

void mapToolWidget::slotToTrigArrowRotate(double yaw, double pitch)
{
	ui.miniMapPage->slotToTrigArrowRotate(yaw, pitch);
}

void mapToolWidget::slotOnHiddenPicGroup()
{
	resize(320, 180);
	ui.pictureGroupPage->hide();

	emit sigOnHiddenPicGroup();
}

void mapToolWidget::slotOnHiddenMiniMap()
{
	resize(320, 180);
	ui.miniMapPage->hide();

	emit sigOnHiddenMiniMap();
}
