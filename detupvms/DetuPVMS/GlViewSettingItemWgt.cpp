#include "GlViewSettingItemWgt.h"

GlViewSettingItemWgt::GlViewSettingItemWgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//setAttribute(Qt::WA_TranslucentBackground);
	setFixedSize(35, 80);

	QPixmap map(":/image/image/glviewsetting.png");
	setAutoFillBackground(true);
	QPalette palette;
	QSize temp;
	palette.setBrush(this->backgroundRole(), QBrush(map.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
	setPalette(palette);


}

GlViewSettingItemWgt::~GlViewSettingItemWgt()
{

}

void GlViewSettingItemWgt::mousePressEvent(QMouseEvent *event)
{
	QWidget::mousePressEvent(event);
}

void GlViewSettingItemWgt::mouseMoveEvent(QMouseEvent *event)
{
	QWidget::mouseMoveEvent(event);
}

void GlViewSettingItemWgt::mouseReleaseEvent(QMouseEvent *event)
{
	QWidget::mouseReleaseEvent(event);

}
