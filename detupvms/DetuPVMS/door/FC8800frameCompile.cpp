#include "FC8800frame.h"
#include "FC8800frameCompile.h"
#include <string.h>

int mRXDStep=0;//�������ݵĲ���
BYTE mRXDbuf[16];//���յ���ʮ��������ֵ
bool mRXDTranslate=false;//���յ�ת����
int mRXDDataIndex=0;//���յ���������
FC8800frame mRxFrame;


//���ؽ�����ϵ�����ṹ
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


//����������������
void AddRxData(BYTE src)
{
	if(mRXDDataIndex==0)//��һ���յ����ݣ���ʼ������
		memset(mRXDbuf, 0, 16);;
	
	mRXDbuf[mRXDDataIndex++]=src;
}


//��ÿ���ֽڽ��м��
//���� true��ʾ����������ϡ�false ��ʾ������û��ͨ������Ҫ������
bool CompileData(BYTE src)
{
		
	//����Ƿ���յ�������ʼ��ʶ
	if(src==126)//7e
	{
		IniRXDValue();
		return false;
	}
		
	//����Ƿ���յ�ת����
	if(src==127)//7f
	{
		mRXDTranslate=true;
		return false;
	}
		
	if(mRXDTranslate)
	{	//���ת�����Ƿ���ȷ
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
	//��ʼ����ʽ���м���
	switch (mRXDStep)
	{
		case 0://��Ϣ����
			if(mRXDDataIndex!=4) //δ�յ�4���ֽڣ���������
			{
				AddRxData(src);
					
				if(mRXDDataIndex==4)
				{
					UINT lData=BytesTolong(mRXDbuf,4,true);

					SetSource(&mRxFrame,lData);	//����
					mRXDDataIndex=0;
					mRXDStep++;//���е���һ��
				}
			}
			else
				mRXDDataIndex=0;//������߽�
			return false;
		case 1://SN
			if(mRXDDataIndex!=16) //δ�յ�16���ֽڣ���������
			{
				AddRxData(src);
					
				if(mRXDDataIndex==16)
				{
					SetSN(&mRxFrame,(char*)mRXDbuf);	//����
					mRXDDataIndex=0;
					mRXDStep++;//���е���һ��
				}
			}
			else
				mRXDDataIndex=0;//������߽�
					
			return false;
		case 2://ͨѶ����
			if(mRXDDataIndex!=4) //δ�յ�4���ֽڣ���������
			{
				AddRxData(src);
					
				if(mRXDDataIndex==4)
				{

					SetPassword(&mRxFrame,mRXDbuf);	//����		
					mRXDDataIndex=0;
					mRXDStep++;//���е���һ��
				}
			}
			else
				mRXDDataIndex=0;//������߽�
				
			return false;

		case 3://��������
			SetCmdType(&mRxFrame,src);	//����
			mRXDStep++;//���е���һ��
			return false;
		case 4://��������
			SetCmdIndex(&mRxFrame,src);	//����
			mRXDStep++;//���е���һ��
			return false;
		case 5://�������
			SetCmdPar(&mRxFrame,src);	//����
			mRXDStep++;//���е���һ��
			return false;
		case 6://���ݳ���
			if(mRXDDataIndex!=4) //δ�յ�4���ֽڣ���������
			{
				AddRxData(src);
					
				if(mRXDDataIndex==4)
				{
					UINT lData=BytesTolong(mRXDbuf,4,true);
					SetDataLen(&mRxFrame,lData);	//����		
					mRXDDataIndex=0;
					mRXDStep++;//���е���һ��
						
					if( lData != 0 )
					{
						SetDatabuffSize(&mRxFrame,lData);
					}
					else
					{
						//�����洢���ݲ���
						mRXDStep++;
					}
				}
					
				return false;
			}
			else
				mRXDDataIndex=0;//������߽�
				
			return false;
				
		case 7://��������
			if(mRXDDataIndex!=mRxFrame.DataLen) //δ�յ�ָ�����ֽڣ���������
			{
				SetDataValue(&mRxFrame,mRXDDataIndex++,src);//����		
					
				if(mRXDDataIndex==mRxFrame.DataLen)
				{	
					mRXDDataIndex=0;
					mRXDStep++;//���е���һ��
				}
			}
			else
				mRXDDataIndex=0;//������߽�
				
			return false;
		case 8://��������
			mRXDStep++;//���е���һ��
				
			Create(&mRxFrame);
				
			if (mRxFrame.CheckData == src)
			{
				return true;//�����ͨ��
			}
			else
				return false;
		default:
			IniRXDValue();
			return false;
	}
}

