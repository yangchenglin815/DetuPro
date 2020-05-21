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
1�����ǿ���չ��
2������ת��ʱ����unsigned
********************************************/

// �����
typedef enum
{
	CMD_REGISTER = 1,		// ע��
	CMD_REGISTER_RES = 2,	// ע����Ӧ

	CMD_UNREGISTER = 3,		// ע��
	CMD_UNREGISTER_RES = 4,	// ע����Ӧ

	CMD_HEART_BEAT = 5,		// ����
	CMD_HEART_BEAT_RES = 6,	// ������Ӧ

	CMD_REQUEST_VIDEO = 7,			// ��Ƶ���󣨰���ʵʱ���ط�����
	CMD_REQUEST_VIDEO_RES = 8,		// ��Ƶ������Ӧ

	CMD_PLAYBACK_CONTROL = 9,		// �طſ���
	CMD_PLAYBACK_CONTROL_RES = 10,	// �طſ�����Ӧ

	CMD_CLOSE_VIDEO = 11,			// �ر���Ƶ�Ự
	CMD_CLOSE_VIDEO_RES = 12,		// �ر���Ƶ������Ӧ

	CMD_RECORD_QUERY = 13,			// ¼���ѯ
	CMD_RECORD_QUERY_RES = 14,		// ¼���ѯ��Ӧ

	CMD_SET_AVPARAM = 15,			// ������Ƶ����
	CMD_SET_AVPARAM_RES = 16,		// ������Ӧ

	CMD_GET_AVPARAM = 17,			// ��ȡ��Ƶ����
	CMD_GET_AVPARAM_RES = 18,		// ��ȡ��Ӧ

	CMD_DISK_FORMAT = 19,			// ��ʽ������
	CMD_DISK_FORMAT_RES = 20,		// ��ʽ����Ӧ

	CMD_GET_DISKINFO = 21,			// ��ȡȫ��������Ϣ�����ṩ������
	CMD_GET_DISKINFO_RES = 22,		// ��ȡ������Ϣ��Ӧ

	CMD_STREAM_HANDLE_RES = 23,		//��������Ӧ��api_protocol_head_t�ṹ��nStreamIdΪ1����ʾstream1��2��ʾstream2��3��ʾstream1+stream2
	CMD_ADD_STREAM = 24,			//��������ͬ��
	CMD_DEL_STREAM = 25,			//ɾ������ͬ��
	CMD_GET_STREAM = 26,			//��ȡ��ǰ����ͬ��

	CMD_DEVICE_RESTART = 27,		//�豸������api_protocol_head_t�ṹ����nStreamIdΪ1����ʾ����M1��2��ʾ����NVR
	CMD_DEVICE_RESTART_RES = 28,	//�豸������Ӧ

	CMD_GET_CALIBRATION = 29,		// ��ȡ�궨��Ϣ
	CMD_GET_CALIBRATION_RES = 30,	// ��ȡ�궨��Ϣ��Ӧ

	CMD_GET_RECORD_CALIBRATION = 31,		// ��ȡ�ط�ʱ��α궨��Ϣ
	CMD_GET_RECORD_CALIBRATION_RES = 32,	// ��ȡ�ط�ʱ��α궨��Ϣ��Ӧ

	CMD_ACTIVE_REPORT = 100,				// �����ϱ�

    CMD_DETU_CLIENT_REGISTER = 2001,		//��ͼע��
    CMD_DETU_CLIENT_REGISTER_RES,

	CMD_DETU_CLIENT_HEART_BEAT,				// ����
	CMD_DETU_CLIENT_HEART_BEAT_RES,

    CMD_DETU_CLIENT_REQUEST_VIDEO,			// ����ʵʱ��Ƶ������ʵʱ���ط�����
    CMD_DETU_CLIENT_REQUEST_VIDEO_RES,

	CMD_DETU_CLIENT_PLAYBACK_CONTROL,		//�طſ���
	CMD_DETU_CLIENT_PLAYBACK_CONTROL_RES,	//�طſ�����Ӧ

    CMD_DETU_CLIENT_RECORD_QUERY,			// ¼���ѯ
    CMD_DETU_CLIENT_RECORD_QUERY_RES,		// ¼���ѯ��Ӧ

    CMD_DETU_CLIENT_CLOSE_VIDEO,			// �ر���Ƶ�Ự������ʵʱ���ط�����
    CMD_DETU_CLIENT_CLOSE_VIDEO_RES,

	CMD_DETU_CLIENT_SET_AVPARAM,			//������Ƶ����
	CMD_DETU_CLIENT_SET_AVPARAM_RES,		//������Ӧ

	CMD_DETU_CLIENT_GET_AVPARAM,			//��ȡ��Ƶ����
	CMD_DETU_CLIENT_GET_AVPARAM_RES,		//��ȡ��Ӧ

	CMD_DETU_CLIENT_DISK_FORMAT,			//��ʽ������
	CMD_DETU_CLIENT_DISK_FORMAT_RES,		//��ʽ����Ӧ

	CMD_DETU_CLIENT_DISKINFO,				//��ȡ������Ϣ
	CMD_DETU_CLIENT_DISKINFO_RES,			//��ȡ������Ӧ

	CMD_DETU_REPORT_NAME,					//�ϱ�����
	CMD_DETU_REPORT_NAME_RES,				//�ϱ�������Ӧ

	CMD_DETU_PTZ_REGISTER,					//���ע��
	CMD_DETU_PTZ_REGISTER_RES,				//���ע����Ӧ

	CMD_DETU_SPY_REGISTER,					//ǹ��ע��
	CMD_DETU_SPY_REGISTER_RES,				//ǹ��ע����Ӧ

	CMD_DETU_CLIENT_STREAM_HANDLE_RES,		//��ͼ�ͻ�����������Ӧ
	CMD_DETU_CLIENT_ADD_STREAM,				//��ͼ�ͻ���������
	CMD_DETU_CLIENT_DEL_STREAM,				//��ͼ�ͻ���ɾ����
	CMD_DETU_CLIENT_GET_STREAM,				//��ͼ�ͻ��˻�ȡ��ǰ��

	CMD_DETU_CLIENT_DEVICE_REBOOT,			//��ͼ�ͻ��˿����豸����
	CMD_DETU_CLIENT_DEVICE_REBOOT_RES,      //��ͼ�ͻ��˿����豸������Ӧ

	CMD_DETU_CLIENT_REPORT_OPTIMIZE_PTS,	//��ͼ�ͻ����ϱ��Ż����pts�ļ�
	CMD_DETU_CLIENT_REPORT_OPTIMIZE_PTS_RES,//��ͼ�ͻ����ϱ��Ż����pts�ļ���Ӧ

	CMD_DETU_CLIENT_ACTIVE_REPORT,			//��ͻ��������ϱ�
			
	CMD_DETU_CLIENT_GET_BANDWIDTH,			//�ͻ��˻�ȡ��������
	CMD_DETU_CLIENT_GET_BANDWIDTH_RES,		//�ͻ��˻�ȡ������Ӧ

	CMD_DETU_CLIENT_GET_PTZ_LIST,			//�ͻ��˻�ȡ����б�
	CMD_DETU_CLIENT_GET_PTZ_LIST_RES,		//�ͻ��˻�ȡ����б���Ӧ

	CMD_DETU_CLIENT_GET_SPY_LIST,			//�ͻ��˻�ȡǹ���б�
	CMD_DETU_CLIENT_GET_SPY_LIST_RES,		//�ͻ��˻�ȡǹ���б���Ӧ

	CMD_DETU_DELETE_PTZ,					//�ͻ���ɾ�����
	CMD_DETU_DELETE_PTZ_RES,                //�ͻ���ɾ�������Ӧ

	CMD_DETU_DELETE_SPY,					//�ͻ���ɾ��ǹ��
	CMD_DETU_DELETE_SPY_RES,				//�ͻ���ɾ��ǹ����Ӧ

	CMD_DETU_SAVE_PTZ_POINT,				//����Ԥ�õ�
	CMD_DETU_SAVE_PTZ_POINT_RES,            //����Ԥ�õ���Ӧ

	CMD_DETU_GET_PTZ_POINT,					//��ȡԤ�õ�
	CMD_DETU_GET_PTZ_POINT_RES,				//��ȡԤ�õ���Ӧ

	CMD_DETU_APP_REGISTER = 4001,			//��ͼAPPע��
	CMD_DETU_APP_REGISTER_RES,				//��ͼAPPע����Ӧ

	CMD_DETU_APP_CLOSE,						//��ͼAPP����ر�
	CMD_DETU_APP_CLOSE_RES,					//��ͼAPP����ر���Ӧ

	CMD_DETU_TCS_REGISTER = 5001,			//TCSע��
	CMD_DETU_TCS_REGISTER_RES,				//TCSע����Ӧ

	CMD_DETU_TCS_HEARTBEAT,					//TCS����
	CMD_DETU_TCS_HEARTBEAT_RES,				//TCS������Ӧ

	CMD_DETU_TCS_TRANSCODE,					//TCSת������
	CMD_DETU_TCS_TRANSCODE_RES,				//TCSת��������Ӧ

	CMD_DETU_TCS_TRANSCODE_STOP,			//TCSֹͣת������
	CMD_DETU_TCS_TRANSCODE_STOP_RES,		//TCSֹͣת����Ӧ
}command_e;


