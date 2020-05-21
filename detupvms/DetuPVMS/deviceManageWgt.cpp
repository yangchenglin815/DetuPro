#include <QMessageBox>
#include <QDir>
#include <QTimer>

#include "ptzSettingPointDlg.h"
#include "gunCamSettingDig.h"

#include "deviceManageWgt.h"
#include "TcpDataManager.hpp"
#include "logging.hpp"
#include "dmconnection.hpp"
#include "SocketManager.h"
#include "DetuPVMSIni.h"
#include "feedback.h"
#include "socketRequest.h"
#include "ViewSignal.h"
#include "MapPointListManager.h"

#include <QDebug>

Q_DECLARE_METATYPE(std::vector<PTZManageTable_t>)
Q_DECLARE_METATYPE(std::vector<SPYManageTable_t>)

deviceManageWgt::deviceManageWgt(QWidget *parent)
: QWidget(parent)
, m_selectId(-1)
, setupDlg_(NULL)
, ptzDlg_(NULL)
, nvr_list_(NULL)
, disk_list_(NULL)
, tipDlg_(NULL)
, qrDlg_(NULL)
, buttonGroup_(NULL)
, m_bindDeviceDlg(NULL)
, m_PtzPointSettingDlg(NULL)
, m_SpyPointSettingDlg(NULL)
, curr_selectID_(-1)
, curr_delete_device_type_(-1)
, m_pushFlowSettingsDlg(NULL)
{
	ui.setupUi(this);
	init();
	initConnect();
}

deviceManageWgt::~deviceManageWgt()
{
	if (nvr_list_ != NULL)
	{
		delete(nvr_list_);
		nvr_list_ = NULL;
	}
	if (disk_list_ != NULL)
	{
		delete(disk_list_);
		disk_list_ = NULL;
	}
}



/*************************************************
函数名:    	initPtzData
函数描述:	初始化球机列表
输入参数:    
输出参数:
返回值:
**************************************************/
void deviceManageWgt::slotOnInitPtzData(QList<PtzInfo> ptzInfoList)
{
	ui.ptzListView->clearItems();
	int count = ptzInfoList.length();
	for (int i = 0; i < count; i++)
	{
		ptzInfoList[i].id = i + 1;
		ui.ptzListView->appendItem(ptzInfoList[i]);
	}
}

/*************************************************
函数名:    	initSpyData
函数描述:	初始化枪机列表
输入参数:
输出参数:
返回值:
**************************************************/
void deviceManageWgt::slotOnInitSpyData(QList<SpyInfo> spyInfoList)
{
	ui.spyListView->clearItems();
	int count = spyInfoList.length();
	for (int i = 0; i < count; i++)
	{
		spyInfoList[i].id = i + 1;
		ui.spyListView->appendItem(spyInfoList[i]);
	}
}

void deviceManageWgt::getSelectId(int selectId)
{
	m_selectId = selectId;
}

void deviceManageWgt::slotOnSetup(deviceInfo info)
{
	if (setupDlg_ == NULL)
	{
		setupDlg_ = new deviceSettingDlg;
		connect(setupDlg_, SIGNAL(sigOnSave(deviceInfo)), this, SLOT(slotOnSave(deviceInfo)));
		connect(setupDlg_, SIGNAL(sigOnSetAutoCircle(bool, QString)), this, SLOT(slotOnSetAutoCircle(bool, QString)));
	}
	DetuPVMSIni::setGlobalSettingGet(true);
	setupDlg_->initData(info);
	setupDlg_->initDirection(info.is_up_down);
	setupDlg_->activateWindow();
	setupDlg_->show();
	QPoint point = this->mapToGlobal(this->pos());
	int x = point.x();
	int y = point.y();
	int xx = this->width();
	int yy = setupDlg_->width();
	int nX = (this->width() - setupDlg_->width()) / 2 + x;
	int nY = (this->height() - setupDlg_->height()) / 2 + y;
	setupDlg_->move(nX, nY);

}

void deviceManageWgt::setServerOnline(bool online)
{
	for (int i = 0; i < m_InfoList.length(); i++)
	{
		if (online)
		{
			m_InfoList[i].status = 1;
		}
		else
		{
			m_InfoList[i].status = 0;
			m_InfoList[i].bClicked = false;
			m_InfoList[i].RbClicked = false;
		}
	}
	for (int i = 0; i < m_InfoList.length(); i++)
	{
		m_InfoList[i].id = i + 1;
		if (m_InfoList[i].id == m_InfoList.length())
		{
			m_InfoList[i].isFinal = true;
		}
		else
		{
			m_InfoList[i].isFinal = false;
		}
	}
	emit sigOnInitData(m_InfoList);
	//分发列表
	emit sigOnDistributeList(m_InfoList);
}

/*************************************************
函数名:    	ptzRegister
函数描述:	球机注册函数
输入参数:
输出参数:
返回值:
**************************************************/
void deviceManageWgt::ptzRegister(QString Ip, int port, QString user, QString passwd)
{
	protocol_head_t api_head;
	PTZManageTable_t api_detu;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_PTZ_REGISTER;
	api_head.nDataLen = api_detu.get_size();
	api_head.nResult = 0x00;
	api_head.nStreamId = 0;
	//api_head.nReserver = 0x01;        //预留位
	api_head.nEndFlags = 0xFA;

	if (curr_selectID_ > 0)
	{
		QString deviceID = m_InfoList[curr_selectID_ - 1].serialNo;
		memcpy(api_detu.pvsID, deviceID.toLocal8Bit().data(), API_ARRAY_LEN);
		memcpy(api_detu.nIP, Ip.toLocal8Bit().data(), API_ARRAY_LEN);
		api_detu.nPort = port;
		memcpy(api_detu.username, user.toLocal8Bit().data(), API_ARRAY_LEN);
		memcpy(api_detu.passwd, passwd.toLocal8Bit().data(), API_ARRAY_LEN);

		response res(api_head.get_size() + api_detu.get_size());
		response_add_resprotocol<protocol_head_t>(res, &api_head);
		response_add_resprotocol<PTZManageTable_t>(res, &api_detu);

		dmconnection* conn = SocketManagerIns.GetCommSocket();
		if (conn != NULL)
		{
			conn->do_write(res);
		}
	}
}

