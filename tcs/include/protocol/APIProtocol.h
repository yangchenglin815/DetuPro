#ifndef _TCS_PROTOCOL_API_H_
#define _TCS_PROTOCOL_API_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_ARRAY_LEN		(32)
#define API_RTMP_LEN		(64)
#define MAX_NVR_LIST_NUM	(50)
#define API_PTS_LEN			(32768)
#define MAX_DEVICE_NUM		(10)
#define API_URL_LENGTH		(512)


/********************************************
1）考虑可拓展性
2）网络转换时会变成unsigned
********************************************/

// 命令号
typedef enum
{
	CMD_REGISTER = 1,		// 注册
	CMD_REGISTER_RES = 2,	// 注册响应

	CMD_UNREGISTER = 3,		// 注销
	CMD_UNREGISTER_RES = 4,	// 注销响应

	CMD_HEART_BEAT = 5,		// 心跳
	CMD_HEART_BEAT_RES = 6,	// 心跳响应

	CMD_REQUEST_VIDEO = 7,			// 视频请求（包含实时、回放流）
	CMD_REQUEST_VIDEO_RES = 8,		// 视频请求响应

	CMD_PLAYBACK_CONTROL = 9,		// 回放控制
	CMD_PLAYBACK_CONTROL_RES = 10,	// 回放控制响应

	CMD_CLOSE_VIDEO = 11,			// 关闭视频会话
	CMD_CLOSE_VIDEO_RES = 12,		// 关闭视频请求响应

	CMD_RECORD_QUERY = 13,			// 录像查询
	CMD_RECORD_QUERY_RES = 14,		// 录像查询响应

	CMD_SET_AVPARAM = 15,			// 设置视频参数
	CMD_SET_AVPARAM_RES = 16,		// 设置响应

	CMD_GET_AVPARAM = 17,			// 获取视频参数
	CMD_GET_AVPARAM_RES = 18,		// 获取响应

	CMD_DISK_FORMAT = 19,			// 格式化磁盘
	CMD_DISK_FORMAT_RES = 20,		// 格式化响应

	CMD_GET_DISKINFO = 21,			// 获取全部磁盘信息（不提供单个）
	CMD_GET_DISKINFO_RES = 22,		// 获取磁盘信息响应

	CMD_STREAM_HANDLE_RES = 23,		//流操作响应：api_protocol_head_t结构中nStreamId为1，表示stream1，2表示stream2，3表示stream1+stream2
	CMD_ADD_STREAM = 24,			//新增流，同上
	CMD_DEL_STREAM = 25,			//删除流，同上
	CMD_GET_STREAM = 26,			//获取当前流，同上

	CMD_DEVICE_RESTART = 27,		//设备重启：api_protocol_head_t结构体中nStreamId为1，表示重启M1，2表示重启NVR
	CMD_DEVICE_RESTART_RES = 28,	//设备重启响应

	CMD_GET_CALIBRATION = 29,		// 获取标定信息
	CMD_GET_CALIBRATION_RES = 30,	// 获取标定信息响应

	CMD_GET_RECORD_CALIBRATION = 31,		// 获取回放时间段标定信息
	CMD_GET_RECORD_CALIBRATION_RES = 32,	// 获取回放时间段标定信息响应

	CMD_ACTIVE_REPORT = 100,				// 主动上报

    CMD_DETU_CLIENT_REGISTER = 2001,		//得图注册
    CMD_DETU_CLIENT_REGISTER_RES,

	CMD_DETU_CLIENT_HEART_BEAT,				// 心跳
	CMD_DETU_CLIENT_HEART_BEAT_RES,

    CMD_DETU_CLIENT_REQUEST_VIDEO,			// 请求实时视频（包含实时、回放流）
    CMD_DETU_CLIENT_REQUEST_VIDEO_RES,

	CMD_DETU_CLIENT_PLAYBACK_CONTROL,		//回放控制
	CMD_DETU_CLIENT_PLAYBACK_CONTROL_RES,	//回放控制响应

    CMD_DETU_CLIENT_RECORD_QUERY,			// 录像查询
    CMD_DETU_CLIENT_RECORD_QUERY_RES,		// 录像查询响应

    CMD_DETU_CLIENT_CLOSE_VIDEO,			// 关闭视频会话（包含实时、回放流）
    CMD_DETU_CLIENT_CLOSE_VIDEO_RES,

	CMD_DETU_CLIENT_SET_AVPARAM,			//设置视频参数
	CMD_DETU_CLIENT_SET_AVPARAM_RES,		//设置响应

	CMD_DETU_CLIENT_GET_AVPARAM,			//获取视频参数
	CMD_DETU_CLIENT_GET_AVPARAM_RES,		//获取响应

	CMD_DETU_CLIENT_DISK_FORMAT,			//格式化磁盘
	CMD_DETU_CLIENT_DISK_FORMAT_RES,		//格式化响应

	CMD_DETU_CLIENT_DISKINFO,				//获取磁盘信息
	CMD_DETU_CLIENT_DISKINFO_RES,			//获取磁盘响应

	CMD_DETU_REPORT_NAME,					//上报别名
	CMD_DETU_REPORT_NAME_RES,				//上报别名响应

	CMD_DETU_PTZ_REGISTER,					//球机注册
	CMD_DETU_PTZ_REGISTER_RES,				//球机注册响应

	CMD_DETU_SPY_REGISTER,					//枪机注册
	CMD_DETU_SPY_REGISTER_RES,				//枪机注册响应

	CMD_DETU_CLIENT_STREAM_HANDLE_RES,		//得图客户端流处理响应
	CMD_DETU_CLIENT_ADD_STREAM,				//得图客户端新增流
	CMD_DETU_CLIENT_DEL_STREAM,				//得图客户端删除流
	CMD_DETU_CLIENT_GET_STREAM,				//得图客户端获取当前流

	CMD_DETU_CLIENT_DEVICE_REBOOT,			//得图客户端控制设备重启
	CMD_DETU_CLIENT_DEVICE_REBOOT_RES,      //得图客户端控制设备重启响应

	CMD_DETU_CLIENT_REPORT_OPTIMIZE_PTS,	//得图客户端上报优化后的pts文件
	CMD_DETU_CLIENT_REPORT_OPTIMIZE_PTS_RES,//得图客户端上报优化后的pts文件响应

	CMD_DETU_CLIENT_ACTIVE_REPORT,			//向客户端主动上报
			
	CMD_DETU_CLIENT_GET_BANDWIDTH,			//客户端获取带宽请求
	CMD_DETU_CLIENT_GET_BANDWIDTH_RES,		//客户端获取带宽响应

	CMD_DETU_CLIENT_GET_PTZ_LIST,			//客户端获取球机列表
	CMD_DETU_CLIENT_GET_PTZ_LIST_RES,		//客户端获取球机列表响应

	CMD_DETU_CLIENT_GET_SPY_LIST,			//客户端获取枪机列表
	CMD_DETU_CLIENT_GET_SPY_LIST_RES,		//客户端获取枪机列表响应

	CMD_DETU_DELETE_PTZ,					//客户端删除球机
	CMD_DETU_DELETE_PTZ_RES,                //客户端删除球机响应

	CMD_DETU_DELETE_SPY,					//客户端删除枪机
	CMD_DETU_DELETE_SPY_RES,				//客户端删除枪机响应

	CMD_DETU_SAVE_PTZ_POINT,				//保存预置点
	CMD_DETU_SAVE_PTZ_POINT_RES,            //保存预置点响应

	CMD_DETU_GET_PTZ_POINT,					//获取预置点
	CMD_DETU_GET_PTZ_POINT_RES,				//获取预置点响应

	CMD_DETU_APP_REGISTER = 4001,			//得图APP注册
	CMD_DETU_APP_REGISTER_RES,				//得图APP注册响应

	CMD_DETU_APP_CLOSE,						//得图APP请求关闭
	CMD_DETU_APP_CLOSE_RES,					//得图APP请求关闭响应

	CMD_DETU_TCS_REGISTER = 5001,			//TCS注册
	CMD_DETU_TCS_REGISTER_RES,				//TCS注册响应

	CMD_DETU_TCS_HEARTBEAT,					//TCS心跳
	CMD_DETU_TCS_HEARTBEAT_RES,				//TCS心跳响应

	CMD_DETU_TCS_TRANSCODE,					//TCS转码请求
	CMD_DETU_TCS_TRANSCODE_RES,				//TCS转码请求响应

	CMD_DETU_TCS_TRANSCODE_STOP,			//TCS停止转码请求
	CMD_DETU_TCS_TRANSCODE_STOP_RES,		//TCS停止转码响应
}command_e;


