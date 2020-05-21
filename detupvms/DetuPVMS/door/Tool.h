typedef unsigned char   BYTE;
typedef unsigned int    UINT;


//转换字节数组为数值
UINT BytesTolong(BYTE* src,int isize,bool byteOrder);

//转换long数值为字节数组
BYTE* longToBytes(UINT src,int lsize,bool byteOrder);


//转换1字节为8个bit数组，
BYTE* BytetoBits(BYTE src,bool byteOrder);

//转换8个bit数组为一个字节(Byte)
BYTE BitstoByte(BYTE *srcBits,int isize,bool byteOrder);
/*
//功能:Byte 到 Bits 的转换,
//参数:待变换数据,处理后结果存放缓冲区指针,Bits缓冲区大小
void BytestoBits(BYTE* srcBytes, BYTE* dstBits, int sizeBits);
void BytestoBits(BYTE* srcBytes, BYTE* dstBits, int sizeBits,bool byteOrder);


//功能:Bits 到 Byte 的转换,
//参数:存储转换后的Byte数组,准备转换为byte的bit数组,Bits缓冲区大小
void BitsToBytes(BYTE* dstBytes,BYTE* srcBits, int sizeBits);
void BitsToBytes(BYTE* dstBytes, BYTE* srcBits, int sizeBits,bool byteOrder);
*/
//功能:Byte到Hex的转换
//参数:需要转换的字节数组，转换的长度
char* Byte2Hex(BYTE* b,int iSize);

//Hex到Byte的转换
BYTE* Hex2Byte(char* hexString,int iSize,int *returnsize);

//从数组中拷贝出其中一段
char* copyOfRange(char* src,int srcsize,int iIndex,int iSize);

//显示字节数组中的内容
char* BytesToString(BYTE* bBytes,int isize,int *returnsize);

//申请指定长度的一个字节数组，不使用时需要用【FreeArray】销毁。
BYTE* NewArray(int isize);

//销毁有【NewArray】函数申请的，不使用的数组。
void FreeArray(void* array);

