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
	* 初始化M1播放器
	* @return: 成功返回0，失败返回对应的错误码,错误码详见Error.h
	*/
	int Init(m1_player_config_s &config);
	/**
	* 开始播放
	* @return: 成功返回0，失败返回对应的错误码,错误码详见Error.h
	*/
	int Play(void);
	/**
	* 断流后，重新请求
	*/
	int RePlay(void);
	/**
	* 停止M1播放器，释放资源
	* @return：成功返回0，失败返回-1
	*/
	int Close(void);

public:
	/**
	* 设置客户端的网络流类型，详见枚举类型stream_type_e
	* 默认为RTMP流
	*/
	void SetStreamType(stream_type_e stream_type);
	/**
	* 设置硬解码方式，详见枚举类型hw_decode_type_e
	* 默认cuda
	*/
	void SetDeocdeType(decode_type_e deocde_type);
	/**
	* 设置帧播放频率
	* 默认30帧每秒
	*/
	void SetDisplayFps(int fps);
	/**
	* 设置本地录像标志位
	* 默认不保存
	*/
	void SetRecordTag(bool is_record);
	/**
	* 设置本地录像保存位置
	*/
	void SetRecordPath(char* path);
	/**
	* 设置显示标志位
	* 默认显示图像
	*/
	void SetDisplayTag(bool is_display);
	/**
	* 设置消息回调对象的id
	*/
	void SetOnwer(long owner_id);

private:
	CM1PlayerImp*	m_player_imp;
};

#endif