// ����ֵ
typedef enum
{
	RESULT_SUCCESS = 0,		// �ɹ�	
	RESULT_FAILED = -1,		// ʧ��

	RESULT_SYNC_OK = 10005,		// ͬ���ɹ�
	RESULT_ONLINE_OK = 10006,	// M1�ĸ�ͨ��������

    RESULT_NOTSUPPORT = -10000,		//��֧��
    RESULT_UNKNOWCMD = -10001,		//δָ֪��
	RESULT_NODATA = -10002,			//������
    RESULT_NOTREGISTER = -10003,	//δע��
    RESULT_PARAM_ERR = -10004,		//��������
	RESULT_SYNC_ERR = -10005,		//ͬ��ʧ��
	RESULT_OFFLINE_ERR = -10006,	//M1һ������������
	RESULT_SEND_ERR = -10007,		//��������ʧ��
	RESULT_CONNECT_ERR = -10008,	//������ý�������ʧ��

    // ע��
    RESULT_USERNAMEERR = -11001,	//�û�������
    RESULT_PWDERR = -11002,			//�������
    RESULT_REDEVICEID = -11003,		//�豸ID�ظ�
	RESULT_CALIBRATIONERR = -11004, //�궨��Ϣ����

	// ת��
	RESULT_TRANSCODE_EXIST = -12001,	// �豸�Ѿ�������
	RESULT_OCCIPIED,					// ת�����ID��ռ��
	RESUKT_PULL_RTMP_ERROR,				// RTMP����ʧ��
	RESULT_PUSH_RTMP_ERROR,				// RTMP����ʧ��
}command_result_e;

