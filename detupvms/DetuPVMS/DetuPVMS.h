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

	//干两件事，刷新列表，刷新地图数据
	void InitRegist();

	void InitUI();
	void initPTZSDK();  //初始化球机SDK
	//初始化单例controller
	void InitController();
	//判断客户端是不是安装后第一次启动
	void InstallFirstStart();
	//初始化TCP
	void initTcpSocket();
	//异步TcpReader
	void RunCommSocketThreadFunc();
	void RunDataSocketThreadFunc();
	void VersionCheckThreadFunc();

	void DetuClientRegistThreadFunc();
	//跟上一个函数其实一个功能
	void UpdateListThreadFunc();

	void UpdateMapDataThreadFunc();

	//pdf
	bool OpenHelpPDF();
	//检查更新
	void CheckForUpdate();
	//服务器连接失败
	void serverConnectFailed();
	//服务器连接成功
	void serverConnectSucceed();
	//心跳请求函数
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
	//版本文件下载完成，检查更新
	void slotOnSoftwareUpdate(QNetworkReply *reply);
	//关闭客户端处理函数
	void slotOnCloseClient();
	//心跳
	void slotOnBreakHeart();
	void slotBeat();
	void slotVersionCheck(bool is_check_ok);
	//
	void slotServerFinished();
	//返回锁定状态
	void slotOnReturnLock();
	void slotOnSelectWarning();  //空选择操作警告槽函数
	void slotOnBindPTZWarning();     //球机未绑定通知槽函数
	void slotOnHandleStreamFailed();  //流处理失败通知函数
	void slotOnRebootDeviceFailed(unsigned char streamId);   //重启设备失败通知函数
	void slotOnOptMizeSuccess();  //优化模板成功
	void slotOnReportTCSError(std::string deviceID, short result);  //上报转码服务异常
	void slotOnReportTCSOffLine(int serverId);    //上报转码服务离线
	void slotOnHandleTCSReset(bool is_Ok);

	//SocketMonitorManager出发信号槽，用以通知服务器状态
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
	QString current_locale_;        //当前语言
	QString init_file_path_;          //初始化文件路径
	QString version_file_path_;		

	bool isDraggingWindow_;
	bool isMaxWindow_;
	bool is_closed_;
	bool isShowHelpPage_;
	//帮助页面位置
	int nXPos_;
	int nYPos_;
	QSize min_size_;                   //最小窗口大小
    QPoint lastMousePos_;
	QDateTime lastTime_;
	QDateTime currTime_;

    commonDlg *firstLoginDlg_;
	//帮助页面对象
	HelpPageWidget *helpPage_;
	//提示框
	Feedback *tip_;
	QNetworkAccessManager *software_update_network_mgr_;
	updateDialog *updateDlg_;
	lockDlg *m_lockDlg;
	systemSettingDlg *m_settingDlg;
	showBandWidthDlg *m_bandWidthDlg;

	//通信socket
	boost::shared_ptr<dm::client::tcpclient> tc_comm_ptr_;
	//发送地图数据socket
	boost::shared_ptr<dm::client::tcpclient> tc_map_data_ptr_;
	
	boost::shared_ptr<boost::thread> write_reg_thread_;
	boost::shared_ptr<boost::thread> update_list_thread_;
	boost::shared_ptr<boost::thread> update_map_data_thread_;
	boost::shared_ptr<boost::thread> version_check_thread_;

	boost::shared_ptr<boost::thread> comm_socket_thread_;
	boost::shared_ptr<boost::thread> data_socket_thread_;

	KillExe kill_exe_;

	//控制开关子码流处理异常上报
	bool m_handle_open;
	QString m_handle_pvsId;
	int m_handle_id;

	bool is_version_checked_;
};

#endif // DETUPVMS_H
