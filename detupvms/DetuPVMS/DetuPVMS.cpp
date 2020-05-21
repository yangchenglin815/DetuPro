#include <QDebug>
#include <QtNetwork/QNetworkAccessManager>
#include <QTimer>
#include <QProcess>
#include <QtNetwork/QNetworkRequest> 
#include <QtNetwork/QNetworkReply> 
#include <QMetaType> 

#include "QHotkey/qhotkey.h"

#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include "memory.h"

#include "DetuPVMS.h"
#include "DetuPVMSIni.h"

#include "updateDialog.h"
#include "lockDlg.h"
#include "commonDlg.h"
#include "helpPageWidget.h"
#include "feedback.h"
#include "systemSettingDlg.h"
#include "showBandWidthDlg.h"

#include "HCNetSDK.h"

//初始化控制器
#include "MessageManager.h"
#include "SocketManager.h"
#include "TcpDataManager.hpp"
#include "ListAndGLWindowManager.h"
#include "PVMSEventManager.h"

#include "SetAdminMananger.h"

#include "ViewSignal.h"
#include "constStruct.h"
#include "feedback.h"


using namespace dm::server;
using namespace dm::client;

Q_DECLARE_METATYPE(std::string)

DetuPVMS::DetuPVMS(QWidget *parent)
: QWidget(parent),
ui(new Ui::DetuPVMS)
, firstLoginDlg_(NULL)
, helpPage_(NULL)
, tip_(NULL)
, tc_comm_ptr_(NULL)
, tc_map_data_ptr_(NULL)
, software_update_network_mgr_(NULL)
, updateDlg_(NULL)
, m_lockDlg(NULL)
, m_settingDlg(NULL)
, m_bandWidthDlg(NULL)
, nXPos_(-1)
, nYPos_(-1)
, m_handle_id(-1)
, is_closed_(false)
, isShowHelpPage_(false)
, m_handle_open(true)
, is_version_checked_(false)
{

	kill_exe_.KillProcess(_T(L"Pano-VMS.exe"));


    ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
	setWindowTitle("Pano-VMS");
	setWindowIcon(QIcon(":/image/image/DetuMonitor_icon.ico"));

	//先初始化控制器，再初始化界面
	InitController();
    initConnect();
	initPTZSDK();
    init();
}

DetuPVMS::~DetuPVMS()
{	
	PVMSEventManagerManagerIns.stopEvent();

	if (tc_comm_ptr_ != NULL){
		tc_comm_ptr_->close();
		tc_comm_ptr_ = NULL;
	}	

	if (tc_map_data_ptr_ != NULL){
		tc_map_data_ptr_->close();
		tc_map_data_ptr_ = NULL;
	}

	Sleep(200);
	// 启动析构海康SDK

    NET_DVR_Cleanup();

	if (write_reg_thread_ && write_reg_thread_->joinable())
	{
		write_reg_thread_->join();
	}

	if (comm_socket_thread_ && comm_socket_thread_->joinable())
	{
		comm_socket_thread_->join();
	}


	if (data_socket_thread_ && data_socket_thread_->joinable())
	{
		data_socket_thread_->join();
	}

	if (firstLoginDlg_ != NULL){
		firstLoginDlg_->deleteLater();
		firstLoginDlg_ = NULL;
	}
	if (m_settingDlg != NULL)
	{
		m_settingDlg->deleteLater();
		m_settingDlg = NULL;
	}
	if (helpPage_ != NULL){
		helpPage_->deleteLater();
		helpPage_ = NULL;
	}
	if (tip_ != NULL){
		tip_->deleteLater();
		tip_ = NULL;
	}
	if (software_update_network_mgr_ != NULL)
	{
		software_update_network_mgr_->deleteLater();
		software_update_network_mgr_ = NULL;
	}
	if (updateDlg_ != NULL)
	{
		updateDlg_->deleteLater();
		updateDlg_ = NULL;
	}
	if (m_lockDlg != NULL)
	{
		m_lockDlg->deleteLater();
		m_lockDlg = NULL;
	}	
}

//初始化
void DetuPVMS::init()
{
	Log::Debug("Client start!");
    isMaxWindow_ = false;
    isDraggingWindow_ = false;
	lastTime_ = QDateTime::currentDateTime();
	currTime_ = QDateTime::currentDateTime();
	ui->label_2->setStyleSheet("background:yellow;border-radius:5px;");
	ui->flvTag->setStyleSheet("background:yellow;border-radius:5px;");

	SetAdminManangerIns.setAdmin(DetuPVMSIni::getIsAdminUser());
	//初始化登录
	QTimer::singleShot(20, this, SLOT(slot_initLogin()));
}

