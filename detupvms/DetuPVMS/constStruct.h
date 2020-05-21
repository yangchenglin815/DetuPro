//解决类型重定义
#pragma once

#include <QString>
#include <QVariant>
#include <QDir>
#include <QVector>
#include <QTime>

#include "HCNetSDK.h"
#include "GeneralDef.h"
#include "dem1server/APIProtocol.h"

#define SERVER_IP "192.168.1.99"
#define SERVER_PORT 8088
#define RMTP_IP "rtmp://192.168.1.95/1/0"
#define  PanoVMS_UPDATE_URL "http://oss-static.detu.com/install/DeSoftVersion.txt"

#define CAPTURE_PANO_WIDTH	4096
#define CAPTURE_PANO_HEIGHT 2048

#define MASK_WIDTH	2880
#define MASK_HEIGHT 1440

const int CLIENT_VERSION = 2210;
const QString CLIENT_VERSION_NO = "2.2.2";
const QString VERSION_CREATETIME = "2018-06-21";
const QString IniPath = QDir::homePath() + "/AppData/Local/Pano-VMS/flv/";
const int GLWINDOW_NUM = 4;

const QString temp_data_base = "001:000100000000001:000100000000002:000100000000003\n"
"001:000200000000001:000200000000002:000200000000003\n"
"001:000300000000001:000300000000002:000300000000003\n"
"001:000400000000001:000400000000002:000400000000003\n"
"001:000500000000001:000500000000002:000500000000003\n"
"001:000600000000001:000500000000002:000600000000003\n";



//VR地图模块状态
typedef enum MapPageState
{
	COMMON_STATE = 0,
	LINK_PATH_STATE = 1,
	CREATE_PATH = 2,
};


//区分预览界面和控制界面
typedef enum MapType
{
	MAP_CONTROL,							//地图控制界面
	MAP_PREVIEW,						    //地图预览界面
};

//地图点信息
typedef enum MapPointType
{
	PANOSCENE_ON_LINE = 0,					//场景在线		
	PANOSCENE_OFF_LINE = 1,					//场景离线
	DEVICE_ON_LINE,							//相机在线
	DEVICE_OFF_LINE,						//相机离线
};

typedef enum ADDDLGTYPE
{
	ADDPANORAMA = 1,         //添加全景
};

typedef enum _ACTIVE_REPORT
{
	RESULT_SUCCESS = 0,		// 成功	
	RESULT_FAILED = -1,		// 失败

	RESULT_SYNC_OK = 10005,	// 同步成功
	RESULT_ONLINE_OK = 10006,	// M1四个通道都在线

	RESULT_NOTSUPPORT = -10000,	// 不支持
	RESULT_UNKNOWCMD = -10001,	// 未知指令
	RESULT_NODATA = -10002,	// 无数据
	RESULT_NOTREGISTER = -10003,	// 未注册
	RESULT_PARAM_ERR = -10004,	// 参数错误
	RESULT_SYNC_ERR = -10005,	// 同步失败
	RESULT_ONLINE_ERR = -10006,	// M1一个或多个不在线
	RESULT_SEND_ERR = -10007,	// 发送数据失败
	RESULT_CONNECT_ERR = -10008,	// 连接流媒体服务器失败

	RESULT_USERNAMEERR = -11001,	// 用户名错误
	RESULT_PWDERR = -11002,	// 密码错误
	RESULT_REDEVICEID = -11003,	// 设备ID重复
	RESULT_CALIBRATIONERR = -11004,	// 标定信息错误
};

//异常状态码
typedef enum _PLAY_ERROR
{
	PLAY_ERROR = 0,
	PLAY_COMPLETE = 1,
	STREAM_ERROR = 2,
	LOW_SCORE = 3,
	CREATE_FILE_FAILED = 4,
};

