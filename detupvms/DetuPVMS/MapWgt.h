/************************************************
* \file MapWgt.h
*
* \author HuZhengdong
* \date 20171130
* ��ͼ����
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
	



	//���õ�ǰ�ǿ��ƽ��棬����Ԥ������
	void setMapType(MapType maptype);

	void setButtonVisible(bool visible);

	//Ԥ�����棬���Ƶ�ͼ��
	void drawAllMapPoint();

	void reSizeScreen();

	void removePanoDevice(PanoMapPointInfo_t panoInfo);

	void clearData();

	void recoverMapSettings();  //��ԭ��ͼ����

	void closeGLScreen();

	void QueryForVideo();

public slots:

	void RePlayRecordTimeSlot();
	//���ƽ���
	void slotOnAddMapPoint(PanoMapPointInfo_t panoramaInfo);
	void slotOnAddMapPointData(PanoMapPointInfo_t panoramaInfo);
	void slotOnDragCurrMapPoint(PanoMapPointInfo_t panoramaInfo);
	void slotOnDoubleCurrMapPoint(PanoMapPointInfo_t panoramaInfo);
	void slotOnSettingPointPath(PanoMapPointInfo_t panoramaInfo);

	void slotOnPicGroupOnClicked(PanoSceneInfo infoItem);
	//���ƿ�
	void slotOnGviewBtnClicked();
	void slotOnConnBtnClicked();
	void slotOnDeleteBtnClicked();

	void slotOnMapPlayRequestSucceed();

	//�ر�Ԥ����ʱ��֪ͨ��־λ
	void slotOnResetMapStatus();
	void slotOnRePaintMap();
	void slotOnOpenReplayCtrl();
	void SlotOnCloseReplayCtrl();

private:
	void SendMapDataThreadFunc();

private slots:
	//��ͼ·����������
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

	//��⵽��ͼ���룬��ӵ�ͼ
	void sigOnAddMapPoint(PanoMapPointInfo_t panoramaInfo);

	//��⵽��ͼ���룬��ӵ�ͼ����
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
	//�ط�¼��ʱ����б�
	QList<m_replayInfoList> m_replay_infoList_;
	//��ʱ��-ʵʱˢ�»ط�ʱ����
	QTimer *updateTimer_;

	//���õ�ǰ�ǿ��ƴ��ڻ���Ԥ������
	MapType current_map_type_;

	QMap<int, MapPointWgt*> m_pointMap;
	MapPointWgt *m_curr_pointWgt;

	//��¼����λ�ã��ƶ���ʱ���õ�ͼ�㲻��

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
