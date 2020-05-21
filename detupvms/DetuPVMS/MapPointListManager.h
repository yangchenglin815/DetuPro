/************************************************
* \file ListAndGLWindowManager.h
*
* \author HuZhengdong
* \date 20171202
* 地图点列表全局单例类，保存单张地图所有点信息
* 可扩展成多张地图
************************************************/

#pragma once

#include <iostream>
#include <string>
#include <map>
#include <QObject>
#include <memory>

#include "UiSingleton.h"
#include "constStruct.h"
#include "APIProtocol.h"

using namespace dm::server;
#define  MapPointListManagerIns MapPointListManager::Instance()

class MapPointListManager : public QObject, public CUiSingleton<MapPointListManager>
{
	Q_OBJECT
		friend class CUiSingleton<MapPointListManager>;
public:
	MapPointListManager();

	void updateMap(PanoMap_t current_map);
	void setMap(PanoMap_t current_map);
	void setMapByPoint(PanoMapPointInfo point);
	void updatePtzData(std::vector<PTZManageTable_t> ptzList);
	void updateSpyData(std::vector<SPYManageTable_t> spyList);
	void updatePtzAndSpyData(QList<deviceInfo> deviceList);

	void updateMapLines(const QList<VRMapPointInfo> &mapLinesList,int index);
	void deleteMapLines(const QList<VRMapPointInfo> &mapLinesList, int index);
	void getMapLines(QList<VRMapPointInfo> &mapLinesList);

	void setLine(const PanoMapPointInfo &prev, const PanoMapPointInfo &next,float angle);

	void setMapPointPos(int id, float pos_x, float pos_y);
	void deletaMapPoint(int id);
	void removeMapDevice(int id);


	PanoMap_t getMap(){	return current_map_;};


	void setMapList(QList<PanoMap_t>list);
	void getMapListFromLocal();

	bool findMapExist(QString path);

	void addMapList();
	QList<PanoMap_t> getMapList(){ return m_panoMapList; };

	void setMapBuilt(bool is_built);
	bool isMapBuilt()	{ return is_map_built_; };

	void setInitAngle(int id,float angle);

	void clear();

	void writeJsonFromMap();

private:

	int find(int id);
private:


	//地图列表，包含每张地图的点列表
	QList<PanoMap_t> m_panoMapList;

	//当前设置的地图
	PanoMap_t current_map_;

	//当前客户端是否设置地图标志位
	bool is_map_built_;

	bool is_map_added_;

};

