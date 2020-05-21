/************************************************
* \file HkSdkProduct.h
*
* \author HuZhengdong
* \date 20170925
* �����࣬HKSDK��װ��Ʒ
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
	//���ɵĹ���ģʽ�ӿ�
	bool Login(QString Ip, int port, QString user, QString passwd);
	void SetCfg(HWND PlayWnd);
	bool Play();
	bool Contral(int index, int dwStop);
	bool Close();
	//��̨���ƺ���
	void PTZControlAll(LONG lRealHandle, DWORD dwPTZCommand, DWORD dwStop, int Speed);

	/*************************************************
	������:    	setPoint
	��������:	����Ԥ�õ�λ
	�������:	index Ԥ�õ����
				type,���ֿ�������
				SET_PRESET 8 ����Ԥ�õ�
				CLE_PRESET 9 ���Ԥ�õ�
				GOTO_PRESET 39 ת��Ԥ�õ�
	�������:
	����ֵ:
	*************************************************/
	void setPoint(int index, int type);

private:
	//��ȡ�豸��Դ��Ϣ
	void DoGetDeviceResoureCfg();	
	//��ȡ��̨��������Ϣ
	void GetDecoderCfg();		



private:

	long lPlayHandle_;
	bool is_reset_ok_;
	LOCAL_DEVICE_INFO struDeviceInfo_;

	bool bIsPlaying_;

	HWND PlayWnd_;			//���ھ��
};

#endif // HKSDKPRODUCT_H