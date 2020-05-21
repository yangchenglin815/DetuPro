
#include <QMessageBox>
#include <QDebug>
#include <QTimer>

#include "ballCamWgt.h"
#include "ballcamctrl.h"

#include "BallCamLinkageManager.h"
#include "socketRequest.h"
#include "feedback.h"

ballCamWgt::ballCamWgt(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::ballWgt)
	, ball_cam_ctrl_wgt_(NULL)
	, factory_(NULL)
	, product_(NULL)
	, cam_type_(HKSDK_TYPE)
	, curr_point_num_(-1)
	, curr_contral_type_(-1)
{
	ui->setupUi(this);
	setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
	init();
	initConnect();

}

ballCamWgt::~ballCamWgt()
{

}

void ballCamWgt::setBallCamParam(deviceInfo currInfo)
{
	curr_device_info_t_ = currInfo;
}

void ballCamWgt::initConnect()
{
	connect(&BallCamLinkageManagerIns, SIGNAL(SignalToTrigBallCamLinkage(int, int)), this, SLOT(SlotToTrigBallCamLinkage(int, int)));
}

void ballCamWgt::init()
{
	isLogin_ = false;
	isPlaying_ = false;
	isRecording_ = false;

	switch (cam_type_)
	{
	case HKSDK_TYPE:
	{			
		//factory_ = new HkSdkFactory();
		product_ =  new HkSdkProduct();//factory_->createProduct();
		break;
	}
	case ONVIF_TYPE:
	{		
		//factory_ = new OnvifFactory();
		//product_ =//factory_->createProduct();
		break;
	}
	default:
		break;
	}

	ball_cam_ctrl_wgt_ = new ballCamCtrl(this);
	connect(ball_cam_ctrl_wgt_, SIGNAL(buttonPressed(int)), this, SLOT(slotButtonGroupPressed(int)));
	connect(ball_cam_ctrl_wgt_, SIGNAL(buttonReleased(int)), this, SLOT(slotButtonGroupReleased(int)));
	connect(ball_cam_ctrl_wgt_, SIGNAL(sigOnSavePoint()), this, SLOT(slotOnSavePoint()));
}

/*************************************************
函数名:    	DoLogin
函数描述:	登录球机函数
输入参数:
输出参数:
返回值:
**************************************************/
bool ballCamWgt::DoLogin(QString Ip, int port, QString user, QString passwd)
{
	switch (cam_type_)
	{
	case HKSDK_TYPE:
	{
		product_->Login(Ip, port, user, passwd);
		break;
	}

	case ONVIF_TYPE:
	{
		product_->Login(Ip, port, user, passwd);
		break;
	}
	default:
		break;
	}
	return true;
}

/*************************************************
函数名:    	startPlay
函数描述:	球机播放函数
输入参数:
输出参数:
返回值:
*************************************************/
bool ballCamWgt::startPlay()
{
	return product_->Play();
}

/*************************************************
函数名:    	closePlay
函数描述:	关闭球机播放函数
输入参数:
输出参数:
返回值:
*************************************************/
bool ballCamWgt::closePlay()
{
	isPlaying_ = false;
	if (ball_cam_ctrl_wgt_ != NULL)
	{
		ball_cam_ctrl_wgt_->hide();
	}
	this->close();
	isLogin_ = false;
	return product_->Close();
}



void ballCamWgt::play(const PtzInfo &currInfo)
{
	if (!isPlaying_)
	{
		if (!isLogin_)
		{
			if (!product_->Login(currInfo.sIP, currInfo.wPort, currInfo.sUserName, currInfo.sPasswd))
			{
				Log::Info("this device ip %s DoLogin failed!", currInfo.sIP.toLocal8Bit().data());
				Feedback::instance()->maskUI(DEVICE_INFO_ERROR);
				isPlaying_ = false;
				this->close();
				return;
			}
			socketRequest::instance()->requestOnRegisterPTZDevice(currInfo);
			HWND winId = (HWND)(ui->widget->winId());
 			product_->SetCfg(winId);
			isLogin_ = true;
		}
		if (startPlay())         //播放球机
		{
			if (ball_cam_ctrl_wgt_ == NULL)
			{
				ball_cam_ctrl_wgt_ = new ballCamCtrl(this);
				connect(ball_cam_ctrl_wgt_, SIGNAL(buttonPressed(int)), this, SLOT(slotButtonGroupPressed(int)));
				connect(ball_cam_ctrl_wgt_, SIGNAL(buttonReleased(int)), this, SLOT(slotButtonGroupReleased(int)));
				connect(ball_cam_ctrl_wgt_, SIGNAL(sigOnSavePoint()), this, SLOT(slotOnSavePoint()));
			}
			ball_cam_ctrl_wgt_->resize(this->width(), this->height());
			ball_cam_ctrl_wgt_->move(mapToGlobal(QPoint(0, 0)).rx(), mapToGlobal(QPoint(0, 0)).ry());
			ball_cam_ctrl_wgt_->show();
			emit sigOnPTZPlayStatus(true);
			QTimer::singleShot(20, this, SLOT(slotOnRefresh()));
			isPlaying_ = true;
			return;
		}
		isPlaying_ = false;
		emit sigOnPTZPlayStatus(false);
	}
	else
	{
		if (closePlay())         //关闭球机播放
		{
			isPlaying_ = false;
			emit sigOnPTZPlayStatus(false);
			return;
		}
	}
}


void ballCamWgt::setSavePresetBtnVisible(bool visible)
{
	if (ball_cam_ctrl_wgt_ != NULL)
	{
		ball_cam_ctrl_wgt_->setSavePresetBtnVisible(visible);
	}
}

void ballCamWgt::setExchangeBtnVisible(bool visible)
{
	if (ball_cam_ctrl_wgt_ != NULL)
	{
		ball_cam_ctrl_wgt_->setSavePresetBtnVisible(visible);
	}
}

void ballCamWgt::slotButtonGroupPressed(int index)
{
	//dwstop：0开始
	product_->Contral(index, 0);
}

void ballCamWgt::slotButtonGroupReleased(int index)
{
	//dwstop：1停止
	product_->Contral(index, 1);
}

void ballCamWgt::slotOnRefresh()
{
	setPosMove();
}

void ballCamWgt::SlotToTrigBallCamLinkage(int pre_point_num,int contral_type)
{
	curr_point_num_ = pre_point_num;
	//跳转	
	product_->setPoint(pre_point_num, 39);
	if (ball_cam_ctrl_wgt_ != NULL)
	{
		ball_cam_ctrl_wgt_->setButtonText(QString::number(pre_point_num), 8);
	}
}

void ballCamWgt::slotOnSavePoint()
{	
	//保存
	product_->setPoint(curr_point_num_, 8);
}

void ballCamWgt::setPosMove()
{
	if (ball_cam_ctrl_wgt_ != NULL)
	{
		ball_cam_ctrl_wgt_->resize(this->width(), this->height());
		ball_cam_ctrl_wgt_->move(mapToGlobal(QPoint(0, 0)).rx(), mapToGlobal(QPoint(0, 0)).ry());
	}
}

void ballCamWgt::setHiddenCtrl(bool visible)
{
	if (ball_cam_ctrl_wgt_ != NULL && isPlaying_)
	{
		ball_cam_ctrl_wgt_->setVisible(visible);
		this->setVisible(visible);
	}
}
