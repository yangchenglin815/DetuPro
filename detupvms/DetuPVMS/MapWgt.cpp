#include <assert.h>
#include <QEvent> 
#include <QDragEnterEvent>
#include <QGraphicsProxyWidget>
#include <QGraphicsGridLayout>
#include <QMovie>
#include <QDrag>
#include <QPainter>

#include "zlib.h"
#include "quazip/JlCompress.h"

#include "MapWgt.h"
#include "MapPointWgt.h"

#include "MinimapWgt.h"
#include "commonListWidget.h"
#include "VRMap/panoramaItemWidget.h"
#include "VRMap/GlViewSetingWgt.h"

#include "playmodewgt.h"
#include "ReplayCtrWgt.h"
#include "feedback.h"
#include "constStruct.h"

#include "DetuPVMSIni.h"
//初始化控制器
#include "MessageManager.h"
#include "SocketManager.h"
#include "TcpDataManager.hpp"
#include "ListAndGLWindowManager.h"
#include "MapPointListManager.h"
#include "ViewSignal.h"
#include "myQGraphicsScene.h"
#include "commonFun.h"

const int space = 5;

//#define DATA_LENGTH 1073741824			//1G
//#define DATA_LENGTH 134217728			//128M			

MapWgt::MapWgt(QWidget *parent)
: QWidget(parent)
, screen_(NULL)
, updateTimer_(NULL)
, replay_ctrl_wgt_(NULL)
, query_video_thread_(NULL)
, replay_server_no_response_(false)
, m_curr_state(COMMON_STATE)
, m_pointWgt_width(93)
, m_pointWgt_height(128)
, bSelected_(false)
, bChanged_(false)
, m_curr_setting_dlg(NULL)
, is_playing_(false)
, gl_view_setting_wgt_(NULL)
, tcpclient_thread_(NULL)
, senddata_thread_(NULL)
{
	ui.setupUi(this);

	init();
	initConnect();
}

MapWgt::~MapWgt()
{
	if (tcpclient_thread_ && tcpclient_thread_->joinable())
	{
		tcpclient_thread_->join();
	}


}

void MapWgt::init()
{
	ui.pathBuildingBtn->setVisible(false);
	setAcceptDrops(true);
	setMouseTracking(true);


}

void MapWgt::initConnect()
{
	connect(ui.mapSettingBtn, SIGNAL(clicked()), this, SIGNAL(sigOnAddMapBtnClicked()));
	connect(ui.pathSaveBtn, SIGNAL(clicked()), this, SLOT(SlotOnSaveMapData()));

	qRegisterMetaType<PanoMapPointInfo_t >("PanoramaManageInfo_t");
	connect(this, SIGNAL(sigOnAddMapPoint(PanoMapPointInfo_t)), this, SLOT(slotOnAddMapPoint(PanoMapPointInfo_t)));
	connect(this, SIGNAL(sigOnAddMapPoint(PanoMapPointInfo_t)), this, SLOT(slotOnAddMapPointData(PanoMapPointInfo_t)));

	connect(ViewSignal::instance(), SIGNAL(sigOnPicGroupOnClicked(PanoSceneInfo)), this, SLOT(slotOnPicGroupOnClicked(PanoSceneInfo)));
	connect(&TcpDataManagerIns, SIGNAL(MapPlayRequestSucceed()), this, SLOT(slotOnMapPlayRequestSucceed()));
}

