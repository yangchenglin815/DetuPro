#include "socketRequest.h"
#include "DetuPVMSIni.h"

#include <QDateTime>

socketRequest* socketRequest::m_pInstance = NULL;

socketRequest* socketRequest::instance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new socketRequest;
	}
	return m_pInstance;
}

void socketRequest::requestOnGetBindDeviceList(int type)
{
	protocol_head_t api_head;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = type ? CMD_DETU_CLIENT_GET_SPY_LIST : CMD_DETU_CLIENT_GET_PTZ_LIST;
	api_head.nDataLen = 0;
	api_head.nResult = 0x00;
	api_head.nStreamId = 0;
	//api_head.nReserver = 0x01;        //‘§¡ÙŒª
	api_head.nEndFlags = 0xFA;

	Log::Debug("requestOnGetBindDeviceList : cmd:%d streamid:%d", api_head.nCmd, api_head.nStreamId);

	response res(api_head.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

void socketRequest::requestOnUnbindPTZDevice(const PtzInfo &info)
{
	protocol_head_t api_head;
	PTZManageTable_t api_detu;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_PTZ_REGISTER;
	api_head.nDataLen = api_detu.get_size();
	api_head.nResult = 0x00;
	api_head.nStreamId = 1;
	//api_head.nReserver = 0x01;        //‘§¡ÙŒª
	api_head.nEndFlags = 0xFA;

	memcpy(api_detu.nIP, info.sIP.toLocal8Bit().data(), API_ARRAY_LEN);
	api_detu.nPort = info.wPort;
	memcpy(api_detu.username, info.sUserName.toLocal8Bit().data(), API_ARRAY_LEN);
	memcpy(api_detu.passwd, info.sPasswd.toLocal8Bit().data(), API_ARRAY_LEN);

	response res(api_head.get_size() + api_detu.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
	response_add_resprotocol<PTZManageTable_t>(res, &api_detu);

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

void socketRequest::requestOnUnbindSPYDevice(const SpyInfo &info)
{
	protocol_head_t api_head;
	SPYManageTable_t api_detu;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_SPY_REGISTER;
	api_head.nDataLen = api_detu.get_size();
	api_head.nResult = 0x00;
	api_head.nStreamId = 1;
	//api_head.nReserver = 0x01;        //‘§¡ÙŒª
	api_head.nEndFlags = 0xFA;

	memcpy(api_detu.nIP, info.sIP.toLocal8Bit().data(), API_ARRAY_LEN);
	api_detu.nPort = info.wPort;
	memcpy(api_detu.username, info.sUserName.toLocal8Bit().data(), API_ARRAY_LEN);
	memcpy(api_detu.passwd, info.sPasswd.toLocal8Bit().data(), API_ARRAY_LEN);

	response res(api_head.get_size() + api_detu.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
	response_add_resprotocol<SPYManageTable_t>(res, &api_detu);

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

void socketRequest::requestOnDeletePTZDevice(const PtzInfo &info)
{
	protocol_head_t api_head;
	PTZManageTable_t api_detu;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_DELETE_PTZ;
	api_head.nDataLen = api_detu.get_size();
	api_head.nResult = 0x00;
	api_head.nStreamId = 0;
	//api_head.nReserver = 0x01;        //‘§¡ÙŒª
	api_head.nEndFlags = 0xFA;

	memcpy(api_detu.nIP, info.sIP.toLocal8Bit().data(), API_ARRAY_LEN);
	api_detu.nPort = info.wPort;
	memcpy(api_detu.username, info.sUserName.toLocal8Bit().data(), API_ARRAY_LEN);
	memcpy(api_detu.passwd, info.sPasswd.toLocal8Bit().data(), API_ARRAY_LEN);

	response res(api_head.get_size() + api_detu.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
	response_add_resprotocol<PTZManageTable_t>(res, &api_detu);

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

void socketRequest::requestOnDeleteSPYDevice(const SpyInfo &info)
{
	protocol_head_t api_head;
	SPYManageTable_t api_detu;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_DELETE_SPY;
	api_head.nDataLen = api_detu.get_size();
	api_head.nResult = 0x00;
	api_head.nStreamId = 0;
	//api_head.nReserver = 0x01;        //‘§¡ÙŒª
	api_head.nEndFlags = 0xFA;

	memcpy(api_detu.nIP, info.sIP.toLocal8Bit().data(), API_ARRAY_LEN);
	api_detu.nPort = info.wPort;
	memcpy(api_detu.username, info.sUserName.toLocal8Bit().data(), API_ARRAY_LEN);
	memcpy(api_detu.passwd, info.sPasswd.toLocal8Bit().data(), API_ARRAY_LEN);

	response res(api_head.get_size() + api_detu.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
	response_add_resprotocol<SPYManageTable_t>(res, &api_detu);

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

void socketRequest::requestOnRegisterPTZDevice(const PtzInfo &info)
{
	protocol_head_t api_head;
	PTZManageTable_t api_detu;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_PTZ_REGISTER;
	api_head.nDataLen = api_detu.get_size();
	api_head.nResult = 0x00;
	api_head.nStreamId = 0;
	//api_head.nReserver = 0x01;        //‘§¡ÙŒª
	api_head.nEndFlags = 0xFA;

	memcpy(api_detu.pvsID, info.pvsID.toLocal8Bit().data(), API_ARRAY_LEN);
	memcpy(api_detu.nIP, info.sIP.toLocal8Bit().data(), API_ARRAY_LEN);
	api_detu.nPort = info.wPort;
	memcpy(api_detu.username, info.sUserName.toLocal8Bit().data(), API_ARRAY_LEN);
	memcpy(api_detu.passwd, info.sPasswd.toLocal8Bit().data(), API_ARRAY_LEN);

	response res(api_head.get_size() + api_detu.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
	response_add_resprotocol<PTZManageTable_t>(res, &api_detu);

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

void socketRequest::requestOnRegisterSPYDevice(const SpyInfo &info)
{
	protocol_head_t api_head;
	SPYManageTable_t api_detu;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_SPY_REGISTER;
	api_head.nDataLen = api_detu.get_size();
	api_head.nResult = 0x00;
	api_head.nStreamId = 0;
	//api_head.nReserver = 0x01;        //‘§¡ÙŒª
	api_head.nEndFlags = 0xFA;

	memcpy(api_detu.pvsID, info.pvsID.toLocal8Bit().data(), API_ARRAY_LEN);
	memcpy(api_detu.nIP, info.sIP.toLocal8Bit().data(), API_ARRAY_LEN);
	api_detu.nPort = info.wPort;

	api_detu.nPosX = info.pos_x;
	api_detu.nPosY = info.pos_y;

	memcpy(api_detu.username, info.sUserName.toLocal8Bit().data(), API_ARRAY_LEN);
	memcpy(api_detu.passwd, info.sPasswd.toLocal8Bit().data(), API_ARRAY_LEN);

	response res(api_head.get_size() + api_detu.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
	response_add_resprotocol<SPYManageTable_t>(res, &api_detu);

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

void socketRequest::requestOnSavePTZPoint(QString ip, QString point)
{
	protocol_head_t api_head;
	PtzPoint_t api_detu;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_SAVE_PTZ_POINT;
	api_head.nDataLen = api_detu.get_size();
	api_head.nResult = 0x00;
	api_head.nStreamId = 0;
	//api_head.nReserver = 0x01;        //‘§¡ÙŒª
	api_head.nEndFlags = 0xFA;

	memcpy(api_detu.nIP, ip.toLocal8Bit().data(), API_ARRAY_LEN);
	memcpy(api_detu.nPoint, point.toLocal8Bit().data(), API_ARRAY_LEN);

	response res(api_head.get_size() + api_detu.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
	response_add_resprotocol<PtzPoint_t>(res, &api_detu);

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

void socketRequest::requestOnGetPTZPoint(QString ip)
{
	protocol_head_t api_head;
	PtzPoint_t api_detu;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_GET_PTZ_POINT;
	api_head.nDataLen = api_detu.get_size();
	api_head.nResult = 0x00;
	api_head.nStreamId = 0;
	//api_head.nReserver = 0x01;        //‘§¡ÙŒª
	api_head.nEndFlags = 0xFA;

	memcpy(api_detu.nIP, ip.toLocal8Bit().data(), API_ARRAY_LEN);

	response res(api_head.get_size() + api_detu.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
	response_add_resprotocol<PtzPoint_t>(res, &api_detu);

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

void socketRequest::requestOnAskFroVideo(int type, int requestTime, const deviceInfo &info, int streamId)
{
	protocol_head_t api_head;
	api_detu_client_request_video_t api_detu;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_CLIENT_REQUEST_VIDEO;
	api_head.nDataLen = api_detu.get_size();
	api_head.nResult = 0x00;
	api_head.nStreamId = streamId;
	api_head.nEndFlags = 0xFA;

	memcpy(api_detu.szDeviceId, info.serialNo.toLocal8Bit(), API_ARRAY_LEN);
	api_detu.nDeviceId = info.id;
	api_detu.nStartTime = type ? requestTime : 0;
	api_detu.nEndTime = 0;

	Log::Debug("video requested: cmd:%d steamid:%d requestTime:%s", api_head.nCmd, api_head.nStreamId, QDateTime::fromTime_t(api_detu.nStartTime).toString("hh:mm:ss").toLocal8Bit().data());

	response res(api_head.get_size() + api_detu.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
	response_add_resprotocol<api_detu_client_request_video_t>(res, &api_detu);

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

void socketRequest::requestOnAskFroVideo(int type, int requestTime, const PanoMapPointInfo_t &info, int streamId)
{
	protocol_head_t api_head;
	api_detu_client_request_video_t api_detu;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_CLIENT_REQUEST_VIDEO;
	api_head.nDataLen = api_detu.get_size();
	api_head.nResult = 0x00;
	api_head.nStreamId = streamId;
	api_head.nEndFlags = 0xFA;

	memcpy(api_detu.szDeviceId, info.cameraInfo.serialNo.toLocal8Bit(), API_ARRAY_LEN);
	//api_detu.nDeviceId = info.id;
	switch (type)
	{
	case MAP_PLAY:
		api_detu.nStartTime = 0;
		break;
	case MAP_REPLAY:
		api_detu.nStartTime = requestTime;
		break;
	}
	api_detu.nEndTime = 0;

	Log::Debug("video requested: cmd:%d steamid:%d requestTime:%s", api_head.nCmd, api_head.nStreamId, QDateTime::fromTime_t(api_detu.nStartTime).toString("hh:mm:ss").toLocal8Bit().data());

	response res(api_head.get_size() + api_detu.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
	response_add_resprotocol<api_detu_client_request_video_t>(res, &api_detu);

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}

}

void socketRequest::requestOnAskForStreamInfo(int streamId, deviceInfo infoData)
{
	protocol_head_t api_head;
	api_detu_client_av_param_t api_detu;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_CLIENT_GET_AVPARAM;
	api_head.nDataLen = api_detu.get_size();
	api_head.nResult = 0x00;
	api_head.nStreamId = streamId + 1;
	api_head.nEndFlags = 0xFA;

	QString selectDevice = infoData.serialNo;
	memcpy(api_detu.szDeviceId, selectDevice.toLocal8Bit().data(), API_ARRAY_LEN);
	Log::Debug("Ask For BitRate: cmd:%d streamid:%d deviceId:%s", api_head.nCmd, api_head.nStreamId, selectDevice.toLocal8Bit().data());

	response res(api_head.get_size() + api_detu.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
	response_add_resprotocol<api_detu_client_av_param_t>(res, &api_detu);

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

void socketRequest::requestOnResetTCSConfig()
{
	protocol_head_t api_head;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_CLIENT_TCS_RESET;
	api_head.nDataLen = 0;
	api_head.nEndFlags = 0xFA;

	response res(api_head.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

void socketRequest::requestOnRegisterUser(const QString &user, const QString &passwd)
{
	protocol_head_t api_head;
	api_detu_client_register_t api_reg;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_CLIENT_REGISTER_USER;
	api_head.nDataLen = api_reg.get_size();
	api_head.nStreamId = 0;
	api_head.nEndFlags = 0xFA;

	memcpy(api_reg.szDetuUserName, user.toLatin1().data(), API_ARRAY_LEN);
	memcpy(api_reg.szDetuPassWord, passwd.toLatin1().data(), API_ARRAY_LEN);
	Log::Info("Register Request : CMD:%d, uuid:%s, username:%s, passwd:%s", api_head.nCmd, api_reg.szDetuDeviceUUId, api_reg.szDetuUserName, api_reg.szDetuPassWord);

	response res(api_head.get_size() + api_reg.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
	response_add_resprotocol<api_detu_client_register_t>(res, &api_reg);

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

void socketRequest::requestOnLoginChecked(const QString &user, const QString &passwd, const QString &quuid)
{
	protocol_head_t api_head;
	api_detu_client_register_t api_reg;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_CLIENT_LOGIN_CHECKED;
	api_head.nDataLen = api_reg.get_size();
	api_head.nStreamId = 0;
	api_head.nEndFlags = 0xFA;

	memcpy(api_reg.szDetuDeviceUUId, quuid.toLatin1().data(), API_ARRAY_LEN);
	memcpy(api_reg.szDetuUserName, user.toLatin1().data(), API_ARRAY_LEN);
	memcpy(api_reg.szDetuPassWord, passwd.toLatin1().data(), API_ARRAY_LEN);
	Log::Info("Login Checked : CMD:%d, uuid:%s, username:%s, passwd:%s", api_head.nCmd, api_reg.szDetuDeviceUUId, api_reg.szDetuUserName, api_reg.szDetuPassWord);

	response res(api_head.get_size() + api_reg.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
	response_add_resprotocol<api_detu_client_register_t>(res, &api_reg);

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

socketRequest::socketRequest(QObject *parent)
	: QObject(parent)
{

}

socketRequest::~socketRequest()
{

}
