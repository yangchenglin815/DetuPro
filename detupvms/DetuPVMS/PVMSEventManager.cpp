#include "PVMSEventManager.h"
#include "DetuPVMSIni.h"

#include "isysinfo.h"
#include "isyswin.h"
#include "logging.hpp"

#define  TIMER_INTERVAL 10

PVMSEventManager::PVMSEventManager() :total_time_(10)
, pISys_(NULL)
{
	pISys_ = new IsysWin();
	timer_ = new QTimer();
	timer_->setInterval(TIMER_INTERVAL);
	connect(timer_, SIGNAL(timeout()), this, SLOT(timerEventUpdate()));
}


PVMSEventManager::~PVMSEventManager()
{

}


void PVMSEventManager::startEvent(){
	if (timer_ != NULL)
	{
		timer_->start();
	}
	

}

void PVMSEventManager::stopEvent(){
	if (timer_ != NULL)
	{
		timer_->stop();
	}

}

void PVMSEventManager::timerEventUpdate(){
	
	total_time_ += TIMER_INTERVAL;
	this->EventUpdate(total_time_);
}

void PVMSEventManager::cpuThread()
{
	if (pISys_){
		pISys_->GetSysCpu(cpu_para_.nCpuRate);
		if (!(pISys_->GetSysMemory(cpu_para_.nMemTotal, cpu_para_.nMemUsed)))
		{
			Log::Debug("Get SysMemory failed");
			return;
		}
		pISys_->GetSysDisk(cpu_para_.nDiskTotal, cpu_para_.nDiskUsed);
		cpu_para_.nMemRate = (int)ceil(100.0*(cpu_para_.nMemUsed) / (cpu_para_.nMemTotal));
		cpu_para_.nDiskRate = (int)ceil(100.0*(cpu_para_.nDiskTotal - cpu_para_.nDiskUsed) / (cpu_para_.nDiskTotal));
	}
}

void  PVMSEventManager::EventUpdate(int totaltime)
{	
	//5秒刷一次CPU
	if (totaltime % 5000 == 0)
	{
		if (cpuThread_ && cpuThread_->joinable())
		{
			cpuThread_->join();
		}
		cpuThread_.reset(new boost::thread(&PVMSEventManager::cpuThread, this));
	}

	if (totaltime % 1000 == 0)
	{
		emit sigOnInitTimeShow();
	}

	if (totaltime %( DetuPVMSIni::getHeartBeat()*1000 )== 0)
	{
		emit sigOnInitHeartBeat();
	}

	if (totaltime % 15000 == 0)
	{
		emit sigOnUpdateList();
	}

	if (totaltime % 10000 == 0)
	{
		//通知检测报警
		//emit sigOnCheckWarningBoard();
	}
}