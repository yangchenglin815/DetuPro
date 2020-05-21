#include "FC8800frame.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>


int const MAX_DATA_COUNT = 340; //数据命令最大值


//初始化命令结构
void IniFrame(FC8800frame *frame)
{
	//完整命令数组
	frame->Frame=NULL;

	//完整命令数组长度;
	frame->Framesize=0;

	frame->SN=NULL;//目标SN
	frame->Password=NULL;//通讯密码
	frame->Source=0;//信息标示
	frame->CmdType=0 ;//命令类型
	frame->CmdIndex=0;//命令索引
	frame->CmdPar=0;//命令参数
	frame->DataLen=0;//数据长度
	frame->CmdData=NULL; //命令数据
	frame->CheckData=0; //检验和
}

//获取一个新的命令结构
struct FC8800frame GetNewFrame()
{
	FC8800frame frame;
	IniFrame(&frame);
	return frame;
}

//销毁一个命令结构
void freeFrame(FC8800frame *frame)
{	
	//完整命令数组
	if (frame->Frame != NULL)
	{	free(frame->Frame);
		frame->Frame=NULL;	}

	//目标SN
	if (frame->SN != NULL)
	{	free(frame->SN);
		frame->SN=NULL;	}

	//通讯密码
	if (frame->Password != NULL)
	{	free(frame->Password);
		frame->Password=NULL;	}

	//命令数据
	if (frame->CmdData != NULL)
	{	free(frame->CmdData);
		frame->CmdData=NULL;	}

	IniFrame(frame);
}



//创建一个命令结构
FC8800frame CreateFrame(char *sSN,BYTE *sPwd,UINT lSource,BYTE iCmdType,BYTE iCmdIndex,BYTE iCmdPar,UINT iDataLen,BYTE *Databuf,UINT iDataSize)
{
	FC8800frame frame=GetNewFrame();

	SetSN(&frame,sSN);
	SetPassword(&frame,sPwd);
	SetSource(&frame,lSource);
	SetCmdType(&frame,iCmdType);
	SetCmdIndex(&frame,iCmdIndex);
	SetCmdPar(&frame,iCmdPar);
	SetDataLen(&frame,iDataLen);
	if (iDataLen>0)
		SetDatabuff(&frame,Databuf,iDataSize);
	//开始生成命令帧
	Create(&frame);

	return frame;
}



//设置SN
void SetSN(FC8800frame *frame,char *sData)
{
	if(frame->SN!=0)
	{
		free(frame->SN);
	}
	frame->SN =(char*)NewArray(16);
	memcpy(frame->SN,sData,16);
}
//获取SN
char* GetSN(FC8800frame *frame)
{
	return frame->SN;
}

//通讯密码
void SetPassword(FC8800frame *frame,BYTE *sData)
{
	if(frame->Password!=0)
	{
		free(frame->Password);
	}
	frame->Password  =NewArray(4);
	memcpy(frame->Password,sData,4);
}
BYTE* GetPassword(FC8800frame *frame){return frame->Password;}

//信息标示
void SetSource(FC8800frame *frame,UINT lData){frame->Source  = lData;}
UINT GetSource(FC8800frame *frame){return frame->Source;}

//命令类型
void SetCmdType(FC8800frame *frame,BYTE iData){frame->CmdType =iData;}
BYTE GetCmdType(FC8800frame *frame){return frame->CmdType;}
	
//命令索引
void SetCmdIndex(FC8800frame *frame,BYTE iData){frame->CmdIndex =iData;}
BYTE GetCmdIndex(FC8800frame *frame){return frame->CmdIndex;}
	
//命令索引
void SetCmdPar(FC8800frame *frame,BYTE iData){frame->CmdPar = iData;}
BYTE GetCmdPar(FC8800frame *frame){return frame->CmdPar;}
	
//数据长度
void SetDataLen(FC8800frame *frame,UINT iData){frame->DataLen = iData;}
UINT GetDataLen(FC8800frame *frame){return frame->DataLen;}

//命令数据
void SetDatabuff(FC8800frame *frame,BYTE *iData,BYTE isize)
{
	if(frame->CmdData!=0)
	{
		free(frame->CmdData);
	}

	frame->CmdData =NewArray(frame->DataLen);

	if(isize > frame->DataLen){isize=frame->DataLen;}

	memcpy(frame->CmdData,iData,isize);
}
BYTE* GetDatabuff(FC8800frame *frame)
{
	return frame->CmdData ;
}
	
