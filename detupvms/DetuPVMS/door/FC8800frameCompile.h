extern int mRXDStep;//接收数据的步骤
extern BYTE mRXDbuf[16];//接收到的十六进制数值
extern bool mRXDTranslate;//接收到转移码
extern int mRXDDataIndex;//接收到缓存索引
extern FC8800frame mRxFrame;//接收到的命令包

void IniRXDValue();

//加入数据至缓冲中
void AddRxData(BYTE src);

//返回解析完毕的命令结构
FC8800frame GetRxFrame();

//对每个字节进行检查
//返回 true表示对命令检测完毕。false 表示命令检测没有通过，需要继续。
bool CompileData(BYTE src);