#include "Tool.h"
#include <string.h>
#include <stdio.h>
#include <malloc.h>




//转换字节数组为数值
UINT BytesTolong(BYTE* src,int isize,bool byteOrder)
{	//转换字节数组为数值，
     //src--需要转换的字节数组
	 //byteOrder -- 数组字节顺序：
	 //		true  表示：高位在前，低位在后。
	 //		false 表示：低位在前，高位在后。
		int iIndex=0;
		long lValue=0;
		int MAX=4;
		BYTE* tmp;

		if(byteOrder)
		{	
			//只取4个字节,后4个
			if(isize>MAX)
				tmp=(BYTE*)copyOfRange((char*)src,isize,isize-MAX,isize);
			else
			{
				//不足8字节，创建一个8字节的数组，并把源数组内容拷贝只新数组后8字节。
				tmp=NewArray(MAX);
				memcpy(&tmp[MAX-isize],src,isize);
			}
				
			iIndex=0;//高位在前，低位在后。
		}
		else
		{
			//只取MAX个字节,前MAX个
			tmp=NewArray(MAX);
			memcpy(tmp,src,isize);
			iIndex=MAX-1;//低位在前，高位在后。
		}
		
		for(int i=0; i < MAX; i++)
		{
			
			lValue += tmp[iIndex]; //取字节的无符号整形数值
			if(i<MAX-1)
				lValue =lValue<<8;//移位
			
			if(byteOrder)
				iIndex+=1;
			else
				iIndex-=1;
		}
		free(tmp);

		return lValue;
}


//转换long数值为字节数组
BYTE* longToBytes(UINT src,int lsize,bool byteOrder)
{    //src--需要转换的数值
	//size -- 需要返回的数组元素数
	//BYTEOrder -- 数组字节顺序：
	//		true  表示：高位在前，低位在后。
	//		false 表示：低位在前，高位在后。
	BYTE * buf=NewArray(8);
	int iIndex=0,i=0;
	int MAX=4;
	if(byteOrder)
		iIndex=24;//高位在前，低位在后。
	else
		iIndex=0;//低位在前，高位在后。
		
	for( i=0; i < MAX; i++)
	{
		buf[i] = (BYTE)(src>>iIndex);
			
		if(byteOrder)
			iIndex-=8;
		else
			iIndex+=8;
	}
	
	BYTE * tmp=NewArray(lsize);

	//返回数组
	if(byteOrder)
	{
		if(lsize>MAX)
		{
			//需要返回的数组大于4字节，则创建一个指定维数的数组，并拷贝数据至新数组后4字节。
			
			memcpy(&tmp[lsize-MAX],buf,MAX);
			
		}
		else
		{
			memcpy(tmp,&buf[MAX-lsize],lsize); //高位在前，低位在后。从数组后面往前截取
		}
	}
	else
	{
		//低位在前，高位在后。
		memcpy(tmp,buf,lsize);
	}

	free(buf);
	return  tmp;//返回数组
}

//转换1字节为8个bit数组，
BYTE* BytetoBits(BYTE src,bool byteOrder)
{	//转换字节为8个bit数组，
	  //src--需要转换的字节 
	  //byteOrder -- 数组字节顺序： 
	  //		true  表示：高位在前，低位在后。 
	  //		false 表示：低位在前，高位在后。 
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

//转换8个bit数组为一个字节(Byte)
BYTE BitstoByte(BYTE *srcBits,int isize, bool byteOrder)
{//转换8个bit数组为一个字节(Byte)
	//srcBits--需要转换的字节 
	//byteOrder -- 数组字节顺序： 
	//		true  表示：高位在前，低位在后。 
	//		false 表示：低位在前，高位在后。 
	int i=0,iIndex=0;
	BYTE dst=0;
	BYTE* tmp;

	//初始化数组
	if(byteOrder)
	{	
		//只取8个字节,后8个
		if(isize>8)
			tmp=(BYTE*)copyOfRange((char*)srcBits,isize,isize-8,isize);
		else
		{
			//不足8字节，创建一个8字节的数组，并把源数组内容拷贝只新数组后8字节。
			tmp=NewArray(8);
			memcpy(&tmp[8-isize],srcBits,isize);
		}
				
		iIndex=0;//高位在前，低位在后。
	}
	else
	{
		//只取8个字节,前8个
		tmp=NewArray(8);
		memcpy(tmp,srcBits,isize);
		iIndex=7;//低位在前，高位在后。
	}
		
		
	//开始抓换
	for(i=0; i < 8; i++)
	{	
		dst += tmp[iIndex];
		if(i<7)
			dst =dst << 1;//移位
			
		if(byteOrder)
			iIndex++;
		else
			iIndex--;
	}
	free( tmp );
	return dst;
}

//功能:Byte到Hex的转换
//参数:需要转换的字节数组，转换的长度
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
			iData= b[i];//取字节的无符号整形数值
				
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

//Hex到Byte的转换
BYTE* Hex2Byte(char* hexString,int iSize,int *returnsize)
{
	int i,iIndex=0,iData;
	
	
	//生成转换值列表
	BYTE * digits =NewArray(128);
	BYTE * tmp;
	tmp  = (BYTE*)"0123456789abcdef";

	for(i=0;i<16;i++)
		digits[tmp[i]]=i;
	tmp  = (BYTE*)"ABCDEF";
	for(i=0;i<6;i++)
		digits[tmp[i]]=i+10;
	
	

	BYTE* sbuf;
	//确定字符串长度必须是2的倍数
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
	//生成缓存
	BYTE* buf=NewArray(iSize / 2);

	//开始转换
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

//从数组中拷贝出其中一段
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

//显示字节数组中的内容
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

//申请指定长度的一个字节数组，不使用时需要用【FreeArray】销毁。
BYTE* NewArray(int isize){	return (BYTE*)calloc(isize+1,1);};

//销毁有【NewArray】函数申请的，不使用的数组。
void FreeArray(void* array)
{
	//free(array);
	array=NULL;
};
