/************************************************
* \file deviceManageWgt.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* 设备管理窗口
************************************************/
#ifndef DEVICEMANAGEWGT_H
#define DEVICEMANAGEWGT_H

#include <QWidget>
#include <QButtonGroup>

#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>

#include "ui_deviceManageWgt.h"
#include "constStruct.h"
#include "deviceSettingDlg.h"
#include "APIProtocol.h"
#include "ptzSettingsDlg.h"
#include "HCNetSDK.h"
#include "commonTipDlg.h"
#include "qrCodeDlg.h"
#include "bindDeviceDlg.h"

#include "pushFlowSettingsDlg.h"

using namespace dm::server;


class ptzSettingPointDlg;
class gunCamSettingDig;

class deviceManageWgt : public QWidget
{
	Q_OBJECT
public:
	deviceManageWgt(QWidget *parent = 0);
	~deviceManageWgt();

	void getSelectId(int selectId);
	void setServerOnline(bool isOnline);
	void ptzRegister(QString Ip, int port, QString user, QString passwd);    //球机注册函数
	void spyRegister(QString Ip, int port, QString user, QString passwd);   //枪机注册函数

	void getDeviceListThread();
	void getDeviceSizeThread();

	void getPTZListThread(std::vector<PTZManageTable_t> ptzList);
	void getSPYListThread(std::vector<SPYManageTable_t> spyList);
signals:
	void sigOnDistributeList(QList<deviceInfo> deviceList);
	void sigOnUpdate();
	void sigOnSelectWarning();   //空选择操作警告信号
	void sigOnBindPTZFailed();    //绑定球机失败信号


	void sigOnInitData(QList<deviceInfo> itemInfoList);
	void sigOnInitPtzData(QList<PtzInfo> ptzInfoList);
	void sigOnInitSpyData(QList<SpyInfo> spyInfoList);

private slots:
    void slotOnSetup(deviceInfo info);
    void slotOnDownMove(deviceInfo info);
    void slotOnUpMove(deviceInfo info);

	//添加线程处理
    void slotOnGetDeviceList();

    void slotOnSave(deviceInfo info);

	//扔到线程处理
    void slotOnGetDiskSize();

    void slotOnUpdate();
	void slotOnUpdateStatus();
    void slotOnSetAutoCircle(bool isAutoCircle, QString deviceId);
	void transportList(QList<deviceInfo> deviceList);
	void resetToolBtn();
	void slotOnBindPTZClicked();     //绑定球机按键槽函数
	void slotOnUnBindPTZ();   //解除绑定球机槽函数

	void slotOnConfirm();

	void slotOnDeletePtz();    //删除球机
	void slotOnDeleteSpy();   //删除枪机
	void slotOnBindPtz(QString Ip, int port, QString user, QString passwd, int type);  //绑定球机槽函数
	void slotOnSelected(deviceInfo info);
	void slotOnScanCode(deviceInfo info);    //扫码触发槽函数
	void slotOnPageChanged(int index);        //列表页面变化槽函数
	void slotOnBindDevice(deviceInfo info);   //绑定设备触发槽函数
	void slotOnLiveShow(deviceInfo info);   //直播触发槽函数
	void slotOnSyncData(deviceInfo info);

	void slotOnSetPtzPoint();
	void slotOnSetSpyPoint();
	//扔到线程处理
	void slotOnGetPTZList(std::vector<PTZManageTable_t> ptzList);
	void slotOnGetSPYList(std::vector<SPYManageTable_t> spyList);

	//刷新UI
	void slotOnInitPtzData(QList<PtzInfo> ptzInfoList);     //初始化球机列表
	void slotOnInitSpyData(QList<SpyInfo> spyInfoList);    //初始化枪机列表

	void slotOnGetTCSInfo(api_detu_tcs_register_t tmpInfo);
	void slotUpdateTCSInfo(api_detu_tcs_heartbeat_t tmpInfo);
	void slotOnDeletePtz(PtzInfo ptzInfo);
	void slotOnDeleteSpy(SpyInfo spyInfo);
	void slotOnDeletePTZRes(short result);
	void slotOnDeleteSPYRes(short result);

	void slotOnInitData(QList<deviceInfo> itemInfoList);
	void slotOnReportTCSOffLine(int serverId);
private:
	void init();
	void initConnect();
	void generateUI();
	void getDiskSize();
	void updateData(deviceInfo *info, QString name, QString deviceId, int direction, QString ip, int port, QString user, QString passwd, QString M1Id, int online);
	void updateData(int id, QString name, QString deviceId, int direction, int port, QString user, QString passwd, QString M1Id, int online);

	void reportOptimizePTSRequest(deviceInfo info);       //上报优化后的pts文件到服务器
	QString readPTSData(QString deviceNo);
	bool isPushFlowDevice(deviceInfo info);
private:
	Ui::deviceManageWgt ui;
	QList<deviceInfo> m_InfoList;
	QList<PtzInfo> m_ptzInfoList;
	QList<SpyInfo> m_spyInfoList;
	int m_selectId;
	//设备设置对话框
	deviceSettingDlg *setupDlg_;
	//绑定球机对话框
	ptzSettingsDlg *ptzDlg_;
	api_detu_client_register_res_list_t *nvr_list_;
	api_detu_client_disk_size_list_t *disk_list_;

	boost::shared_ptr<boost::thread> get_device_list_thread_ = NULL;
	boost::shared_ptr<boost::thread> get_device_size_thread_ = NULL;

	boost::shared_ptr<boost::thread> get_ptz_thread_ = NULL;
	boost::shared_ptr<boost::thread> get_spy_thread_ = NULL;

	boost::mutex locker;

	//当前选择的全局ID
	int curr_selectID_;
	//通用提示框
	commonTipDlg *tipDlg_;
	//扫码对话框
	qrCodeDlg *qrDlg_;
	//控制按键
	QButtonGroup *buttonGroup_;
	//绑定设备对话框
	bindDeviceDlg *m_bindDeviceDlg;
	//设置预设点对话框
	ptzSettingPointDlg *m_PtzPointSettingDlg;
	gunCamSettingDig *	m_SpyPointSettingDlg;

	int curr_delete_device_type_;
	QString curr_bind_ptz_ip_;
	PtzInfo curr_bind_ptz_;
	SpyInfo	curr_bind_spy_;
	QList<TCSManageInfo> m_TCSManageInfoList;

	//推流设置对话框
	pushFlowSettingsDlg *m_pushFlowSettingsDlg;
};

#endif // DEVICEMANAGEWGT_H
