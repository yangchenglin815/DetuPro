#include <iostream>
#include <string>
#include <map>
#include <QObject>
#include <memory>

#include "APIProtocol.h"
#include "UiSingleton.h"

using namespace dm::server;


#define  TcpDataManagerIns TcpDataManager::Instance()

class DetuPVMS;

class TcpDataManager :public QObject, public CUiSingleton<TcpDataManager>
{
    Q_OBJECT
	friend class CUiSingleton<TcpDataManager>;
private:
	TcpDataManager();

public:
	void SetList(api_detu_client_register_res_t* res);
	//获取磁盘容量
	void setDiskSizeList(std::vector<api_detu_client_disk_size_t> list);
	//格式化磁盘
	void setDiskFormat(bool is_ok);
	//回放控制返回
	void getPlaybackRes(bool is_ok);
	//流处理返回
	void handleStreamRes(short result, unsigned char streamId);
	//重启设备返回
	void handleRebootDeviceRes(short result, unsigned char streamId);
	//PVS主动上报
	void handleActiveReport(short errCode, std::string PVSId, unsigned char streamId);
	//获取带宽
	void handleGetBandWidth(PVSManageTable_t &apiData);
	//获取球机列表
	void handleGetPTZList(std::vector<PTZManageTable_t> list);
	//获取枪机列表
	void handleGetSPYList(std::vector<SPYManageTable_t> list);
	//删除球机
	void handleDeletePtz(short result);
	//删除枪机
	void handleDeleteSpy(short result);
	//获取球机预置点
	void handleGetPtzPoint(QString ip, QString point);
	//获取转码服务信息
	void handleGetTCSInfo(const api_detu_tcs_register_t &tmpInfo);
	//
	void handleUpdateTCSInfo(const api_detu_tcs_heartbeat_t &tmpInfo);
	//
	void handleReportTCSError(const api_detu_tcs_transcode_res_t &tmpInfo, short result);
	//
	void handleTCSOffLine(const api_detu_tcs_register_t &tmpInfo);
	void handleTCSReset(short result);
	//客户端登录校验
	void handleLoginChecked(api_detu_client_register_t api_query, short result);
	//客户端注册用户请求
	void handleRegisterUser(api_detu_client_register_t api_query, short result);

	api_detu_client_register_res_list_t* GetList(){ return api_reg_res_; };

    void SetRecordTime(std::vector<api_record_query_respond> api_record_time_list);
	std::vector<api_detu_client_disk_size_t>GetDiskSizeList(){ return api_disk_size_list_; };
	void clearData(){ api_disk_size_list_.clear(); };
    std::vector<api_record_query_respond> GetRecordTime(){ return api_record_time_list_; };
	api_detu_client_request_video_res_t* GetRequestTime(){ return replay_api_url_; };

	void SetMainWindow(DetuPVMS* main_window);
	void SetRequestVideoSucceed(api_detu_client_request_video_res_t* res);
	void SetRequestVideoFailed();
	//球机注册成功返回
	void ptz_register_res(bool is_ok, unsigned char streamId);
	//枪机注册成功返回
	void spy_register_res(bool is_ok, unsigned char streamId);
	//
    void setCapturePath(QString path);
    QString getCapturePath(){ return capture_path_; };
	//心跳
	void breakHeart();
	//版本信息
	void version_check(bool is_check_ok);
	//获取码率信息
	void getBitRate(api_detu_client_av_param_t* res, unsigned char streamId);
	//设置码率信息
	void setBitRate(unsigned char streamId, bool is_Ok);

signals:
	void DetuClientLoginOk();
	void DetuClientLoginFailed();
    void NvrListReceived();
	void sigOnGetDiskSize();
	void RecordTimeReceived();
	void sigOnLoginChecked(std::string cuuid, short result);
	void sigOnRegisterUser(std::string user, std::string passwd, std::string cUuid, short result);

	void ReplayRequestSucceed();
	void playRequestSucceed();
	void MapPlayRequestSucceed();
	void MapBackRequestSucceed();

	void RecordRequestFailed();

	void sigOnSetDiskFormat(bool is_ok);
	void sigOnGetPlaybackRes(bool is_ok);
	//心跳
	void sigOnBreakHeart();
	//版本信息
	void sigOnVersionCheck(bool is_check_ok);
	//获取码率信息
	void sigOnGetBitRate(unsigned char streamId, api_detu_client_av_param_t *res);
	//设置码率信息
	void sigOnSetBitRate(unsigned char streamId, bool is_Ok);
	//球机注册返回信号
	void sigOnRegisterPTZRes(bool is_ok, unsigned char streamId);
	//枪机注册返回信号
	void sigOnRegisterSPYRes(bool is_ok, unsigned char streamId);
	//PVS主动上报
	void sigOnActiveReport(short errCode, std::string PVSId, unsigned char streamId);
	//获取带宽
	void sigOnGetBandWidth(PVSManageTable_t apiData);
	//获取球机列表
	void sigOnGetPTZList(std::vector<PTZManageTable_t> list);
	//获取枪机列表
	void sigOnGetSPYList(std::vector<SPYManageTable_t> list);
	//删除球机
	void sigOnDeletePTZ(short result);
	//删除枪机
	void sigOnDeleteSPY(short result);
	//获取球机预置点
	void sigOnGetPtzPoint(QString ip, QString point);
	//
	void sigOnGetTCSInfo(api_detu_tcs_register_t api_info);
	void sigUpdateTCSInfo(api_detu_tcs_heartbeat_t api_info);
	void sigOnReportTCSError(std::string deviceID, short result);
	void sigOnReportTCSOffLine(int serverId);
	void sigOnHandleTCSReset(bool OK);
	//
	void sigOnHandleStreamSuccess(unsigned char streamId);
	void sigOnHandleStreamFailed();
	//
	void sigOnRebootDeviceSuccess(unsigned char streamId);
	void sigOnRebootDeviceFailed(unsigned char streamId);
private:
	std::string address_;
	uint16_t port_;
	std::string session_;
	std::string url_;
	
	boost::mutex do_read_mutx_;

	/// Buffer for incoming data.
	protocol_head_t prot_head_;
	int incoming_buf_size_;
	netbuffer_t incoming_buf_;

	api_detu_client_register_res_list_t  *api_reg_res_;

	api_detu_client_disk_size_list_t *api_disk_res_;
	api_detu_client_request_video_res_t *replay_api_url_;
    std::vector<api_record_query_respond> api_record_time_list_;
	std::vector<api_detu_client_disk_size_t> api_disk_size_list_;

	DetuPVMS *mainwindow_;

    QString capture_path_;

	bool is_tcp_closed_;
};