// 状态码
typedef enum _PLAY_STATUS
{
	PLAY_STATUS_PTS_WT_OK = 10,						// 处理正确

	PLAY_STATUS_PTS_WT_ERR,							// 处理错误

	PLAY_STATUS_CAPTURE_ERROR,						// 抓图失败

	PLAY_STATUS_PTS_WT_CREATING,					// 正在生成pts，wt

	PLAY_STATUS_PTS_WT_CREAT_FILE_ERROR,			// 生成文件夹错误

	PLAY_STATUS_PTS_WT_PTS_ERROR,					// 写入的pts文件错误

	PLAY_STATUS_M1_PLAYER_SERVER_TYPE = 100,		// 连接服务器错误

	PLAY_STATUS_M1_PLAYER_STREAM_TYPE,				// 连接流错误

	PLAY_STATUS_M1_PLAYER_INIT_FFMPEG_TYPE,			// 初始化ffmpeg错误

	PLAY_STATUS_REPUEST_SRS_STREAM,                 // 请求SRS

	PLAY_STATUS_REQUEST_SRS_ERROR,					//请求SRS异常

	PLAY_STATUS_SRS_NO_RESPONSE,					//SRS无响应

	PLAY_STATUS_GET_SRS_STREAM_ERR,					// 播放器拉流失败

	PLAY_STATUS_CALIBRATION_HIGH_SCORE,				// 客户端标定评分ok

	PLAY_STATUS_CALIBRATION_LOW_SCORE,				// 客户端标定评分过低，请重试或更新场景

	PLAY_STATUS_CALIBRATION_ERROR,				// 客户端标定评分出错

	PLAY_STATUS_CREATE_PTS_FAILED,					//生成PTS失败

	PLAY_STATUS_M1_ERROR,							//相机异常，获取PTS失败

	PLAY_STATUS_SOCKET_NO_RESPONSE,					//服务器无响应

	PLAY_STATUS_CHECK_STITCH_PARA,					//校验拼接参数

	PLAY_STATUS_CAPTURING,							//正在抓图

	PLAY_STATUS_OPTIMIZE,							//初次优化本地拼接模板

	PLAY_STATUS_OPTIMIZE_HIGH_SCORE,				// 客户端优化评分ok

	PLAY_STATUS_OPTIMIZE_LOW_SCORE,					// 客户端优化评分过低，请重试或更新场景

	PLAY_STATUS_OPTIMIZE_ERROR,						// 客户端优化评分出错

	PLAY_STATUS_CREAT_WT_MASK,						//正在生成wt、mask图片

	PLAY_STATUS_CLIENT_CALIBRATION,					//客户端重新标定中

	PLAY_STATUS_PVSID_ERROR,                         //未找到对应SRS的PVSID

	PLAY_STATUS_SERVER_ERROR,                     //通信服务器无响应

}PLAY_STATUS;

//拼接参数枚举
enum StitchStatus
{
	STITCH_STATUS_START = 0,			//初始状态	
	STITCH_STATUS_COMMUNICATION,		//通信状态
	STITCH_STATUS_GET_SRS,				//获取SRS回调状态			
	STITCH_STATUS_CHECK_PARA,
	STITCH_STATUS_CAPTURE,
	STITCH_STATUS_CREAT_PTS,			//获取SRS回调状态
	STITCH_STATUS_OPTIMIZE,				//拼接状态
	STITCH_STATUS_CREAT_WT,				//生成PTS
	STITCH_STATUS_CALIBRATION,			//标定
};

//页面选项
enum PageMode
{
	PREVIEW = 0,    //预览
	REPLAY = 1,     //回放
	MAP_PLAY	 = 2, 	//地图预览
	MAP_REPLAY = 3,   //地图回放
};

//绑定设备类型
enum DeviceType
{
	DEVICE_PTZ = 0,      //球机
	DEVICE_SPY = 1,      //枪机
};

//球机预置点位
enum PointPos
{
	POINT_ONE = 0,
	POINT_TWO = 1,
	POINT_THREE = 2,
	POINT_FOUR = 3,
	POINT_FINISH = 4,
};

//回放时间轴精度
enum DurationTime
{
	DURATION_HOUR = 1,
	DURATION_HALF_HOUR = 2,
	DURATION_TEN_MIN = 3,
	DURATION_MIN = 4,
	DURATION_TEN_SECOND = 5,
	DURATION_SECOND = 6,
};

enum DeviceDirection
{

	DIRECTION_TO_UP = 0,                    //方向朝上
	DIRECTION_TO_DOWN = 1,					//方向朝下
};

enum CamType
{
	HKSDK_TYPE = 0,                     //方向朝上
	ONVIF_TYPE = 1,					 //方向朝下
};


