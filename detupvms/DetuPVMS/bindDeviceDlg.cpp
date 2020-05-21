#include "bindDeviceDlg.h"
#include "APIProtocol.h"
#include "dmconnection.hpp"
#include "SocketManager.h"
#include "socketRequest.h"
#include "TcpDataManager.hpp"
#include "feedback.h"
#include "FramelessHelper.h"

#include "ptzSettingPointDlg.h"
#include "gunCamSettingDig.h"

bindDeviceDlg::bindDeviceDlg(QWidget *parent)
: QDialog(parent)
, m_XPos(-1)
, m_YPos(-1)
, m_Width(-1)
, m_Height(-1)
, m_addDeviceDlg(NULL)
, tipDlg_(NULL)
, ptz_set_point_dlg_(NULL)
, spy_set_point_dlg_(NULL)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
	setModal(true);

	FramelessHelper *helper = new FramelessHelper;
	helper->activateOn(this);
	helper->setDbClickOn(false);
	helper->setWidgetResizable(false);
	ui.label_4->setVisible(false);
	ui.clearButton->setVisible(false);
	initConnect();
}

bindDeviceDlg::~bindDeviceDlg()
{

}

void bindDeviceDlg::setParentPos(int x, int y, int width, int height)
{
	m_XPos = x;
	m_YPos = y;
	m_Width = width;
	m_Height = height;
}

void bindDeviceDlg::slotOnAddDevice()
{
	if (m_addDeviceDlg == NULL)
	{
		m_addDeviceDlg = new addDeviceDlg;
		connect(m_addDeviceDlg, SIGNAL(sigOnBindPtz(QString, int, QString, QString, int)), this, SIGNAL(sigOnBindPtz(QString, int, QString, QString, int)));
	}
	m_addDeviceDlg->clearData();
	if (ui.ptzBtn->isChecked())
	{
		m_addDeviceDlg->setTitleLabel(QStringLiteral("添加球机"));
		m_addDeviceDlg->setType(DEVICE_PTZ);
		m_addDeviceDlg->initPTZList(m_ptzInfoList);
	}
	else
	{
		m_addDeviceDlg->setTitleLabel(QStringLiteral("添加枪机"));
		m_addDeviceDlg->setType(DEVICE_SPY);
		m_addDeviceDlg->initSPYList(m_spyInfoList);
	}
 	int nX = (m_Width - m_addDeviceDlg->width()) / 2 + m_XPos;
 	int nY = (m_Height - m_addDeviceDlg->height()) / 2 + m_YPos;
	m_addDeviceDlg->move(nX, nY);
	m_addDeviceDlg->exec();
}

void bindDeviceDlg::slotOnClickedSPY(bool checked)
{
	if (checked)
	{
		ui.widget->setVisible(true);
		ui.label_4->setVisible(false);
		ui.clearButton->setVisible(false);
		ui.listWidget->clear();
		ui.addBtn->setText(QStringLiteral("+ 添加枪机"));
		socketRequest::instance()->requestOnGetBindDeviceList(DEVICE_SPY);
	}
}

void bindDeviceDlg::slotOnClickedPTZ(bool checked)
{
	if (checked)
	{
		ui.widget->setVisible(true);
		ui.label_4->setVisible(false);
		ui.clearButton->setVisible(false);
		ui.listWidget->clear();
		ui.addBtn->setText(QStringLiteral("+ 添加球机"));
		socketRequest::instance()->requestOnGetBindDeviceList(DEVICE_PTZ);
	}
}

void bindDeviceDlg::slotOnClickedHOT(bool checked)
{
	if (checked)
	{
		ui.widget->setVisible(false);
		ui.label_4->setVisible(true);
		ui.clearButton->setVisible(true);
	}
}


void bindDeviceDlg::slotOnClickedHOTConfirm()
{
	if (ui.hotBtn->isChecked())
	{
		if (spy_set_point_dlg_ == NULL)
		{
			spy_set_point_dlg_ = new gunCamSettingDig;
		}

		spy_set_point_dlg_->setTitleText("设置热点图片");
		spy_set_point_dlg_->raise();
		spy_set_point_dlg_->activateWindow();
		spy_set_point_dlg_->show();
		spy_set_point_dlg_->showHotPic();
	}
}

