#include "homeWgt.h"
#include "ui_homeWgt.h"

#include "feedback.h"

//全局控制器
#include "MessageManager.h"
#include "SocketManager.h"
#include "TcpDataManager.hpp"
#include "SetAdminMananger.h"
#include "PVMSEventManager.h"

using namespace dm::server;

homeWgt::homeWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::homeWgt)
{
    ui->setupUi(this);
    init();
	initConnect();
}

homeWgt::~homeWgt()
{

}

void homeWgt::setCloseClient()
{
	ui->playWgt_->ClosePlayer();
	ui->replayWgt_->closePlayer();
}

void homeWgt::setServerOline(bool online)
{
	ui->deviceWgt_->setServerOnline(online);
}

void homeWgt::setSpeedPos(int w)
{
	ui->replayWgt_->setSpeedPos(w);
}

void homeWgt::clearPlayerStatus()
{
	ui->playWgt_->ResetPlayerStatus();
	ui->replayWgt_->clearPlayerStatus();
}

void homeWgt::setPosMove()
{
	ui->playWgt_->setPosMove();
}

void homeWgt::closePreviewReplay()
{
	ui->playWgt_->ResetPlayerStatus();
	ui->replayWgt_->clearPlayerStatus();
}

void homeWgt::closeMapPlay()
{
	ui->VRViewWgt_->clearPlayerStatus();
}

void homeWgt::slotOnStepOnMapSettings()
{
	ui->stackedWidget->setCurrentWidget(ui->VRMapWgt_);
	if (!ui->tabVRMapWgt_->isVisible())
	{
		ui->tabVRMapWgt_->setVisible(true);
	}
}

void homeWgt::slotOnSetFullScreen(bool is_full_screen)
{
	ui->contrlWgt->setVisible(is_full_screen);
}

bool homeWgt::eventFilter(QObject *watched, QEvent *event)
{
	if (watched == ui->stackedWidget)
	{
		if (ui->stackedWidget->currentWidget() == ui->consoleWgt_)
		{
			ui->tabConsoleWgt_->setSelectedStatus(1);
			ui->tabDeviceWgt_->setSelectedStatus(0);
			ui->tabPlayWgt_->setSelectedStatus(0);
			ui->tabReplayWgt_->setSelectedStatus(0);
			ui->tabStorageWgt_->setSelectedStatus(0);
			ui->tabVRMapWgt_->setSelectedStatus(0);
			ui->tabVRViewWgt_->setSelectedStatus(0);
			ui->tabIOTPlatformWgt_->setSelectedStatus(0);
		}
		if (ui->stackedWidget->currentWidget() == ui->deviceWgt_)
		{
			ui->tabConsoleWgt_->setSelectedStatus(0);
			ui->tabDeviceWgt_->setSelectedStatus(1);
			ui->tabPlayWgt_->setSelectedStatus(0);
			ui->tabReplayWgt_->setSelectedStatus(0);
			ui->tabStorageWgt_->setSelectedStatus(0);
			ui->tabVRMapWgt_->setSelectedStatus(0);
			ui->tabVRViewWgt_->setSelectedStatus(0);
			ui->tabIOTPlatformWgt_->setSelectedStatus(0);
		}
		if (ui->stackedWidget->currentWidget() == ui->playWgt_)
		{
			closeMapPlay();
			ui->tabConsoleWgt_->setSelectedStatus(0);
			ui->tabDeviceWgt_->setSelectedStatus(0);
			ui->tabPlayWgt_->setSelectedStatus(1);
			ui->tabReplayWgt_->setSelectedStatus(0);
			ui->tabStorageWgt_->setSelectedStatus(0);
			ui->tabVRMapWgt_->setSelectedStatus(0);
			ui->tabVRViewWgt_->setSelectedStatus(0);
			ui->tabIOTPlatformWgt_->setSelectedStatus(0);
		}
		if (ui->stackedWidget->currentWidget() == ui->replayWgt_)
		{
			closeMapPlay();
			ui->tabConsoleWgt_->setSelectedStatus(0);
			ui->tabDeviceWgt_->setSelectedStatus(0);
			ui->tabPlayWgt_->setSelectedStatus(0);
			ui->tabReplayWgt_->setSelectedStatus(1);
			ui->tabStorageWgt_->setSelectedStatus(0);
			ui->tabVRMapWgt_->setSelectedStatus(0);
			ui->tabVRViewWgt_->setSelectedStatus(0);
			ui->tabIOTPlatformWgt_->setSelectedStatus(0);
		}
		if (ui->stackedWidget->currentWidget() == ui->storageWgt_)
		{
			ui->tabConsoleWgt_->setSelectedStatus(0);
			ui->tabDeviceWgt_->setSelectedStatus(0);
			ui->tabPlayWgt_->setSelectedStatus(0);
			ui->tabReplayWgt_->setSelectedStatus(0);
			ui->tabStorageWgt_->setSelectedStatus(1);
			ui->tabVRMapWgt_->setSelectedStatus(0);
			ui->tabVRViewWgt_->setSelectedStatus(0);
			ui->tabIOTPlatformWgt_->setSelectedStatus(0);
		}
		if (ui->stackedWidget->currentWidget() == ui->VRMapWgt_)
		{
			closePreviewReplay();
			ui->tabConsoleWgt_->setSelectedStatus(0);

			ui->tabDeviceWgt_->setSelectedStatus(0);
			ui->tabPlayWgt_->setSelectedStatus(0);
			ui->tabReplayWgt_->setSelectedStatus(0);
			ui->tabStorageWgt_->setSelectedStatus(0);
			ui->tabVRMapWgt_->setSelectedStatus(1);
			ui->tabVRViewWgt_->setSelectedStatus(0);
			ui->tabIOTPlatformWgt_->setSelectedStatus(0);
		}
		if (ui->stackedWidget->currentWidget() == ui->VRViewWgt_)
		{
			closePreviewReplay();
			ui->tabConsoleWgt_->setSelectedStatus(0);
			ui->tabDeviceWgt_->setSelectedStatus(0);
			ui->tabPlayWgt_->setSelectedStatus(0);
			ui->tabReplayWgt_->setSelectedStatus(0);
			ui->tabStorageWgt_->setSelectedStatus(0);
			ui->tabVRMapWgt_->setSelectedStatus(0);
			ui->tabVRViewWgt_->setSelectedStatus(1);
			ui->tabIOTPlatformWgt_->setSelectedStatus(0);
		}
		if (ui->stackedWidget->currentWidget() == ui->IOTPlatWgt_)
		{
			closePreviewReplay();
			ui->tabConsoleWgt_->setSelectedStatus(0);
			ui->tabDeviceWgt_->setSelectedStatus(0);
			ui->tabPlayWgt_->setSelectedStatus(0);
			ui->tabReplayWgt_->setSelectedStatus(0);
			ui->tabStorageWgt_->setSelectedStatus(0);
			ui->tabVRMapWgt_->setSelectedStatus(0);
			ui->tabVRViewWgt_->setSelectedStatus(0);
			ui->tabIOTPlatformWgt_->setSelectedStatus(1);
		}
	}
	return QWidget::eventFilter(watched, event);
}

