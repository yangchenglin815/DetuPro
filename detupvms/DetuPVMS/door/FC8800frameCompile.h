extern int mRXDStep;//�������ݵĲ���
extern BYTE mRXDbuf[16];//���յ���ʮ��������ֵ
extern bool mRXDTranslate;//���յ�ת����
extern int mRXDDataIndex;//���յ���������
extern FC8800frame mRxFrame;//���յ��������

void IniRXDValue();

//����������������
void AddRxData(BYTE src);

//���ؽ�����ϵ�����ṹ
FC8800frame GetRxFrame();

//��ÿ���ֽڽ��м��
//���� true��ʾ����������ϡ�false ��ʾ������û��ͨ������Ҫ������
bool CompileData(BYTE src);