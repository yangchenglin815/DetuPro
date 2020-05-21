/************************************************
* \file playmodewgt.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* ��װ�ĵ�������ҳ�棬����glwindow�ͱ�����
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

	//���ó��ð�ť�Ƿ�ɼ�
	void setBtnVisible(bool visible);
	void setShowTime( QString time, int mode);
	void setShowStreamInfo();
	void closeShowTime();
	void setTimeLabelHeight(int nHeight);
	//����GLWindow��ţ���Ϊ��־
	void SetPlayWindowNum(int play_window_num);
	int GetPlayWindowNum(){ return play_window_num_; };
	//����top�Ƿ�ɼ�
	void setTopWgtVisable(bool chosen);
	
	bool isPlaying(){ return is_playing_; };
	void setIsPlaying(bool is_playing);

	void setGLConfig();
	//����pts���Ż��ļ�
	void CreatStitchFiles(int type, int requestTime);
	void CreatStitchFilesThread();

	void play();
	void close();
	void clearPlay();
	void closeUI();

	void handshakeFailed();
	void switchStream();
	//�л�����
	void sequencer();
	void pauseUI(bool reset);
	void exchangeUI();
	void closeStream();
	void closePlayer();
	void setStreamInfo(QString resolution, int framerate, int bitrate);
	void thread_play();

	void thread_close_player();
	//֪ͨ�ر�NVR����
	void thread_close_stream();
	void OnVideoData(m1_video_frame_s** av_frame_sync_list_, int index, unsigned int timestamp);
	void setCailbration();
	
	void setPlayConfig(deviceInfo current_select_item_info/*, PlayModelType isOrigin*/);
	void setReplayConfig(QString url, deviceInfo current_select_item_info/*, PlayModelType isOrigin*/);

	void setMapPlayConfig(PanoMapPointInfo_t panoMapInfo);
	void setMapScenePlayConfig(PanoMapPointInfo_t panoMapInfo);

	void resizeMapControl();

	//����pts/����wtͼ���̺߳���
	void thread_capture();

	//ʵʱ�Ż�pts�̺߳���
	void thread_optimize_pts();

	//�ж��Ƿ����ڳ�ʼ����������ڣ�return
	bool isStitchFileOk(){ return is_stitch_file_ok_; };

	//��ʼ����Ƶʧ�ܣ������б�״̬
	void updatePlayListStatus();

	//���������������λ��
	void setPosMove();
	void setTimePos(int mode);

	void setHiddenCtrl(bool visible);   //�������������
	void setHiddenTime(bool visible);
	void closePTZ();
	void initWindow(int window_type);
	void setGLWindowMax(bool is_max);
	//��������Ϣ�׳�
	void onSigaction(int message_type, long attach);
public slots:
	//�л�������play_flag״̬�����ǲ�����
	void OnSwitchPlatFlagSlot(bool play_flag);

	//�����Զ���ת
	void onSetAutoRotateSlot();
	//�رյ�ǰ����
	void onClosePlaySlot();
	//�򿪳�����ͼ
	void slotOnPicGroupClicked(bool checked);
    //֪ͨ��ʾGLWindow
    void onShowGlWindowSlot();
    //��ͼ
    void onCaptureSlot();
	//�򿪻�ر�HTC
	void onOpenHtcViveSlot();


	//�򿪻�ر�ǹ��
	void slotOnOpenGunCam(SpyInfo_t spy_info);

	//�򿪻�ر�ͼƬ�ȵ�
	void slotOnOpenHotPic(QString path);

	//�򿪻�ر��������ģʽ
	void onOpenBallCamSlot();


	//�򿪻�ر�ʵʱ�Ż�
	void onOpenOptimizeSlot();

	//���ò���״̬
	void onSetGlLabelSlot(PLAY_STATUS play_status);
	//
	void slotOnPTZPlayStatus(bool success);
	//��ȡ������������
	void slotOnRequestGetBandWidth();
	//�л�����
	void OnSwitchStreamSlot(bool checked);

	//��ͼ���水ť��Ӧ�¼�
	void OnOpenPanoMapSlot(bool checked);
	void OnOpenMapReplaySlot();

	void slotOnHiddenMiniMap();
	void slotOnHiddenPicGroup();

	void slotOnUpdate();
	void slotOnUpdateStreamInfo();
	void slotOnReportUI(PLAY_STATUS play_status, int errorNo);

	//SRS�����ź����Ӻ͹رգ���ΪҪ���ĸ��������ӣ�����͵ù�
	void srsConn();
	void srsDisConn();


	//Ԥ�������SRS����
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

	//��⾯����
	void slotOnCheckWarningBoard();