void homeWgt::init()
{
	ui->stackedWidget->installEventFilter(this);
	ui->tabDeviceWgt_->setTittle(tr("Device"),supTabWidget::TabDevice);
	ui->tabPlayWgt_->setTittle(tr("Preview"), supTabWidget::TabPlay);
	ui->tabReplayWgt_->setTittle(tr("Replay"), supTabWidget::TabRePlay);
	ui->tabStorageWgt_->setTittle(tr("Storage"), supTabWidget::TabStorage);
	ui->tabVRMapWgt_->setTittle(tr("VRMap"), supTabWidget::TabVRMap);
	ui->tabVRViewWgt_->setTittle(tr("VRView"), supTabWidget::TabVRView);
	ui->tabIOTPlatformWgt_->setTittle(tr("IOTPlat"), supTabWidget::TabIOTPlat);

	ui->tabDeviceWgt_->setVisible(false);
	ui->tabPlayWgt_->setVisible(false);
	ui->tabReplayWgt_->setVisible(false);
	ui->tabStorageWgt_->setVisible(false);
	ui->tabVRMapWgt_->setVisible(false);
	ui->tabVRViewWgt_->setVisible(false);
	ui->tabIOTPlatformWgt_->setVisible(false);
	ui->stackedWidget->setCurrentWidget(ui->consoleWgt_);
}