// 返回值
typedef enum
{
	RESULT_SUCCESS = 0,		// 成功	
	RESULT_FAILED = -1,		// 失败

	RESULT_SYNC_OK = 10005,		// 同步成功
	RESULT_ONLINE_OK = 10006,	// M1四个通道都在线

    RESULT_NOTSUPPORT = -10000,		//不支持
    RESULT_UNKNOWCMD = -10001,		//未知指令
	RESULT_NODATA = -10002,			//无数据
    RESULT_NOTREGISTER = -10003,	//未注册
    RESULT_PARAM_ERR = -10004,		//参数错误
	RESULT_SYNC_ERR = -10005,		//同步失败
	RESULT_OFFLINE_ERR = -10006,	//M1一个或多个不在线
	RESULT_SEND_ERR = -10007,		//发送数据失败
	RESULT_CONNECT_ERR = -10008,	//连接流媒体服务器失败

    // 注册
    RESULT_USERNAMEERR = -11001,	//用户名错误
    RESULT_PWDERR = -11002,			//密码错误
    RESULT_REDEVICEID = -11003,		//设备ID重复
	RESULT_CALIBRATIONERR = -11004, //标定信息错误

	// 转码
	RESULT_TRANSCODE_EXIST = -12001,	// 设备已经在推流
	RESULT_OCCIPIED,					// 转码服务ID被占用
	RESUKT_PULL_RTMP_ERROR,				// RTMP拉流失败
	RESULT_PUSH_RTMP_ERROR,				// RTMP推流失败
}command_result_e;

