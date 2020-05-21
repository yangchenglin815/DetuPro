#pragma once
#include "message.h"
#define API_ARRAY_LEN	(32)
#define  API_URL_LEN  (512)
#define API_RTMP_LEN      (64)
#define MAX_NVR_LIST_NUM (50)
#define API_PTS_LEN	(32768)

#define API_MAP_DATA_BLOCK_LEN	(8192)		//�ݶ�1024�ֽڴ���

#define  MAX_DEVICE_NUM (10)

#define API_MAP_PATH   (200)

/********************************************
1�����ǿ���չ��
2������ת��ʱ����unsigned

********************************************/

/*********************************************************************************************
APIClient����(NVR)��
1��ʵ����ע�ᡢʵʱ��Ƶ������Ӧ������������
1���������������a)ϵͳ����ʱ b����Ϣ���� c���������������� d������ע������ʧ��
2��ÿ10s���������a������socketʧ�� b������ʧ��  c��ע��ʧ��
APIServer(��Ҫ����)���ṩ��3�����Գ������APIClient�����ץ������������㿪��
**********************************************************************************************/
namespace dm {
	namespace server {
		// �����
		typedef enum
		{
			CMD_REGISTER = 1,	         // ע��
			CMD_REGISTER_RES = 2,		// ע����Ӧ

			CMD_UNREGISTER = 3,			// ע��
			CMD_UNREGISTER_RES = 4,		// ע����Ӧ

			CMD_HEART_BEAT = 5,			// ����
			CMD_HEART_BEAT_RES = 6,		// ������Ӧ

			CMD_REQUEST_VIDEO = 7,		// ��Ƶ���󣨰���ʵʱ���ط�����
			CMD_REQUEST_VIDEO_RES = 8,	// ��Ƶ������Ӧ

			CMD_PLAYBACK_CONTROL = 9,	// �طſ���
			CMD_PLAYBACK_CONTROL_RES = 10,	// �طſ�����Ӧ

			CMD_CLOSE_VIDEO = 11,		// �ر���Ƶ�Ự
			CMD_CLOSE_VIDEO_RES = 12,	// �ر���Ƶ������Ӧ

			CMD_RECORD_QUERY = 13,		// ¼���ѯ
			CMD_RECORD_QUERY_RES = 14,	// ¼���ѯ��Ӧ

			CMD_SET_AVPARAM = 15,		// ������Ƶ����
			CMD_SET_AVPARAM_RES = 16,	// ������Ӧ

			CMD_GET_AVPARAM = 17,		// ��ȡ��Ƶ����
			CMD_GET_AVPARAM_RES = 18,	// ��ȡ��Ӧ

			CMD_DISK_FORMAT = 19,		// ��ʽ������
			CMD_DISK_FORMAT_RES = 20,	// ��ʽ����Ӧ

			CMD_GET_DISKINFO = 21,		// ��ȡȫ��������Ϣ�����ṩ������
			CMD_GET_DISKINFO_RES = 22,	// ��ȡ������Ϣ��Ӧ

			CMD_STREAM_HANDLE_RES = 23,      //��������Ӧ��api_protocol_head_t�ṹ��nStreamIdΪ1����ʾstream1��2��ʾstream2��3��ʾstream1+stream2
			CMD_ADD_STREAM = 24,             //��������ͬ��
			CMD_DEL_STREAM = 25,             //ɾ������ͬ��
			CMD_GET_STREAM = 26,             //��ȡ��ǰ����ͬ��

			CMD_DEVICE_RESTART = 27,         //�豸������api_protocol_head_t�ṹ����nStreamIdΪ1����ʾ����M1��2��ʾ����NVR
			CMD_DEVICE_RESTART_RES = 28,	 //�豸������Ӧ

			CMD_GET_CALIBRATION = 29,		// ��ȡ�궨��Ϣ
			CMD_GET_CALIBRATION_RES = 30,	// ��ȡ�궨��Ϣ��Ӧ

			CMD_GET_RECORD_CALIBRATION = 31,		// ��ȡ�ط�ʱ��α궨��Ϣ
			CMD_GET_RECORD_CALIBRATION_RES = 32,	// ��ȡ�ط�ʱ��α궨��Ϣ��Ӧ

			CMD_SET_M1_TIME = 33,		// ����M1ʱ��: api_device_time_t
			CMD_SET_M1_TIME_RES = 34,	// ��Ӧ
			CMD_GET_M1_TIME = 35,		// ��ȡM1ʱ��
			CMD_GET_M1_TIME_RES = 36,	// ��Ӧ

			CMD_SET_RECORD_POLICY = 37,			// ����¼�����: api_record_policy_t
			CMD_SET_RECORD_POLICY_RES = 38,		// ��Ӧ
			CMD_GET_RECORD_POLICY = 39,			// ��ȡ¼�����
			CMD_GET_RECORD_POLICY_RES = 40,		// ��Ӧ

			CMD_ACTIVE_REPORT = 100,			// �����ϱ�

			CMD_DETU_CLIENT_GET_LIST = 2001,	//��ͼע��
			CMD_DETU_CLIENT_GET_LIST_RES,

			CMD_DETU_CLIENT_HEART_BEAT,							// ����
			CMD_DETU_CLIENT_HEART_BEAT_RES,

			CMD_DETU_CLIENT_VERSION_CHECK,							// ����
			CMD_DETU_CLIENT_VERSION_CHECK_RES,


			CMD_DETU_CLIENT_REQUEST_VIDEO,						// ����ʵʱ��Ƶ������ʵʱ���ط�����
			CMD_DETU_CLIENT_REQUEST_VIDEO_RES,

			CMD_DETU_CLIENT_PLAYBACK_CONTROL,                   //�طſ���
			CMD_DETU_CLIENT_PLAYBACK_CONTROL_RES,				//�طſ�����Ӧ

			CMD_DETU_CLIENT_RECORD_QUERY,						// ¼���ѯ
			CMD_DETU_CLIENT_RECORD_QUERY_RES,					// ¼���ѯ��Ӧ

			CMD_DETU_CLIENT_CLOSE_VIDEO,						// �ر���Ƶ�Ự������ʵʱ���ط�����
			CMD_DETU_CLIENT_CLOSE_VIDEO_RES,

			CMD_DETU_CLIENT_SET_AVPARAM,						//������Ƶ����
			CMD_DETU_CLIENT_SET_AVPARAM_RES,					//������Ӧ

			CMD_DETU_CLIENT_GET_AVPARAM,					//��ȡ��Ƶ����
			CMD_DETU_CLIENT_GET_AVPARAM_RES,				//��ȡ��Ӧ

			CMD_DETU_CLIENT_DISK_FORMAT,                    //��ʽ������
			CMD_DETU_CLIENT_DISK_FORMAT_RES,				//��ʽ����Ӧ

			CMD_DETU_CLIENT_DISKINFO,                        //��ȡ������Ϣ
			CMD_DETU_CLIENT_DISKINFO_RES,                    //��ȡ������Ӧ

			CMD_DETU_REPORT_NAME,                            //�ϱ�����
			CMD_DETU_REPORT_NAME_RES,                        //�ϱ�������Ӧ

			CMD_DETU_PTZ_REGISTER,                                //���ע��
			CMD_DETU_PTZ_REGISTER_RES,                       //���ע����Ӧ

			CMD_DETU_SPY_REGISTER,                                //ǹ��ע��
			CMD_DETU_SPY_REGISTER_RES,                       //ǹ��ע����Ӧ

			CMD_DETU_CLIENT_STREAM_HANDLE_RES,				//��ͼ�ͻ�����������Ӧ
			CMD_DETU_CLIENT_ADD_STREAM,                     //��ͼ�ͻ���������
			CMD_DETU_CLIENT_DEL_STREAM,                      //��ͼ�ͻ���ɾ����
			CMD_DETU_CLIENT_GET_STREAM,                      //��ͼ�ͻ��˻�ȡ��ǰ��

			CMD_DETU_CLIENT_DEVICE_REBOOT,               //��ͼ�ͻ��˿����豸����
			CMD_DETU_CLIENT_DEVICE_REBOOT_RES,      //��ͼ�ͻ��˿����豸������Ӧ

			CMD_DETU_CLIENT_REPORT_OPTIMIZE_PTS,               //��ͼ�ͻ����ϱ��Ż����pts�ļ�
			CMD_DETU_CLIENT_REPORT_OPTIMIZE_PTS_RES,      //��ͼ�ͻ����ϱ��Ż����pts�ļ���Ӧ

			CMD_DETU_CLIENT_ACTIVE_REPORT,               //��ͻ��������ϱ�

			CMD_DETU_CLIENT_GET_BANDWIDTH,           //�ͻ��˻�ȡ��������
			CMD_DETU_CLIENT_GET_BANDWIDTH_RES,   //�ͻ��˻�ȡ������Ӧ

			CMD_DETU_CLIENT_GET_PTZ_LIST,             //�ͻ��˻�ȡ����б�
			CMD_DETU_CLIENT_GET_PTZ_LIST_RES,         //�ͻ��˻�ȡ����б���Ӧ

			CMD_DETU_CLIENT_GET_SPY_LIST,             //�ͻ��˻�ȡǹ���б�
			CMD_DETU_CLIENT_GET_SPY_LIST_RES,         //�ͻ��˻�ȡǹ���б���Ӧ

			CMD_DETU_DELETE_PTZ,                        //�ͻ���ɾ�����
			CMD_DETU_DELETE_PTZ_RES,                //�ͻ���ɾ�������Ӧ

			CMD_DETU_DELETE_SPY,                       //�ͻ���ɾ��ǹ��
			CMD_DETU_DELETE_SPY_RES,               //�ͻ���ɾ��ǹ����Ӧ

			CMD_DETU_SAVE_PTZ_POINT,                     //����Ԥ�õ�
			CMD_DETU_SAVE_PTZ_POINT_RES,            //����Ԥ�õ���Ӧ

			CMD_DETU_GET_PTZ_POINT,                        //��ȡԤ�õ�
			CMD_DETU_GET_PTZ_POINT_RES,               //��ȡԤ�õ���Ӧ

			CMD_DETU_CLIENT_LOGIN_CHECKED,    //�ͻ��˵�¼У��
			CMD_DETU_CLIENT_LOGIN_CHECKED_RES,  //��Ӧ

			CMD_DETU_CLIENT_REGISTER_USER,    //�ͻ���ע���û�����
			CMD_DETU_CLIENT_REGISTER_USER_RES,  //��Ӧ

			CMD_DETU_SET_MAP,						//�ͻ������õ�ͼ����
			CMD_DETU_SET_MAP_RES,					//��Ӧ

			CMD_DETU_GET_MAP,						//�ͻ��������ͼ����
			CMD_DETU_GET_MAP_RES,					//��Ӧ

			/********************APP���*********************/
			CMD_DETU_APP_REGISTER = 4001,                   //��ͼAPPע��
			CMD_DETU_APP_REGISTER_RES,                        //��ͼAPPע����Ӧ

			CMD_DETU_APP_CLOSE,                                      //��ͼAPP����ر�
			CMD_DETU_APP_CLOSE_RES,                             //��ͼAPP����ر���Ӧ

			/********************ת��������*********************/
			CMD_DETU_TCS_REGISTER = 5001,			//TCSע��
			CMD_DETU_TCS_REGISTER_RES,				//TCSע����Ӧ

			CMD_DETU_TCS_HEARTBEAT,					//TCS����
			CMD_DETU_TCS_HEARTBEAT_RES,				//TCS������Ӧ

			CMD_DETU_TCS_TRANSCODE,					//TCSת������
			CMD_DETU_TCS_TRANSCODE_RES,				//TCSת��������Ӧ

			CMD_DETU_TCS_TRANSCODE_STOP,			//TCSֹͣת������
			CMD_DETU_TCS_TRANSCODE_STOP_RES,		//TCSֹͣת����Ӧ

			CMD_DETU_CLIENT_GET_TCS_INFO,         //��ͻ��˷���TCS��Ϣ
			CMD_DETU_CLIENT_GET_TCS_INFO_RES,    //��ͻ��˷���TCS��Ϣ��Ӧ

			CMD_DETU_CLIENT_UPDATE_TCSINFO,          //����ת�������Ϣ
			CMD_DETU_CLIENT_UPDATE_TCSINFO_RES,      //����ת�������Ϣ

			CMD_DETU_CLIENT_TCS_REPORT_ERROR,        //ת���쳣�ϱ�
			CMD_DETU_CLINET_TCS_OFFLINE,             //ת���������

			CMD_DETU_CLIENT_TCS_RESET,                //����ת������
			CMD_DETU_CLIENT_TCS_RESET_RES,        //����ת��Ӧ��

			CMD_DETU_SET_M1_TIME,	// ����M1ʱ��: api_device_time_t
			CMD_DETU_SET_M1_TIME_RES,	// ��Ӧ
			CMD_DETU_GET_M1_TIME,	// ��ȡM1ʱ��
			CMD_DETU_GET_M1_TIME_RES,	// ��Ӧ

			CMD_DETU_SET_RECORD_POLICY,	// ����¼�����: api_record_policy_t
			CMD_DETU_SET_RECORD_POLICY_RES,	// ��Ӧ
			CMD_DETU_GET_RECORD_POLICY,	// ��ȡ¼�����
			CMD_DETU_GET_RECORD_POLICY_RES,	// ��Ӧ

			CMD_DETU_SEND_MAP_DATA,
			CMD_DETU_SEND_MAP_DATA_RES,
			CMD_DETU_GET_MAP_DATA,
			CMD_DETU_GET_MAP_DATA_RES,

		}command_e;

