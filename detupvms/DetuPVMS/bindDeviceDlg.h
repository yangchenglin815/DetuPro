#ifndef BINDDEVICEDLG_H
#define BINDDEVICEDLG_H

#include <QDialog>

#include "ui_bindDeviceDlg.h"
#include "addItemWidget.h"
#include "addDeviceDlg.h"
#include "constStruct.h"
#include "commonTipDlg.h"


class ptzSettingPointDlg;
class gunCamSettingDig;

class bindDeviceDlg : public QDialog
{
	Q_OBJECT

public:
	bindDeviceDlg(QWidget *parent = 0);
	~bindDeviceDlg();
	void setParentPos(int x, int y, int width, int height);
	void init(const deviceInfo &info);

signals:
	void sigOnBindPtz(QString ip, int port, QString user, QString passwd, int type);
	void sigOnSetPoint();

public slots:
	void slotOnInitPtzData(QList<PtzInfo> ptzInfoList);     //��ʼ������б�
	void slotOnInitSpyData(QList<SpyInfo> spyInfoList);    //��ʼ��ǹ���б�

	void slotOnInitPtzList(QList<PtzInfo> ptzInfoList);
	void slotOnInitSpyList(QList<SpyInfo> spyInfoList);



private slots:
	void slotOnAddDevice();
	void slotOnClickedSPY(bool checked);
	void slotOnClickedPTZ(bool checked);
	void slotOnClickedHOT(bool checked);

	void slotOnClickedHOTConfirm();
	void slotOnClearButton();

	void slotOnSettings(PtzInfo pInfo, SpyInfo sInfo);
	void slotOnUnbind(PtzInfo pInfo, SpyInfo sInfo);
	void slotOnItemClicked(QListWidgetItem *item);
	void slotOnRegisterPTZRes(bool is_ok, unsigned char streamId);   //���ע�᷵�زۺ���
	void slotOnRegisterSPYRes(bool is_ok, unsigned char streamId);   //ǹ��ע�᷵�زۺ���
	void slotOnConfirmUnbind();

private:
	void initConnect();
private:
	Ui::bindDeviceDlg ui;
	addDeviceDlg *m_addDeviceDlg;
	boost::shared_ptr<boost::thread> get_ptz_list_thread_;
	//������
	int m_XPos;
	int m_YPos;
	int m_Width;
	int m_Height;

	QList<PtzInfo> m_ptzInfoList;
	QList<SpyInfo> m_spyInfoList;
	PtzInfo m_curr_ptzInfo;
	SpyInfo m_curr_spyInfo;
	commonTipDlg *tipDlg_;

	ptzSettingPointDlg *ptz_set_point_dlg_;
	gunCamSettingDig *spy_set_point_dlg_;
	deviceInfo m_curr_info;
};

#endif // BINDDEVICEDLG_H
