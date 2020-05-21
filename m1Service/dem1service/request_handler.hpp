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

			//PVS注册
			int handle_request_nvr_register(protocol_head_t *head, netbuffer *buf);
			//请求PVS标定响应
			int handle_request_calibration_res(protocol_head_t *head, netbuffer *buf);
			//请求PVS回放标定响应
			int handle_request_replay_calibration_res(protocol_head_t *head, netbuffer *buf);
			//请求PVS标定信息的回复处理
			int handle_request_nvr_calibration(protocol_head_t *head, netbuffer *buf);
			//PVS心跳
			int handle_request_nvr_heart_beat(std::string session_id_, netbuffer *buf);
			//得图客户端注册
			int handle_request_detu_client_heart_beat(std::string session_id_);
			//得图客户端版本匹配
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
			//上报设备别名
			int handle_request_report_name(netbuffer *buf, std::string session_id_);
			//球机注册
			int handle_request_ptz_register(netbuffer *buf, unsigned char streamId);
			//枪机注册
			int handle_request_spy_register(netbuffer *buf, unsigned char streamId);
			//获取当前流
			int handle_request_get_stream(netbuffer *buf);
			//新增流
			int handle_request_add_stream(netbuffer *buf, unsigned char streamId);
			//删除流
			int handle_request_del_stream(netbuffer *buf, unsigned char streamId);
			//流处理响应返回
			int handle_request_handle_stream_res(short result, unsigned char streamId);
			//重启设备请求
			int handle_request_reboot_device(netbuffer *buf,  unsigned char streamId);
			//重启设备响应
			int handle_request_reboot_device_res(short result, unsigned char streamId);
			//APP注册请求
			int handle_request_app_register(netbuffer *buf);
			//客户端上报pts文件数据
			int handle_request_report_pts_data(netbuffer *buf, std::string session_id_);
			//PVS主动上报
			int handle_request_active_report(std::string session_id_, unsigned short result, unsigned char streamId);
			//客户端获取带宽
			int handle_request_get_bandWidth(netbuffer *buf);
			//客户端获取球机列表
			int handle_request_get_ptz_list();
			//客户端获取枪机列表
			int handle_request_get_spy_list();
			//删除球机
			int handle_request_delete_ptz(netbuffer *buf);
			//删除枪机
			int handle_request_delete_spy(netbuffer *buf);
			//保存球机预置点
			int handle_request_save_ptz_point(netbuffer *buf);
			//获取球机预置点
			int handle_request_get_ptz_point(netbuffer *buf);
			//TCS服务注册
			int handle_request_tcs_register(netbuffer *buf);
			//处理TCS心跳
			int handle_request_tcs_heartbeat(netbuffer *buf);
			//处理TCS离线
			int handle_request_tcs_offline(unsigned int nServerId);
			//处理转码重置请求
			int handle_request_tcs_reset();

			//处理M1时间设置请求
			int handle_request_set_m1_time(netbuffer *buf);
			int handle_request_get_m1_time(netbuffer *buf);
			int handle_request_set_record(netbuffer *buf);
			int handle_request_get_record(netbuffer *buf);

			//地图数据存储
			int handle_request_set_map_data(netbuffer *buf);
			int handle_request_get_map_data(netbuffer *buf);

            //先不用宏实现
            int handle_request(api_record_query_respond_t *req);

			//查询PVS回放
			int handle_request(netbuffer *buf, int n, unsigned char streamId);

			int handle_request_detu_register(netbuffer *buf);
			int handle_request(int n, netbuffer *buf, unsigned char streamId);

			//客户端请求视频
			int handle_request_detu_client_request_video(netbuffer *buf, unsigned char streamId, unsigned char deviceType);
			//nvr请求视频后回复
			int handle_request_nvr_request_video_res(short nResult, unsigned char deviceType);
			//客户端关闭视频
			int handle_request_detu_client_close_video(netbuffer *buf, unsigned char streamId, short result, std::string sessionID);
			//客户端登录校验
			int handle_request_detu_client_login_checked(netbuffer *buf);
			//用户的注册用户校验
			int handle_request_detu_client_register_user(netbuffer *buf);
        private:
            bool handle_reg_to_sql(api_register_t *req);

		private:
			sql::Connection* pconn_;//数据库连接
			boost::shared_ptr<sql::Statement> pstmt_;

			std::shared_ptr<connection> curr_conn_;//当前ＳＯＣＫＥＴ连接
		};

	}  // namespace server
}  // namespace dem1

#endif  // M1_REQUEST_HANDLER_HPP
