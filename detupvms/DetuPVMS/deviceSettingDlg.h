/************************************************
* \file deviceSettingDlg.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* 设备设置弹窗
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
	void initData(deviceInfo info);    //初始化数据信息
	void getBitRate(int streamId);    //获取码率等信息请求
	void setBitRate(int streamId, QString bitRate);    //设置码率等信息请求
	void initDirection(int direction);    //初始化相机方向
	void getStream();     //获取流请求
	void delStream();     //删除流请求
	void addStream();    //增加流请求
	void rebootM1Request();    //重启设备请求
signals:
	void sigOnSave(deviceInfo info);
	void sigOnSaveDirection(int direction);
	void sigOnSetAutoCircle(bool isAutoRotate, QString deviceId);
protected:
	/*鼠标事件  控制窗口移动*/
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
private slots:
	void slotOnSave();   //保存按键触发槽函数
	void slotOnCancel();
	void slotOnGetBitRate(unsigned char streamId, api_detu_client_av_param_t* res);   //请求码率等返回槽函数
	void slotOnSetBitRate(unsigned char streamId, bool is_ok);     //设置码率等返回槽函数
	void slotOnSetAutoCircle();
	void slotOnScrollMove();  //滚动条移动槽函数
	void slotOnStartSubBit(bool chceked);   //子码流开启关闭槽函数
	void slotOnHandleStreamSuccess(unsigned char streamId);   //流处理成功返回槽函数
	void slotOnRebootM1();   //M1重启槽函数
	void slotOnRebootDeviceSuccess(unsigned char streamId);    //设备重启成功返回槽函数
	void slotOnResetFramerate(QString framerate);      //重置子码流帧率
	void slotOnTipBitrate(int index);    //标注所选分辨率的码率范围
private:
	void init();   //初始化界面
	void initConnect();  //初始化信号槽
	void reportDeviceName(QString name, QString deviceId);  //上报对应nvr ID的别名
	void checkout(bool subChecked);  //校验是否需要重启M1
	void rebootM1Tip();  //重启M1提示框
	void checkoutBitRate(int min, int max);   //校验码率
private:
	Ui::deviceSettingDlg ui;
	QPoint lastMousePos_;
	bool isDraggingWindow_;
	bool isAutoRotate_;
	int direction_;    //相机预置方向
	deviceInfo m_info;   //当前设备信息
	api_detu_client_av_param_t av_param_1t_;   //主码流相关信息
	api_detu_client_av_param_t av_param_2t_;   //子码流相关信息
	//統計器
	int setBitRateCount_;
	boost::shared_ptr<boost::thread> get_stream_thread_;    //获取流线程
	boost::shared_ptr<boost::thread> reboot_device_thread_;    //重启设备线程
	commonTipDlg *tipDlg;   //相机提示框对象
	/*由于分辨率和帧率的修改需重启相机，这里保存当前的值来校验是否设置发生了变化，导致重启相机*/
	QString mResolution;
	QString mFramerate;
	QString mSubResolution;
	QString mSubFramerate;
};

#endif // DEVICESETTINGDLG_H