typedef enum
{
	RTMP_LIVE_MAIN1 = 0,			// ʵʱ��������1��ʾ��Ŀ1�����ں������ܵĶ����Ŀ��
	RTMP_LIVE_SUB1,					// ʵʱ������

	RTMP_BACK_MAIN1,				// �ط�������
	RTMP_BACK_SUB1,					// �ط�������

	RTMP_LIVESTITCH_MAIN1,			// ʵʱƴ��������
	RTMP_LIVESTITCH_SUB1,			// ʵʱƴ��������

	RTMP_BACKSTITCH_MAIN1,			// �ط�ƴ��������
	RTMP_BACKSTITCH_SUB1,			// �ط�ƴ��������
}streamId_type_e;

typedef enum
{
	DISKSTATUS_DORMANCY = 1,		// ����״̬
	DISKSTATUS_ABNORMAL = 2,		// ������״̬
	DISKSTATUS_NOT_EXISTENT = 3,	// ���̲�����
	DISKSTATUS_WRITE_PROTECT = 4,	// ����д����	
	DISKSTATUS_NOT_FORMAT = 5,		// ����δ��ʽ��
	DISKSTATUS_FORMATTING = 6,		// �������ڸ�ʽ��
	DISKSTATUS_UNKOWN = 7,			// δ֪״̬
}disk_status_e;

