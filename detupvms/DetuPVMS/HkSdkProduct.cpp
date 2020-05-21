
#include <QMessageBox>
#include "HkSdkProduct.h"

#include "GeneralDef.h"

HkSdkProduct::HkSdkProduct()
{
}


HkSdkProduct::~HkSdkProduct()
{
}

bool HkSdkProduct::Login(QString Ip, int port, QString user, QString passwd)
{
	NET_DVR_DEVICEINFO_V30 DeviceInfoTmp;
	memset(&DeviceInfoTmp, 0, sizeof(NET_DVR_DEVICEINFO_V30));
	QByteArray ip_ = Ip.toLatin1();
	WORD port_ = port;
	QByteArray user_ = user.toLatin1();
	QByteArray passwd_ = passwd.toLatin1();
	LONG loginID = NET_DVR_Login_V30(ip_.data(), port_, user_.data(), passwd_.data(), &DeviceInfoTmp);
	if (loginID == -1)
	{
		Log::Info("Login to Device failed!");
		return false;
	}
	struDeviceInfo_.lLoginID = loginID;
	struDeviceInfo_.iDeviceChanNum = DeviceInfoTmp.byChanNum;
	struDeviceInfo_.iIPChanNum = DeviceInfoTmp.byIPChanNum;
	struDeviceInfo_.iStartChan = DeviceInfoTmp.byStartChan;
	struDeviceInfo_.iIPStartChan = DeviceInfoTmp.byStartDChan;
	return true;
}


void HkSdkProduct::SetCfg(HWND PlayWnd)
{
	DoGetDeviceResoureCfg();		//获取设备资源信息
	GetDecoderCfg();                //获取云台解码器信息

	PlayWnd_ = PlayWnd;
}

bool HkSdkProduct::Play()
{	 	
	NET_DVR_CLIENTINFO ClientInfo;
	ClientInfo.hPlayWnd = PlayWnd_;
	ClientInfo.lChannel = 1;
	ClientInfo.lLinkMode = 0;
	ClientInfo.sMultiCastIP = NULL;
	lPlayHandle_ = NET_DVR_RealPlay_V30(struDeviceInfo_.lLoginID, &ClientInfo, NULL, NULL, TRUE);
	if (-1 == lPlayHandle_)
	{
		DWORD err = NET_DVR_GetLastError();
		QString error = QStringLiteral("播放出错，错误代码:%1").arg(err);
		Log::Debug("LOAD HKSDK PLAY ERROR CODE : %s", error.toStdString().c_str());
		return false;
	}
	bIsPlaying_ = true;
	return true;
}

bool HkSdkProduct::Contral(int index, int dwStop)
{
	this->PTZControlAll(lPlayHandle_, index, dwStop, 6);
	return 0;
}

bool HkSdkProduct::Close()
{
	if (lPlayHandle_ != -1)
	{
		bool ret = NET_DVR_StopRealPlay(lPlayHandle_);
		if (!ret)
		{
			return false;
		}
		lPlayHandle_ = -1;
		bIsPlaying_ = false;
		return true;
	}
	return false;
}

/*************************************************
函数名:    	DoGetDeviceResoureCfg
函数描述:	获取设备的通道资源
输入参数:
输出参数:
返回值:
**************************************************/
void HkSdkProduct::DoGetDeviceResoureCfg()
{
	 	NET_DVR_IPPARACFG_V40 IpAccessCfg;
	 	memset(&IpAccessCfg, 0, sizeof(IpAccessCfg));
	 	DWORD  dwReturned;
	 
	 	struDeviceInfo_.bIPRet = NET_DVR_GetDVRConfig(0,
	 		NET_DVR_GET_IPPARACFG_V40, 0, &IpAccessCfg, sizeof(NET_DVR_IPPARACFG_V40), &dwReturned);
	 	int i;
	 	if (!struDeviceInfo_.bIPRet)   //不支持ip接入,9000以下设备不支持禁用模拟通道
	 	{
	 		for (i = 0; i < MAX_ANALOG_CHANNUM; i++)
	 		{
	 			if (i < struDeviceInfo_.iDeviceChanNum)
	 			{
	 				sprintf(struDeviceInfo_.struChanInfo[i].chChanName, "camera%d", i + struDeviceInfo_.iStartChan);
	 				struDeviceInfo_.struChanInfo[i].iChanIndex = i + struDeviceInfo_.iStartChan;  //通道号
	 				struDeviceInfo_.struChanInfo[i].bEnable = TRUE;
	 			}
	 			else
	 			{
	 				struDeviceInfo_.struChanInfo[i].iChanIndex = -1;
	 				struDeviceInfo_.struChanInfo[i].bEnable = FALSE;
	 				sprintf(struDeviceInfo_.struChanInfo[i].chChanName, "");
	 			}
	 		}
	 	}
	 	else        //支持IP接入，9000设备
	 	{
	 		for (i = 0; i < MAX_ANALOG_CHANNUM; i++)  //模拟通道
	 		{
	 			if (i < struDeviceInfo_.iDeviceChanNum)
	 			{
	 				sprintf(struDeviceInfo_.struChanInfo[i].chChanName, "camera%d", i + struDeviceInfo_.iStartChan);
	 				struDeviceInfo_.struChanInfo[i].iChanIndex = i + struDeviceInfo_.iStartChan;
	 				if (IpAccessCfg.byAnalogChanEnable[i])
	 				{
	 					struDeviceInfo_.struChanInfo[i].bEnable = TRUE;
	 				}
	 				else
	 				{
	 					struDeviceInfo_.struChanInfo[i].bEnable = FALSE;
	 				}
	 
	 			}
	 			else//clear the state of other channel
	 			{
	 				struDeviceInfo_.struChanInfo[i].iChanIndex = -1;
	 				struDeviceInfo_.struChanInfo[i].bEnable = FALSE;
	 				sprintf(struDeviceInfo_.struChanInfo[i].chChanName, "");
	 			}
	 		}
	 
	 		//数字通道
	 		for (i = 0; i < MAX_IP_CHANNEL; i++)
	 		{
	 			if (IpAccessCfg.struStreamMode[i].uGetStream.struChanInfo.byEnable)  //ip通道在线
	 			{
	 				struDeviceInfo_.struChanInfo[i + MAX_ANALOG_CHANNUM].bEnable = TRUE;
	 				struDeviceInfo_.struChanInfo[i + MAX_ANALOG_CHANNUM].iChanIndex = i + IpAccessCfg.dwStartDChan;
	 				sprintf(struDeviceInfo_.struChanInfo[i + MAX_ANALOG_CHANNUM].chChanName, "IP Camera %d", i + 1);
	 
	 			}
	 			else
	 			{
	 				struDeviceInfo_.struChanInfo[i + MAX_ANALOG_CHANNUM].bEnable = FALSE;
	 				struDeviceInfo_.struChanInfo[i + MAX_ANALOG_CHANNUM].iChanIndex = -1;
	 			}
	 		}
	 	}
}

