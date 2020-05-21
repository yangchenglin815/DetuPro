#ifndef SOCKETREQUEST_H
#define SOCKETREQUEST_H

#include <QObject>

#include "constStruct.h"
#include "APIProtocol.h"
#include "dmconnection.hpp"
#include "SocketManager.h"

class socketRequest : public QObject
{
	Q_OBJECT
public:
	static socketRequest* instance();
	void requestOnGetBindDeviceList(int type);
	void requestOnUnbindPTZDevice(const PtzInfo &info);
	void requestOnUnbindSPYDevice(const SpyInfo &info);
	void requestOnDeletePTZDevice(const PtzInfo &info);
	void requestOnDeleteSPYDevice(const SpyInfo &info);

	void requestOnRegisterPTZDevice(const PtzInfo &info);
	void requestOnRegisterSPYDevice(const SpyInfo &info);


	void requestOnSavePTZPoint(QString ip, QString point);
	void requestOnGetPTZPoint(QString ip);
	void requestOnAskFroVideo(int type, int requestTime, const deviceInfo &info, int streamId);

	void requestOnAskFroVideo(int type, int requestTime, const PanoMapPointInfo_t &info, int streamId);

	void requestOnAskForStreamInfo(int streamId, deviceInfo infoData);

	void requestOnResetTCSConfig();
	void requestOnRegisterUser(const QString &user, const QString &passwd);  //客户端注册请求
	void requestOnLoginChecked(const QString &user, const QString &passwd, const QString &quuid);   //客户端登录校验请求
private:
	explicit socketRequest(QObject *parent = 0);
	~socketRequest();
private:
	static socketRequest* m_pInstance;
	
};

#endif // SOCKETREQUEST_H
