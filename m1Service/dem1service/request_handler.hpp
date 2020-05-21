#ifndef M1_REQUEST_HANDLER_HPP
#define M1_REQUEST_HANDLER_HPP
#include "core.h"
#include <string>
#include <map>
#include <string>
#include <memory>
#include <vector>
#include <iostream>

#include "APIProtocol.h"
#include "response.hpp"
#include "connect_pool.hpp"
#include "detunvrlist.h"
#include "detuclientlist.h"
#include "detuapplist.h"
#include "OnlineConnList.h"


namespace dem1 {
	namespace server {

		class connection;
		class request_handler {
		public:
			request_handler();

            int start(std::shared_ptr<connection>  dm_conn);
			void stop();

			//PVSע��
			int handle_request_nvr_register(protocol_head_t *head, netbuffer *buf);
			//����PVS�궨��Ӧ
			int handle_request_calibration_res(protocol_head_t *head, netbuffer *buf);
			//����PVS�طű궨��Ӧ
			int handle_request_replay_calibration_res(protocol_head_t *head, netbuffer *buf);
			//����PVS�궨��Ϣ�Ļظ�����
			int handle_request_nvr_calibration(protocol_head_t *head, netbuffer *buf);
			//PVS����
			int handle_request_nvr_heart_beat(std::string session_id_, netbuffer *buf);
			//��ͼ�ͻ���ע��
			int handle_request_detu_client_heart_beat(std::string session_id_);
			//��ͼ�ͻ��˰汾ƥ��
			int handle_request_detu_client_version_check(protocol_head_t *head);
			

			int handle_request_playback_control(netbuffer *buf, unsigned char streamId);
			int handle_request_get_avparam(netbuffer *buf, unsigned char streamId);
			int handle_request_get_avparam_res(netbuffer *buf, unsigned char streamId);
			int handle_request_set_avparam(netbuffer *buf, unsigned char streamId);
			int handle_request_set_avparam_res(short result, unsigned char streamId);
			int handle_request_disk_info(netbuffer *buf, unsigned char streamId);
			int handle_request_disk_format(netbuffer *buf, unsigned char streamId);
			int handle_request(unsigned char result, unsigned char streamId);
			int handle_request(std::string session_id_, int n, netbuffer *buf, unsigned char streamId);
			int handle_request(std::string session_id_, unsigned short result, unsigned char streamId);
			int handle_request_close_video(unsigned short result);
			//�ϱ��豸����
			int handle_request_report_name(netbuffer *buf, std::string session_id_);
			//���ע��
			int handle_request_ptz_register(netbuffer *buf, unsigned char streamId);
			//ǹ��ע��
			int handle_request_spy_register(netbuffer *buf, unsigned char streamId);
			//��ȡ��ǰ��
			int handle_request_get_stream(netbuffer *buf);
			//������
			int handle_request_add_stream(netbuffer *buf, unsigned char streamId);
			//ɾ����
			int handle_request_del_stream(netbuffer *buf, unsigned char streamId);
			//��������Ӧ����
			int handle_request_handle_stream_res(short result, unsigned char streamId);
			//�����豸����
			int handle_request_reboot_device(netbuffer *buf,  unsigned char streamId);
			//�����豸��Ӧ
			int handle_request_reboot_device_res(short result, unsigned char streamId);
			//APPע������
			int handle_request_app_register(netbuffer *buf);
			//�ͻ����ϱ�pts�ļ�����
			int handle_request_report_pts_data(netbuffer *buf, std::string session_id_);
			//PVS�����ϱ�
			int handle_request_active_report(std::string session_id_, unsigned short result, unsigned char streamId);
			//�ͻ��˻�ȡ����
			int handle_request_get_bandWidth(netbuffer *buf);
			//�ͻ��˻�ȡ����б�
			int handle_request_get_ptz_list();
			//�ͻ��˻�ȡǹ���б�
			int handle_request_get_spy_list();
			//ɾ�����
			int handle_request_delete_ptz(netbuffer *buf);
			//ɾ��ǹ��
			int handle_request_delete_spy(netbuffer *buf);
			//�������Ԥ�õ�
			int handle_request_save_ptz_point(netbuffer *buf);
			//��ȡ���Ԥ�õ�
			int handle_request_get_ptz_point(netbuffer *buf);
			//TCS����ע��
			int handle_request_tcs_register(netbuffer *buf);
			//����TCS����
			int handle_request_tcs_heartbeat(netbuffer *buf);
			//����TCS����
			int handle_request_tcs_offline(unsigned int nServerId);
			//����ת����������
			int handle_request_tcs_reset();

			//����M1ʱ����������
			int handle_request_set_m1_time(netbuffer *buf);
			int handle_request_get_m1_time(netbuffer *buf);
			int handle_request_set_record(netbuffer *buf);
			int handle_request_get_record(netbuffer *buf);

			//��ͼ���ݴ洢
			int handle_request_set_map_data(netbuffer *buf);
			int handle_request_get_map_data(netbuffer *buf);

            //�Ȳ��ú�ʵ��
            int handle_request(api_record_query_respond_t *req);

			//��ѯPVS�ط�
			int handle_request(netbuffer *buf, int n, unsigned char streamId);

			int handle_request_detu_register(netbuffer *buf);
			int handle_request(int n, netbuffer *buf, unsigned char streamId);

			//�ͻ���������Ƶ
			int handle_request_detu_client_request_video(netbuffer *buf, unsigned char streamId, unsigned char deviceType);
			//nvr������Ƶ��ظ�
			int handle_request_nvr_request_video_res(short nResult, unsigned char deviceType);
			//�ͻ��˹ر���Ƶ
			int handle_request_detu_client_close_video(netbuffer *buf, unsigned char streamId, short result, std::string sessionID);
			//�ͻ��˵�¼У��
			int handle_request_detu_client_login_checked(netbuffer *buf);
			//�û���ע���û�У��
			int handle_request_detu_client_register_user(netbuffer *buf);
        private:
            bool handle_reg_to_sql(api_register_t *req);

		private:
			sql::Connection* pconn_;//���ݿ�����
			boost::shared_ptr<sql::Statement> pstmt_;

			std::shared_ptr<connection> curr_conn_;//��ǰ�ӣϣãˣţ�����
		};

	}  // namespace server
}  // namespace dem1

#endif  // M1_REQUEST_HANDLER_HPP
