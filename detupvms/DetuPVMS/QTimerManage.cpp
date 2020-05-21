#include "QTimerManage.h"

QTimerManage* QTimerManage::m_plnstance = NULL;

QTimerManage* QTimerManage::instance()
{
	if (m_plnstance == NULL)
	{
		m_plnstance = new QTimerManage;
	}
	return m_plnstance;
}

void QTimerManage::initTimer(QString deviceID)
{
	QTimer *timer = new QTimer(this);

	TimerBindInfo_t timerInfo;
	timerInfo.szTimer = timer;
	m_timer_map.insert(deviceID, timerInfo);
	m_deviceID = deviceID;

	connect(timer, SIGNAL(timeout()), this, SLOT(slotOnTimerFunc()));
	timer->setInterval(1000);
	timer->start();
}

void QTimerManage::closeTimer(QString deviceID)
{
	int index = -1;
	QMapIterator<QString, TimerBindInfo_t> i(m_timer_map);
	while (i.hasNext()) {
		i.next();
		if (i.key() == deviceID)
		{
			i.value().szTimer->stop();
			i.value().szTimer->deleteLater();
			 
			index++;
		}
	}

	if (index > -1){
		m_timer_map.remove(deviceID);
	}

	emit sigOnStopTimer(m_deviceID);
}

QTimerManage::QTimerManage(QObject *parent)
	: QObject(parent)
{

}

QTimerManage::~QTimerManage()
{

}

void QTimerManage::slotOnTimerFunc()
{
	int val = m_timer_map[m_deviceID].interVal++;
	emit sigOnUpdateTimer(val, m_deviceID);
}
