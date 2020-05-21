/************************************************
* \file MinimapWgt.h
*
* \author HuZhengdong
* \date 20180109
* ǹ�����Ŵ���
************************************************/

#ifndef BALLWGT_H
#define BALLWGT_H

#include <QWidget>
#include "ui_ballwgt.h"

#include "GeneralDef.h"
#include "logging.hpp"
#include "constStruct.h"


//�����࣬����ONVIF��HKSDK
#include "CamFactory.h"
#include "HkSdkFactory.h"
#include "OnvifFactory.h"

#include "UiSingleton.h"

namespace Ui
{
	class ballCamWgt;
}

class ballCamCtrl;

class ballCamWgt : public QWidget
{
	Q_OBJECT

public:
	ballCamWgt(QWidget *parent = 0);
	~ballCamWgt();

	void ballCamWgt::setPosMove();

	void setBallCamParam(deviceInfo currInfo);
	bool startPlay();									//�������
	bool closePlay();									//�ر��������

	void play(const PtzInfo &currInfo);

	//���ñ���Ԥ�õ㰴ť�ɲ��ɼ�
	void setSavePresetBtnVisible(bool visible);
	//�����л���С��ť�ɲ��ɼ�
	void setExchangeBtnVisible(bool visible);

	void ballCamWgt::setHiddenCtrl(bool visible);


private:
	void initConnect();
	void init();
	//�����¼
	bool DoLogin(QString Ip, int port, QString user, QString passwd); 
	//��̨���ƺ���
	void PTZControlAll(LONG lRealHandle, DWORD dwPTZCommand, DWORD dwStop, int Speed);  

private slots :
	void slotButtonGroupPressed(int index);
	void slotButtonGroupReleased(int index);
	void slotOnRefresh();

	//�������
	void SlotToTrigBallCamLinkage(int pre_point_num,int contral_type);
	void slotOnSavePoint();
signals:
	void sigOnBindPTZWarning();
	void sigOnPTZPlayStatus(bool success);
private:
	Ui::ballWgt* ui;
	ballCamCtrl *ball_cam_ctrl_wgt_;
	deviceInfo curr_device_info_t_;
	bool isLogin_;
	bool isPlaying_;
	bool isRecording_;

	//�����࣬����ONVIF��HKSDK
	CamFactory *factory_;
	HkSdkProduct *product_;
	CamType cam_type_;

	int curr_point_num_;
	int curr_contral_type_;
};

#endif // BALLWGT_H