typedef enum
{
	RTMP_LIVE_MAIN1 = 0,			// 实时主码流（1表示四目1，便于后续可能的多个四目）
	RTMP_LIVE_SUB1,					// 实时子码流

	RTMP_BACK_MAIN1,				// 回放主码流
	RTMP_BACK_SUB1,					// 回放子码流

	RTMP_LIVESTITCH_MAIN1,			// 实时拼接主码流
	RTMP_LIVESTITCH_SUB1,			// 实时拼接子码流

	RTMP_BACKSTITCH_MAIN1,			// 回放拼接主码流
	RTMP_BACKSTITCH_SUB1,			// 回放拼接子码流
}streamId_type_e;

typedef enum
{
	DISKSTATUS_DORMANCY = 1,		// 正常状态
	DISKSTATUS_ABNORMAL = 2,		// 不正常状态
	DISKSTATUS_NOT_EXISTENT = 3,	// 磁盘不存在
	DISKSTATUS_WRITE_PROTECT = 4,	// 磁盘写保护	
	DISKSTATUS_NOT_FORMAT = 5,		// 磁盘未格式化
	DISKSTATUS_FORMATTING = 6,		// 磁盘正在格式化
	DISKSTATUS_UNKOWN = 7,			// 未知状态
}disk_status_e;

