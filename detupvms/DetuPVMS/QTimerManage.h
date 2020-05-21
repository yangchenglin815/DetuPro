#ifndef QTIMERMANAGE_H
#define QTIMERMANAGE_H

#include <QObject>
#include <QTimer>
#include <QMap>

typedef struct TimerBindInfo
{
	QTimer *szTimer;
	int interVal;
	TimerBindInfo(){
		interVal = 0;
	}
}TimerBindInfo_t;
Q_DECLARE_METATYPE(TimerBindInfo)

class QTimerManage : public QObject
{
	Q_OBJECT

public:
	static QTimerManage* instance();
	void initTimer(QString deviceID);
	void closeTimer(QString deviceID);
private:
	explicit QTimerManage(QObject *parent = 0);
	~QTimerManage();
signals:
	void sigOnUpdateTimer(int val, QString deviceID);
	void sigOnStopTimer(QString deviceID);
public slots:
	void slotOnTimerFunc();
private:
	static QTimerManage* m_plnstance;
	QMap<QString, TimerBindInfo_t> m_timer_map;
	QString m_deviceID;
};

#endif // QTIMERMANAGE_H
