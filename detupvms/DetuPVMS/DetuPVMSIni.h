#pragma once
#include <QString>


static bool m_global_stream_type = false;
static bool m_global_Setting_get_stream = false;

class DetuPVMSIni
{
public:
	//�Ƿ�Ϊ�״ε�½
	static bool isFirstLogin();   
	static void setIsFirstLogin(bool isFirstLogin);
	//д��CPU�ͺ�
	static void setCpuType(QString cpu);
	//�û�����Ա�˻�
	static QString getAdminUser();
	static void setAdminUser(QString adminUser);
	//�Ƿ��ǹ���Ա�˻�
	static bool getIsAdminUser();
	static void setIsAdminUser(bool is_adminUser);
	//�û�����Ա����
	static QString getAdminPasswd();
	static void setAdminPasswd(QString adminPasswd);
	//�Ƿ��Զ���¼
	static bool isAutoLogin();
	static void setAutoLogin(bool isAutoLogin);
	//�Ƿ�Ϊ����״̬
	static bool isUnlockState();
	static void setUnlockState(bool isUnlock);
	//��ȡ������IP��ַ
	static QString getServerIP();
	static void setServerIP(QString serverIP);
	//��ȡ�������˿�
	static QString getServerPort();
	static void setServerPort(QString serverPort);
	//Ԥ������
	static QString getPlayRtmpUrl();
	static void setPlayRtmpUrl(QString rtmpUrl);
	//�ط�����
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
	//������Ӳ��
	static bool getDecodeMode();
	static void setDecodeMode(bool hardDecode);
	//������Ӳ��
	static bool getSubDecodeMode();
	static void setSubDecodeMode(bool hardDecode);
	//��������
	static int getHeartBeat();
	static void setHeartBeat(int time);
	//ץͼ�洢·��
	static QString getCapturePath();
	static void setCapturePath(QString path);
	//����
	static QString getPlayBitRate();
	static void setPlayBitRate(QString bitRate);
	static QString getSubPlayBitRate();
	static void setSubPlayBitRate(QString bitRate);
	static QString getReplayBitRate();
	static void setReplayBitRate(QString bitRate);
	static QString getSubReplayBitRate();
	static void setSubReplayBitRate(QString bitRate);
	//����������
	static bool getStartSubBitRate();
	static void setStartSubBitRate(bool on);
	//��¼�ͻ��˵Ŀ�ߺ�����
	static  QStringList getClientPos();
	static void setClientPos(QStringList list);
	//�궨����
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

