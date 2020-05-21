/************************************************
* \file playmodewgt.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* 封装的单个播放页面，包含glwindow和标题栏
************************************************/
#ifndef PLAYMODEWGT_H
#define PLAYMODEWGT_H

#include <QWidget>
#include <QPushButton>

#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>

#include "M1PixelPanoPlayer.h"
#include "m1player\header\M1Player.h"

#include "QtPanoPlayer\header\getweight\GetResult.h"

#include "QtPanoPlayer\header\qtpanoplayer\GLSurfaceWidget.h"
#include "QtPanoPlayer\header\qtpanoplayer\ScreenShotListener.h"
#include "QtPanoPlayer\header\qtpanoplayer\IPanoPlayerPluginListener.h"
#include "QtPanoPlayer\header\qtpanoplayer\IPanoPlayerListener.h"
#include "QtPanoPlayer\header\qtpanoplayer\IPanoPlayerRenderEventListener.h"
#include "QtPanoPlayer\header\qtpanoplayer\QtPanoPlayer.h"

#include "timeLabel.h"
#include "constStruct.h"
using namespace std;
using namespace DetuPanoPlayer;

class SequencerWgt;
class SequencerTipWgt;
class directionArrowWgt;
class RoamFragment;
class ballCamWgt;
class gunCamWgt;
class MinimapWgt;
class mapToolWidget;
class PanoCalibraterAndCapturer;
class RFIDReader;
class DoorManager;
class weather_peopleflow;

namespace Ui {
	class playModeWgt;
}

