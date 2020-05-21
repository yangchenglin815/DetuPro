#include <QEvent> 
#include <QMouseEvent> 
#include <QDebug>
#include "GlViewSetingWgt.h"

#include "GlViewSettingItemWgt.h"

//初始化控制器
#include "MapPointListManager.h"

GlViewSetingWgt::GlViewSetingWgt(QWidget *parent)
	: QWidget(parent)
	, gl_view_setting_item_(NULL)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground, false);

	connect(ui.confirmBtn, SIGNAL(clicked()), this, SLOT(slotOnConfirmClicked()));
}

GlViewSetingWgt::~GlViewSetingWgt()
{

}

void GlViewSetingWgt::setPanoParam(PanoMapPointInfo_t panoramaInfo)
{
	panoramaInfo_ = panoramaInfo;

	if (panoramaInfo_.map_point_type == DEVICE_ON_LINE || panoramaInfo_.map_point_type == DEVICE_OFF_LINE)
	{

		QString pano_path = QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/pts") + "/" + panoramaInfo_.cameraInfo.m1DeviceId + "/pano.jpg";

		setPanoImg(pano_path);
	}
	else
	{
		//默认打开第一个
		setPanoImg(panoramaInfo_.sceneInfo.sceneList.at(0).Path );
	}
}


void GlViewSetingWgt::slotOnConfirmClicked()
{
	float angle = -((float(gl_view_setting_item_->pos().x()) + 17.0 - 100.0) / 100.0) * 180.0;

	qDebug() << angle;

	emit sigOnUpdateInitAngle(angle);
	MapPointListManagerIns.setInitAngle(panoramaInfo_.curr_id, angle);

	this->hide();
}

void GlViewSetingWgt::mousePressEvent(QMouseEvent *event)
{
	last_pos_ = gl_view_setting_item_->pos();
	if (event->type() == QEvent::MouseButtonPress)
	{
		if (event->button() == Qt::LeftButton)
		{
			delta_pos_ = last_pos_ - event->pos();
		}
	}
	QWidget::mousePressEvent(event);
}

void GlViewSetingWgt::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		if (event->pos().x() + delta_pos_.x()>0 && event->pos().x() + delta_pos_.x()<165)
		{
			gl_view_setting_item_->move(event->pos().x() + delta_pos_.x(), 31);
		}
	}

	QWidget::mouseMoveEvent(event);
}

void GlViewSetingWgt::mouseReleaseEvent(QMouseEvent *event)
{
	//通知保存初始角度
	QWidget::mouseReleaseEvent(event);
}

void GlViewSetingWgt::setPanoImg(QString img_path)
{
	ui.img_label_->setScaledContents(true);
	QImage pano_img(img_path);
	QPalette palette;
	palette.setBrush(this->backgroundRole(), QBrush(pano_img));
	ui.img_label_->setPixmap(QPixmap::fromImage(pano_img));

	//每次重置
	if (gl_view_setting_item_ != NULL)
	{
		gl_view_setting_item_->deleteLater();
		gl_view_setting_item_ = NULL;
	}

	gl_view_setting_item_ = new GlViewSettingItemWgt(this);

	gl_view_setting_item_->move(100 - 17 - panoramaInfo_.initial_angle *100.0 / 180.0, 31);

	qDebug() << panoramaInfo_.initial_angle;
	qDebug() << 100 - 17 - panoramaInfo_.initial_angle *100.0 / 180.0;

	gl_view_setting_item_->show();

}

