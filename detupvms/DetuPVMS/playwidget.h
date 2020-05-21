/************************************************
* \file playmodewgt.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* ʵʱ����ҳ�洰��
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
	void setHiddenCtrl(bool visible);   //�������������
	void setStatusShowLabel(PLAY_STATUS play_status);
signals:
	void sigOnSwitchViewMode(PanoViewMode view_mode);
	void sigOnTransportList(QList<deviceInfo> deviceList);

	//�л�������play_flag
	void sigOnSwitchPlayFlag(bool play_flag);
	//���δ��֪ͨ
	void sigOnBindPTZWarning();
	//�Ż�ģ��ɹ��ź�
	void sigOnOptMizeSuccess();

public slots:
	//��·ģʽ
	void slotOnSingleModeSelected();
	//��·ģʽ
	void slotOnFourModeSelected();
	//�л��������ģʽ
	void slotOnSwitchBallCam(bool is_ball_cam_open);

	//ԭͼģʽ
	void slotOnOriginModeSelected();
	//360ģʽ
	void slotOnPanoModeSelected();
	//ȫ��ģʽ
	void slot_fullOfScreenMode();
	//��Ӧ�б�˫���¼�
	void onListItemDoubleClickedSlot(QTreeWidgetItem* itemWidget, int column);
	//�ر���Ƶ������б�״̬
	void slotOnResetStatus(int item_num);
	//����M1�رղ��Ż���
	void slotOnCloseSubStreamClearPlayer(int id);
	//��ǰ�����Ƿ�ѡ�У�Ȼ������
	void slotOnPlaywgtSelected(int index);
	//��ȡԤ����Ƶʵʱʱ��
	void slotOnGetRecordTime(int time);
   //
	void slotOnUpdate();
	void slotOnGetBitRate(unsigned char streamId, api_detu_client_av_param_t* res);
	void slotOnRebootM1ResetPlayer(int id);
	void slotOnPlayRequestSucceed();
	void slotOnSetFullScreen(bool is_full_screen);
private:
	//���ò��Ŵ���
	playModeWgt* SetPlayModelWgt();
	//��ȡ�Ѿ����õĲ��Ŵ���,���뵱ǰ�б�����
	playModeWgt* GetPlayModelWgt(int list_item_num);

	//����is_four_channel_playing
	void UpdateIsFourChannelPlaying();

	//�¼����ˣ���Ӧ��ͬgl���ڵĵ���ʱ��
	bool eventFilter(QObject *watched, QEvent *event);



	//��·�Ѿ�ͬʱ����ʱ����ȥ���ز��ţ��ȹر�ѡ�е�GL����
	void closeSelectedGLWindow(CurrentSelectGLWindow current_select_GLWindow_);
	//��ʼ���������źŲ�
	void init();
	void initConnect();
	//��ʼ��ģʽ��ť
	void initModeBtn();
	//��ʼ��ģʽ����
	void initSingleFunction();
	//�����б�
	void GenerateUI();
	//
	void initDecodeStatus(bool single);
private:
	Ui::playWidget *ui;
	//��ǰ���ѡ�����Ǹ�����
	CurrentSelectGLWindow current_select_GLWindow_;

	//���ſ��ƽṹ��
	//PlayListItemCfg_t real_play_cfg_;

	boost::shared_ptr<boost::thread> double_click_to_play_status_machine_thread_;



	bool is_ball_cam_open_;						//�Ƿ������������

	bool is_four_channel_playing_;				//�ĸ������Ƿ��ڲ���

	bool is_full_screenm_;						//��ǰ�Ƿ���ȫ��״̬

	bool singleMode_;							//��·ģʽ����·ģʽ�л�	// 1:��·ģʽ   0:��·ģʽ

	PanoViewMode currentPlayMode_;				//ԭͼģʽ��360ģʽ�л�		// 0:��׼ģ��   0:��ģ��

	bool m_online_;								//����������״̬

	bool fourFullScreen_;						//����4����ȫ������������ȫ��ʱ˫��������ɽ���δˢ�£�

	//�б����
	QList<deviceInfo> InfoList_;
	QList<deviceItemWidget*> itemList_;
	deviceInfo current_select_item_info_;
	int m_selectId;
	//����������һ��ʱ��
	QList<int> oriTimeList_;

	playModeWgt *current_select_playmodewgt_;
	QMap<int, playModeWgt*> windowMap_;
};

#endif // PLAYWIDGET_H
