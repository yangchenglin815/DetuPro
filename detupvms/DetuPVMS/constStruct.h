//��������ض���
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



//VR��ͼģ��״̬
typedef enum MapPageState
{
	COMMON_STATE = 0,
	LINK_PATH_STATE = 1,
	CREATE_PATH = 2,
};


//����Ԥ������Ϳ��ƽ���
typedef enum MapType
{
	MAP_CONTROL,							//��ͼ���ƽ���
	MAP_PREVIEW,						    //��ͼԤ������
};

//��ͼ����Ϣ
typedef enum MapPointType
{
	PANOSCENE_ON_LINE = 0,					//��������		
	PANOSCENE_OFF_LINE = 1,					//��������
	DEVICE_ON_LINE,							//�������
	DEVICE_OFF_LINE,						//�������
};

typedef enum ADDDLGTYPE
{
	ADDPANORAMA = 1,         //���ȫ��
};

typedef enum _ACTIVE_REPORT
{
	RESULT_SUCCESS = 0,		// �ɹ�	
	RESULT_FAILED = -1,		// ʧ��

	RESULT_SYNC_OK = 10005,	// ͬ���ɹ�
	RESULT_ONLINE_OK = 10006,	// M1�ĸ�ͨ��������

	RESULT_NOTSUPPORT = -10000,	// ��֧��
	RESULT_UNKNOWCMD = -10001,	// δָ֪��
	RESULT_NODATA = -10002,	// ������
	RESULT_NOTREGISTER = -10003,	// δע��
	RESULT_PARAM_ERR = -10004,	// ��������
	RESULT_SYNC_ERR = -10005,	// ͬ��ʧ��
	RESULT_ONLINE_ERR = -10006,	// M1һ������������
	RESULT_SEND_ERR = -10007,	// ��������ʧ��
	RESULT_CONNECT_ERR = -10008,	// ������ý�������ʧ��

	RESULT_USERNAMEERR = -11001,	// �û�������
	RESULT_PWDERR = -11002,	// �������
	RESULT_REDEVICEID = -11003,	// �豸ID�ظ�
	RESULT_CALIBRATIONERR = -11004,	// �궨��Ϣ����
};

//�쳣״̬��
typedef enum _PLAY_ERROR
{
	PLAY_ERROR = 0,
	PLAY_COMPLETE = 1,
	STREAM_ERROR = 2,
	LOW_SCORE = 3,
	CREATE_FILE_FAILED = 4,
};

// ״̬��
typedef enum _PLAY_STATUS
{
	PLAY_STATUS_PTS_WT_OK = 10,						// ������ȷ

	PLAY_STATUS_PTS_WT_ERR,							// �������

	PLAY_STATUS_CAPTURE_ERROR,						// ץͼʧ��

	PLAY_STATUS_PTS_WT_CREATING,					// ��������pts��wt

	PLAY_STATUS_PTS_WT_CREAT_FILE_ERROR,			// �����ļ��д���

	PLAY_STATUS_PTS_WT_PTS_ERROR,					// д���pts�ļ�����

	PLAY_STATUS_M1_PLAYER_SERVER_TYPE = 100,		// ���ӷ���������

	PLAY_STATUS_M1_PLAYER_STREAM_TYPE,				// ����������

	PLAY_STATUS_M1_PLAYER_INIT_FFMPEG_TYPE,			// ��ʼ��ffmpeg����

	PLAY_STATUS_REPUEST_SRS_STREAM,                 // ����SRS

	PLAY_STATUS_REQUEST_SRS_ERROR,					//����SRS�쳣

	PLAY_STATUS_SRS_NO_RESPONSE,					//SRS����Ӧ

	PLAY_STATUS_GET_SRS_STREAM_ERR,					// ����������ʧ��

	PLAY_STATUS_CALIBRATION_HIGH_SCORE,				// �ͻ��˱궨����ok

	PLAY_STATUS_CALIBRATION_LOW_SCORE,				// �ͻ��˱궨���ֹ��ͣ������Ի���³���

	PLAY_STATUS_CALIBRATION_ERROR,				// �ͻ��˱궨���ֳ���

	PLAY_STATUS_CREATE_PTS_FAILED,					//����PTSʧ��

	PLAY_STATUS_M1_ERROR,							//����쳣����ȡPTSʧ��

	PLAY_STATUS_SOCKET_NO_RESPONSE,					//����������Ӧ

	PLAY_STATUS_CHECK_STITCH_PARA,					//У��ƴ�Ӳ���

	PLAY_STATUS_CAPTURING,							//����ץͼ

	PLAY_STATUS_OPTIMIZE,							//�����Ż�����ƴ��ģ��

	PLAY_STATUS_OPTIMIZE_HIGH_SCORE,				// �ͻ����Ż�����ok

	PLAY_STATUS_OPTIMIZE_LOW_SCORE,					// �ͻ����Ż����ֹ��ͣ������Ի���³���

	PLAY_STATUS_OPTIMIZE_ERROR,						// �ͻ����Ż����ֳ���

	PLAY_STATUS_CREAT_WT_MASK,						//��������wt��maskͼƬ

	PLAY_STATUS_CLIENT_CALIBRATION,					//�ͻ������±궨��

	PLAY_STATUS_PVSID_ERROR,                         //δ�ҵ���ӦSRS��PVSID

	PLAY_STATUS_SERVER_ERROR,                     //ͨ�ŷ���������Ӧ

}PLAY_STATUS;