/*************************************************
函数名:    	spyRegister
函数描述:	枪机注册函数
输入参数:
输出参数:
返回值:
**************************************************/
void deviceManageWgt::spyRegister(QString Ip, int port, QString user, QString passwd)
{
	protocol_head_t api_head;
	SPYManageTable_t api_detu;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_SPY_REGISTER;
	api_head.nDataLen = api_detu.get_size();
	api_head.nResult = 0x00;
	api_head.nStreamId = 0;
	//api_head.nReserver = 0x01;        //预留位
	api_head.nEndFlags = 0xFA;

	if (curr_selectID_ > 0)
	{
		QString deviceID = m_InfoList[curr_selectID_ - 1].serialNo;
		memcpy(api_detu.pvsID, deviceID.toLocal8Bit().data(), API_ARRAY_LEN);
		memcpy(api_detu.nIP, Ip.toLocal8Bit().data(), API_ARRAY_LEN);
		api_detu.nPort = port;
		memcpy(api_detu.username, user.toLocal8Bit().data(), API_ARRAY_LEN);
		memcpy(api_detu.passwd, passwd.toLocal8Bit().data(), API_ARRAY_LEN);

		response res(api_head.get_size() + api_detu.get_size());
		response_add_resprotocol<protocol_head_t>(res, &api_head);
		response_add_resprotocol<SPYManageTable_t>(res, &api_detu);

		dmconnection* conn = SocketManagerIns.GetCommSocket();
		if (conn != NULL)
		{
			conn->do_write(res);
		}
	}
}



void deviceManageWgt::slotOnDownMove(deviceInfo info)
{
	if (info.id != m_InfoList.length())
	{
		m_InfoList.swap(info.id - 1,  info.id);
		for (int i = 0; i < m_InfoList.length(); i++)
		{
			m_InfoList[i].id = i + 1;
			if (m_InfoList[i].id == m_InfoList.length())
			{
				m_InfoList[i].isFinal = true;
			}
			else
			{
				m_InfoList[i].isFinal = false;
			}
		}
		emit sigOnInitData(m_InfoList);
		//分发列表
		emit sigOnDistributeList(m_InfoList);
	}
}

void deviceManageWgt::slotOnUpMove(deviceInfo info)
{
	if (info.id != 1)
	{
		m_InfoList.swap(info.id - 1, info.id - 2);
		for (int i = 0; i < m_InfoList.length(); i++)
		{
			m_InfoList[i].id = i + 1;
			if (m_InfoList[i].id == m_InfoList.length())
			{
				m_InfoList[i].isFinal = true;
			}
			else
			{
				m_InfoList[i].isFinal = false;
			}
		}
		emit sigOnInitData(m_InfoList);
		//分发列表
		emit sigOnDistributeList(m_InfoList);
	}
}

void deviceManageWgt::slotOnGetDeviceList()
{
	if (get_device_list_thread_ && get_device_list_thread_->joinable())
	{
		get_device_list_thread_->join();
	}
	get_device_list_thread_.reset(new boost::thread(&deviceManageWgt::getDeviceListThread, this));
}

void deviceManageWgt::getDeviceListThread()
{
	locker.lock();
	nvr_list_ = TcpDataManagerIns.GetList();
	Log::Debug("nvrlist num:%d", nvr_list_->numlist);
	deviceInfo *info = NULL;

	if (m_InfoList.size() > 0)
	{
		QList<int> filterList;    //过滤器列表
		//过滤掉客户端中服务器已经离线的nvr设备信息
		for (int i = 0; i < m_InfoList.size(); i++)
		{
			QString device = m_InfoList.at(i).serialNo;
			int num = 0;
			for (int j = 0; j < nvr_list_->numlist; j++)
			{
				QString devicename((char*)(nvr_list_->nvrList[i].szDeviceId));
				if (devicename == device)
				{
					num++;
				}
			}
			if (num == 0)
			{
				filterList.append(m_InfoList.at(i).id);
			}
		}

		//启动过滤器
		for (int k = 0; k < filterList.size(); k++)
		{
			int filterId = filterList.at(k);
			for (int m = 0; m < m_InfoList.size(); m++)
			{
				if (m_InfoList.at(m).id == filterId)
				{
					m_InfoList.removeAt(m);
				}
			}
		}

		//更新数据
		for (int i = 0; i < nvr_list_->numlist; i++)
		{
			QString devicename((char*)(nvr_list_->nvrList[i].szDeviceId));
			QString M1Id((char*)nvr_list_->nvrList[i].m1DeviceId);
			QString name = QString::fromLocal8Bit((char*)(nvr_list_->nvrList[i].szName));
			int direction = nvr_list_->nvrList[i].szUpDown;
			QString ip((char*)(nvr_list_->nvrList[i].ptz.nIP));
			int port = nvr_list_->nvrList[i].ptz.nPort;
			int online = nvr_list_->nvrList[i].online;
			QString user((char*)(nvr_list_->nvrList[i].ptz.nUser));
			QString passwd((char*)(nvr_list_->nvrList[i].ptz.nPasswd));
			Log::Debug("Update get device:[%d] %s", i + 1, devicename.toLocal8Bit().data());
			info = new deviceInfo;
			int num = 0;
			for (int j = 0; j < m_InfoList.size(); j++)
			{
				if (devicename == m_InfoList.at(j).serialNo)
				{
					num++;
					//更新设备列表
					updateData(j, name, devicename, direction, port, user, passwd, M1Id, online);
				}
			}
			if (num == 0)
			{
				//添加服务端的新nvr设备信息
				updateData(info, name, devicename, direction, ip, port, user, passwd, M1Id, online);
			}
		}
	}
	else
	{
		//初始化数据
		for (int i = 0; i < nvr_list_->numlist; i++)
		{
			QString devicename((char*)(nvr_list_->nvrList[i].szDeviceId));
			QString M1Id((char*)nvr_list_->nvrList[i].m1DeviceId);
			QString name = QString::fromLocal8Bit((char*)(nvr_list_->nvrList[i].szName));
			int direction = nvr_list_->nvrList[i].szUpDown;
			int online = nvr_list_->nvrList[i].online;
			QString ip((char*)(nvr_list_->nvrList[i].ptz.nIP));
			int port = nvr_list_->nvrList[i].ptz.nPort;
			QString user((char*)(nvr_list_->nvrList[i].ptz.nUser));
			QString passwd((char*)(nvr_list_->nvrList[i].ptz.nPasswd));
			Log::Debug("Register get device:[%d] %s", i + 1, devicename.toLocal8Bit().data());

			info = new deviceInfo;
			updateData(info, name, devicename, direction, ip, port, user, passwd, M1Id, online);
		}
	}	
	for (int i = 0; i < m_InfoList.length(); i++)
	{
		m_InfoList[i].id = i + 1;
		if (m_InfoList[i].id == m_InfoList.length())
		{
			m_InfoList[i].isFinal = true;
		}
		else
		{
			m_InfoList[i].isFinal = false;
		}
	}
	emit sigOnInitData(m_InfoList);
	//分发列表
	emit sigOnDistributeList(m_InfoList);
	ViewSignal::instance()->sigOnDistributeList(m_InfoList);
		//
	if (SocketManagerIns.isConnected()){
	    getDiskSize();
		socketRequest::instance()->requestOnGetBindDeviceList(DEVICE_PTZ);
		socketRequest::instance()->requestOnGetBindDeviceList(DEVICE_SPY);
	}
	ui.toolButton->setEnabled(true);
	locker.unlock();
}