void bindDeviceDlg::slotOnClearButton()
{
	QFile pic_list(QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/Map/hotPic/list.txt"));
	pic_list.remove();
}

void bindDeviceDlg::slotOnSettings(PtzInfo pInfo, SpyInfo sInfo)
{
	this->close();
	if (ui.ptzBtn->isChecked())
	{
		if (ptz_set_point_dlg_ == NULL)
		{
			ptz_set_point_dlg_ = new ptzSettingPointDlg;
		}
		//socketRequest::instance()->requestOnGetPTZPoint(pInfo.sIP);
		if (m_curr_info.m1DeviceId == "default")
		{
			pInfo.m1Id = m_curr_info.serialNo;
		}
		else
		{
			pInfo.m1Id = m_curr_info.m1DeviceId;
		}
		pInfo.pvsID = m_curr_info.serialNo;
		ptz_set_point_dlg_->setTitleText(pInfo);
		ptz_set_point_dlg_->raise();
		ptz_set_point_dlg_->activateWindow();
		QPoint point = this->mapToGlobal(this->pos());
		int x = point.x();
		int y = point.y();
		int xx = this->width();
		int yy = ptz_set_point_dlg_->width();
		int nX = (this->width() - ptz_set_point_dlg_->width() + x) / 2;
		int nY = (this->height() - ptz_set_point_dlg_->height() + y) / 2;
		ptz_set_point_dlg_->move(nX, nY);
		ptz_set_point_dlg_->setPosSet(nX, nY);
		ptz_set_point_dlg_->show();
	}
	else if (ui.spyBtn->isChecked())
	{
		if (spy_set_point_dlg_ == NULL)
		{
			spy_set_point_dlg_ = new gunCamSettingDig;
		}

		if (m_curr_info.m1DeviceId == "default")
		{
			sInfo.m1Id = m_curr_info.serialNo;
		}
		else
		{
			sInfo.m1Id = m_curr_info.m1DeviceId;
		}

		spy_set_point_dlg_->setTitleText(sInfo);
		spy_set_point_dlg_->raise();
		spy_set_point_dlg_->activateWindow();
		spy_set_point_dlg_->show();
		spy_set_point_dlg_->showGunCam();

	}
}

void bindDeviceDlg::slotOnUnbind(PtzInfo pInfo, SpyInfo sInfo)
{
	if (tipDlg_ == NULL)
	{
		tipDlg_ = new commonTipDlg;
		connect(tipDlg_, SIGNAL(sigOnConfirm()), this, SLOT(slotOnConfirmUnbind()));
	}
	tipDlg_->setTitleLabelText(QStringLiteral("解绑设备"));
	if (ui.ptzBtn->isChecked())
	{
		m_curr_ptzInfo = pInfo;
		tipDlg_->setTipText(QStringLiteral("确定要解除全景相机M1（%1）与球机（%2）的绑定吗？").arg(pInfo.pvsID).arg(pInfo.sIP));
	}
	else
	{
		m_curr_spyInfo = sInfo;
		tipDlg_->setTipText(QStringLiteral("确定要解除全景相机M1（%1）与枪机（%2）的绑定吗？").arg(sInfo.pvsID).arg(sInfo.sIP));
	}
	tipDlg_->raise();
	tipDlg_->activateWindow();
	QPoint point = this->mapToGlobal(this->pos());
	int x = point.x();
	int y = point.y();
	int xx = this->width();
	int yy = tipDlg_->width();
	int nX = (this->width() - tipDlg_->width() + x) / 2;
	int nY = (this->height() - tipDlg_->height() + y) / 2;
	tipDlg_->move(nX, nY);
	tipDlg_->exec();
}

void bindDeviceDlg::slotOnItemClicked(QListWidgetItem *item)
{
	addItemWidget *itemWidget = qobject_cast<addItemWidget*>(ui.listWidget->itemWidget(item));
	if (itemWidget)
	{
		itemWidget->getPtzData(m_curr_ptzInfo);
		itemWidget->getSpyData(m_curr_spyInfo);
	}
}

void bindDeviceDlg::slotOnRegisterPTZRes(bool is_ok, unsigned char streamId)
{
	if (m_addDeviceDlg != NULL)
	{
		m_addDeviceDlg->close();
	}
	if (is_ok)
	{
		Feedback::instance()->maskUI(PTZ_BIND_SUCCESS);
		if (streamId == 0)
		{
			Log::Info("bind ptz device success!");
		}
		else if (streamId == 1)
		{
			Log::Info("unbind ptz device success!");
		}
	}
	else
	{
		Feedback::instance()->maskUI(PTZ_BIND_FAILED);
	}
}

void bindDeviceDlg::slotOnRegisterSPYRes(bool is_ok, unsigned char streamId)
{
	if (m_addDeviceDlg != NULL)
	{
		m_addDeviceDlg->close();
	}
	if (is_ok)
	{
		Feedback::instance()->maskUI(SPY_BIND_SUCCESS);
		this->close();
	}
	else
	{
		Feedback::instance()->maskUI(SPY_BIND_FAILED);
	}
}

void bindDeviceDlg::slotOnConfirmUnbind()
{
	if (tipDlg_ != NULL)
	{
		tipDlg_->close();
	}
	if (ui.ptzBtn->isChecked())
	{
		socketRequest::instance()->requestOnUnbindPTZDevice(m_curr_ptzInfo);
	}
	else
	{
		socketRequest::instance()->requestOnUnbindSPYDevice(m_curr_spyInfo);
	}
}

void bindDeviceDlg::initConnect()
{
	connect(ui.cancelBtn, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.addBtn, SIGNAL(clicked()), this, SLOT(slotOnAddDevice()));
	connect(ui.spyBtn, SIGNAL(clicked(bool)), this, SLOT(slotOnClickedSPY(bool)));
	connect(ui.ptzBtn, SIGNAL(clicked(bool)), this, SLOT(slotOnClickedPTZ(bool)));
	connect(ui.hotBtn, SIGNAL(clicked(bool)), this, SLOT(slotOnClickedHOT(bool)));

	connect(ui.confirmBtn, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.confirmBtn, SIGNAL(clicked()), this, SLOT(slotOnClickedHOTConfirm()));
	
	connect(ui.clearButton, SIGNAL(clicked()), this, SLOT(slotOnClearButton()));

	connect(ui.listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotOnItemClicked(QListWidgetItem*)));
	connect(&TcpDataManagerIns, SIGNAL(sigOnRegisterPTZRes(bool, unsigned char)), this, SLOT(slotOnRegisterPTZRes(bool, unsigned char)));
	connect(&TcpDataManagerIns, SIGNAL(sigOnRegisterSPYRes(bool, unsigned char)), this, SLOT(slotOnRegisterSPYRes(bool, unsigned char)));
}