		// ����ֵ
		typedef enum
		{
			RESULT_SUCCESS = 0,		// �ɹ�	
			RESULT_FAILED = -1,		// ʧ��

			RESULT_SYNC_OK = 10005,	// ͬ���ɹ�
			RESULT_ONLINE_OK = 10006,	// M1�ĸ�ͨ��������

			RESULT_NOTSUPPORT = -10000,         //��֧��
			RESULT_UNKNOWCMD = -10001,		//δָ֪��
			RESULT_NODATA = -10002,                 //������
			RESULT_NOTREGISTER = -10003,        //δע��
			RESULT_PARAM_ERR = -10004,		   //��������
			RESULT_SYNC_ERR = -10005,              //ͬ��ʧ��
			RESULT_OFFLINE_ERR = -10006,         //M1һ������������
			RESULT_SEND_ERR = -10007,	// ��������ʧ��
			RESULT_CONNECT_ERR = -10008,	// ������ý�������ʧ��

			// ע��
			RESULT_USERNAMEERR = -11001,				// �û�������
			RESULT_PWDERR = -11002,				// �������
			RESULT_REDEVICEID = -11003,				// �豸ID�ظ�
			RESULT_CALIBRATIONERR = -11004,  //�궨��Ϣ����

			//ת��
			RESULT_TRANSCODE_EXIST = -12001,     //�����Ѿ�������
			RESULT_OCCIPIED,                                       //ת�����ID��ռ��
			RESUKT_PULL_RTMP_ERROR,				// RTMP����ʧ��
			RESULT_PUSH_RTMP_ERROR,				// RTMP����ʧ��
		}command_result_e;

