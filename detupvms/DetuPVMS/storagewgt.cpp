#include "storagewgt.h"
#include "DetuPVMSIni.h"
#include "dmconnection.hpp"
#include "SocketManager.h"
#include "TcpDataManager.hpp"
#include "logging.hpp"
#include "feedback.h"
#include "constStruct.h"

storageWgt::storageWgt(QWidget *parent)
	: QWidget(parent)
	, m_selectId(-1)
	, waitDlg_(NULL)
	, formatDlg_(NULL)
	, timer_(NULL)
	, isUpdate_(false)
{
	ui.setupUi(this);
	//init();
	initConnect();
}

storageWgt::~storageWgt()
{
	if (waitDlg_ != NULL)
	{
		waitDlg_->deleteLater();
		waitDlg_ = NULL;
	}
	if (timer_ != NULL)
	{
		timer_->deleteLater();
		timer_ = NULL;
	}
}

void storageWgt::initData(const QList<deviceInfo> &itemInfoList)
{
	m_InfoList = itemInfoList;
	generateUI();
}

void storageWgt::getSelectId(int selectId)
{
	m_selectId = selectId;
}

void storageWgt::updateDeviceList(QList<deviceInfo> deviceList)
{
	m_InfoList = deviceList;
	initData(m_InfoList);
	isUpdate_ = true;
	ui.refreshBtn->setEnabled(true);
}

void storageWgt::refreshDisk()
{
	slotOnRefresh();
}

void storageWgt::slotOnRefresh()
{
	if (SocketManagerIns.isConnected())
	{
		isUpdate_ = false;
		ui.refreshBtn->setEnabled(false);
		emit sigOnUpdate();
		QTimer::singleShot(3000, this, SLOT(slotOnRefreshStatus()));
	}
}

void storageWgt::slotOnDiskFormat()
{
	m_selectedId = ui.listView->getSelectKeyId();
	if (m_selectedId.size() > 0)
	{
		if (formatDlg_ == NULL)
		{
			formatDlg_ = new diskFormatDlg;
			Log::Info("formatDlg_->setParent(this);");
			formatDlg_->setParent(this);
			connect(formatDlg_, SIGNAL(sigOnDiskFormat()), this, SLOT(slotDiskFormat()));
		}
		formatDlg_->activateWindow();
		formatDlg_->show();
		QPoint point = this->mapToGlobal(this->pos());
		int x = point.x();
		int y = point.y();
		int nX = (this->width() - formatDlg_->width()) / 2;
		int nY = (this->height() - formatDlg_->height()) / 2;
		formatDlg_->move(nX, nY - 60);
		return;
	}
	Feedback::instance()->maskUI(FORMAT_NULL);
}

void storageWgt::slotDiskFormat()
{
	if (formatDlg_ != NULL)
	{
		formatDlg_->close();
	}
	if (get_disk_thread_ && get_disk_thread_->joinable())
	{
		get_disk_thread_->join();
	}
	get_disk_thread_.reset(new boost::thread(&storageWgt::requestDiskFormat, this));
}

void storageWgt::slotOnGetDiskSize()
{
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
		initData(m_InfoList);
	}
}

void storageWgt::slotOnRefreshStatus()
{
	ui.refreshBtn->setEnabled(true);
}

void storageWgt::slotOnSetDiskFormat(bool is_ok)
{
	if (is_ok)
	{
		Log::Debug("request format success!");
		if (waitDlg_ == NULL)
		{
			waitDlg_ = new waitWidget;
			Log::Debug("waitDlg_->setParent(this);");
			waitDlg_->setParent(this);
		}
		waitDlg_->show();
		QPoint point = this->mapToGlobal(this->pos());
		int x = point.x();
		int y = point.y();
		int nX = (this->width() - waitDlg_->width()) / 2;
		int nY = (this->height() - waitDlg_->height()) / 2;
		waitDlg_->move(nX, nY - 60);

		if (timer_ == NULL)
		{
			timer_ = new QTimer(this);
			connect(timer_, SIGNAL(timeout()), this, SLOT(slotOnCheckFormatResult()));
		}		
		timer_->setInterval(10000);
		timer_->start();
	}
	else
	{
		Log::Debug("disk format failed!");
		Feedback::instance()->maskUI(FORMAT_FAILED);
	}
}