typedef enum
{
	DISKTYPE_HARDDISK = 1,			// ����Ӳ��
	DISKTYPE_SDCARD = 2,			// SD��
	DISKTYPE_FTP = 3,				// FTP
	DISKTYPE_NAS = 4,				// NAS
	DISKTYPE_EXTERN_DISK = 5,		// ����豸
	DISKTYPE_REMOTE_EXTERN_DISK = 6,// Զ������豸
	DISKTYPE_ESATA = 7,				// ESata��
	DISKTYPE_RAID = 8,				// Raid����
}disk_type_e;

typedef enum {
	SERVER_TYPE_CLINET = 0,		// CU
	SERVER_TYPE_TCS,			// TCS
}server_type_e;

//ָ����1�ֽڶ���
#pragma pack (1) 


// Э��ͷ
typedef struct protocol_head
{

    unsigned char	nStartFlags;			// ��ʼ��ʾ:0xAF
    unsigned char	nVersion;				// �汾:0x01
    unsigned short	nCmd;					// ָ��:command_e ö�ٽṹ
    unsigned int	nDataLen;				// ���س���

    short			nResult;				// �����������:command_result_e ö�ٽṹ
	unsigned char   nM1Id;					// ���ں������ܵĶ��M1
	unsigned char   nStreamId;				// ��id   1����������2��������

    unsigned char	deviceNum;				// Ԥ��
    unsigned char	nEndFlags;				// ������ʾ:oxFA	

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



// CMD_DETU_CLIENT_REQUEST_VIDEO, ��Ƶ����, �ͻ��˵�������
typedef struct api_detu_client_request_video
{
	unsigned char 	szDeviceId[API_ARRAY_LEN];		// ��ӦNVR���豸ID������֪ͨ��������Ҫ�Ǹ��豸��ʼ����
	unsigned char   nDeviceId;						// �ͻ��˸����豸��ţ�������װ����ַ�����ֲ���
	
	// ���ڻط�
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



// CMD_DETU_CLIENT_REQUEST_VIDEO_RES, ��Ƶ������, ����������URL���ͻ���
typedef struct api_detu_client_request_video_res
{
	unsigned char 	szDeviceId[API_ARRAY_LEN];		// ��ӦNVR���豸ID������֪ͨ��������Ҫ�Ǹ��豸��ʼ����
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



// CMD_DETU_CLIENT_CLOSE_VIDEO, �ر���Ƶ, �ͻ��˵�������
typedef struct api_detu_client_close_video
{
	unsigned char szDeviceId[API_ARRAY_LEN];      //��ӦNVR���豸ID

	api_detu_client_close_video()
	{
		memset(&szDeviceId, 0, API_ARRAY_LEN);
	}

	int get_size()
	{
		return sizeof(api_detu_client_close_video);
	}

}api_detu_client_close_video_t;
 


// CMD_DETU_TCS_REGISTER, ע��, TCS����������
typedef struct api_detu_tcs_register
{
	unsigned char	szTcsIp[API_ARRAY_LEN];	//TCS����IP
	unsigned int	nPort;					//TCS�����˿�

	unsigned int	nServerId;				//TCS����ID(�ֲ�ʽ)
	unsigned int	nLimits;				//TCS����ת��·������

	unsigned int	nHeartbeatInterval;		// �������	

	api_detu_tcs_register()
	{
		memset(&szTcsIp, 0, API_ARRAY_LEN);
	}

	int get_size()
	{
		return sizeof(api_detu_tcs_register);
	}

}api_detu_tcs_register_t;



// CMD_DETU_TCS_HEARTBEAT������, TCS����������
typedef struct api_detu_tcs_heartbeat
{
	unsigned int	nServerId;				//TCS����ID(�ֲ�ʽ)
	unsigned int	nLimits;				//TCS����ת��·������
	unsigned int	nCAU;					//TCS��ǰת��·��

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


// CMD_DETU_TCS_TRANSCODE, ת��, �ͻ��˷���TCS
typedef struct api_detu_tcs_transcode
{
	unsigned char 	szRtmpURL[API_URL_LENGTH];		// rtmp������ַ
	unsigned char 	szDeviceId[API_ARRAY_LEN];		// ��ӦNVR���豸ID������֪ͨ��������Ҫ�Ǹ��豸��ʼ����
	unsigned char   nDeviceId;						// �ͻ��˸����豸��ţ�������װ����ַ�����ֲ���

	unsigned char   nStreamType;					// ��������
	unsigned char   nFps;							// ֡��
	unsigned int    nbitrate;						// ����(kbps)
	unsigned int    nWidth;							// ��
	unsigned int    nHeight;						// ��

	// ���ڻط�
	unsigned int  	nStartTime;
	unsigned int  	nEndTime;

	unsigned int	nPtsLen;
	unsigned char 	pts_data[API_PTS_LEN];			//PTS�ļ�����

	api_detu_tcs_transcode()
	{
		memset(&szDeviceId, 0, API_ARRAY_LEN);
	}

	int get_size()
	{
		return sizeof(api_detu_tcs_transcode);
	}

}api_detu_tcs_transcode_t;

// CMD_DETU_TCS_TRANSCODE_RES, ת����Ӧ��Ϣ��TCS�����ͻ���
typedef struct api_detu_tcs_transcode_res
{
	unsigned char szDeviceId[API_ARRAY_LEN];      //��ӦNVR���豸ID

	api_detu_tcs_transcode_res()
	{
		memset(&szDeviceId, 0, API_ARRAY_LEN);
	}

	int get_size()
	{
		return sizeof(api_detu_tcs_transcode_res);
	}

}api_detu_tcs_transcode_res_t;

// CMD_DETU_TCS_TRANSCODE_STOP�� ֹͣת��, �ͻ��˷���TCS
typedef struct api_detu_tcs_transcode_stop
{
	unsigned char szDeviceId[API_ARRAY_LEN];      //��ӦNVR���豸ID

	api_detu_tcs_transcode_stop()
	{
		memset(&szDeviceId, 0, API_ARRAY_LEN);
	}

	int get_size()
	{
		return sizeof(api_detu_tcs_transcode_stop);
	}

}api_detu_tcs_transcode_stop_t;

// CMD_DETU_TCS_TRANSCODE_STOP_RES�� ֹͣת����Ӧ��Ϣ, TCS�����ͻ���
typedef struct api_detu_tcs_transcode_stop_res
{
	unsigned char szDeviceId[API_ARRAY_LEN];      //��ӦNVR���豸ID

	api_detu_tcs_transcode_stop_res()
	{
		memset(&szDeviceId, 0, API_ARRAY_LEN);
	}

	int get_size()
	{
		return sizeof(api_detu_tcs_transcode_stop_res);
	}

}api_detu_tcs_transcode_stop_res_t;


#pragma pack ()  // ȡ��ָ�����룬�ָ�ȱʡ����


#endif
