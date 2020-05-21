#include <QJsonDocument> 
#include <QJsonObject> 
#include <QJsonArray>
#include <QtGlobal>

#include "MapPointListManager.h"
#include "commonFun.h"
#include "logging.hpp"
#include "ViewSignal.h"


MapPointListManager::MapPointListManager():
is_map_built_(false)
{
}


void MapPointListManager::updateMap(PanoMap_t map)
{
	current_map_ = map;

}

void MapPointListManager::setMap(PanoMap_t current_map)
{
	current_map_ = current_map;
	ViewSignal::instance()->sigOnUpdateMapData();
}

void MapPointListManager::setMapByPoint(PanoMapPointInfo point)
{
	int i = find(point.curr_id);
	current_map_.panoramaList[i] = point;
}



void MapPointListManager::updatePtzData(std::vector<PTZManageTable_t> ptzList)
{
	for (int i = 0; i < current_map_.panoramaList.size(); ++i)
	{
		if (current_map_.panoramaList[i].map_point_type == DEVICE_ON_LINE || current_map_.panoramaList[i].map_point_type == DEVICE_OFF_LINE)
		{
			current_map_.panoramaList[i].cameraInfo.m_PtzInfoList.clear();
			for (std::vector<PTZManageTable_t>::iterator iter = ptzList.begin(); iter != ptzList.end(); iter++)
			{
				PtzInfo skt_t1;
				skt_t1.pvsID = QString::fromStdString((char*)iter->pvsID);
				skt_t1.sUserName = QString::fromStdString((char*)iter->username);
				skt_t1.sPasswd = QString::fromStdString((char*)iter->passwd);
				skt_t1.sIP = QString::fromStdString((char*)iter->nIP);
				skt_t1.wPort = iter->nPort;

				QString pvsID = QString::fromStdString((char*)iter->pvsID);
				if (pvsID == current_map_.panoramaList[i].cameraInfo.serialNo)
				{
					current_map_.panoramaList[i].cameraInfo.m_PtzInfoList.append(skt_t1);
				}
			}
		}
	}
}

void MapPointListManager::updateSpyData(std::vector<SPYManageTable_t> spyList)
{
	for (int i = 0; i < current_map_.panoramaList.size(); ++i)
	{
		if (current_map_.panoramaList[i].map_point_type == DEVICE_ON_LINE || current_map_.panoramaList[i].map_point_type == DEVICE_OFF_LINE)
		{
			current_map_.panoramaList[i].cameraInfo.m_SpyInfoList.clear();
			for (std::vector<SPYManageTable_t>::iterator iter = spyList.begin(); iter != spyList.end(); iter++)
			{
				SpyInfo skt_t1;
				skt_t1.pvsID = QString::fromStdString((char*)iter->pvsID);
				skt_t1.sUserName = QString::fromStdString((char*)iter->username);
				skt_t1.sPasswd = QString::fromStdString((char*)iter->passwd);
				skt_t1.sIP = QString::fromStdString((char*)iter->nIP);
				skt_t1.wPort = iter->nPort;

				QString pvsID = QString::fromStdString((char*)iter->pvsID);
				if (pvsID == current_map_.panoramaList[i].cameraInfo.serialNo)
				{
					current_map_.panoramaList[i].cameraInfo.m_SpyInfoList.append(skt_t1);
				}
			}
		}
	}
}

void MapPointListManager::updatePtzAndSpyData(QList<deviceInfo> deviceList)
{
	for (int i = 0; i < deviceList.size(); ++i)
	{
		for (int j = 0; j < current_map_.panoramaList.size(); ++j)
		{
			if (current_map_.panoramaList[j].map_point_type == DEVICE_ON_LINE || current_map_.panoramaList[j].map_point_type == DEVICE_OFF_LINE)
			{
				if (deviceList[i].serialNo == current_map_.panoramaList[j].cameraInfo.serialNo)
				{
					current_map_.panoramaList[j].cameraInfo.m_PtzInfoList = deviceList[i].m_PtzInfoList;
					current_map_.panoramaList[j].cameraInfo.m_SpyInfoList = deviceList[i].m_SpyInfoList; 
					Log::Info("updatePtzAndSpyData");

				}
			}
		}
	}
}

void MapPointListManager::updateMapLines(const QList<VRMapPointInfo> &mapLinesList, int index)
{
	current_map_.mapLinesList = mapLinesList;
	ViewSignal::instance()->sigOnUpdateMapData();

}