enum PlaySpeedType
{
	PLAY_FOR_REDUCE_QUADRUPLE = 1,
	PLAY_FOR_REDUCE_DOUBLE = 2,
	PLAY_FOR_NORMAL = 3,
	PLAY_FOR_DOUBLE = 4,
	//PLAY_FOR_QUADRUPLE = 5,
};

enum PlayStreamType
{
	REALTIME_PALY = 1,						//实时视频
	RE_PLAY,								//回放视频
};

enum SelectedGLWindow
{
	GLWINDOW0 = 0,
	GLWINDOW1 = 1,
	GLWINDOW2,
	GLWINDOW3,
	GLWINDOW4,
};




enum tipType{
	SERVER_UNCONNECT = 1,					//服务无响应
	PDF_NOTFOUND = 2,                       //PDF无法打开
	IMAGE_SAVE_SUCCESS = 3,					//图像保存成功
	IMAGE_SAVE_FAILED = 4,					//图像保存失败
	PLAY_REQUEST_FAILED = 5,				//預覽視頻請求失敗
	REPLAY_REQUEST_FAILED = 6,				//回放視頻請求失敗
	CAPTURE_SUCCESS = 7,					//截图成功
	CAPTURE_FAILED = 8,                     //截图失败
	SETTINGS_SUCCESS = 9,					//配置保存成功
	SETTINGS_FAILED = 10,                   //配置保存失败
	FORMAT_SUCCESS = 11,					//格式化成功
	FORMAT_FAILED = 12,                     //格式化失败
	WARN_BITRATE = 13,                      //碼率越界
	FORMAT_NULL = 14,                       //空格式化
	NULL_SELECTED = 15,						//空选择操作
	PTZ_BIND_SUCCESS = 16,					//球机绑定成功
	PTZ_BIND_FAILED = 17,					//球机绑定失败
	PTZ_NO_BIND = 18,                       //球机未绑定
	STREAM_HANDLE_FAILED = 19,				//流处理失败
	REBOOT_M1_FAILED = 20,					//重启M1失败
	OPT_MIZE_SUCCESS = 21,					//模板优化成功
	SRS_ERROR = 22,                                //SRS推流异常
	SPY_BIND_SUCCESS = 23,					//枪机绑定成功
	SPY_BIND_FAILED = 24,					//枪机绑定失败
	SPY_NO_BIND = 25,                         //未绑定枪机
	DELETE_PTZ_SUCCESS = 26,         //删除球机成功
	DELETE_PTZ_FAILED = 27,             //删除球机失败
	DELETE_SPY_SUCCESS = 28,         //删除枪机成功
	DELETE_SPY_FAILED = 29,             //删除枪机失败

	DEVICE_INFO_ERROR = 30,          //设备登录信息错误，枪球机先复用

	NOT_ADMIN = 31,
	SET_ADMIN = 32,
	SET_NOT_ADMIN = 33,

	SET_PRE_POINT_OK,			//预置点OK
	SET_GUN_CAM_POINT_OK,			//预置点OK

	WARN_ONE_STREAM,      //仅有一路主码流播放
	DEVICE_OFFLINE,                //设备离线
	WARN_SUBSTREAM_DELETED,     //子码流已删除警告

	TCS_SERVER_DISCONNECT_ERROR,    //转码服务异常断开
	TCS_SERVER_OFFLINE,    //转码服务离线
	TCS_TRANSCODE_SUCCESS,    //转码成功
	TCS_CLOSE_TRANSCODE_SUCCESS,   //关闭转码成功
	TCS_PULL_RTMP_ERROR,				// RTMP拉流失败
	TCS_PUSH_RTMP_ERROR,				// RTMP推流失败

	WAIT_PLAY = 1000,                             //等待播放画面
	STREAM_ERR = 1001,                        //拉流失败
	M1_WARNING = 1002,                     //m1异常
	CALIBRATION_LOW_SCORE = 1003,    //标定评分过低
	SRS_NO_RESPONSE = 1004,             //SRS无响应
	CREATE_PTS_FILE_FAILED = 1005,              //生成pts文件夾失敗

	NO_PREV_POINT,
	NO_NEXT_POINT,