void DetuPVMS::initConnect()
{
	Log::Debug("init connect success!");
	connect(ui->tittleWidget, SIGNAL(sigonCloseClient()), this, SLOT(slotOnCloseClient()));
    connect(ui->tittleWidget, SIGNAL(sigonMinimized()), this, SLOT(showMinimized()));
    connect(ui->tittleWidget, SIGNAL(sigonMaxminzed()), this, SLOT(slot_Exemaxminzed()));
	connect(ui->tittleWidget, SIGNAL(sigonUnlock()), this, SLOT(slot_unlock()));
	connect(ui->tittleWidget, SIGNAL(sigonHelpPos(int, int)), this, SLOT(slot_getHelpPagePos(int, int)));
	connect(ui->tittleWidget, SIGNAL(sigonShowHelpDlg()), this, SLOT(slot_showHelpPage()));
	connect(ui->tittleWidget, SIGNAL(sigonCloseHelp()), this, SLOT(slot_closeHelpPage()));
	connect(ui->tittleWidget, SIGNAL(sigOnShowSettingDlg()), this, SLOT(slotOnShowSettingDlg()));
	connect(ui->tittleWidget, SIGNAL(sigOnDbClickTitle()), this, SLOT(slot_Exemaxminzed()));

	connect(ui->homeWidget, SIGNAL(sigOnUpdate()), this, SLOT(slotOnUpdateDeviceList()));
	connect(ui->homeWidget, SIGNAL(sigOnSelectWarning()), this, SLOT(slotOnSelectWarning()));
	connect(ui->homeWidget, SIGNAL(sigOnBindPTZFailed()), this, SLOT(slotOnRegisterPTZRes(false)));
	connect(ui->homeWidget, SIGNAL(sigOnBindPTZWarning()), this, SLOT(slotOnBindPTZWarning()));
	connect(ui->homeWidget, SIGNAL(sigOnOptMizeSuccess()), this, SLOT(slotOnOptMizeSuccess()));

	connect(ViewSignal::instance(), SIGNAL(sigOnHandleSubStreamMessage(bool, QString, int)), this, SLOT(slotOnHandleSubStreamMessage(bool, QString, int)));

	connect(&TcpDataManagerIns, SIGNAL(sigOnBreakHeart()), this, SLOT(slotBeat()));
	connect(&TcpDataManagerIns, SIGNAL(sigOnVersionCheck(bool)), this, SLOT(slotVersionCheck(bool)));
	connect(&TcpDataManagerIns, SIGNAL(sigOnHandleStreamFailed()), this, SLOT(slotOnHandleStreamFailed()));
	connect(&TcpDataManagerIns, SIGNAL(sigOnRebootDeviceFailed(unsigned char)), this, SLOT(slotOnRebootDeviceFailed(unsigned char)));
	qRegisterMetaType<PVSManageTable_t>("PVSManageTable_t");
	connect(&TcpDataManagerIns, SIGNAL(sigOnGetBandWidth(PVSManageTable_t)), this, SLOT(slotOnGetBandWidth(PVSManageTable_t)));
	qRegisterMetaType<std::string>();
	connect(&TcpDataManagerIns, SIGNAL(sigOnActiveReport(short, std::string, unsigned char)), this, SLOT(slotOnActiveReport(short, std::string, unsigned char)));
	connect(&TcpDataManagerIns, SIGNAL(sigOnReportTCSError(std::string, short)), this, SLOT(slotOnReportTCSError(std::string, short)));
	connect(&TcpDataManagerIns, SIGNAL(sigOnReportTCSOffLine(int)), this, SLOT(slotOnReportTCSOffLine(int)));
	connect(&TcpDataManagerIns, SIGNAL(sigOnHandleTCSReset(bool)), this, SLOT(slotOnHandleTCSReset(bool)));

	connect(&PVMSEventManagerManagerIns, SIGNAL(sigOnSetFullScreen(bool)), this, SLOT(slotOnSetFullScreen(bool)), Qt::AutoConnection);
	connect(&PVMSEventManagerManagerIns, SIGNAL(sigOnReplaySetFullScreen(bool)), this, SLOT(slotOnSetFullScreen(bool)), Qt::AutoConnection);

	
}

//初始化解锁
void DetuPVMS::initUnlock()
{
	if (!DetuPVMSIni::isUnlockState())
	{
		slot_unlock();
	}
}

//初始化TCP线程
void DetuPVMS::RunCommSocketThreadFunc()
{
	Log::Debug("init comm server socket!");
	QString serverIp = DetuPVMSIni::getServerIP();
	QString port = DetuPVMSIni::getServerPort();
	Log::Debug("GetSetver ip:%s:%s", serverIp.toLocal8Bit().data(), port.toLocal8Bit().data());

	//通信socket
	if (tc_comm_ptr_ != NULL)
	{
		tc_comm_ptr_->close();
	}
	tc_comm_ptr_.reset(new tcpclient());
	connect(tc_comm_ptr_.get(), SIGNAL(sig0nSocketConnectStatus(int)), this, SLOT(slot0nSocketConnectStatus(int)));
	tc_comm_ptr_->setconnectioninfo(serverIp.toStdString(), port.toInt());
	tc_comm_ptr_->run();
}

void DetuPVMS::RunDataSocketThreadFunc()
{
	Log::Debug("init data socket!");
	QString serverIp = DetuPVMSIni::getServerIP();
	QString port = DetuPVMSIni::getServerPort();
	Log::Debug("GetSetver ip:%s:%s", serverIp.toLocal8Bit().data(), port.toLocal8Bit().data());
	
	//地图数据socket
	if (tc_map_data_ptr_ != NULL)
	{
		tc_map_data_ptr_->close();
	}
	tc_map_data_ptr_.reset(new tcpclient());
	connect(tc_map_data_ptr_.get(), SIGNAL(sig0nSocketConnectStatus(int)), this, SLOT(slot0nSocketConnectStatus(int)));
	tc_map_data_ptr_->setconnectioninfo(serverIp.toStdString(), port.toInt());
	tc_map_data_ptr_->run();
}

