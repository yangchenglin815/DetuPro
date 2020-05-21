#ifndef PTZSETTINGPOINTDLG_H
#define PTZSETTINGPOINTDLG_H

#include <QDialog>
#include "ui_ptzSettingPointDlg.h"
#include "ptzPointCtrlWidget.h"

#include "GeneralDef.h"
#include "logging.hpp"
#include "constStruct.h"
#include "ballCamWgt.h"

class ptzSettingPointDlg : public QDialog
{
	Q_OBJECT

public:
	ptzSettingPointDlg(QWidget *parent = 0);
	~ptzSettingPointDlg();

	void setTitleText(const PtzInfo &curr_info);

	void setPosSet(int x, int y);
signals:
	//numԤ�õ���ţ���������
	void SignalToTrigBallCamLinkage(int pre_point_num, int contral_type);

private slots:
    void slotOnConfirm();
	void slotOnCancel();

	//checked�Ƿ����ã�numԤ�õ����
	void slotOnPanoPrePointClicked(bool checked, int num);
private:
	void init();
	void initConnect();
private:
	Ui::ptzSettingPointDlg ui;
	ptzPointCtrlWidget *ctrlWgt_;
	PtzInfo m_curr_ptzInfo;
	ballCamWgt *ballWgt_;
};

#endif // PTZSETTINGPOINTDLG_H
