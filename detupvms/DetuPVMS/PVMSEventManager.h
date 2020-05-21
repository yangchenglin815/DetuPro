#pragma once

#include <QObject>
#include <QTimer>

#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>

#include "UiSingleton.h"

#define  PVMSEventManagerManagerIns PVMSEventManager::Instance()

struct CpuPara  
{
	int nCpuRate = -1;
	int nMemTotal = -1;
	int nMemUsed = -1;
	int nDiskTotal = -1;
	int nDiskUsed = -1;
	int nMemRate = -1;
	int nDiskRate = -1;
};

class IsysWin;

class PVMSEventManager : public QObject, public CUiSingleton<PVMSEventManager>
{
	Q_OBJECT
		friend class CUiSingleton<PVMSEventManager>;
public:
	PVMSEventManager();
	~PVMSEventManager();

	void startEvent();
	void stopEvent();

	virtual void EventUpdate(int totaltime);

signals:
	void sigOnInitTimeShow();
	void sigOnInitHeartBeat();
	void sigOnUpdateList();

	void sigOnCheckWarningBoard();

	void sigOnSetFullScreen(bool is_full_screen);
	void sigOnReplaySetFullScreen(bool is_full_screen);


private slots :
	void timerEventUpdate();

private:
	void cpuThread();
private:
	QTimer *timer_;
	float total_time_;

	IsysWin *pISys_;  //windowsµ˜”√¿‡

	boost::shared_ptr<boost::thread> cpuThread_ = NULL;
	boost::mutex mutex_;

public:
	CpuPara cpu_para_;
};

