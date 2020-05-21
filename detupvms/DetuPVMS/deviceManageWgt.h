/************************************************
* \file deviceManageWgt.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* �豸������
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
	void ptzRegister(QString Ip, int port, QString user, QString passwd);    //���ע�ắ��
	void spyRegister(QString Ip, int port, QString user, QString passwd);   //ǹ��ע�ắ��

	void getDeviceListThread();
	void getDeviceSizeThread();

	void getPTZListThread(std::vector<PTZManageTable_t> ptzList);
	void getSPYListThread(std::vector<SPYManageTable_t> spyList);
signals:
	void sigOnDistributeList(QList<deviceInfo> deviceList);
	void sigOnUpdate();
	void sigOnSelectWarning();   //��ѡ����������ź�
	void sigOnBindPTZFailed();    //�����ʧ���ź�


	void sigOnInitData(QList<deviceInfo> itemInfoList);
	void sigOnInitPtzData(QList<PtzInfo> ptzInfoList);
	void sigOnInitSpyData(QList<SpyInfo> spyInfoList);

private slots:
    void slotOnSetup(deviceInfo info);
    void slotOnDownMove(deviceInfo info);
    void slotOnUpMove(deviceInfo info);

	//����̴߳���
    void slotOnGetDeviceList();

    void slotOnSave(deviceInfo info);

	//�ӵ��̴߳���
    void slotOnGetDiskSize();

    void slotOnUpdate();
	void slotOnUpdateStatus();
    void slotOnSetAutoCircle(bool isAutoCircle, QString deviceId);
	void transportList(QList<deviceInfo> deviceList);
	void resetToolBtn();
	void slotOnBindPTZClicked();     //����������ۺ���
	void slotOnUnBindPTZ();   //���������ۺ���

	void slotOnConfirm();

	void slotOnDeletePtz();    //ɾ�����
	void slotOnDeleteSpy();   //ɾ��ǹ��
	void slotOnBindPtz(QString Ip, int port, QString user, QString passwd, int type);  //������ۺ���
	void slotOnSelected(deviceInfo info);
	void slotOnScanCode(deviceInfo info);    //ɨ�봥���ۺ���
	void slotOnPageChanged(int index);        //�б�ҳ��仯�ۺ���
	void slotOnBindDevice(deviceInfo info);   //���豸�����ۺ���
	void slotOnLiveShow(deviceInfo info);   //ֱ�������ۺ���
	void slotOnSyncData(deviceInfo info);

	void slotOnSetPtzPoint();
	void slotOnSetSpyPoint();
	//�ӵ��̴߳���
	void slotOnGetPTZList(std::vector<PTZManageTable_t> ptzList);
	void slotOnGetSPYList(std::vector<SPYManageTable_t> spyList);

	//ˢ��UI
	void slotOnInitPtzData(QList<PtzInfo> ptzInfoList);     //��ʼ������б�
	void slotOnInitSpyData(QList<SpyInfo> spyInfoList);    //��ʼ��ǹ���б�

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

	void reportOptimizePTSRequest(deviceInfo info);       //�ϱ��Ż����pts�ļ���������
	QString readPTSData(QString deviceNo);
	bool isPushFlowDevice(deviceInfo info);
private:
	Ui::deviceManageWgt ui;
	QList<deviceInfo> m_InfoList;
	QList<PtzInfo> m_ptzInfoList;
	QList<SpyInfo> m_spyInfoList;
	int m_selectId;
	//�豸���öԻ���
	deviceSettingDlg *setupDlg_;
	//������Ի���
	ptzSettingsDlg *ptzDlg_;
	api_detu_client_register_res_list_t *nvr_list_;
	api_detu_client_disk_size_list_t *disk_list_;

	boost::shared_ptr<boost::thread> get_device_list_thread_ = NULL;
	boost::shared_ptr<boost::thread> get_device_size_thread_ = NULL;

	boost::shared_ptr<boost::thread> get_ptz_thread_ = NULL;
	boost::shared_ptr<boost::thread> get_spy_thread_ = NULL;

	boost::mutex locker;

	//��ǰѡ���ȫ��ID
	int curr_selectID_;
	//ͨ����ʾ��
	commonTipDlg *tipDlg_;
	//ɨ��Ի���
	qrCodeDlg *qrDlg_;
	//���ư���
	QButtonGroup *buttonGroup_;
	//���豸�Ի���
	bindDeviceDlg *m_bindDeviceDlg;
	//����Ԥ���Ի���
	ptzSettingPointDlg *m_PtzPointSettingDlg;
	gunCamSettingDig *	m_SpyPointSettingDlg;

	int curr_delete_device_type_;
	QString curr_bind_ptz_ip_;
	PtzInfo curr_bind_ptz_;
	SpyInfo	curr_bind_spy_;
	QList<TCSManageInfo> m_TCSManageInfoList;

	//�������öԻ���
	pushFlowSettingsDlg *m_pushFlowSettingsDlg;
};

#endif // DEVICEMANAGEWGT_H
