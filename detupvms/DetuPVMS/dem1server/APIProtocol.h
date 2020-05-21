#pragma once
#include "message.h"
#define API_ARRAY_LEN	(32)
#define  API_URL_LEN  (512)
#define API_RTMP_LEN      (64)
#define MAX_NVR_LIST_NUM (50)
#define API_PTS_LEN	(32768)

#define API_MAP_DATA_BLOCK_LEN	(8192)		//暂定1024字节传输

#define  MAX_DEVICE_NUM (10)

#define API_MAP_PATH   (200)

/********************************************
1）考虑可拓展性
2）网络转换时会变成unsigned

********************************************/

/*********************************************************************************************
APIClient处理(NVR)：
1）实现了注册、实时视频请求响应，及重连处理
1）马上重连情况：a)系统启动时 b）消息错误 c）服务器参数重置 d）发送注册请求失败
2）每10s重连情况：a）创建socket失败 b）连接失败  c）注册失败
APIServer(你要做的)：提供了3个测试程序，针对APIClient，你可抓包分析，配合你开发
**********************************************************************************************/
namespace dm {
	namespace server {
		// 命令号
		typedef enum
		{
			CMD_REGISTER = 1,	         // 注册
			CMD_REGISTER_RES = 2,		// 注册响应

			CMD_UNREGISTER = 3,			// 注销
			CMD_UNREGISTER_RES = 4,		// 注销响应

			CMD_HEART_BEAT = 5,			// 心跳
			CMD_HEART_BEAT_RES = 6,		// 心跳响应

			CMD_REQUEST_VIDEO = 7,		// 视频请求（包含实时、回放流）
			CMD_REQUEST_VIDEO_RES = 8,	// 视频请求响应

			CMD_PLAYBACK_CONTROL = 9,	// 回放控制
			CMD_PLAYBACK_CONTROL_RES = 10,	// 回放控制响应

			CMD_CLOSE_VIDEO = 11,		// 关闭视频会话
			CMD_CLOSE_VIDEO_RES = 12,	// 关闭视频请求响应

			CMD_RECORD_QUERY = 13,		// 录像查询
			CMD_RECORD_QUERY_RES = 14,	// 录像查询响应

			CMD_SET_AVPARAM = 15,		// 设置视频参数
			CMD_SET_AVPARAM_RES = 16,	// 设置响应

			CMD_GET_AVPARAM = 17,		// 获取视频参数
			CMD_GET_AVPARAM_RES = 18,	// 获取响应

			CMD_DISK_FORMAT = 19,		// 格式化磁盘
			CMD_DISK_FORMAT_RES = 20,	// 格式化响应

			CMD_GET_DISKINFO = 21,		// 获取全部磁盘信息（不提供单个）
			CMD_GET_DISKINFO_RES = 22,	// 获取磁盘信息响应

			CMD_STREAM_HANDLE_RES = 23,      //流操作响应：api_protocol_head_t结构中nStreamId为1，表示stream1，2表示stream2，3表示stream1+stream2
			CMD_ADD_STREAM = 24,             //新增流，同上
			CMD_DEL_STREAM = 25,             //删除流，同上
			CMD_GET_STREAM = 26,             //获取当前流，同上

			CMD_DEVICE_RESTART = 27,         //设备重启：api_protocol_head_t结构体中nStreamId为1，表示重启M1，2表示重启NVR
			CMD_DEVICE_RESTART_RES = 28,	 //设备重启响应

			CMD_GET_CALIBRATION = 29,		// 获取标定信息
			CMD_GET_CALIBRATION_RES = 30,	// 获取标定信息响应

			CMD_GET_RECORD_CALIBRATION = 31,		// 获取回放时间段标定信息
			CMD_GET_RECORD_CALIBRATION_RES = 32,	// 获取回放时间段标定信息响应

			CMD_SET_M1_TIME = 33,		// 设置M1时间: api_device_time_t
			CMD_SET_M1_TIME_RES = 34,	// 响应
			CMD_GET_M1_TIME = 35,		// 获取M1时间
			CMD_GET_M1_TIME_RES = 36,	// 响应

			CMD_SET_RECORD_POLICY = 37,			// 设置录像策略: api_record_policy_t
			CMD_SET_RECORD_POLICY_RES = 38,		// 响应
			CMD_GET_RECORD_POLICY = 39,			// 获取录像策略
			CMD_GET_RECORD_POLICY_RES = 40,		// 响应

			CMD_ACTIVE_REPORT = 100,			// 主动上报

			CMD_DETU_CLIENT_GET_LIST = 2001,	//得图注册
			CMD_DETU_CLIENT_GET_LIST_RES,

			CMD_DETU_CLIENT_HEART_BEAT,							// 心跳
			CMD_DETU_CLIENT_HEART_BEAT_RES,

			CMD_DETU_CLIENT_VERSION_CHECK,							// 心跳
			CMD_DETU_CLIENT_VERSION_CHECK_RES,


			CMD_DETU_CLIENT_REQUEST_VIDEO,						// 请求实时视频（包含实时、回放流）
			CMD_DETU_CLIENT_REQUEST_VIDEO_RES,

			CMD_DETU_CLIENT_PLAYBACK_CONTROL,                   //回放控制
			CMD_DETU_CLIENT_PLAYBACK_CONTROL_RES,				//回放控制响应

			CMD_DETU_CLIENT_RECORD_QUERY,						// 录像查询
			CMD_DETU_CLIENT_RECORD_QUERY_RES,					// 录像查询响应

			CMD_DETU_CLIENT_CLOSE_VIDEO,						// 关闭视频会话（包含实时、回放流）
			CMD_DETU_CLIENT_CLOSE_VIDEO_RES,

			CMD_DETU_CLIENT_SET_AVPARAM,						//设置视频参数
			CMD_DETU_CLIENT_SET_AVPARAM_RES,					//设置响应

			CMD_DETU_CLIENT_GET_AVPARAM,					//获取视频参数
			CMD_DETU_CLIENT_GET_AVPARAM_RES,				//获取响应

			CMD_DETU_CLIENT_DISK_FORMAT,                    //格式化磁盘
			CMD_DETU_CLIENT_DISK_FORMAT_RES,				//格式化响应

			CMD_DETU_CLIENT_DISKINFO,                        //获取磁盘信息
			CMD_DETU_CLIENT_DISKINFO_RES,                    //获取磁盘响应

			CMD_DETU_REPORT_NAME,                            //上报别名
			CMD_DETU_REPORT_NAME_RES,                        //上报别名响应

			CMD_DETU_PTZ_REGISTER,                                //球机注册
			CMD_DETU_PTZ_REGISTER_RES,                       //球机注册响应

			CMD_DETU_SPY_REGISTER,                                //枪机注册
			CMD_DETU_SPY_REGISTER_RES,                       //枪机注册响应

			CMD_DETU_CLIENT_STREAM_HANDLE_RES,				//得图客户端流处理响应
			CMD_DETU_CLIENT_ADD_STREAM,                     //得图客户端新增流
			CMD_DETU_CLIENT_DEL_STREAM,                      //得图客户端删除流
			CMD_DETU_CLIENT_GET_STREAM,                      //得图客户端获取当前流

			CMD_DETU_CLIENT_DEVICE_REBOOT,               //得图客户端控制设备重启
			CMD_DETU_CLIENT_DEVICE_REBOOT_RES,      //得图客户端控制设备重启响应

			CMD_DETU_CLIENT_REPORT_OPTIMIZE_PTS,               //得图客户端上报优化后的pts文件
			CMD_DETU_CLIENT_REPORT_OPTIMIZE_PTS_RES,      //得图客户端上报优化后的pts文件响应

			CMD_DETU_CLIENT_ACTIVE_REPORT,               //向客户端主动上报

			CMD_DETU_CLIENT_GET_BANDWIDTH,           //客户端获取带宽请求
			CMD_DETU_CLIENT_GET_BANDWIDTH_RES,   //客户端获取带宽响应

			CMD_DETU_CLIENT_GET_PTZ_LIST,             //客户端获取球机列表
			CMD_DETU_CLIENT_GET_PTZ_LIST_RES,         //客户端获取球机列表响应

			CMD_DETU_CLIENT_GET_SPY_LIST,             //客户端获取枪机列表
			CMD_DETU_CLIENT_GET_SPY_LIST_RES,         //客户端获取枪机列表响应

			CMD_DETU_DELETE_PTZ,                        //客户端删除球机
			CMD_DETU_DELETE_PTZ_RES,                //客户端删除球机响应

			CMD_DETU_DELETE_SPY,                       //客户端删除枪机
			CMD_DETU_DELETE_SPY_RES,               //客户端删除枪机响应

			CMD_DETU_SAVE_PTZ_POINT,                     //保存预置点
			CMD_DETU_SAVE_PTZ_POINT_RES,            //保存预置点响应

			CMD_DETU_GET_PTZ_POINT,                        //获取预置点
			CMD_DETU_GET_PTZ_POINT_RES,               //获取预置点响应

			CMD_DETU_CLIENT_LOGIN_CHECKED,    //客户端登录校验
			CMD_DETU_CLIENT_LOGIN_CHECKED_RES,  //响应

			CMD_DETU_CLIENT_REGISTER_USER,    //客户端注册用户请求
			CMD_DETU_CLIENT_REGISTER_USER_RES,  //响应

			CMD_DETU_SET_MAP,						//客户端设置地图数据
			CMD_DETU_SET_MAP_RES,					//响应

			CMD_DETU_GET_MAP,						//客户端请求地图数据
			CMD_DETU_GET_MAP_RES,					//响应

			/********************APP相关*********************/
			CMD_DETU_APP_REGISTER = 4001,                   //得图APP注册
			CMD_DETU_APP_REGISTER_RES,                        //得图APP注册响应

			CMD_DETU_APP_CLOSE,                                      //得图APP请求关闭
			CMD_DETU_APP_CLOSE_RES,                             //得图APP请求关闭响应

			/********************转码服务相关*********************/
			CMD_DETU_TCS_REGISTER = 5001,			//TCS注册
			CMD_DETU_TCS_REGISTER_RES,				//TCS注册响应

			CMD_DETU_TCS_HEARTBEAT,					//TCS心跳
			CMD_DETU_TCS_HEARTBEAT_RES,				//TCS心跳响应

			CMD_DETU_TCS_TRANSCODE,					//TCS转码请求
			CMD_DETU_TCS_TRANSCODE_RES,				//TCS转码请求响应

			CMD_DETU_TCS_TRANSCODE_STOP,			//TCS停止转码请求
			CMD_DETU_TCS_TRANSCODE_STOP_RES,		//TCS停止转码响应

			CMD_DETU_CLIENT_GET_TCS_INFO,         //向客户端发送TCS信息
			CMD_DETU_CLIENT_GET_TCS_INFO_RES,    //向客户端发送TCS信息响应

			CMD_DETU_CLIENT_UPDATE_TCSINFO,          //更新转码服务信息
			CMD_DETU_CLIENT_UPDATE_TCSINFO_RES,      //更新转码服务信息

			CMD_DETU_CLIENT_TCS_REPORT_ERROR,        //转码异常上报
			CMD_DETU_CLINET_TCS_OFFLINE,             //转码服务离线

			CMD_DETU_CLIENT_TCS_RESET,                //重置转码请求
			CMD_DETU_CLIENT_TCS_RESET_RES,        //重置转码应答

			CMD_DETU_SET_M1_TIME,	// 设置M1时间: api_device_time_t
			CMD_DETU_SET_M1_TIME_RES,	// 响应
			CMD_DETU_GET_M1_TIME,	// 获取M1时间
			CMD_DETU_GET_M1_TIME_RES,	// 响应

			CMD_DETU_SET_RECORD_POLICY,	// 设置录像策略: api_record_policy_t
			CMD_DETU_SET_RECORD_POLICY_RES,	// 响应
			CMD_DETU_GET_RECORD_POLICY,	// 获取录像策略
			CMD_DETU_GET_RECORD_POLICY_RES,	// 响应

			CMD_DETU_SEND_MAP_DATA,
			CMD_DETU_SEND_MAP_DATA_RES,
			CMD_DETU_GET_MAP_DATA,
			CMD_DETU_GET_MAP_DATA_RES,

		}command_e;