//返回检验和
BYTE GetCheckData(FC8800frame *frame){return frame->CheckData;}

//设置命令数据长度
void SetDatabuffSize(FC8800frame *frame,int size)
{
	if(frame->CmdData!=0)
	{
		free(frame->CmdData);
	}

	frame->CmdData = NewArray(size);
}

//设置命令数据内容
void SetDataValue(FC8800frame *frame,int lIndex,BYTE bValue){frame->CmdData[lIndex]=bValue;}

//返回原始数据包
BYTE* GetFrame(FC8800frame *frame){return frame->Frame;}

//返回原始数据包长度
UINT GetFrameSize(FC8800frame *frame){return frame->Framesize;};



//返回一个取值范围在0xfeff-0x1000 之间的数值
UINT GetRndNum()
{
	UINT MAX=1895825407,MIN=34952;
	srand( (UINT)time(NULL) );
	UINT value = rand() % (MAX + 1 - MIN) + MIN;
	return value;
}



//创建数据包，并计算校验和
bool Create(FC8800frame *frame)
{
	BYTE *buf,*bData;
	UINT iBufLen=0,iBegin=0;
	UINT i;
	//计算数据包长度
	iBufLen = 16 //设备SN
				+ 4 //密码
				+ 4 //信息代码
				+ 1 //分类
				+ 1 //索引
				+ 1 //参数
				+ 4 //数据长度a
				+ frame->DataLen //数据内容
				+ 1 //检验和
				+ 2;//标志
	//创建缓冲
	buf=NewArray(iBufLen);
	memset(buf, 0,iBufLen);
	

	//先设置起始和结束标识
	buf[0]=126;//7E
	buf[iBufLen-1]=126;//7E

	char *hex = Byte2Hex(buf,iBufLen);

	//SN
	iBegin=1;
	memcpy(&buf[iBegin],frame->SN,16);

	//通讯密码
	iBegin+=16;
	memcpy(&buf[iBegin],frame->Password,4);
	
	//填充信息代码
	iBegin+=4;
	bData = longToBytes(frame->Source,4,true);
	memcpy(&buf[iBegin],bData,4);
	free(bData);
		
	//命令类型
	iBegin+=4;
	buf[iBegin++]=frame->CmdType;
	//命令索引
	buf[iBegin++]=frame->CmdIndex;
	//命令参数
	buf[iBegin++]=frame->CmdPar;
		
	//数据长度
	bData =  longToBytes(frame->DataLen,4,true);
	memcpy(&buf[iBegin],bData,4);
	free(bData);

	//命令数据
	iBegin+=4;
	if(frame->DataLen>0)
		for(i=0;i<frame->DataLen;i++)
			buf[iBegin++]=frame->CmdData[i];
	//计算检验和
	unsigned long lCheck;
	lCheck=0;
	for(i=1;i<iBufLen-2;i++)
		lCheck+=buf[i];//取字节的无符号整形数值
	//检验和
	frame->CheckData=lCheck % 256;
	buf[iBegin]=frame->CheckData;
	
	//进行转译码处理并保存数据

	int iframesize=0;
	frame->Frame = TranslateCommandFrame(buf,iBegin+1,&iframesize);
	frame->Framesize=iframesize;

	free(buf);buf=NULL;
	
	return true;
}
	




BYTE* TranslateCommandFrame(BYTE* buf,UINT bufsize,int *returnsize)
{//对命令中的需要转译的数据进行处理 7E = 7F 01; 7F=7F 02;
	BYTE *iData;
	UINT iIndex=1,i,iValue;
	//开始命令转译
	iData = NewArray(bufsize*2);
	iData[0] = buf[0];
		
	for(i = 1 ;i<bufsize;i++)
	{	
		iValue=buf[i];//取字节的无符号整形数值
		switch (iValue)
		{
			case 126://7E = 7F 01
				iData[iIndex++] = 127;
				iData[iIndex++] = 1;
				break;
			case 127://7F = 7F 02
				iData[iIndex++] = 127;
				iData[iIndex++] = 2;
				break;
			default:
				iData[iIndex++] = buf[i];
		}
	}
	iData[iIndex++] = buf[i];

	//free(buf);

	BYTE *ret = NewArray(iIndex);
	memcpy(ret,iData,iIndex);
	
	free(iData);
	
	*returnsize=iIndex;

	return ret;
}