void DetuPVMS::VersionCheckThreadFunc()
{
	Log::Debug("DetuPVMS::VersionCheckThreadFunc()!!");

	protocol_head_t api_head;
	api_head.nCmd = CMD_DETU_CLIENT_VERSION_CHECK;

	//复用，做版本匹配
	api_head.nResult = CLIENT_VERSION;
	api_head.nDataLen = 0;

	response res(api_head.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);

	//使用data_socket
	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

void DetuPVMS::DetuClientRegistThreadFunc()
{
	if (DetuPVMSIni::getClienUUID().isEmpty())
	{
		return;
	}

	protocol_head_t api_head;
	api_detu_client_register_t api_reg;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_CLIENT_GET_LIST;
	api_head.nDataLen = api_reg.get_size();
	api_head.nResult = 0x00;
	api_head.nStreamId = 0;
	//api_head.nReserver = 0x01;        //预留位
	api_head.nEndFlags = 0xFA;

	QString userName = DetuPVMSIni::getAdminUser().trimmed();
	QString passWd = DetuPVMSIni::getAdminPasswd().trimmed();
	if (userName.isEmpty() || passWd.isEmpty())
	{
		return;
	}

	QString cUuid = DetuPVMSIni::getClienUUID().trimmed();
	memcpy(api_reg.szDetuDeviceUUId, cUuid.toStdString().c_str(), cUuid.length());
	memcpy(api_reg.szDetuUserName, userName.toStdString().c_str(), userName.length());
	memcpy(api_reg.szDetuPassWord, passWd.toStdString().c_str(), passWd.length());
	Log::Debug("Register Request: cmd:%d deviceid:%s username:%s passwd:%s",api_head.nCmd, api_reg.szDetuDeviceUUId, api_reg.szDetuUserName, api_reg.szDetuPassWord);

	response res(api_head.get_size() + api_reg.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
    response_add_resprotocol<api_detu_client_register_t>(res, &api_reg);

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

void DetuPVMS::UpdateListThreadFunc()
{
	if (DetuPVMSIni::getClienUUID().isEmpty())
	{
		return;
	}

	protocol_head_t api_head;
	api_detu_client_register_t api_reg;

	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_CLIENT_GET_LIST;
	api_head.nDataLen = api_reg.get_size();
	api_head.nResult = 0x00;
	api_head.nStreamId = 0;
	//api_head.nReserver = 0x01;        //预留位
	api_head.nEndFlags = 0xFA;

	QString userName = DetuPVMSIni::getAdminUser().trimmed();
	QString passWd = DetuPVMSIni::getAdminPasswd().trimmed();
	if (userName.isEmpty() || passWd.isEmpty())
	{
		return;
	}

	QString cUuid = DetuPVMSIni::getClienUUID().trimmed();
	memcpy(api_reg.szDetuDeviceUUId, cUuid.toStdString().c_str(), cUuid.length());
	memcpy(api_reg.szDetuUserName, userName.toStdString().c_str(), userName.length());
	memcpy(api_reg.szDetuPassWord, passWd.toStdString().c_str(), passWd.length());
	Log::Debug("Register Request: cmd:%d deviceid:%s username:%s passwd:%s", api_head.nCmd, api_reg.szDetuDeviceUUId, api_reg.szDetuUserName, api_reg.szDetuPassWord);

	response res(api_head.get_size() + api_reg.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
	response_add_resprotocol<api_detu_client_register_t>(res, &api_reg);

	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

void DetuPVMS::UpdateMapDataThreadFunc()
{
	if (DetuPVMSIni::getClienUUID().isEmpty())
	{
		return;
	}
	Log::Debug("DetuPVMS::UpdateMapDataThreadFunc()!!");

	protocol_head_t api_head;
	api_head.nCmd = CMD_DETU_GET_MAP_DATA;
	api_head.nDataLen = 0;

	response res(api_head.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);

	//使用data_socket
	dmconnection* conn = SocketManagerIns.GetDataSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

void DetuPVMS::InitRegist()
{
	if (write_reg_thread_ && write_reg_thread_->joinable())
	{
		write_reg_thread_->join();
	}
	write_reg_thread_.reset(new boost::thread(&DetuPVMS::DetuClientRegistThreadFunc, this));


// 	if (update_map_data_thread_ && update_map_data_thread_->joinable())
// 	{
// 		update_map_data_thread_->join();
// 	}
// 	update_map_data_thread_.reset(new boost::thread(&DetuPVMS::UpdateMapDataThreadFunc, this));
}

/*************************************************
函数名:    	initPTZSDK
函数描述:	初始化球机SDK函数
输入参数:
输出参数:
返回值:
**************************************************/
void DetuPVMS::initPTZSDK()
{
	//启动初始化海康SDK
	bool ret = NET_DVR_Init();
	if (!ret){
		QMessageBox::warning(this, "error", "init SDK failed!");
		Log::Info("init SDK failed!");
		return;
	}
	//设置连接时间与重连时间
	NET_DVR_SetConnectTime(2000, 1);
	NET_DVR_SetReconnect(10000, true);
}

void DetuPVMS::InitController()
{
	Log::Debug("init controller success!");
	
	if (min_size_.width() < MINWIDTH)
	{
		min_size_.setWidth(MINWIDTH);
	}
	if (min_size_.height() < MINHEIGHT)
	{
		min_size_.setHeight(MINHEIGHT);
	}
	setMinimumSize(min_size_);
	resize(min_size_.width(), min_size_.height());

	MessageManagerIns.SetMainWindow(this);

	QHotkey *hotkey = new QHotkey(QKeySequence("ctrl+alt+R"), true);
	Log::Info("Is Registered hotkey : %d", hotkey->isRegistered());
	QObject::connect(hotkey, &QHotkey::activated, qApp, [&](){
		bool flag = !DetuPVMSIni::getSaveFlvTag();
		Log::Info("Hotkey Activated - the application will change flag now - saveFlvTag is %d", flag);
		DetuPVMSIni::setSaveFlvTag(flag);
		ViewSignal::instance()->sigOnControlPlayerRecordFlv();
	});
}

bool DetuPVMS::OpenHelpPDF()
{
	QString pdf = QApplication::applicationDirPath() + "/detuhelp.pdf";
	bool isOpen = QDesktopServices::openUrl(QUrl::fromLocalFile(pdf));
	return isOpen;
}

//检查客户端版本更新
void DetuPVMS::CheckForUpdate()
{
	Log::Debug("check client update!");
	if (software_update_network_mgr_ == NULL){
		software_update_network_mgr_ = new QNetworkAccessManager;
		connect(software_update_network_mgr_, SIGNAL(finished(QNetworkReply *)), this, SLOT(slotOnSoftwareUpdate(QNetworkReply *)));
	}
	QNetworkRequest network_request;
	network_request.setUrl(QUrl(PanoVMS_UPDATE_URL));
	Log::Debug("update client url is %s", PanoVMS_UPDATE_URL);
	software_update_network_mgr_->get(network_request);
}

void DetuPVMS::serverConnectFailed()
{
	if (firstLoginDlg_ != NULL){
		firstLoginDlg_->serverConnectFailed();
	}
}

void DetuPVMS::serverConnectSucceed()
{
	if (firstLoginDlg_ != NULL)
	{
		firstLoginDlg_->setServerSettingDlg();
	}
}

void DetuPVMS::beatHeart()
{
	lastTime_ = QDateTime::currentDateTime();
	protocol_head_t api_head;
	api_head.nStartFlags = 0xAF;
	api_head.nVersion = 0x01;
	api_head.nCmd = CMD_DETU_CLIENT_HEART_BEAT;
	api_head.nDataLen = 0;
	api_head.nResult = 0x00;
	api_head.nStreamId = 0;
	//api_head.nReserver = 0x01;        //预留位
	api_head.nEndFlags = 0xFA;

	response res(api_head.get_size());
	response_add_resprotocol<protocol_head_t>(res, &api_head);
	dmconnection* conn = SocketManagerIns.GetCommSocket();
	if (conn != NULL)
	{
		conn->do_write(res);
	}
}

void DetuPVMS::SlotOnUpdateList()
{
	//干一件事，刷新列表，不刷新地图数据
	if (write_reg_thread_ && write_reg_thread_->joinable())
	{
		write_reg_thread_->join();
	}
	write_reg_thread_.reset(new boost::thread(&DetuPVMS::DetuClientRegistThreadFunc, this));
}

void DetuPVMS::slotOnActiveReport(short errCode, std::string PVSId, unsigned char streamId)
{
	//
	if (!m_handle_open && PVSId == m_handle_pvsId.toStdString() && streamId == 1)
	{
		if (m_handle_id > 0)
		{
			ViewSignal::instance()->sigOnCloseSubStreamClearPlayer(m_handle_id);
		}
		return;
	}
	Log::Info("report PVS active : PVSID : %s result : %d streamId : %d", PVSId.c_str(), errCode, streamId);
	Feedback::instance()->tipsUI(errCode, PVSId, streamId);
}

void DetuPVMS::slotOnGetBandWidth(PVSManageTable_t apiData)
{
	if (m_bandWidthDlg == NULL)
	{
		m_bandWidthDlg = new showBandWidthDlg;
	}
	QString pvsID = QString::fromStdString((char*)apiData.pvsID);
	m_bandWidthDlg->setBandWidth(pvsID, apiData.nInputBandWidth, apiData.nOuntputBandWidth);
	setWindowState((windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
	this->raise();
	activateWindow();
	QPoint point = this->mapToGlobal(this->pos());
	int x = point.x();
	int y = point.y();
	int nX = (this->width() - m_bandWidthDlg->width() + x) / 2;
	int nY = (this->height() - m_bandWidthDlg->height() + y) / 2;
	m_bandWidthDlg->move(nX, nY);
	m_bandWidthDlg->exec();
}

void DetuPVMS::slotOnHandleSubStreamMessage(bool open, QString pvsId, int id)
{
	m_handle_open = open;
	m_handle_pvsId = pvsId;
	m_handle_id = id;
}

void DetuPVMS::slotOnSetFullScreen(bool is_full_screen)
{
	ui->tittleWidget->setVisible(is_full_screen);
	ui->bottomWidget->setVisible(is_full_screen);
	if (!is_full_screen)
	{
		this->showFullScreen();
	}
	else
	{
		this->showNormal();
	}

}

//判断客户端是不是安装后第一次启动
void DetuPVMS::InstallFirstStart()
{
	bool isFirstInstall = DetuPVMSIni::isFirstLogin();
	if (isFirstInstall){
		QDir dir;
		QString feedback_path = qApp->applicationDirPath();
		bool exist = dir.exists(feedback_path + "/Feedback/Feedback.exe");
		if (exist)
		{
			QProcess p(0);
			QString command = feedback_path + "/Feedback/Feedback.exe";//./Feedback/Feedback.exe
			QStringList args;
			args.append("0");
			args.append("Pano-VMS");
			args.append(CLIENT_VERSION_NO);
			args.append(qApp->property("locale").toString());
			QProcess::startDetached(command, args);
			return;
		}
		else
		{
			return;
		}
	}
}

//初始化TCP
void DetuPVMS::initTcpSocket()
{
	if (comm_socket_thread_ && comm_socket_thread_->joinable())
	{
		comm_socket_thread_->join();
	}
	comm_socket_thread_.reset(new boost::thread(&DetuPVMS::RunCommSocketThreadFunc, this));

	//当前版本关闭
// 	if (data_socket_thread_ && data_socket_thread_->joinable())
// 	{
// 		data_socket_thread_->join();
// 	}
// 	data_socket_thread_.reset(new boost::thread(&DetuPVMS::RunDataSocketThreadFunc, this));
}

void DetuPVMS::slotOnInitTimeShow()
{

	QString  time = QTime::currentTime().toString("hh:mm:ss");
	ui->tittleWidget->setTimeShow(time);
	QString tip = QString("CPU：%1%      内存：%2%      磁盘：%3%")
		.arg(PVMSEventManagerManagerIns.cpu_para_.nCpuRate)
		.arg(PVMSEventManagerManagerIns.cpu_para_.nMemRate)
		.arg(PVMSEventManagerManagerIns.cpu_para_.nDiskRate);

	ui->label->setText(tip);
	if (!SocketManagerIns.isConnected())
	{
		ui->label_2->setStyleSheet("background:red;border-radius:5px;");
	}
	else
	{
		ui->label_2->setStyleSheet("background:green;border-radius:5px;");
	}

	if (DetuPVMSIni::getSaveFlvTag())
	{
		ui->label_4->setVisible(true);
		ui->flvTag->setVisible(true);
		ui->flvTag->setStyleSheet("background:green;border-radius:5px;");
	}
	else
	{
		ui->label_4->setVisible(false);
		ui->flvTag->setVisible(false);
		ui->flvTag->setStyleSheet("background:red;border-radius:5px;");
	}
}

//初始化登录模式
void DetuPVMS::slot_initLogin()
{
	CheckForUpdate();
    firstLogin();
}

//初始化首次登录
void DetuPVMS::firstLogin()
{
	//
	if (firstLoginDlg_ == NULL){
		firstLoginDlg_ = new commonDlg;
		firstLoginDlg_->setTitleLabel(QStringLiteral("连接服务器"));
		firstLoginDlg_->setCloseBtn(false);
		connect(firstLoginDlg_, SIGNAL(sigOnFirstFinish()), this, SLOT(setAdminFinish()));
		connect(firstLoginDlg_, SIGNAL(sigOnLogin()), this, SLOT(slot_loginFinish()));
		connect(firstLoginDlg_, SIGNAL(sigOnClose()), this, SLOT(close()));
		connect(firstLoginDlg_, SIGNAL(sigOnServerFinished()), this, SLOT(slotServerFinished()));
		connect(firstLoginDlg_, SIGNAL(sigOnReturnLock()), this, SLOT(slotOnReturnLock()));
		connect(firstLoginDlg_, SIGNAL(sigOnCloseUnlock()), this, SLOT(slotOnCloseUnlock()));
	}

	//判断是否首次登陆
	if (DetuPVMSIni::isFirstLogin()){
		Log::Debug("client first Login and init local data!");
		DetuPVMSIni::setAutoLogin(false);
		DetuPVMSIni::setUnlockState(true);
		DetuPVMSIni::setHeartBeat(5);
		DetuPVMSIni::setDecodeMode(0);
		DetuPVMSIni::setSubDecodeMode(0);
		DetuPVMSIni::setPlayRtmpUrl("1");
		DetuPVMSIni::setReplayRtmpUrl("3");
		DetuPVMSIni::setCapturePath(QApplication::applicationDirPath() + "/capture");
		DetuPVMSIni::setIPCValue("33");
		DetuPVMSIni::setDecodeType("1");
		DetuPVMSIni::setStartSubBitRate(true);
		DetuPVMSIni::setCalibrationScore(50);
		DetuPVMSIni::setSaveFlvTag(false);
		DetuPVMSIni::setIsAdminUser(true);
		//serverConnectSucceed();
		firstLoginDlg_->activateWindow();
		firstLoginDlg_->exec();
	}
	else
	{
		slot_loginDetu();
	}
}

//首次登录完成
void DetuPVMS::setAdminFinish()
{
	slot_loginFinish();
}

void DetuPVMS::slot_loginDetu()
{
	if (!DetuPVMSIni::isAutoLogin()){
		DetuPVMSIni::setUnlockState(true);
		initTcpSocket();
		firstLoginDlg_->setCloseBtn(false);
		firstLoginDlg_->setTitleLabel(QStringLiteral("用户登录"));
		firstLoginDlg_->setLoginDlg();
		firstLoginDlg_->activateWindow();
		firstLoginDlg_->exec();
	}
	else
	{
		//自动登录
		initUnlock();
		show();
		//初始化tcp
		if (!DetuPVMSIni::isFirstLogin())
		{
			initTcpSocket();
		}
		//初始化定时器
		PVMSEventManagerManagerIns.startEvent();
		//启动心跳
		connect(&PVMSEventManagerManagerIns, SIGNAL(sigOnInitHeartBeat()), this, SLOT(slotOnBreakHeart()), Qt::AutoConnection);
		//开始计时
		connect(&PVMSEventManagerManagerIns, SIGNAL(sigOnInitTimeShow()), this, SLOT(slotOnInitTimeShow()), Qt::AutoConnection);
		//刷新列表
		connect(&PVMSEventManagerManagerIns, SIGNAL(sigOnUpdateList()), this, SLOT(SlotOnUpdateList()), Qt::AutoConnection);
	}
	TcpDataManagerIns.setCapturePath(DetuPVMSIni::getCapturePath());
	DetuPVMSIni::setIsFirstLogin(false);
}

void DetuPVMS::slot_loginFinish()
{
	//初始化注册线程
	InitRegist();
	ui->homeWidget->setServerOline(1);
	//初始化定时器
	PVMSEventManagerManagerIns.startEvent();
	//启动心跳
	connect(&PVMSEventManagerManagerIns, SIGNAL(sigOnInitHeartBeat()), this, SLOT(slotOnBreakHeart()), Qt::AutoConnection);
	//开始计时
	connect(&PVMSEventManagerManagerIns, SIGNAL(sigOnInitTimeShow()), this, SLOT(slotOnInitTimeShow()), Qt::AutoConnection);
	//刷新列表
	connect(&PVMSEventManagerManagerIns, SIGNAL(sigOnUpdateList()), this, SLOT(SlotOnUpdateList()), Qt::AutoConnection);

	firstLoginDlg_->close();
    show();
	//首次登录无需校验解锁状态
	if (!DetuPVMSIni::isFirstLogin()){
		initUnlock();
		//initTcpSocket();
	}
	TcpDataManagerIns.setCapturePath(DetuPVMSIni::getCapturePath());
	DetuPVMSIni::setIsFirstLogin(false);
}

void DetuPVMS::slot_unlock()
{
	//解锁
	DetuPVMSIni::setUnlockState(false);
	if (m_lockDlg == NULL)
	{
		m_lockDlg = new lockDlg;
		connect(m_lockDlg, SIGNAL(sigOnUnlock()), this, SLOT(slotOnUnlock()));
	}
	m_lockDlg->activateWindow();
	m_lockDlg->show();
	ui->tittleWidget->setLockStyleSheet(true);
	QPoint point = this->mapToGlobal(this->pos());
	int x = point.x();
	int y = point.y();
	int nX = (this->width() - m_lockDlg->width() + x) / 2;
	int nY = (this->height() - m_lockDlg->height() + y) / 2;
	m_lockDlg->move(nX, nY);
}

void DetuPVMS::slotOnUnlock()
{
	m_lockDlg->hide();
	firstLoginDlg_->setTitleLabel(QStringLiteral("解锁"));
	firstLoginDlg_->setCloseBtn(true);
	firstLoginDlg_->setBtnState();
	firstLoginDlg_->clearPasswd();
	firstLoginDlg_->setUnlockDlg();
	firstLoginDlg_->setUserName();
	firstLoginDlg_->activateWindow();
	firstLoginDlg_->show();
	QPoint point = this->mapToGlobal(this->pos());
	int x = point.x();
	int y = point.y();
	int nX = (this->width() - firstLoginDlg_->width() + x) / 2;
	int nY = (this->height() - firstLoginDlg_->height() + y) / 2;
	firstLoginDlg_->move(nX, nY);
}

void DetuPVMS::slotOnCloseUnlock()
{
	if (firstLoginDlg_ != NULL)
	{
		firstLoginDlg_->close();
		ui->tittleWidget->setLockStyleSheet(false);
	}
}

void DetuPVMS::slot_showHelpPage()
{
		if (helpPage_ == NULL){
			helpPage_ = new HelpPageWidget;
			Log::Debug("helpPage_->setParent(this);");
			helpPage_->setParent(this);
			connect(helpPage_, SIGNAL(sigOnclickToAboutBtn()), this, SLOT(slot_clickToAboutBtn()));
			connect(helpPage_, SIGNAL(sigOnclickToHelpBtn()), this, SLOT(slot_clickToHelpBtn()));
			connect(helpPage_, SIGNAL(sigOnclickToFeedbackBtn()), this, SLOT(slot_clickToFeedbackBtn()));
		}
		helpPage_->move(nXPos_, nYPos_);
		helpPage_->activateWindow();
		helpPage_->show();
}

void DetuPVMS::slot_getHelpPagePos(int x, int y)
{
	nXPos_ = x;
	nYPos_ = y;
	if (helpPage_ != NULL)
	{
		helpPage_->move(nXPos_, nYPos_);
	}
}

void DetuPVMS::slot_clickToAboutBtn()
{
	helpPage_->close();
	firstLoginDlg_->setCloseBtn(false);
	firstLoginDlg_->setTitleLabel(QStringLiteral("关于"));
	firstLoginDlg_->setAboutDlg();
	firstLoginDlg_->activateWindow();
	QPoint point = this->mapToGlobal(this->pos());
	int x = point.x();
	int y = point.y();
	int nX = (this->width() - firstLoginDlg_->width() + x) / 2;
	int nY = (this->height() - firstLoginDlg_->height() + y) / 2;
	firstLoginDlg_->move(nX, nY);
	firstLoginDlg_->resize(521, 360);
	firstLoginDlg_->exec();
}

void DetuPVMS::slot_clickToHelpBtn()
{
	helpPage_->close();
	if (!OpenHelpPDF()){
		Feedback::instance()->maskUI(PDF_NOTFOUND);
	}
}

void DetuPVMS::slot_closeHelpPage()
{
	if (isShowHelpPage_)
	{
		if (helpPage_ != NULL){
			helpPage_->hide();
		}
		isShowHelpPage_ = false;
	}
	else
	{
		slot_showHelpPage();
		isShowHelpPage_ = true;
	}
}

void DetuPVMS::slot_clickToFeedbackBtn()
{
	return;
	helpPage_->close();
	QDir dir;
	QString feedback_path = qApp->applicationDirPath();
	bool exist = dir.exists(feedback_path + "/Feedback/Feedback.exe");
	if (exist){
		Log::Debug("title:Open the feedback interface");
		QProcess p(0);
		QString command = feedback_path + "/Feedback/Feedback.exe";
		QStringList args;
		args.append("1");
		args.append("Pano-VMS");
		args.append(CLIENT_VERSION_NO);
		Log::Debug("clicked feedback to %s\n", qApp->property("local").toString().toLocal8Bit().data());
		args.append(qApp->property("local").toString());
		QProcess::startDetached(command, args);
		return;
	}
	else
	{
		return;
	}
}

void DetuPVMS::slotOnTipClose()
{
	if (tip_ != NULL)
	{
		tip_->hide();
	}
}

void DetuPVMS::slotOnShowSettingDlg()
{
	if (m_settingDlg != NULL)
	{
		m_settingDlg->deleteLater();
		m_settingDlg = NULL;
	}
	m_settingDlg = new systemSettingDlg;
	m_settingDlg->initData();
	m_settingDlg->activateWindow();
	m_settingDlg->show();
	QPoint point = this->mapToGlobal(this->pos());
	int x = point.x();
	int y = point.y();
	int nX = (this->width() - m_settingDlg->width() + x) / 2;
	int nY = (this->height() - m_settingDlg->height() + y) / 2;
	m_settingDlg->move(nX, nY);
}

void DetuPVMS::slotOnSaveAtSettings()
{
	Feedback::instance()->maskUI(SETTINGS_SUCCESS);
}

void DetuPVMS::slotOnUpdateDeviceList()
{
	if (update_list_thread_ && update_list_thread_->joinable())
	{
		update_list_thread_->join();
	}
	update_list_thread_.reset(new boost::thread(&DetuPVMS::UpdateListThreadFunc, this));


}

void DetuPVMS::slotOnSoftwareUpdate(QNetworkReply *reply)
{
	//获取响应的信息，状态码200表示正常
	QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
	//无错误返回
	if (reply->error() == QNetworkReply::NoError)
	{

		QByteArray bytes = reply->readAll();  //获取字节
		QString str_info(bytes);
		if (!bytes.isEmpty())
		{
			if (str_info.contains("Pano-VMS"))
			{
				QStringList version_list = str_info.split("Pano-VMS=");
				assert(version_list.size() == 2);
				if (version_list.size() == 2)
				{
					QString version_url = version_list[1];        //1.0004......DetuPlay_URL= http.....
					qDebug() << "lastest version:" << version_url;
					int lastest_version = version_url.left(6).toDouble() * 10000;          //1.0004


					QString download_url = version_url.remove(0, version_url.indexOf("=") + 1);          //http.....
					download_url = download_url.left(download_url.indexOf(".exe") + 4);

					if (lastest_version > CLIENT_VERSION_NO.toInt() * 10000)
					{
						updateDialog *update = new updateDialog;
						if (update->exec() == QDialog::Accepted)
						{						
							QDesktopServices::openUrl(QUrl(download_url));
							Log::Debug("update download_url is %s", download_url.toLocal8Bit().data());
						}
					}
				}
			}
		}
		else
		{
			Log::Debug("Failed to get software update");
		}
	}
	else
	{
		Log::Debug("Failed to get software update. Please check your Internet connection");
	}
	reply->deleteLater();
}

void DetuPVMS::slotOnDetuClientLoginOk()
{
	//其他登录，初始化tcp
	if (comm_socket_thread_ && comm_socket_thread_->joinable())
	{
		comm_socket_thread_->join();
	}
	comm_socket_thread_.reset(new boost::thread(&DetuPVMS::RunCommSocketThreadFunc, this));

	//当前版本关闭
// 	if (data_socket_thread_ && data_socket_thread_->joinable())
// 	{
// 		data_socket_thread_->join();
// 	}
// 	data_socket_thread_.reset(new boost::thread(&DetuPVMS::RunDataSocketThreadFunc, this));
}

void DetuPVMS::slot_quitExe()
{
    qApp->quit();
}

void DetuPVMS::slot_Exemaxminzed()
{
    static QPoint lastPos;
    static QSize lastSize;
    if(isMaxWindow_) {
        move(lastPos);
        resize(lastSize);
		ui->tittleWidget->setMaxBtnStatus(true);
    } else {
        lastPos = mapToGlobal(rect().topLeft());
        lastSize = size();

        int screen = qApp->desktop()->screenNumber(this);  
        QRect rect = qApp->desktop()->availableGeometry(screen);
        move(rect.topLeft());
        resize(rect.size());
		ui->tittleWidget->setMaxBtnStatus(false);
    }
	ui->homeWidget->setSpeedPos(width() - 190);
	ui->tittleWidget->getShowPos();
	ui->homeWidget->setPosMove();
    isMaxWindow_ = !isMaxWindow_;
	QPoint point = this->mapToGlobal(this->pos());
	QStringList list;
	list << QString::number(this->width()) << QString::number(this->height()) << QString::number(point.x()) << QString::number(point.y());
	DetuPVMSIni::setClientPos(list);

	emit ViewSignal::instance()->sigOnResizeMap();
}

void DetuPVMS::slotOnCloseClient()
{
    ui->homeWidget->setCloseClient();
	

	close();
}




void DetuPVMS::slotOnBreakHeart()
{
	beatHeart();
}

void DetuPVMS::slotBeat()
{
	currTime_ = QDateTime::currentDateTime();
	Log::Debug("beat Time : %s", currTime_.toString("yyyy-MM-dd hh:mm:ss").toLocal8Bit().data());

	//第一次心跳回来后检测版本
	if (!is_version_checked_)
	{
		if (version_check_thread_ && version_check_thread_->joinable())
		{
			version_check_thread_->join();
		}
		version_check_thread_.reset(new boost::thread(&DetuPVMS::VersionCheckThreadFunc, this));
	}
}


void DetuPVMS::slotVersionCheck(bool is_check_ok)
{
	//由于result_sec赋值为0，所以要反一下
	if (is_check_ok)
	{
		is_version_checked_ = true;
	}
	else
	{
		Feedback::instance()->maskUI(VERSION_CHECK_FAILED);
	}

}

void DetuPVMS::slotServerFinished()
{
	initTcpSocket();
}

void DetuPVMS::slotOnReturnLock()
{
	if (firstLoginDlg_ != NULL && m_lockDlg != NULL)
	{
		firstLoginDlg_->close();
		m_lockDlg->activateWindow();
		m_lockDlg->show();
		QPoint point = this->mapToGlobal(this->pos());
		int x = point.x();
		int y = point.y();
		int nX = (this->width() - m_lockDlg->width() + x) / 2;
		int nY = (this->height() - m_lockDlg->height() + y) / 2;
		m_lockDlg->move(nX, nY);
	}
}

/*************************************************
函数名:    	slotOnSelectWarning
函数描述:	空选择操作警告响应函数
输入参数:
输出参数:
返回值:
**************************************************/
void DetuPVMS::slotOnSelectWarning()
{
	Feedback::instance()->maskUI(NULL_SELECTED);
}

/*************************************************
函数名:    	slotOnBindPTZWarning
函数描述:	球机未绑定通知槽函数
输入参数:
输出参数:
返回值:
**************************************************/
void DetuPVMS::slotOnBindPTZWarning()
{
	Feedback::instance()->maskUI(PTZ_NO_BIND);
}

/*************************************************
函数名:    	slotOnHandleStreamFailed
函数描述:	流处理失败通知函数
输入参数:
输出参数:
返回值:
**************************************************/
void DetuPVMS::slotOnHandleStreamFailed()
{
	Feedback::instance()->maskUI(STREAM_HANDLE_FAILED);
}

/*************************************************
函数名:    	slotOnRebootDeviceFailed
函数描述:	重启设备失败通知函数
输入参数:    streamId：1（M1）  2（nvr）
输出参数:
返回值:
**************************************************/
void DetuPVMS::slotOnRebootDeviceFailed(unsigned char streamId)
{
	if (streamId == 1)
	{
		Feedback::instance()->maskUI(REBOOT_M1_FAILED);
	}
}

void DetuPVMS::slotOnOptMizeSuccess()
{
	Feedback::instance()->maskUI(OPT_MIZE_SUCCESS);
}

void DetuPVMS::slotOnReportTCSError(std::string deviceID, short result)
{
	switch (result)
	{
	case -1:
		Feedback::instance()->tipsUI(TCS_SERVER_DISCONNECT_ERROR, deviceID, 0);
		break;
	case -11999:
		QMessageBox::warning(this, QString::fromStdString(deviceID), tr("TCS server : pullFlow failed !"));
		//Feedback::instance()->tipsUI(TCS_PULL_RTMP_ERROR, deviceID, 0);
		break;
	case -11998:
		QMessageBox::warning(this, QString::fromStdString(deviceID), tr("TCS server : pushFlow failed !"));
		//Feedback::instance()->tipsUI(TCS_PUSH_RTMP_ERROR, deviceID, 0);
		break;
	default:
		break;
	}
	ViewSignal::instance()->sigOnReportTCSDisconnectError(deviceID);
}

void DetuPVMS::slotOnReportTCSOffLine(int serverId)
{
	Feedback::instance()->tipsUI(TCS_SERVER_OFFLINE, boost::lexical_cast<std::string>(serverId), 0);
	ViewSignal::instance()->sigOnReportTCSOffLine(serverId);
}

void DetuPVMS::slotOnHandleTCSReset(bool is_Ok)
{
	if (is_Ok)
	{
		QMessageBox::warning(this, tr("tips"), tr("reset TCS config success !"));
	}
	else{
		QMessageBox::warning(this, tr("tips"), tr("reset TCS config failed !"));
	}
}

void DetuPVMS::slot0nSocketConnectStatus(int status)
{
	SOCKETSTATE_ENUM socket_status = (SOCKETSTATE_ENUM)status;
	switch (socket_status)
	{
	case SOCKETSTATE_SUCCESS:
	{
		if (tc_comm_ptr_!=NULL)
		{
			SocketManagerIns.SetCommSocket(tc_comm_ptr_->get_connection());
		}
		if (tc_map_data_ptr_ != NULL)
		{
			SocketManagerIns.SetDataSocket(tc_map_data_ptr_->get_connection());
		}
		if (DetuPVMSIni::isFirstLogin())
		{
			serverConnectSucceed();
		}
		else if (DetuPVMSIni::isAutoLogin())
		{
			//初始化注册线程
			InitRegist();
			ui->homeWidget->setServerOline(1);
		}
		Log::Debug("server connected");
		SocketManagerIns.setIsConnected(true);
		break;
	}
	case SOCKETSTATE_DISCONNECT:
	case SOCKETSTATE_FAILED:
	{		
		SocketManagerIns.setIsConnected(false);
		SocketManagerIns.SetCommSocket(nullptr);
 		Feedback::instance()->maskUI(SERVER_UNCONNECT);
 		ui->homeWidget->setServerOline(0);
		ui->homeWidget->closePreviewReplay();
		break;
	}
	default:
		break;
	}



}


void DetuPVMS::mousePressEvent(QMouseEvent *event)
{
    if(isMaxWindow_) {
        return;
    }

    // current
    int x = event->pos().x();
    int y = event->pos().y();

    // top left
    int x1 = ui->tittleWidget->pos().x();
    int y1 = ui->tittleWidget->pos().y();

    // bottom right
    int x2 = x1 + ui->tittleWidget->width();
    int y2 = y1 + ui->tittleWidget->height();

    if(x > x1 && x < x2 && y > y1 && y < y2) {
        lastMousePos_ = event->pos();
        isDraggingWindow_ = true;
    }
}

void DetuPVMS::mouseMoveEvent(QMouseEvent *event)
{

    if(isDraggingWindow_) {
        this->move(event->globalPos()-lastMousePos_);
		ui->homeWidget->setPosMove();
		emit ViewSignal::instance()->sigOnResizeMap();
    }
}

void DetuPVMS::mouseReleaseEvent(QMouseEvent *event)
{
     isDraggingWindow_ = false;
	 QPoint point = this->mapToGlobal(this->pos());
	 QStringList list;
	 list << QString::number(this->width()) << QString::number(this->height()) << QString::number(point.x()) << QString::number(point.y());
	 DetuPVMSIni::setClientPos(list);
}

void DetuPVMS::keyPressEvent(QKeyEvent *event)
{
	return QWidget::keyPressEvent(event);
	if (event->key() == Qt::Key_P){
		bool flag = !DetuPVMSIni::getSaveFlvTag();
		Log::Info("Flv file save open/close : %d", flag);
		DetuPVMSIni::setSaveFlvTag(flag);
	}
}

void DetuPVMS::closeEvent(QCloseEvent *e)
{
    static bool isQuiting = false;
    e->ignore();
    if(!isQuiting) {
        isQuiting = true;
        slot_quitExe();
    }
}

//重写显示事件，避免客户端最小化时界面不去刷新
void DetuPVMS::showEvent(QShowEvent *e)
{
	this->setAttribute(Qt::WA_Mapped);
	QPoint point = this->mapToGlobal(this->pos());
	QStringList list;
	list << QString::number(this->width()) << QString::number(this->height()) << QString::number(point.x()) << QString::number(point.y());
	DetuPVMSIni::setClientPos(list);
	QWidget::showEvent(e);
}