		// 返回值
		typedef enum
		{
			RESULT_SUCCESS = 0,		// 成功	
			RESULT_FAILED = -1,		// 失败

			RESULT_SYNC_OK = 10005,	// 同步成功
			RESULT_ONLINE_OK = 10006,	// M1四个通道都在线

			RESULT_NOTSUPPORT = -10000,         //不支持
			RESULT_UNKNOWCMD = -10001,		//未知指令
			RESULT_NODATA = -10002,                 //无数据
			RESULT_NOTREGISTER = -10003,        //未注册
			RESULT_PARAM_ERR = -10004,		   //参数错误
			RESULT_SYNC_ERR = -10005,              //同步失败
			RESULT_OFFLINE_ERR = -10006,         //M1一个或多个不在线
			RESULT_SEND_ERR = -10007,	// 发送数据失败
			RESULT_CONNECT_ERR = -10008,	// 连接流媒体服务器失败

			// 注册
			RESULT_USERNAMEERR = -11001,				// 用户名错误
			RESULT_PWDERR = -11002,				// 密码错误
			RESULT_REDEVICEID = -11003,				// 设备ID重复
			RESULT_CALIBRATIONERR = -11004,  //标定信息错误

			//转码
			RESULT_TRANSCODE_EXIST = -12001,     //设置已经在推流
			RESULT_OCCIPIED,                                       //转码服务ID被占用
			RESUKT_PULL_RTMP_ERROR,				// RTMP拉流失败
			RESULT_PUSH_RTMP_ERROR,				// RTMP推流失败
		}command_result_e;

		typedef enum
		{
			RTMP_LIVE_MAIN1 = 0,		// 实时主码流（1表示四目1，便于后续可能的多个四目）
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
			DISKSTATUS_DORMANCY = 1,	// 正常状态
			DISKSTATUS_ABNORMAL = 2,	// 不正常状态
			DISKSTATUS_NOT_EXISTENT = 3,	// 磁盘不存在
			DISKSTATUS_WRITE_PROTECT = 4,	// 磁盘写保护	
			DISKSTATUS_NOT_FORMAT = 5,	// 磁盘未格式化
			DISKSTATUS_FORMATTING = 6,	// 磁盘正在格式化
			DISKSTATUS_UNKOWN = 7,	// 未知状态
		}disk_status_e;

		typedef enum
		{
			DISKTYPE_HARDDISK = 1,	// 本地硬盘
			DISKTYPE_SDCARD = 2,	// SD卡
			DISKTYPE_FTP = 3,	// FTP
			DISKTYPE_NAS = 4,	// NAS
			DISKTYPE_EXTERN_DISK = 5,	// 外接设备
			DISKTYPE_REMOTE_EXTERN_DISK = 6,	// 远程外接设备
			DISKTYPE_ESATA = 7,	// ESata盘
			DISKTYPE_RAID = 8,	// Raid阵列
		}disk_type_e;

		typedef enum {
			SERVER_TYPE_CLINET = 0,		// CU
			SERVER_TYPE_TCS,			// TCS
		}server_type_e;

		//客户端注册用户校验
		typedef enum{
			HAVE_BEEN_REGISTERED = -5001,
			REGISTER_SUCCESSFUL = 5001,
		}register_type_e;

