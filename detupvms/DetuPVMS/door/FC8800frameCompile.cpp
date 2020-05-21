#include "FC8800frame.h"
#include "FC8800frameCompile.h"
#include <string.h>

int mRXDStep=0;//接收数据的步骤
BYTE mRXDbuf[16];//接收到的十六进制数值
bool mRXDTranslate=false;//接收到转移码
int mRXDDataIndex=0;//接收到缓存索引
FC8800frame mRxFrame;


//返回解析完毕的命令结构
FC8800frame GetRxFrame()
{
	return mRxFrame;
}

void IniRXDValue()
{
	mRXDStep=0;
	memset(mRXDbuf, 0, 16);
	mRXDTranslate=false;
	mRXDDataIndex=0;
	freeFrame(&mRxFrame);
}


//加入数据至缓冲中
void AddRxData(BYTE src)
{
	if(mRXDDataIndex==0)//第一次收到数据，初始化缓存
		memset(mRXDbuf, 0, 16);;
	
	mRXDbuf[mRXDDataIndex++]=src;
}


//对每个字节进行检查
//返回 true表示对命令检测完毕。false 表示命令检测没有通过，需要继续。
bool CompileData(BYTE src)
{
		
	//检查是否接收到命令起始标识
	if(src==126)//7e
	{
		IniRXDValue();
		return false;
	}
		
	//检查是否接收到转译码
	if(src==127)//7f
	{
		mRXDTranslate=true;
		return false;
	}
		
	if(mRXDTranslate)
	{	//检查转译码是否正确
		switch (src)
		{
			case 1:
				src=126;//7f 01=7e
				break;
			case 2:
				src=127;//7f 02=7f
				break;
			default:
				IniRXDValue();
				return false;
		}
		mRXDTranslate=false;
	}
	//开始按格式进行计算
	switch (mRXDStep)
	{
		case 0://信息代码
			if(mRXDDataIndex!=4) //未收到4个字节，继续接收
			{
				AddRxData(src);
					
				if(mRXDDataIndex==4)
				{
					UINT lData=BytesTolong(mRXDbuf,4,true);

					SetSource(&mRxFrame,lData);	//保存
					mRXDDataIndex=0;
					mRXDStep++;//进行到下一步
				}
			}
			else
				mRXDDataIndex=0;//溢出过边界
			return false;
		case 1://SN
			if(mRXDDataIndex!=16) //未收到16个字节，继续接收
			{
				AddRxData(src);
					
				if(mRXDDataIndex==16)
				{
					SetSN(&mRxFrame,(char*)mRXDbuf);	//保存
					mRXDDataIndex=0;
					mRXDStep++;//进行到下一步
				}
			}
			else
				mRXDDataIndex=0;//溢出过边界
					
			return false;
		case 2://通讯密码
			if(mRXDDataIndex!=4) //未收到4个字节，继续接收
			{
				AddRxData(src);
					
				if(mRXDDataIndex==4)
				{

					SetPassword(&mRxFrame,mRXDbuf);	//保存		
					mRXDDataIndex=0;
					mRXDStep++;//进行到下一步
				}
			}
			else
				mRXDDataIndex=0;//溢出过边界
				
			return false;

		case 3://命令类型
			SetCmdType(&mRxFrame,src);	//保存
			mRXDStep++;//进行到下一步
			return false;
		case 4://命令索引
			SetCmdIndex(&mRxFrame,src);	//保存
			mRXDStep++;//进行到下一步
			return false;
		case 5://命令参数
			SetCmdPar(&mRxFrame,src);	//保存
			mRXDStep++;//进行到下一步
			return false;
		case 6://数据长度
			if(mRXDDataIndex!=4) //未收到4个字节，继续接收
			{
				AddRxData(src);
					
				if(mRXDDataIndex==4)
				{
					UINT lData=BytesTolong(mRXDbuf,4,true);
					SetDataLen(&mRxFrame,lData);	//保存		
					mRXDDataIndex=0;
					mRXDStep++;//进行到下一步
						
					if( lData != 0 )
					{
						SetDatabuffSize(&mRxFrame,lData);
					}
					else
					{
						//跳过存储数据步骤
						mRXDStep++;
					}
				}
					
				return false;
			}
			else
				mRXDDataIndex=0;//溢出过边界
				
			return false;
				
		case 7://命令数据
			if(mRXDDataIndex!=mRxFrame.DataLen) //未收到指定的字节，继续接收
			{
				SetDataValue(&mRxFrame,mRXDDataIndex++,src);//保存		
					
				if(mRXDDataIndex==mRxFrame.DataLen)
				{	
					mRXDDataIndex=0;
					mRXDStep++;//进行到下一步
				}
			}
			else
				mRXDDataIndex=0;//溢出过边界
				
			return false;
		case 8://计算检验和
			mRXDStep++;//进行到下一步
				
			Create(&mRxFrame);
				
			if (mRxFrame.CheckData == src)
			{
				return true;//检验和通过
			}
			else
				return false;
		default:
			IniRXDValue();
			return false;
	}
}

