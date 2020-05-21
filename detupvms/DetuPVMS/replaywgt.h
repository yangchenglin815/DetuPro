/************************************************
* \file replaywgt.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* �ط�ҳ�洰��
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

	//�ط�״̬��ö��
	enum RePlayDoubleClickToPlayStatus
	{
		REPLAY_DOUBLE_CLICK_TO_PLAY_STATUS_START = 0,			//��ʼ״̬	
		REPLAY_DOUBLE_CLICK_TO_PLAY_STATUS_COMMUNICATION,		//ͨ��״̬
		REPLAY_DOUBLE_CLICK_TO_PLAY_STATUS_GET_SRS,			//��ȡSRS�ص�״̬
		REPLAY_DOUBLE_CLICK_TO_PLAY_STATUS_STITCH,				//ƴ��״̬
	};

public:
	replayWgt(QWidget *parent = 0);
	~replayWgt();

	void QueryForVideo();
	//�رղ���������
	void closeReplaySourse(int glwindow_num);
	//��ͣ������
	void pausePlayer(int glwindow_num, bool reset);
	//�б����ݴ���
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
	//��·ģʽ
	void slot_singleModeSelected();
	//��·ģʽ
	void slot_fourModeSelected();
	//��ĳ·���������ģʽ
	void slot_openOneBallCam();
	//�ر��������ģʽ
	void slot_closeOneBallCam();
	//ԭͼģʽ
	void slot_originModeSelected();
	//360ģʽ
	void slot_360ModeSelected();
	//ȫ��ģʽ
	void slot_fullOfScreen();
	void initFullofScreen();
	//����ظ�¼��
	void slotOnRequestReplayRadio(int time, int duration);
	//��ȡ�ط���Ƶʵʱʱ��
	void slotOnGetRecordTime(int time);
	//��ʾ����
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

	//��ǰ�����Ƿ�ѡ�У�Ȼ������
	void slotOnRePlaywgtSelected(int index);

	void slotOnReplayResetSlider();
	void slotOnTimeEditFinished(QString request_time);

	void slotOnReplayOnSwitchViewMode(PanoViewMode view_mode);
protected:
	//�¼����ˣ���Ӧ��ͬgl���ڵĵ���ʱ��
	bool eventFilter(QObject *watched, QEvent *event);
private:
	//����is_four_channel_playing
	void RePlaySetIsFourChannelPlaying();
	//�첽API������Ƶ��
	void RePlayAskForVideo();

   //��ʼ������
	void init();
	void initConnect();
	//��ʾ����
	void showCalendar();
	//��ʼ��ģʽ��ť
	void initModeBtn();
	//��ʼ��ģʽ����
	void initSingleFunction();
	//�����б�
	void generateUI();
	//���ſ�������
	void playControlRequest(bool m_isPlay, int m_speed);
	//��λת��
	int changeSpeed(int m_speed);
	QString changeSpeedLabel(int m_speed);
	//��ԭUI
	void restoreUi();

	//���ò��Ŵ���
	playModeWgt *SetPlayModelWgt();
	//��ȡ�Ѿ����õĲ��Ŵ���,���뵱ǰ�б�����
	playModeWgt* GetPlayModelWgt(int list_item_num);

	//����is_four_channel_playing
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
	//�ĸ������Ƿ��ڲ���
	bool replay_is_four_channel_playing_;

	//��ǰ���ѡ�����Ǹ�����
	RePlayCurrentSelectGLWindow replay_current_select_GLWindow_;

	//��������
	calendarWidget *calendar_;
	//��������λ��
	int nPosX_;
	int nPosY_;
	bool isShowCalendar_;
	//����״̬
	bool isPlay_;
	bool isPause_;
	int speed_;
	//
	bool m_online;
	//��ǰ�Ƿ���ȫ��״̬
	bool replay_is_full_screenm_;
	//��·ģʽ����·ģʽ�л�
	bool singleMode_;    // 1:��·ģʽ   0:��·ģʽ

	//ԭͼģʽ��360ģʽ�л�
	PanoViewMode currentPlayMode_;				//ԭͼģʽ��360ģʽ�л�		// 0:��׼ģ��   0:��ģ��

	bool fourFullScreen_;

	boost::shared_ptr<boost::thread> replay_double_click_to_play_status_machine_thread_;
	boost::shared_ptr<boost::thread> ask_video_thread_;
	boost::shared_ptr<boost::thread> query_video_thread_;

	//�ط�¼��ʱ����б�
	QList<m_replayInfoList> m_replay_infoList_;
	api_detu_client_request_video_res_t *replay_request_url_;
	//ȫ������طŵ�ǰʱ���
	int curr_time_;
	int curr_duration_;
	int oriTime_;
	int request_time;
	//�б�����
	QList<deviceInfo> InfoList_;
	QList<deviceItemWidget*> itemWidgetList_;
	deviceInfo replay_current_select_item_info_;
	int m_selectId_;
	//��ʱ��-ʵʱˢ�»ط�ʱ����
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
