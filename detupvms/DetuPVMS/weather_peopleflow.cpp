#include "weather_peopleflow.h"

#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QGraphicsOpacityEffect>
weather_peopleflow::weather_peopleflow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.weather, SIGNAL(clicked()), this, SLOT(slotOnSetWeatherImg()));


	QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
	this->setGraphicsEffect(opacityEffect);
	//opacityEffect->setOpacity(0.7);
}

weather_peopleflow::~weather_peopleflow()
{

}

void weather_peopleflow::slotOnSetWeatherImg()
{
	QString weather_path = QFileDialog::getOpenFileName(this, tr("Open Weather"), QDir::homePath() + "/AppData/Local/Pano-VMS/Map/panoMap", tr("Image Files (*.png *.jpg *.bmp)"));
	QPixmap weather_img(weather_path);
	if (weather_path == "")
	{
		return;
	}
	ui.weather->setFlat(true);
	QSize temp(300, 236);
	ui.weather->setIconSize(temp);
	ui.weather->setIcon(weather_img);

}

