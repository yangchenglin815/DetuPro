#include "Tool.h"
#include <string.h>
#include <stdio.h>
#include <malloc.h>




//ת���ֽ�����Ϊ��ֵ
UINT BytesTolong(BYTE* src,int isize,bool byteOrder)
{	//ת���ֽ�����Ϊ��ֵ��
     //src--��Ҫת�����ֽ�����
	 //byteOrder -- �����ֽ�˳��
	 //		true  ��ʾ����λ��ǰ����λ�ں�
	 //		false ��ʾ����λ��ǰ����λ�ں�
		int iIndex=0;
		long lValue=0;
		int MAX=4;
		BYTE* tmp;

		if(byteOrder)
		{	
			//ֻȡ4���ֽ�,��4��
			if(isize>MAX)
				tmp=(BYTE*)copyOfRange((char*)src,isize,isize-MAX,isize);
			else
			{
				//����8�ֽڣ�����һ��8�ֽڵ����飬����Դ�������ݿ���ֻ�������8�ֽڡ�
				tmp=NewArray(MAX);
				memcpy(&tmp[MAX-isize],src,isize);
			}
				
			iIndex=0;//��λ��ǰ����λ�ں�
		}
		else
		{
			//ֻȡMAX���ֽ�,ǰMAX��
			tmp=NewArray(MAX);
			memcpy(tmp,src,isize);
			iIndex=MAX-1;//��λ��ǰ����λ�ں�
		}
		
		for(int i=0; i < MAX; i++)
		{
			
			lValue += tmp[iIndex]; //ȡ�ֽڵ��޷���������ֵ
			if(i<MAX-1)
				lValue =lValue<<8;//��λ
			
			if(byteOrder)
				iIndex+=1;
			else
				iIndex-=1;
		}
		free(tmp);

		return lValue;
}


//ת��long��ֵΪ�ֽ�����
BYTE* longToBytes(UINT src,int lsize,bool byteOrder)
{    //src--��Ҫת������ֵ
	//size -- ��Ҫ���ص�����Ԫ����
	//BYTEOrder -- �����ֽ�˳��
	//		true  ��ʾ����λ��ǰ����λ�ں�
	//		false ��ʾ����λ��ǰ����λ�ں�
	BYTE * buf=NewArray(8);
	int iIndex=0,i=0;
	int MAX=4;
	if(byteOrder)
		iIndex=24;//��λ��ǰ����λ�ں�
	else
		iIndex=0;//��λ��ǰ����λ�ں�
		
	for( i=0; i < MAX; i++)
	{
		buf[i] = (BYTE)(src>>iIndex);
			
		if(byteOrder)
			iIndex-=8;
		else
			iIndex+=8;
	}
	
	BYTE * tmp=NewArray(lsize);

	//��������
	if(byteOrder)
	{
		if(lsize>MAX)
		{
			//��Ҫ���ص��������4�ֽڣ��򴴽�һ��ָ��ά�������飬�������������������4�ֽڡ�
			
			memcpy(&tmp[lsize-MAX],buf,MAX);
			
		}
		else
		{
			memcpy(tmp,&buf[MAX-lsize],lsize); //��λ��ǰ����λ�ں󡣴����������ǰ��ȡ
		}
	}
	else
	{
		//��λ��ǰ����λ�ں�
		memcpy(tmp,buf,lsize);
	}

	free(buf);
	return  tmp;//��������
}

//ת��1�ֽ�Ϊ8��bit���飬
BYTE* BytetoBits(BYTE src,bool byteOrder)
{	//ת���ֽ�Ϊ8��bit���飬
	  //src--��Ҫת�����ֽ� 
	  //byteOrder -- �����ֽ�˳�� 
	  //		true  ��ʾ����λ��ǰ����λ�ں� 
	  //		false ��ʾ����λ��ǰ����λ�ں� 
	BYTE* dstBits=NewArray(8);
	for(int i=0; i < 8; i++)
	{
		if(byteOrder)
			dstBits[7-i] =src % 2;
		else
			dstBits[i] =src % 2;
				
		src=src/2;
	}
	return dstBits;
}

