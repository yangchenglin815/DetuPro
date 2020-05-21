#ifndef GUNCAMWGT_H
#define GUNCAMWGT_H

#include <QWidget>
#include "ui_gunCamWgt.h"

#include "GeneralDef.h"
#include "logging.hpp"
#include "constStruct.h"


//�����࣬����ONVIF��HKSDK
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
	bool startPlay();									//����ǹ��
	bool closePlay();									//�ر�ǹ������
	void setHiddenCtrl(bool visible);					//����ǹ��������

	bool play(SpyInfo currInfo);
	bool play(QString path);

	//void setTittle(QS);
public slots:
	void closeUI();
	void scaleUI();

private:

	//ǹ����¼
	bool DoLogin(QString Ip, int port, QString user, QString passwd);


private:
	Ui::gunCamWgt ui;

	bool isLogin_;
	bool isPlaying_;
	bool isRecording_;

	//�����࣬����ONVIF��HKSDK
	CamFactory *factory_;
	HkSdkProduct *product_;
	CamType cam_type_;

	SpyInfo currInfo_;
};

#endif // GUNCAMWGT_H
