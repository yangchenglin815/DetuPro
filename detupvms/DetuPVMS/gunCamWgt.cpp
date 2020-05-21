#include "gunCamWgt.h"

#include "socketRequest.h"
#include "feedback.h"

gunCamWgt::gunCamWgt(QWidget *parent)
	: QWidget(parent)
	, factory_(NULL)
	, product_(NULL)
	, cam_type_(HKSDK_TYPE)
{
	ui.setupUi(this);

	setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

	init();
	initConnect();
}

gunCamWgt::~gunCamWgt()
{

}

void gunCamWgt::init()
{
	isLogin_ = false;
	isPlaying_ = false;
	isRecording_ = false;

	switch (cam_type_)
	{
	case HKSDK_TYPE:
	{
		//factory_ = new HkSdkFactory();
		product_ = new HkSdkProduct();//factory_->createProduct();
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
}

void gunCamWgt::initConnect()
{
	connect(ui.closeBtn, SIGNAL(clicked()), this, SLOT(closeUI()));
	connect(ui.scaleBtn, SIGNAL(clicked()), this, SLOT(scaleUI()));
}

void gunCamWgt::setGunCamParam(deviceInfo currInfo)
{

}

bool gunCamWgt::startPlay()
{
	return product_->Play();
}

bool gunCamWgt::closePlay()
{
	isPlaying_ = false;
	isLogin_ = false;
	return product_->Close();
}

bool gunCamWgt::play(SpyInfo currInfo)
{
	currInfo_ = currInfo;
	QString tittle = "Ç¹»ú" + currInfo.sIP;
	 
	ui.titleLabel->setText(tittle);
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
				return false;
			}
			HWND winId = (HWND)(ui.widget->winId());
			product_->SetCfg(winId);
			isLogin_ = true;
		}
		if (startPlay())         //²¥·ÅÇò»ú
		{
			isPlaying_ = true;
			return true;
		}
		isPlaying_ = false;
		return false;
	}
} 

bool gunCamWgt::play(QString path)
{
	ui.titleLabel->setText(path);


	QPalette palette = this->palette();
	palette.setBrush(QPalette::Window,
	QBrush(QPixmap(QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/Map/hotPic/" + path))
		.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

	ui.widget->setAutoFillBackground(true);
	ui.widget->setPalette(palette);

	return 0;
}

void gunCamWgt::closeUI()
{
	this->closePlay();
	this->hide();
}

void gunCamWgt::scaleUI()
{
	if (this->isFullScreen())
	{
		this->closePlay();
		this->showNormal();
		this->play(currInfo_);
	}
	else
	{
		this->closePlay();
		this->showFullScreen();
		this->play(currInfo_);
	}

}

bool gunCamWgt::DoLogin(QString Ip, int port, QString user, QString passwd)
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