class playModeWgt : public QWidget,
	public IPanoPlayerPluginListener,
	public ScreenShotListener,
	public IPanoPlayerListener,
	public IPanoPlayerRenderEventListener
{
	Q_OBJECT

public:
	playModeWgt(QWidget *parent);
	playModeWgt(QWidget *parent, bool is_map_available);
	~playModeWgt();

	//设置常用按钮是否可见
	void setBtnVisible(bool visible);
	void setShowTime( QString time, int mode);
	void setShowStreamInfo();
	void closeShowTime();
	void setTimeLabelHeight(int nHeight);
	//设置GLWindow序号，作为标志
	void SetPlayWindowNum(int play_window_num);
	int GetPlayWindowNum(){ return play_window_num_; };
	//设置top是否可见
	void setTopWgtVisable(bool chosen);
	
	bool isPlaying(){ return is_playing_; };
	void setIsPlaying(bool is_playing);

	void setGLConfig();
	//查找pts、优化文件
	void CreatStitchFiles(int type, int requestTime);
	void CreatStitchFilesThread();

	void play();
	void close();
	void clearPlay();
	void closeUI();

	void handshakeFailed();
	void switchStream();
	//切换场景
	void sequencer();
	void pauseUI(bool reset);
	void exchangeUI();
	void closeStream();
	void closePlayer();
	void setStreamInfo(QString resolution, int framerate, int bitrate);
	void thread_play();

	void thread_close_player();
	//通知关闭NVR的流
	void thread_close_stream();
	void OnVideoData(m1_video_frame_s** av_frame_sync_list_, int index, unsigned int timestamp);
	void setCailbration();
	
	void setPlayConfig(deviceInfo current_select_item_info/*, PlayModelType isOrigin*/);
	void setReplayConfig(QString url, deviceInfo current_select_item_info/*, PlayModelType isOrigin*/);

	void setMapPlayConfig(PanoMapPointInfo_t panoMapInfo);
	void setMapScenePlayConfig(PanoMapPointInfo_t panoMapInfo);

	void resizeMapControl();

	//生成pts/生成wt图像线程函数
	void thread_capture();

	//实时优化pts线程函数
	void thread_optimize_pts();

	//判断是否正在初始化，如果正在，return
	bool isStitchFileOk(){ return is_stitch_file_ok_; };

	//初始化视频失败，更新列表状态
	void updatePlayListStatus();

	//设置球机控制器的位置
	void setPosMove();
	void setTimePos(int mode);

	void setHiddenCtrl(bool visible);   //隐藏球机控制器
	void setHiddenTime(bool visible);
	void closePTZ();
	void initWindow(int window_type);
	void setGLWindowMax(bool is_max);
	//播放器消息抛出
	void onSigaction(int message_type, long attach);
public slots:
	//切换播放器play_flag状态，就是不解码
	void OnSwitchPlatFlagSlot(bool play_flag);

	//设置自动旋转
	void onSetAutoRotateSlot();
	//关闭当前窗口
	void onClosePlaySlot();
	//打开场景组图
	void slotOnPicGroupClicked(bool checked);
    //通知显示GLWindow
    void onShowGlWindowSlot();
    //截图
    void onCaptureSlot();
	//打开或关闭HTC
	void onOpenHtcViveSlot();


	//打开或关闭枪机
	void slotOnOpenGunCam(SpyInfo_t spy_info);

	//打开或关闭图片热点
	void slotOnOpenHotPic(QString path);

	//打开或关闭球机联动模式
	void onOpenBallCamSlot();


	//打开或关闭实时优化
	void onOpenOptimizeSlot();

	//设置播放状态
	void onSetGlLabelSlot(PLAY_STATUS play_status);
	//
	void slotOnPTZPlayStatus(bool success);
	//获取带宽网络请求
	void slotOnRequestGetBandWidth();
	//切换码流
	void OnSwitchStreamSlot(bool checked);

	//地图界面按钮响应事件
	void OnOpenPanoMapSlot(bool checked);
	void OnOpenMapReplaySlot();

	void slotOnHiddenMiniMap();
	void slotOnHiddenPicGroup();

	void slotOnUpdate();
	void slotOnUpdateStreamInfo();
	void slotOnReportUI(PLAY_STATUS play_status, int errorNo);

	//SRS请求信号连接和关闭，因为要和四个子类连接，用完就得关
	void srsConn();
	void srsDisConn();


	//预览界面的SRS请求
	void slotOnGetSrsInfo(int id, bool state);
	void slotOnNetWorkError(int error);
	void slotOnNetWorkResponse();
	void slotOnNoResponseMessage();

	void slotOnRequestNetWork();
	void slotOnPVSIDError();

	void slotOnSwitchViewMode(PanoViewMode view_mode);


	void slotOnSequencer(int id);

	void slotOnMoveSequencer();
	void slotOnSetSwtichScreen(int button_num);

	//检测警告牌
	void slotOnCheckWarningBoard();

signals:
	//设置播放状态，
	void SignalToSetGlLabel(PLAY_STATUS play_status);
	void sigOnReportUI(PLAY_STATUS play_status, int errorNo);


	void SignalToShowGlWindow();
	void SignalToSetGlStop();
	void SignalToSetGlPause();
	void sigOnPlayStatus();

	void sigOnGetRecordTime(int time);
	void sigOnResetStatus(int item_num);
	void sigOnResetMapStatus();
	void SignalToCapture();

	//打开球机模式信号
	void sigOnBallCamBtnClicked(bool is_ball_cam_open);
	//发信号到主线程初始化gl_render
	void sigOnToSetGlRender();
	//通知球机播放
	void sigOnPlayBallCam();
	//球机为绑定通知
	void sigOnBindPTZWarning();
	//优化模板成功
	void sigOnOptMizeSuccess();


	void SignalToShowGlWindowPrivate();
	void sigOnReplayResetSlider();

	void sigOnNetWorkResponse();

	//通知地图界面重绘
	void sigOnRePaintMap();
	//通知地图打开回放控制
	void sigOnOpenReplayCtrl();
	void sigOnCloseReplayCtrl();

	void SignalToRFIDUi(int type, int id);
private slots:
	void updatePos();
	void slotOnBindPTZWarning();
	void slotOnControlPlayerRecordFlv();
	void slotOnHandleSubStreamMessage(bool open, QString pvsId, int id);

public:
	void setStitchStatus(StitchStatus stitch_status);
	//状态机处理函数，处理从双击列表到播放的状态流转
	void StitchStatusMachine();
private:
	void StitchStatusCommunication();
	void StitchStatusGetSrs();
	void StitchStatueCheckStitchPara();
	void StitchStatusCapture();
	void StitchStatusCreatWt();
	void StitchStatusOptimize();
	void StitchStatusCalibration();

	//dpv继承
	void onPanoPlayerLoading();
	void onPanoPlayerLoaded();
	void onPanoPlayerError(PanoPlayerErrorCode errorCode);
	void onPanoPlayerPluginStatusChanged(PanoPluginStatus status, string tip);
	void onPanoPlayerPluginProgressChanged(long playProgress, long bufferProgress, long duration);
	void onPanoPlayerPluginStatisticsDataChanged(PanoPluginStatisticsData* statisticsData);
	void onScreenShotFinished(ScreenShot* screenShot);
	void onPanoPlayerRenderBefore();
	void onPanoPlayerRenderAfter();

	//抓图，抓全景图，从glview移出来
	void CaptureThreadFunc();

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
private:
	Ui::playModeWgt *ui;

	//ballWgt *ball_cam_wgt_;
	bool is_map_available_;
	bool is_map_opened_;
	bool is_playing_;								//当前窗口是否正在播放
	bool is_rotating_;								//当前窗口是否正在旋转
	bool is_full_screen_;							//GLWindow是否最大化
	int play_window_num_;							//设置主窗口，设置GLWindow序号
	int play_window_type_;							//当前播放窗口是预览还是回放
	int replay_request_time_;						//回放窗口请求时间点
	int m_global_video_time_;

	bool is_htc_open_;								//htc头盔是否打开
	bool is_ball_cam_open_;							//球机联动模式是否打开

	bool is_replaying_;						//当前观看是否是回放
	
	//设置模版文件是否全部优化生成，如果有播放，如果没有setTexture需要return
	//判断第一次是否要抓图
	//默认是true，如果没初始化，则先置否
	bool is_stitch_file_ok_;
	bool is_init_caprure_;
	bool is_error_;

	bool is_optimize_capture_;						//是否需要优化截图
	bool is_optimize_ok_;							//优化是否结束
	bool m_play_thread_return_;
	bool m_first_frames;
	bool m_subStream_open;            //子码流开启标志位

	boost::shared_ptr<boost::thread> playThread_ = NULL;
	boost::shared_ptr<boost::thread> closePlayerThread_ = NULL;
	boost::shared_ptr<boost::thread> closeStreamThread_ = NULL;
	boost::shared_ptr<boost::thread> creatPtsThread_ = NULL;
	boost::shared_ptr<boost::thread> optimizePtsThread_ = NULL;
	boost::shared_ptr<boost::thread> creatStitchFilesThread_ = NULL;
	boost::shared_ptr<boost::thread> captureThread_ = NULL;

	boost::shared_ptr<boost::thread> checkWarningBoradThread_ = NULL;

	boost::mutex mutex_stitch_ok_;
	boost::mutex mutex_open_htc_;
	boost::mutex mutex_open_ball_cam_;
	boost::mutex mutex_protected_player_;



	QString RTMP_URL_;								//码流地址	
	deviceInfo current_select_item_info_;
	QString select_pvs_device_;						//播放的设备id
	QString select_m1_device_;						//播放的m1设备id


	QLabel *time_label_;
	timeLabel *timeLbl_;
	timeLabel *streamInfoLbl_;
	QString current_stream_info_;

	StitchStatus current_stitch_status_;

	bool is_exchange_;

	ballCamWgt *ballwgt_;
	gunCamWgt *gunwgt_;


	//srs全局变量
	bool net_no_response_;
	int srs_http_no_response;
	int m_preview_stream_type;
	int m_replay_stream_type;
	int m_map_preview_stream_type;
	int m_map_replay_stream_type;

	GLSurfaceWidget *gl_view_screen_;

	RoamFragment *decorFragment_;
	M1PixelPanoPlayer* m1_pixel_pano_player_;		

	boost::shared_ptr<CM1Player> m1_player_;								//得图合并流播放器
	m1_video_frame_s** m_av_frame_sync_list_;

	PixelPlugin* m_pixelPlugin;
	bool		 first_frames_;
	int			 vcodec_type_;
	long		 m_signal_id_;
	PluginFrame  m_frames[PLUGIN_MAX_PLANE];
	PanoViewMode m_panoViewMode;	
	//地图点数据
	PanoMapPointInfo_t m_panoPointInfo;

	directionArrowWgt *sequencer_wgt_;

	SequencerTipWgt *sequencer_tip_wgt_;
	bool is_sequencer_play_;

	MinimapWgt *miniMap_;
	mapToolWidget *m_mapToolWgt;

	//场景切换角度偏转量
	float sequencer_angle_;
	//组图按钮
	QPushButton *picGroupBtn_;

	//图像处理类
	PanoCalibraterAndCapturer *calibrater_and_capturer_;

	//RFID测试,播放的时候启动
	RFIDReader *rfid_reader_;
	DoorManager *door_manager_;

	weather_peopleflow *weather_peopleflow_;

	int total_people_;
};

#endif // PLAYMODEWGT_H
