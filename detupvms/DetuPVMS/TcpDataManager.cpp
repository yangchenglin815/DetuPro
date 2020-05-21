#include <iostream>
#include <boost/algorithm/string.hpp>

#include "TcpDataManager.hpp"
#include "MessageManager.h"
#include "logging.hpp"
#include "string"



TcpDataManager::TcpDataManager()
{
	api_reg_res_ = new api_detu_client_register_res_list_t();
	api_disk_res_ = NULL;
	//api_record_time_res_ = new api_detu_client_record_query_res_t();
}



void TcpDataManager::SetList(api_detu_client_register_res_t* res)
{
	if (res->curr_num==1)
	{
		//每次有新进来清空列表，重新获取，此时curr_num==1
		free(api_reg_res_);
		api_reg_res_ = NULL;
		api_reg_res_ = new api_detu_client_register_res_list_t();
	}
	if (res->total_num!=0)
	{
		api_reg_res_->numlist = res->total_num;
		memcpy(&api_reg_res_->nvrList[res->curr_num - 1], res, sizeof(api_detu_client_register_res_t));

		if (res->curr_num == res->total_num)
		{
			emit NvrListReceived();
		}
	}
	else
	{
		emit NvrListReceived();
	}

	return;
}

void TcpDataManager::setDiskSizeList(std::vector<api_detu_client_disk_size_t> list)
{
	for (std::vector<api_detu_client_disk_size_t>::iterator iter = list.begin(); iter != list.end(); iter++)
	{
		api_detu_client_disk_size_t skt_t1;
		skt_t1.nCurDiskNum = iter->nCurDiskNum;
		skt_t1.nDiskId = iter->nDiskId;
		skt_t1.nDiskStatus = iter->nDiskStatus;
		skt_t1.nDiskType = iter->nDiskType;
		skt_t1.nTotalDiskNum = iter->nTotalDiskNum;
		skt_t1.nTotalDiskSize = iter->nTotalDiskSize;
		skt_t1.nUsedSize = iter->nUsedSize;
		memcpy(skt_t1.szDeviceId, iter->szDeviceId, API_ARRAY_LEN);
		api_disk_size_list_.push_back(skt_t1);
	}
	emit sigOnGetDiskSize();
	return;
}

void TcpDataManager::setDiskFormat(bool is_ok)
{
	emit sigOnSetDiskFormat(is_ok);
	return;
}

void TcpDataManager::getPlaybackRes(bool is_ok)
{
	emit sigOnGetPlaybackRes(is_ok);
}

void TcpDataManager::handleStreamRes(short result, unsigned char streamId)
{
	if (result == RESULT_SUCCESS)
	{
		emit sigOnHandleStreamSuccess(streamId);
		Log::Debug("stream handle success and streamId is %d", streamId);
	}
	else
	{
		emit sigOnHandleStreamFailed();
		Log::Debug("stream handle failed!");
	}
}

void TcpDataManager::handleRebootDeviceRes(short result, unsigned char streamId)
{
	if (result == RESULT_SUCCESS)
	{
		emit sigOnRebootDeviceSuccess(streamId);
		Log::Debug("Reboot Device success and streamId is %d", streamId);
	}
	else
	{
		emit sigOnRebootDeviceFailed(streamId);
		Log::Debug("Reboot Device failed and streamId is %d", streamId);
	}
}

void TcpDataManager::handleActiveReport(short errCode, std::string PVSId, unsigned char streamId)
{
	emit sigOnActiveReport(errCode, PVSId, streamId);
}

void TcpDataManager::handleGetBandWidth(PVSManageTable_t &apiData)
{
	emit sigOnGetBandWidth(apiData);
}

void TcpDataManager::handleGetPTZList(std::vector<PTZManageTable_t> list)
{
	emit sigOnGetPTZList(list);
}

void TcpDataManager::handleGetSPYList(std::vector<SPYManageTable_t> list)
{
	emit sigOnGetSPYList(list);
}

void TcpDataManager::handleDeletePtz(short result)
{
	emit sigOnDeletePTZ(result);
}

void TcpDataManager::handleDeleteSpy(short result)
{
	emit sigOnDeleteSPY(result);
}

void TcpDataManager::handleGetPtzPoint(QString ip, QString point)
{
	emit sigOnGetPtzPoint(ip, point);
}