		typedef enum
		{
			RTMP_LIVE_MAIN1 = 0,		// ʵʱ��������1��ʾ��Ŀ1�����ں������ܵĶ����Ŀ��
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
			DISKSTATUS_DORMANCY = 1,	// ����״̬
			DISKSTATUS_ABNORMAL = 2,	// ������״̬
			DISKSTATUS_NOT_EXISTENT = 3,	// ���̲�����
			DISKSTATUS_WRITE_PROTECT = 4,	// ����д����	
			DISKSTATUS_NOT_FORMAT = 5,	// ����δ��ʽ��
			DISKSTATUS_FORMATTING = 6,	// �������ڸ�ʽ��
			DISKSTATUS_UNKOWN = 7,	// δ֪״̬
		}disk_status_e;

		typedef enum
		{
			DISKTYPE_HARDDISK = 1,	// ����Ӳ��
			DISKTYPE_SDCARD = 2,	// SD��
			DISKTYPE_FTP = 3,	// FTP
			DISKTYPE_NAS = 4,	// NAS
			DISKTYPE_EXTERN_DISK = 5,	// ����豸
			DISKTYPE_REMOTE_EXTERN_DISK = 6,	// Զ������豸
			DISKTYPE_ESATA = 7,	// ESata��
			DISKTYPE_RAID = 8,	// Raid����
		}disk_type_e;

