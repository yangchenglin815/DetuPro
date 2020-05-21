#ifndef WEATHER_PEOPLEFLOW_H
#define WEATHER_PEOPLEFLOW_H

#include <QWidget>
#include "ui_weather_peopleflow.h"

class weather_peopleflow : public QWidget
{
	Q_OBJECT

public:
	weather_peopleflow(QWidget *parent = 0);
	~weather_peopleflow();

public slots:
	void slotOnSetWeatherImg();

private:
	Ui::weather_peopleflow ui;
};

#endif // WEATHER_PEOPLEFLOW_H