typedef enum
{
	DISKTYPE_HARDDISK = 1,			// 本地硬盘
	DISKTYPE_SDCARD = 2,			// SD卡
	DISKTYPE_FTP = 3,				// FTP
	DISKTYPE_NAS = 4,				// NAS
	DISKTYPE_EXTERN_DISK = 5,		// 外接设备
	DISKTYPE_REMOTE_EXTERN_DISK = 6,// 远程外接设备
	DISKTYPE_ESATA = 7,				// ESata盘
	DISKTYPE_RAID = 8,				// Raid阵列
}disk_type_e;

typedef enum {
	SERVER_TYPE_CLINET = 0,		// CU
	SERVER_TYPE_TCS,			// TCS
}server_type_e;

//指定按1字节对齐
#pragma pack (1) 


// 协议头
typedef struct protocol_head
{

    unsigned char	nStartFlags;			// 开始标示:0xAF
    unsigned char	nVersion;				// 版本:0x01
    unsigned short	nCmd;					// 指令:command_e 枚举结构
    unsigned int	nDataLen;				// 负载长度

    short			nResult;				// 仅用于命令返回:command_result_e 枚举结构
	unsigned char   nM1Id;					// 用于后续可能的多个M1
	unsigned char   nStreamId;				// 流id   1：主码流，2：子码流

    unsigned char	deviceNum;				// 预留
    unsigned char	nEndFlags;				// 结束标示:oxFA	

    protocol_head()
	{
        nStartFlags = 0xAF;
        nVersion = 0x01;
        nCmd = 0;
        nDataLen = 0;
        nResult = 0;
		nM1Id = 0;
		nStreamId = 0;
        deviceNum = 0;
        nEndFlags = 0xFA;
    }

    int get_size()
	{
        return sizeof(protocol_head);
    }

}protocol_head_t;



// CMD_DETU_CLIENT_REQUEST_VIDEO, 视频请求, 客户端到服务器
typedef struct api_detu_client_request_video
{
	unsigned char 	szDeviceId[API_ARRAY_LEN];		// 对应NVR的设备ID，用来通知服务器需要那个设备开始推流
	unsigned char   nDeviceId;						// 客户端给的设备序号，用以组装留地址，区分播放
	
	// 用于回放
	unsigned int  	nStartTime;
	unsigned int  	nEndTime;

	api_detu_client_request_video()
	{
		memset(&szDeviceId, 0, API_ARRAY_LEN);
	}

	int get_size()
	{
		return sizeof(api_detu_client_request_video);
	}

}api_detu_client_request_video_t;



// CMD_DETU_CLIENT_REQUEST_VIDEO_RES, 视频请求反馈, 服务器反馈URL给客户端
typedef struct api_detu_client_request_video_res
{
	unsigned char 	szDeviceId[API_ARRAY_LEN];		// 对应NVR的设备ID，用来通知服务器需要那个设备开始推流
	unsigned char 	szRtmpURL[API_RTMP_LEN];

	api_detu_client_request_video_res()
	{
		memset(&szRtmpURL, 0, API_RTMP_LEN);
	}

	int get_size()
	{
		return sizeof(api_detu_client_request_video_res);
	}

}api_detu_client_request_video_res_t;



// CMD_DETU_CLIENT_CLOSE_VIDEO, 关闭视频, 客户端到服务器
typedef struct api_detu_client_close_video
{
	unsigned char szDeviceId[API_ARRAY_LEN];      //对应NVR的设备ID

	api_detu_client_close_video()
	{
		memset(&szDeviceId, 0, API_ARRAY_LEN);
	}

	int get_size()
	{
		return sizeof(api_detu_client_close_video);
	}

}api_detu_client_close_video_t;
 