//ƴ�Ӳ���ö��
enum StitchStatus
{
	STITCH_STATUS_START = 0,			//��ʼ״̬	
	STITCH_STATUS_COMMUNICATION,		//ͨ��״̬
	STITCH_STATUS_GET_SRS,				//��ȡSRS�ص�״̬			
	STITCH_STATUS_CHECK_PARA,
	STITCH_STATUS_CAPTURE,
	STITCH_STATUS_CREAT_PTS,			//��ȡSRS�ص�״̬
	STITCH_STATUS_OPTIMIZE,				//ƴ��״̬
	STITCH_STATUS_CREAT_WT,				//����PTS
	STITCH_STATUS_CALIBRATION,			//�궨
};

//ҳ��ѡ��
enum PageMode
{
	PREVIEW = 0,    //Ԥ��
	REPLAY = 1,     //�ط�
	MAP_PLAY	 = 2, 	//��ͼԤ��
	MAP_REPLAY = 3,   //��ͼ�ط�
};

//���豸����
enum DeviceType
{
	DEVICE_PTZ = 0,      //���
	DEVICE_SPY = 1,      //ǹ��
};

//���Ԥ�õ�λ
enum PointPos
{
	POINT_ONE = 0,
	POINT_TWO = 1,
	POINT_THREE = 2,
	POINT_FOUR = 3,
	POINT_FINISH = 4,
};

//�ط�ʱ���ᾫ��
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

	DIRECTION_TO_UP = 0,                    //������
	DIRECTION_TO_DOWN = 1,					//������
};

enum CamType
{
	HKSDK_TYPE = 0,                     //������
	ONVIF_TYPE = 1,					 //������
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
	REALTIME_PALY = 1,						//ʵʱ��Ƶ
	RE_PLAY,								//�ط���Ƶ
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
	SERVER_UNCONNECT = 1,					//��������Ӧ
	PDF_NOTFOUND = 2,                       //PDF�޷���
	IMAGE_SAVE_SUCCESS = 3,					//ͼ�񱣴�ɹ�
	IMAGE_SAVE_FAILED = 4,					//ͼ�񱣴�ʧ��
	PLAY_REQUEST_FAILED = 5,				//�A�[ҕ�lՈ��ʧ��
	REPLAY_REQUEST_FAILED = 6,				//�ط�ҕ�lՈ��ʧ��
	CAPTURE_SUCCESS = 7,					//��ͼ�ɹ�
	CAPTURE_FAILED = 8,                     //��ͼʧ��
	SETTINGS_SUCCESS = 9,					//���ñ���ɹ�
	SETTINGS_FAILED = 10,                   //���ñ���ʧ��
	FORMAT_SUCCESS = 11,					//��ʽ���ɹ�
	FORMAT_FAILED = 12,                     //��ʽ��ʧ��
	WARN_BITRATE = 13,                      //�a��Խ��
	FORMAT_NULL = 14,                       //�ո�ʽ��
	NULL_SELECTED = 15,						//��ѡ�����
	PTZ_BIND_SUCCESS = 16,					//����󶨳ɹ�
	PTZ_BIND_FAILED = 17,					//�����ʧ��
	PTZ_NO_BIND = 18,                       //���δ��
	STREAM_HANDLE_FAILED = 19,				//������ʧ��
	REBOOT_M1_FAILED = 20,					//����M1ʧ��
	OPT_MIZE_SUCCESS = 21,					//ģ���Ż��ɹ�
	SRS_ERROR = 22,                                //SRS�����쳣
	SPY_BIND_SUCCESS = 23,					//ǹ���󶨳ɹ�
	SPY_BIND_FAILED = 24,					//ǹ����ʧ��
	SPY_NO_BIND = 25,                         //δ��ǹ��
	DELETE_PTZ_SUCCESS = 26,         //ɾ������ɹ�
	DELETE_PTZ_FAILED = 27,             //ɾ�����ʧ��
	DELETE_SPY_SUCCESS = 28,         //ɾ��ǹ���ɹ�
	DELETE_SPY_FAILED = 29,             //ɾ��ǹ��ʧ��

	DEVICE_INFO_ERROR = 30,          //�豸��¼��Ϣ����ǹ����ȸ���

	NOT_ADMIN = 31,
	SET_ADMIN = 32,
	SET_NOT_ADMIN = 33,

	SET_PRE_POINT_OK,			//Ԥ�õ�OK
	SET_GUN_CAM_POINT_OK,			//Ԥ�õ�OK

	WARN_ONE_STREAM,      //����һ·����������
	DEVICE_OFFLINE,                //�豸����
	WARN_SUBSTREAM_DELETED,     //��������ɾ������

	TCS_SERVER_DISCONNECT_ERROR,    //ת������쳣�Ͽ�
	TCS_SERVER_OFFLINE,    //ת���������
	TCS_TRANSCODE_SUCCESS,    //ת��ɹ�
	TCS_CLOSE_TRANSCODE_SUCCESS,   //�ر�ת��ɹ�
	TCS_PULL_RTMP_ERROR,				// RTMP����ʧ��
	TCS_PUSH_RTMP_ERROR,				// RTMP����ʧ��

	WAIT_PLAY = 1000,                             //�ȴ����Ż���
	STREAM_ERR = 1001,                        //����ʧ��
	M1_WARNING = 1002,                     //m1�쳣
	CALIBRATION_LOW_SCORE = 1003,    //�궨���ֹ���
	SRS_NO_RESPONSE = 1004,             //SRS����Ӧ
	CREATE_PTS_FILE_FAILED = 1005,              //����pts�ļ��Aʧ��

	NO_PREV_POINT,
	NO_NEXT_POINT,

	OFF_LINE_NO_PLAY,				//�豸�����ߣ������Ч
	ROTATING_NO_SWITCH,				//��ת�����л�

	MAP_SAVE_OK,				//�����ͼ��ʾ

	VERSION_CHECK_FAILED,		//�汾ƥ�����

	RFID_DETECTED,				//��⵽RFID

};

//��������Ϣ 
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

//ǹ�������Ϣ
typedef struct SpyInfo
{
	int id;
	QString pvsID; 
	QString sUserName;
	QString sPasswd;
	QString sIP;
	unsigned short wPort;
	QString m1Id;
	float pos_x;			//ֱ�ӱ��澭γ��
	float pos_y;
	SpyInfo()
	{
		pos_x = 0.0; 
		pos_y = 0.0;
	}
}SpyInfo_t;
Q_DECLARE_METATYPE(SpyInfo)

//���������Ϣ
typedef struct DiskSizeInfo
{
	unsigned char	szDeviceId[API_ARRAY_LEN];
	unsigned char	nCurDiskNum;					// ��ǰ�������
	unsigned char	nTotalDiskNum;					// ��������

	unsigned char	nDiskId;						// ����Id��
	unsigned char	nDiskStatus;					// ����״̬������Ųμ� disk_status_e �ṹ
	unsigned char   nDiskType;						// �������ͣ�����Ųμ� disk_type_e �ṹ
	unsigned char	nReserver[3];					// Ԥ��

	unsigned int	nTotalDiskSize;					// ��������������λ��Mbyte
	unsigned int	nUsedSize;						// ����������������λ��Mbyte
}DiskSizeInfo_t;
Q_DECLARE_METATYPE(DiskSizeInfo)

