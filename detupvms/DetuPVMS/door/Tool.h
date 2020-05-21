typedef unsigned char   BYTE;
typedef unsigned int    UINT;


//ת���ֽ�����Ϊ��ֵ
UINT BytesTolong(BYTE* src,int isize,bool byteOrder);

//ת��long��ֵΪ�ֽ�����
BYTE* longToBytes(UINT src,int lsize,bool byteOrder);


//ת��1�ֽ�Ϊ8��bit���飬
BYTE* BytetoBits(BYTE src,bool byteOrder);

//ת��8��bit����Ϊһ���ֽ�(Byte)
BYTE BitstoByte(BYTE *srcBits,int isize,bool byteOrder);
/*
//����:Byte �� Bits ��ת��,
//����:���任����,���������Ż�����ָ��,Bits��������С
void BytestoBits(BYTE* srcBytes, BYTE* dstBits, int sizeBits);
void BytestoBits(BYTE* srcBytes, BYTE* dstBits, int sizeBits,bool byteOrder);


//����:Bits �� Byte ��ת��,
//����:�洢ת�����Byte����,׼��ת��Ϊbyte��bit����,Bits��������С
void BitsToBytes(BYTE* dstBytes,BYTE* srcBits, int sizeBits);
void BitsToBytes(BYTE* dstBytes, BYTE* srcBits, int sizeBits,bool byteOrder);
*/
//����:Byte��Hex��ת��
//����:��Ҫת�����ֽ����飬ת���ĳ���
char* Byte2Hex(BYTE* b,int iSize);

//Hex��Byte��ת��
BYTE* Hex2Byte(char* hexString,int iSize,int *returnsize);

//�������п���������һ��
char* copyOfRange(char* src,int srcsize,int iIndex,int iSize);

//��ʾ�ֽ������е�����
char* BytesToString(BYTE* bBytes,int isize,int *returnsize);

//����ָ�����ȵ�һ���ֽ����飬��ʹ��ʱ��Ҫ�á�FreeArray�����١�
BYTE* NewArray(int isize);

//�����С�NewArray����������ģ���ʹ�õ����顣
void FreeArray(void* array);

