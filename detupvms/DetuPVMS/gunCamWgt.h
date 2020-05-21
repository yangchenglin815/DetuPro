#ifndef GUNCAMWGT_H
#define GUNCAMWGT_H

#include <QWidget>
#include "ui_gunCamWgt.h"

#include "GeneralDef.h"
#include "logging.hpp"
#include "constStruct.h"


//工厂类，区分ONVIF和HKSDK
#include "CamFactory.h"
#include "HkSdkFactory.h"
#include "OnvifFactory.h"

#include "UiSingleton.h"


class gunCamWgt : public QWidget
{
	Q_OBJECT

public:
	gunCamWgt(QWidget *parent = 0);
	~gunCamWgt();

	void init();
	void initConnect();

	void setGunCamParam(deviceInfo currInfo);
	bool startPlay();									//播放枪机
	bool closePlay();									//关闭枪机播放
	void setHiddenCtrl(bool visible);					//隐藏枪机控制器

	bool play(SpyInfo currInfo);
	bool play(QString path);

	//void setTittle(QS);
public slots:
	void closeUI();
	void scaleUI();

private:

	//枪机登录
	bool DoLogin(QString Ip, int port, QString user, QString passwd);


private:
	Ui::gunCamWgt ui;

	bool isLogin_;
	bool isPlaying_;
	bool isRecording_;

	//工厂类，区分ONVIF和HKSDK
	CamFactory *factory_;
	HkSdkProduct *product_;
	CamType cam_type_;

	SpyInfo currInfo_;
};

#endif // GUNCAMWGT_H