void homeWgt::initConnect()
{
	//是否切换到预览和回放界面，如果是则播放，如果不是就解码队列return
	connect(ui->stackedWidget, SIGNAL(currentChanged(int)), ui->playWgt_, SLOT(slotOnPlaywgtSelected(int)));
	connect(ui->stackedWidget, SIGNAL(currentChanged(int)), ui->replayWgt_, SLOT(slotOnRePlaywgtSelected(int)));

	//主界面tab按钮信号槽链接
	connect(ui->tabDeviceWgt_, SIGNAL(TrigSupTabButtonClicked(supTabWidget::supTabWgtButton)), this, SLOT(TabSupButtonClickedSlot(supTabWidget::supTabWgtButton)));
	connect(ui->tabPlayWgt_, SIGNAL(TrigSupTabButtonClicked(supTabWidget::supTabWgtButton)), this, SLOT(TabSupButtonClickedSlot(supTabWidget::supTabWgtButton)));
	connect(ui->tabReplayWgt_, SIGNAL(TrigSupTabButtonClicked(supTabWidget::supTabWgtButton)), this, SLOT(TabSupButtonClickedSlot(supTabWidget::supTabWgtButton)));
	connect(ui->tabStorageWgt_, SIGNAL(TrigSupTabButtonClicked(supTabWidget::supTabWgtButton)), this, SLOT(TabSupButtonClickedSlot(supTabWidget::supTabWgtButton)));
	connect(ui->tabVRMapWgt_, SIGNAL(TrigSupTabButtonClicked(supTabWidget::supTabWgtButton)), this, SLOT(TabSupButtonClickedSlot(supTabWidget::supTabWgtButton)));
	connect(ui->tabVRViewWgt_, SIGNAL(TrigSupTabButtonClicked(supTabWidget::supTabWgtButton)), this, SLOT(TabSupButtonClickedSlot(supTabWidget::supTabWgtButton)));
	connect(ui->tabIOTPlatformWgt_, SIGNAL(TrigSupTabButtonClicked(supTabWidget::supTabWgtButton)), this, SLOT(TabSupButtonClickedSlot(supTabWidget::supTabWgtButton)));

	connect(ui->tabConsoleWgt_, SIGNAL(TrigTabConsoleButtonClicked()), this, SLOT(TabConsoleButtonClickedSlot()));
	connect(ui->tabPlayWgt_, SIGNAL(sigOnTabClose(supTabWidget::supTabWgtButton)), this, SLOT(slot_tabClosed(supTabWidget::supTabWgtButton)));
	connect(ui->tabReplayWgt_, SIGNAL(sigOnTabClose(supTabWidget::supTabWgtButton)), this, SLOT(slot_tabClosed(supTabWidget::supTabWgtButton)));
	connect(ui->tabDeviceWgt_, SIGNAL(sigOnTabClose(supTabWidget::supTabWgtButton)), this, SLOT(slot_tabClosed(supTabWidget::supTabWgtButton)));
	connect(ui->tabStorageWgt_, SIGNAL(sigOnTabClose(supTabWidget::supTabWgtButton)), this, SLOT(slot_tabClosed(supTabWidget::supTabWgtButton)));
	connect(ui->tabVRMapWgt_, SIGNAL(sigOnTabClose(supTabWidget::supTabWgtButton)), this, SLOT(slot_tabClosed(supTabWidget::supTabWgtButton)));
	connect(ui->tabVRViewWgt_, SIGNAL(sigOnTabClose(supTabWidget::supTabWgtButton)), this, SLOT(slot_tabClosed(supTabWidget::supTabWgtButton)));
	connect(ui->tabIOTPlatformWgt_, SIGNAL(sigOnTabClose(supTabWidget::supTabWgtButton)), this, SLOT(slot_tabClosed(supTabWidget::supTabWgtButton)));

	//控制台界面按钮信号槽信号链接
	connect(ui->consoleWgt_, SIGNAL(ConsoleButtonClicked(commonPageWgt::ConsoleButton)), this, SLOT(ConsoleButtonClickedSlot(commonPageWgt::ConsoleButton)));
	//分发列表
	qRegisterMetaType<QList<deviceInfo>>("QList<deviceInfo>");
	connect(ui->deviceWgt_, SIGNAL(sigOnDistributeList(QList<deviceInfo>)), this, SLOT(slotOnDistributeList(QList<deviceInfo>)));
	connect(ui->deviceWgt_, SIGNAL(sigOnUpdate()), this, SIGNAL(sigOnUpdate()));
	connect(ui->deviceWgt_, SIGNAL(sigOnSelectWarning()), this, SIGNAL(sigOnSelectWarning()));
	connect(ui->deviceWgt_, SIGNAL(sigOnBindPTZFailed()), this, SIGNAL(sigOnBindPTZFailed()));

	connect(ui->storageWgt_, SIGNAL(sigOnUpdate()), this, SIGNAL(sigOnUpdate()));

	connect(ui->playWgt_, SIGNAL(sigOnBindPTZWarning()), this, SIGNAL(sigOnBindPTZWarning()));
	connect(ui->playWgt_, SIGNAL(sigOnOptMizeSuccess()), this, SIGNAL(sigOnOptMizeSuccess()));
	connect(ui->playWgt_, SIGNAL(sigOnTransportList(QList<deviceInfo>)), ui->deviceWgt_, SLOT(transportList(QList<deviceInfo>)));

	connect(ui->replayWgt_, SIGNAL(sigOnTransportList(QList<deviceInfo>)), ui->deviceWgt_, SLOT(transportList(QList<deviceInfo>)));
	connect(ui->replayWgt_, SIGNAL(sigOnOptMizeSuccess()), this, SIGNAL(sigOnOptMizeSuccess()));

	connect(ui->VRViewWgt_, SIGNAL(sigOnStepOnMapSettings()), this, SLOT(slotOnStepOnMapSettings()));
	connect(this, SIGNAL(sigOnSetMapView()), ui->VRViewWgt_, SLOT(slotOnSetMapView()));

	connect(&PVMSEventManagerManagerIns, SIGNAL(sigOnSetFullScreen(bool)), this, SLOT(slotOnSetFullScreen(bool)), Qt::AutoConnection);
	connect(&PVMSEventManagerManagerIns, SIGNAL(sigOnReplaySetFullScreen(bool)), this, SLOT(slotOnSetFullScreen(bool)), Qt::AutoConnection);

}