	OFF_LINE_NO_PLAY,				//设备不在线，点击无效
	ROTATING_NO_SWITCH,				//旋转不可切换

	MAP_SAVE_OK,				//保存地图提示

	VERSION_CHECK_FAILED,		//版本匹配错误

	RFID_DETECTED,				//检测到RFID

};

//球机相关信息 
typedef struct PtzInfo
{
	int id;
	QString pvsID;
	QString sUserName;
	QString sPasswd;
	QString sIP;
	unsigned short wPort;
	QString m1Id;
}PtzInfo_t;
Q_DECLARE_METATYPE(PtzInfo)

//枪机相关信息
typedef struct SpyInfo
{
	int id;
	QString pvsID; 
	QString sUserName;
	QString sPasswd;
	QString sIP;
	unsigned short wPort;
	QString m1Id;
	float pos_x;			//直接保存经纬度
	float pos_y;
	SpyInfo()
	{
		pos_x = 0.0; 
		pos_y = 0.0;
	}
}SpyInfo_t;
Q_DECLARE_METATYPE(SpyInfo)

//磁盘相关信息
typedef struct DiskSizeInfo
{
	unsigned char	szDeviceId[API_ARRAY_LEN];
	unsigned char	nCurDiskNum;					// 当前磁盘序号
	unsigned char	nTotalDiskNum;					// 磁盘总数

	unsigned char	nDiskId;						// 磁盘Id号
	unsigned char	nDiskStatus;					// 磁盘状态，错误号参见 disk_status_e 结构
	unsigned char   nDiskType;						// 磁盘类型，错误号参见 disk_type_e 结构
	unsigned char	nReserver[3];					// 预留

	unsigned int	nTotalDiskSize;					// 磁盘总容量，单位：Mbyte
	unsigned int	nUsedSize;						// 磁盘已用容量，单位：Mbyte
}DiskSizeInfo_t;
Q_DECLARE_METATYPE(DiskSizeInfo)

typedef struct StreamParam
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

	StreamParam(){
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
}StreamParam_t;
Q_DECLARE_METATYPE(StreamParam)

//设备列表，从服务器获取
typedef struct deviceInfo
{
	int id;
	bool status;							// 在线状态   0：离线  1：在线
	QString name;							//别名
	QString serialNo;						//设备序列号
	QString m1DeviceId;						//M1序列号
	int usedRoom;							//已用空间
	int usingRoom;							//使用空间
	int is_up_down;							//安装方式
	unsigned char diskNum;					//硬盘个数
	bool bClicked;							//点击状态
	bool RbClicked;
	bool isFinal;							//是否是最后一个
	bool isPushFlow;                 //推流标志位
	QString szPushFlowUrl;
	QString nServerId;    //转码服务ID

	StreamParam av_param_t;      //码流信息
	QList<DiskSizeInfo_t> disk_info_list;   //磁盘信息列表
	QList<PtzInfo_t> m_PtzInfoList;         //绑定球机信息表
	QList<SpyInfo_t> m_SpyInfoList;			//绑定枪机信息表
	deviceInfo()
	{
		id = -1;
		name = "default";
		serialNo = "default";
		m1DeviceId = "default";
		usedRoom=-1;					
		usingRoom = -1;
		is_up_down = -1;
		
		bClicked=false;					
		RbClicked = false;
		isFinal = false;
		isPushFlow = false;

		disk_info_list.clear();
		m_PtzInfoList.clear();
		m_SpyInfoList.clear();
	}
	void clear()
	{
		id = -1;
		name = "default";
		serialNo = "default";
		m1DeviceId = "default";
		usedRoom = -1;
		usingRoom = -1;
		is_up_down = -1;

		bClicked = false;
		RbClicked = false;
		isFinal = false;
		isPushFlow = false;

		disk_info_list.clear();
		m_PtzInfoList.clear();
		m_SpyInfoList.clear();
	}
}deviceInfo_t;
Q_DECLARE_METATYPE(deviceInfo)

