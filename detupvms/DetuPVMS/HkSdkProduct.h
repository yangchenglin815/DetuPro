/************************************************
* \file HkSdkProduct.h
*
* \author HuZhengdong
* \date 20170925
* 工厂类，HKSDK封装产品
************************************************/
#ifndef HKSDKPRODUCT_H
#define HKSDKPRODUCT_H

#include "CamProduct.h"



class HkSdkProduct//:public CamProduct
{
public:
	HkSdkProduct();
	virtual ~HkSdkProduct();
public:
	//集成的工厂模式接口
	bool Login(QString Ip, int port, QString user, QString passwd);
	void SetCfg(HWND PlayWnd);
	bool Play();
	bool Contral(int index, int dwStop);
	bool Close();
	//云台控制函数
	void PTZControlAll(LONG lRealHandle, DWORD dwPTZCommand, DWORD dwStop, int Speed);

	/*************************************************
	函数名:    	setPoint
	函数描述:	设置预置点位
	输入参数:	index 预置点序号
				type,三种控制类型
				SET_PRESET 8 设置预置点
				CLE_PRESET 9 清除预置点
				GOTO_PRESET 39 转到预置点
	输出参数:
	返回值:
	*************************************************/
	void setPoint(int index, int type);

private:
	//获取设备资源信息
	void DoGetDeviceResoureCfg();	
	//获取云台解码器信息
	void GetDecoderCfg();		



private:

	long lPlayHandle_;
	bool is_reset_ok_;
	LOCAL_DEVICE_INFO struDeviceInfo_;

	bool bIsPlaying_;

	HWND PlayWnd_;			//窗口句柄
};

#endif // HKSDKPRODUCT_H