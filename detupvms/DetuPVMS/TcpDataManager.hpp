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
	//��ȡ��������
	void setDiskSizeList(std::vector<api_detu_client_disk_size_t> list);
	//��ʽ������
	void setDiskFormat(bool is_ok);
	//�طſ��Ʒ���
	void getPlaybackRes(bool is_ok);
	//��������
	void handleStreamRes(short result, unsigned char streamId);
	//�����豸����
	void handleRebootDeviceRes(short result, unsigned char streamId);
	//PVS�����ϱ�
	void handleActiveReport(short errCode, std::string PVSId, unsigned char streamId);
	//��ȡ����
	void handleGetBandWidth(PVSManageTable_t &apiData);
	//��ȡ����б�
	void handleGetPTZList(std::vector<PTZManageTable_t> list);
	//��ȡǹ���б�
	void handleGetSPYList(std::vector<SPYManageTable_t> list);
	//ɾ�����
	void handleDeletePtz(short result);
	//ɾ��ǹ��
	void handleDeleteSpy(short result);
	//��ȡ���Ԥ�õ�
	void handleGetPtzPoint(QString ip, QString point);
	//��ȡת�������Ϣ
	void handleGetTCSInfo(const api_detu_tcs_register_t &tmpInfo);
	//
	void handleUpdateTCSInfo(const api_detu_tcs_heartbeat_t &tmpInfo);
	//
	void handleReportTCSError(const api_detu_tcs_transcode_res_t &tmpInfo, short result);
	//
	void handleTCSOffLine(const api_detu_tcs_register_t &tmpInfo);
	void handleTCSReset(short result);
	//�ͻ��˵�¼У��
	void handleLoginChecked(api_detu_client_register_t api_query, short result);
	//�ͻ���ע���û�����
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
	//���ע��ɹ�����
	void ptz_register_res(bool is_ok, unsigned char streamId);
	//ǹ��ע��ɹ�����
	void spy_register_res(bool is_ok, unsigned char streamId);
	//
    void setCapturePath(QString path);
    QString getCapturePath(){ return capture_path_; };
	//����
	void breakHeart();
	//�汾��Ϣ
	void version_check(bool is_check_ok);
	//��ȡ������Ϣ
	void getBitRate(api_detu_client_av_param_t* res, unsigned char streamId);
	//����������Ϣ
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
	//����
	void sigOnBreakHeart();
	//�汾��Ϣ
	void sigOnVersionCheck(bool is_check_ok);
	//��ȡ������Ϣ
	void sigOnGetBitRate(unsigned char streamId, api_detu_client_av_param_t *res);
	//����������Ϣ
	void sigOnSetBitRate(unsigned char streamId, bool is_Ok);
	//���ע�᷵���ź�
	void sigOnRegisterPTZRes(bool is_ok, unsigned char streamId);
	//ǹ��ע�᷵���ź�
	void sigOnRegisterSPYRes(bool is_ok, unsigned char streamId);
	//PVS�����ϱ�
	void sigOnActiveReport(short errCode, std::string PVSId, unsigned char streamId);
	//��ȡ����
	void sigOnGetBandWidth(PVSManageTable_t apiData);
	//��ȡ����б�
	void sigOnGetPTZList(std::vector<PTZManageTable_t> list);
	//��ȡǹ���б�
	void sigOnGetSPYList(std::vector<SPYManageTable_t> list);
	//ɾ�����
	void sigOnDeletePTZ(short result);
	//ɾ��ǹ��
	void sigOnDeleteSPY(short result);
	//��ȡ���Ԥ�õ�
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
