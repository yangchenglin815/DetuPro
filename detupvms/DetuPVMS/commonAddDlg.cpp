#include "commonAddDlg.h"
#include "feedback.h"
#include "FramelessHelper.h"
#include "constStruct.h"
#include "logging.hpp"
#include "ViewSignal.h"
#include "socketRequest.h"
#include <QTimer>

commonAddDlg::commonAddDlg(QWidget *parent)
: QDialog(parent)
, m_currDlg_type(-1)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	FramelessHelper *helper = new FramelessHelper;
	helper->activateOn(this);
	helper->setDbClickOn(false);
	helper->setWidgetResizable(false);

	ui.tab1->setChecked(true);
	ui.stackedWidget_2->setCurrentWidget(ui.deviceListPage);
	setAddPanoramaDlg();
	initConnect();
}

commonAddDlg::~commonAddDlg()
{

}

void commonAddDlg::setDlgTitleText(QString text)
{
	ui.titleLabel->setText(text);
}

void commonAddDlg::setTabName(QString tabName_1, QString tabName_2)
{
	ui.tab1->setText(tabName_1);
	ui.tab2->setText(tabName_2);
}

void commonAddDlg::setDlgType(int type)
{
	m_currDlg_type = type;

	switch (m_currDlg_type)
	{
	case ADDPANORAMA:
		setAddPanoramaDlg();
		break;
	default:
		break;
	}
}


void commonAddDlg::initDeviceList(QList<deviceInfo> deviceList, QList<PanoSceneInfo> panoSceneList)
{
	m_deviceList = deviceList;
	m_panoSceneList = panoSceneList;

	initTab1Page();
	initTab2Page();
}

void commonAddDlg::updateDeviceItem(QList<PanoMapPointInfo> panoInfoList)
{
	m_panoramaList = panoInfoList;
}

void commonAddDlg::removeOnMapItem(PanoMapPointInfo panoInfo)
{
	int index = -1;
	for (int i = 0; i < m_onMap_panoramaList.size(); ++i)
	{
		if (m_onMap_panoramaList[i].curr_id == panoInfo.curr_id)
		{
			index = i;
		}
	}

	if (index > -1)
	{
		m_onMap_panoramaList.removeAt(index);
	}
}

void commonAddDlg::initTab1Page()
{
	m_listWgt->clear();
	panoCameraItemList.clear();
	int num = 0;
	for (int i = 0; i < m_deviceList.size(); ++i)
	{
		VRMapAddDlgListWgt *itemWidget = new VRMapAddDlgListWgt;
		panoCameraItemList.append(itemWidget);
		itemWidget->initAddPanoramaCamera(m_deviceList[i]);
		for (int j = 0; j < m_panoramaList.size(); ++j)
		{
			if (m_panoramaList[j].map_point_type == DEVICE_ON_LINE && m_deviceList[i].serialNo == m_panoramaList[j].cameraInfo.serialNo)
			{
				itemWidget->setItemChecked(true);
				num++;
			}
		}

		QListWidgetItem *item = new QListWidgetItem;
		item->setSizeHint(QSize(320, 30));
		m_listWgt->insertItem(i, item);
		m_listWgt->setItemWidget(item, itemWidget);
	}

	if (m_listWgt->count() == num)
	{
		m_addDlgTiltWgt->setCheckBoxChecked(Qt::Checked);
	}
	else
	{
		m_addDlgTiltWgt->setCheckBoxChecked(Qt::Unchecked);
	}
}

void commonAddDlg::initTab2Page()
{
	m_sceneListWgt->clear();
	panoPictureItemList.clear();
	int num = 0;
	for (int i = 0; i < m_panoSceneList.size(); ++i)
	{
		VRMapAddDlgListWgt *itemWidget = new VRMapAddDlgListWgt;
		panoPictureItemList.append(itemWidget);
		itemWidget->initAddPanoramaScene(m_panoSceneList[i]);
		for (int j = 0; j < m_panoramaList.size(); ++j)
		{
			if (m_panoramaList[j].map_point_type == PANOSCENE_ON_LINE && m_panoSceneList[i].name == m_panoramaList[j].sceneInfo.name)
			{
				itemWidget->setItemChecked(true);
				num++;
			}
		}

		QListWidgetItem *item = new QListWidgetItem;
		item->setSizeHint(QSize(320, 50));
		m_sceneListWgt->insertItem(i, item);
		m_sceneListWgt->setItemWidget(item, itemWidget);
	}

	if (m_sceneListWgt->count() == num)
	{
		m_addSceneTitWgt->setCheckBoxChecked(Qt::Checked);
	}
	else
	{
		m_addSceneTitWgt->setCheckBoxChecked(Qt::Unchecked);
	}
}