void TcpDataManager::handleGetTCSInfo(const api_detu_tcs_register_t &tmpInfo)
{
	emit sigOnGetTCSInfo(tmpInfo);
}

void TcpDataManager::handleUpdateTCSInfo(const api_detu_tcs_heartbeat_t &tmpInfo)
{
	emit sigUpdateTCSInfo(tmpInfo);
}

void TcpDataManager::handleReportTCSError(const api_detu_tcs_transcode_res_t &tmpInfo, short result)
{
	std::string deviceId = (char*)(tmpInfo.szDeviceId);
	emit sigOnReportTCSError(deviceId, result);
}

void TcpDataManager::handleTCSOffLine(const api_detu_tcs_register_t &tmpInfo)
{
	int nServerId = tmpInfo.nServerId;
	emit sigOnReportTCSOffLine(nServerId);
}

void TcpDataManager::handleTCSReset(short result)
{
	if (result == RESULT_SUCCESS)
	{
		emit sigOnHandleTCSReset(true);
	}
	else if (result == RESULT_FAILED)
	{
		emit sigOnHandleTCSReset(false);
	}
}

void TcpDataManager::handleLoginChecked(api_detu_client_register_t api_query, short result)
{
	std::string cuuid = (char*)api_query.szDetuDeviceUUId;

	emit sigOnLoginChecked(cuuid, result);
}

void TcpDataManager::handleRegisterUser(api_detu_client_register_t api_query, short result)
{
	std::string user = (char*)api_query.szDetuUserName;
	std::string passwd = (char*)api_query.szDetuPassWord;
	std::string cUuid = (char*)api_query.szDetuDeviceUUId;

	emit sigOnRegisterUser(user, passwd, cUuid, result);
}

void TcpDataManager::SetRecordTime(std::vector<api_record_query_respond> api_record_time_list)
{

    api_record_time_list_ = api_record_time_list;
	//memcpy(api_record_time_res_, res, sizeof(api_detu_client_record_query_res_t));
	emit RecordTimeReceived();
}

void TcpDataManager::SetMainWindow(DetuPVMS* main_window)
{
	mainwindow_ = main_window;
}

void TcpDataManager::SetRequestVideoSucceed(api_detu_client_request_video_res_t* res)
{
	replay_api_url_ = res;
	QString url = QString(QLatin1String((char*)res->szRtmpURL));
	QString url_ = url[url.length() - 3];
	if (url_ == "0" || url_ == "1"){
		Log::Debug("received playRTMP:%s\n", url.toLocal8Bit().data());
		emit playRequestSucceed();
	}
	else if (url_ == "2" || url_ == "3")
	{
		Log::Debug("received replayRTMP:%s\n", url.toLocal8Bit().data());
		emit ReplayRequestSucceed();
	}
	else if (url_ == "4" || url_ == "5")
	{
		Log::Debug("received MapPlay RTMP:%s\n", url.toLocal8Bit().data());
		emit MapPlayRequestSucceed();
	}
	else if (url_ == "6" || url_ == "7")
	{
		Log::Debug("received MapBack RTMP:%s\n", url.toLocal8Bit().data());
		emit MapBackRequestSucceed();
	}
}

void TcpDataManager::SetRequestVideoFailed()
{
	Log::Debug("received replay failed!");
	emit RecordRequestFailed();
}

void TcpDataManager::ptz_register_res(bool is_ok, unsigned char streamId)
{
	emit sigOnRegisterPTZRes(is_ok, streamId);
}

void TcpDataManager::spy_register_res(bool is_ok, unsigned char streamId)
{
	emit sigOnRegisterSPYRes(is_ok, streamId);
}

void TcpDataManager::setCapturePath(QString path)
{
    capture_path_ = path;
}

void TcpDataManager::breakHeart()
{
	emit sigOnBreakHeart();
}

void TcpDataManager::version_check(bool is_check_ok)
{
	emit sigOnVersionCheck(is_check_ok);
}

void TcpDataManager::getBitRate(api_detu_client_av_param_t* res, unsigned char streamId)
{
	emit sigOnGetBitRate(streamId, res);
}

void TcpDataManager::setBitRate(unsigned char streamId, bool is_Ok)
{
	emit sigOnSetBitRate(streamId, is_Ok);
}