void homeWgt::TabSupButtonClickedSlot(supTabWidget::supTabWgtButton type)
{
	switch (type)
	{
	case supTabWidget::TabPlay:
	{
		ui->stackedWidget->setCurrentWidget(ui->playWgt_);
		ui->playWgt_->setHiddenCtrl(true);
		break;
	}
	case supTabWidget::TabRePlay:
	{
		ui->stackedWidget->setCurrentWidget(ui->replayWgt_);
		QTimer::singleShot(1, this, [&](){
			ui->playWgt_->setHiddenCtrl(false);
		});
		break;
	}
	case supTabWidget::TabDevice:
	{
		ui->stackedWidget->setCurrentWidget(ui->deviceWgt_);
		QTimer::singleShot(1, this, [&](){
			ui->playWgt_->setHiddenCtrl(false);
		});
		break;
	}
	case supTabWidget::TabStorage:
	{
		ui->stackedWidget->setCurrentWidget(ui->storageWgt_);
		QTimer::singleShot(1, this, [&](){
			ui->playWgt_->setHiddenCtrl(false);
		});
		break;
	}
	case supTabWidget::TabVRMap:
	{
		ui->stackedWidget->setCurrentWidget(ui->VRMapWgt_);
		QTimer::singleShot(1, this, [&](){
			ui->playWgt_->setHiddenCtrl(false);
		});
		break;
	}
	case supTabWidget::TabVRView:
	{
		ui->stackedWidget->setCurrentWidget(ui->VRViewWgt_);
		emit sigOnSetMapView();
		QTimer::singleShot(1, this, [&](){
			ui->playWgt_->setHiddenCtrl(false);
		});
		break;
	}
	case supTabWidget::TabIOTPlat:
	{
		ui->stackedWidget->setCurrentWidget(ui->IOTPlatWgt_);
		QTimer::singleShot(1, this, [&](){
			ui->playWgt_->setHiddenCtrl(false);
		});
		break;
	}
	default:
	{
		ui->playWgt_->setHiddenCtrl(false);
		break;
	}
	}
}

void homeWgt::TabConsoleButtonClickedSlot()
{
	ui->stackedWidget->setCurrentWidget(ui->consoleWgt_);
	QTimer::singleShot(1, this, [&](){
		ui->playWgt_->setHiddenCtrl(false);
	//	ui->replayWgt_->setHiddenTime(false);
	});
}

