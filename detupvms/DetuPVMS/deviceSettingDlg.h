/************************************************
* \file deviceSettingDlg.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* �豸���õ���
************************************************/
#ifndef DEVICESETTINGDLG_H
#define DEVICESETTINGDLG_H

#include <QDialog>
#include <QMouseEvent>
#include "ui_deviceSettingDlg.h"
#include "constStruct.h"
#include "APIProtocol.h"
#include "commonTipDlg.h"

using namespace dm::server;
class deviceSettingDlg : public QDialog
{
	Q_OBJECT

public:
	deviceSettingDlg(QWidget *parent = 0);
	~deviceSettingDlg();
	void initData(deviceInfo info);    //��ʼ��������Ϣ
	void getBitRate(int streamId);    //��ȡ���ʵ���Ϣ����
	void setBitRate(int streamId, QString bitRate);    //�������ʵ���Ϣ����
	void initDirection(int direction);    //��ʼ���������
	void getStream();     //��ȡ������
	void delStream();     //ɾ��������
	void addStream();    //����������
	void rebootM1Request();    //�����豸����
signals:
	void sigOnSave(deviceInfo info);
	void sigOnSaveDirection(int direction);
	void sigOnSetAutoCircle(bool isAutoRotate, QString deviceId);
protected:
	/*����¼�  ���ƴ����ƶ�*/
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
private slots:
	void slotOnSave();   //���水�������ۺ���
	void slotOnCancel();
	void slotOnGetBitRate(unsigned char streamId, api_detu_client_av_param_t* res);   //�������ʵȷ��زۺ���
	void slotOnSetBitRate(unsigned char streamId, bool is_ok);     //�������ʵȷ��زۺ���
	void slotOnSetAutoCircle();
	void slotOnScrollMove();  //�������ƶ��ۺ���
	void slotOnStartSubBit(bool chceked);   //�����������رղۺ���
	void slotOnHandleStreamSuccess(unsigned char streamId);   //������ɹ����زۺ���
	void slotOnRebootM1();   //M1�����ۺ���
	void slotOnRebootDeviceSuccess(unsigned char streamId);    //�豸�����ɹ����زۺ���
	void slotOnResetFramerate(QString framerate);      //����������֡��
	void slotOnTipBitrate(int index);    //��ע��ѡ�ֱ��ʵ����ʷ�Χ
private:
	void init();   //��ʼ������
	void initConnect();  //��ʼ���źŲ�
	void reportDeviceName(QString name, QString deviceId);  //�ϱ���Ӧnvr ID�ı���
	void checkout(bool subChecked);  //У���Ƿ���Ҫ����M1
	void rebootM1Tip();  //����M1��ʾ��
	void checkoutBitRate(int min, int max);   //У������
private:
	Ui::deviceSettingDlg ui;
	QPoint lastMousePos_;
	bool isDraggingWindow_;
	bool isAutoRotate_;
	int direction_;    //���Ԥ�÷���
	deviceInfo m_info;   //��ǰ�豸��Ϣ
	api_detu_client_av_param_t av_param_1t_;   //�����������Ϣ
	api_detu_client_av_param_t av_param_2t_;   //�����������Ϣ
	//�yӋ��
	int setBitRateCount_;
	boost::shared_ptr<boost::thread> get_stream_thread_;    //��ȡ���߳�
	boost::shared_ptr<boost::thread> reboot_device_thread_;    //�����豸�߳�
	commonTipDlg *tipDlg;   //�����ʾ�����
	/*���ڷֱ��ʺ�֡�ʵ��޸���������������ﱣ�浱ǰ��ֵ��У���Ƿ����÷����˱仯�������������*/
	QString mResolution;
	QString mFramerate;
	QString mSubResolution;
	QString mSubFramerate;
};

#endif // DEVICESETTINGDLG_H
