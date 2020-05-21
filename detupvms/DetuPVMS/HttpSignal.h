#ifndef HTTPSIGNAL_H
#define HTTPSIGNAL_H

#include <QObject>

class HttpSignal : public QObject
{
	Q_OBJECT

public:
	static HttpSignal* instance();
signals:
	void sigOnGetSrsInfo(int id, bool state);
	void sigOnNetWorkError(int error);
	void sigOnPVSIDError();
	void sigOnRequestNetWork();

	void sigOnReplayGetSrsInfo(int id, bool state);
	void sigOnReplayNetWorkError(int error);
	void sigOnReplayRequestNetWork();
	void sigOnReplayPVSIDError();

	void sigOnMapGetSrsInfo(int id, bool state);
	void sigOnMapNetWorkError(int error);
	void sigOnMapPVSIDError();
	void sigOnMapRequestNetWork();

	void sigOnMapBackGetSrsInfo(int id, bool state);
	void sigOnMapBackNetWorkError(int error);
	void sigOnMapBackPVSIDError();
	void sigOnMapBackRequestNetWork();

private:
	explicit HttpSignal(QObject *parent = 0);
	~HttpSignal();
private:
	static HttpSignal* m_pInstance;
};

#endif // HTTPSIGNAL_H