void homeWgt::ConsoleButtonClickedSlot(commonPageWgt::ConsoleButton type)
{
	switch (type)
	{
	case commonPageWgt::Play:
	{
		ui->stackedWidget->setCurrentWidget(ui->playWgt_);
			ui->playWgt_->setHiddenCtrl(true);
		//	ui->replayWgt_->setHiddenTime(false);
		if (!ui->tabPlayWgt_->isVisible())
		{
			ui->tabPlayWgt_->setVisible(true);
		}
	}
	break;
	case commonPageWgt::RePlay:
	{		
		ui->stackedWidget->setCurrentWidget(ui->replayWgt_);
		QTimer::singleShot(1, this, [&](){
			ui->playWgt_->setHiddenCtrl(false);
	//		ui->replayWgt_->setHiddenTime(true);
		});
		if (!ui->tabReplayWgt_->isVisible())
		{
			ui->tabReplayWgt_->setVisible(true);
		}
	}
	break;
	case commonPageWgt::Device:
	{
		if (!SetAdminManangerIns.getAdmin())
		{
			Feedback::instance()->maskUI(NOT_ADMIN);
			return;
		}
		ui->stackedWidget->setCurrentWidget(ui->deviceWgt_);
		QTimer::singleShot(1, this, [&](){
			ui->playWgt_->setHiddenCtrl(false);
		//	ui->replayWgt_->setHiddenTime(false);
		});
		if (!ui->tabDeviceWgt_->isVisible())
		{
			ui->tabDeviceWgt_->setVisible(true);
		}
	}
	break;
	case commonPageWgt::Storage:
	{
		if (!SetAdminManangerIns.getAdmin())
		{
			Feedback::instance()->maskUI(NOT_ADMIN);
			return;
		}
		ui->stackedWidget->setCurrentWidget(ui->storageWgt_);
		QTimer::singleShot(1, this, [&](){
			ui->playWgt_->setHiddenCtrl(false);
		//	ui->replayWgt_->setHiddenTime(false);
		});
		if (!ui->tabStorageWgt_->isVisible())
		{
			ui->tabStorageWgt_->setVisible(true);
		}
	}
	break;
	case commonPageWgt::VRMap:
	{
		if (!SetAdminManangerIns.getAdmin())
		{
			Feedback::instance()->maskUI(NOT_ADMIN);
			return;
		}
		ui->stackedWidget->setCurrentWidget(ui->VRMapWgt_);
		QTimer::singleShot(1, this, [&](){
			ui->playWgt_->setHiddenCtrl(false);
			//	ui->replayWgt_->setHiddenTime(false);
		});
		if (!ui->tabVRMapWgt_->isVisible())
		{
			ui->tabVRMapWgt_->setVisible(true);
		}
		break;
	}
	case commonPageWgt::VRView:
	{
		if (!SetAdminManangerIns.getAdmin())
		{
			Feedback::instance()->maskUI(NOT_ADMIN);
			return;
		}
		ui->stackedWidget->setCurrentWidget(ui->VRViewWgt_);
		emit sigOnSetMapView();

		QTimer::singleShot(1, this, [&](){
			ui->playWgt_->setHiddenCtrl(false);
			//		ui->replayWgt_->setHiddenTime(false);
		});
		if (!ui->tabVRViewWgt_->isVisible())
		{
			ui->tabVRViewWgt_->setVisible(true);
		}
		break;
	}
	case commonPageWgt::IOTPlat:
	{
		if (!SetAdminManangerIns.getAdmin())
		{
			Feedback::instance()->maskUI(NOT_ADMIN);
			return;
		}
		ui->stackedWidget->setCurrentWidget(ui->IOTPlatWgt_);
		QTimer::singleShot(1, this, [&](){
			ui->playWgt_->setHiddenCtrl(false);
		});
		if (!ui->tabIOTPlatformWgt_->isVisible())
		{
			ui->tabIOTPlatformWgt_->setVisible(true);
		}
		break;
	}
	default:
		break;
	}
}

void homeWgt::slot_tabClosed(supTabWidget::supTabWgtButton type)
{
	
	ui->stackedWidget->setCurrentWidget(ui->consoleWgt_);
	switch (type)
	{
	case commonPageWgt::Play:
	{
		ui->tabPlayWgt_->setVisible(false);
		ui->playWgt_->setHiddenCtrl(false);
	}
		break;
	case commonPageWgt::RePlay:
	{
		ui->tabReplayWgt_->setVisible(false);
		//ui->replayWgt_->setHiddenTime(false);
	}
		break;
	case commonPageWgt::Device:
	{
		 ui->tabDeviceWgt_->setVisible(false);
	}
		break;
	case commonPageWgt::Storage:
	{
		ui->tabStorageWgt_->setVisible(false);
	}
		break;
	case commonPageWgt::VRMap:
		ui->tabVRMapWgt_->setVisible(false);
		break;
	case commonPageWgt::VRView:
		ui->tabVRViewWgt_->setVisible(false);
		break;
	case commonPageWgt::IOTPlat:
		ui->tabIOTPlatformWgt_->setVisible(false);
		break;
	default:
		break;
	}
}

void homeWgt::slotOnDistributeList(QList<deviceInfo> deviceList)
{
	ui->playWgt_->UpdateListSlot(deviceList);
	ui->replayWgt_->RePlayUpdateListSlot(deviceList);
	ui->storageWgt_->updateDeviceList(deviceList);
}