//全景场景列表，从文件夹获取
typedef struct PanoSceneInfo
{
	int id;
	int currPicIndex;
	QString name;                               //组名
	QString Path;                               //路径
	QString fileData;                           //文件数据
	QList<PanoSceneInfo> sceneList;				//文件列表
	int is_up_down;								//安装方式

	PanoSceneInfo()
	{
		id = -1;
		currPicIndex = 0;
		name = "default";
		is_up_down = 0;
	}
	void clear()
	{
		id = -1;
		currPicIndex = 0;
		name = "default";
		Path = "default";
		fileData = "default";
		sceneList.clear();
		is_up_down = 0;
	}
}PanoSceneInfo_t;
Q_DECLARE_METATYPE(PanoSceneInfo)

//记录地图点前项后项的方向向量
typedef struct SequencerPointInfo
{
	int id;
	float angle;


	SequencerPointInfo()
	{
		id = 0;
		angle = 0.0;
	}
	void clear()
	{
		id = 0;
		angle = 0.0;
	}
}SequencerPointInfo_t;
Q_DECLARE_METATYPE(SequencerPointInfo)




//地图设备列表，包括全景场景和实时设备列表
typedef struct PanoMapPointInfo
{
	int curr_id;

	//id,角度
	QMap<int, float> sequencer_point_info_map_;

	bool onMapFlag;
	MapPointType map_point_type;		
	float pos_x;
	float pos_y;

	float initial_angle;					//初始视角

	deviceInfo cameraInfo;
    PanoSceneInfo sceneInfo;
	PanoMapPointInfo()
	{
		curr_id = -1;

		sequencer_point_info_map_.clear();

		onMapFlag = false;		
		pos_x = 0.0;
		pos_y = 0.0;

		initial_angle = 0.0;

		cameraInfo.clear();
		sceneInfo.clear();
	}
	void clear()
	{
		curr_id = -1;

		sequencer_point_info_map_.clear();

		onMapFlag = false;
		pos_x = 0.0;
		pos_y = 0.0;

		initial_angle = 0.0;

		cameraInfo.clear();
		sceneInfo.clear();
	}
	//判断是否存在
	bool operator ==(const PanoMapPointInfo& info1)
	{
		if ((this->cameraInfo.name != "default"&&this->cameraInfo.name == info1.cameraInfo.name)
			|| (this->sceneInfo.name != "default"&&this->sceneInfo.name == info1.sceneInfo.name))
		{
			return true;
		}

		else
		{
			return false;
		}
	}
}PanoMapPointInfo_t;
Q_DECLARE_METATYPE(PanoMapPointInfo)


//存储前后两个VR地图点信息
typedef struct VRMapPointInfo
{
	PanoMapPointInfo previousPoint;
	PanoMapPointInfo nextPoint;
	QVector<QPointF> pointEnterArea;
	bool bSelected;
	VRMapPointInfo()
	{
		bSelected = 0;
	}
}VRMapPointInfo_t;
Q_DECLARE_METATYPE(VRMapPointInfo)

//map结构体,包含地图信息、地图设备列表
typedef struct  PanoMap
{
	int id;
	QString mapName;
	QString mapPath;
	QString mapData;
	QList<PanoMapPointInfo> panoramaList;
	QList<VRMapPointInfo> mapLinesList;
	PanoMap()
	{
		id = -1;
		mapName = "default";
		mapPath = "default";
		mapData = "default";
	}
	void clear()
	{
		id = -1;
		mapName = "default";
		mapPath = "default";
		mapData = "default";
		panoramaList.clear();
	}
}PanoMap_t;
Q_DECLARE_METATYPE(PanoMap)

typedef struct replayInfo
{
	int id;
	unsigned int startTime;
	unsigned int endTime;
}m_replayInfo;
Q_DECLARE_METATYPE(replayInfo)

typedef struct replayInfoList
{
	int id;
	int duration;
	QList<replayInfo> m_infoList;
}m_replayInfoList;
Q_DECLARE_METATYPE(replayInfoList)

//热点信息
typedef struct HotPointInfo
{

	QString name;						//热点名称
	int id;								//热点序号
	float x;							//初始x坐标
	float y;							//初始y坐标
	float yaw;							//初始经度
	float pitch;						//初始维度

}HotPointInfo_t;

//转码服务相关
typedef struct TCSManageInfo
{
	QString szDeviceId;
	QString szTcsIp;        //TCS服务IP
	quint16 nPort;           //TCS监听端口
	QString nServerId;      //TCS服务ID(分布式)
	int nLimits;                   //TCS服务转码路数限制
	int nCAU;                  //TCS当前转码路数
}TCSManageInfo_t;
Q_DECLARE_METATYPE(TCSManageInfo)

