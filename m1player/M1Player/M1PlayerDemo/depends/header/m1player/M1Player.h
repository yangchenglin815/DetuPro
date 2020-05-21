#ifndef _M1_PLAYER_H_
#define _M1_PLAYER_H_

#include "Error.h"
#include "Global.h"

class CM1PlayerImp;

class CM1Player
{
public:
	CM1Player();
	~CM1Player();

public:
	/**
	* ��ʼ��M1������
	* @return: �ɹ�����0��ʧ�ܷ��ض�Ӧ�Ĵ�����,���������Error.h
	*/
	int Init(m1_player_config_s &config);
	/**
	* ��ʼ����
	* @return: �ɹ�����0��ʧ�ܷ��ض�Ӧ�Ĵ�����,���������Error.h
	*/
	int Play(void);
	/**
	* ��������������
	*/
	int RePlay(void);
	/**
	* ֹͣM1���������ͷ���Դ
	* @return���ɹ�����0��ʧ�ܷ���-1
	*/
	int Close(void);

public:
	/**
	* ���ÿͻ��˵����������ͣ����ö������stream_type_e
	* Ĭ��ΪRTMP��
	*/
	void SetStreamType(stream_type_e stream_type);
	/**
	* ����Ӳ���뷽ʽ�����ö������hw_decode_type_e
	* Ĭ��cuda
	*/
	void SetDeocdeType(decode_type_e deocde_type);
	/**
	* ����֡����Ƶ��
	* Ĭ��30֡ÿ��
	*/
	void SetDisplayFps(int fps);
	/**
	* ���ñ���¼���־λ
	* Ĭ�ϲ�����
	*/
	void SetRecordTag(bool is_record);
	/**
	* ���ñ���¼�񱣴�λ��
	*/
	void SetRecordPath(char* path);
	/**
	* ������ʾ��־λ
	* Ĭ����ʾͼ��
	*/
	void SetDisplayTag(bool is_display);
	/**
	* ������Ϣ�ص������id
	*/
	void SetOnwer(long owner_id);

private:
	CM1PlayerImp*	m_player_imp;
};

#endif