// CMD_DETU_TCS_REGISTER, 注册, TCS发往服务器
typedef struct api_detu_tcs_register
{
	unsigned char	szTcsIp[API_ARRAY_LEN];	//TCS服务IP
	unsigned int	nPort;					//TCS监听端口

	unsigned int	nServerId;				//TCS服务ID(分布式)
	unsigned int	nLimits;				//TCS服务转码路数限制

	unsigned int	nHeartbeatInterval;		// 心跳间隔	

	api_detu_tcs_register()
	{
		memset(&szTcsIp, 0, API_ARRAY_LEN);
	}

	int get_size()
	{
		return sizeof(api_detu_tcs_register);
	}

}api_detu_tcs_register_t;



// CMD_DETU_TCS_HEARTBEAT，心跳, TCS发往服务器
typedef struct api_detu_tcs_heartbeat
{
	unsigned int	nServerId;				//TCS服务ID(分布式)
	unsigned int	nLimits;				//TCS服务转码路数限制
	unsigned int	nCAU;					//TCS当前转码路数

	api_detu_tcs_heartbeat()
	{
		nServerId = 0;
		nLimits = 0;
		nCAU = 0;
	}

	int get_size()
	{
		return sizeof(api_detu_tcs_heartbeat);
	}

}api_detu_tcs_heartbeat_t;


// CMD_DETU_TCS_TRANSCODE, 转码, 客户端发往TCS
typedef struct api_detu_tcs_transcode
{
	unsigned char 	szRtmpURL[API_URL_LENGTH];		// rtmp推流地址
	unsigned char 	szDeviceId[API_ARRAY_LEN];		// 对应NVR的设备ID，用来通知服务器需要那个设备开始推流
	unsigned char   nDeviceId;						// 客户端给的设备序号，用以组装留地址，区分播放

	unsigned char   nStreamType;					// 码流类型
	unsigned char   nFps;							// 帧率
	unsigned int    nbitrate;						// 码率(kbps)
	unsigned int    nWidth;							// 高
	unsigned int    nHeight;						// 宽

	// 用于回放
	unsigned int  	nStartTime;
	unsigned int  	nEndTime;

	unsigned int	nPtsLen;
	unsigned char 	pts_data[API_PTS_LEN];			//PTS文件数据

	api_detu_tcs_transcode()
	{
		memset(&szDeviceId, 0, API_ARRAY_LEN);
	}

	int get_size()
	{
		return sizeof(api_detu_tcs_transcode);
	}

}api_detu_tcs_transcode_t;

// CMD_DETU_TCS_TRANSCODE_RES, 转码响应消息，TCS发往客户端
typedef struct api_detu_tcs_transcode_res
{
	unsigned char szDeviceId[API_ARRAY_LEN];      //对应NVR的设备ID

	api_detu_tcs_transcode_res()
	{
		memset(&szDeviceId, 0, API_ARRAY_LEN);
	}

	int get_size()
	{
		return sizeof(api_detu_tcs_transcode_res);
	}

}api_detu_tcs_transcode_res_t;

// CMD_DETU_TCS_TRANSCODE_STOP， 停止转码, 客户端发往TCS
typedef struct api_detu_tcs_transcode_stop
{
	unsigned char szDeviceId[API_ARRAY_LEN];      //对应NVR的设备ID

	api_detu_tcs_transcode_stop()
	{
		memset(&szDeviceId, 0, API_ARRAY_LEN);
	}

	int get_size()
	{
		return sizeof(api_detu_tcs_transcode_stop);
	}

}api_detu_tcs_transcode_stop_t;

// CMD_DETU_TCS_TRANSCODE_STOP_RES， 停止转码响应消息, TCS发往客户端
typedef struct api_detu_tcs_transcode_stop_res
{
	unsigned char szDeviceId[API_ARRAY_LEN];      //对应NVR的设备ID

	api_detu_tcs_transcode_stop_res()
	{
		memset(&szDeviceId, 0, API_ARRAY_LEN);
	}

	int get_size()
	{
		return sizeof(api_detu_tcs_transcode_stop_res);
	}

}api_detu_tcs_transcode_stop_res_t;


#pragma pack ()  // 取消指定对齐，恢复缺省对齐


#endif