/*************************************************
函数名:    	GetDecoderCfg
函数描述:	获取云台解码器信息
输入参数:
输出参数:
返回值:
**************************************************/
void HkSdkProduct::GetDecoderCfg()
{
	 	NET_DVR_DECODERCFG_V30 DecoderCfg;
	 	DWORD  dwReturned;
	 	BOOL bRet;
	 
	 	//获取通道解码器信息
	 	for (int i = 0; i < MAX_CHANNUM_V30; i++)
	 	{
	 		if (struDeviceInfo_.struChanInfo[i].bEnable)
	 		{
	 			memset(&DecoderCfg, 0, sizeof(NET_DVR_DECODERCFG_V30));
	 			bRet = NET_DVR_GetDVRConfig(struDeviceInfo_.lLoginID, NET_DVR_GET_DECODERCFG_V30, \
		 				struDeviceInfo_.struChanInfo[i].iChanIndex, &DecoderCfg, sizeof(NET_DVR_DECODERCFG_V30), &dwReturned);
	 			if (!bRet)
	 			{
	 				Log::Info("Get DecderCfg failed,Chan : %d", struDeviceInfo_.struChanInfo[i].iChanIndex);
	 				continue;
	 			}
	 			memcpy(&struDeviceInfo_.struChanInfo[i].struDecodercfg, &DecoderCfg, sizeof(NET_DVR_DECODERCFG_V30));
	 		}
	 	}
}

/*************************************************
函数名:    	PTZControlAll
函数描述:	云台控制函数
输入参数:
输出参数:
返回值:
*************************************************/
void HkSdkProduct::PTZControlAll(LONG lRealHandle, DWORD dwPTZCommand, DWORD dwStop, int Speed)
{

	BOOL ret;
	if (Speed >= 1)
	{
		ret = NET_DVR_PTZControlWithSpeed(lRealHandle, dwPTZCommand, dwStop, Speed);
		if (!ret)
		{
			//qDebug() << ("云台控制失败!");
			return;
		}
	}
	else
	{
		ret = NET_DVR_PTZControl(lRealHandle, dwPTZCommand, dwStop);
		if (!ret)
		{
			//qDebug() << ("云台控制失败!");
			return;
		}
	}

}


void HkSdkProduct::setPoint(int index,int type)
{
		//待定
	 	//if (m_struDeviceInfo.struChanInfo[0].struDecodercfg.bySetPreset[index - 1] == TRUE)
	 	//{
	 	//	delPoint(index);
	 	//}
	 	if (lPlayHandle_ >= 0)
	 	{
			if (!NET_DVR_PTZPreset(lPlayHandle_, type, index))
	 		{
	 			Log::Info("set point failed!");
	 			return;
	 		}
	 	}
	 	else
	 	{
	 		//if (!NET_DVR_PTZPreset_Other(m_struDeviceInfo.lLoginID, m_struDeviceInfo.struChanInfo[0].iChanIndex, SET_PRESET, index))
	 		{
	 			Log::Info("set point failed!");
	 			return;
	 		}
	 	}
	 	//添加到预置点信息
	 	//m_struDeviceInfo.struChanInfo[0].struDecodercfg.bySetPreset[index - 1] = TRUE;
}