		typedef enum {
			SERVER_TYPE_CLINET = 0,		// CU
			SERVER_TYPE_TCS,			// TCS
		}server_type_e;

		//�ͻ���ע���û�У��
		typedef enum{
			HAVE_BEEN_REGISTERED = -5001,
			REGISTER_SUCCESSFUL = 5001,
		}register_type_e;

		//�ͻ��˵�¼У����
		typedef enum{
			USERNAME_ERR = -6001,
			PASSWD_ERR,
			MUTI_CLIENT_ERR,
			READ_DATABASE_ERR,
			CHECK_FINISHED = 6001,
		}login_type_e;

#pragma pack (1) // ָ����1�ֽڶ���
		// Э��ͷ
		typedef struct protocol_head
		{

			unsigned char	nStartFlags;			// ��ʼ��ʾ:0xAF
			unsigned char	nVersion;				// �汾:0x01
			unsigned short	nCmd;					// ָ��:command_e ö�ٽṹ
			unsigned int	nDataLen;				// ���س���

			short			nResult;				// �����������:command_result_e ö�ٽṹ
			unsigned char nM1Id;        //���ں������ܵĶ��M1
			unsigned char nStreamId;     //��id   1����������2��������

			unsigned char	deviceNum;				// Ԥ��
			unsigned char	nEndFlags;				// ������ʾ:oxFA	

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

		// ע�� : CMD_REGISTER
		typedef struct api_register
		{
			unsigned char 	szDeviceId[API_ARRAY_LEN];			// �豸ID��Ψһ��ʶ
			unsigned char 	szUserName[API_ARRAY_LEN];			// �û���
			unsigned char 	szPassWord[API_ARRAY_LEN];			// ����
			unsigned int	nHeartbeatInterval;		// �������	

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

		// ע�� : CMD_REGISTER
		typedef struct api_pts_file
		{
			unsigned int	nPtsLen;
			unsigned char 	pts_data[API_PTS_LEN];		//PTS�ļ�����
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

		//��������NVR��ѯ�طŽṹ��
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

		//NVR��ѯ�طŷ��ط������ṹ��
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



		// ��Ƶ���󣨺�ʵʱ���طţ�:CMD_REQUEST_LIVE_VIDEO ****************��������NVR
		typedef struct api_request_video
		{
			unsigned char 	szRtmpURL[API_RTMP_LEN];

			// ���ڻط�
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

		// ע�� : CMD_DETU_CLIENT_REGISTER
		typedef struct api_detu_client_register
		{
			unsigned char 	szDetuDeviceUUId[API_RTMP_LEN];			// �豸ID��Ψһ��ʶ
			unsigned char 	szDetuUserName[API_ARRAY_LEN];			// �û���
			unsigned char 	szDetuPassWord[API_ARRAY_LEN];			// ����

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

		//��������Ϣ
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
			unsigned  char	szDeviceId[API_ARRAY_LEN];			// �豸ID��Ψһ��ʶ
			unsigned char szName[API_ARRAY_LEN];
			unsigned char m1DeviceId[API_ARRAY_LEN];
			unsigned int              szUpDown;
			unsigned int				curr_num;
			unsigned int				total_num;
			unsigned int              online;
			//unsigned int               onMap;              // 1��map����      0��Ϊ��map����
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
			unsigned  char	szDeviceId[API_ARRAY_LEN];			// �豸ID��Ψһ��ʶ
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





		// ��Ƶ���󣨺�ʵʱ���طţ�:CMD_DETU_CLIENT_REQUEST_LIVE_VIDEO ********�ͻ��˵�������
		typedef struct api_detu_client_request_video
		{
			unsigned char 	szDeviceId[API_ARRAY_LEN];;		// ��ӦNVR���豸ID������֪ͨ��������Ҫ�Ǹ��豸��ʼ����
			unsigned char   nDeviceId;						// �ͻ��˸����豸��ţ�������װ����ַ�����ֲ���
			// ���ڻط�
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

		// ��Ƶ����������ʵʱ���طţ�:CMD_DETU_CLIENT_REQUEST_LIVE_VIDEO_RES ********����������URL���ͻ���
		typedef struct api_detu_client_request_video_res
		{
			unsigned char 	szDeviceId[API_ARRAY_LEN];;		// ��ӦNVR���豸ID
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

#pragma pack ()  // ȡ��ָ�����룬�ָ�ȱʡ����





		// ��ѯ¼��:CMD_DETU_CLIENT_RECORD_QUERY ********�ͻ��˵�������
		typedef struct api_detu_client_record_query
		{
			unsigned char 	szDeviceId[API_ARRAY_LEN];;      //��ӦNVR���豸ID������֪ͨ��������ѯ�ĸ��豸��¼��
			// ���ڻط�ʱ�������
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


		// ��ѯ¼����:CMD_DETU_CLIENT_RECORD_QUERY_RES ********���������ͻ���
		typedef struct api_detu_client_record_query_res
		{
			// ¼��ʱ���Unixʱ���
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

		// ��ѯ¼��:CMD_DETU_CLIENT_RECORD_QUERY ********�ͻ��˵�������
		typedef struct api_detu_client_close_video
		{
			unsigned char szDeviceId[API_ARRAY_LEN];;      //��ӦNVR���豸ID������֪ͨ��������ѯ�ĸ��豸��¼��

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

		// �طſ��� : CMD_PLAYBACK_CONTROL
		typedef struct api_playback_control
		{
			unsigned char	nControlType;					// �������ͣ�1������ 2����ͣ
			unsigned char	nSpeed;							// ���ʿ��ƣ�1�������ٶ� 2:2x 3:1/2x
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


		//�طſ��ƽӿ�
		typedef struct api_detu_client_replay_control
		{
			unsigned char 	szDeviceId[API_ARRAY_LEN];
			unsigned char nControlType;          //�������ͣ�1�����š�2����ͣ
			unsigned char nSpeed;                     //�����ڲ��ţ�1���������ţ�2��2x��3��1/2x��4��4x��5��1/4x

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

		// ��Ƶ��Ϣ : CMD_SET_AVPARAM CMD_GET_AVPARAM
		typedef struct api_av_param
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

		//���ʿ��ƽӿ�  
		typedef struct api_detu_client_av_param
		{
			unsigned char 	szDeviceId[API_ARRAY_LEN];
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



		//���������ӿ�

		typedef struct api_disk_info
		{
			unsigned char	nCurDiskNum;					// ��ǰ�������
			unsigned char	nTotalDiskNum;					// ��������

			unsigned char	nDiskId;						// ����Id��
			unsigned char	nDiskStatus;					// ����״̬������Ųμ� disk_status_e �ṹ
			unsigned char   nDiskType;						// �������ͣ�����Ųμ� disk_type_e �ṹ
			unsigned char	nReserver[3];					// Ԥ��

			unsigned int	nTotalDiskSize;					// ��������������λ��Mbyte
			unsigned int	nUsedSize;						// ����������������λ��Mbyte
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
			unsigned char	nCurDiskNum;					// ��ǰ�������
			unsigned char	nTotalDiskNum;					// ��������

			unsigned char	nDiskId;						// ����Id��
			unsigned char	nDiskStatus;					// ����״̬������Ųμ� disk_status_e �ṹ
			unsigned char   nDiskType;						// �������ͣ�����Ųμ� disk_type_e �ṹ
			unsigned char	nReserver[3];					// Ԥ��

			unsigned int	nTotalDiskSize;					// ��������������λ��Mbyte
			unsigned int	nUsedSize;						// ����������������λ��Mbyte
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

		//���������б�
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

		//APPע�� : CMD_DETU_TRANSCODING_REGISTER
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

		// APPע����Ӧ : CMD_DETU_TRANSCODING_REGISTER_RES
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
			unsigned int	nInputBandWidth;				// �������M1 --> PVS����λ��Byte/s��3s��ֵ
			unsigned int	nOuntputBandWidth;				// �������PVS --> ��ý�������
			unsigned int	nStream1Status;					// ������״̬��0��ʾ��·��ȫ������1��ʾ��ͬ����2��ʾ����
			unsigned int	nStream2Status;					// ������״̬��ͬ��
			unsigned int	nCalibrationStatus;				// �궨��Ϣ״̬��0��ʾ�ɹ���������ʾʧ��
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

		// CMD_DETU_TCS_REGISTER, ע��, TCS����������
		typedef struct api_detu_tcs_register
		{
			unsigned char	szTcsIp[API_ARRAY_LEN];	//TCS����IP
			unsigned int	nPort;					//TCS�����˿�
			unsigned int	nServerId;				//TCS����ID(�ֲ�ʽ)
			unsigned int	nLimits;				//TCS����ת��·������
			unsigned int	nHeartbeatInterval;		// �������	

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



		// CMD_DETU_TCS_HEARTBEAT������, TCS����������
		typedef struct api_detu_tcs_heartbeat
		{
			unsigned int	nServerId;				//TCS����ID(�ֲ�ʽ)
			unsigned int	nLimits;				//TCS����ת��·������
			unsigned int	nCAU;					//TCS��ǰת��·��

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


		// CMD_DETU_TCS_TRANSCODE, ת��, �ͻ��˷���TCS
		typedef struct api_detu_tcs_transcode
		{
			unsigned char szRtmpURL[API_URL_LEN];      //rtmp������ַ
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

		// CMD_DETU_TCS_TRANSCODE_RES, ת����Ӧ��Ϣ��TCS�����ͻ���
		typedef struct api_detu_tcs_transcode_res
		{
			unsigned char szDeviceId[API_ARRAY_LEN];      //��ӦNVR���豸ID

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

		//��ͼ�����豸�ṹ��
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

		//��ͼ�����ṹ��
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



		//��ͼ��ṹ��
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


		// ��ͼ���ݽṹ��
		typedef struct api_detu_vr_map_data
		{
			short				curr_num;			//��ǰ
			short				total_num;			//��ͼ����

			unsigned char mapName[API_ARRAY_LEN];      //��ͼ����
			unsigned char mapPath[API_MAP_PATH];      //��Ӧ�ļ���·��
			//unsigned char mapData[API_ARRAY_LEN];    //��ͼ����


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

		// ��ͼ�б�
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

		// ��ͼ���ݿ�
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