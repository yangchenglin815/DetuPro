#include "panoramaItemWidget.h"
#include "logging.hpp"

panoramaItemWidget::panoramaItemWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	
	m_deleteBtn = new QPushButton(this);
	connect(m_deleteBtn, SIGNAL(clicked()), this, SIGNAL(sigOnDeleteItem()));
	m_deleteBtn->resize(QSize(10, 10));
	m_deleteBtn->setText("");
	m_deleteBtn->setStyleSheet("	QPushButton{border-image:url(:/image/image/deleteItem.png);}QPushButton::hover{border-image:url(:/image/image/deleteItemb.png);}QPushButton::pressed{padding:1px;margin:1px;}");
	m_deleteBtn->move(width() - 24, (height() - 10) / 2);
	m_deleteBtn->setVisible(false);
}

panoramaItemWidget::~panoramaItemWidget()
{

}

void panoramaItemWidget::initData(PanoMapPointInfo_t info_t)
{
	m_panoramaInfo = info_t;

	if (info_t.map_point_type == PANOSCENE_ON_LINE)
	{
		ui.deviceLabel->setText(info_t.sceneInfo.name);
		QString pictureStyle = QString("#widget{background:rgba(24,25,25,1);}#deviceLabel{font-family:%1;font-size:12px;color:rgba(238,238,238,1);}#iconLabel{border-image:url(:/image/image/pictureOn.png);}#label{border-image:url(:/image/image/showNew.png);}").arg(QStringLiteral("Î¢ÈíÑÅºÚ"));
		setStyleSheet(pictureStyle);
	}
	else if (info_t.map_point_type == DEVICE_ON_LINE)
	{
		QString cameraStyle;
		ui.deviceLabel->setText(info_t.cameraInfo.name);
		if (info_t.cameraInfo.status)
		{
			   cameraStyle = QString("#widget{background:rgba(24,25,25,1);}#deviceLabel{font-family:%1;font-size:12px;color:rgba(238,238,238,1);}#iconLabel{border-image:url(:/image/image/cameraOn.png)}#label{border-image:url(:/image/image/showNew.png);}").arg(QStringLiteral("Î¢ÈíÑÅºÚ"));
		}
		else
		{
			   cameraStyle = QString("#widget{background:rgba(24,25,25,1);}#deviceLabel{font-family:%1;font-size:12px;color:rgba(204,204,204,1);}#iconLabel{border-image:url(:/image/image/cameraOff.png)}#label{border-image:url(:/image/image/showNew.png);}").arg(QStringLiteral("Î¢ÈíÑÅºÚ"));
		}
		setStyleSheet(cameraStyle);
	}
}

void panoramaItemWidget::getItemData(PanoMapPointInfo_t &info_t)
{
	info_t = m_panoramaInfo;
}


void panoramaItemWidget::setItemData(PanoMapPointInfo_t &info_t)
{
	m_panoramaInfo = info_t;
}

void panoramaItemWidget::setDeleteChecked(bool checked)
{
	m_deleteBtn->setVisible(checked);
}

void panoramaItemWidget::setNewHidden(bool hidden)
{
	if (ui.label)
	{
		ui.label->setHidden(hidden);
	}
	m_panoramaInfo.onMapFlag = hidden;
}

bool panoramaItemWidget::getNewHidden()
{
	return ui.label->isHidden();
}

void panoramaItemWidget::removeId(int id)
{
	m_panoramaInfo.sequencer_point_info_map_.remove(id);
}

void panoramaItemWidget::enterEvent(QEvent *event)
{
	setCursor(Qt::PointingHandCursor);
	if (m_panoramaInfo.map_point_type == PANOSCENE_ON_LINE)
	{
		QString pictureStyle = QString("#widget{background:rgba(24,25,25,1);border:1px solid #00A092;}#deviceLabel{font-family:%1;font-size:12px;color:rgba(238,238,238,1);}#iconLabel{border-image:url(:/image/image/pictureOn.png)}#label{border-image:url(:/image/image/showNew.png);}").arg(QStringLiteral("Î¢ÈíÑÅºÚ"));
		setStyleSheet(pictureStyle);
	}
	else if (m_panoramaInfo.map_point_type == DEVICE_ON_LINE)
	{
		QString cameraStyle;
		if (m_panoramaInfo.cameraInfo.status)
		{
			cameraStyle = QString("#widget{background:rgba(24,25,25,1);border:1px solid #00A092;}#deviceLabel{font-family:%1;font-size:12px;color:rgba(238,238,238,1);}#iconLabel{border-image:url(:/image/image/cameraOn.png)}#label{border-image:url(:/image/image/showNew.png);}").arg(QStringLiteral("Î¢ÈíÑÅºÚ"));
		}
		else
		{
			cameraStyle = QString("#widget{background:rgba(24,25,25,1);border:1px solid #00A092;}#deviceLabel{font-family:%1;font-size:12px;color:rgba(204,204,204,1);}#iconLabel{border-image:url(:/image/image/cameraOff.png)}#label{border-image:url(:/image/image/showNew.png);}").arg(QStringLiteral("Î¢ÈíÑÅºÚ"));
		}
		setStyleSheet(cameraStyle);
	}
}

void panoramaItemWidget::leaveEvent(QEvent *event)
{
	setCursor(Qt::ArrowCursor);
	if (m_panoramaInfo.map_point_type == PANOSCENE_ON_LINE)
	{
		QString pictureStyle = QString("#widget{background:rgba(24,25,25,1);}#deviceLabel{font-family:%1;font-size:12px;color:rgba(238,238,238,1);}#iconLabel{border-image:url(:/image/image/pictureOn.png)}#label{border-image:url(:/image/image/showNew.png);}").arg(QStringLiteral("Î¢ÈíÑÅºÚ"));
		setStyleSheet(pictureStyle);
	}
	else if (m_panoramaInfo.map_point_type == DEVICE_ON_LINE)
	{
		QString cameraStyle;
		if (m_panoramaInfo.cameraInfo.status)
		{
			cameraStyle = QString("#widget{background:rgba(24,25,25,1);}#deviceLabel{font-family:%1;font-size:12px;color:rgba(238,238,238,1);}#iconLabel{border-image:url(:/image/image/cameraOn.png)}#label{border-image:url(:/image/image/showNew.png);}").arg(QStringLiteral("Î¢ÈíÑÅºÚ"));
		}
		else
		{
			cameraStyle = QString("#widget{background:rgba(24,25,25,1);}#deviceLabel{font-family:%1;font-size:12px;color:rgba(204,204,204,1);}#iconLabel{border-image:url(:/image/image/cameraOff.png)}#label{border-image:url(:/image/image/showNew.png);}").arg(QStringLiteral("Î¢ÈíÑÅºÚ"));
		}
		setStyleSheet(cameraStyle);
	}
}
