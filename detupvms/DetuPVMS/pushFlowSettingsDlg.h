#ifndef PUSHFLOWSETTINGSDLG_H
#define PUSHFLOWSETTINGSDLG_H

#include <QDialog>
#include <QListView>
#include <QMessageBox>
#include <QLineEdit>

#include "constStruct.h"
#include "APIProtocol.h"

namespace Ui {
class pushFlowSettingsDlg;
}

using namespace dm::server;
class pushFlowSettingsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit pushFlowSettingsDlg(QWidget *parent = 0);
    ~pushFlowSettingsDlg();
	void initData(const deviceInfo &info);
	void initTCSList(QList<TCSManageInfo> TCSManageInfoList);
	void syncConnection(bool flag);
	void initPushFlowPage();
	void initPushFlowInfoPage();
signals:
	void sigOnSyncData(deviceInfo info);
public slots:
    void slotOnDeleteItem(const QModelIndex &index);
    void slotOnStartPushFlow();
	void slotOnDisConnected();
	void slotOnCopyUrl();
    void updateLineEditStyleSheet();
	void slotOnGetBitRate(unsigned char streamId, api_detu_client_av_param_t *res);
	void slotOnClose();
	void slotOnPushFlowSuccess();
	void slotOnPushFlowFailed();
	void slotOnCloseTranscode();
	void slotOnReportTCSDisconnectError(std::string deviceID);
	void slotOnReportTCSOffLine(int serverId);
	void slotOnUpdateTimer(int val, QString deviceID);
private:
    Ui::pushFlowSettingsDlg *ui;
    QLineEdit *m_lineEdit;
	deviceInfo m_deviceInfo;
	QList<TCSManageInfo> m_TCSManageInfoList;
	QString m_pushFlowIP;
	quint16 m_pushFlowPort;
	QString m_currServerID;
};

#endif // PUSHFLOWSETTINGSDLG_H