void deviceManageWgt::slotOnSave(deviceInfo info)
{
	m_InfoList[info.id - 1].name = info.name;
	m_InfoList[info.id - 1].is_up_down = info.is_up_down;
	for (int i = 0; i < m_InfoList.length(); i++)
	{
		m_InfoList[i].id = i + 1;
		if (m_InfoList[i].id == m_InfoList.length())
		{
			m_InfoList[i].isFinal = true;
		}
		else
		{
			m_InfoList[i].isFinal = false;
		}
	}
	emit sigOnInitData(m_InfoList);
	//分发列表
	emit sigOnDistributeList(m_InfoList);
	if (setupDlg_ != NULL)
	{
		setupDlg_->close();
		DetuPVMSIni::setGlobalSettingGet(false);
	}
}

void deviceManageWgt::slotOnGetDiskSize()
{
	if (get_device_size_thread_ && get_device_size_thread_->joinable())
	{
		get_device_size_thread_->join();
	}
	get_device_size_thread_.reset(new boost::thread(&deviceManageWgt::getDeviceSizeThread, this));
}

void deviceManageWgt::getDeviceSizeThread()
{
	locker.lock();
	std::vector<api_detu_client_disk_size_t> list_t = TcpDataManagerIns.GetDiskSizeList();
	TcpDataManagerIns.clearData();
	DiskSizeInfo_t disk_info;
	int k = 0;
	if (list_t.size() > 0){
		//首先清空该nvr的存储容量信息
		for (std::vector<api_detu_client_disk_size_t>::iterator iter = list_t.begin(); iter != list_t.end(); iter++)
		{
			for (int j = 0; j < m_InfoList.size(); j++)
			{
				if (m_InfoList[j].serialNo == QString((char*)iter->szDeviceId))
				{
					m_InfoList[j].disk_info_list.clear();
					m_InfoList[j].usedRoom = 0;
					m_InfoList[j].usingRoom = 0;
					Log::Debug("getDiskInfo:  device:%s, diskNum:%d, curNo:%d, TotalRoom:%d, usedRoom:%d", m_InfoList[j].serialNo.toLocal8Bit().data(), iter->nTotalDiskNum, iter->nCurDiskNum, iter->nTotalDiskSize, iter->nUsedSize);
				}
			}
		}
		//处理更新存储容量信息
		for (std::vector<api_detu_client_disk_size_t>::iterator iter = list_t.begin(); iter != list_t.end(); iter++)
		{
			for (int j = 0; j < m_InfoList.size(); j++)
			{
				if (m_InfoList[j].serialNo == QString((char*)iter->szDeviceId))
				{
					m_InfoList[j].usedRoom += iter->nUsedSize;
					m_InfoList[j].usingRoom += iter->nTotalDiskSize;
					m_InfoList[j].diskNum = iter->nTotalDiskNum;

					disk_info.nCurDiskNum = iter->nCurDiskNum;
					disk_info.nDiskId = iter->nDiskId;
					disk_info.nDiskStatus = iter->nDiskStatus;
					disk_info.nDiskType = iter->nDiskType;
					disk_info.nTotalDiskNum = iter->nTotalDiskNum;
					disk_info.nTotalDiskSize = iter->nTotalDiskSize;
					disk_info.nUsedSize = iter->nUsedSize;
					memcpy(disk_info.szDeviceId, iter->szDeviceId, API_ARRAY_LEN);
					m_InfoList[j].disk_info_list.append(disk_info);
				}
			}
		}
		for (int i = 0; i < m_InfoList.length(); i++)
		{
			m_InfoList[i].id = i + 1;
			if (m_InfoList[i].id == m_InfoList.length())
			{
				m_InfoList[i].isFinal = true;
			}
			else
			{
				m_InfoList[i].isFinal = false;
			}
		}
		emit sigOnInitData(m_InfoList);
		//分发列表
		emit sigOnDistributeList(m_InfoList);
	}
	locker.unlock();
}


void deviceManageWgt::slotOnUpdate()
{
	if (SocketManagerIns.isConnected())
	{
		ui.toolButton->setEnabled(false);
		emit sigOnUpdate();
		QTimer::singleShot(3000, this, SLOT(slotOnUpdateStatus()));
	}
}

void deviceManageWgt::slotOnUpdateStatus()
{
	ui.toolButton->setEnabled(true);
}

void deviceManageWgt::slotOnSetAutoCircle(bool isAutoCircle, QString deviceId)
{
// 	for (int i = 0; i < m_InfoList.size(); i++)
// 		{
// 			if (m_InfoList.at(i).serialNo == deviceId)
// 			{
// 				//m_InfoList[i].isAutoCircle = isAutoCircle;
// 			}
// 		}
// 		//initData(m_InfoList);
	//分发列表
//	emit sigOnDistributeList(m_InfoList);
}

void deviceManageWgt::transportList(QList<deviceInfo> deviceList)
{
	m_InfoList = deviceList;
	for (int i = 0; i < m_InfoList.length(); i++)
	{
		m_InfoList[i].id = i + 1;
		if (m_InfoList[i].id == m_InfoList.length())
		{
			m_InfoList[i].isFinal = true;
		}
		else
		{
			m_InfoList[i].isFinal = false;
		}
	}
	emit sigOnInitData(m_InfoList);
	//分发列表
	emit sigOnDistributeList(m_InfoList);
}

void deviceManageWgt::resetToolBtn()
{
	ui.toolButton->setEnabled(true);
}

