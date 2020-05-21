#include "Tool.h"

struct FC8800frame 
{
	BYTE *Frame;//������������
	UINT Framesize;//�����������鳤��;

	char *SN;//Ŀ��SN
	BYTE *Password;//ͨѶ����
	UINT Source;//��Ϣ��ʾ
	BYTE CmdType ;//��������
	BYTE CmdIndex;//��������
	BYTE CmdPar;//�������
	UINT DataLen;//���ݳ���
	BYTE *CmdData; //��������
	BYTE CheckData ; //�����
};

//��ʼ������ṹ
void IniFrame(FC8800frame *frame);

//��ȡһ���µ�����ṹ
struct FC8800frame GetNewFrame();

//����һ������ṹ
void freeFrame(FC8800frame *frame);

//����һ������ṹ
struct FC8800frame CreateFrame(char *sSN,BYTE *sPwd,UINT lSource,BYTE iCmdType,BYTE iCmdIndex,BYTE iCmdPar,UINT iDataLen,BYTE *Databuf,UINT iDataSize);

//SN
void SetSN(FC8800frame *frame,char *sData);
char* GetSN(FC8800frame *frame);


//ͨѶ����
void SetPassword(FC8800frame *frame,BYTE *sData);
BYTE* GetPassword(FC8800frame *frame);

//��Ϣ��ʾ
void SetSource(FC8800frame *frame,UINT lData);
UINT GetSource(FC8800frame *frame);


//��������
void SetCmdType(FC8800frame *frame,BYTE iData);
BYTE GetCmdType(FC8800frame *frame);
	
//��������
void SetCmdIndex(FC8800frame *frame,BYTE iData);
BYTE GetCmdIndex(FC8800frame *frame);
	
//��������
void SetCmdPar(FC8800frame *frame,BYTE iData);
BYTE GetCmdPar(FC8800frame *frame);
	
//���ݳ���
void SetDataLen(FC8800frame *frame,UINT iData);
UINT GetDataLen(FC8800frame *frame);

//��������
void SetDatabuff(FC8800frame *frame,BYTE *iData,BYTE isize);
BYTE* GetDatabuff(FC8800frame *frame);


//���ؼ����
BYTE GetCheckData(FC8800frame *frame);

//�����������ݳ���
void SetDatabuffSize(FC8800frame *frame,int size);

//����������������
void SetDataValue(FC8800frame *frame,int lIndex,BYTE bValue);

//����ԭʼ���ݰ�
BYTE* GetFrame(FC8800frame *frame);

//����ԭʼ���ݰ�����
UINT GetFrameSize(FC8800frame *frame);

//����һ��ȡֵ��Χ��0xfeff-0x1000 ֮�����ֵ
UINT GetRndNum();

//�������ݰ���������У���
bool Create(FC8800frame *frame);
//�������е���Ҫת������ݽ��д��� 7E = 7F 01; 7F=7F 02
BYTE* TranslateCommandFrame(BYTE* buf,UINT bufsize,int *returnsize);