void commonAddDlg::setAddPanoramaDlg()
{
	QVBoxLayout *vboxLayout = new QVBoxLayout(ui.deviceListPage);
	vboxLayout->setSpacing(0);
	vboxLayout->setContentsMargins(0, 0, 0, 0);
	m_addDlgTiltWgt = new VRMapAddDlgTitleWidget(ui.deviceListPage);
	m_addDlgTiltWgt->setMinimumSize(QSize(320, 30));
	m_addDlgTiltWgt->setMaximumSize(QSize(320, 30));
	vboxLayout->addWidget(m_addDlgTiltWgt);
	m_listWgt = new QListWidget(ui.deviceListPage);
	vboxLayout->addWidget(m_listWgt);
	m_listWgt->setFocusPolicy(Qt::NoFocus);
	m_listWgt->setSelectionMode(QAbstractItemView::MultiSelection);
	m_listWgt->setStyleSheet("border:1px solid #C3C9C9;outline:0px;");
	m_listWgt->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	m_addDlgTiltWgt->setTitleText(QStringLiteral("别名"), QStringLiteral("设备序列号"));
	connect(m_listWgt, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotOnItemClicked(QListWidgetItem*)));
	connect(m_addDlgTiltWgt, SIGNAL(stateChanged(int)), this, SLOT(slotOnStateChanged(int)));

	QVBoxLayout *vboxLayout1 = new QVBoxLayout(ui.sceneListPage);
	vboxLayout1->setSpacing(0);
	vboxLayout1->setContentsMargins(0, 0, 0, 0);
	m_addSceneTitWgt = new VRMapAddDlgTitleWidget(ui.sceneListPage);
	m_addSceneTitWgt->setMinimumSize(QSize(320, 30));
	m_addSceneTitWgt->setMaximumSize(QSize(320, 30));
	vboxLayout1->addWidget(m_addSceneTitWgt);
	m_sceneListWgt = new QListWidget(ui.sceneListPage);
	vboxLayout1->addWidget(m_sceneListWgt);
	m_sceneListWgt->setFocusPolicy(Qt::NoFocus);
	m_sceneListWgt->setSelectionMode(QAbstractItemView::MultiSelection);
	m_sceneListWgt->setStyleSheet("border:1px solid #C3C9C9;outline:0px;");
	m_sceneListWgt->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	m_addSceneTitWgt->setTitleText(QStringLiteral("别名"), QStringLiteral("全景图"));
	connect(m_sceneListWgt, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotOnSceneItemClicked(QListWidgetItem*)));
	connect(m_addSceneTitWgt, SIGNAL(stateChanged(int)), this, SLOT(slotOnStateSceneChanged(int)));
}


void commonAddDlg::savePanoramaCameraData()
{
	QList<QListWidgetItem*> itemWidgetList = m_listWgt->selectedItems();
	Log::Info("itemWidgetList selected camera num : %d", itemWidgetList.size());
	if (itemWidgetList.size() > 0)
	{
		for (int i = 0; i < itemWidgetList.size(); ++i)
		{
			int index = 0;
			VRMapAddDlgListWgt *itemWidget = qobject_cast<VRMapAddDlgListWgt*>(m_listWgt->itemWidget(itemWidgetList[i]));
			if (itemWidget)
			{
				deviceInfo info;
				itemWidget->getInfoBySelectedItem(info);

				for (int j = 0; j < m_panoramaList.size(); ++j)
				{
					{
						if (m_panoramaList[j].map_point_type == DEVICE_ON_LINE && info.serialNo == m_panoramaList[j].cameraInfo.serialNo)
						{
							index++;
						}
					}
				}
					if (!index){
						PanoMapPointInfo_t info_t;
						info_t.cameraInfo = info;
						info_t.map_point_type = DEVICE_ON_LINE;
						m_panoramaList.append(info_t);
					}
				}
			}
		}
	}

void commonAddDlg::savePanoramaPictureData()
{
	QList<QListWidgetItem*> itemWidgetList = m_sceneListWgt->selectedItems();
	Log::Info("itemWidgetList selected picture num : %d", itemWidgetList.size());
	if (itemWidgetList.size() > 0)
	{
		for (int i = 0; i < itemWidgetList.size(); ++i)
		{
			int index = 0;
			VRMapAddDlgListWgt *itemWidget = qobject_cast<VRMapAddDlgListWgt*>(m_sceneListWgt->itemWidget(itemWidgetList[i]));
			if (itemWidget)
			{
				PanoSceneInfo info;
				itemWidget->getSceneBySelectedItem(info);

				for (int j = 0; j < m_panoramaList.size(); ++j)
				{
					if (m_panoramaList[j].map_point_type == PANOSCENE_ON_LINE && info.name == m_panoramaList[j].sceneInfo.name)
					{
						index++;
					}
				}

				if (!index){
					PanoMapPointInfo_t info_t;
					info_t.sceneInfo = info;
					info_t.map_point_type = PANOSCENE_ON_LINE;
					m_panoramaList.append(info_t);
				}
			}
		}
	}
}

void commonAddDlg::slotOnTab1Clicked(bool checked)
{
	if (checked)
	{
		initTab1Page();
		ui.stackedWidget_2->setCurrentWidget(ui.deviceListPage);
	}
}

