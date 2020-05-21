#pragma once

#include "core.h"
#include <string>
#include <map>
#include <string>
#include <memory>
#include <vector>
#include <iostream>

#include "APIProtocol.h"
#include "response.hpp"


/*#include "multi_rtsp.hpp"*/


namespace dm 
{
	namespace server 
	{
        class dmconnection;
		class request_handler 
		{
			public:
				request_handler();

				int start(dmconnection* dm_conn);
				void stop();
           
				//心跳
				int handle_request();
				int handle_request(api_detu_client_register_res_t *req);
				//版本匹配
				int handle_version_check(protocol_head_t head);
				//格式化磁盘
				int handle_request(bool is_ok);
				//球机注册响应
				int handle_request_ptz_register_res(bool is_ok, unsigned char streamId);
				//枪机注册响应
				int handle_request_spy_register_res(bool is_ok, unsigned char streamId);
				//
				int handle_request(netbuffer *buf, bool is_video_ok);
				//回放控制返回
				int handle_request_replay_control(bool is_ok, unsigned char streamId);
				//获取码率信息
				int handle_request(netbuffer *buf, unsigned char streamId);
				//设置码率信息
				int handle_request(unsigned char streamId, bool is_video_ok);
				//处理服务器转发的查询录像时间段
                int handle_request(netbuffer *buf, int n);
                //处理服务器转发的磁盘容量信息
				int handle_request_disk_size(netbuffer *buf, int n);
				//流处理返回响应
				int handle_request_handle_stream_res(short result, unsigned char streamId);
				//重启设备返回响应
				int handle_request_reboot_device_res(short result, unsigned char streamId);
				//PVS主动上报
				int handle_request_active_report(netbuffer *buf, unsigned char streamId);
				//获取带宽
				int handle_request_get_bandWidth(netbuffer *buf);
				//获取球机列表
				int handle_request_get_ptz_list(netbuffer *buf);
				//获取枪机列表
				int handle_request_get_spy_list(netbuffer *buf);
				//删除球机
				int handle_request_delete_ptz(short result);
				//删除枪机
				int handle_request_delete_spy(short result);
				//获取球机预置点
				int handle_request_get_ptz_point(netbuffer *buf);
				//获取转码服务信息
				int handle_request_get_tcs_info(netbuffer *buf);
				//更新心跳数据
				int handle_request_update_tcs_info(netbuffer *buf);
				//上报转码服务异常
				int handle_request_report_tcs_error(netbuffer *buf, short result);
				//TCS离线
				int handle_request_tcs_offline(netbuffer *buf);
				//
				int handle_request_tcs_reset(short result);

				//得图发送地图数据响应
				int handle_request_send_map_data_res(netbuffer *buf);
				//得图请求地图数据响应
				int handle_request_get_map_data_res(netbuffer *buf);
				//客户端登录校验请求响应
				int handle_request_login_checked_res(netbuffer *buf, short result);
				//客户端注册用户请求响应
				int handle_request_register_user_res(netbuffer *buf, short result);
			private:
				dmconnection* curr_conn_;//当前ＳＯＣＫＥＴ连接
           
		};

	}  // namespace server
}  // namespace dem1


