/************************************************
* \file MapWgt.h
*
* \author HuZhengdong
* \date 20171130
* 地图窗口
************************************************/
#ifndef MAPWGT_H
#define MAPWGT_H

#include <QWidget>
#include <QGraphicsScene> 
#include <QGraphicsView>

#include "ui_MapWgt.h"

#include "APIProtocol.h"
#include "constStruct.h"
#include "VRMap/MapPointSetingWgt.h"

#include "tcpclient.hpp"

using namespace dm::server;
using namespace dm::client;

class playModeWgt;
class ReplayCtrWgt;
class MinimapWgt;
class MapPointWgt;
class GlViewSetingWgt;

class MapWgt : public QWidget
{
	Q_OBJECT

public:
	MapWgt(QWidget *parent = 0);
	~MapWgt();

	void init();
	void initConnect();
	



	//设置当前是控制界面，或者预览界面
	void setMapType(MapType maptype);

	void setButtonVisible(bool visible);

	//预览界面，绘制地图点
	void drawAllMapPoint();

	void reSizeScreen();

	void removePanoDevice(PanoMapPointInfo_t panoInfo);

	void clearData();

	void recoverMapSettings();  //还原地图配置

	void closeGLScreen();

	void QueryForVideo();

public slots:

	void RePlayRecordTimeSlot();
	//控制界面
	void slotOnAddMapPoint(PanoMapPointInfo_t panoramaInfo);
	void slotOnAddMapPointData(PanoMapPointInfo_t panoramaInfo);
	void slotOnDragCurrMapPoint(PanoMapPointInfo_t panoramaInfo);
	void slotOnDoubleCurrMapPoint(PanoMapPointInfo_t panoramaInfo);
	void slotOnSettingPointPath(PanoMapPointInfo_t panoramaInfo);

	void slotOnPicGroupOnClicked(PanoSceneInfo infoItem);
	//控制框
	void slotOnGviewBtnClicked();
	void slotOnConnBtnClicked();
	void slotOnDeleteBtnClicked();

	void slotOnMapPlayRequestSucceed();

	//关闭预览的时候通知标志位
	void slotOnResetMapStatus();
	void slotOnRePaintMap();
	void slotOnOpenReplayCtrl();
	void SlotOnCloseReplayCtrl();

private:
	void SendMapDataThreadFunc();

private slots:
	//地图路径数据生成
	void SlotOnSaveMapData();

protected:
	void dropEvent(QDropEvent *event);
	void dragEnterEvent(QDragEnterEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);

	void paintEvent(QPaintEvent *event);

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

signals:
	void sigOnAddMapBtnClicked();
	void sigOnBuildMapPath();

	//检测到地图拖入，添加地图
	void sigOnAddMapPoint(PanoMapPointInfo_t panoramaInfo);

	//检测到地图拖入，添加地图数据
	void sigOnRemoveOnMapDevice(PanoMapPointInfo_t panoInfo);

	void sigOnModifyState(int id);


private:
	Ui::MapWgt ui;

	playModeWgt *screen_;

	ReplayCtrWgt *replay_ctrl_wgt_;

	boost::shared_ptr<boost::thread> query_video_thread_;
	bool replay_server_no_response_;
	std::vector<api_record_query_respond> query_list_;
	bool m_load_state_;
	//回放录像时间段列表
	QList<m_replayInfoList> m_replay_infoList_;
	//定时器-实时刷新回放时间域
	QTimer *updateTimer_;

	//设置当前是控制窗口或者预览窗口
	MapType current_map_type_;

	QMap<int, MapPointWgt*> m_pointMap;
	MapPointWgt *m_curr_pointWgt;

	//记录鼠标的位置，移动的时候让地图点不跳

	QPoint delta_pos_;				
	QPoint last_pos_;

	int m_curr_state;
	QPoint m_curr_point;
	PanoMapPointInfo_t m_curr_selected_info;
	PanoMapPointInfo_t m_previous_info;
	int m_pointWgt_width;
	int m_pointWgt_height;
	bool bSelected_;
	QList<VRMapPointInfo> pointInfoList_;

	MapPointSetingWgt *m_curr_setting_dlg;

	bool bChanged_;

	bool is_playing_;

	GlViewSetingWgt *gl_view_setting_wgt_;
	

	boost::shared_ptr<boost::thread> tcpclient_thread_;
	boost::shared_ptr<boost::thread> senddata_thread_;
};

#endif // MAPWGT_H
