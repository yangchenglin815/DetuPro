#include "DetuPVMSIni.h"

#include <QSettings>
#include <QFile>
#include <QDir>

QString DetuPVMSIniPath = QDir::homePath() + "/AppData/Local/Pano-VMS/Pano-VMS.ini";

bool DetuPVMSIni::isFirstLogin()
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	return settings.value("login/isFirstLogin", true).toBool();
}

void DetuPVMSIni::setIsFirstLogin(bool isFirstLogin)
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	settings.setValue("login/isFirstLogin", isFirstLogin);
}

void DetuPVMSIni::setCpuType(QString cpu)
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	settings.setValue("CPU/CPUType", cpu);
}

QString DetuPVMSIni::getAdminUser()
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	return settings.value("admin/username", "").toString();
}

void DetuPVMSIni::setAdminUser(QString adminUser)
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	settings.setValue("admin/username", adminUser);
}

bool DetuPVMSIni::getIsAdminUser()
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	return settings.value("admin/is_adminUser", true).toBool();
}

void DetuPVMSIni::setIsAdminUser(bool is_adminUser)
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	settings.setValue("admin/is_adminUser", is_adminUser);
}
QString DetuPVMSIni::getAdminPasswd()
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	return settings.value("admin/passwd", "").toString();
}

void DetuPVMSIni::setAdminPasswd(QString adminPasswd)
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	settings.setValue("admin/passwd", adminPasswd);
}

bool DetuPVMSIni::isAutoLogin()
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	return settings.value("login/isAutoLogin", true).toBool();
}

void DetuPVMSIni::setAutoLogin(bool isAutoLogin)
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	settings.setValue("login/isAutoLogin", isAutoLogin);
}

bool DetuPVMSIni::isUnlockState()
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	return settings.value("login/isUnlock", true).toBool();
}

void DetuPVMSIni::setUnlockState(bool isUnlock)
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	settings.setValue("login/isUnlock", isUnlock);
}

QString DetuPVMSIni::getServerIP()
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	return settings.value("server/ip", "").toString();
}

void DetuPVMSIni::setServerIP(QString serverIP)
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	settings.setValue("server/ip", serverIP);
}

QString DetuPVMSIni::getServerPort()
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	return settings.value("server/port", "").toString();
}

void DetuPVMSIni::setServerPort(QString serverPort)
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	settings.setValue("server/port", serverPort);
}

QString DetuPVMSIni::getPlayRtmpUrl()
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	return settings.value("detu/playRtmp", "").toString();
}

void DetuPVMSIni::setPlayRtmpUrl(QString rtmpUrl)
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	settings.setValue("detu/playRtmp", rtmpUrl);
}

QString DetuPVMSIni::getReplayRtmpUrl()
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	return settings.value("detu/replayRtmp", "").toString();
}

void DetuPVMSIni::setReplayRtmpUrl(QString rtmpUrl)
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	settings.setValue("detu/replayRtmp", rtmpUrl);
}

QString DetuPVMSIni::getIPCValue()
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	return settings.value("detu/ipc", "").toString();
}

void DetuPVMSIni::setIPCValue(QString ipc)
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	settings.setValue("detu/ipc", ipc);
}

QString DetuPVMSIni::getDecodeType()
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	return settings.value("detu/decodeType", "").toString();
}

void DetuPVMSIni::setDecodeType(QString decodeType)
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	settings.setValue("detu/decodeType", decodeType);
}

bool DetuPVMSIni::getSaveFlvTag()
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	return settings.value("detu/flvSaveTag", true).toBool();
}

void DetuPVMSIni::setSaveFlvTag(bool saveTag)
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	settings.setValue("detu/flvSaveTag", saveTag);
}

bool DetuPVMSIni::getDecodeMode()
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	return settings.value("detu/isHardDecode", true).toBool();
}

void DetuPVMSIni::setDecodeMode(bool hardDecode)
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	settings.setValue("detu/isHardDecode", hardDecode);
}

bool DetuPVMSIni::getSubDecodeMode()
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	return settings.value("detu/isSubHardDecode", true).toBool();
}

void DetuPVMSIni::setSubDecodeMode(bool hardDecode)
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	settings.setValue("detu/isSubHardDecode", hardDecode);
}

int DetuPVMSIni::getHeartBeat()
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	return settings.value("detu/heartBeat", -1).toInt();
}

void DetuPVMSIni::setHeartBeat(int time)
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	settings.setValue("detu/heartBeat", time);
}

QString DetuPVMSIni::getCapturePath()
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	return settings.value("detu/capturePath", "").toString();
}

void DetuPVMSIni::setCapturePath(QString path)
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	settings.setValue("detu/capturePath", path);
}

QString DetuPVMSIni::getPlayBitRate()
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	return settings.value("BitRate/playBitRate", "").toString();
}

void DetuPVMSIni::setPlayBitRate(QString bitRate)
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	settings.setValue("BitRate/playBitRate", bitRate);
}

QString DetuPVMSIni::getSubPlayBitRate()
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	return settings.value("BitRate/subPlayBitRate", "").toString();
}

void DetuPVMSIni::setSubPlayBitRate(QString bitRate)
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	settings.setValue("BitRate/subPlayBitRate", bitRate);
}

QString DetuPVMSIni::getReplayBitRate()
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	return settings.value("BitRate/replayBitRate", "").toString();
}

void DetuPVMSIni::setReplayBitRate(QString bitRate)
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	settings.setValue("BitRate/replayBitRate", bitRate);
}

QString DetuPVMSIni::getSubReplayBitRate()
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	return settings.value("BitRate/subReplayBitRate", "").toString();
}

void DetuPVMSIni::setSubReplayBitRate(QString bitRate)
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	settings.setValue("BitRate/subReplayBitRate", bitRate);
}

bool DetuPVMSIni::getStartSubBitRate()
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	return settings.value("detu/isStartBitRate", true).toBool();
}

void DetuPVMSIni::setStartSubBitRate(bool on)
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	settings.setValue("detu/isStartBiipctRate", on);
}

QStringList DetuPVMSIni::getClientPos()
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	return settings.value("detu/clientPos", "" ).toStringList();
}

void DetuPVMSIni::setClientPos(QStringList list)
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	settings.setValue("detu/clientPos", list);
}

int DetuPVMSIni::getCalibrationScore()
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	return settings.value("detu/CalibrationScore", -1).toInt();
}

void DetuPVMSIni::setCalibrationScore(int score)
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	settings.setValue("detu/CalibrationScore", score);
}

void DetuPVMSIni::setGlobalStreamType(bool type)
{
	m_global_stream_type = type;
}

bool DetuPVMSIni::getGlobalStreamType()
{
	return m_global_stream_type;
}

void DetuPVMSIni::setGlobalSettingGet(bool flag)
{
	m_global_Setting_get_stream = flag;
}

bool DetuPVMSIni::getGlobalSettingGet()
{
	return m_global_Setting_get_stream;
}

void DetuPVMSIni::setClientUUID(QString quuid)
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	settings.setValue("admin/uuid", quuid);
}

QString DetuPVMSIni::getClienUUID()
{
	QSettings settings(DetuPVMSIniPath, QSettings::IniFormat);
	return settings.value("admin/uuid", "").toString();
}
