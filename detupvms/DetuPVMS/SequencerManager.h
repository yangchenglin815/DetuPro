/************************************************
* \file SequencerManager.h
*
* \author HuZhengdong
* \date 20171207
* ³¡¾°ÇÐ»»×ø±ê±ä»»
************************************************/

#pragma once

#include <iostream>
#include <string>
#include <map>
#include <QObject>
#include <memory>

#include "UiSingleton.h"

#define  SequencerManagerIns SequencerManager::Instance()

class SequencerManager : public QObject, public CUiSingleton<SequencerManager>
{
	Q_OBJECT
		friend class CUiSingleton<SequencerManager>;

public:
	SequencerManager();

public slots:
void SlotToTrigSequencer(double yaw, double pitch);

signals:
void SignalToTrigArrowRotate(double yaw, double pitch);


};