/*************************************************
函数名:    	slotOnBindPTZClicked
函数描述:	绑定球机按钮响应槽函数
输入参数:
输出参数:
返回值:
**************************************************/
void deviceManageWgt::slotOnBindPTZClicked()
{
	curr_selectID_ = ui.listView->getSelectIdList();
	if (curr_selectID_ < 0)
	{
		emit sigOnSelectWarning();
		return;
	}

	if (!m_InfoList[curr_selectID_ - 1].m_PtzInfoList[0].sUserName.isEmpty())
	{
		if (tipDlg_ == NULL)
		{
			tipDlg_ = new commonTipDlg;
			connect(tipDlg_, SIGNAL(sigOnConfirm()), this, SLOT(slotOnUnBindPTZ()));
		}
		tipDlg_->setTitleLabelText(QStringLiteral("解除绑定"));
		tipDlg_->setTipText(QStringLiteral("确定要解除M1全景相机（%1）与球机（%2）的绑定吗？").arg(m_InfoList[curr_selectID_ - 1].name).arg(m_InfoList[curr_selectID_ - 1].m_PtzInfoList[0].sIP));
		tipDlg_->activateWindow();
		QPoint point = this->mapToGlobal(this->pos());
		int x = point.x();
		int y = point.y();
		int xx = this->width();
		int yy = tipDlg_->width();
		int nX = (this->width() - tipDlg_->width()) / 2 + x;
		int nY = (this->height() - tipDlg_->height()) / 2 + y;
		tipDlg_->move(nX, nY);
		tipDlg_->exec();
		return;
	}
	if (ptzDlg_ == NULL)
	{
		ptzDlg_ = new ptzSettingsDlg;
		connect(ptzDlg_, SIGNAL(sigOnBindPtz(QString, int, QString, QString)), this, SLOT(slotOnBindPtz(QString, int, QString, QString)));
		ptzDlg_->activateWindow();
	}
	QString ip = m_InfoList[curr_selectID_ - 1].m_PtzInfoList[0].sIP;
	int port = m_InfoList[curr_selectID_ - 1].m_PtzInfoList[0].wPort;
	QString user = m_InfoList[curr_selectID_ - 1].m_PtzInfoList[0].sUserName;
	QString passwd = m_InfoList[curr_selectID_ - 1].m_PtzInfoList[0].sPasswd;
	ptzDlg_->setCurrData(ip, port, user, passwd);
	QPoint point = this->mapToGlobal(this->pos());
	int x = point.x();
	int y = point.y();
	int xx = this->width();
	int yy = ptzDlg_->width();
	int nX = (this->width() - ptzDlg_->width()) / 2 + x;
	int nY = (this->height() - ptzDlg_->height()) / 2 + y;
	ptzDlg_->move(nX, nY);
	ptzDlg_->exec();
}

/*************************************************
函数名:    	slotOnUnBindPTZ
函数描述:	解除绑定球机响应槽函数
输入参数:
输出参数:
返回值:
**************************************************/
void deviceManageWgt::slotOnUnBindPTZ()
{
	m_InfoList[curr_selectID_ - 1].m_PtzInfoList[0].sIP = "";
	m_InfoList[curr_selectID_ - 1].m_PtzInfoList[0].wPort = 0;
	m_InfoList[curr_selectID_ - 1].m_PtzInfoList[0].sUserName = "";
	m_InfoList[curr_selectID_ - 1].m_PtzInfoList[0].sPasswd = "";

	for (int i = 0; i < m_InfoList.length(); i++)
	{
		m_InfoList[i].id = i + 1;
		if (m_InfoList[i].id == m_InfoList.length())
		{
			m_InfoList[i].isFinal = true;
		}
		else
		{
			m_InfoList[i].isFinal = false;
		}
	}

	emit sigOnInitData(m_InfoList);
	//分发列表
	emit sigOnDistributeList(m_InfoList);
	//球机注册
// 	if (ptz_register_thread_ && ptz_register_thread_->joinable())
// 	{
// 		ptz_register_thread_->join();
// 	}
// 	ptz_register_thread_.reset(new boost::thread(&deviceManageWgt::ptzRegister, this));
	if (tipDlg_ != NULL)
	{
		tipDlg_->close();
	}
	//ui.ptzBtn->setText(QStringLiteral("     绑定球机"));
}

void deviceManageWgt::slotOnConfirm()
{
	if (tipDlg_ != NULL)
	{
		tipDlg_->close();
	}

	switch (curr_delete_device_type_)
	{
	case DEVICE_PTZ:
		slotOnDeletePtz();
		break;
	case DEVICE_SPY:
		slotOnDeleteSpy();
		break;
	default:
		break;
	}
}


/*************************************************
函数名:    	slotOnBindPtz
函数描述:	绑定球机响应槽函数
输入参数:
输出参数:
返回值:
**************************************************/
void deviceManageWgt::slotOnBindPtz(QString Ip, int port, QString user, QString passwd, int type)
{
	switch (type)
	{
	case 0:
	{
		curr_bind_ptz_.sIP = Ip;
		curr_bind_ptz_.sUserName = user;
		curr_bind_ptz_.sPasswd = passwd;
		curr_bind_ptz_.wPort = port;
		curr_selectID_ = ui.listView->getSelectIdList();

		if (m_InfoList[curr_selectID_ - 1].m1DeviceId == "default")
		{
			curr_bind_ptz_.m1Id = m_InfoList[curr_selectID_ - 1].serialNo;
		}
		else
		{
			curr_bind_ptz_.m1Id = m_InfoList[curr_selectID_ - 1].m1DeviceId;
		}
		curr_bind_ptz_.pvsID = m_InfoList[curr_selectID_ - 1].serialNo;
		slotOnSetPtzPoint();
		break;
	}
	case 1:
		{ 			
			curr_bind_spy_.sIP = Ip;
			curr_bind_spy_.sUserName = user;
			curr_bind_spy_.sPasswd = passwd;
			curr_bind_spy_.wPort = port;
			curr_selectID_ = ui.listView->getSelectIdList();

			if (m_InfoList[curr_selectID_ - 1].m1DeviceId == "default")
			{
				curr_bind_spy_.m1Id = m_InfoList[curr_selectID_ - 1].serialNo;
			}
			else
			{
				curr_bind_spy_.m1Id = m_InfoList[curr_selectID_ - 1].m1DeviceId;
			}
			curr_bind_spy_.pvsID = m_InfoList[curr_selectID_ - 1].serialNo;
			slotOnSetSpyPoint();
			break;
		}
	default:
		break;
	}
}

void deviceManageWgt::slotOnSelected(deviceInfo info)
{
	if (info.m_PtzInfoList[0].sUserName.isEmpty())
	{
		//ui.ptzBtn->setText(QStringLiteral("     绑定球机"));
	}
	else
	{
		//ui.ptzBtn->setText(QStringLiteral("     解绑球机"));
	}
}

/*************************************************
函数名:    	slotOnScanCode
函数描述:	扫码按键触发槽函数
输入参数:    info：设备项相关数据
输出参数:
返回值:
**************************************************/
void deviceManageWgt::slotOnScanCode(deviceInfo info)
{
	reportOptimizePTSRequest(info);
	if (qrDlg_ == NULL)
	{
		qrDlg_ = new qrCodeDlg;
		qrDlg_->activateWindow();
	}
	QString IP = DetuPVMSIni::getServerIP();
	QString port = DetuPVMSIni::getServerPort();
	QString nvrID = info.serialNo;
	qrDlg_->initData(nvrID, IP, port);
	QPoint point = this->mapToGlobal(this->pos());
	int x = point.x();
	int y = point.y();
	int xx = this->width();
	int yy = qrDlg_->width();
	int nX = (this->width() - qrDlg_->width()) / 2 + x;
	int nY = (this->height() - qrDlg_->height()) / 2 + y;
	qrDlg_->move(nX, nY);
	qrDlg_->exec();
}

