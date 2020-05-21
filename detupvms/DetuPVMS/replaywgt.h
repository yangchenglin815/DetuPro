/************************************************
* \file replaywgt.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* 回放页面窗口
************************************************/
#ifndef REPLAYWGT_H
#define REPLAYWGT_H

#include <QWidget>
#include <QListWidgetItem>
#include <QMouseEvent>

#include "calendarWidget.h"
#include "constStruct.h"
#include "ui_replaywgt.h"
#include "APIProtocol.h"
#include "Preview/deviceItemWidget.h"

#include <QTimer>

using namespace dm::server;

namespace Ui {
	class replayWgt;
}

class replayWgt : public QWidget
{
	Q_OBJECT

	enum RePlayCurrentSelectGLWindow
	{
		RePlayGL0 = 0,
		RePlayGL1 = 1,
		RePlayGL2,
		RePlayGL3,
		RePlayGL4,
	};

	//回放状态机枚举
	enum RePlayDoubleClickToPlayStatus
	{
		REPLAY_DOUBLE_CLICK_TO_PLAY_STATUS_START = 0,			//初始状态	
		REPLAY_DOUBLE_CLICK_TO_PLAY_STATUS_COMMUNICATION,		//通信状态
		REPLAY_DOUBLE_CLICK_TO_PLAY_STATUS_GET_SRS,			//获取SRS回调状态
		REPLAY_DOUBLE_CLICK_TO_PLAY_STATUS_STITCH,				//拼接状态
	};

public:
	replayWgt(QWidget *parent = 0);
	~replayWgt();

	void QueryForVideo();
	//关闭播放器功能
	void closeReplaySourse(int glwindow_num);
	//暂停播放器
	void pausePlayer(int glwindow_num, bool reset);
	//列表数据处理
	void initData(const QList<deviceInfo> &itemInfoList);
	void getSelectId(int selectId);
	void RePlayUpdateListSlot(QList<deviceInfo> deviceList);
	void setSpeedPos(int w);
	void clearPlayerStatus();
	void setPosMove();
	void setTimePos();
	void setHiddenTime(bool visible);
	void closePlayer();
	void setMoveEnabled(bool enable);
	void setReplayStatusShowLabel(PLAY_STATUS play_status);
signals:
	void sigOnReplaySwitchViewMode(PanoViewMode view_mode);

	void sigOnTransportList(QList<deviceInfo> deviceList);

	void sigOnSwitchRePlayFlag(bool play_flag);
	void sigOnOptMizeSuccess();
	void sigOnNetWorkResponse();
public slots:
	void RePlayRecordTimeSlot();
	//单路模式
	void slot_singleModeSelected();
	//四路模式
	void slot_fourModeSelected();
	//打开某路的球机联动模式
	void slot_openOneBallCam();
	//关闭球机联动模式
	void slot_closeOneBallCam();
	//原图模式
	void slot_originModeSelected();
	//360模式
	void slot_360ModeSelected();
	//全屏模式
	void slot_fullOfScreen();
	void initFullofScreen();
	//请求回复录像
	void slotOnRequestReplayRadio(int time, int duration);
	//获取回放视频实时时间
	void slotOnGetRecordTime(int time);
	//显示日历
	void slotOnShowCalendar();
	//
	void slotOnResetStatus(int item_num);
	void slotOnPlayStatus();
	void slotOnFastPlay();
	void slotOnSlowPlay();
	void slotOnGetPlaybackRes(bool is_ok);
	void slotOnRecordRequestFailed();
	void slotOnCloseSubStreamClearPlayer(int id);
	void slotOnRebootM1ResetPlayer(int id);

	//当前窗口是否被选中，然后处理播放
	void slotOnRePlaywgtSelected(int index);

	void slotOnReplayResetSlider();
	void slotOnTimeEditFinished(QString request_time);

	void slotOnReplayOnSwitchViewMode(PanoViewMode view_mode);
protected:
	//事件过滤，响应不同gl窗口的单击时间
	bool eventFilter(QObject *watched, QEvent *event);
private:
	//更新is_four_channel_playing
	void RePlaySetIsFourChannelPlaying();
	//异步API请求视频流
	void RePlayAskForVideo();

   //初始化窗口
	void init();
	void initConnect();
	//显示日历
	void showCalendar();
	//初始化模式按钮
	void initModeBtn();
	//初始化模式功能
	void initSingleFunction();
	//绘制列表
	void generateUI();
	//播放控制请求
	void playControlRequest(bool m_isPlay, int m_speed);
	//挡位转换
	int changeSpeed(int m_speed);
	QString changeSpeedLabel(int m_speed);
	//还原UI
	void restoreUi();

	//设置播放窗口
	playModeWgt *SetPlayModelWgt();
	//获取已经设置的播放窗口,传入当前列表的序号
	playModeWgt* GetPlayModelWgt(int list_item_num);

	//更新is_four_channel_playing
	void UpdateIsFourChannelPlaying();
	void RePlayDoubleClickToPlayStatusCommunication();
private slots:
	void slot_pause_play();
	void slot_setSelectedDate(QString date);
	void slotOnReplayRequestSucceed();
	void onListItemDoubleClickedSlot(QTreeWidgetItem* itemWidget, int column);
	void slotOnRequestReplayTimer();

	void slotOnReplaySetFullScreen(bool is_full_screen);

private:
	Ui::replayWgt *ui;
	//四个窗口是否都在播放
	bool replay_is_four_channel_playing_;

	//当前鼠标选中了那个窗口
	RePlayCurrentSelectGLWindow replay_current_select_GLWindow_;

	//创建日历
	calendarWidget *calendar_;
	//日历弹出位置
	int nPosX_;
	int nPosY_;
	bool isShowCalendar_;
	//播放状态
	bool isPlay_;
	bool isPause_;
	int speed_;
	//
	bool m_online;
	//当前是否有全屏状态
	bool replay_is_full_screenm_;
	//单路模式与四路模式切换
	bool singleMode_;    // 1:单路模式   0:四路模式

	//原图模式与360模式切换
	PanoViewMode currentPlayMode_;				//原图模式与360模式切换		// 0:标准模型   0:球模型

	bool fourFullScreen_;

	boost::shared_ptr<boost::thread> replay_double_click_to_play_status_machine_thread_;
	boost::shared_ptr<boost::thread> ask_video_thread_;
	boost::shared_ptr<boost::thread> query_video_thread_;

	//回放录像时间段列表
	QList<m_replayInfoList> m_replay_infoList_;
	api_detu_client_request_video_res_t *replay_request_url_;
	//全局请求回放当前时间点
	int curr_time_;
	int curr_duration_;
	int oriTime_;
	int request_time;
	//列表数据
	QList<deviceInfo> InfoList_;
	QList<deviceItemWidget*> itemWidgetList_;
	deviceInfo replay_current_select_item_info_;
	int m_selectId_;
	//定时器-实时刷新回放时间域
	QTimer *updateTimer_;
	int current_request_time_;
	int current_duration_;
	int srs_http_no_response;
	bool replay_net_no_response_;
	bool replay_server_no_response_;

	std::vector<api_record_query_respond> query_list_;

	playModeWgt *current_select_replaymodewgt_;
	bool m_load_state_;
};

#endif // REPLAYWGT_H