typedef struct StreamParam
{
	unsigned short	nVideoHeight;					// �߶ȣ���֧��3072*2048��1088*720��720*576
	unsigned short	nVideoWidth;					// ���
	unsigned short	nBitRate;						// ���ʣ�������[2000, 8000]��������[500, 3000]
	unsigned char	nBitRateType;					// �������ͣ�vbr��cbr
	unsigned char	nFrameRate;						// ֡��

	unsigned char	nQuality;						// ��Ƶ����ֵ
	unsigned char	nIFrameInterval;				// I֡����
	unsigned char	nIFrameIntervalUnit;			// I֡�����λ
	unsigned char	nVideoEncoderType;				// ��Ƶ��������
	unsigned char	nVideoEncodeLevel;				// ��Ƶ����ȼ�
	unsigned char	nAudioEncoderType;				// ��Ƶ��������

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

//�豸�б��ӷ�������ȡ
typedef struct deviceInfo
{
	int id;
	bool status;							// ����״̬   0������  1������
	QString name;							//����
	QString serialNo;						//�豸���к�
	QString m1DeviceId;						//M1���к�
	int usedRoom;							//���ÿռ�
	int usingRoom;							//ʹ�ÿռ�
	int is_up_down;							//��װ��ʽ
	unsigned char diskNum;					//Ӳ�̸���
	bool bClicked;							//���״̬
	bool RbClicked;
	bool isFinal;							//�Ƿ������һ��
	bool isPushFlow;                 //������־λ
	QString szPushFlowUrl;
	QString nServerId;    //ת�����ID

	StreamParam av_param_t;      //������Ϣ
	QList<DiskSizeInfo_t> disk_info_list;   //������Ϣ�б�
	QList<PtzInfo_t> m_PtzInfoList;         //�������Ϣ��
	QList<SpyInfo_t> m_SpyInfoList;			//��ǹ����Ϣ��
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

//ȫ�������б����ļ��л�ȡ
typedef struct PanoSceneInfo
{
	int id;
	int currPicIndex;
	QString name;                               //����
	QString Path;                               //·��
	QString fileData;                           //�ļ�����
	QList<PanoSceneInfo> sceneList;				//�ļ��б�
	int is_up_down;								//��װ��ʽ

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

//��¼��ͼ��ǰ�����ķ�������
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




//��ͼ�豸�б�����ȫ��������ʵʱ�豸�б�
typedef struct PanoMapPointInfo
{
	int curr_id;

	//id,�Ƕ�
	QMap<int, float> sequencer_point_info_map_;

	bool onMapFlag;
	MapPointType map_point_type;		
	float pos_x;
	float pos_y;

	float initial_angle;					//��ʼ�ӽ�

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
	//�ж��Ƿ����
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


//�洢ǰ������VR��ͼ����Ϣ
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

//map�ṹ��,������ͼ��Ϣ����ͼ�豸�б�
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

//�ȵ���Ϣ
typedef struct HotPointInfo
{

	QString name;						//�ȵ�����
	int id;								//�ȵ����
	float x;							//��ʼx����
	float y;							//��ʼy����
	float yaw;							//��ʼ����
	float pitch;						//��ʼά��

}HotPointInfo_t;

//ת��������
typedef struct TCSManageInfo
{
	QString szDeviceId;
	QString szTcsIp;        //TCS����IP
	quint16 nPort;           //TCS�����˿�
	QString nServerId;      //TCS����ID(�ֲ�ʽ)
	int nLimits;                   //TCS����ת��·������
	int nCAU;                  //TCS��ǰת��·��
}TCSManageInfo_t;
Q_DECLARE_METATYPE(TCSManageInfo)

//RFID���ݽṹ��
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

//���ݿ�rfid��������Ա��Ϣ
typedef struct RFIDData
{
	QString label_id;						//��ǩ����
	QString	helmet_id;						//ͷ��ID
	QString	cloth_id;						//�·�ID
	QString	glove_id;						//����ID

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

//���߼�Ᵽ����rfid
typedef struct RFIDOnlineData
{
	QString label_id;						//��ǩ����
	RFIDReaderType rfid_reader_type;		//���ֶ�д��λ��
	RFIDMessageType message_type;			//֪ͨ����Ǳ������������ֻ���֪ͨ
	QString	helmet_id;						//ͷ��ID
	QString	cloth_id;						//�·�ID
	QString	glove_id;						//����ID
	int label_message_num;					//��Ӧ����
	bool is_in;
	bool is_trained;

	QTime start_time;						//��¼����ʱ��
	QTime end_time;							//��¼��ȥʱ��

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

//���͵�UI�ṹ��
typedef struct RFIDToUi
{
	int label_id;						//��ǩ����
	int	helmet_id;						//ͷ��ID
	int	cloth_id;						//�·�ID
	int	glove_id;						//����ID
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
	int  enter_time;			//��ʱ��
	int  out_time;				//��ʱ��
	bool status;				//��ǰ״̬��0��ʾ�����ڲ�

}DoorData_t;
Q_DECLARE_METATYPE(DoorData)

typedef struct IntrudeData
{
	int  intrude_time;			//���ִ���
}IntrudeData_t;
Q_DECLARE_METATYPE(IntrudeData)



//Ŀ�����Ϣ
typedef struct TargetInfo
{
	int  img_id;			//ͼƬ���
	int  target_id;			//ͼƬ���
	int  pos_x;			//����
	int  pos_y;
	int  w;			//���
	int  h;		

	TargetInfo()
	{
		img_id = -1;			//ͼƬ���
		target_id = -1;			//ͼƬ���
		pos_x = -1;		//����
		pos_y = -1;
		w = -1;			//���
		h = -1;
	}

}TargetInfo_t;
Q_DECLARE_METATYPE(TargetInfo)