/*************************************************
函数名:    	slotOnPageChanged
函数描述:	列表页面变化触发槽函数
输入参数:    index：按钮的key
输出参数:
返回值:
**************************************************/
void deviceManageWgt::slotOnPageChanged(int index)
{
	if (index > 0)
	{
		ui.listStackedWidget->setCurrentIndex(index - 1);
		ui.tittleWgt->setCurrentPage(index - 1);
// 		QList<PtzInfo> test;
// 		PtzInfo *info = new PtzInfo;
// 		QList<SpyInfo> test1;
// 		SpyInfo *info1 = new SpyInfo;
		switch (index)
		{
		case 1:
			break;
		case 2:
			socketRequest::instance()->requestOnGetBindDeviceList(DEVICE_PTZ); 
			break;
		case 3:
			socketRequest::instance()->requestOnGetBindDeviceList(DEVICE_SPY);
			break;
		}
	}
}

/*************************************************
函数名:    	slotOnBindDevice
函数描述:	绑定设备触发槽函数
输入参数:    info
输出参数:
返回值:
**************************************************/
void deviceManageWgt::slotOnBindDevice(deviceInfo info)
{
	if (m_bindDeviceDlg == NULL)
	{
		m_bindDeviceDlg = new bindDeviceDlg();
		connect(m_bindDeviceDlg, SIGNAL(sigOnBindPtz(QString, int, QString, QString, int)), this, SLOT(slotOnBindPtz(QString, int, QString, QString, int)));
		connect(m_bindDeviceDlg, SIGNAL(sigOnSetPoint()), this, SLOT(slotOnSetPtzPoint()));

		qRegisterMetaType<QList<PtzInfo>>();
		connect(this, SIGNAL(sigOnInitPtzData(QList<PtzInfo>)), m_bindDeviceDlg, SLOT(slotOnInitPtzData(QList<PtzInfo>)), Qt::QueuedConnection);

		qRegisterMetaType<QList<SpyInfo>>();
		connect(this, SIGNAL(sigOnInitSpyData(QList<SpyInfo>)), m_bindDeviceDlg, SLOT(slotOnInitSpyData(QList<SpyInfo>)), Qt::QueuedConnection);

	}
	m_bindDeviceDlg->init(info);
	m_bindDeviceDlg->activateWindow();
	QPoint point = this->mapToGlobal(this->pos());
	int x = point.x();
	int y = point.y();
	int xx = this->width();
	int yy = m_bindDeviceDlg->width();
	int nX = (this->width() - m_bindDeviceDlg->width()) / 2 + x;
	int nY = (this->height() - m_bindDeviceDlg->height()) / 2 + y;
	m_bindDeviceDlg->setParentPos(x, y, this->width(), this->height());
	m_bindDeviceDlg->move(nX, nY);
	m_bindDeviceDlg->show();
}

void deviceManageWgt::slotOnLiveShow(deviceInfo info)
{
	bool ret = isPushFlowDevice(info);
	if (ret && !info.isPushFlow)
	{
		QMessageBox::warning(this, tr("warning"), tr("has been in the stream !"));
		return;
	}

	if (m_pushFlowSettingsDlg == NULL)
	{
		m_pushFlowSettingsDlg = new pushFlowSettingsDlg(this);
		connect(m_pushFlowSettingsDlg, SIGNAL(sigOnSyncData(deviceInfo)), this, SLOT(slotOnSyncData(deviceInfo)));
	}

	if (info.isPushFlow)
	{
		m_pushFlowSettingsDlg->initPushFlowInfoPage();
	}
	else
	{
		m_pushFlowSettingsDlg->initPushFlowPage();
	}
	m_pushFlowSettingsDlg->initTCSList(m_TCSManageInfoList);
	m_pushFlowSettingsDlg->syncConnection(true);
	m_pushFlowSettingsDlg->initData(info);
	QPoint point = this->mapToGlobal(this->pos());
	int x = point.x();
	int y = point.y();
	int nX = (this->width() - m_pushFlowSettingsDlg->width()) / 2;
	int nY = (this->height() - m_pushFlowSettingsDlg->height()) / 2;
	m_pushFlowSettingsDlg->move(nX, nY);
	m_pushFlowSettingsDlg->exec();
}

void deviceManageWgt::slotOnSyncData(deviceInfo info)
{
	for (int i = 0; i < m_InfoList.size(); ++i)
	{
		if (m_InfoList[i].serialNo == info.serialNo)
		{
			m_InfoList[i] = info;
		}
	}
	for (int i = 0; i < m_InfoList.length(); i++)
	{
		m_InfoList[i].id = i + 1;
		if (m_InfoList[i].id == m_InfoList.length())
		{
			m_InfoList[i].isFinal = true;
		}
		else
		{
			m_InfoList[i].isFinal = false;
		}
	}
	emit sigOnInitData(m_InfoList);
	emit sigOnDistributeList(m_InfoList);
	ViewSignal::instance()->sigOnDistributeList(m_InfoList);
}

void deviceManageWgt::slotOnSetPtzPoint()
{
	if (m_bindDeviceDlg != NULL)
	{
		m_bindDeviceDlg->deleteLater();
		m_bindDeviceDlg = NULL;
	}

	m_PtzPointSettingDlg->deleteLater();
	m_PtzPointSettingDlg = NULL;

	m_PtzPointSettingDlg = new ptzSettingPointDlg;
	m_PtzPointSettingDlg->setTitleText(curr_bind_ptz_);
	m_PtzPointSettingDlg->raise();
	m_PtzPointSettingDlg->activateWindow();
	QPoint point = this->mapToGlobal(this->pos());
	int x = point.x();
	int y = point.y();
	int xx = this->width();
	int yy = m_PtzPointSettingDlg->width();
	int nX = (this->width() - m_PtzPointSettingDlg->width()) / 2 + x;
	int nY = (this->height() - m_PtzPointSettingDlg->height()) / 2 + y;
	m_PtzPointSettingDlg->move(nX, nY);
	m_PtzPointSettingDlg->setPosSet(nX, nY);
    m_PtzPointSettingDlg->show();
}