signals:
	//���ò���״̬��
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

	//�����ģʽ�ź�
	void sigOnBallCamBtnClicked(bool is_ball_cam_open);
	//���źŵ����̳߳�ʼ��gl_render
	void sigOnToSetGlRender();
	//֪ͨ�������
	void sigOnPlayBallCam();
	//���Ϊ��֪ͨ
	void sigOnBindPTZWarning();
	//�Ż�ģ��ɹ�
	void sigOnOptMizeSuccess();


	void SignalToShowGlWindowPrivate();
	void sigOnReplayResetSlider();

	void sigOnNetWorkResponse();

	//֪ͨ��ͼ�����ػ�
	void sigOnRePaintMap();
	//֪ͨ��ͼ�򿪻طſ���
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
	//״̬���������������˫���б����ŵ�״̬��ת
	void StitchStatusMachine();
private:
	void StitchStatusCommunication();
	void StitchStatusGetSrs();
	void StitchStatueCheckStitchPara();
	void StitchStatusCapture();
	void StitchStatusCreatWt();
	void StitchStatusOptimize();
	void StitchStatusCalibration();

	//dpv�̳�
	void onPanoPlayerLoading();
	void onPanoPlayerLoaded();
	void onPanoPlayerError(PanoPlayerErrorCode errorCode);
	void onPanoPlayerPluginStatusChanged(PanoPluginStatus status, string tip);
	void onPanoPlayerPluginProgressChanged(long playProgress, long bufferProgress, long duration);
	void onPanoPlayerPluginStatisticsDataChanged(PanoPluginStatisticsData* statisticsData);
	void onScreenShotFinished(ScreenShot* screenShot);
	void onPanoPlayerRenderBefore();
	void onPanoPlayerRenderAfter();

	//ץͼ��ץȫ��ͼ����glview�Ƴ���
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
	bool is_playing_;								//��ǰ�����Ƿ����ڲ���
	bool is_rotating_;								//��ǰ�����Ƿ�������ת
	bool is_full_screen_;							//GLWindow�Ƿ����
	int play_window_num_;							//���������ڣ�����GLWindow���
	int play_window_type_;							//��ǰ���Ŵ�����Ԥ�����ǻط�
	int replay_request_time_;						//�طŴ�������ʱ���
	int m_global_video_time_;

	bool is_htc_open_;								//htcͷ���Ƿ��
	bool is_ball_cam_open_;							//�������ģʽ�Ƿ��

	bool is_replaying_;						//��ǰ�ۿ��Ƿ��ǻط�
	
	//����ģ���ļ��Ƿ�ȫ���Ż����ɣ�����в��ţ����û��setTexture��Ҫreturn
	//�жϵ�һ���Ƿ�Ҫץͼ
	//Ĭ����true�����û��ʼ���������÷�
	bool is_stitch_file_ok_;
	bool is_init_caprure_;
	bool is_error_;

	bool is_optimize_capture_;						//�Ƿ���Ҫ�Ż���ͼ
	bool is_optimize_ok_;							//�Ż��Ƿ����
	bool m_play_thread_return_;
	bool m_first_frames;
	bool m_subStream_open;            //������������־λ

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



	QString RTMP_URL_;								//������ַ	
	deviceInfo current_select_item_info_;
	QString select_pvs_device_;						//���ŵ��豸id
	QString select_m1_device_;						//���ŵ�m1�豸id


	QLabel *time_label_;
	timeLabel *timeLbl_;
	timeLabel *streamInfoLbl_;
	QString current_stream_info_;

	StitchStatus current_stitch_status_;

	bool is_exchange_;

	ballCamWgt *ballwgt_;
	gunCamWgt *gunwgt_;


	//srsȫ�ֱ���
	bool net_no_response_;
	int srs_http_no_response;
	int m_preview_stream_type;
	int m_replay_stream_type;
	int m_map_preview_stream_type;
	int m_map_replay_stream_type;

	GLSurfaceWidget *gl_view_screen_;

	RoamFragment *decorFragment_;
	M1PixelPanoPlayer* m1_pixel_pano_player_;		

	boost::shared_ptr<CM1Player> m1_player_;								//��ͼ�ϲ���������
	m1_video_frame_s** m_av_frame_sync_list_;

	PixelPlugin* m_pixelPlugin;
	bool		 first_frames_;
	int			 vcodec_type_;
	long		 m_signal_id_;
	PluginFrame  m_frames[PLUGIN_MAX_PLANE];
	PanoViewMode m_panoViewMode;	
	//��ͼ������
	PanoMapPointInfo_t m_panoPointInfo;

	directionArrowWgt *sequencer_wgt_;

	SequencerTipWgt *sequencer_tip_wgt_;
	bool is_sequencer_play_;

	MinimapWgt *miniMap_;
	mapToolWidget *m_mapToolWgt;

	//�����л��Ƕ�ƫת��
	float sequencer_angle_;
	//��ͼ��ť
	QPushButton *picGroupBtn_;

	//ͼ������
	PanoCalibraterAndCapturer *calibrater_and_capturer_;

	//RFID����,���ŵ�ʱ������
	RFIDReader *rfid_reader_;
	DoorManager *door_manager_;

	weather_peopleflow *weather_peopleflow_;

	int total_people_;
};

#endif // PLAYMODEWGT_H
