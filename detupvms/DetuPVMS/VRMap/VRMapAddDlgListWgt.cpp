#include "VRMapAddDlgListWgt.h"
#include <QHBoxLayout>
#include <QTimer>

VRMapAddDlgListWgt::VRMapAddDlgListWgt(QWidget *parent)
	: QWidget(parent)
{
	
}

VRMapAddDlgListWgt::~VRMapAddDlgListWgt()
{

}

void VRMapAddDlgListWgt::initAddPanoramaCamera(deviceInfo info)
{
	m_deviceInfo = info;

	QHBoxLayout *hboxLayout_ = new QHBoxLayout(this);
	hboxLayout_->setSpacing(0);
	hboxLayout_->setContentsMargins(0, 0, 0, 0);
	QWidget *widget_ = new QWidget(this);
	widget_->setFixedSize(QSize(320, 30));
	QHBoxLayout *hboxLayout = new QHBoxLayout(widget_);
	hboxLayout->setSpacing(6);
	hboxLayout->setContentsMargins(9, 0, 6, 0);
	m_checkBox = new QCheckBox(widget_);
	hboxLayout->addWidget(m_checkBox);
	m_labelName = new QLabel(widget_);
	hboxLayout->addWidget(m_labelName);
	m_labelNo = new QLabel(widget_);
	hboxLayout->addWidget(m_labelNo);

	widget_->setStyleSheet("border-top:none;border-left:none;border-right:none;");
	m_labelName->setStyleSheet(QString("border:none;font-size:12px;font-family:%1;color:rgba(102,102,102,1);").arg(QStringLiteral("Î¢ÈíÑÅºÚ")));
	m_labelNo->setStyleSheet(QString("border:none;font-size:12px;font-family:%1;color:rgba(102,102,102,1);").arg(QStringLiteral("Î¢ÈíÑÅºÚ")));
	m_checkBox->setStyleSheet("QCheckBox{spacing:5px;border:none;}" \
		                                                 "QCheckBox::indicator{width: 18px;height:18px;}" \
                                                         "QCheckBox::indicator:checked{image:url(:/image/image/addCheckboxb.png);}" \
                                                         "QCheckBox::indicator:unchecked{image:url(:/image/image/addCheckbox.png);}");
	m_labelName->setText(info.name);
	m_labelNo->setText(info.serialNo);
}


void VRMapAddDlgListWgt::initAddPanoramaScene(PanoSceneInfo info)
{
	m_PanoSceneInfo = info;

	QHBoxLayout *hboxLayout_ = new QHBoxLayout(this);
	hboxLayout_->setSpacing(0);
	hboxLayout_->setContentsMargins(0, 0, 0, 0);
	QWidget *widget_ = new QWidget(this);
	widget_->setFixedSize(QSize(320, 50));
	QHBoxLayout *hboxLayout = new QHBoxLayout(widget_);
	hboxLayout->setSpacing(6);
	hboxLayout->setContentsMargins(9, 0, 6, 0);
	m_checkBox = new QCheckBox(widget_);
	hboxLayout->addWidget(m_checkBox);
	m_labelName = new QLabel(widget_);
	hboxLayout->addWidget(m_labelName);
	m_labelNo = new QLabel(widget_);
	hboxLayout->addWidget(m_labelNo);

	widget_->setStyleSheet("border-top:none;border-left:none;border-right:none;");
	m_labelName->setStyleSheet(QString("border:none;font-size:12px;font-family:%1;color:rgba(102,102,102,1);").arg(QStringLiteral("Î¢ÈíÑÅºÚ")));
	m_labelNo->setStyleSheet("border:none;");
	m_checkBox->setStyleSheet("QCheckBox{spacing:5px;border:none;}" \
		"QCheckBox::indicator{width: 18px;height:18px;}" \
		"QCheckBox::indicator:checked{image:url(:/image/image/addCheckboxb.png);}" \
		"QCheckBox::indicator:unchecked{image:url(:/image/image/addCheckbox.png);}");
	m_labelName->setText(info.name);
	m_labelNo->resize(QSize(80, 40));

	QImage image(info.sceneList[0].Path);
	image = image.scaled(80, 40);
	m_labelNo->setPixmap(QPixmap::fromImage(image));

	if (info.sceneList.size() > 1)
	{
		QLabel *numLabel = new QLabel(m_labelNo);
		numLabel->setText(QString::number(info.sceneList.size()));
		numLabel->resize(QSize(17, 17));
		numLabel->setAlignment(Qt::AlignCenter);
		numLabel->setStyleSheet(QString("font-size:12px;font-family:%1;color:rgba(255,255,255,1);" \
			"background:rgba(0,0,0,0.6);border-radius:8px;").arg(QStringLiteral("Î¢ÈíÑÅºÚ")));
		numLabel->show();
		numLabel->move((80 - 19), 7);
	}
}

void VRMapAddDlgListWgt::setItemChecked(bool checked)
{
	if (m_checkBox)
	{
		m_checkBox->setChecked(checked);
	}
}

void VRMapAddDlgListWgt::onItemSelected()
{
	m_checkBox->setChecked(!m_checkBox->isChecked());
}

void VRMapAddDlgListWgt::getInfoBySelectedItem(deviceInfo &info)
{
	info = m_deviceInfo;
}

void VRMapAddDlgListWgt::getSceneBySelectedItem(PanoSceneInfo &info)
{
	info = m_PanoSceneInfo;
}