void deviceManageWgt::slotOnSetSpyPoint()
{
	if (m_bindDeviceDlg != NULL)
	{
		m_bindDeviceDlg->deleteLater();
		m_bindDeviceDlg = NULL;
	}

	m_SpyPointSettingDlg->deleteLater();
	m_SpyPointSettingDlg = NULL;
	m_SpyPointSettingDlg = new gunCamSettingDig;
	
	m_SpyPointSettingDlg->setTitleText(curr_bind_spy_);
	m_SpyPointSettingDlg->raise();
	m_SpyPointSettingDlg->activateWindow();
	QPoint point = this->mapToGlobal(this->pos());
	int x = point.x();
	int y = point.y();
	int xx = this->width();
	int yy = m_SpyPointSettingDlg->width();
	int nX = (this->width() - m_SpyPointSettingDlg->width()) / 2 + x;
	int nY = (this->height() - m_SpyPointSettingDlg->height()) / 2 + y;
	m_SpyPointSettingDlg->move(nX, nY);
	//m_SpyPointSettingDlg->setPosSet(nX, nY);
	m_SpyPointSettingDlg->show();
	m_SpyPointSettingDlg->showGunCam();

}

void deviceManageWgt::slotOnGetPTZList(std::vector<PTZManageTable_t> ptzList)
{
		if (get_ptz_thread_ && get_ptz_thread_->joinable())
		{
			get_ptz_thread_->join();
		}
		get_ptz_thread_.reset(new boost::thread(&deviceManageWgt::getPTZListThread, this,ptzList));
}

void deviceManageWgt::getPTZListThread(std::vector<PTZManageTable_t> ptzList)
{
	locker.lock();
	for (int i = 0; i < m_InfoList.size(); ++i)
	{
		m_ptzInfoList.clear();
		m_InfoList[i].m_PtzInfoList.clear();
		for (std::vector<PTZManageTable_t>::iterator iter = ptzList.begin(); iter != ptzList.end(); iter++)
		{
			PtzInfo skt_t1;
			skt_t1.pvsID = QString::fromStdString((char*)iter->pvsID);
			skt_t1.sUserName = QString::fromStdString((char*)iter->username);
			skt_t1.sPasswd = QString::fromStdString((char*)iter->passwd);
			skt_t1.sIP = QString::fromStdString((char*)iter->nIP);
			skt_t1.wPort = iter->nPort;
			m_ptzInfoList.append(skt_t1);

			QString pvsID = QString::fromStdString((char*)iter->pvsID);
			if (pvsID == m_InfoList[i].serialNo)
			{
				m_InfoList[i].m_PtzInfoList.append(skt_t1);
			}
		}
	}
	curr_selectID_ = ui.listView->getSelectIdList();
	if (m_bindDeviceDlg != NULL && curr_selectID_ > 0)
	{
		m_bindDeviceDlg->slotOnInitPtzList(m_ptzInfoList);
	}

	//分发列表
	for (int i = 0; i < m_InfoList.length(); i++)
	{
		m_InfoList[i].id = i + 1;
		if (m_InfoList[i].id == m_InfoList.length())
		{
			m_InfoList[i].isFinal = true;
		}
		else
		{
			m_InfoList[i].isFinal = false;
		}
	}
	emit sigOnInitData(m_InfoList);
	emit sigOnInitPtzData(m_ptzInfoList);
	emit sigOnDistributeList(m_InfoList);
	ViewSignal::instance()->sigOnDistributeList(m_InfoList);
	//MapPointListManagerIns.updatePtzData(ptzList);

	locker.unlock();
}


void deviceManageWgt::slotOnGetSPYList(std::vector<SPYManageTable_t> spyList)
{

	if (get_spy_thread_ && get_spy_thread_->joinable())
	{
		get_spy_thread_->join();
	}
	get_spy_thread_.reset(new boost::thread(&deviceManageWgt::getSPYListThread, this, spyList));
}

void deviceManageWgt::getSPYListThread(std::vector<SPYManageTable_t> spyList)
{
	locker.lock();
	for (int i = 0; i < m_InfoList.size(); ++i)
	{
		m_spyInfoList.clear();
		m_InfoList[i].m_SpyInfoList.clear();
		for (std::vector<SPYManageTable_t>::iterator iter = spyList.begin(); iter != spyList.end(); iter++)
		{
			SpyInfo skt_t1;
			skt_t1.pvsID = QString::fromStdString((char*)iter->pvsID);
			skt_t1.sUserName = QString::fromStdString((char*)iter->username);
			skt_t1.sPasswd = QString::fromStdString((char*)iter->passwd);
			skt_t1.sIP = QString::fromStdString((char*)iter->nIP);
			skt_t1.wPort = iter->nPort;

			skt_t1.pos_x = iter->nPosX;
			skt_t1.pos_y = iter->nPosY;

			m_spyInfoList.append(skt_t1);

			QString pvsID = QString::fromStdString((char*)iter->pvsID);
			if (pvsID == m_InfoList[i].serialNo)
			{
				m_InfoList[i].m_SpyInfoList.append(skt_t1);
			}
		}
	}

	curr_selectID_ = ui.listView->getSelectIdList();
	if (m_bindDeviceDlg != NULL && curr_selectID_ > 0)
	{
		m_bindDeviceDlg->slotOnInitSpyList(m_spyInfoList);
	}

	//分发列表
	for (int i = 0; i < m_InfoList.length(); i++)
	{
		m_InfoList[i].id = i + 1;
		if (m_InfoList[i].id == m_InfoList.length())
		{
			m_InfoList[i].isFinal = true;
		}
		else
		{
			m_InfoList[i].isFinal = false;
		}
	}
	emit sigOnInitData(m_InfoList);
	emit sigOnInitSpyData(m_spyInfoList);
	emit sigOnDistributeList(m_InfoList);
	ViewSignal::instance()->sigOnDistributeList(m_InfoList);
	//MapPointListManagerIns.updateSpyData(spyList);

	locker.unlock();
}

void deviceManageWgt::slotOnGetTCSInfo(api_detu_tcs_register_t tmpInfo)
{
	TCSManageInfo TCSInfo;
	TCSInfo.szTcsIp = (char*)tmpInfo.szTcsIp;
	TCSInfo.nPort = tmpInfo.nPort;
	TCSInfo.nServerId = QString::number(tmpInfo.nServerId);
	TCSInfo.nLimits = tmpInfo.nLimits;
	TCSInfo.nCAU = 0;

	int index = 0;
	for (int i = 0; i < m_TCSManageInfoList.size(); ++i)
	{
		if (m_TCSManageInfoList[i].nServerId == TCSInfo.nServerId)
		{
			index++;
			m_TCSManageInfoList[i] = TCSInfo;
		}
	}

	if (index == 0)
	{
		m_TCSManageInfoList.append(TCSInfo);
	}

	if (m_pushFlowSettingsDlg)
	{
		m_pushFlowSettingsDlg->initTCSList(m_TCSManageInfoList);
	}
}

