#include <QList>
#include "VRViewWidget.h"

//³õÊ¼»¯¿ØÖÆÆ÷
#include "MessageManager.h"
#include "SocketManager.h"
#include "TcpDataManager.hpp"
#include "ListAndGLWindowManager.h"
#include "MapPointListManager.h"
#include "ViewSignal.h"

VRViewWidget::VRViewWidget(QWidget *parent)
	: QWidget(parent)
	, is_map_load_(false)
{
	ui.setupUi(this);
	initConnect();
}

VRViewWidget::~VRViewWidget()
{

}

void VRViewWidget::clearPlayerStatus()
{
	ui.mapPage->closeGLScreen();
}

void VRViewWidget::setPosMove()
{
}

void VRViewWidget::slotOnSetMapView()
{
	if (MapPointListManagerIns.isMapBuilt())
	{
		ui.stackedWidget->setCurrentWidget(ui.mapPage);
		QPixmap map(MapPointListManagerIns.getMapList().at(0).mapPath);
		ui.mapPage->setAutoFillBackground(true);

		QPalette palette;
		palette.setBrush(ui.mapPage->backgroundRole(), QBrush(map.scaled(ui.mapPage->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
		ui.mapPage->setPalette(palette);
		ui.mapPage->setMapType(MAP_PREVIEW);
		ui.mapPage->drawAllMapPoint();
		ui.mapPage->setButtonVisible(false);

		is_map_load_ = true;
	}
	else
	{
		return;
	}
}

void VRViewWidget::slotOnResizePreviewMap()
{
	if (is_map_load_)
	{
		QPixmap map(MapPointListManagerIns.getMapList().at(0).mapPath);
		ui.mapPage->setAutoFillBackground(true);
		QPalette palette;
		QSize temp;
		palette.setBrush(ui.mapPage->backgroundRole(), QBrush(map.scaled(ui.mapPage->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
		ui.mapPage->setPalette(palette);
		ui.mapPage->reSizeScreen();
	}
}



void VRViewWidget::initConnect()
{
	connect(ui.arrowButton, SIGNAL(clicked()), this, SIGNAL(sigOnStepOnMapSettings()));

	connect(ViewSignal::instance(), SIGNAL(sigOnResizeMap()), this, SLOT(slotOnResizePreviewMap()));
}
