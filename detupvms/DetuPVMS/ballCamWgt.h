/************************************************
* \file MinimapWgt.h
*
* \author HuZhengdong
* \date 20180109
* 枪机播放窗口
************************************************/

#ifndef BALLWGT_H
#define BALLWGT_H

#include <QWidget>
#include "ui_ballwgt.h"

#include "GeneralDef.h"
#include "logging.hpp"
#include "constStruct.h"


//工厂类，区分ONVIF和HKSDK
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
	bool startPlay();									//播放球机
	bool closePlay();									//关闭球机播放

	void play(const PtzInfo &currInfo);

	//设置保存预置点按钮可不可见
	void setSavePresetBtnVisible(bool visible);
	//设置切换大小按钮可不可见
	void setExchangeBtnVisible(bool visible);

	void ballCamWgt::setHiddenCtrl(bool visible);


private:
	void initConnect();
	void init();
	//球机登录
	bool DoLogin(QString Ip, int port, QString user, QString passwd); 
	//云台控制函数
	void PTZControlAll(LONG lRealHandle, DWORD dwPTZCommand, DWORD dwStop, int Speed);  

private slots :
	void slotButtonGroupPressed(int index);
	void slotButtonGroupReleased(int index);
	void slotOnRefresh();

	//触发球机
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

	//工厂类，区分ONVIF和HKSDK
	CamFactory *factory_;
	HkSdkProduct *product_;
	CamType cam_type_;

	int curr_point_num_;
	int curr_contral_type_;
};

#endif // BALLWGT_H
