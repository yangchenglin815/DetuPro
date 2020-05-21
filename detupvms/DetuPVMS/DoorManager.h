#pragma once

#include <QObject>

#include <stdio.h>   
#include <windows.h>  

#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>

#include "logging.hpp"

class DoorManager :public QObject
{
	Q_OBJECT

public:
	DoorManager();
	~DoorManager();

public slots:
	void slotOnOpenDoor(int in_or_out);

public:
	void openDoor(int in_or_out);

private: 

};