		//客户端登录校验码
		typedef enum{
			USERNAME_ERR = -6001,
			PASSWD_ERR,
			MUTI_CLIENT_ERR,
			READ_DATABASE_ERR,
			CHECK_FINISHED = 6001,
		}login_type_e;

#pragma pack (1) // 指定按1字节对齐
		// 协议头
		typedef struct protocol_head
		{

			unsigned char	nStartFlags;			// 开始标示:0xAF
			unsigned char	nVersion;				// 版本:0x01
			unsigned short	nCmd;					// 指令:command_e 枚举结构
			unsigned int	nDataLen;				// 负载长度

			short			nResult;				// 仅用于命令返回:command_result_e 枚举结构
			unsigned char nM1Id;        //用于后续可能的多个M1
			unsigned char nStreamId;     //流id   1：主码流，2：子码流

			unsigned char	deviceNum;				// 预留
			unsigned char	nEndFlags;				// 结束标示:oxFA	

			protocol_head(){
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
			int get_size(){

				return sizeof(protocol_head);
			}

			void read(netbuffer_t* rb){

				read_uchar(this->nStartFlags, rb);
				read_uchar(this->nVersion, rb);
				read_ushort(this->nCmd, rb);
				read_uint(this->nDataLen, rb);
				read_short(this->nResult, rb);
				read_uchar(this->nM1Id, rb);
				read_uchar(this->nStreamId, rb);
				read_uchar(this->deviceNum, rb);
				read_uchar(this->nEndFlags, rb);
			}

			void write(netbuffer_t* wb){

				write_uchar(this->nStartFlags, wb);
				write_uchar(this->nVersion, wb);
				write_ushort(this->nCmd, wb);
				write_uint(this->nDataLen, wb);
				write_short(this->nResult, wb);
				write_uchar(this->nM1Id, wb);
				write_uchar(this->nStreamId, wb);
				write_uchar(this->deviceNum, wb);
				write_uchar(this->nEndFlags, wb);
			}
		}protocol_head_t;

		// 注册 : CMD_REGISTER
		typedef struct api_register
		{
			unsigned char 	szDeviceId[API_ARRAY_LEN];			// 设备ID，唯一标识
			unsigned char 	szUserName[API_ARRAY_LEN];			// 用户名
			unsigned char 	szPassWord[API_ARRAY_LEN];			// 密码
			unsigned int	nHeartbeatInterval;		// 心跳间隔	

			api_register(){
				memset(&szDeviceId, 0, API_ARRAY_LEN);
				memset(&szUserName, 0, API_ARRAY_LEN);
				memset(&szPassWord, 0, API_ARRAY_LEN);
			}

			int get_size(){

				return sizeof(api_register);
			}

			void read(netbuffer_t* rb){

				readdata(this->szDeviceId, API_ARRAY_LEN, rb);
				readdata(this->szUserName, API_ARRAY_LEN, rb);
				readdata(this->szPassWord, API_ARRAY_LEN, rb);
				read_uint(this->nHeartbeatInterval, rb);
			}

			void write(netbuffer_t* wb){
				writedata(this->szDeviceId, API_ARRAY_LEN, wb);
				writedata(this->szUserName, API_ARRAY_LEN, wb);
				writedata(this->szPassWord, API_ARRAY_LEN, wb);
				write_uint(this->nHeartbeatInterval, wb);

			}

		}api_register_t;

		// 注册 : CMD_REGISTER
		typedef struct api_pts_file
		{
			unsigned int	nPtsLen;
			unsigned char 	pts_data[API_PTS_LEN];		//PTS文件数据
			api_pts_file(){
				nPtsLen = 0;
				memset(&pts_data, 0, API_PTS_LEN);
			}

			int get_size(){
				return sizeof(api_register);
			}

			void read(netbuffer_t* rb){
				read_uint(this->nPtsLen, rb);
				readdata(this->pts_data, API_PTS_LEN, rb);
			}

			void write(netbuffer_t* wb){
				write_uint(this->nPtsLen, wb);
				writedata(this->pts_data, API_PTS_LEN, wb);
			}
		}api_pts_file_t;

		//服务器向NVR查询回放结构体
		typedef struct api_record_query
		{
			unsigned int  	nStartTime;						//
			unsigned int  	nEndTime;						//

			api_record_query()
			{
				nStartTime = 0;
				nEndTime = 0;
			}

			int get_size()
			{
				return sizeof(api_record_query);
			}

			void read(netbuffer_t* rb)
			{
				read_uint(this->nStartTime, rb);
				read_uint(this->nEndTime, rb);
			}

			void write(netbuffer_t* wb)
			{
				write_uint(this->nStartTime, wb);
				write_uint(this->nEndTime, wb);
			}

		}api_record_query_t;

		//NVR查询回放返回服务器结构体
		typedef struct api_record_query_respond
		{
			unsigned char 	nCurRecordSegmentNum;			//
			unsigned char	nTotalRecordSegmentNum;		    //

			unsigned int  	nStartTime;						//
			unsigned int  	nEndTime;						//

			api_record_query_respond()
			{
				nCurRecordSegmentNum = 1;		    //
				nTotalRecordSegmentNum = 1;		    //
				nStartTime = 0;
				nEndTime = 0;
			}
			int get_size()
			{
				return sizeof(api_record_query_respond);
			}
			void read(netbuffer_t* rb)
			{
				read_uchar(this->nCurRecordSegmentNum, rb);
				read_uchar(this->nTotalRecordSegmentNum, rb);
				read_uint(this->nStartTime, rb);
				read_uint(this->nEndTime, rb);
			}

			void write(netbuffer_t* wb)
			{
				write_uchar(this->nCurRecordSegmentNum, wb);
				write_uchar(this->nTotalRecordSegmentNum, wb);
				write_uint(this->nStartTime, wb);
				write_uint(this->nEndTime, wb);
			}


		}api_record_query_respond_t;



		// 视频请求（含实时、回放）:CMD_REQUEST_LIVE_VIDEO ****************服务器到NVR
		typedef struct api_request_video
		{
			unsigned char 	szRtmpURL[API_RTMP_LEN];

			// 用于回放
			unsigned int  	nStartTime;
			unsigned int  	nEndTime;

			api_request_video()
			{
				memset(&szRtmpURL, 0, API_RTMP_LEN);
				nStartTime = 0;
				nEndTime = 0;
			}

			int get_size(){
				return sizeof(api_request_video);
			}



			void read(netbuffer_t* rb){
				readdata(this->szRtmpURL, API_RTMP_LEN, rb);
				read_uint(this->nStartTime, rb);
				read_uint(this->nEndTime, rb);
			}

			void write(netbuffer_t* wb){
				writedata(this->szRtmpURL, API_RTMP_LEN, wb);
				write_uint(this->nStartTime, wb);
				write_uint(this->nEndTime, wb);
			}
		}api_request_video_t;

		// 注册 : CMD_DETU_CLIENT_REGISTER
		typedef struct api_detu_client_register
		{
			unsigned char 	szDetuDeviceUUId[API_RTMP_LEN];			// 设备ID，唯一标识
			unsigned char 	szDetuUserName[API_ARRAY_LEN];			// 用户名
			unsigned char 	szDetuPassWord[API_ARRAY_LEN];			// 密码

			api_detu_client_register(){
				memset(&szDetuDeviceUUId, 0, API_RTMP_LEN);
				memset(&szDetuUserName, 0, API_ARRAY_LEN);
				memset(&szDetuPassWord, 0, API_ARRAY_LEN);
			}
			int get_size(){
				return sizeof(api_detu_client_register);
			}

			void read(netbuffer_t* rb){
				readdata(this->szDetuDeviceUUId, API_RTMP_LEN, rb);
				readdata(this->szDetuUserName, API_ARRAY_LEN, rb);
				readdata(this->szDetuPassWord, API_ARRAY_LEN, rb);
			}
			void write(netbuffer_t* wb){
				writedata(this->szDetuDeviceUUId, API_RTMP_LEN, wb);
				writedata(this->szDetuUserName, API_ARRAY_LEN, wb);
				writedata(this->szDetuPassWord, API_ARRAY_LEN, wb);
			}
		}api_detu_client_register_t;

		//球机相关信息
		typedef struct api_detu_client_ptz
		{
			unsigned char nIP[API_ARRAY_LEN];
			unsigned short nPort;
			unsigned char nUser[API_ARRAY_LEN];
			unsigned char nPasswd[API_ARRAY_LEN];

			api_detu_client_ptz()
			{
				memset(&nIP, 0, API_ARRAY_LEN);
				nPort = 0;
				memset(&nUser, 0, API_ARRAY_LEN);
				memset(&nPasswd, 0, API_ARRAY_LEN);
			}
			int get_size(){
				return sizeof(api_detu_client_ptz);
			}
			void read(netbuffer_t* rb){
				readdata(this->nIP, API_ARRAY_LEN, rb);
				read_ushort(this->nPort, rb);
				readdata(this->nUser, API_ARRAY_LEN, rb);
				readdata(this->nPasswd, API_ARRAY_LEN, rb);
			}
			void write(netbuffer_t* wb){
				writedata(this->nIP, API_ARRAY_LEN, wb);
				write_ushort(this->nPort, wb);
				writedata(this->nUser, API_ARRAY_LEN, wb);
				writedata(this->nPasswd, API_ARRAY_LEN, wb);
			}
		}api_detu_client_ptz_t;


		typedef struct api_detu_client_register_res
		{
			unsigned  char	szDeviceId[API_ARRAY_LEN];			// 设备ID，唯一标识
			unsigned char szName[API_ARRAY_LEN];
			unsigned char m1DeviceId[API_ARRAY_LEN];
			unsigned int              szUpDown;
			unsigned int				curr_num;
			unsigned int				total_num;
			unsigned int              online;
			//unsigned int               onMap;              // 1：map设置      0：为从map设置
			api_pts_file	pts;
			api_detu_client_ptz ptz;
			api_detu_client_register_res(){
				memset(&szDeviceId, 0, API_ARRAY_LEN);
				memset(&szName, 0, API_ARRAY_LEN);
				memcpy(&m1DeviceId, "default", API_ARRAY_LEN);
				szUpDown = 0;
				curr_num = 0;
				total_num = 0;
				online = 0;
				//onMap = 0;
			}
			int get_size(){
				return sizeof(api_detu_client_register_res);
			}
			void read(netbuffer_t* rb){
				readdata(this->szDeviceId, API_ARRAY_LEN, rb);
				readdata(this->szName, API_ARRAY_LEN, rb);
				readdata(this->m1DeviceId, API_ARRAY_LEN, rb);
				read_uint(this->szUpDown, rb);
				read_uint(this->curr_num, rb);
				read_uint(this->total_num, rb);
				read_uint(this->online, rb);
				//read_uint(this->onMap, rb);
				pts.read(rb);
				ptz.read(rb);
			}
			void write(netbuffer_t* wb){
				writedata(this->szDeviceId, API_ARRAY_LEN, wb);
				writedata(this->szName, API_ARRAY_LEN, wb);
				writedata(this->m1DeviceId, API_ARRAY_LEN, wb);
				write_uint(this->szUpDown, wb);
				write_uint(this->curr_num, wb);
				write_uint(this->total_num, wb);
				write_uint(this->online, wb);
				//write_uint(this->onMap, wb);
				pts.write(wb);
				ptz.write(wb);
			}
		}api_detu_client_register_res_t;

		typedef struct api_detu_client_optmize
		{
			unsigned  char	szDeviceId[API_ARRAY_LEN];			// 设备ID，唯一标识
			api_pts_file    optmize_pts;
			api_detu_client_optmize(){
				memset(&szDeviceId, 0, API_ARRAY_LEN);
			}
			int get_size(){
				return sizeof(api_detu_client_optmize);
			}
			void read(netbuffer_t* rb){
				readdata(this->szDeviceId, API_ARRAY_LEN, rb);
				optmize_pts.read(rb);
			}
			void write(netbuffer_t* wb){
				writedata(this->szDeviceId, API_ARRAY_LEN, wb);
				optmize_pts.write(wb);
			}
		}api_detu_client_optmize_t;

		typedef struct api_detu_client_register_res_list
		{
			short numlist;
			api_detu_client_register_res_t nvrList[MAX_NVR_LIST_NUM];


			api_detu_client_register_res_list(){
				numlist = 0;
			}
			int get_size(){
				return  sizeof(api_detu_client_register_res_list);
			}
			void read(netbuffer_t* rb){
				read_short(this->numlist, rb);

				for (int i = 0; i < this->numlist; i++)
				{
					nvrList[i].read(rb);
				}
			}
			void write(netbuffer_t* wb){
				write_short(this->numlist, wb);

				for (int i = 0; i < numlist; i++){
					nvrList[i].write(wb);
				}
			}

		}api_detu_client_register_res_list_t;





		// 视频请求（含实时、回放）:CMD_DETU_CLIENT_REQUEST_LIVE_VIDEO ********客户端到服务器
		typedef struct api_detu_client_request_video
		{
			unsigned char 	szDeviceId[API_ARRAY_LEN];;		// 对应NVR的设备ID，用来通知服务器需要那个设备开始推流
			unsigned char   nDeviceId;						// 客户端给的设备序号，用以组装留地址，区分播放
			// 用于回放
			unsigned int  	nStartTime;
			unsigned int  	nEndTime;

			api_detu_client_request_video(){
				memset(&szDeviceId, 0, API_ARRAY_LEN);
			}

			int get_size(){
				return sizeof(api_detu_client_request_video);
			}

			void read(netbuffer_t* rb){
				readdata(this->szDeviceId, API_ARRAY_LEN, rb);
				read_uchar(this->nDeviceId, rb);
				read_uint(this->nStartTime, rb);
				read_uint(this->nEndTime, rb);
			}

			void write(netbuffer_t* wb){
				writedata(this->szDeviceId, API_ARRAY_LEN, wb);
				write_uchar(this->nDeviceId, wb);
				write_uint(this->nStartTime, wb);
				write_uint(this->nEndTime, wb);
			}
		}api_detu_client_request_video_t;

		// 视频请求反馈（含实时、回放）:CMD_DETU_CLIENT_REQUEST_LIVE_VIDEO_RES ********服务器反馈URL给客户端
		typedef struct api_detu_client_request_video_res
		{
			unsigned char 	szDeviceId[API_ARRAY_LEN];;		// 对应NVR的设备ID
			unsigned char 	szRtmpURL[API_RTMP_LEN];
			api_detu_client_request_video_res()
			{
				memset(&szDeviceId, 0, API_ARRAY_LEN);
				memset(&szRtmpURL, 0, API_RTMP_LEN);
			}
			void read(netbuffer_t* rb){
				readdata(this->szDeviceId, API_ARRAY_LEN, rb);
				readdata(this->szRtmpURL, API_RTMP_LEN, rb);
			}

			void write(netbuffer_t* wb){
				writedata(this->szDeviceId, API_ARRAY_LEN, wb);
				writedata(this->szRtmpURL, API_RTMP_LEN, wb);
			}
		}api_detu_client_request_video_res_t;

#pragma pack ()  // 取消指定对齐，恢复缺省对齐





		// 查询录像:CMD_DETU_CLIENT_RECORD_QUERY ********客户端到服务器
		typedef struct api_detu_client_record_query
		{
			unsigned char 	szDeviceId[API_ARRAY_LEN];;      //对应NVR的设备ID，用来通知服务器查询哪个设备的录像
			// 用于回放时间段请求
			unsigned int  	nStartTime;
			unsigned int  	nEndTime;
			api_detu_client_record_query()
			{
				memset(&szDeviceId, 0, API_ARRAY_LEN);
			}
			int get_size(){
				return sizeof(api_detu_client_record_query);
			}

			void read(netbuffer_t* rb)
			{
				readdata(this->szDeviceId, API_ARRAY_LEN, rb);
				read_uint(nStartTime, rb);
				read_uint(nEndTime, rb);
			}
			void write(netbuffer_t* wb)
			{
				writedata(this->szDeviceId, API_ARRAY_LEN, wb);
				write_uint(nStartTime, wb);
				write_uint(nEndTime, wb);
			}
		}api_detu_client_record_query_t;


		// 查询录像反馈:CMD_DETU_CLIENT_RECORD_QUERY_RES ********服务器到客户端
		typedef struct api_detu_client_record_query_res
		{
			// 录像时间段Unix时间戳
			unsigned int  	nStartTime;
			unsigned int  	nEndTime;

			api_detu_client_record_query_res()
			{
				nStartTime = 0;
				nEndTime = 0;
			}
			int get_size(){
				return sizeof(api_detu_client_record_query_res);
			}

			void read(netbuffer_t* rb){
				read_uint(this->nStartTime, rb);
				read_uint(this->nEndTime, rb);
			}

			void write(netbuffer_t* wb)
			{
				write_uint(this->nStartTime, wb);
				write_uint(this->nEndTime, wb);
			}
		}api_detu_client_record_query_res_t;

		// 查询录像:CMD_DETU_CLIENT_RECORD_QUERY ********客户端到服务器
		typedef struct api_detu_client_close_video
		{
			unsigned char szDeviceId[API_ARRAY_LEN];;      //对应NVR的设备ID，用来通知服务器查询哪个设备的录像

			api_detu_client_close_video()
			{
				memset(&szDeviceId, 0, API_ARRAY_LEN);
			}
			int get_size(){
				return sizeof(api_detu_client_close_video);
			}

			void read(netbuffer_t* rb)
			{
				readdata(this->szDeviceId, API_ARRAY_LEN, rb);
			}
			void write(netbuffer_t* wb)
			{
				writedata(this->szDeviceId, API_ARRAY_LEN, wb);
			}
		}api_detu_client_close_video_t;

		// 回放控制 : CMD_PLAYBACK_CONTROL
		typedef struct api_playback_control
		{
			unsigned char	nControlType;					// 控制类型，1：播放 2：暂停
			unsigned char	nSpeed;							// 速率控制，1：正常速度 2:2x 3:1/2x
			api_playback_control(){
				nControlType = 0;
				nSpeed = 0;
			}
			int get_size(){
				return sizeof(api_playback_control);
			}
			void read(netbuffer_t* rb)
			{
				read_uchar(this->nControlType, rb);
				read_uchar(this->nSpeed, rb);
			}
			void write(netbuffer_t* wb)
			{
				write_uchar(this->nControlType, wb);
				write_uchar(this->nSpeed, wb);
			}
		}api_playback_control_t;


		//回放控制接口
		typedef struct api_detu_client_replay_control
		{
			unsigned char 	szDeviceId[API_ARRAY_LEN];
			unsigned char nControlType;          //控制类型，1：播放、2：暂停
			unsigned char nSpeed;                     //仅用于播放，1：正常播放，2：2x，3：1/2x，4：4x，5：1/4x

			api_detu_client_replay_control(){
				memset(&szDeviceId, 0, API_ARRAY_LEN);
			}
			int get_size(){
				return sizeof(api_detu_client_replay_control);
			}
			void read(netbuffer_t* rb)
			{
				readdata(this->szDeviceId, API_ARRAY_LEN, rb);
				read_uchar(this->nControlType, rb);
				read_uchar(this->nSpeed, rb);
			}
			void write(netbuffer_t* wb)
			{
				writedata(this->szDeviceId, API_ARRAY_LEN, wb);
				write_uchar(this->nControlType, wb);
				write_uchar(this->nSpeed, wb);
			}
		}api_detu_client_replay_control_t;

		// 视频信息 : CMD_SET_AVPARAM CMD_GET_AVPARAM
		typedef struct api_av_param
		{
			unsigned short	nVideoHeight;					// 高度：仅支持3072*2048、1088*720、720*576
			unsigned short	nVideoWidth;					// 宽度
			unsigned short	nBitRate;						// 码率：主码流[2000, 8000]，子码流[500, 3000]
			unsigned char	nBitRateType;					// 码率类型：vbr、cbr
			unsigned char	nFrameRate;						// 帧率

			unsigned char	nQuality;						// 视频质量值
			unsigned char	nIFrameInterval;				// I帧步长
			unsigned char	nIFrameIntervalUnit;			// I帧间隔单位
			unsigned char	nVideoEncoderType;				// 视频编码类型
			unsigned char	nVideoEncodeLevel;				// 视频编码等级
			unsigned char	nAudioEncoderType;				// 音频编码类型
			api_av_param(){
				nVideoHeight = 0;
				nVideoWidth = 0;
				nBitRate = 0;
				nBitRateType = 0;
				nFrameRate = 0;

				nQuality = 0;
				nIFrameInterval = 0;
				nIFrameIntervalUnit = 0;
				nVideoEncoderType = 0;
				nVideoEncodeLevel = 0;
				nAudioEncoderType = 0;
			}
			int get_size(){
				return sizeof(api_av_param);
			}
			void read(netbuffer_t* rb)
			{
				read_ushort(this->nVideoHeight, rb);
				read_ushort(this->nVideoWidth, rb);
				read_ushort(this->nBitRate, rb);
				read_uchar(this->nBitRateType, rb);
				read_uchar(this->nFrameRate, rb);

				read_uchar(this->nQuality, rb);
				read_uchar(this->nIFrameInterval, rb);
				read_uchar(this->nIFrameIntervalUnit, rb);
				read_uchar(this->nVideoEncoderType, rb);
				read_uchar(this->nVideoEncodeLevel, rb);
				read_uchar(this->nAudioEncoderType, rb);
			}
			void write(netbuffer_t* wb)
			{
				write_ushort(this->nVideoHeight, wb);
				write_ushort(this->nVideoWidth, wb);
				write_ushort(this->nBitRate, wb);
				write_uchar(this->nBitRateType, wb);
				write_uchar(this->nFrameRate, wb);

				write_uchar(this->nQuality, wb);
				write_uchar(this->nIFrameInterval, wb);
				write_uchar(this->nIFrameIntervalUnit, wb);
				write_uchar(this->nVideoEncoderType, wb);
				write_uchar(this->nVideoEncodeLevel, wb);
				write_uchar(this->nAudioEncoderType, wb);
			}
		}api_av_param_t;

		//码率控制接口  
		typedef struct api_detu_client_av_param
		{
			unsigned char 	szDeviceId[API_ARRAY_LEN];
			unsigned short	nVideoHeight;					// 高度：仅支持3072*2048、1088*720、720*576
			unsigned short	nVideoWidth;					// 宽度
			unsigned short	nBitRate;						// 码率：主码流[2000, 8000]，子码流[500, 3000]
			unsigned char	nBitRateType;					// 码率类型：vbr、cbr
			unsigned char	nFrameRate;						// 帧率

			unsigned char	nQuality;						// 视频质量值
			unsigned char	nIFrameInterval;				// I帧步长
			unsigned char	nIFrameIntervalUnit;			// I帧间隔单位
			unsigned char	nVideoEncoderType;				// 视频编码类型
			unsigned char	nVideoEncodeLevel;				// 视频编码等级
			unsigned char	nAudioEncoderType;				// 音频编码类型
			api_detu_client_av_param(){
				memset(&szDeviceId, 0, API_ARRAY_LEN);
				nVideoHeight = 0;
				nVideoWidth = 0;
				nBitRate = 0;
				nBitRateType = 0;
				nFrameRate = 0;

				nQuality = 0;
				nIFrameInterval = 0;
				nIFrameIntervalUnit = 0;
				nVideoEncoderType = 0;
				nVideoEncodeLevel = 0;
				nAudioEncoderType = 0;
			}
			int get_size(){
				return sizeof(api_detu_client_av_param);
			}
			void read(netbuffer_t* rb)
			{
				readdata(this->szDeviceId, API_ARRAY_LEN, rb);
				read_ushort(this->nVideoHeight, rb);
				read_ushort(this->nVideoWidth, rb);
				read_ushort(this->nBitRate, rb);
				read_uchar(this->nBitRateType, rb);
				read_uchar(this->nFrameRate, rb);

				read_uchar(this->nQuality, rb);
				read_uchar(this->nIFrameInterval, rb);
				read_uchar(this->nIFrameIntervalUnit, rb);
				read_uchar(this->nVideoEncoderType, rb);
				read_uchar(this->nVideoEncodeLevel, rb);
				read_uchar(this->nAudioEncoderType, rb);
			}
			void write(netbuffer_t* wb)
			{
				writedata(this->szDeviceId, API_ARRAY_LEN, wb);
				write_ushort(this->nVideoHeight, wb);
				write_ushort(this->nVideoWidth, wb);
				write_ushort(this->nBitRate, wb);
				write_uchar(this->nBitRateType, wb);
				write_uchar(this->nFrameRate, wb);

				write_uchar(this->nQuality, wb);
				write_uchar(this->nIFrameInterval, wb);
				write_uchar(this->nIFrameIntervalUnit, wb);
				write_uchar(this->nVideoEncoderType, wb);
				write_uchar(this->nVideoEncodeLevel, wb);
				write_uchar(this->nAudioEncoderType, wb);
			}
		}api_detu_client_av_param_t;



		//磁盘容量接口

		typedef struct api_disk_info
		{
			unsigned char	nCurDiskNum;					// 当前磁盘序号
			unsigned char	nTotalDiskNum;					// 磁盘总数

			unsigned char	nDiskId;						// 磁盘Id号
			unsigned char	nDiskStatus;					// 磁盘状态，错误号参见 disk_status_e 结构
			unsigned char   nDiskType;						// 磁盘类型，错误号参见 disk_type_e 结构
			unsigned char	nReserver[3];					// 预留

			unsigned int	nTotalDiskSize;					// 磁盘总容量，单位：Mbyte
			unsigned int	nUsedSize;						// 磁盘已用容量，单位：Mbyte
			api_disk_info(){
				nCurDiskNum = 0;
				nTotalDiskNum = 0;
				nDiskId = 0;
				nDiskStatus = 0;
				nDiskType = 0;
				memset(&nReserver, 0, 3);
				nTotalDiskSize = 0;
				nUsedSize = 0;
			}
			int get_size(){
				return sizeof(api_disk_info);
			}
			void read(netbuffer_t* rb)
			{
				read_uchar(this->nCurDiskNum, rb);
				read_uchar(this->nTotalDiskNum, rb);
				read_uchar(this->nDiskId, rb);
				read_uchar(this->nDiskStatus, rb);
				read_uchar(this->nDiskType, rb);
				readdata(this->nReserver, 3, rb);
				read_uint(this->nTotalDiskSize, rb);
				read_uint(this->nUsedSize, rb);
			}
			void write(netbuffer_t* wb)
			{
				write_uchar(this->nCurDiskNum, wb);
				write_uchar(this->nTotalDiskNum, wb);
				write_uchar(this->nDiskId, wb);
				write_uchar(this->nDiskStatus, wb);
				write_uchar(this->nDiskType, wb);
				writedata(this->nReserver, 3, wb);
				write_uint(this->nTotalDiskSize, wb);
				write_uint(this->nUsedSize, wb);
			}
		}api_disk_info_t;

		typedef struct api_detu_client_disk_size
		{
			unsigned char szDeviceId[API_ARRAY_LEN];
			unsigned char	nCurDiskNum;					// 当前磁盘序号
			unsigned char	nTotalDiskNum;					// 磁盘总数

			unsigned char	nDiskId;						// 磁盘Id号
			unsigned char	nDiskStatus;					// 磁盘状态，错误号参见 disk_status_e 结构
			unsigned char   nDiskType;						// 磁盘类型，错误号参见 disk_type_e 结构
			unsigned char	nReserver[3];					// 预留

			unsigned int	nTotalDiskSize;					// 磁盘总容量，单位：Mbyte
			unsigned int	nUsedSize;						// 磁盘已用容量，单位：Mbyte
			api_detu_client_disk_size(){
				memset(&szDeviceId, 0, API_ARRAY_LEN);
				nCurDiskNum = 0;
				nTotalDiskNum = 0;
				nDiskId = 0;
				nDiskStatus = 0;
				nDiskType = 0;
				memset(&nReserver, 0, 3);
				nTotalDiskSize = 0;
				nUsedSize = 0;
			}
			int get_size(){
				return sizeof(api_detu_client_disk_size);
			}

			void copyto(api_detu_client_disk_size  &api){
				memcpy(api.szDeviceId, szDeviceId, API_ARRAY_LEN);

				api.nCurDiskNum = nCurDiskNum;
				api.nTotalDiskNum = nTotalDiskNum;
				api.nDiskId = nDiskId;
				api.nDiskStatus = nDiskStatus;
				api.nDiskType = nDiskType;


				memcpy(api.nReserver, szDeviceId, 3);
				api.nTotalDiskSize = nTotalDiskSize;
				api.nUsedSize = nUsedSize;
			}
			void read(netbuffer_t* rb)
			{
				readdata(this->szDeviceId, API_ARRAY_LEN, rb);
				read_uchar(this->nCurDiskNum, rb);
				read_uchar(this->nTotalDiskNum, rb);
				read_uchar(this->nDiskId, rb);
				read_uchar(this->nDiskStatus, rb);
				read_uchar(this->nDiskType, rb);
				readdata(this->nReserver, 3, rb);
				read_uint(this->nTotalDiskSize, rb);
				read_uint(this->nUsedSize, rb);
			}
			void write(netbuffer_t* wb)
			{
				writedata(this->szDeviceId, API_ARRAY_LEN, wb);
				write_uchar(this->nCurDiskNum, wb);
				write_uchar(this->nTotalDiskNum, wb);
				write_uchar(this->nDiskId, wb);
				write_uchar(this->nDiskStatus, wb);
				write_uchar(this->nDiskType, wb);
				writedata(this->nReserver, 3, wb);
				write_uint(this->nTotalDiskSize, wb);
				write_uint(this->nUsedSize, wb);
			}
		}api_detu_client_disk_size_t;

		//磁盘容量列表
		typedef struct api_detu_client_disk_size_list
		{
			short numlist;
			api_detu_client_disk_size_t diskList[MAX_NVR_LIST_NUM];


			api_detu_client_disk_size_list(){
				numlist = 0;
			}
			int get_size(){
				return  sizeof(api_detu_client_disk_size_list);
			}
			void read(netbuffer_t* rb){
				read_short(this->numlist, rb);

				for (int i = 0; i < this->numlist; i++)
				{
					readdata(this->diskList[i].szDeviceId, API_ARRAY_LEN, rb);
					read_uint(this->diskList[i].nTotalDiskSize, rb);
					read_uint(this->diskList[i].nUsedSize, rb);
					read_uchar(this->diskList[i].nCurDiskNum, rb);
					read_uchar(this->diskList[i].nTotalDiskNum, rb);
					read_uchar(this->diskList[i].nDiskId, rb);
					read_uchar(this->diskList[i].nDiskStatus, rb);
					read_uchar(this->diskList[i].nDiskType, rb);
					readdata(this->diskList[i].nReserver, 3, rb);
				}
			}
			void write(netbuffer_t* wb){
				write_short(this->numlist, wb);

				for (int i = 0; i < numlist; i++){
					writedata(this->diskList[i].szDeviceId, API_ARRAY_LEN, wb);
					write_uint(this->diskList[i].nTotalDiskSize, wb);
					write_uint(this->diskList[i].nUsedSize, wb);
					write_uchar(this->diskList[i].nCurDiskNum, wb);
					write_uchar(this->diskList[i].nTotalDiskNum, wb);
					write_uchar(this->diskList[i].nDiskId, wb);
					write_uchar(this->diskList[i].nDiskStatus, wb);
					write_uchar(this->diskList[i].nDiskType, wb);
					writedata(this->diskList[i].nReserver, 3, wb);
				}
			}

		}api_detu_client_disk_size_list_t;

		//APP注册 : CMD_DETU_TRANSCODING_REGISTER
		typedef struct api_detu_app_register
		{
			unsigned char 	pvsId[API_ARRAY_LEN];
			unsigned char 	appId[API_ARRAY_LEN];
			unsigned char 	szUserName[API_ARRAY_LEN];
			unsigned char 	szPassWord[API_ARRAY_LEN];

			api_detu_app_register(){
				memset(&pvsId, 0, API_ARRAY_LEN);
				memset(&appId, 0, API_ARRAY_LEN);
				memset(&szUserName, 0, API_ARRAY_LEN);
				memset(&szPassWord, 0, API_ARRAY_LEN);
			}

			int get_size(){
				return sizeof(api_detu_app_register);
			}

			void read(netbuffer_t* rb){
				readdata(this->pvsId, API_ARRAY_LEN, rb);
				readdata(this->appId, API_ARRAY_LEN, rb);
				readdata(this->szUserName, API_ARRAY_LEN, rb);
				readdata(this->szPassWord, API_ARRAY_LEN, rb);
			}

			void write(netbuffer_t* wb){
				writedata(this->pvsId, API_ARRAY_LEN, wb);
				writedata(this->appId, API_ARRAY_LEN, wb);
				writedata(this->szUserName, API_ARRAY_LEN, wb);
				writedata(this->szPassWord, API_ARRAY_LEN, wb);
			}
		}api_detu_app_register_t;

		// APP注册响应 : CMD_DETU_TRANSCODING_REGISTER_RES
		typedef struct api_detu_app_register_res
		{
			unsigned char 	szRtmpURL[API_RTMP_LEN];
			api_pts_file	pts;

			api_detu_app_register_res(){
				memset(&szRtmpURL, 0, API_RTMP_LEN);
			}

			int get_size(){
				return sizeof(api_detu_app_register_res);
			}

			void read(netbuffer_t* rb){
				readdata(this->szRtmpURL, API_RTMP_LEN, rb);
				pts.read(rb);
			}

			void write(netbuffer_t* wb){
				writedata(this->szRtmpURL, API_RTMP_LEN, wb);
				pts.write(wb);
			}
		}api_detu_app_register_res_t;

		typedef struct active_report_body
		{
			short nErrorCode;
			unsigned char 	pvsId[API_ARRAY_LEN];

			active_report_body(){
				nErrorCode = 0;
				memset(&pvsId, 0, API_ARRAY_LEN);
			}
			int get_size(){
				return sizeof(active_report_body);
			}
			void read(netbuffer_t* rb){
				read_short(this->nErrorCode, rb);
				readdata(this->pvsId, API_ARRAY_LEN, rb);
			}
			void write(netbuffer_t* wb){
				write_short(this->nErrorCode, wb);
				writedata(this->pvsId, API_ARRAY_LEN, wb);
			}
		}active_report_body_t;

		typedef struct PVSManageTable{
			unsigned char pvsID[API_ARRAY_LEN];
			unsigned int	nInputBandWidth;				// 输入带宽：M1 --> PVS，单位：Byte/s，3s均值
			unsigned int	nOuntputBandWidth;				// 输出带宽：PVS --> 流媒体服务器
			unsigned int	nStream1Status;					// 主码流状态：0表示四路不全正常，1表示不同步，2表示正常
			unsigned int	nStream2Status;					// 子码流状态，同上
			unsigned int	nCalibrationStatus;				// 标定信息状态：0表示成功，其他表示失败
			PVSManageTable(){
				memset(&pvsID, 0, API_ARRAY_LEN);
				nInputBandWidth = 0;
				nOuntputBandWidth = 0;
				nStream1Status = 0;
				nStream2Status = 0;
				nCalibrationStatus = 0;
			}
			int get_size(){
				return sizeof(PVSManageTable);
			}
			void read(netbuffer_t* rb){
				read_uint(this->nInputBandWidth, rb);
				read_uint(this->nOuntputBandWidth, rb);
				read_uint(this->nStream1Status, rb);
				read_uint(this->nStream2Status, rb);
				read_uint(this->nCalibrationStatus, rb);
				readdata(this->pvsID, API_ARRAY_LEN, rb);
			}
			void write(netbuffer_t* wb){
				write_uint(this->nInputBandWidth, wb);
				write_uint(this->nOuntputBandWidth, wb);
				write_uint(this->nStream1Status, wb);
				write_uint(this->nStream2Status, wb);
				write_uint(this->nCalibrationStatus, wb);
				writedata(this->pvsID, API_ARRAY_LEN, wb);
			}
		}PVSManageTable_t;

		typedef struct PTZManageTable
		{
			unsigned char pvsID[API_ARRAY_LEN];
			unsigned char username[API_ARRAY_LEN];
			unsigned char passwd[API_ARRAY_LEN];
			unsigned char nIP[API_ARRAY_LEN];
			unsigned short nPort;

			PTZManageTable(){
				memset(&pvsID, 0, API_ARRAY_LEN);
				memset(&username, 0, API_ARRAY_LEN);
				memset(&passwd, 0, API_ARRAY_LEN);
				memset(&nIP, 0, API_ARRAY_LEN);
				nPort = 0;
			}
			int get_size(){
				return sizeof(PTZManageTable);
			}
			void copyto(PTZManageTable  &api){
				memcpy(api.pvsID, pvsID, API_ARRAY_LEN);
				memcpy(api.username, username, API_ARRAY_LEN);
				memcpy(api.passwd, passwd, API_ARRAY_LEN);
				memcpy(api.nIP, nIP, API_ARRAY_LEN);
				api.nPort = nPort;
			}
			void read(netbuffer_t* rb){
				readdata(this->pvsID, API_ARRAY_LEN, rb);
				readdata(this->username, API_ARRAY_LEN, rb);
				readdata(this->passwd, API_ARRAY_LEN, rb);
				readdata(this->nIP, API_ARRAY_LEN, rb);
				read_ushort(this->nPort, rb);
			}
			void write(netbuffer_t* wb){
				writedata(this->pvsID, API_ARRAY_LEN, wb);
				writedata(this->username, API_ARRAY_LEN, wb);
				writedata(this->passwd, API_ARRAY_LEN, wb);
				writedata(this->nIP, API_ARRAY_LEN, wb);
				write_ushort(this->nPort, wb);
			}
		}PTZManageTable_t;

		typedef struct PTZManageTableList
		{
			short numlist;
			PTZManageTable_t ptzList[MAX_DEVICE_NUM];

			PTZManageTableList(){
				numlist = 0;
			}
			int get_size(){
				return  sizeof(PTZManageTableList);
			}
			void read(netbuffer_t* rb){
				read_short(this->numlist, rb);

				for (int i = 0; i < this->numlist; i++)
				{
					readdata(this->ptzList[i].pvsID, API_ARRAY_LEN, rb);
					readdata(this->ptzList[i].username, API_ARRAY_LEN, rb);
					readdata(this->ptzList[i].passwd, API_ARRAY_LEN, rb);
					readdata(this->ptzList[i].nIP, API_ARRAY_LEN, rb);
					read_ushort(this->ptzList[i].nPort, rb);
				}
			}
			void write(netbuffer_t* wb){
				write_short(this->numlist, wb);

				for (int i = 0; i < numlist; i++){
					writedata(this->ptzList[i].pvsID, API_ARRAY_LEN, wb);
					writedata(this->ptzList[i].username, API_ARRAY_LEN, wb);
					writedata(this->ptzList[i].passwd, API_ARRAY_LEN, wb);
					writedata(this->ptzList[i].nIP, API_ARRAY_LEN, wb);
					write_ushort(this->ptzList[i].nPort, wb);
				}
			}
		}PTZManageTableList_t;

		typedef struct SPYManageTable
		{
			unsigned char pvsID[API_ARRAY_LEN];
			unsigned char username[API_ARRAY_LEN];
			unsigned char passwd[API_ARRAY_LEN];
			unsigned char nIP[API_ARRAY_LEN];
			unsigned short nPort;
			short nPosX;
			short nPosY;

			SPYManageTable(){
				memset(&pvsID, 0, API_ARRAY_LEN);
				memset(&username, 0, API_ARRAY_LEN);
				memset(&passwd, 0, API_ARRAY_LEN);
				memset(&nIP, 0, API_ARRAY_LEN);
				nPort = 0;
				nPosX = -1;
				nPosY = -1;
			}
			int get_size(){
				return sizeof(SPYManageTable);
			}
			void copyto(SPYManageTable  &api){
				memcpy(api.pvsID, pvsID, API_ARRAY_LEN);
				memcpy(api.username, username, API_ARRAY_LEN);
				memcpy(api.passwd, passwd, API_ARRAY_LEN);
				memcpy(api.nIP, nIP, API_ARRAY_LEN);
				api.nPort = nPort;
				api.nPosX = nPosX;
				api.nPosY = nPosY;
			}
			void read(netbuffer_t* rb){
				readdata(this->pvsID, API_ARRAY_LEN, rb);
				readdata(this->username, API_ARRAY_LEN, rb);
				readdata(this->passwd, API_ARRAY_LEN, rb);
				readdata(this->nIP, API_ARRAY_LEN, rb);
				read_ushort(this->nPort, rb);
				read_short(this->nPosX, rb);
				read_short(this->nPosY, rb);
			}
			void write(netbuffer_t* wb){
				writedata(this->pvsID, API_ARRAY_LEN, wb);
				writedata(this->username, API_ARRAY_LEN, wb);
				writedata(this->passwd, API_ARRAY_LEN, wb);
				writedata(this->nIP, API_ARRAY_LEN, wb);
				write_ushort(this->nPort, wb);
				write_short(this->nPosX, wb);
				write_short(this->nPosY, wb);
			}
		}SPYManageTable_t;

		typedef struct SPYManageTableList
		{
			short numlist;
			SPYManageTable_t spyList[MAX_DEVICE_NUM];

			SPYManageTableList(){
				numlist = 0;
			}
			int get_size(){
				return  sizeof(SPYManageTableList);
			}
			void read(netbuffer_t* rb){
				read_short(this->numlist, rb);

				for (int i = 0; i < this->numlist; i++)
				{
					readdata(this->spyList[i].pvsID, API_ARRAY_LEN, rb);
					readdata(this->spyList[i].username, API_ARRAY_LEN, rb);
					readdata(this->spyList[i].passwd, API_ARRAY_LEN, rb);
					readdata(this->spyList[i].nIP, API_ARRAY_LEN, rb);
					read_ushort(this->spyList[i].nPort, rb);
					read_short(this->spyList[i].nPosX, rb);
					read_short(this->spyList[i].nPosY, rb);
				}
			}
			void write(netbuffer_t* wb){
				write_short(this->numlist, wb);

				for (int i = 0; i < numlist; i++){
					writedata(this->spyList[i].pvsID, API_ARRAY_LEN, wb);
					writedata(this->spyList[i].username, API_ARRAY_LEN, wb);
					writedata(this->spyList[i].passwd, API_ARRAY_LEN, wb);
					writedata(this->spyList[i].nIP, API_ARRAY_LEN, wb);
					write_ushort(this->spyList[i].nPort, wb);
					write_short(this->spyList[i].nPosX, wb);
					write_short(this->spyList[i].nPosY, wb);
				}
			}
		}SPYManageTableList_t;

		typedef struct PtzPoint{
			unsigned char nIP[API_ARRAY_LEN];
			unsigned char nPoint[API_ARRAY_LEN];
			PtzPoint(){
				memset(&nIP, 0, API_ARRAY_LEN);
				memset(&nPoint, 0, API_ARRAY_LEN);
			}
			int get_size(){
				return  sizeof(PtzPoint);
			}
			void read(netbuffer_t* rb){
				readdata(this->nIP, API_ARRAY_LEN, rb);
				readdata(this->nPoint, API_ARRAY_LEN, rb);
			}
			void write(netbuffer_t* wb){
				writedata(this->nIP, API_ARRAY_LEN, wb);
				writedata(this->nPoint, API_ARRAY_LEN, wb);
			}
		}PtzPoint_t;

		// CMD_DETU_TCS_REGISTER, 注册, TCS发往服务器
		typedef struct api_detu_tcs_register
		{
			unsigned char	szTcsIp[API_ARRAY_LEN];	//TCS服务IP
			unsigned int	nPort;					//TCS监听端口
			unsigned int	nServerId;				//TCS服务ID(分布式)
			unsigned int	nLimits;				//TCS服务转码路数限制
			unsigned int	nHeartbeatInterval;		// 心跳间隔	

			api_detu_tcs_register() {
				memset(&szTcsIp, 0, API_ARRAY_LEN);
				nPort = 0;
				nServerId = 0;
				nLimits = 0;
				nHeartbeatInterval = 0;
			}

			int get_size() {
				return sizeof(api_detu_tcs_register);
			}

			void read(netbuffer_t* rb) {
				readdata(this->szTcsIp, API_ARRAY_LEN, rb);
				read_uint(this->nPort, rb);
				read_uint(this->nServerId, rb);
				read_uint(this->nLimits, rb);
				read_uint(this->nHeartbeatInterval, rb);
			}

			void write(netbuffer_t* wb) {
				writedata(this->szTcsIp, API_ARRAY_LEN, wb);
				write_uint(this->nPort, wb);
				write_uint(this->nServerId, wb);
				write_uint(this->nLimits, wb);
				write_uint(this->nHeartbeatInterval, wb);
			}
		}api_detu_tcs_register_t;



		// CMD_DETU_TCS_HEARTBEAT，心跳, TCS发往服务器
		typedef struct api_detu_tcs_heartbeat
		{
			unsigned int	nServerId;				//TCS服务ID(分布式)
			unsigned int	nLimits;				//TCS服务转码路数限制
			unsigned int	nCAU;					//TCS当前转码路数

			api_detu_tcs_heartbeat() {
				nServerId = 0;
				nLimits = 0;
				nCAU = 0;
			}

			int get_size() {
				return sizeof(api_detu_tcs_heartbeat);
			}

			void read(netbuffer_t* rb) {
				read_uint(this->nServerId, rb);
				read_uint(this->nLimits, rb);
				read_uint(this->nCAU, rb);
			}

			void write(netbuffer_t* wb) {
				write_uint(this->nServerId, wb);
				write_uint(this->nLimits, wb);
				write_uint(this->nCAU, wb);
			}
		}api_detu_tcs_heartbeat_t;


		// CMD_DETU_TCS_TRANSCODE, 转码, 客户端发往TCS
		typedef struct api_detu_tcs_transcode
		{
			unsigned char szRtmpURL[API_URL_LEN];      //rtmp推流地址
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

			api_detu_tcs_transcode() {
				memset(&szRtmpURL, 0, API_URL_LEN);
				memset(&szDeviceId, 0, API_ARRAY_LEN);
				nDeviceId = 0;

				nStreamType = 0;
				nFps = 0;
				nbitrate = 0;
				nWidth = 0;
				nHeight = 0;

				nStartTime = 0;
				nEndTime = 0;

				nPtsLen = 0;
				memset(&pts_data, 0, API_PTS_LEN);
			}

			int get_size() {
				return sizeof(api_detu_tcs_transcode);
			}

			void read(netbuffer_t* rb) {
				readdata(this->szRtmpURL, API_URL_LEN, rb);
				readdata(this->szDeviceId, API_ARRAY_LEN, rb);
				read_uchar(this->nDeviceId, rb);

				read_uchar(this->nStreamType, rb);
				read_uchar(this->nFps, rb);
				read_uint(this->nbitrate, rb);
				read_uint(this->nWidth, rb);
				read_uint(this->nHeight, rb);

				read_uint(this->nStartTime, rb);
				read_uint(this->nEndTime, rb);

				read_uint(this->nPtsLen, rb);
				readdata(this->pts_data, API_PTS_LEN, rb);
			}

			void write(netbuffer_t* wb) {
				writedata(this->szRtmpURL, API_URL_LEN, wb);
				writedata(this->szDeviceId, API_ARRAY_LEN, wb);
				write_uchar(this->nDeviceId, wb);

				write_uchar(this->nStreamType, wb);
				write_uchar(this->nFps, wb);
				write_uint(this->nbitrate, wb);
				write_uint(this->nWidth, wb);
				write_uint(this->nHeight, wb);

				write_uint(this->nStartTime, wb);
				write_uint(this->nEndTime, wb);

				write_uint(this->nPtsLen, wb);
				writedata(this->pts_data, API_PTS_LEN, wb);
			}
		}api_detu_tcs_transcode_t;

		// CMD_DETU_TCS_TRANSCODE_RES, 转码响应消息，TCS发往客户端
		typedef struct api_detu_tcs_transcode_res
		{
			unsigned char szDeviceId[API_ARRAY_LEN];      //对应NVR的设备ID

			api_detu_tcs_transcode_res() {
				memset(&szDeviceId, 0, API_ARRAY_LEN);
			}

			int get_size() {
				return sizeof(api_detu_tcs_transcode_res);
			}

			void read(netbuffer_t* rb) {
				readdata(this->szDeviceId, API_ARRAY_LEN, rb);
			}

			void write(netbuffer_t* wb) {
				writedata(this->szDeviceId, API_ARRAY_LEN, wb);
			}
		}api_detu_tcs_transcode_res_t;

		//地图在线设备结构体
		typedef struct api_detu_vr_map_device_point
		{
			short			id;
			unsigned char	deviceName[API_ARRAY_LEN];
			unsigned char	szDeviceId[API_ARRAY_LEN];
			unsigned char	m1DeviceId[API_ARRAY_LEN];
			short			is_up_down;
			short			status;

			api_detu_vr_map_device_point()
			{
				id = -1;
				memset(&deviceName, 0, API_ARRAY_LEN);
				memset(&szDeviceId, 0, API_ARRAY_LEN);
				memcpy(&m1DeviceId, "default", API_ARRAY_LEN);
				is_up_down = 0;
				status = 0;
			}
			int get_size() {
				return sizeof(api_detu_vr_map_device_point);
			}
			void read(netbuffer_t* rb) {
				read_short(this->id, rb);
				readdata(this->deviceName, API_ARRAY_LEN, rb);
				readdata(this->szDeviceId, API_ARRAY_LEN, rb);
				readdata(this->m1DeviceId, API_ARRAY_LEN, rb);
				read_short(this->is_up_down, rb);
				read_short(this->status, rb);
			}
			void write(netbuffer_t* wb) {
				write_short(this->id, wb);
				writedata(this->deviceName, API_ARRAY_LEN, wb);
				writedata(this->szDeviceId, API_ARRAY_LEN, wb);
				writedata(this->m1DeviceId, API_ARRAY_LEN, wb);
				write_short(this->is_up_down, wb);
				write_short(this->status, wb);
			}
		}api_detu_vr_map_device_point_t;

		//地图场景结构体
		typedef struct api_detu_vr_map_scene_point
		{
			short			id;
			unsigned char	sceneName[API_ARRAY_LEN];
			unsigned char	scenePath[API_MAP_PATH];
			//unsigned char sceneData[API_ARRAY_LEN];	
			//PanoSceneInfo	sceneList[MAX_NVR_LIST_NUM];
			short			is_up_down;;

			api_detu_vr_map_scene_point()
			{
				id = 0;
				memset(&sceneName, 0, API_ARRAY_LEN);
				memset(&scenePath, 0, API_MAP_PATH);
				is_up_down = 0;
			}
			int get_size() {
				return sizeof(api_detu_vr_map_scene_point);
			}
			void read(netbuffer_t* rb) {
				read_short(this->id, rb);
				readdata(this->sceneName, API_ARRAY_LEN, rb);
				readdata(this->scenePath, API_MAP_PATH, rb);
				read_short(this->is_up_down, rb);
			}
			void write(netbuffer_t* wb) {
				write_short(this->id, wb);
				writedata(this->sceneName, API_ARRAY_LEN, wb);
				writedata(this->scenePath, API_ARRAY_LEN, wb);
				write_short(this->is_up_down, wb);
			}
		}api_detu_vr_map_scene_point_t;

		typedef struct sequencer_vecter
		{
			short 	vector_x;
			short	vector_y;

			sequencer_vecter()
			{
				vector_x = 0;
				vector_y = 0;
			}
			int get_size(){
				return  sizeof(sequencer_vecter);
			}
			void read(netbuffer_t* rb) {
				read_short(this->vector_x, rb);
				read_short(this->vector_y, rb);
			}
			void write(netbuffer_t* wb) {
				write_short(this->vector_x, wb);
				write_short(this->vector_y, wb);
			}
		}sequencer_vecter_t;



		//地图点结构体
		typedef struct api_detu_vr_map_point
		{
			short curr_id;
			short prev_id;
			sequencer_vecter_t prev_vector;
			short next_id;
			sequencer_vecter_t next_vector;
			short onMapFlag;
			short map_point_type;
			short pos_x;
			short pos_y;
			api_detu_vr_map_device_point_t		cameraInfo;
			api_detu_vr_map_scene_point_t		sceneInfo;

			api_detu_vr_map_point()
			{
				curr_id = -1;
				prev_id = -1;
				next_id = -1;
				onMapFlag = -1;
				map_point_type = -1;
				pos_x = 0;
				pos_y = 0;
			}
			int get_size(){
				return  sizeof(api_detu_vr_map_point);
			}
			void read(netbuffer_t* rb) {
				read_short(this->curr_id, rb);
				read_short(this->prev_id, rb);
				prev_vector.read(rb);
				read_short(this->next_id, rb);
				next_vector.read(rb);
				read_short(this->onMapFlag, rb);
				read_short(this->map_point_type, rb);
				read_short(this->pos_x, rb);
				read_short(this->pos_y, rb);
				cameraInfo.read(rb);
				sceneInfo.read(rb);

			}
			void write(netbuffer_t* wb) {
				write_short(this->curr_id, wb);
				write_short(this->prev_id, wb);
				prev_vector.write(wb);
				write_short(this->next_id, wb);
				next_vector.read(wb);
				write_short(this->onMapFlag, wb);
				write_short(this->map_point_type, wb);
				write_short(this->pos_x, wb);
				write_short(this->pos_y, wb);
				cameraInfo.write(wb);
				sceneInfo.write(wb);
			}

		}api_detu_vr_map_point_t;


		// 地图数据结构体
		typedef struct api_detu_vr_map_data
		{
			short				curr_num;			//当前
			short				total_num;			//地图总数

			unsigned char mapName[API_ARRAY_LEN];      //地图名字
			unsigned char mapPath[API_MAP_PATH];      //对应文件夹路径
			//unsigned char mapData[API_ARRAY_LEN];    //地图数据


			short point_num;
			api_detu_vr_map_point_t mapPoint[MAX_NVR_LIST_NUM];

			api_detu_vr_map_data() {
				curr_num = 0;
				total_num = 0;
				memset(&mapName, 0, API_ARRAY_LEN);
				memset(&mapPath, 0, API_ARRAY_LEN);
				point_num = 0;
			}

			int get_size() {
				return sizeof(api_detu_vr_map_data);
			}

			void read(netbuffer_t* rb) {
				read_short(this->curr_num, rb);
				read_short(this->total_num, rb);
				readdata(this->mapName, API_ARRAY_LEN, rb);
				readdata(this->mapPath, API_ARRAY_LEN, rb);
				read_short(this->point_num, rb);
				for (int i = 0; i < point_num; i++)
				{
					mapPoint[i].read(rb);
				}
			}

			void write(netbuffer_t* wb) {
				write_short(this->curr_num, wb);
				write_short(this->total_num, wb);
				writedata(this->mapName, API_ARRAY_LEN, wb);
				writedata(this->mapPath, API_ARRAY_LEN, wb);
				write_short(this->point_num, wb);
				for (int i = 0; i < point_num; i++)
				{
					mapPoint[i].write(wb);
				}

			}
		}api_detu_vr_map_data_t;

		// 地图列表
		typedef struct api_detu_vr_map_data_list
		{
			short numlist;
			api_detu_vr_map_data_t maplist[MAX_NVR_LIST_NUM];
			api_detu_vr_map_data_list()	{
				numlist = 0;
			}
			int get_size() {
				return sizeof(api_detu_vr_map_data_list);
			}
			void read(netbuffer_t* rb) {
				read_short(this->numlist, rb);

				for (int i = 0; i < this->numlist; i++)
				{
					maplist[i].read(rb);
				}
			}
			void write(netbuffer_t* wb) {
				write_short(this->numlist, wb);
				for (int i = 0; i < numlist; i++){
					maplist[i].write(wb);
				}
			}
		}api_detu_vr_map_data_list_t;

		// 地图数据块
		typedef struct api_detu_vr_map_data_block
		{
			unsigned int length;
			unsigned int offset;
			unsigned char data[API_MAP_DATA_BLOCK_LEN];

			api_detu_vr_map_data_block()	{
				length = 0;
				offset = 0;
				memset(&data, 0, API_MAP_DATA_BLOCK_LEN);
			}
			int get_size() {
				return sizeof(api_detu_vr_map_data_block);
			}
			void read(netbuffer_t* rb) {
				read_uint(this->length, rb);
				read_uint(this->offset, rb);
				readdata(this->data, API_MAP_DATA_BLOCK_LEN, rb);
			}

			void write(netbuffer_t* wb) {
				write_uint(this->length, wb);
				write_uint(this->offset, wb);
				writedata(this->data, API_MAP_DATA_BLOCK_LEN, wb);
			}

		}api_detu_vr_map_data_block_t;

	}  // namespace server
}  // namespace dem1