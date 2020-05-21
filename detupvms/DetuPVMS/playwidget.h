/************************************************
* \file playmodewgt.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* 实时播放页面窗口
************************************************/
#ifndef PLAYWIDGET_H
#define PLAYWIDGET_H

#include <QWidget>
#include <QTreeWidgetItem> 

#include "MediaFileItem.h"
#include "playmodewgt.h"

#include "constStruct.h"
#include "APIProtocol.h"

#include "Preview/deviceItemWidget.h"

using namespace dm::server;

namespace Ui {
	class playWidget;
}



class playWidget : public QWidget
{
	Q_OBJECT

	enum CurrentSelectGLWindow
	{
		GL0 = 0,
		GL1 = 1,
		GL2,
		GL3,
		GL4,
	};


public:
	playWidget(QWidget *parent = 0);
	~playWidget();

	bool IsInitPlayingOK(int glwindow_num);
	void ClosePlaySourse(int glwindow_num);
	void ClosePlayer();

	void InitData(const QList<deviceInfo> &itemInfoList);
	void GetSelectId(int selectId);
	void UpdateListSlot(QList<deviceInfo> deviceList);
	void ResetPlayerStatus();
	void setPosMove();
	void setTimePos();
	void setHiddenCtrl(bool visible);   //隐藏球机控制器
	void setStatusShowLabel(PLAY_STATUS play_status);
signals:
	void sigOnSwitchViewMode(PanoViewMode view_mode);
	void sigOnTransportList(QList<deviceInfo> deviceList);

	//切换播放器play_flag
	void sigOnSwitchPlayFlag(bool play_flag);
	//球机未绑定通知
	void sigOnBindPTZWarning();
	//优化模板成功信号
	void sigOnOptMizeSuccess();

public slots:
	//单路模式
	void slotOnSingleModeSelected();
	//四路模式
	void slotOnFourModeSelected();
	//切换球机联动模式
	void slotOnSwitchBallCam(bool is_ball_cam_open);

	//原图模式
	void slotOnOriginModeSelected();
	//360模式
	void slotOnPanoModeSelected();
	//全屏模式
	void slot_fullOfScreenMode();
	//响应列表双击事件
	void onListItemDoubleClickedSlot(QTreeWidgetItem* itemWidget, int column);
	//关闭视频后更新列表状态
	void slotOnResetStatus(int item_num);
	//重启M1关闭播放画面
	void slotOnCloseSubStreamClearPlayer(int id);
	//当前窗口是否被选中，然后处理播放
	void slotOnPlaywgtSelected(int index);
	//获取预览视频实时时间
	void slotOnGetRecordTime(int time);
   //
	void slotOnUpdate();
	void slotOnGetBitRate(unsigned char streamId, api_detu_client_av_param_t* res);
	void slotOnRebootM1ResetPlayer(int id);
	void slotOnPlayRequestSucceed();
	void slotOnSetFullScreen(bool is_full_screen);
private:
	//设置播放窗口
	playModeWgt* SetPlayModelWgt();
	//获取已经设置的播放窗口,传入当前列表的序号
	playModeWgt* GetPlayModelWgt(int list_item_num);

	//更新is_four_channel_playing
	void UpdateIsFourChannelPlaying();

	//事件过滤，响应不同gl窗口的单击时间
	bool eventFilter(QObject *watched, QEvent *event);



	//四路已经同时播放时，再去加载播放，先关闭选中的GL窗口
	void closeSelectedGLWindow(CurrentSelectGLWindow current_select_GLWindow_);
	//初始化界面与信号槽
	void init();
	void initConnect();
	//初始化模式按钮
	void initModeBtn();
	//初始化模式功能
	void initSingleFunction();
	//绘制列表
	void GenerateUI();
	//
	void initDecodeStatus(bool single);
private:
	Ui::playWidget *ui;
	//当前鼠标选中了那个窗口
	CurrentSelectGLWindow current_select_GLWindow_;

	//播放控制结构体
	//PlayListItemCfg_t real_play_cfg_;

	boost::shared_ptr<boost::thread> double_click_to_play_status_machine_thread_;



	bool is_ball_cam_open_;						//是否正在球机联动

	bool is_four_channel_playing_;				//四个窗口是否都在播放

	bool is_full_screenm_;						//当前是否有全屏状态

	bool singleMode_;							//单路模式与四路模式切换	// 1:单路模式   0:四路模式

	PanoViewMode currentPlayMode_;				//原图模式与360模式切换		// 0:标准模型   0:球模型

	bool m_online_;								//服务器在线状态

	bool fourFullScreen_;						//控制4画面全屏（避免由于全屏时双击操作造成界面未刷新）

	//列表相关
	QList<deviceInfo> InfoList_;
	QList<deviceItemWidget*> itemList_;
	deviceInfo current_select_item_info_;
	int m_selectId;
	//播放器的上一秒时间
	QList<int> oriTimeList_;

	playModeWgt *current_select_playmodewgt_;
	QMap<int, playModeWgt*> windowMap_;
};

#endif // PLAYWIDGET_H