void deviceManageWgt::slotUpdateTCSInfo(api_detu_tcs_heartbeat_t tmpInfo)
{
	for (int i = 0; i < m_TCSManageInfoList.size(); ++i)
	{
		if (m_TCSManageInfoList[i].nServerId == QString::number(tmpInfo.nServerId))
		{
			m_TCSManageInfoList[i].nCAU = tmpInfo.nCAU;
			m_TCSManageInfoList[i].nLimits = tmpInfo.nLimits;
		}
	}

	if (m_pushFlowSettingsDlg)
	{
		m_pushFlowSettingsDlg->initTCSList(m_TCSManageInfoList);
	}
}

void deviceManageWgt::slotOnDeletePtz(PtzInfo ptzInfo)
{
	curr_delete_device_type_ = DEVICE_PTZ;
	if (tipDlg_ == NULL)
	{
		tipDlg_ = new commonTipDlg;
		connect(tipDlg_, SIGNAL(sigOnConfirm()), this, SLOT(slotOnConfirm()));
	}
	tipDlg_->setTitleLabelText(QStringLiteral("删除设备"));
	tipDlg_->setTipText(QStringLiteral("确定要删除球机（%2）设备吗？").arg(ptzInfo.sIP));
	tipDlg_->activateWindow();
	QPoint point = this->mapToGlobal(this->pos());
	int x = point.x();
	int y = point.y();
	int xx = this->width();
	int yy = tipDlg_->width();
	int nX = (this->width() - tipDlg_->width()) / 2 + x;
	int nY = (this->height() - tipDlg_->height()) / 2 + y;
	tipDlg_->move(nX, nY);
	tipDlg_->exec();
}

void deviceManageWgt::slotOnDeletePtz()
{
	curr_selectID_ = ui.ptzListView->getSelectIdList();
	if (curr_selectID_ > 0)
	{
		socketRequest::instance()->requestOnDeletePTZDevice(m_ptzInfoList[curr_selectID_ - 1]);
	}
}

void deviceManageWgt::slotOnDeleteSpy(SpyInfo spyInfo)
{
	curr_delete_device_type_ = DEVICE_SPY;
	if (tipDlg_ == NULL)
	{
		tipDlg_ = new commonTipDlg;
		connect(tipDlg_, SIGNAL(sigOnConfirm()), this, SLOT(slotOnConfirm()));
	}
	tipDlg_->setTitleLabelText(QStringLiteral("删除设备"));
	tipDlg_->setTipText(QStringLiteral("确定要删除枪机（%2）设备吗？").arg(spyInfo.sIP));
	tipDlg_->activateWindow();
	QPoint point = this->mapToGlobal(this->pos());
	int x = point.x();
	int y = point.y();
	int xx = this->width();
	int yy = tipDlg_->width();
	int nX = (this->width() - tipDlg_->width()) / 2 + x;
	int nY = (this->height() - tipDlg_->height()) / 2 + y;
	tipDlg_->move(nX, nY);
	tipDlg_->exec();
}

void deviceManageWgt::slotOnDeleteSpy()
{
	curr_selectID_ = ui.spyListView->getSelectIdList();
	if (curr_selectID_ > 0)
	{
		socketRequest::instance()->requestOnDeleteSPYDevice(m_spyInfoList[curr_selectID_ - 1]);
	}
}

void deviceManageWgt::slotOnDeletePTZRes(short result)
{
	switch (result)
	{
	case _ACTIVE_REPORT::RESULT_FAILED:
		Feedback::instance()->maskUI(DELETE_PTZ_FAILED);
		break;
	case _ACTIVE_REPORT::RESULT_SUCCESS:
		Feedback::instance()->maskUI(DELETE_PTZ_SUCCESS);
		break;
	default:
		break;
	}
}

void deviceManageWgt::slotOnDeleteSPYRes(short result)
{
	switch (result)
	{
	case _ACTIVE_REPORT::RESULT_FAILED:
		Feedback::instance()->maskUI(DELETE_SPY_FAILED);
		break;
	case _ACTIVE_REPORT::RESULT_SUCCESS:
		Feedback::instance()->maskUI(DELETE_SPY_SUCCESS);
		break;
	default:
		break;
	}
}

void deviceManageWgt::slotOnInitData(QList<deviceInfo> itemInfoList)
{
	ui.listView->clearItems();
	int count = itemInfoList.length();
	for (int i = 0; i < count; i++)
	{
		ui.listView->appendItem(itemInfoList[i]);
	}
}

void deviceManageWgt::slotOnReportTCSOffLine(int serverId)
{
	int index = -1;
	for (int i = 0; i < m_TCSManageInfoList.size(); ++i)
	{
		if (m_TCSManageInfoList[i].nServerId.toInt() == serverId)
		{
			index = i;
		}
	}

	if (index >0)
	{
		m_TCSManageInfoList.removeAt(index);
	}

	if (m_pushFlowSettingsDlg)
	{
		m_pushFlowSettingsDlg->deleteLater();
		m_pushFlowSettingsDlg = NULL;
	}
}

void deviceManageWgt::init()
{
    buttonGroup_ = new QButtonGroup;
	buttonGroup_->addButton(ui.panoramicBtn, 1);
	buttonGroup_->addButton(ui.ptzBtn, 2);
	buttonGroup_->addButton(ui.spyBtn, 3);
	ui.panoramicBtn->setChecked(true);
	ui.listStackedWidget->setCurrentWidget(ui.homePage);
}

