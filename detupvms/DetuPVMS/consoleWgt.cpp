#include "consoleWgt.h"
#include "ui_consoleWgt.h"

consoleWgt::consoleWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::consoleWgt)
{
    ui->setupUi(this);
	init();
	initConnect();
}

consoleWgt::~consoleWgt()
{

}

void consoleWgt::init()
{
	QString playPath = "background-image:url(:/image/image/preview.png); background-size:41px 31px; background-repeat:no-repeat; background-position:center; background-color:#323232; border-radius:8px; ";
	QString replayPath = "background-image:url(:/image/image/replay.png); background-size:41px 31px; background-repeat:no-repeat; background-position:center; background-color:#323232; border-radius:8px; ";
	QString devicePath = "background-image:url(:/image/image/device.png); background-size:41px 31px; background-repeat:no-repeat; background-position:center; background-color:#323232; border-radius:8px; ";
	QString storagePath = "background-image:url(:/image/image/storage.png); background-size:41px 31px; background-repeat:no-repeat; background-position:center; background-color:#323232; border-radius:8px; ";
	QString VRMapPath = "background-image:url(:/image/image/map.png); background-size:41px 31px; background-repeat:no-repeat; background-position:center; background-color:#323232; border-radius:8px;";
	QString VRViewPath = "background-image:url(:/image/image/vr.png); background-size:41px 31px; background-repeat:no-repeat; background-position:center; background-color:#323232; border-radius:8px;";
	QString IOTPlatPath = "background-image:url(:/image/image/iotPlatform.png); background-size:41px 31px; background-repeat:no-repeat; background-position:center; background-color:#323232; border-radius:8px;";
	
	ui->playPage_->setImageAndText(tr("Preview"), tr("Panoramic image real-time monitoring"), playPath, commonPageWgt::Play);
	ui->replayPage_->setImageAndText(tr("Replay"), tr("Play a panoramic video at a specified time"), replayPath, commonPageWgt::RePlay);
	ui->devicePage_->setImageAndText(tr("Device"), tr("Add support for the camera device, the device initialization"), devicePath, commonPageWgt::Device);
	ui->storagePage_->setImageAndText(tr("Storage"), tr("View the storage device and format the device"), storagePath, commonPageWgt::Storage);
	ui->VRMapPage->setImageAndText(tr("VRMap"), tr("Add a map showing the location of the panorama in the map"), VRMapPath, commonPageWgt::VRMap);
	ui->VRViewPage->setImageAndText(tr("VRView"), tr("View the panorama through map navigation"), VRViewPath, commonPageWgt::VRView);
	
	ui->IOTPage_->setImageAndText(tr("IOTPlatform"), tr("IOT data manager center"), IOTPlatPath, commonPageWgt::IOTPlat);

}

void consoleWgt::initConnect()
{
	connect(ui->playPage_, SIGNAL(TrigConsoleButtonClicked(commonPageWgt::ConsoleButton)), this, SIGNAL(ConsoleButtonClicked(commonPageWgt::ConsoleButton)));
	connect(ui->replayPage_, SIGNAL(TrigConsoleButtonClicked(commonPageWgt::ConsoleButton)), this, SIGNAL(ConsoleButtonClicked(commonPageWgt::ConsoleButton)));
	
	
	
	connect(ui->devicePage_, SIGNAL(TrigConsoleButtonClicked(commonPageWgt::ConsoleButton)), this, SIGNAL(ConsoleButtonClicked(commonPageWgt::ConsoleButton)));
	connect(ui->storagePage_, SIGNAL(TrigConsoleButtonClicked(commonPageWgt::ConsoleButton)), this, SIGNAL(ConsoleButtonClicked(commonPageWgt::ConsoleButton)));
	connect(ui->VRMapPage, SIGNAL(TrigConsoleButtonClicked(commonPageWgt::ConsoleButton)), this, SIGNAL(ConsoleButtonClicked(commonPageWgt::ConsoleButton)));
	connect(ui->VRViewPage, SIGNAL(TrigConsoleButtonClicked(commonPageWgt::ConsoleButton)), this, SIGNAL(ConsoleButtonClicked(commonPageWgt::ConsoleButton)));
	connect(ui->IOTPage_, SIGNAL(TrigConsoleButtonClicked(commonPageWgt::ConsoleButton)), this, SIGNAL(ConsoleButtonClicked(commonPageWgt::ConsoleButton)));
}