void MapPointListManager::deleteMapLines(const QList<VRMapPointInfo> &mapLinesList, int index)
{
	current_map_.mapLinesList.removeAt(index);

	if (index >= 0)
	{
		int pre_id = mapLinesList[index].previousPoint.curr_id;
		int next_id = mapLinesList[index].nextPoint.curr_id;

		int i = find(pre_id);
		current_map_.panoramaList[i].sequencer_point_info_map_.remove(next_id);

		int j = find(next_id);
		current_map_.panoramaList[j].sequencer_point_info_map_.remove(pre_id);


	}

	ViewSignal::instance()->sigOnUpdateMapData();
}

void MapPointListManager::getMapLines(QList<VRMapPointInfo> &mapLinesList)
{
	mapLinesList = current_map_.mapLinesList;
}


void MapPointListManager::setLine(const PanoMapPointInfo &prev, const PanoMapPointInfo &next, float angle)
{

	int i = find(prev.curr_id);
	current_map_.panoramaList[i].sequencer_point_info_map_.insert(next.curr_id, angle);

	int j = find(next.curr_id);
	current_map_.panoramaList[j].sequencer_point_info_map_.insert(prev.curr_id, angle + 3.14);
}

void MapPointListManager::setMapPointPos(int id, float pos_x, float pos_y)
{
	int i = find(id);
	current_map_.panoramaList[i].pos_x = pos_x;
	current_map_.panoramaList[i].pos_y = pos_y;
	
	ViewSignal::instance()->sigOnUpdateMapData();
}

void MapPointListManager::deletaMapPoint(int id)
{
	int i = find(id);
	//删除前一个，再删除后一个
	QMap<int, float>::const_iterator j = current_map_.panoramaList[i].sequencer_point_info_map_.constBegin();
	while (j != current_map_.panoramaList[i].sequencer_point_info_map_.constEnd())
	{

		int key = j.key();
		int k = find(key);
		current_map_.panoramaList[k].sequencer_point_info_map_.remove(id);

		++j;
	}

	current_map_.panoramaList[i].sequencer_point_info_map_.clear();
	current_map_.panoramaList[i].onMapFlag = false;

	ViewSignal::instance()->sigOnUpdateMapData();
}

void MapPointListManager::removeMapDevice(int id)
{
	int i = find(id);
	current_map_.panoramaList.removeAt(i);

	for (int i = 0; i < current_map_.panoramaList.size(); ++i)
	{
		current_map_.panoramaList[i].sequencer_point_info_map_.remove(id);
	}

	ViewSignal::instance()->sigOnUpdateMapData();
}

void MapPointListManager::setMapList(QList<PanoMap_t>list)
{
	m_panoMapList = list;
}

void MapPointListManager::getMapListFromLocal()
{
	m_panoMapList.clear();
	commonFun::resolveFromJsonFunc(m_panoMapList);
}

bool MapPointListManager::findMapExist(QString path)
{
	for (int i = 0; i < m_panoMapList.size(); ++i)
	{
		if (m_panoMapList[i].mapPath == path)
		{
			current_map_ = m_panoMapList[i];
			return true;
		}
	}
	return false;
}

void MapPointListManager::addMapList()
{
	is_map_added_ = false;
	if (m_panoMapList.size()==0){
		m_panoMapList.append(current_map_);
	}
	else{
		for (int i = 0; i < m_panoMapList.size(); i++){
			if (m_panoMapList.at(i).mapName == current_map_.mapName){
				m_panoMapList.replace(i, current_map_);
				is_map_added_ = true;
			}
		}
		if (is_map_added_==false){
			m_panoMapList.append(current_map_);
		}
	}
	commonFun::generateToJsonFunc(m_panoMapList);

}

void MapPointListManager::setMapBuilt(bool is_built)
{
	is_map_built_ = is_built;
}

void MapPointListManager::setInitAngle(int id, float angle)
{
	int i = find(id);
	current_map_.panoramaList[i].initial_angle = angle;
}

void MapPointListManager::clear()
{
	current_map_.clear();
}

void MapPointListManager::writeJsonFromMap()
{

}

int MapPointListManager::find(int id)
{
	for (int i = 0; i < current_map_.panoramaList.size(); i++)
	{
		if (current_map_.panoramaList[i].curr_id == id)
		{
			return i;
		}
	}
	return -1;
}

