
#include <QFileDialog>

#include "VRMapWidget.h"
#include "ViewSignal.h"
#include "logging.hpp"

//初始化控制器
#include "MessageManager.h"
#include "SocketManager.h"
#include "TcpDataManager.hpp"
#include "ListAndGLWindowManager.h"
#include "MapPointListManager.h"

VRMapWidget::VRMapWidget(QWidget *parent)
	: QWidget(parent)
	, m_addDlag(NULL)
	, m_tipDlg(NULL)
	, is_map_load_(false)
{
	ui.setupUi(this);
	init();
	initConnect();
}

VRMapWidget::~VRMapWidget()
{

}

void VRMapWidget::slotOnAddPanoramaBtnClicked()
{
	if (m_addDlag == NULL){
		m_addDlag = new commonAddDlg;
		connect(m_addDlag, SIGNAL(sigOnGetPanoramaList(QList<PanoMapPointInfo_t>)), this, SLOT(slotOnGetPanoramaList(QList<PanoMapPointInfo_t>)));
		m_addDlag->setTabName(QStringLiteral("全景机"), QStringLiteral("全景场景"));
		m_addDlag->setDlgTitleText(QStringLiteral("添加全景"));
	}

	current_map_ = MapPointListManagerIns.getMap();
	m_addDlag->updateDeviceItem(current_map_.panoramaList);
	m_addDlag->initDeviceList(m_deviceList, m_panoSceneList);
	m_addDlag->activateWindow();
	m_addDlag->raise();
	QPoint point = this->mapToGlobal(this->pos());
	int x = point.x();
	int y = point.y();
	int xx = this->width();
	int yy = m_addDlag->width();
	int nX = (this->width() - m_addDlag->width()) / 2 + x;
	int nY = (this->height() - m_addDlag->height()) / 2 + y;
	m_addDlag->move(nX, nY);
	m_addDlag->exec();
}