void storageWgt::slotOnCheckFormatResult()
{
	Log::Debug("check format result timer start!");
	//更新磁盘列表
	getDiskSize();//async

	//
	if (isUpdate_)
	{
		//校验被选中nvr的所有磁盘格式化成功
		int totalNum = 0;
		if (m_selectedId.size() > 0 && m_InfoList.size() > 0)
		{
			for (int i = 0; i < m_selectedId.size(); i++)
			{
				for (int j = 0; j < m_InfoList.size(); j++)
				{
					if (m_selectedId.at(i) == m_InfoList.at(j).id)
					{
						int curNum = m_InfoList.at(j).disk_info_list.size();
						totalNum += curNum;
						for (int k = 0; k < curNum; k++)
						{
							if (m_InfoList.at(j).disk_info_list.at(k).nDiskStatus == DISKSTATUS_DORMANCY)
							{
								totalNum--;
							}
						}
					}
				}
			}
			if (totalNum == 0)
			{
				Log::Debug("disk format success!");
				Feedback::instance()->maskUI(FORMAT_SUCCESS);
				if (waitDlg_ != NULL)
				{
					waitDlg_->hide();
					timer_->stop();
				}
			}
		}
		else
		{
			Log::Debug("please select disk to formatting!");
			Feedback::instance()->maskUI(FORMAT_FAILED);
		}
	}
}

void storageWgt::init()
{
	deviceInfo *info = new deviceInfo;
	info->bClicked = false;
	info->diskNum = 1;
	info->is_up_down = 0;
	info->isFinal = 1;
	info->name = QStringLiteral("大门");
	info->serialNo = "B3CD4X";
	info->RbClicked = false;
	info->status = 1;
	info->usedRoom = 1024;
	info->usingRoom = 2048;
	m_InfoList.append(*info);
	initData(m_InfoList);
}

void storageWgt::initConnect()
{
	connect(ui.refreshBtn, SIGNAL(clicked()), this, SLOT(slotOnRefresh()));
	connect(ui.clearBtn, SIGNAL(clicked()), this, SLOT(slotOnDiskFormat()));
	connect(&TcpDataManagerIns, SIGNAL(sigOnSetDiskFormat(bool)), this, SLOT(slotOnSetDiskFormat(bool)));
/*	connect(&TcpDataManagerIns, SIGNAL(sigOnGetDiskSize()), this, SLOT(slotOnGetDiskSize()));*/
}

void storageWgt::generateUI()
{
	ui.listView->clearItems();
	int count = m_InfoList.length();
	for (int i = 0; i < count; i++)
	{
		m_InfoList[i].id = i + 1;
		ui.listView->appendItem(m_InfoList[i]);
	}
}

void storageWgt::requestDiskSize()
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

void storageWgt::requestDiskFormat()
{
	if (!SocketManagerIns.isConnected()){
		Feedback::instance()->maskUI(SERVER_UNCONNECT);
		return;
	}
	isUpdate_ = false;
	if (m_selectedId.size() > 0)
	{
		api_detu_client_disk_size_list_t api_list;
		api_list.numlist = m_selectedId.size();
		int m = 0;
		for (int i = 0; i < m_selectedId.size(); i++)
		{
			for (int j = 0; j < m_InfoList.size(); j++)
			{
				if (m_selectedId.at(i) == m_InfoList.at(j).id)
				{
					int count = m_InfoList.at(j).diskNum;
					for (int n = 0; n < count; n++)
					{
						api_list.diskList[m].nTotalDiskNum = count;
						api_list.diskList[m].nDiskId = m_InfoList.at(j).disk_info_list.at(n).nDiskId;
						memcpy(api_list.diskList[m].szDeviceId, m_InfoList.at(j).serialNo.toLocal8Bit().data(), API_ARRAY_LEN);
						m++;
					}
				}
			}
		}
		protocol_head_t api_head;

		api_head.nStartFlags = 0xAF;
		api_head.nVersion = 0x01;
		api_head.nCmd = CMD_DETU_CLIENT_DISK_FORMAT;
		api_head.nDataLen = api_list.get_size();
		api_head.nResult = 0x00;
		api_head.nStreamId = 0;
		//api_head.nReserver = 0x01;        //预留位
		api_head.nEndFlags = 0xFA;

		Log::Debug("Disk Format: cmd:%d streamid:%d", api_head.nCmd, api_head.nStreamId);
		response res(api_head.get_size() + api_list.get_size());
		response_add_resprotocol<protocol_head_t>(res, &api_head);
		response_add_resprotocol<api_detu_client_disk_size_list_t>(res, &api_list);
		dmconnection* conn = SocketManagerIns.GetCommSocket();
		if (conn != NULL)
		{
			conn->do_write(res);
		}
	}
}

void storageWgt::getDiskSize()
{
	if (format_disk_thread_ && format_disk_thread_->joinable())
	{
		format_disk_thread_->join();
	}
	format_disk_thread_.reset(new boost::thread(&storageWgt::requestDiskSize, this));
}