//ת��8��bit����Ϊһ���ֽ�(Byte)
BYTE BitstoByte(BYTE *srcBits,int isize, bool byteOrder)
{//ת��8��bit����Ϊһ���ֽ�(Byte)
	//srcBits--��Ҫת�����ֽ� 
	//byteOrder -- �����ֽ�˳�� 
	//		true  ��ʾ����λ��ǰ����λ�ں� 
	//		false ��ʾ����λ��ǰ����λ�ں� 
	int i=0,iIndex=0;
	BYTE dst=0;
	BYTE* tmp;

	//��ʼ������
	if(byteOrder)
	{	
		//ֻȡ8���ֽ�,��8��
		if(isize>8)
			tmp=(BYTE*)copyOfRange((char*)srcBits,isize,isize-8,isize);
		else
		{
			//����8�ֽڣ�����һ��8�ֽڵ����飬����Դ�������ݿ���ֻ�������8�ֽڡ�
			tmp=NewArray(8);
			memcpy(&tmp[8-isize],srcBits,isize);
		}
				
		iIndex=0;//��λ��ǰ����λ�ں�
	}
	else
	{
		//ֻȡ8���ֽ�,ǰ8��
		tmp=NewArray(8);
		memcpy(tmp,srcBits,isize);
		iIndex=7;//��λ��ǰ����λ�ں�
	}
		
		
	//��ʼץ��
	for(i=0; i < 8; i++)
	{	
		dst += tmp[iIndex];
		if(i<7)
			dst =dst << 1;//��λ
			
		if(byteOrder)
			iIndex++;
		else
			iIndex--;
	}
	free( tmp );
	return dst;
}

//����:Byte��Hex��ת��
//����:��Ҫת�����ֽ����飬ת���ĳ���
char* Byte2Hex(BYTE* b,int iSize)
{
	char* sHexbuf=(char*)NewArray(iSize * 2+1);
	int lIndex=0;
	int iData;
		
	char* digits = (char*)"0123456789ABCDEF";
	try
	{
		for(int i=0;i<iSize;i++)
		{
			iData= b[i];//ȡ�ֽڵ��޷���������ֵ
				
			sHexbuf[lIndex++] = digits[iData / 16];
			sHexbuf[lIndex++] = digits[iData % 16];
		}
		sHexbuf[lIndex++]='\0';

		return sHexbuf;
	}
	catch(...)
	{
		return NULL;
	}
}

//Hex��Byte��ת��
BYTE* Hex2Byte(char* hexString,int iSize,int *returnsize)
{
	int i,iIndex=0,iData;
	
	
	//����ת��ֵ�б�
	BYTE * digits =NewArray(128);
	BYTE * tmp;
	tmp  = (BYTE*)"0123456789abcdef";

	for(i=0;i<16;i++)
		digits[tmp[i]]=i;
	tmp  = (BYTE*)"ABCDEF";
	for(i=0;i<6;i++)
		digits[tmp[i]]=i+10;
	
	

	BYTE* sbuf;
	//ȷ���ַ������ȱ�����2�ı���
	if( (iSize % 2) ==1 )
	{
		sbuf=NewArray(iSize+1);
		iSize+=1;
		memcpy(&sbuf[1],hexString,iSize);
	}
	else
	{
		sbuf=NewArray(iSize);
		memcpy(sbuf,hexString,iSize);
	}
	//���ɻ���
	BYTE* buf=NewArray(iSize / 2);

	//��ʼת��
	for(i=0;i<iSize;i++)
	{
		iData=digits[sbuf[i++]]*16;
		iData=iData+digits[sbuf[i]];
			
		buf[iIndex]=iData;
		iIndex++;
	}

	*returnsize=iIndex;

	free( digits);
	free( sbuf) ;

	return buf;
}

//�������п���������һ��
char* copyOfRange(char* src,int srcsize,int iIndex,int iSize)
{
	char* tmp=(char*)NewArray(iSize);
	if (srcsize>=iSize )
	{
		memcpy(tmp,src,iSize);
	}
	else
	{
		memcpy(tmp,src,srcsize);
	}

	return tmp;
}

//��ʾ�ֽ������е�����
char* BytesToString( BYTE* bBytes,int isize,int *returnsize )
{
	char *str=(char*)NewArray(isize * 4);	
	int iIndex=0;
	char tmpvalue[10];
	int ivalue=0;
	for(int i=0;i<isize;i++)
	{
		ivalue=bBytes[i];

		memset(tmpvalue, 0, 10);
		sprintf_s(tmpvalue,"%d,",ivalue);

		for(int j=0;j<10;j++)
		{
			if (tmpvalue[j] ==0 )
				break;

			str[iIndex]=tmpvalue[j];
			iIndex++;

		}
	}

	char *tmp=(char*)NewArray(iIndex);
	*returnsize=iIndex-1;
	memcpy(tmp,str,iIndex-1);

	iIndex=strlen(tmp);
	iIndex=strlen(str);

	free(str);

	return tmp;
}

//����ָ�����ȵ�һ���ֽ����飬��ʹ��ʱ��Ҫ�á�FreeArray�����١�
BYTE* NewArray(int isize){	return (BYTE*)calloc(isize+1,1);};

//�����С�NewArray����������ģ���ʹ�õ����顣
void FreeArray(void* array)
{
	//free(array);
	array=NULL;
};
