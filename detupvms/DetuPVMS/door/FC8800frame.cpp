#include "FC8800frame.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>


int const MAX_DATA_COUNT = 340; //�����������ֵ


//��ʼ������ṹ
void IniFrame(FC8800frame *frame)
{
	//������������
	frame->Frame=NULL;

	//�����������鳤��;
	frame->Framesize=0;

	frame->SN=NULL;//Ŀ��SN
	frame->Password=NULL;//ͨѶ����
	frame->Source=0;//��Ϣ��ʾ
	frame->CmdType=0 ;//��������
	frame->CmdIndex=0;//��������
	frame->CmdPar=0;//�������
	frame->DataLen=0;//���ݳ���
	frame->CmdData=NULL; //��������
	frame->CheckData=0; //�����
}

//��ȡһ���µ�����ṹ
struct FC8800frame GetNewFrame()
{
	FC8800frame frame;
	IniFrame(&frame);
	return frame;
}

//����һ������ṹ
void freeFrame(FC8800frame *frame)
{	
	//������������
	if (frame->Frame != NULL)
	{	free(frame->Frame);
		frame->Frame=NULL;	}

	//Ŀ��SN
	if (frame->SN != NULL)
	{	free(frame->SN);
		frame->SN=NULL;	}

	//ͨѶ����
	if (frame->Password != NULL)
	{	free(frame->Password);
		frame->Password=NULL;	}

	//��������
	if (frame->CmdData != NULL)
	{	free(frame->CmdData);
		frame->CmdData=NULL;	}

	IniFrame(frame);
}



//����һ������ṹ
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
	//��ʼ��������֡
	Create(&frame);

	return frame;
}



//����SN
void SetSN(FC8800frame *frame,char *sData)
{
	if(frame->SN!=0)
	{
		free(frame->SN);
	}
	frame->SN =(char*)NewArray(16);
	memcpy(frame->SN,sData,16);
}
//��ȡSN
char* GetSN(FC8800frame *frame)
{
	return frame->SN;
}

//ͨѶ����
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

//��Ϣ��ʾ
void SetSource(FC8800frame *frame,UINT lData){frame->Source  = lData;}
UINT GetSource(FC8800frame *frame){return frame->Source;}

//��������
void SetCmdType(FC8800frame *frame,BYTE iData){frame->CmdType =iData;}
BYTE GetCmdType(FC8800frame *frame){return frame->CmdType;}
	
//��������
void SetCmdIndex(FC8800frame *frame,BYTE iData){frame->CmdIndex =iData;}
BYTE GetCmdIndex(FC8800frame *frame){return frame->CmdIndex;}
	
//��������
void SetCmdPar(FC8800frame *frame,BYTE iData){frame->CmdPar = iData;}
BYTE GetCmdPar(FC8800frame *frame){return frame->CmdPar;}
	
//���ݳ���
void SetDataLen(FC8800frame *frame,UINT iData){frame->DataLen = iData;}
UINT GetDataLen(FC8800frame *frame){return frame->DataLen;}

//��������
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
	
//���ؼ����
BYTE GetCheckData(FC8800frame *frame){return frame->CheckData;}

//�����������ݳ���
void SetDatabuffSize(FC8800frame *frame,int size)
{
	if(frame->CmdData!=0)
	{
		free(frame->CmdData);
	}

	frame->CmdData = NewArray(size);
}

//����������������
void SetDataValue(FC8800frame *frame,int lIndex,BYTE bValue){frame->CmdData[lIndex]=bValue;}

//����ԭʼ���ݰ�
BYTE* GetFrame(FC8800frame *frame){return frame->Frame;}

//����ԭʼ���ݰ�����
UINT GetFrameSize(FC8800frame *frame){return frame->Framesize;};



//����һ��ȡֵ��Χ��0xfeff-0x1000 ֮�����ֵ
UINT GetRndNum()
{
	UINT MAX=1895825407,MIN=34952;
	srand( (UINT)time(NULL) );
	UINT value = rand() % (MAX + 1 - MIN) + MIN;
	return value;
}



//�������ݰ���������У���
bool Create(FC8800frame *frame)
{
	BYTE *buf,*bData;
	UINT iBufLen=0,iBegin=0;
	UINT i;
	//�������ݰ�����
	iBufLen = 16 //�豸SN
				+ 4 //����
				+ 4 //��Ϣ����
				+ 1 //����
				+ 1 //����
				+ 1 //����
				+ 4 //���ݳ���a
				+ frame->DataLen //��������
				+ 1 //�����
				+ 2;//��־
	//��������
	buf=NewArray(iBufLen);
	memset(buf, 0,iBufLen);
	

	//��������ʼ�ͽ�����ʶ
	buf[0]=126;//7E
	buf[iBufLen-1]=126;//7E

	char *hex = Byte2Hex(buf,iBufLen);

	//SN
	iBegin=1;
	memcpy(&buf[iBegin],frame->SN,16);

	//ͨѶ����
	iBegin+=16;
	memcpy(&buf[iBegin],frame->Password,4);
	
	//�����Ϣ����
	iBegin+=4;
	bData = longToBytes(frame->Source,4,true);
	memcpy(&buf[iBegin],bData,4);
	free(bData);
		
	//��������
	iBegin+=4;
	buf[iBegin++]=frame->CmdType;
	//��������
	buf[iBegin++]=frame->CmdIndex;
	//�������
	buf[iBegin++]=frame->CmdPar;
		
	//���ݳ���
	bData =  longToBytes(frame->DataLen,4,true);
	memcpy(&buf[iBegin],bData,4);
	free(bData);

	//��������
	iBegin+=4;
	if(frame->DataLen>0)
		for(i=0;i<frame->DataLen;i++)
			buf[iBegin++]=frame->CmdData[i];
	//��������
	unsigned long lCheck;
	lCheck=0;
	for(i=1;i<iBufLen-2;i++)
		lCheck+=buf[i];//ȡ�ֽڵ��޷���������ֵ
	//�����
	frame->CheckData=lCheck % 256;
	buf[iBegin]=frame->CheckData;
	
	//����ת���봦����������

	int iframesize=0;
	frame->Frame = TranslateCommandFrame(buf,iBegin+1,&iframesize);
	frame->Framesize=iframesize;

	free(buf);buf=NULL;
	
	return true;
}
	




BYTE* TranslateCommandFrame(BYTE* buf,UINT bufsize,int *returnsize)
{//�������е���Ҫת������ݽ��д��� 7E = 7F 01; 7F=7F 02;
	BYTE *iData;
	UINT iIndex=1,i,iValue;
	//��ʼ����ת��
	iData = NewArray(bufsize*2);
	iData[0] = buf[0];
		
	for(i = 1 ;i<bufsize;i++)
	{	
		iValue=buf[i];//ȡ�ֽڵ��޷���������ֵ
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