void bindDeviceDlg::init(const deviceInfo &info)
{
	m_curr_info = info;
	ui.ptzBtn->setChecked(true);
	ui.widget->setVisible(true);
	ui.label_4->setVisible(false);
	ui.clearButton->setVisible(false);
	ui.addBtn->setText(QStringLiteral("+ 添加球机"));
	socketRequest::instance()->requestOnGetBindDeviceList(DEVICE_PTZ);

}

void bindDeviceDlg::slotOnInitPtzData(QList<PtzInfo> ptzInfoList)
{
	if (ui.ptzBtn->isChecked())
	{
		ui.listWidget->clear();
		for (int i = 0; i < ptzInfoList.size(); ++i)
		{
			addItemWidget *itemWidget = new addItemWidget;
			qRegisterMetaType<PtzInfo >("PtzInfo");
			qRegisterMetaType<SpyInfo >("SpyInfo");
			connect(itemWidget, SIGNAL(sigOnSettings(PtzInfo, SpyInfo)), this, SLOT(slotOnSettings(PtzInfo, SpyInfo)));
			connect(itemWidget, SIGNAL(sigOnUnbind(PtzInfo, SpyInfo)), this, SLOT(slotOnUnbind(PtzInfo, SpyInfo)));
			itemWidget->initPtzData(ptzInfoList[i]);
			QListWidgetItem *item = new QListWidgetItem;
			item->setSizeHint(QSize(200, 30));
			ui.listWidget->insertItem(i, item);
			ui.listWidget->setItemWidget(item, itemWidget);
		}
	}
}

void bindDeviceDlg::slotOnInitSpyData(QList<SpyInfo> spyInfoList)
{
	if (ui.spyBtn->isChecked())
	{
		ui.listWidget->clear();
		for (int i = 0; i < spyInfoList.size(); ++i)
		{
			addItemWidget *itemWidget = new addItemWidget;
			qRegisterMetaType<PtzInfo >("PtzInfo");
			qRegisterMetaType<SpyInfo >("SpyInfo");
			connect(itemWidget, SIGNAL(sigOnSettings(PtzInfo, SpyInfo)), this, SLOT(slotOnSettings(PtzInfo, SpyInfo)));
			connect(itemWidget, SIGNAL(sigOnUnbind(PtzInfo, SpyInfo)), this, SLOT(slotOnUnbind(PtzInfo, SpyInfo)));
			itemWidget->initSpyData(spyInfoList[i]);
			QListWidgetItem *item = new QListWidgetItem;
			item->setSizeHint(QSize(200, 30));
			ui.listWidget->insertItem(i, item);
			ui.listWidget->setItemWidget(item, itemWidget);
		}
	}
}

void bindDeviceDlg::slotOnInitPtzList(QList<PtzInfo> ptzInfoList)
{
	m_ptzInfoList = ptzInfoList;
}

void bindDeviceDlg::slotOnInitSpyList(QList<SpyInfo> spyInfoList)
{
	m_spyInfoList = spyInfoList;
}