void deviceManageWgt::initConnect()
{
	connect(ui.listView, SIGNAL(sigOnSetup(deviceInfo)), this, SLOT(slotOnSetup(deviceInfo)));
	connect(ui.listView, SIGNAL(sigOnDownMove(deviceInfo)), this, SLOT(slotOnDownMove(deviceInfo)));
	connect(ui.listView, SIGNAL(sigOnUpMove(deviceInfo)), this, SLOT(slotOnUpMove(deviceInfo)));
	connect(ui.listView, SIGNAL(sigOnClicked(deviceInfo)), this, SLOT(slotOnSelected(deviceInfo)));
	connect(ui.listView, SIGNAL(sigOnScanCode(deviceInfo)), this, SLOT(slotOnScanCode(deviceInfo)));
	connect(ui.listView, SIGNAL(sigOnBindDevice(deviceInfo)), this, SLOT(slotOnBindDevice(deviceInfo)));
	connect(ui.listView, SIGNAL(sigOnLiveShow(deviceInfo)), this, SLOT(slotOnLiveShow(deviceInfo)));

	connect(ui.ptzListView, SIGNAL(sigOnDeletePtz(PtzInfo)), this, SLOT(slotOnDeletePtz(PtzInfo)));
	connect(ui.spyListView, SIGNAL(sigOnDeleteSpy(SpyInfo)), this, SLOT(slotOnDeleteSpy(SpyInfo)));

	connect(ui.toolButton, SIGNAL(clicked()), this, SLOT(slotOnUpdate()));
	connect(buttonGroup_, SIGNAL(buttonClicked(int)), this, SLOT(slotOnPageChanged(int)));

	qRegisterMetaType<QList<deviceInfo>>();
	connect(this, SIGNAL(sigOnInitData(QList<deviceInfo>)), this, SLOT(slotOnInitData(QList<deviceInfo>)), Qt::QueuedConnection);

	qRegisterMetaType<QList<PtzInfo>>();
	connect(this, SIGNAL(sigOnInitPtzData(QList<PtzInfo>)), this, SLOT(slotOnInitPtzData(QList<PtzInfo>)), Qt::QueuedConnection);

	qRegisterMetaType<QList<SpyInfo>>();
	connect(this, SIGNAL(sigOnInitSpyData(QList<SpyInfo>)), this, SLOT(slotOnInitSpyData(QList<SpyInfo>)), Qt::QueuedConnection);
	

	connect(&TcpDataManagerIns, SIGNAL(NvrListReceived()), this, SLOT(slotOnGetDeviceList()));
	connect(&TcpDataManagerIns, SIGNAL(sigOnGetDiskSize()), this, SLOT(slotOnGetDiskSize()));
	connect(&TcpDataManagerIns, SIGNAL(sigOnDeletePTZ(short)), this, SLOT(slotOnDeletePTZRes(short)));
	connect(&TcpDataManagerIns, SIGNAL(sigOnDeleteSPY(short)), this, SLOT(slotOnDeleteSPYRes(short)));

	qRegisterMetaType<std::vector<PTZManageTable_t>>();
	connect(&TcpDataManagerIns, SIGNAL(sigOnGetPTZList(std::vector<PTZManageTable_t>)), this, SLOT(slotOnGetPTZList(std::vector<PTZManageTable_t>)));
	qRegisterMetaType<std::vector<SPYManageTable_t>>();
	connect(&TcpDataManagerIns, SIGNAL(sigOnGetSPYList(std::vector<SPYManageTable_t>)), this, SLOT(slotOnGetSPYList(std::vector<SPYManageTable_t>)));

	qRegisterMetaType<api_detu_tcs_register_t>("api_detu_tcs_register_t");
	connect(&TcpDataManagerIns, SIGNAL(sigOnGetTCSInfo(api_detu_tcs_register_t)), this, SLOT(slotOnGetTCSInfo(api_detu_tcs_register_t)));
	qRegisterMetaType<api_detu_tcs_heartbeat_t>("api_detu_tcs_heartbeat_t");
	connect(&TcpDataManagerIns, SIGNAL(sigUpdateTCSInfo(api_detu_tcs_heartbeat_t)), this, SLOT(slotUpdateTCSInfo(api_detu_tcs_heartbeat_t)));

	connect(ViewSignal::instance(), SIGNAL(sigOnReportTCSOffLine(int)), this, SLOT(slotOnReportTCSOffLine(int)));
}


void deviceManageWgt::getDiskSize()
{
	protocol_head_t api_head;
	api_detu_client_disk_size_t api_detu;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_CLIENT_DISKINFO;
	api_head.nDataLen = 0;
	api_head.nResult = 0x00;
	api_head.nStreamId = 0;
	//api_head.nReserver = 0x01;        //预留位
	api_head.nEndFlags = 0xFA;

	Log::Debug("Get DiskSize: cmd:%d streamid:%d", api_head.nCmd, api_head.nStreamId);
	response res(api_head.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

void deviceManageWgt::updateData(deviceInfo *info, QString name, QString deviceId, int direction, QString ip, int port, QString user, QString passwd, QString M1Id, int online)
{
	if (name.isEmpty())
	{
		info->name = deviceId;
	}
	else
	{
		info->name = name;
	}
	info->serialNo = deviceId;
	info->m1DeviceId = M1Id;
	info->is_up_down = direction;
	info->status = online;
	info->bClicked = false;
	info->RbClicked = false;
	info->usedRoom = 0;
	info->usingRoom = 0;
	info->diskNum = 0;
	m_InfoList.append(*info);
}


void deviceManageWgt::updateData(int id, QString name, QString deviceId, int direction, int port, QString user, QString passwd, QString M1Id, int online)
{
	if (name.isEmpty())
	{
		m_InfoList[id].name = deviceId;
	}
	else
	{
		m_InfoList[id].name = name;
	}
	m_InfoList[id].serialNo = deviceId;
	m_InfoList[id].m1DeviceId = M1Id;
	m_InfoList[id].is_up_down = direction;
	m_InfoList[id].status = online;
}

/*************************************************
函数名:    	reportOptimizePTSRequest
函数描述:	上报优化后的pts文件到服务器请求
输入参数:    info
输出参数:
返回值:
**************************************************/
void deviceManageWgt::reportOptimizePTSRequest(deviceInfo info)
{
	protocol_head_t api_head;
	api_detu_client_optmize api_detu;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_CLIENT_REPORT_OPTIMIZE_PTS;
	api_head.nDataLen = api_detu.get_size();
	api_head.nResult = 0x00;
	api_head.nStreamId = 0;
	//api_head.nReserver = 0x01;        //预留位
	api_head.nEndFlags = 0xFA;
	QString data;
	if (info.m1DeviceId=="default")
	{
		data = readPTSData(info.serialNo);
	}
	else
	{
		data = readPTSData(info.m1DeviceId);
	}
	if (data.isEmpty())
	{
		return;
	}
	memcpy(api_detu.szDeviceId, info.serialNo.toLocal8Bit().data(), API_ARRAY_LEN);
	api_detu.optmize_pts.nPtsLen = data.length();
	memcpy(api_detu.optmize_pts.pts_data, data.toLocal8Bit().data(), API_PTS_LEN);
	Log::Debug("report pts data length : %d to server", data.length());

	response res(api_head.get_size() + api_detu.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
	response_add_resprotocol<api_detu_client_optmize>(res, &api_detu);

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

QString deviceManageWgt::readPTSData(QString deviceNo)
{
	QString pts_file_path = QDir::homePath() + "/AppData/Local/Pano-VMS/pts/" + deviceNo + "/pat.pts";
	QFile file(pts_file_path);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		Log::Info("read pts file open failed or pts file no exit!");
		return "";
	}
	QByteArray array = file.readAll();
	QString data(array);
	return data;
}

bool deviceManageWgt::isPushFlowDevice(deviceInfo info)
{
	int index = 0;

	for (int i = 0; i < m_InfoList.size(); ++i)
	{
		if (m_InfoList[i].isPushFlow && !m_InfoList[i].szPushFlowUrl.isEmpty())
		{
			index++;
		}
	}

	if (index)
	{
		return true;
	}

	return false;
}