void VRMapWidget::slotOnAddMapBtnClicked()
{
	MapPointListManagerIns.getMapListFromLocal();
	current_filePath_ = QFileDialog::getOpenFileName(this, tr("Open Map"), QDir::homePath() + "/AppData/Local/Pano-VMS/Map/panoMap", tr("Image Files (*.png *.jpg *.bmp)"));
	if (current_filePath_ == "")
	{
		return;
	}
	if (current_filePath_==current_map_.mapPath)
	{
		return;
	}

	ui.listWidget->clear();
	m_listWgtItemList.clear();
	current_map_.clear();
	MapPointListManagerIns.clear();

	if (MapPointListManagerIns.findMapExist(current_filePath_))
	{
		current_map_ = MapPointListManagerIns.getMap();
		if (m_addDlag == NULL){
			m_addDlag = new commonAddDlg;
			connect(m_addDlag, SIGNAL(sigOnGetPanoramaList(QList<PanoMapPointInfo_t>)), this, SLOT(slotOnGetPanoramaList(QList<PanoMapPointInfo_t>)));
			m_addDlag->setTabName(QStringLiteral("全景机"), QStringLiteral("全景场景"));
			m_addDlag->setDlgTitleText(QStringLiteral("添加全景"));
		}
		m_addDlag->updateDeviceItem(current_map_.panoramaList);
		slotOnGetPanoramaList(current_map_.panoramaList);
		ui.mapPage->recoverMapSettings();
	}
	else
	{
		/*
		*  每次设置新地图，把上一个地图数据current_map_清空
		*  清空、或者刷新列表
		*  重新绘制地图上的点
		*  如果从数据库拉去，再去刷新
		*/

		if (m_addDlag)
		{
			m_addDlag->deleteLater();
			m_addDlag = NULL;
		}
		ui.mapPage->clearData();


		QStringList strList = current_filePath_.split("/");
		QString file;
		if (strList.size() > 0)
		{
			file = strList.at(strList.size() - 1);
			current_map_.mapName = file.left(file.indexOf("."));
			current_map_.mapPath = current_filePath_;


			QFile file(current_filePath_);
			if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
			{
				Log::Info("read map file open failed or map file no exit!");
			}
			QByteArray array = file.readAll();
			QString data(array);
			current_map_.mapData = data;
			Log::Info("%s", current_map_.mapName.toStdString().c_str());
		}

		MapPointListManagerIns.updateMap(current_map_);
	}

	ui.stackedWidget->setCurrentWidget(ui.mapPage);
	//先要打开左边的列表，在缩放地图大小，否则有误差
	ui.leftWidget->setVisible(true);

	QPixmap map(current_filePath_);
	ui.mapPage->setAutoFillBackground(true);
	QPalette palette;
	QSize temp;
	palette.setBrush(ui.mapPage->backgroundRole(), QBrush(map.scaled(ui.mapPage->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
	ui.mapPage->setPalette(palette);
	ui.mapPage->setMapType(MAP_CONTROL);
	ui.mapPage->drawAllMapPoint();
	is_map_load_ = true;



}


void VRMapWidget::slotOnRemoveOnMapDevice(PanoMapPointInfo_t panoInfo)
{
	for (int i = 0; i < m_listWgtItemList.size(); ++i)
	{
		PanoMapPointInfo_t info;
		m_listWgtItemList[i]->getItemData(info);
		if (info.curr_id == panoInfo.curr_id){
			m_listWgtItemList[i]->setNewHidden(false);
		}
	}

	if (m_addDlag)	{
		m_addDlag->removeOnMapItem(panoInfo);
	}
}

void VRMapWidget::slotOnGetDeviceList(const QList<deviceInfo> deviceList)
{
	//在线设备列表
	m_deviceList = deviceList;
	m_panoSceneList.clear();

	//文件读取全景场景列表
	QDir panoSceneDir(QDir::homePath() + "/AppData/Local/Pano-VMS/panoScene");
	panoSceneDir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
	QFileInfoList panoScenelist = panoSceneDir.entryInfoList();

    for (int i = 0; i < panoScenelist.size(); i++)
	{
		QFileInfo fileInfo = panoScenelist.at(i);
		PanoSceneInfo_t info;
		info.id = i + 1;
		info.name = fileInfo.fileName();
		info.Path = fileInfo.filePath();
	//	Log::Info("dir num : %d , num %d dir name : %s", panoScenelist.size(), i+1,info.name.toStdString().c_str());

		QDir fileDir(fileInfo.filePath());
		fileDir.setFilter(QDir::Files | QDir::NoSymLinks);
		QFileInfoList flieList = fileDir.entryInfoList();
		for (int j = 0; j < flieList.size(); ++j)
		{
			QFileInfo listInfo = flieList.at(j);
			PanoSceneInfo_t subInfo;
			subInfo.id = j + 1;
			subInfo.name = listInfo.fileName();
			subInfo.Path = listInfo.filePath();

			QFile file(listInfo.filePath());
			if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
			{
				Log::Info("read scene  open failed or scene file no exit!");
			}
			QByteArray array = file.readAll();
			QString data(array);
			subInfo.fileData = data;
		//	Log::Info("file num : %d , file %d file name : %s", flieList.size(), j + 1, subInfo.name.toStdString().c_str());

			info.sceneList.append(subInfo);
		}
		m_panoSceneList.append(info);
	}

	if (m_addDlag)
	{
		m_addDlag->initDeviceList(m_deviceList, m_panoSceneList);
	}

	MapPointListManagerIns.updatePtzAndSpyData(deviceList);
}


void VRMapWidget::slotOnGetPanoramaList(QList<PanoMapPointInfo_t> panoramaList)
{
	current_map_.panoramaList = panoramaList;

	int itemNum = ui.listWidget->count();
	if (itemNum == 0)
	{
		m_listWgtItemList.clear();
		for (int i = 0; i < current_map_.panoramaList.size(); ++i)
		{
			panoramaItemWidget *itemWidget = new panoramaItemWidget;
			connect(itemWidget, SIGNAL(sigOnDeleteItem()), this, SLOT(slotOnDeleteItem()));
			current_map_.panoramaList[i].curr_id = i + 1;
			if (current_map_.panoramaList[i].onMapFlag)
			{
				itemWidget->setNewHidden(true);
			}
			itemWidget->initData(current_map_.panoramaList[i]);
			QListWidgetItem *item = new QListWidgetItem;
			item->setSizeHint(QSize(150, 42));
			ui.listWidget->insertItem(i, item);
			ui.listWidget->setItemWidget(item, itemWidget);
			m_listWgtItemList.append(itemWidget);
		}
	}
	else{
		for (int i = 0; i < current_map_.panoramaList.size(); ++i)
		{
			int index = 0;
			for (int j = 0; j < m_listWgtItemList.size(); ++j)
			{
				PanoMapPointInfo_t panoMapInfo;
				m_listWgtItemList[j]->getItemData(panoMapInfo);

				if (panoMapInfo.map_point_type == DEVICE_ON_LINE || panoMapInfo.map_point_type == DEVICE_OFF_LINE)
				{
					if (!panoMapInfo.cameraInfo.name.isEmpty() && panoMapInfo.cameraInfo.name == current_map_.panoramaList[i].cameraInfo.name)
					{
						index++;
					}
				}
				else if (panoMapInfo.map_point_type == PANOSCENE_ON_LINE)
				{
					if (!panoMapInfo.sceneInfo.name.isEmpty() && panoMapInfo.sceneInfo.name == current_map_.panoramaList[i].sceneInfo.name)
					{
						index++;
					}
				}
			}

			if (index == 0)
			{
				panoramaItemWidget *itemWidget = new panoramaItemWidget;
				connect(itemWidget, SIGNAL(sigOnDeleteItem()), this, SLOT(slotOnDeleteItem()));

				PanoMapPointInfo_t panoMapInfo;
				m_listWgtItemList[m_listWgtItemList.size() - 1]->getItemData(panoMapInfo);
				current_map_.panoramaList[i].curr_id = panoMapInfo.curr_id + 1;
				if (current_map_.panoramaList[i].onMapFlag)
				{
					itemWidget->setNewHidden(true);
				}
				itemWidget->initData(current_map_.panoramaList[i]);
				QListWidgetItem *item = new QListWidgetItem;
				item->setSizeHint(QSize(150, 42));
				ui.listWidget->insertItem(i, item);
				ui.listWidget->setItemWidget(item, itemWidget);
				m_listWgtItemList.append(itemWidget);
			}
		}
	}



	if (m_addDlag)
	{
		m_addDlag->updateDeviceItem(current_map_.panoramaList);
	}

	//保存到单例中,每次地图控制界面添加数据，都传入到地图界面中，只维护一份地图数据
	MapPointListManagerIns.updateMap(current_map_);
}

void VRMapWidget::slotItemSelected(QListWidgetItem *current, QListWidgetItem *previous)
{
	panoramaItemWidget *preItemWidget = qobject_cast<panoramaItemWidget*> (ui.listWidget->itemWidget(previous));
	if (preItemWidget)
	{
		preItemWidget->setDeleteChecked(false);
	}

	panoramaItemWidget *curItemWidget = qobject_cast<panoramaItemWidget*> (ui.listWidget->itemWidget(current));
	if (curItemWidget)
	{
		curItemWidget->setDeleteChecked(true);
	}
}

void VRMapWidget::slotOnDeleteItem()
{
	if (m_tipDlg == NULL)
	{
		m_tipDlg = new commonTipDlg;
		connect(m_tipDlg, SIGNAL(sigOnConfirm()), this, SLOT(slotOnTipDlgConfirm()));
	}
	m_tipDlg->setTitleLabelText(QStringLiteral("删除全景设备"));
	m_tipDlg->setTipText(QStringLiteral("确定要删除该全景设备吗？"));
	m_tipDlg->activateWindow();
	QPoint point = this->mapToGlobal(this->pos());
	int x = point.x();
	int y = point.y();
	int xx = this->width();
	int yy = m_tipDlg->width();
	int nX = (this->width() - m_tipDlg->width()) / 2 + x;
	int nY = (this->height() - m_tipDlg->height()) / 2 + y;
	m_tipDlg->move(nX, nY);
	m_tipDlg->exec();
}

void VRMapWidget::slotOnTipDlgConfirm()
{
	if (m_tipDlg)
	{
		m_tipDlg->close();
	}
	
	int currId = -1;
	QListWidgetItem *item = ui.listWidget->selectedItems().at(0);
	panoramaItemWidget *ItemWidget = qobject_cast<panoramaItemWidget*> (ui.listWidget->itemWidget(item));
	if (ItemWidget)
	{
		PanoMapPointInfo_t info;
		ItemWidget->getItemData(info);
		currId = info.curr_id;

		if (m_addDlag)
		{
			m_addDlag->updateDeviceItem(current_map_.panoramaList);
		}
		if (info.onMapFlag)
		{
			ui.mapPage->removePanoDevice(info);
		}

		//一前一后删除了两次……
		MapPointListManagerIns.removeMapDevice(info.curr_id);

	}

	delete ui.listWidget->takeItem(ui.listWidget->currentRow());

	int index = -1;
	for (int i = 0; i < m_listWgtItemList.size(); ++i)
	{
		PanoMapPointInfo_t panoMapInfo;
		m_listWgtItemList[i]->getItemData(panoMapInfo);

		if (panoMapInfo.curr_id == currId)
		{
			index = i;
		}
	}

	if (index > -1)
	{
		m_listWgtItemList.removeAt(index);
	}
}

void VRMapWidget::slotOnUpdateMapData()
{
	current_map_ = MapPointListManagerIns.getMap();
	if (m_addDlag == NULL){
		m_addDlag = new commonAddDlg;
		connect(m_addDlag, SIGNAL(sigOnGetPanoramaList(QList<PanoMapPointInfo_t>)), this, SLOT(slotOnGetPanoramaList(QList<PanoMapPointInfo_t>)));
		m_addDlag->setTabName(QStringLiteral("全景机"), QStringLiteral("全景场景"));
		m_addDlag->setDlgTitleText(QStringLiteral("添加全景"));
		m_addDlag->setDlgType(ADDPANORAMA);
	}
	m_addDlag->updateDeviceItem(current_map_.panoramaList);
	slotOnGetPanoramaList(current_map_.panoramaList);


}

void VRMapWidget::slotOnResizeControlMap()
{
	if (is_map_load_)
	{
		QPixmap map(current_filePath_);
		ui.mapPage->setAutoFillBackground(true);
		QPalette palette;
		QSize temp;
		palette.setBrush(ui.mapPage->backgroundRole(), QBrush(map.scaled(ui.mapPage->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
		ui.mapPage->setPalette(palette);
		ui.mapPage->reSizeScreen();
	}
}

void VRMapWidget::slotOnModifyState(int id)
{
	for (int i = 0; i < m_listWgtItemList.size(); ++i)
	{
		m_listWgtItemList[i]->removeId(id);
	}
}

void VRMapWidget::init()
{
	ui.leftWidget->setVisible(false);
	ui.stackedWidget->setCurrentWidget(ui.initPage);
}

void VRMapWidget::initConnect()
{
	connect(ui.addPanoramaBtn, SIGNAL(clicked()), this, SLOT(slotOnAddPanoramaBtnClicked()));

	connect(ui.addMapBtn, SIGNAL(clicked()), this, SLOT(slotOnAddMapBtnClicked()));

	connect(ui.mapPage, SIGNAL(sigOnAddMapBtnClicked()), this, SLOT(slotOnAddMapBtnClicked()));
	connect(ui.mapPage, SIGNAL(sigOnRemoveOnMapDevice(PanoMapPointInfo_t)), SLOT(slotOnRemoveOnMapDevice(PanoMapPointInfo_t)));

	connect(ui.mapPage, SIGNAL(sigOnModifyState(int)), this, SLOT(slotOnModifyState(int)));
	connect(ViewSignal::instance(), SIGNAL(sigOnDistributeList(const QList<deviceInfo>)), this, SLOT(slotOnGetDeviceList(const QList<deviceInfo>)));

	connect(ui.listWidget, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(slotItemSelected(QListWidgetItem*, QListWidgetItem*)));

	connect(ViewSignal::instance(), SIGNAL(sigOnResizeMap()), this, SLOT(slotOnResizeControlMap()));

	connect(ViewSignal::instance(), SIGNAL(sigOnUpdateMapData()), this, SLOT(slotOnUpdateMapData()));

}
