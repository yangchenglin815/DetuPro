#include "Tool.h"

struct FC8800frame 
{
	BYTE *Frame;//完整命令数组
	UINT Framesize;//完整命令数组长度;

	char *SN;//目标SN
	BYTE *Password;//通讯密码
	UINT Source;//信息标示
	BYTE CmdType ;//命令类型
	BYTE CmdIndex;//命令索引
	BYTE CmdPar;//命令参数
	UINT DataLen;//数据长度
	BYTE *CmdData; //命令数据
	BYTE CheckData ; //检验和
};

//初始化命令结构
void IniFrame(FC8800frame *frame);

//获取一个新的命令结构
struct FC8800frame GetNewFrame();

//销毁一个命令结构
void freeFrame(FC8800frame *frame);

//创建一个命令结构
struct FC8800frame CreateFrame(char *sSN,BYTE *sPwd,UINT lSource,BYTE iCmdType,BYTE iCmdIndex,BYTE iCmdPar,UINT iDataLen,BYTE *Databuf,UINT iDataSize);

//SN
void SetSN(FC8800frame *frame,char *sData);
char* GetSN(FC8800frame *frame);


//通讯密码
void SetPassword(FC8800frame *frame,BYTE *sData);
BYTE* GetPassword(FC8800frame *frame);

//信息标示
void SetSource(FC8800frame *frame,UINT lData);
UINT GetSource(FC8800frame *frame);


//命令类型
void SetCmdType(FC8800frame *frame,BYTE iData);
BYTE GetCmdType(FC8800frame *frame);
	
//命令索引
void SetCmdIndex(FC8800frame *frame,BYTE iData);
BYTE GetCmdIndex(FC8800frame *frame);
	
//命令索引
void SetCmdPar(FC8800frame *frame,BYTE iData);
BYTE GetCmdPar(FC8800frame *frame);
	
//数据长度
void SetDataLen(FC8800frame *frame,UINT iData);
UINT GetDataLen(FC8800frame *frame);

//命令数据
void SetDatabuff(FC8800frame *frame,BYTE *iData,BYTE isize);
BYTE* GetDatabuff(FC8800frame *frame);


//返回检验和
BYTE GetCheckData(FC8800frame *frame);

//设置命令数据长度
void SetDatabuffSize(FC8800frame *frame,int size);

//设置命令数据内容
void SetDataValue(FC8800frame *frame,int lIndex,BYTE bValue);

//返回原始数据包
BYTE* GetFrame(FC8800frame *frame);

//返回原始数据包长度
UINT GetFrameSize(FC8800frame *frame);

//返回一个取值范围在0xfeff-0x1000 之间的数值
UINT GetRndNum();

//创建数据包，并计算校验和
bool Create(FC8800frame *frame);
//对命令中的需要转译的数据进行处理 7E = 7F 01; 7F=7F 02
BYTE* TranslateCommandFrame(BYTE* buf,UINT bufsize,int *returnsize);


