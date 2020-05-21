#pragma once
#include <QString>


static bool m_global_stream_type = false;
static bool m_global_Setting_get_stream = false;

class DetuPVMSIni
{
public:
	//是否为首次登陆
	static bool isFirstLogin();   
	static void setIsFirstLogin(bool isFirstLogin);
	//写入CPU型号
	static void setCpuType(QString cpu);
	//用户管理员账户
	static QString getAdminUser();
	static void setAdminUser(QString adminUser);
	//是否是管理员账户
	static bool getIsAdminUser();
	static void setIsAdminUser(bool is_adminUser);
	//用户管理员密码
	static QString getAdminPasswd();
	static void setAdminPasswd(QString adminPasswd);
	//是否自动登录
	static bool isAutoLogin();
	static void setAutoLogin(bool isAutoLogin);
	//是否为锁定状态
	static bool isUnlockState();
	static void setUnlockState(bool isUnlock);
	//获取服务器IP地址
	static QString getServerIP();
	static void setServerIP(QString serverIP);
	//获取服务器端口
	static QString getServerPort();
	static void setServerPort(QString serverPort);
	//预览码流
	static QString getPlayRtmpUrl();
	static void setPlayRtmpUrl(QString rtmpUrl);
	//回放码流
	static QString getReplayRtmpUrl();
	static void setReplayRtmpUrl(QString rtmpUrl);
	//ipc
	static QString getIPCValue();
	static void setIPCValue(QString ipc);
	//decode type
	static QString getDecodeType();
	static void setDecodeType(QString decodeType);
	//flv
	static bool getSaveFlvTag();
	static void setSaveFlvTag(bool saveTag);
	//主码流硬解
	static bool getDecodeMode();
	static void setDecodeMode(bool hardDecode);
	//子码流硬解
	static bool getSubDecodeMode();
	static void setSubDecodeMode(bool hardDecode);
	//心跳设置
	static int getHeartBeat();
	static void setHeartBeat(int time);
	//抓图存储路径
	static QString getCapturePath();
	static void setCapturePath(QString path);
	//码率
	static QString getPlayBitRate();
	static void setPlayBitRate(QString bitRate);
	static QString getSubPlayBitRate();
	static void setSubPlayBitRate(QString bitRate);
	static QString getReplayBitRate();
	static void setReplayBitRate(QString bitRate);
	static QString getSubReplayBitRate();
	static void setSubReplayBitRate(QString bitRate);
	//开启子码流
	static bool getStartSubBitRate();
	static void setStartSubBitRate(bool on);
	//记录客户端的宽高和坐标
	static  QStringList getClientPos();
	static void setClientPos(QStringList list);
	//标定评分
	static int getCalibrationScore();
	static void setCalibrationScore(int score);

	static void setGlobalStreamType(bool type);
    static bool getGlobalStreamType();

	static void setGlobalSettingGet(bool flag);
	static bool getGlobalSettingGet();

	//UUID
	static void setClientUUID(QString quuid);
	static QString getClienUUID();
};