void MapWgt::QueryForVideo()
{
	protocol_head_t api_head;
	api_detu_client_record_query api_detu;
	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_CLIENT_RECORD_QUERY;
	api_head.nDataLen = api_detu.get_size();
	api_head.nResult = 0x00;
	api_head.nStreamId = DetuPVMSIni::getReplayRtmpUrl().toInt();			//获取主码流或者子码流，通过配置文件
	//api_head.nReserver = 0x01;        //预留位
	api_head.nEndFlags = 0xFA;

	memcpy(api_detu.szDeviceId, m_curr_selected_info.cameraInfo.serialNo.toLocal8Bit(), API_ARRAY_LEN);
	QString m_date = replay_ctrl_wgt_->getSelectedDate();
	Log::Debug("current requested replayDate is %s", m_date.toLocal8Bit().data());
	api_detu.nStartTime = commonFun::getStartTime(m_date) + 28800;
	api_detu.nEndTime = commonFun::getEndTime(m_date) + 28800;

	response res(api_head.get_size() + api_detu.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
	response_add_resprotocol<api_detu_client_record_query>(res, &api_detu);

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

void MapWgt::setMapType(MapType maptype)
{
	current_map_type_ = maptype;	
}


void MapWgt::setButtonVisible(bool visible)
{
	ui.mapSettingBtn->setVisible(visible);
	ui.pathBuildingBtn->setVisible(visible);
	ui.pathSaveBtn->setVisible(visible);
}

void MapWgt::drawAllMapPoint()
{
	if (is_playing_)
		return;
	//每次进入的时候清空
	//清除点
	QMapIterator<int, MapPointWgt*> i(m_pointMap);
	while (i.hasNext())
	{
		i.next();
		i.value()->deleteLater();
	}
	m_pointMap.clear();
	//清除线
	PanoMap_t panoMap = MapPointListManagerIns.getMap();
	for (int j = 0; j < panoMap.panoramaList.size(); j++)
	{
		if (panoMap.panoramaList[j].onMapFlag)
		{
			MapPointWgt *map_point_wgt = new MapPointWgt(this);

			connect(map_point_wgt, SIGNAL(sigOnDoubleCurrMapPoint(const PanoMapPointInfo_t &)), this, SLOT(slotOnDoubleCurrMapPoint(const PanoMapPointInfo_t &)));
			if (current_map_type_ == MAP_CONTROL)
			{
				connect(map_point_wgt, SIGNAL(sigOnDragCurrMapPoint(const PanoMapPointInfo_t &)), this, SLOT(slotOnDragCurrMapPoint(const PanoMapPointInfo_t &)));
				connect(map_point_wgt, SIGNAL(sigOnSettingPointPath(const PanoMapPointInfo_t &)), this, SLOT(slotOnSettingPointPath(const PanoMapPointInfo_t &)));
			}

			map_point_wgt->resize(m_pointWgt_width, m_pointWgt_height); 
			map_point_wgt->setMapPointInfo(panoMap.panoramaList.at(j));
			map_point_wgt->move((int)(panoMap.panoramaList.at(j).pos_x * width()), (int)(panoMap.panoramaList.at(j).pos_y * height()));
			if (panoMap.panoramaList.at(j).map_point_type == DEVICE_ON_LINE)
			{
				map_point_wgt->setMapPointTitle(panoMap.panoramaList.at(j).cameraInfo.name);
				m_pointMap.insert(panoMap.panoramaList.at(j).curr_id, map_point_wgt);
				if (panoMap.panoramaList.at(j).cameraInfo.status)
				{
					map_point_wgt->setMapPointType(DEVICE_ON_LINE);
				}
				else{
					map_point_wgt->setMapPointType(DEVICE_OFF_LINE);
				}
			}
			else if (panoMap.panoramaList.at(j).map_point_type == PANOSCENE_ON_LINE)
			{
				map_point_wgt->setMapPointTitle(panoMap.panoramaList.at(j).sceneInfo.name);
				m_pointMap.insert(panoMap.panoramaList.at(j).curr_id, map_point_wgt);
				map_point_wgt->setMapPointType(PANOSCENE_ON_LINE);
			}
			map_point_wgt->installEventFilter(this);
			map_point_wgt->show();
		}
	}	
}

void MapWgt::reSizeScreen()
{
	if (screen_!=NULL)
	{
		screen_->resize(this->size());
		screen_->resizeMapControl();
	}
	if (replay_ctrl_wgt_!=NULL)
	{
		replay_ctrl_wgt_->resize(this->width(), 136);
		replay_ctrl_wgt_->move(0, this->height() - 136);
		replay_ctrl_wgt_->setSpeedPos(this->width());
	}

	QMapIterator<int, MapPointWgt*> i(m_pointMap);
	while (i.hasNext())
	{
		i.next();
		PanoMapPointInfo_t info;
		i.value()->getMapPointInfo(info);
		i.value()->move((int)(info.pos_x * width()), (int)(info.pos_y * height()));
	}
}

void MapWgt::removePanoDevice(PanoMapPointInfo_t panoInfo)
{
	//移除地图上因移除设备而清除的点信息
	if (panoInfo.onMapFlag)
	{
		emit sigOnModifyState(panoInfo.curr_id);
		QMapIterator<int, float> it(panoInfo.sequencer_point_info_map_);
		while (it.hasNext())
		{
			it.next();
			int key = it.key();
			m_pointMap[key]->removePointInfo(panoInfo.curr_id);
		}
	}

	//移除单例点信息，更新列表和窗口
	QMapIterator<int, MapPointWgt*> i(m_pointMap);
	int index = 0;
	while (i.hasNext())
	{
		i.next();
		PanoMapPointInfo_t info;
		i.value()->getMapPointInfo(info);
		if (info.curr_id == panoInfo.curr_id)
		{
			i.value()->deleteLater();
			emit sigOnRemoveOnMapDevice(info);
			index++;
		}
	}

	if (index)
	{
		m_pointMap.remove(panoInfo.curr_id);
	}

	//更新删除线信息
	if (m_curr_state == COMMON_STATE || m_curr_state == CREATE_PATH)
	{
		QList<int> indexList;
		for (int i = 0; i < pointInfoList_.size(); ++i)
		{
			if (pointInfoList_[i].previousPoint.curr_id == panoInfo.curr_id || pointInfoList_[i].nextPoint.curr_id == panoInfo.curr_id)
			{
				indexList.append(i);
			}
		}
		if (indexList.size() > 0)
		{
			for (int i = 0; i < indexList.size(); ++i)
			{
				//先修改状态，在删除
				MapPointListManagerIns.deleteMapLines(pointInfoList_, indexList[i] - i);
				pointInfoList_.removeAt(indexList[i] - i);
			}
		}
		update();
	}
}

void MapWgt::clearData()
{
	m_curr_state = COMMON_STATE;
	bSelected_ = false;

	QMapIterator<int, MapPointWgt*> i(m_pointMap);
	while (i.hasNext())
	{
		i.next();
		i.value()->deleteLater();
	}
	m_pointMap.clear();
	pointInfoList_.clear();
}

void MapWgt::recoverMapSettings()
{
	pointInfoList_.clear();
	MapPointListManagerIns.getMapLines(pointInfoList_);
	m_curr_state = COMMON_STATE;
	update();
}

void MapWgt::closeGLScreen()
{
	if (screen_ != NULL&&screen_->isPlaying())
	{
		screen_->deleteLater();
		screen_ = NULL;
	}
	if (replay_ctrl_wgt_!=NULL)
	{
		replay_ctrl_wgt_->deleteLater();
		replay_ctrl_wgt_ = NULL;
	}
}

void MapWgt::RePlayRecordTimeSlot()
{
	query_list_.clear();
	query_list_ = TcpDataManagerIns.GetRecordTime();
	replay_server_no_response_ = false;
	m_replayInfoList *info_ = NULL;
	info_ = new m_replayInfoList;
	if (query_list_.size() > 0){
		m_load_state_ = true;
		for (std::vector<api_record_query_respond>::iterator iter = query_list_.begin(); iter != query_list_.end(); iter++)
		{
			m_replayInfo *info = NULL;
			info = new m_replayInfo;
			info->id = iter->nCurRecordSegmentNum;
			//时区转换，减8个小时
			info->startTime = iter->nStartTime - 28800;
			info->endTime = iter->nEndTime - 28800;
			info_->m_infoList.append(*info);
		}
		info_->id = 1;
		info_->duration = replay_ctrl_wgt_->getDurationBySlider();
		m_replay_infoList_.clear();
		m_replay_infoList_.append(*info_);
		replay_ctrl_wgt_->initData(m_replay_infoList_);

		//请求回放时间域成功，启动定时器实时获取
		if (updateTimer_ == NULL)
		{
			updateTimer_ = new QTimer;
			updateTimer_->setInterval(60000);
			connect(updateTimer_, SIGNAL(timeout()), this, SLOT(slotOnRequestReplayTimer()));
		}
		if (!updateTimer_->isActive())
		{
			updateTimer_->start();
			Log::Debug("replay request timer start!");
		}
	}
	else{
		m_load_state_ = false;
		Feedback::instance()->maskUI(REPLAY_REQUEST_FAILED);
	}
	Log::Debug("Get %d time staff", info_->m_infoList.length());
}

void MapWgt::slotOnAddMapPoint(PanoMapPointInfo_t panoramaInfo)
{
	MapPointWgt *map_point_wgt = new MapPointWgt(this);
	map_point_wgt->resize(m_pointWgt_width, m_pointWgt_height);
	connect(map_point_wgt, SIGNAL(sigOnDoubleCurrMapPoint(PanoMapPointInfo_t)), this, SLOT(slotOnDoubleCurrMapPoint(PanoMapPointInfo_t)));
	if (current_map_type_ == MAP_CONTROL)
	{
		connect(map_point_wgt, SIGNAL(sigOnDragCurrMapPoint(PanoMapPointInfo_t)), this, SLOT(slotOnDragCurrMapPoint(PanoMapPointInfo_t)));
		connect(map_point_wgt, SIGNAL(sigOnSettingPointPath(PanoMapPointInfo_t)), this, SLOT(slotOnSettingPointPath(PanoMapPointInfo_t)));
	}	map_point_wgt->setMapPointInfo(panoramaInfo);

	map_point_wgt->move((int)(panoramaInfo.pos_x * width()), (int)(panoramaInfo.pos_y * height()));

	if (panoramaInfo.map_point_type == DEVICE_ON_LINE)
	{
		map_point_wgt->setMapPointTitle(panoramaInfo.cameraInfo.name);
		m_pointMap.insert(panoramaInfo.curr_id, map_point_wgt);
		if (panoramaInfo.cameraInfo.status)
		{
			map_point_wgt->setMapPointType(DEVICE_ON_LINE);
		}
		else{
			map_point_wgt->setMapPointType(DEVICE_OFF_LINE);
		}
	}
	else if (panoramaInfo.map_point_type == PANOSCENE_ON_LINE)
	{
		map_point_wgt->setMapPointTitle(panoramaInfo.sceneInfo.name);
		m_pointMap.insert(panoramaInfo.curr_id, map_point_wgt);
		map_point_wgt->setMapPointType(PANOSCENE_ON_LINE);
	}

	map_point_wgt->installEventFilter(this);
	map_point_wgt->show();

	ViewSignal::instance()->sigOnReportOnMapDevice(panoramaInfo);
}

void MapWgt::slotOnAddMapPointData(PanoMapPointInfo_t panoramaInfo)
{
	//直接拷贝数据，列表id比数据id大1
	MapPointListManagerIns.setMapByPoint(panoramaInfo);
}


void MapWgt::slotOnDragCurrMapPoint(PanoMapPointInfo_t panoramaInfo)
{
	if (current_map_type_ == MAP_CONTROL)
	{
		int key;
		VRMapPointInfo pointInfo;
		PanoMap_t currentMap = MapPointListManagerIns.getMap();

		key = panoramaInfo.curr_id;

		m_curr_pointWgt = m_pointMap[key];
		last_pos_ = m_curr_pointWgt->pos();

		int flag = -1;
		for (int i = 0; i < currentMap.panoramaList.size(); ++i)
		{
			if (currentMap.panoramaList[i].curr_id == key)
			{
				flag = i;
			}
		}
		if (flag > -1)
		{
			m_curr_pointWgt->setMapPointInfo(currentMap.panoramaList[flag]);
		}

		int index = 0;

		PanoMapPointInfo_t info;

		QPoint startPoint;
		QPoint endPoint;
		float angle = 0.0;

		switch (m_curr_state)
		{
		case COMMON_STATE:

			break; 
		case LINK_PATH_STATE:
			//更新单例数据
			m_previous_info = m_curr_selected_info;
			m_curr_selected_info = panoramaInfo;	
		
			pointInfo.previousPoint = m_previous_info;
			pointInfo.nextPoint = m_curr_selected_info;
		   
			//更新地图点信息数据
			startPoint.setX(m_previous_info.pos_x*width());
			startPoint.setY(m_previous_info.pos_y*height());

			endPoint.setX(m_curr_selected_info.pos_x*width());
			endPoint.setY(m_curr_selected_info.pos_y*height());
			angle = commonFun::calculateLineSlope(startPoint, endPoint);
			m_pointMap[m_previous_info.curr_id]->updatePointInfo(m_curr_selected_info.curr_id, angle);
			m_pointMap[m_curr_selected_info.curr_id]->updatePointInfo(m_previous_info.curr_id, angle + 3.14);
			
			MapPointListManagerIns.setLine(m_previous_info, m_curr_selected_info, angle);

            //把对应点的连线组装起来		
			for (int i = 0; i < pointInfoList_.size(); ++i)
			{
				if ((pointInfoList_[i].previousPoint.curr_id == pointInfo.previousPoint.curr_id && pointInfoList_[i].nextPoint.curr_id == pointInfo.nextPoint.curr_id) || 
					pointInfoList_[i].previousPoint.curr_id == pointInfo.nextPoint.curr_id && pointInfoList_[i].nextPoint.curr_id == pointInfo.previousPoint.curr_id)
				{
					index++;
				}
			}
			if (!index)
			{
				pointInfoList_.append(pointInfo);
			}
			update();
			bChanged_ = true;
			break;
		case CREATE_PATH:
			break;
		default:
			break;
		}
	}
}

void MapWgt::slotOnDoubleCurrMapPoint(PanoMapPointInfo_t panoramaInfo)
{
	m_curr_selected_info = panoramaInfo;
	if (current_map_type_ == MAP_PREVIEW)
	{
		if (panoramaInfo.map_point_type == DEVICE_ON_LINE)
		{
			if (panoramaInfo.cameraInfo.status == 0)
			{
				Feedback::instance()->maskUI(OFF_LINE_NO_PLAY);
				return;
			}
		}

		is_playing_ = true;
		if (screen_ != NULL)
		{
			screen_->deleteLater();
			screen_ = NULL;
		}
		screen_ = new playModeWgt(this, true);
		screen_->resize(this->size());
		screen_->setIsPlaying(true);

		connect(screen_, SIGNAL(sigOnResetMapStatus()), this, SLOT(slotOnResetMapStatus()));
		connect(screen_, SIGNAL(sigOnRePaintMap()), this, SLOT( slotOnRePaintMap()));
		connect(screen_, SIGNAL(sigOnOpenReplayCtrl()), this, SLOT(slotOnOpenReplayCtrl()));
		connect(screen_, SIGNAL(sigOnCloseReplayCtrl()), this, SLOT(SlotOnCloseReplayCtrl()));
		
		if (panoramaInfo.map_point_type == DEVICE_ON_LINE)
		{
			screen_->setMapPlayConfig(panoramaInfo);
			screen_->CreatStitchFiles(MAP_PLAY, 0);
		}
		else
		{
			screen_->setMapScenePlayConfig(panoramaInfo);
		}
		screen_->show();
	}
}

void MapWgt::slotOnSettingPointPath(PanoMapPointInfo_t panoramaInfo)
{
	if (current_map_type_ == MAP_CONTROL)
	{
		m_curr_selected_info = panoramaInfo;

		if (m_curr_setting_dlg)
		{
			m_curr_setting_dlg->close();
			m_curr_setting_dlg->deleteLater();
			m_curr_setting_dlg = NULL;
		}

		MapPointSetingWgt *map_point_seting_wgt = new MapPointSetingWgt(this);
		m_curr_setting_dlg = map_point_seting_wgt;
		connect(map_point_seting_wgt, SIGNAL(sigOnGviewBtnClicked()), this, SLOT(slotOnGviewBtnClicked()));
		connect(map_point_seting_wgt, SIGNAL(sigOnConnBtnClicked()), this, SLOT(slotOnConnBtnClicked()));
		connect(map_point_seting_wgt, SIGNAL(sigOnDeleteBtnClicked()), this, SLOT(slotOnDeleteBtnClicked()));
		map_point_seting_wgt->move((int)(panoramaInfo.pos_x * width()) + m_pointWgt_width, (int)(panoramaInfo.pos_y * height()) + 40);
		map_point_seting_wgt->show();
	}
}

void MapWgt::slotOnPicGroupOnClicked(PanoSceneInfo infoItem)
{
	if (screen_ != NULL)
	{
		m_curr_selected_info.sceneInfo.currPicIndex = infoItem.currPicIndex;
		screen_->close();
		slotOnDoubleCurrMapPoint(m_curr_selected_info);
	}
}

void MapWgt::slotOnGviewBtnClicked()
{
	//调整视角
	if (gl_view_setting_wgt_!=NULL)
	{
		gl_view_setting_wgt_->deleteLater();
		gl_view_setting_wgt_ = NULL;
	}
	gl_view_setting_wgt_ = new GlViewSetingWgt(this);
	connect(gl_view_setting_wgt_, SIGNAL(sigOnUpdateInitAngle(float)), m_pointMap[m_curr_selected_info.curr_id], SLOT(slotOnUpdateInitAngle(float)));
	gl_view_setting_wgt_->move(m_curr_setting_dlg->pos());
	gl_view_setting_wgt_->setPanoParam(m_curr_selected_info);
	gl_view_setting_wgt_->show();
}

void MapWgt::slotOnConnBtnClicked()
{
	//路径链接
	m_curr_state = LINK_PATH_STATE;
}

void MapWgt::slotOnDeleteBtnClicked()
{
	//移除相机,只是移除标志位，不在地图上
	MapPointListManagerIns.deletaMapPoint(m_curr_selected_info.curr_id);
	emit sigOnRemoveOnMapDevice(m_curr_selected_info);

	//移除地图上因移除设备而清除的点信息
	QMapIterator<int, float> it(m_curr_selected_info.sequencer_point_info_map_);
	while (it.hasNext())
	{
		it.next();
		int key = it.key();
		m_pointMap[key]->removePointInfo(m_curr_selected_info.curr_id);
	}

	//移除单例中的点信息，更新列表和窗口
	QMapIterator<int, MapPointWgt*> i(m_pointMap);
	int index = 0;
	while (i.hasNext())
	{
		i.next();
		if (i.key() == m_curr_selected_info.curr_id)
		{
			i.value()->deleteLater();
			index++;
		}
	}

	if (index)
	{
		m_pointMap.remove(m_curr_selected_info.curr_id);
	}
	m_curr_pointWgt = NULL;

	//移除新相关信息
	if (m_curr_state == COMMON_STATE || m_curr_state == CREATE_PATH)
	{
		QList<int> indexList;
		for (int i = 0; i < pointInfoList_.size(); ++i)
		{
			if (pointInfoList_[i].previousPoint.curr_id == m_curr_selected_info.curr_id || pointInfoList_[i].nextPoint.curr_id == m_curr_selected_info.curr_id)
			{
				indexList.append(i);
			}
		}
		if (indexList.size() > 0)
		{
			for (int i = 0; i < indexList.size(); ++i)
			{
				//先修改状态，在删除
				pointInfoList_.removeAt(indexList[i] - i);
				MapPointListManagerIns.updateMapLines(pointInfoList_, indexList[i] - i);
			}
		}
		update();
	}
}

void MapWgt::slotOnMapPlayRequestSucceed()
{
	if (screen_)
	{
		screen_->setStitchStatus(StitchStatus::STITCH_STATUS_GET_SRS);
	}
}

void MapWgt::slotOnResetMapStatus()
{
	is_playing_ = false;
}

void MapWgt::slotOnRePaintMap()
{
	drawAllMapPoint();
	//需要关闭回放控制界面
	if (replay_ctrl_wgt_ != NULL)
	{
		replay_ctrl_wgt_->deleteLater();
		replay_ctrl_wgt_ = NULL;
	}	
}

void MapWgt::slotOnOpenReplayCtrl()
{
	screen_->resize(100,200);
	emit ViewSignal::instance()->sigOnResizeMap();


	replay_ctrl_wgt_ = new ReplayCtrWgt(this);
	replay_ctrl_wgt_->resize(this->width(),136);
	replay_ctrl_wgt_->setSpeedPos(this->width());
	replay_ctrl_wgt_->move(0, this->height() - 136);
	replay_ctrl_wgt_->show();

	connect(&TcpDataManagerIns, SIGNAL(RecordTimeReceived()), this, SLOT(RePlayRecordTimeSlot()), Qt::QueuedConnection);

	//查询回放			
	if (SocketManagerIns.isConnected())
	{
		//查询回放接口
		if (query_video_thread_ && query_video_thread_->joinable())
		{
			query_video_thread_->join();
		}
		query_video_thread_.reset(new boost::thread(&MapWgt::QueryForVideo, this));
		replay_server_no_response_ = true;
	}
}



void MapWgt::SlotOnCloseReplayCtrl()
{
	replay_ctrl_wgt_->deleteLater();
	replay_ctrl_wgt_ = NULL;
}


void MapWgt::SendMapDataThreadFunc()
{
	//等待socket起来，大坑
	Sleep(20);

	QString map_data_path = QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS") + "/Map.zip";
	QFile map_data_file(map_data_path);

	//检测文件是否存在
	if (!map_data_file.exists())
	{
		Log::Info("MapWgt::SendMapDataThreadFunc()::Map.zip not exists!!");
		return;
	}

	int map_data_length = map_data_file.size();
	int block_num = map_data_length / API_MAP_DATA_BLOCK_LEN;
	int last_block_length = map_data_length % API_MAP_DATA_BLOCK_LEN;

	//发送数据，先循环发送块，在发送最后一段

	for (int i = 0; i < block_num; i++)
	{	
		protocol_head_t api_head;
		api_detu_vr_map_data_block api_detu;

		api_head.nCmd = CMD_DETU_SEND_MAP_DATA;
		api_head.nDataLen = api_detu.get_size();

		api_detu.length = map_data_length;
		api_detu.offset = API_MAP_DATA_BLOCK_LEN*(i + 1);

		//获取固定长度 API_MAP_DATA_BLOCK_LEN 大小的数据量
		unsigned char *map_data = (unsigned char *)malloc(API_MAP_DATA_BLOCK_LEN);
		memset(map_data, 0, API_MAP_DATA_BLOCK_LEN);
		
		FILE* map_zip = fopen(map_data_path.toLocal8Bit(), "rb");
		if (map_zip)
		{
			fseek(map_zip, api_detu.offset - API_MAP_DATA_BLOCK_LEN, SEEK_SET);
			int sts = fread(map_data, 1, API_MAP_DATA_BLOCK_LEN, map_zip);
			if (sts == 0)
			{
				Log::Debug("sts = fread(map_data, 1, map_data_length, pat_pts) failed");
				fclose(map_zip);
			}
			std::memcpy(api_detu.data, map_data, API_MAP_DATA_BLOCK_LEN);
		}
		fclose(map_zip);
		free(map_data);
		map_data = NULL;

		response res(api_head.get_size() + api_detu.get_size());
		response_add_resprotocol<protocol_head_t>(res, &api_head);
		response_add_resprotocol<api_detu_vr_map_data_block>(res, &api_detu);

		dmconnection* conn = SocketManagerIns.GetDataSocket();
		if (conn != NULL)
		{
			conn->do_write(res);
		}
	}

	//发送最后一段
	if (last_block_length != 0)
	{
		protocol_head_t api_head;
		api_detu_vr_map_data_block api_detu;

		api_head.nCmd = CMD_DETU_SEND_MAP_DATA;
		api_head.nDataLen = api_detu.get_size();

		api_detu.length = map_data_length;
		api_detu.offset = map_data_length;

		//获取固定长度 API_MAP_DATA_BLOCK_LEN 大小的数据量
		unsigned char *map_data = (unsigned char *)malloc(API_MAP_DATA_BLOCK_LEN);
		memset(map_data, 0, API_MAP_DATA_BLOCK_LEN);

		FILE* pat_pts = fopen(map_data_path.toLocal8Bit(), "rb");
		if (pat_pts)
		{
			fseek(pat_pts, map_data_length - last_block_length, SEEK_SET);
			int sts = fread(map_data, 1, last_block_length, pat_pts);
			if (sts == 0)
			{
				Log::Debug("sts = fread(map_data, 1, map_data_length, pat_pts) failed");
				fclose(pat_pts);
			}
			std::memcpy(api_detu.data, map_data, last_block_length);
		}
		fclose(pat_pts);
		free(map_data);
		map_data = NULL;

		response res(api_head.get_size() + api_detu.get_size());
		response_add_resprotocol<protocol_head_t>(res, &api_head);
		response_add_resprotocol<api_detu_vr_map_data_block>(res, &api_detu);

		dmconnection* conn = SocketManagerIns.GetDataSocket();
		if (conn != NULL)
		{
			Log::Debug("MapWgt::send_data_thread() :send last block!");
			conn->do_write(res);
		}
	}
}

void MapWgt::SlotOnSaveMapData()
{
	MapPointListManagerIns.setMapBuilt(true);

	//保存单例中的current_map_
	MapPointListManagerIns.addMapList();
	Feedback::instance()->maskUI(MAP_SAVE_OK);

	//压缩Map文件夹
	JlCompress::compressDir(QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS")+"/Map.zip", QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/Map")); //压缩
	//JlCompress::extractDir("d:\\test.zip", "d:\\test");//解压缩  
	
	//发送压缩包文件
	if (senddata_thread_ && senddata_thread_->joinable())
	{
		senddata_thread_->join();
	}
	senddata_thread_.reset(new boost::thread(&MapWgt::SendMapDataThreadFunc, this));
}

void MapWgt::mousePressEvent(QMouseEvent *event)
{
	int index = -1;
	if (event->type() == QEvent::MouseButtonPress){
		if (current_map_type_ == MAP_CONTROL){
			if (event->button() == Qt::LeftButton)
			{
				if (m_curr_setting_dlg && m_curr_setting_dlg->isVisible())
				{
					if (event->pos().x() <m_curr_setting_dlg->pos().x() || event->pos().y() < m_curr_setting_dlg->pos().y() ||
						event->pos().x() > m_curr_setting_dlg->pos().x() + m_curr_setting_dlg->width() ||
						event->pos().y() > m_curr_setting_dlg->pos().y() + m_curr_setting_dlg->height())
					{
						m_curr_setting_dlg->close();
						m_curr_setting_dlg->deleteLater();
						m_curr_setting_dlg = NULL;
					}
				}
				if (gl_view_setting_wgt_ && gl_view_setting_wgt_->isVisible())
				{
					if (event->pos().x() < gl_view_setting_wgt_->pos().x() || event->pos().y() < gl_view_setting_wgt_->pos().y() ||
						event->pos().x() > gl_view_setting_wgt_->pos().x() + gl_view_setting_wgt_->width() ||
						event->pos().y() > gl_view_setting_wgt_->pos().y() + gl_view_setting_wgt_->height())
					{
						gl_view_setting_wgt_->deleteLater();
						gl_view_setting_wgt_ = NULL;
					}
				}
			}

			switch (m_curr_state)
			{
			case COMMON_STATE:							
			{
				delta_pos_ = last_pos_ - event->pos();
				if (event->button() == Qt::LeftButton)
				{
					for (int i = 0; i < pointInfoList_.size(); ++i)
					{
						QPolygonF polygon(pointInfoList_[i].pointEnterArea);
						if (polygon.containsPoint(event->pos(), Qt::OddEvenFill))
						{
							index = i;
							break;
						}
					}

					if (index >= 0)
					{
						//先修改状态，在删除
						MapPointListManagerIns.deleteMapLines(pointInfoList_, index);
						pointInfoList_.removeAt(index);
						setCursor(Qt::ArrowCursor);
					}
				}
			}
				break;
			case LINK_PATH_STATE:
			{
									if (event->button() == Qt::RightButton)
									{
										m_curr_state = COMMON_STATE;
									}
									else if (event->button() == Qt::LeftButton)
									{
										if (bChanged_)
										{
											m_curr_state = CREATE_PATH;
											bChanged_ = false;
										}
									}
			}
				break;
			case CREATE_PATH:
			{
								if (event->button() == Qt::LeftButton)
								{
									for (int i = 0; i < pointInfoList_.size(); ++i)
									{
										QPolygonF polygon(pointInfoList_[i].pointEnterArea);
										if (polygon.containsPoint(event->pos(), Qt::OddEvenFill))
										{
											index = i;
											break;
										}
									}
									if (index >= 0)
									{
										//先修改状态，在删除
										MapPointListManagerIns.deleteMapLines(pointInfoList_,index);
										pointInfoList_.removeAt(index);
										setCursor(Qt::ArrowCursor);
									}
								}
								m_curr_state = COMMON_STATE;
			}
				break;
			default:
				break;
			}
			update();
		}
	}
	QWidget::mousePressEvent(event);
}

void MapWgt::mouseMoveEvent(QMouseEvent *event)
{
	m_curr_point = event->pos();
	if (current_map_type_ == MAP_CONTROL){
		switch (m_curr_state)
		{
		case COMMON_STATE:
		{
			if (event->buttons() & Qt::LeftButton)
			{
				if (m_curr_pointWgt)
				{
					PanoMapPointInfo_t info;
					m_curr_pointWgt->getMapPointInfo(info);

					if (info.sequencer_point_info_map_.isEmpty())
					{
						m_curr_pointWgt->move(event->pos() + delta_pos_);
						m_curr_pointWgt->updatePoint(m_curr_point + delta_pos_, width(), height());
						float pos_x = (event->pos() + delta_pos_).x() * 1.0 / width();
						float pos_y = (event->pos() + delta_pos_).y() * 1.0 / height();
						MapPointListManagerIns.setMapPointPos(info.curr_id, pos_x, pos_y);
					}

					else
					{
						//以后在添加连线移动，同时需要修改若干连线
						return;
						int pos_x = event->pos().x() * 1.0 / width();
						int pos_y = event->pos().y() * 1.0 / height();

					}
				}
			}
			else
			{
				for (int i = 0; i < pointInfoList_.size(); ++i)
				{
					QPolygonF polygon(pointInfoList_[i].pointEnterArea);
					if (polygon.containsPoint(event->pos(), Qt::OddEvenFill))
					{
						setCursor(QPixmap(":/image/image/deletePath.png"));
						pointInfoList_[i].bSelected = true;
						break;
					}
					else
					{
						setCursor(Qt::ArrowCursor);
						pointInfoList_[i].bSelected = false;
					}
				}
			}
		}
		
			break;
		case LINK_PATH_STATE:
			break;
		case CREATE_PATH:
		{
			for (int i = 0; i < pointInfoList_.size(); ++i)
			{
				QPolygonF polygon(pointInfoList_[i].pointEnterArea);
				if (polygon.containsPoint(event->pos(), Qt::OddEvenFill))
				{
					setCursor(QPixmap(":/image/image/deletePath.png"));
					pointInfoList_[i].bSelected = true;
					break;
				}
				else
				{
					setCursor(Qt::ArrowCursor);
					pointInfoList_[i].bSelected = false;
				}
			}
		}
			break;
		default:
			break;
		}
		update();
	}
	QWidget::mouseMoveEvent(event);
}

void MapWgt::mouseReleaseEvent(QMouseEvent *event)
{
	if (current_map_type_ == MAP_CONTROL){
		switch (m_curr_state)
		{
		case COMMON_STATE:
			if (m_curr_pointWgt)
			{
				m_curr_pointWgt = NULL;
			}
			break;
		case LINK_PATH_STATE:
			break;
		case CREATE_PATH:
			break;
		default:
			break;
		}
	}

	QWidget::mouseReleaseEvent(event);
}

void MapWgt::dropEvent(QDropEvent *event)
{
	commonListWidget *source = qobject_cast<commonListWidget *>(event->source());
	if (source) {
		panoramaItemWidget *itemWgt = qobject_cast<panoramaItemWidget *>(source->itemWidget(source->currentItem()));
		itemWgt->setNewHidden(true);
		QListWidgetItem *item = source->currentItem();
		QPoint temp_pos = event->pos();
		//QPoint globel_temp_pos = event->globalPos();
		event->setDropAction(Qt::MoveAction);
		event->accept();

		PanoMapPointInfo_t panoramaInfo;
		itemWgt->getItemData(panoramaInfo);

		//传入单例数据
		panoramaInfo.pos_x = event->pos().x() * 1.0 / this->width();
		panoramaInfo.pos_y = event->pos().y() * 1.0 / this->height();

		emit sigOnAddMapPoint(panoramaInfo);

	}
}

void MapWgt::dragEnterEvent(QDragEnterEvent *event)
{
// 	/*event->acceptProposedAction();//接受拖动动作*/
	commonListWidget *source = qobject_cast<commonListWidget *>(event->source());
	if (source) {
		panoramaItemWidget *itemWgt = qobject_cast<panoramaItemWidget *>(source->itemWidget(source->currentItem()));
		if (itemWgt->getNewHidden())
		{
			event->ignore();
		}
		else
		{
			event->setDropAction(Qt::MoveAction);
			event->accept();
		}
	}
}

void MapWgt::dragMoveEvent(QDragMoveEvent *event)
{
// 	commonListWidget *source =
// 		qobject_cast<commonListWidget *>(event->source());
// 	if (source) {
// 		event->setDropAction(Qt::MoveAction);
 		event->accept();
// 	}
}

void MapWgt::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	int startPosX = -1;
	int startPosY = -1;
	int endPosX = -1;
	int endPosY = -1;
	QVector<QPointF> pointF;

	if (current_map_type_ == MAP_CONTROL){
		QList<PanoMap_t> panoMapList(MapPointListManagerIns.getMapList());
		switch (m_curr_state)
		{
		case COMMON_STATE:
			for (int i = 0; i < pointInfoList_.size(); ++i)
			{
				if (pointInfoList_[i].bSelected){
					painter.setPen(QPen(QBrush("#00A294"), 3, Qt::DotLine));
				}
				else{
					painter.setPen(QPen(QBrush("#00A294"), 3, Qt::SolidLine));
				}
			
				startPosX = (int)(pointInfoList_[i].previousPoint.pos_x * width()) + m_pointWgt_width / 2;
				startPosY = (int)(pointInfoList_[i].previousPoint.pos_y * height()) + m_pointWgt_height - 18;
				endPosX = (int)(pointInfoList_[i].nextPoint.pos_x * width()) + m_pointWgt_width / 2;
				endPosY = (int)(pointInfoList_[i].nextPoint.pos_y * height()) + m_pointWgt_height - 18;
				painter.drawLine(QPoint(startPosX, startPosY), QPoint(endPosX, endPosY));

				painter.setPen(QPen(QBrush(Qt::transparent), 1, Qt::SolidLine));
				painter.setBrush(QBrush(Qt::transparent, Qt::VerPattern));//设置画刷形式

				QPointF points[4] = {
					QPointF(startPosX - space, startPosY - space),
					QPointF(startPosX + space, startPosY + space),
					QPointF(endPosX + space, endPosY + space),
					QPointF(endPosX - space, endPosY - space)
				};

				painter.drawPolygon(points, 4);
			}
			break;
		case LINK_PATH_STATE:
			for (int i = 0; i < pointInfoList_.size(); ++i)
			{
				painter.setPen(QPen(QBrush("#00A294"), 3, Qt::SolidLine));
				startPosX = (int)(pointInfoList_[i].previousPoint.pos_x * width()) + m_pointWgt_width / 2;
				startPosY = (int)(pointInfoList_[i].previousPoint.pos_y * height()) + m_pointWgt_height - 18;
				endPosX = (int)(pointInfoList_[i].nextPoint.pos_x * width()) + m_pointWgt_width / 2;
				endPosY = (int)(pointInfoList_[i].nextPoint.pos_y * height()) + m_pointWgt_height - 18;
				painter.drawLine(QPoint(startPosX, startPosY), QPoint(endPosX, endPosY));

				painter.setPen(QPen(QBrush(Qt::transparent), 1, Qt::SolidLine));
				painter.setBrush(QBrush(Qt::transparent, Qt::VerPattern));//设置画刷形式

				QPointF points[4] = {
					QPointF(startPosX - space, startPosY - space),
					QPointF(startPosX + space, startPosY + space),
					QPointF(endPosX + space, endPosY + space),
					QPointF(endPosX - space, endPosY - space)
				};

				painter.drawPolygon(points, 4);
			}

			painter.setPen(QPen(QBrush("#00A294"), 2, Qt::SolidLine));
			painter.drawLine(QPoint((int)(m_curr_selected_info.pos_x * width()) + m_pointWgt_width / 2, (int)(m_curr_selected_info.pos_y * height()) + m_pointWgt_height - 18), m_curr_point);
			break;
		case CREATE_PATH:

			for (int i = 0; i < pointInfoList_.size(); ++i)
			{
				pointF.clear();
				if (pointInfoList_[i].bSelected){
					painter.setPen(QPen(QBrush("#00A294"), 3, Qt::DotLine));
				}
				else{
					painter.setPen(QPen(QBrush("#00A294"), 3, Qt::SolidLine));
				}

				startPosX = (int)(pointInfoList_[i].previousPoint.pos_x * width()) + m_pointWgt_width / 2;
				startPosY = (int)(pointInfoList_[i].previousPoint.pos_y * height()) + m_pointWgt_height - 18;
				endPosX = (int)(pointInfoList_[i].nextPoint.pos_x * width()) + m_pointWgt_width / 2;
				endPosY = (int)(pointInfoList_[i].nextPoint.pos_y * height()) + m_pointWgt_height - 18;
				painter.drawLine(QPoint(startPosX, startPosY), QPoint(endPosX, endPosY));

				painter.setPen(QPen(QBrush(Qt::transparent), 1, Qt::SolidLine));
				painter.setBrush(QBrush(Qt::transparent, Qt::VerPattern));//设置画刷形式

				QPointF points[4] = {
					QPointF(startPosX - space, startPosY - space),
					QPointF(startPosX + space, startPosY + space),
					QPointF(endPosX + space, endPosY + space),
					QPointF(endPosX - space, endPosY - space)
				};
				pointF.append(QPointF(startPosX - space, startPosY - space));
				pointF.append(QPointF(startPosX + space, startPosY + space));
				pointF.append(QPointF(endPosX + space, endPosY + space));
				pointF.append(QPointF(endPosX - space, endPosY - space));
				pointInfoList_[i].pointEnterArea = pointF;

				MapPointListManagerIns.updateMapLines(pointInfoList_, 0);
				painter.drawPolygon(points, 4);
			}
			break;
		}
	}
	else if (current_map_type_ == MAP_PREVIEW){

		PanoMap_t panoMap = MapPointListManagerIns.getMap();
		painter.setPen(QPen(QBrush("#00A294"), 3, Qt::SolidLine));

		for (int i = 0; i < panoMap.mapLinesList.size(); ++i)
		{
			startPosX = (int)(panoMap.mapLinesList[i].previousPoint.pos_x * width()) + m_pointWgt_width / 2;
			startPosY = (int)(panoMap.mapLinesList[i].previousPoint.pos_y * height()) + m_pointWgt_height - 18;
			endPosX = (int)(panoMap.mapLinesList[i].nextPoint.pos_x * width()) + m_pointWgt_width / 2;
			endPosY = (int)(panoMap.mapLinesList[i].nextPoint.pos_y * height()) + m_pointWgt_height - 18;
			painter.drawLine(QPoint(startPosX, startPosY), QPoint(endPosX, endPosY));
		}
	}
}
