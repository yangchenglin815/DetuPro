#ifndef DETUPVMS_H
#define DETUPVMS_H

#include <assert.h>
#include <vector>
#include <string>

#include <QWidget>
#include <QObject>
#include <QFileInfo>
#include <QListWidgetItem>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QDesktopWidget>
#include <QMenu>
#include <QTime>
#include <QTimer>
#include <QUrl>
#include <QMimeData>
#include <QFileIconProvider>
#include <QFileInfo>
#include <QSettings>
#include <QtEvents>
#include <QPaintEvent>
#include <QCursor>
#include <QDesktopServices>
#include <QNetworkAccessManager>


#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>

#include "ui_DetuPVMS.h"

#include "tcpclient.hpp"
#include "KillExe.h"




using namespace dm::server;
using namespace dm::client;

#define DETU_PVMS_VERSION 1.000  
#define MINWIDTH 1200
#define MINHEIGHT 660
#define PanoVMS_PORT 8088
#define PanoVMS_SERVER "10.0.0.93"

namespace Ui {
class DetuPVMS;
}

class updateDialog;
class lockDlg;
class commonDlg;
class HelpPageWidget;
class Feedback;
class systemSettingDlg;
class showBandWidthDlg;

class DetuPVMS : public QWidget
{
    Q_OBJECT

public:
    explicit DetuPVMS(QWidget *parent = 0);
    ~DetuPVMS();
signals:
	void DetuClientLoginFailed();
	void sigOnSave(deviceInfo info);

public:
	void SocketStateCallBack(SOCKETSTATE_ENUM  socketstate);


private:
    void init();
    void initConnect();
	void initUnlock();

	//�������£�ˢ���б�ˢ�µ�ͼ����
	void InitRegist();

	void InitUI();
	void initPTZSDK();  //��ʼ�����SDK
	//��ʼ������controller
	void InitController();
	//�жϿͻ����ǲ��ǰ�װ���һ������
	void InstallFirstStart();
	//��ʼ��TCP
	void initTcpSocket();
	//�첽TcpReader
	void RunCommSocketThreadFunc();
	void RunDataSocketThreadFunc();
	void VersionCheckThreadFunc();

	void DetuClientRegistThreadFunc();
	//����һ��������ʵһ������
	void UpdateListThreadFunc();

	void UpdateMapDataThreadFunc();

	//pdf
	bool OpenHelpPDF();
	//������
	void CheckForUpdate();
	//����������ʧ��
	void serverConnectFailed();
	//���������ӳɹ�
	void serverConnectSucceed();
	//����������
	void beatHeart();

	void EventUpdate(int totaltime);

private slots:
	void slotOnDetuClientLoginOk();
    void slot_quitExe();
    void slot_Exemaxminzed();
    void slotOnInitTimeShow();
    void slot_initLogin();
    void firstLogin();
	void setAdminFinish();
	void slot_loginDetu();
	void slot_loginFinish();
	void slot_unlock();
	void slotOnUnlock();
	void slotOnCloseUnlock();
	void slot_showHelpPage();
	void slot_getHelpPagePos(int x, int y);
	void slot_clickToAboutBtn();
	void slot_clickToHelpBtn();
	void slot_closeHelpPage();
	void slot_clickToFeedbackBtn();
	void slotOnTipClose();
	void slotOnShowSettingDlg();
	void slotOnSaveAtSettings();
	void slotOnUpdateDeviceList();
	//�汾�ļ�������ɣ�������
	void slotOnSoftwareUpdate(QNetworkReply *reply);
	//�رտͻ��˴�����
	void slotOnCloseClient();
	//����
	void slotOnBreakHeart();
	void slotBeat();
	void slotVersionCheck(bool is_check_ok);
	//
	void slotServerFinished();
	//��������״̬
	void slotOnReturnLock();
	void slotOnSelectWarning();  //��ѡ���������ۺ���
	void slotOnBindPTZWarning();     //���δ��֪ͨ�ۺ���
	void slotOnHandleStreamFailed();  //������ʧ��֪ͨ����
	void slotOnRebootDeviceFailed(unsigned char streamId);   //�����豸ʧ��֪ͨ����
	void slotOnOptMizeSuccess();  //�Ż�ģ��ɹ�
	void slotOnReportTCSError(std::string deviceID, short result);  //�ϱ�ת������쳣
	void slotOnReportTCSOffLine(int serverId);    //�ϱ�ת���������
	void slotOnHandleTCSReset(bool is_Ok);

	//SocketMonitorManager�����źŲۣ�����֪ͨ������״̬
	void slot0nSocketConnectStatus(int status);

	void SlotOnUpdateList();
	void slotOnActiveReport(short errCode, std::string PVSId, unsigned char streamId);
	void slotOnGetBandWidth(PVSManageTable_t apiData);
	void slotOnHandleSubStreamMessage(bool open, QString pvsId, int id);

	void slotOnSetFullScreen(bool is_full_screen);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *e);
	void showEvent(QShowEvent *e);

private:
    Ui::DetuPVMS *ui;
	QString current_locale_;        //��ǰ����
	QString init_file_path_;          //��ʼ���ļ�·��
	QString version_file_path_;		

	bool isDraggingWindow_;
	bool isMaxWindow_;
	bool is_closed_;
	bool isShowHelpPage_;
	//����ҳ��λ��
	int nXPos_;
	int nYPos_;
	QSize min_size_;                   //��С���ڴ�С
    QPoint lastMousePos_;
	QDateTime lastTime_;
	QDateTime currTime_;

    commonDlg *firstLoginDlg_;
	//����ҳ�����
	HelpPageWidget *helpPage_;
	//��ʾ��
	Feedback *tip_;
	QNetworkAccessManager *software_update_network_mgr_;
	updateDialog *updateDlg_;
	lockDlg *m_lockDlg;
	systemSettingDlg *m_settingDlg;
	showBandWidthDlg *m_bandWidthDlg;

	//ͨ��socket
	boost::shared_ptr<dm::client::tcpclient> tc_comm_ptr_;
	//���͵�ͼ����socket
	boost::shared_ptr<dm::client::tcpclient> tc_map_data_ptr_;
	
	boost::shared_ptr<boost::thread> write_reg_thread_;
	boost::shared_ptr<boost::thread> update_list_thread_;
	boost::shared_ptr<boost::thread> update_map_data_thread_;
	boost::shared_ptr<boost::thread> version_check_thread_;

	boost::shared_ptr<boost::thread> comm_socket_thread_;
	boost::shared_ptr<boost::thread> data_socket_thread_;

	KillExe kill_exe_;

	//���ƿ��������������쳣�ϱ�
	bool m_handle_open;
	QString m_handle_pvsId;
	int m_handle_id;

	bool is_version_checked_;
};

#endif // DETUPVMS_H
