#include <QEvent> 
#include <QMouseEvent> 
#include <QTextStream>

#include "gunCamSettingDig.h"

#include "gunCamMiniItem.h"
#include "gunCamWgt.h"

#include "feedback.h"

#include "socketRequest.h"

gunCamSettingDig::gunCamSettingDig(QWidget *parent)
	: QWidget(parent),
	gun_cam_mini_item_(NULL),
	gunWgt_(NULL),
	delta_pos_(0.0, 0.0),
	last_pos_(0.0, 0.0),
	is_cun_cam_(false),
	is_hot_pic_(false)
{
	ui.setupUi(this);

	setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

	init();
	initConnect();
}

gunCamSettingDig::~gunCamSettingDig()
{

}


void gunCamSettingDig::setTitleText(const SpyInfo &curr_info)
{
	m_curr_spyInfo = curr_info;
	QString title = QStringLiteral("球机") + m_curr_spyInfo.sIP;
	ui.titleLabel->setText(title);

	ui.label->setScaledContents(true);
	QImage image;
	image.load(QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/pts") + "/" + m_curr_spyInfo.m1Id + "/pano.jpg");
	QPalette palette;
	palette.setBrush(this->backgroundRole(), QBrush(image));
	ui.label->setPixmap(QPixmap::fromImage(image));
}

void gunCamSettingDig::setTitleText(QString tittle)
{
	ui.titleLabel->setText(tittle);

	ui.label->setScaledContents(true);
	QImage image;
	image.load(QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/pts/pano.jpg"));
	QPalette palette;
	palette.setBrush(this->backgroundRole(), QBrush(image));
	ui.label->setPixmap(QPixmap::fromImage(image));
}

void gunCamSettingDig::setPosSet(int x, int y)
{	

}

void gunCamSettingDig::showGunCam()
{
	is_cun_cam_ = true;
	is_hot_pic_ = false;
	//先播放枪机，判断是否能够登录、播放
	gunWgt_ = new gunCamWgt();

	if (!gunWgt_->play(m_curr_spyInfo))
	{
		this->deleteLater();
	}
	gunWgt_->closePlay();
	gunWgt_->deleteLater();


	//每次重置
	if (gun_cam_mini_item_ != NULL)
	{
		gun_cam_mini_item_->deleteLater();
		gun_cam_mini_item_ = NULL;
	}

	gun_cam_mini_item_ = new gunCamMiniItem(this);

	gun_cam_mini_item_->move((m_curr_spyInfo.pos_x / 18000.0)*(float(this->width() / 2)) + this->width() / 2, this->height() / 2 + (m_curr_spyInfo.pos_y / 9000.0) *(float(this->height() / 2)));
	gun_cam_mini_item_->show();



}

void gunCamSettingDig::showHotPic()
{
	is_cun_cam_ = false;
	is_hot_pic_ = true;
	//每次重置
	if (gun_cam_mini_item_ != NULL)
	{
		gun_cam_mini_item_->deleteLater();
		gun_cam_mini_item_ = NULL;
	}

	gun_cam_mini_item_ = new gunCamMiniItem(this);
	gun_cam_mini_item_->move(this->width() / 2, this->height() / 2 );
	gun_cam_mini_item_->show();
}

void gunCamSettingDig::init()
{
}

void gunCamSettingDig::initConnect()
{
	connect(ui.cancelBtn, SIGNAL(clicked()), this, SLOT(slotOnCancel()));
	connect(ui.confirmBtn, SIGNAL(clicked()), this, SLOT(slotOnConfirm()));
}

void gunCamSettingDig::mousePressEvent(QMouseEvent *event)
{
	last_pos_ = gun_cam_mini_item_->pos();
	if (event->type() == QEvent::MouseButtonPress)
	{
		if (event->button() == Qt::LeftButton)
		{
			delta_pos_ = last_pos_ - event->pos();
		}
	}
	QWidget::mousePressEvent(event);

}

void gunCamSettingDig::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		if (delta_pos_.x()<20 && delta_pos_.y()<20)
		{
			gun_cam_mini_item_->move(event->pos() + delta_pos_);
		}

	}

	QWidget::mouseMoveEvent(event);
}

void gunCamSettingDig::mouseReleaseEvent(QMouseEvent *event)
{

}

void gunCamSettingDig::slotOnCancel()
{
	gun_cam_mini_item_->deleteLater();
	gun_cam_mini_item_ = NULL;

	this->hide();
}


void gunCamSettingDig::slotOnConfirm()
{
	if (is_cun_cam_)
	{	//计算经纬度放大100倍，提高精度
		m_curr_spyInfo.pos_x = (float(gun_cam_mini_item_->pos().x() - this->width() / 2) / float(this->width() / 2)) * 18000.0;
		m_curr_spyInfo.pos_y = -(float(this->height() / 2 - gun_cam_mini_item_->pos().y()) / float(this->height() / 2)) * 9000.0;

		socketRequest::instance()->requestOnRegisterSPYDevice(m_curr_spyInfo);

		gun_cam_mini_item_->deleteLater();
		gun_cam_mini_item_ = NULL;

		this->hide();

		Feedback::instance()->maskUI(SET_PRE_POINT_OK);
	}

	else if (is_hot_pic_)
	{	
		//计算经纬度放大100倍，提高精度
		m_curr_spyInfo.pos_x = (float(gun_cam_mini_item_->pos().x() - this->width() / 2) / float(this->width() / 2)) * 18000.0;
		m_curr_spyInfo.pos_y = -(float(this->height() / 2 - gun_cam_mini_item_->pos().y()) / float(this->height() / 2)) * 9000.0;


		///////////////////////////////////////写文件保存////////////////////////////////////////////////////////////
		QDir dir;
		QFile pic_list(QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/Map/hotPic/list.txt"));
		QString initFilePath = QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/Map");
		if (!dir.exists(initFilePath + "/hotPic"))
		{
			dir.mkpath(initFilePath + "/hotPic");
		}
		if (!pic_list.exists())
		{
			pic_list.open(QIODevice::ReadWrite);
			pic_list.close();
		}

		QString hot_pic_path = gun_cam_mini_item_->getHotPicPath();
		if (hot_pic_path=="")
		{
			return;
		}

		QFileInfo fi(hot_pic_path);

		pic_list.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text  );
		QTextStream txtOutput(&pic_list);
		QString s1 = fi.fileName();

		txtOutput.seek(pic_list.size());
		txtOutput << s1 << "---x:" << m_curr_spyInfo.pos_x << "---y:" << m_curr_spyInfo.pos_y << endl;

		pic_list.close();

		/////////////////////////////////////////////////////关闭界面///////////////////////////////////////////////
		gun_cam_mini_item_->deleteLater();
		gun_cam_mini_item_ = NULL;
		this->hide();
		Feedback::instance()->maskUI(SET_PRE_POINT_OK);
	}


}