void commonAddDlg::slotOnTab2Clicked(bool checked)
{
	if (checked)
	{
		initTab2Page();
		ui.stackedWidget_2->setCurrentWidget(ui.sceneListPage);
	}
}

void commonAddDlg::slotOnConfirmClicked()
{
	if (ui.tab1->isChecked())
	{
		savePanoramaCameraData();
	}
	else if (ui.tab2->isChecked())
	{
		savePanoramaPictureData();
	}

	for (int i = 0; i < m_panoramaList.size(); ++i){
		PanoMapPointInfo panoInfo = m_panoramaList[i];
		for (int j = 0; j < m_onMap_panoramaList.size(); ++j)
		{
			PanoMapPointInfo onMapInfo = m_onMap_panoramaList[j];
			if (panoInfo.map_point_type == onMapInfo.map_point_type)
			{
				if (panoInfo.map_point_type == DEVICE_ON_LINE && panoInfo.cameraInfo.name == onMapInfo.cameraInfo.name && panoInfo.cameraInfo.name != "")
				{
					m_panoramaList[i].onMapFlag = true;
				}
				if (panoInfo.map_point_type == PANOSCENE_ON_LINE && panoInfo.sceneInfo.name == onMapInfo.sceneInfo.name && panoInfo.sceneInfo.name != "")
				{
					m_panoramaList[i].onMapFlag = true;
				}
			}
		}
	}
	emit sigOnGetPanoramaList(m_panoramaList);
	close();
}

void commonAddDlg::slotOnItemClicked(QListWidgetItem* item)
{
	VRMapAddDlgListWgt *itemWidget = qobject_cast<VRMapAddDlgListWgt*>(m_listWgt->itemWidget(item));
	if (itemWidget)
	{
		itemWidget->onItemSelected();
	}
}

void commonAddDlg::slotOnSceneItemClicked(QListWidgetItem* item)
{
	VRMapAddDlgListWgt *itemWidget = qobject_cast<VRMapAddDlgListWgt*>(m_sceneListWgt->itemWidget(item));
	if (itemWidget)
	{
		itemWidget->onItemSelected();
	}
}

void commonAddDlg::slotOnReportOnMapDevice(PanoMapPointInfo_t panoramaInfo)
{
	m_onMap_panoramaList.append(panoramaInfo);
}

void commonAddDlg::slotOnStateChanged(int checkState)
{
	for (int i = 0; i < panoCameraItemList.size(); ++i)
	{
		panoCameraItemList[i]->setItemChecked(checkState);
		deviceInfo info;
		panoCameraItemList[i]->getInfoBySelectedItem(info);
		int index = 0;
		for (int j = 0; j < m_panoramaList.size(); ++j)
		{
			{
				if (m_panoramaList[j].map_point_type == DEVICE_ON_LINE && info.serialNo == m_panoramaList[j].cameraInfo.serialNo)
				{
					index++;
				}
			}
		}
		if (!index && checkState){
			PanoMapPointInfo_t info_t;
			info_t.cameraInfo = info;
			info_t.map_point_type = DEVICE_ON_LINE;
			m_panoramaList.append(info_t);
		}
	}
}

void commonAddDlg::slotOnStateSceneChanged(int checkState)
{
	for (int i = 0; i < panoPictureItemList.size(); ++i)
	{
		panoPictureItemList[i]->setItemChecked(checkState);
		PanoSceneInfo info;
		panoPictureItemList[i]->getSceneBySelectedItem(info);
		int index = 0;
		for (int j = 0; j < m_panoramaList.size(); ++j)
		{
			if (m_panoramaList[j].map_point_type == PANOSCENE_ON_LINE && info.name == m_panoramaList[j].sceneInfo.name)
			{
				index++;
			}
		}

		if (!index && checkState){
			PanoMapPointInfo_t info_t;
			info_t.sceneInfo = info;
			info_t.map_point_type = PANOSCENE_ON_LINE;
			m_panoramaList.append(info_t);
		}
	}
}

void commonAddDlg::slotOnCancel()
{
	m_panoramaList.clear();
	close();
}

void commonAddDlg::initConnect()
{
	connect(ui.tab1, SIGNAL(clicked(bool)), this, SLOT(slotOnTab1Clicked(bool)));
	connect(ui.tab2, SIGNAL(clicked(bool)), this, SLOT(slotOnTab2Clicked(bool)));
	connect(ui.confirmBtn, SIGNAL(clicked()), this, SLOT(slotOnConfirmClicked()));
	connect(ui.cancelBtn, SIGNAL(clicked()), this, SLOT(slotOnCancel()));

	connect(ViewSignal::instance(), SIGNAL(sigOnReportOnMapDevice(PanoMapPointInfo_t)), this, SLOT(slotOnReportOnMapDevice(PanoMapPointInfo_t)));
}

void commonAddDlg::initData(int type)
{
	switch (type)
	{
	case 0:
		slotOnTab1Clicked(true);
		break;
	case 1:
		slotOnTab2Clicked(true);
		break;
	default:
		break;
	}
}