//RFID数据结构体
enum RFIDReaderType
{
	RFID_ERR = -1,
	DOOR = 0,
	WORKING_AREA = 1,
	DANGER_AREA = 2,
	STORAGE = 3,
};

enum RFIDMessageType
{
	MESSAGER = 0,
	INTRUDE_ALARM = 1,
};

//数据库rfid，保存人员信息
typedef struct RFIDData
{
	QString label_id;						//标签名字
	QString	helmet_id;						//头盔ID
	QString	cloth_id;						//衣服ID
	QString	glove_id;						//手套ID

	RFIDData()
	{
		label_id = "null";
		helmet_id = "null";
		cloth_id = "null";
		glove_id = "null";
	}

	void Init(QString labelid, QString helmetid, QString clothid, QString gloveid)
	{
		label_id = labelid;
		helmet_id = helmetid;
		cloth_id = clothid;
		glove_id = gloveid;
	}
}RFIDData_t;
Q_DECLARE_METATYPE(RFIDData)

//在线检测保留的rfid
typedef struct RFIDOnlineData
{
	QString label_id;						//标签名字
	RFIDReaderType rfid_reader_type;		//区分读写器位置
	RFIDMessageType message_type;			//通知类别，是报警、还是入侵还是通知
	QString	helmet_id;						//头盔ID
	QString	cloth_id;						//衣服ID
	QString	glove_id;						//手套ID
	int label_message_num;					//响应次数
	bool is_in;
	bool is_trained;

	QTime start_time;						//记录进入时间
	QTime end_time;							//记录出去时间

	RFIDOnlineData()
	{
		label_id = "null";
		helmet_id = "null";
		cloth_id = "null";
		glove_id = "null";
		label_message_num = -1;
		is_in = false;
		is_trained = false;
		start_time = QTime(0, 0, 0);
		end_time = QTime(0, 0, 0);
	}
	void clear()
	{
		label_id = "null";
		helmet_id = "null";
		cloth_id = "null";
		glove_id = "null";
		label_message_num = -1;
		is_in = false;
		is_trained = false;
		start_time = QTime(0, 0, 0);
		end_time = QTime(0, 0, 0);
	}

	void Init(QString labelid, QString helmetid, QString clothid, QString gloveid)
	{
		label_id = labelid;
		helmet_id = helmetid;
		cloth_id = clothid;
		glove_id = gloveid;
	}

	bool IsPackaged()
	{
		if (helmet_id != "null"&& cloth_id != "null"&&glove_id != "null")
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}RFIDOnlineData_t;
Q_DECLARE_METATYPE(RFIDOnlineData)

//传送到UI结构体
typedef struct RFIDToUi
{
	int label_id;						//标签名字
	int	helmet_id;						//头盔ID
	int	cloth_id;						//衣服ID
	int	glove_id;						//手套ID
	int rfid_redear_id;

	RFIDToUi()
	{
		label_id = -1;
		helmet_id = -1;
		cloth_id = -1;
		glove_id = -1;
		rfid_redear_id = -1;
	}

}RFIDToUi_t;
Q_DECLARE_METATYPE(RFIDToUi)

typedef struct DoorData
{
	int  enter_time;			//进时间
	int  out_time;				//出时间
	bool status;				//当前状态，0表示不在内部

}DoorData_t;
Q_DECLARE_METATYPE(DoorData)

typedef struct IntrudeData
{
	int  intrude_time;			//入侵次数
}IntrudeData_t;
Q_DECLARE_METATYPE(IntrudeData)



//目标点信息
typedef struct TargetInfo
{
	int  img_id;			//图片序号
	int  target_id;			//图片序号
	int  pos_x;			//坐标
	int  pos_y;
	int  w;			//宽高
	int  h;		

	TargetInfo()
	{
		img_id = -1;			//图片序号
		target_id = -1;			//图片序号
		pos_x = -1;		//坐标
		pos_y = -1;
		w = -1;			//宽高
		h = -1;
	}

}TargetInfo_t;
Q_DECLARE_METATYPE(TargetInfo)

