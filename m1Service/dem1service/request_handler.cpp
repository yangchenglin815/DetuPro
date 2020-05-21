#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>    
#define BOOST_DATE_TIME_SOURCE    

#include "../dem1serivce_server/sqliteManage.h"

#include "connection.hpp"
#include "connection_manager.hpp"
#include "request_handler.hpp"
#include "setip.h"
#include "construct.h"

namespace dem1 {
	namespace server {


		request_handler::request_handler()
        {

		}

        int request_handler::start(std::shared_ptr<connection>  dm_conn){

			this->curr_conn_ = dm_conn;
		
			return 0;
		}

		void request_handler::stop(){
			//MySQLPool.ReleaseConnection(pconn_);//回收
			std::string sessionId = curr_conn_->get_sessionid();
			int type;
			bool ret = SessionManage.getSessionIdTyptFromTable(sessionId, type);
			if (ret)
			{
				int nServerId = -1;
				switch (type)
				{
				case 0:
					DetuNvrlist.removeSessionId(sessionId);
					PVSManage.updatePVSDeviceState(sessionId);
					break;
				case 1:
					DetuClientlist.removeSessionId(sessionId);
					PanoManage.deletePanoFromTable(sessionId);
					break;
				case 2:
					if (TCSManage.getTCSServerID(nServerId, sessionId) && nServerId > 0)
					{
						TCSManage.deleteTCSFromTable(sessionId);
						TCSManage.deleteTCSServer(nServerId);
						handle_request_tcs_offline(nServerId);
					}
					break;
				case 3:
					DetuAPPlist.removeSessionId(sessionId);
					break;
				default:
					break;
				}
			}
			SessionManage.deleteSessionFromTable(sessionId);
		}

		int request_handler::handle_request_nvr_register(protocol_head_t *head, netbuffer *buf) {
			
            //返给NVR注册成功
			protocol_head_t prot_head;
            response res(prot_head.get_size());

			prot_head.nCmd = CMD_REGISTER_RES;
            prot_head.nResult = RESULT_SUCCESS;
			prot_head.nStreamId = 0;

            response_add_resprotocol<protocol_head_t>(res, &prot_head);

            if (curr_conn_ != NULL)
            {
                curr_conn_->do_write(res);
            }
			
			//保存注册数据
			api_register_t nvr_reg;
			nvr_reg.read(buf);
			//std::string szDeviceId = (char*)nvr_reg.szDeviceId;

			api_detu_client_register_res_t api_reg;
			memcpy(api_reg.szDeviceId, nvr_reg.szDeviceId, API_ARRAY_LEN);
			std::string deviceId = (char*)nvr_reg.szDeviceId;
			DetuNvrlist.addSessionId(curr_conn_->get_sessionid(), api_reg);
			SessionManage.updateSessionManageTable(curr_conn_->get_sessionid(), deviceId, 0);
			PVSManage.savePVSRegisterInfo(nvr_reg, curr_conn_->get_sessionid());

			//请求标定
			protocol_head_t prot_head_cali;
			response res_cali(prot_head_cali.get_size());

			prot_head_cali.nCmd = CMD_GET_CALIBRATION;
			prot_head_cali.nResult = RESULT_SUCCESS;
			prot_head_cali.nStreamId = 0;

			response_add_resprotocol<protocol_head_t>(res_cali, &prot_head_cali);

			if (curr_conn_ != NULL)
			{
				curr_conn_->do_write(res_cali);
			}

			//设置时间测试
			protocol_head_t prot_head_1;
			api_device_time_t set_time;

			prot_head_1.nDataLen = set_time.get_size();
			prot_head_1.nCmd = CMD_SET_M1_TIME;
			prot_head_1.nResult = RESULT_SUCCESS;
			prot_head_1.nStreamId = 0;

			std::string strTime = boost::posix_time::to_iso_string(\
				boost::posix_time::second_clock::local_time());

			// 这时候strTime里存放时间的格式是YYYYMMDDTHHMMSS，日期和时间用大写字母T隔开了    

			int pos = strTime.find('T');
			set_time.nYear = atoi(strTime.substr(0, 4).c_str());
			set_time.nMonth = atoi(strTime.substr(4, 2).c_str());
			set_time.nDay = atoi(strTime.substr(6, 2).c_str());

			set_time.nHour = atoi(strTime.substr(9, 2).c_str());
			set_time.nMinute = atoi(strTime.substr(11, 2).c_str());
			set_time.nSecond = atoi(strTime.substr(13, 2).c_str());
			//每天中午十二点第一分钟 校验时间
			if (set_time.nHour == 12 && set_time.nMinute == 00)
			{
				response res_1(prot_head_1.get_size() + set_time.get_size());
				response_add_resprotocol<protocol_head_t>(res_1, &prot_head_1);
				response_add_resprotocol<api_device_time_t>(res_1, &set_time);
				if (curr_conn_ != NULL)
				{
					curr_conn_->do_write(res_1);
				}
			}


/*
			//获取时间测试
			protocol_head_t prot_head_2;
			prot_head_2.nDataLen =0;
			prot_head_2.nCmd = CMD_GET_M1_TIME;
			prot_head_2.nResult = RESULT_SUCCESS;
			prot_head_2.nStreamId = 0;

			response res_2(prot_head_1.get_size());
			response_add_resprotocol<protocol_head_t>(res_2, &prot_head_2);


			if (curr_conn_ != NULL)
			{
				curr_conn_->do_write(res_2);
			}

			//设置分段存储测试
			protocol_head_t prot_head_2;
			api_record_policy_t set_record;

			prot_head_2.nDataLen = set_record.get_size();
			prot_head_2.nCmd = CMD_SET_RECORD_POLICY;
			prot_head_2.nResult = RESULT_SUCCESS;
			prot_head_2.nStreamId = 0;

			set_record.nAllDayRecord = 2;
			set_record.nSegmentNum = 168;

			for (int i = 0; i < set_record.nSegmentNum; i++)
			{
				set_record.szSegmentTime[i].nStartTime = i * 60;
				set_record.szSegmentTime[i].nEndTime = set_record.szSegmentTime[i].nStartTime + 30;
			}


			response res_2(prot_head_2.get_size()+set_record.get_size());
			response_add_resprotocol<protocol_head_t>(res_2, &prot_head_2);
			response_add_resprotocol<api_record_policy_t>(res_2, &set_record);

			if (curr_conn_ != NULL)
			{
				curr_conn_->do_write(res_2);
			}
			*/
			//查询分段存储测试
			protocol_head_t prot_head_3;
		
			prot_head_3.nDataLen = 0;
			prot_head_3.nCmd = CMD_GET_RECORD_POLICY;
			prot_head_3.nResult = RESULT_SUCCESS;
			prot_head_3.nStreamId = 0;

			response res_3(prot_head_3.get_size() );
			response_add_resprotocol<protocol_head_t>(res_3, &prot_head_3);

			if (curr_conn_ != NULL)
			{
				curr_conn_->do_write(res_3);
			}

			return 0;
        }

		int request_handler::handle_request_calibration_res(protocol_head_t *head, netbuffer *buf)
		{
			api_detu_client_register_res_t api_reg;
			//负载长度减去注册结构体长度，就是pts文件长度
			api_reg.pts.nPtsLen = head->nDataLen;
			std::memcpy(api_reg.pts.pts_data, buf->buffer + buf->buffer_offset, api_reg.pts.nPtsLen);
			buf->buffer_offset = buf->buffer_offset + api_reg.pts.nPtsLen;

			if (strstr((char*)api_reg.pts.pts_data, "pat.pts:") == NULL)
			{
				DetuNvrlist.addSessionId(curr_conn_->get_sessionid(), api_reg.m1DeviceId, api_reg.pts.nPtsLen, api_reg.pts.pts_data);
			}
			else
			{
				std::string temp = (char*)api_reg.pts.pts_data;
				std::string m1id = temp.substr(temp.size() - 6);
				DetuNvrlist.addSessionId(curr_conn_->get_sessionid(), (unsigned char*)m1id.c_str(), api_reg.pts.nPtsLen, api_reg.pts.pts_data);
				memset(api_reg.m1DeviceId, 0, API_ARRAY_LEN);
				memcpy(api_reg.m1DeviceId, m1id.c_str(), API_ARRAY_LEN);
			}
			PVSManage.saveCailbrationInfo(api_reg, curr_conn_->get_sessionid());
			return 0;
		}



		int request_handler::handle_request_detu_client_request_video(netbuffer *buf, unsigned char streamId, unsigned char deviceType)
        {                       
			api_detu_client_request_video_t *video_request = new api_detu_client_request_video_t;
			video_request->read(buf);
            api_request_video_t api_req_video;

			//读取srs的ip地址
            std::string rtmp_path = ConfigFileRead("srs");
			//客户端设备名称
			std::string device_id((char*)video_request->szDeviceId);

			//组装推流地址
			switch (streamId)
            {
            case RTMP_LIVE_MAIN1:
				rtmp_path = "rtmp://" + rtmp_path + ":1935/" + device_id + "_0" + "/0";
				memcpy(api_req_video.szRtmpURL, rtmp_path.c_str(), API_RTMP_LEN);
                break;
            case RTMP_LIVE_SUB1:
				rtmp_path = "rtmp://" + rtmp_path + ":1935/" + device_id + "_1" + "/1";
				memcpy(api_req_video.szRtmpURL, rtmp_path.c_str(), API_RTMP_LEN);
                break;
            case RTMP_BACK_MAIN1:
				rtmp_path = "rtmp://" + rtmp_path + ":1935/" + device_id + "_2" + "/2";
				memcpy(api_req_video.szRtmpURL, rtmp_path.c_str(), API_RTMP_LEN);
                break;
            case RTMP_BACK_SUB1:
				rtmp_path = "rtmp://" + rtmp_path + ":1935/" + device_id + "_3" + "/3";
				memcpy(api_req_video.szRtmpURL, rtmp_path.c_str(), API_RTMP_LEN);
                break;
			case RTMP_MAP_MAIN1:
				rtmp_path = "rtmp://" + rtmp_path + ":1935/" + device_id + "_4" + "/0";
				memcpy(api_req_video.szRtmpURL, rtmp_path.c_str(), API_RTMP_LEN);
				break;
			case RTMP_MAP_SUB1:
				rtmp_path = "rtmp://" + rtmp_path + ":1935/" + device_id + "_5" + "/1";
				memcpy(api_req_video.szRtmpURL, rtmp_path.c_str(), API_RTMP_LEN);
				break;
			case RTMP_MAP_BACK_MAIN1:
				rtmp_path = "rtmp://" + rtmp_path + ":1935/" + device_id + "_6" + "/2";
				memcpy(api_req_video.szRtmpURL, rtmp_path.c_str(), API_RTMP_LEN);
				break;
			case RTMP_MAP_BACK_SUB1:
				rtmp_path = "rtmp://" + rtmp_path + ":1935/" + device_id + "_7" + "/3";
				memcpy(api_req_video.szRtmpURL, rtmp_path.c_str(), API_RTMP_LEN);
				break;
            default:
                break;
            }
			Log::Info("dem1service:: request streamId : %s deviceType : %d", rtmp_path.c_str(), deviceType);

			//保存当前nvr被请求的推流地址，一会要发给客户端
			std::string request_nvr_session_id = DetuNvrlist.getSessionIdByDeivceId((char*)video_request->szDeviceId);
			DetuNvrlist.updateCurrentNvrRtmpPath(request_nvr_session_id, rtmp_path);

			switch (streamId)
			{
			case RTMP_MAP_MAIN1:
				streamId = 0;
				break;
			case RTMP_MAP_SUB1:
				streamId = 1;
				break;
			case RTMP_MAP_BACK_MAIN1:
				streamId = 2;
				break;
			case RTMP_MAP_BACK_SUB1:
				streamId = 3;
				break;
			default:
				break;
			}
		
			api_req_video.nStartTime = video_request->nStartTime;
			api_req_video.nEndTime = video_request->nStartTime;

			protocol_head_t prot_head;
			prot_head.nDataLen = api_req_video.get_size();
			prot_head.nCmd = CMD_REQUEST_VIDEO;
			prot_head.nResult = RESULT_SUCCESS;
			prot_head.nStreamId = streamId;
			prot_head.deviceNum = deviceType;

			response res(prot_head.get_size() + api_req_video.get_size());
			response_add_resprotocol<protocol_head_t>(res, &prot_head);
			response_add_resprotocol<api_request_video_t>(res, &api_req_video);

			std::string session_id = DetuNvrlist.getSessionIdByDeivceId((char*)video_request->szDeviceId);
			Log::Info("dem1service:: test get sessionId : %s", session_id.c_str());

			OnlineConnInfo_t conn_t;
			switch (deviceType)
			{
			case SERVER_TYPE_CLINET:
				conn_t.client_session = curr_conn_->get_sessionid();
				conn_t.cmd_id = CMD_REQUEST_VIDEO_RES;
				conn_t.pvs_session = session_id;
				OnlineConnListIns.AddOnlineConn(conn_t);
				break;
			case SERVER_TYPE_TCS:
				TCSManage.updatePushFlowDevice(device_id, curr_conn_->get_sessionid());
				SessionManage.updatePushFlowDevice(device_id, curr_conn_->get_sessionid(), deviceType);
				break;
			default:
				break;
			}

			std::shared_ptr<connection> conn = curr_conn_->connection_manager_.get_connect(session_id);
			if (conn != NULL){
				conn->do_write(res);
			}
            return 0;
        }


		int request_handler::handle_request(unsigned char result, unsigned char streamId)
		{

			//先找到对应设备
			OnlineConnInfo_t conn_t;
			std::vector<std::string> list_t;
			conn_t.cmd_id = CMD_PLAYBACK_CONTROL_RES;
			conn_t.pvs_session = curr_conn_->get_sessionid();
			list_t = OnlineConnListIns.GetList(conn_t);

			protocol_head_t prot_head;
			prot_head.nStreamId = streamId;
			prot_head.nDataLen = 0;
			prot_head.nCmd = CMD_DETU_CLIENT_PLAYBACK_CONTROL_RES;
			if (result == 0)
			{
				prot_head.nResult = RESULT_SUCCESS;
			}
			else
			{
				prot_head.nResult = RESULT_FAILED;
			}
			response res(prot_head.get_size());
			response_add_resprotocol<protocol_head_t>(res, &prot_head);

			//快进
			//找到对应设备发送
			for (std::vector<std::string>::iterator it = list_t.begin(); it != list_t.end(); ++it)
			{
				Log::Info("dem1service:: test send Data to client : %s", (*it).c_str());
				std::shared_ptr<connection> conn = curr_conn_->connection_manager_.get_connect(*it);
				if (conn != NULL){
					conn->do_write(res);
				}
			}

			return 0;
		}

		int request_handler::handle_request(std::string session_id_,int n, netbuffer *buf, unsigned char streamId)
		{
			protocol_head_t prot_head;
			api_detu_client_disk_size_t disk_size;
			prot_head.nDataLen = disk_size.get_size() * n;
			prot_head.nCmd = CMD_DETU_CLIENT_DISKINFO_RES;
			prot_head.nResult = RESULT_SUCCESS;
			prot_head.nStreamId = streamId;

			response res(prot_head.get_size() + disk_size.get_size() * n);
			response_add_resprotocol<protocol_head_t>(res, &prot_head);
			std::string deviceNo = DetuNvrlist.getDeviceIdBySessionld(session_id_);
			for (int i = 0; i < n; i++)
			{
				api_disk_info_t *api_query = new api_disk_info_t();
				api_query->read(buf);
				disk_size.nCurDiskNum = api_query->nCurDiskNum;
				disk_size.nDiskId = api_query->nDiskId;
				disk_size.nDiskStatus = api_query->nDiskStatus;
				disk_size.nDiskType = api_query->nDiskType;
				disk_size.nTotalDiskNum = api_query->nTotalDiskNum;
				disk_size.nTotalDiskSize = api_query->nTotalDiskSize;
				disk_size.nUsedSize = api_query->nUsedSize;
				memcpy(disk_size.szDeviceId, deviceNo.c_str(), API_ARRAY_LEN);
				response_add_resprotocol<api_detu_client_disk_size_t>(res, &disk_size);

				delete api_query;
			
			}

			std::vector<std::string> list_t;
			OnlineConnInfo_t conn_t;
			conn_t.pvs_session = "disk";
			conn_t.cmd_id = (int)CMD_GET_DISKINFO_RES;
			list_t = OnlineConnListIns.GetList(conn_t);
			for (std::vector<std::string>::iterator it = list_t.begin(); it != list_t.end(); ++it)
			{
				std::shared_ptr<connection> conn = curr_conn_->connection_manager_.get_connect(*it);
				if (conn != NULL){
					conn->do_write(res);
				}
			}
			return 0;
		}

		int request_handler::handle_request(std::string session_id_, unsigned short result, unsigned char streamId)
		{
			//格式化
			//先找到对应设备
			OnlineConnInfo_t conn_t;
			std::vector<std::string> list_t;
			conn_t.cmd_id = CMD_DISK_FORMAT_RES;
			conn_t.pvs_session = curr_conn_->get_sessionid();
			list_t = OnlineConnListIns.GetList(conn_t);



			protocol_head_t prot_head;
			prot_head.nDataLen = 0;
			prot_head.nCmd = CMD_DETU_CLIENT_DISK_FORMAT_RES;
			prot_head.nStreamId = streamId;

			response res(prot_head.get_size());

			if (result == 0){
				prot_head.nResult = RESULT_SUCCESS;
			}
			else{
				prot_head.nResult = RESULT_FAILED;
			}

			response_add_resprotocol<protocol_head_t>(res, &prot_head);

			//找到对应设备发送
			for (std::vector<std::string>::iterator it = list_t.begin(); it != list_t.end(); ++it)
			{
				Log::Info("dem1service:: test send Data to client : %s", (*it).c_str());
				std::shared_ptr<connection> conn = curr_conn_->connection_manager_.get_connect(*it);
				if (conn != NULL){
					conn->do_write(res);
				}
			}

			return 0;
		}

		int request_handler::handle_request_close_video(unsigned short result)
		{
			std::string PVSID = DetuNvrlist.getDeviceIdBySessionld(curr_conn_->get_sessionid());
			if (result == RESULT_SUCCESS)
			{
				int num = 0;
				bool ret = PVSManage.getPushFlowNum(PVSID, num);
				if (ret && num >0)
				{
					num--;
					PVSManage.updatePushFlowNum(PVSID, num);
				}
			}
			return 1;
		}

		int request_handler::handle_request_report_name(netbuffer *buf, std::string session_id_)
		{
			api_detu_client_register_res_t api_detu;
			api_detu.read(buf);
			DetuNvrlist.saveDeviceName(session_id_, api_detu);
			PVSManage.saveDeviceInfo(api_detu);

			std::vector<api_detu_client_register_res_t> nvrList;
			nvrList.clear();
			nvrList.resize(0);
			std::vector<api_detu_client_register_res_t>::iterator it;
			PVSManage.getPVSRegisterInfo(nvrList);

			int index = 1;
			if (nvrList.size() != 0)
			{
				it = nvrList.begin();
				while (it != nvrList.end())
				{
					api_detu_client_register_res_t api_res_t;
					memcpy(api_res_t.szDeviceId, it->szDeviceId, API_ARRAY_LEN);
					memcpy(api_res_t.szName, it->szName, API_ARRAY_LEN);
					memcpy(api_res_t.m1DeviceId, it->m1DeviceId, API_ARRAY_LEN);
					api_res_t.online = it->online;
					api_res_t.szUpDown = it->szUpDown;
					api_res_t.curr_num = index;
					api_res_t.total_num = nvrList.size();
					api_res_t.pts.nPtsLen = it->pts.nPtsLen;
					memcpy(api_res_t.pts.pts_data, it->pts.pts_data, API_PTS_LEN);

					protocol_head_t port_detu_head;
					response res(port_detu_head.get_size() + api_res_t.get_size());

					port_detu_head.nCmd = CMD_DETU_CLIENT_GET_LIST_RES;
					port_detu_head.nResult = RESULT_SUCCESS;
					port_detu_head.nDataLen = api_res_t.get_size();
					port_detu_head.nStreamId = 0;
					response_add_resprotocol<protocol_head_t>(res, &port_detu_head);
					response_add_resprotocol<api_detu_client_register_res_t>(res, &api_res_t);

					std::vector<std::string> sessionList;
					bool ret = SessionManage.getSessionIdByTypeFromTable(sessionList, 1);
					if (ret)
					{
						for (int i = 0; i < sessionList.size(); ++i)
						{
							std::shared_ptr<connection> conn = curr_conn_->connection_manager_.get_connect(sessionList[i]);
							if (conn != NULL){
								conn->do_write(res);
							}
						}
					}
					index++;
					it++;
				}
			}
			return 0;
		}

		int request_handler::handle_request_ptz_register(netbuffer *buf, unsigned char streamId)
		{
			PTZManageTable_t api_detu;
			api_detu.read(buf);
			bool ret = PTZManage.updatePTZDeviceToTable(api_detu);

			protocol_head_t port_detu_head;
			port_detu_head.nCmd = CMD_DETU_PTZ_REGISTER_RES;
			port_detu_head.nResult = ret ? RESULT_SUCCESS : RESULT_FAILED;
			port_detu_head.nDataLen = 0;
			port_detu_head.nStreamId = streamId;

			response res(port_detu_head.get_size());
			response_add_resprotocol<protocol_head_t>(res, &port_detu_head);
			Log::Info("dem1service:: register ptz : cmd : %d  result : %d", port_detu_head.nCmd, port_detu_head.nResult);

			if (curr_conn_ != NULL){
				curr_conn_->do_write(res);
			}
			this->handle_request_get_ptz_list();
			return 0;
		}

		int request_handler::handle_request_spy_register(netbuffer *buf, unsigned char streamId)
		{
			SPYManageTable_t api_detu;
			api_detu.read(buf);
			bool ret = SPYManage.updateSPYDeviceToTable(api_detu);

			protocol_head_t port_detu_head;
			port_detu_head.nCmd = CMD_DETU_SPY_REGISTER_RES;
			port_detu_head.nResult = ret ? RESULT_SUCCESS : RESULT_FAILED;
			port_detu_head.nDataLen = 0;
			port_detu_head.nStreamId = streamId;

			response res(port_detu_head.get_size());
			response_add_resprotocol<protocol_head_t>(res, &port_detu_head);
			Log::Info("dem1service:: register spy : cmd : %d  result : %d", port_detu_head.nCmd, port_detu_head.nResult);

			if (curr_conn_ != NULL){
				curr_conn_->do_write(res);
			}
			this->handle_request_get_spy_list();
			return 0;
		}

		//获取当前流
		int request_handler::handle_request_get_stream(netbuffer *buf)
		{
			api_detu_client_av_param_t *api_query = new api_detu_client_av_param_t;
			api_query->read(buf);

			api_av_param api_av;
			protocol_head_t prot_head;
			prot_head.nDataLen = 0;
			prot_head.nCmd = CMD_GET_STREAM;
			prot_head.nResult = RESULT_SUCCESS;
			prot_head.nStreamId = 3;

			response res(prot_head.get_size());
			response_add_resprotocol<protocol_head_t>(res, &prot_head);
			Log::Info("dem1service:: Get Stream: cmd:%d streamID:%d", prot_head.nCmd, prot_head.nStreamId);

 			std::string session_id = DetuNvrlist.getSessionIdByDeivceId((char*)api_query->szDeviceId);
 			std::shared_ptr<connection> conn = curr_conn_->connection_manager_.get_connect(session_id);

			//添加到在线列表
			OnlineConnInfo_t conn_t;
			conn_t.client_session = curr_conn_->get_sessionid();
			conn_t.pvs_session = conn->get_sessionid();
			conn_t.cmd_id = (int)CMD_STREAM_HANDLE_RES;
			OnlineConnListIns.AddOnlineConn(conn_t);

 			if (conn != NULL){
 				conn->do_write(res);
 			}
			return 0;
		}

		int request_handler::handle_request_add_stream(netbuffer *buf, unsigned char streamId)
		{
			api_detu_client_av_param_t *api_query = new api_detu_client_av_param_t;
			api_query->read(buf);

			api_av_param api_av;
			protocol_head_t prot_head;
			prot_head.nDataLen = 0;
			prot_head.nCmd = CMD_ADD_STREAM;
			prot_head.nResult = RESULT_SUCCESS;
			prot_head.nStreamId = streamId;

			response res(prot_head.get_size());
			response_add_resprotocol<protocol_head_t>(res, &prot_head);
			Log::Info("dem1service:: Add Stream: cmd:%d streamID:%d", prot_head.nCmd, prot_head.nStreamId);

			std::string session_id = DetuNvrlist.getSessionIdByDeivceId((char*)api_query->szDeviceId);
			std::shared_ptr<connection> conn = curr_conn_->connection_manager_.get_connect(session_id);

			//添加到在线列表
			OnlineConnInfo_t conn_t;
			conn_t.client_session = curr_conn_->get_sessionid();
			conn_t.pvs_session = conn->get_sessionid();
			conn_t.cmd_id = (int)CMD_STREAM_HANDLE_RES;
			OnlineConnListIns.AddOnlineConn(conn_t);

			if (conn != NULL){
				conn->do_write(res);
			}
			return 0;
		}

		int request_handler::handle_request_del_stream(netbuffer *buf, unsigned char streamId)
		{
			api_detu_client_av_param_t *api_query = new api_detu_client_av_param_t;
			api_query->read(buf);

			api_av_param api_av;
			protocol_head_t prot_head;
			prot_head.nDataLen = 0;
			prot_head.nCmd = CMD_DEL_STREAM;
			prot_head.nResult = RESULT_SUCCESS;
			prot_head.nStreamId = 2;

			response res(prot_head.get_size());
			response_add_resprotocol<protocol_head_t>(res, &prot_head);
			Log::Info("dem1service:: Del Stream: cmd:%d streamID:%d", prot_head.nCmd, prot_head.nStreamId);

			std::string session_id = DetuNvrlist.getSessionIdByDeivceId((char*)api_query->szDeviceId);
			std::shared_ptr<connection> conn = curr_conn_->connection_manager_.get_connect(session_id);

			//添加到在线列表
			OnlineConnInfo_t conn_t;
			conn_t.client_session = curr_conn_->get_sessionid();
			conn_t.pvs_session = conn->get_sessionid();
			conn_t.cmd_id = (int)CMD_STREAM_HANDLE_RES;
			OnlineConnListIns.AddOnlineConn(conn_t);

			if (conn != NULL){
				conn->do_write(res);
			}
			return 0;
		}

		int request_handler::handle_request_handle_stream_res(short result, unsigned char streamId)
		{
			//先找到对应设备
			OnlineConnInfo_t conn_t;
			std::vector<std::string> list_t;
			conn_t.cmd_id = CMD_STREAM_HANDLE_RES;
			conn_t.pvs_session = curr_conn_->get_sessionid();
			list_t = OnlineConnListIns.GetList(conn_t);

			protocol_head_t prot_head;
			prot_head.nDataLen = 0;
			prot_head.nCmd = CMD_DETU_CLIENT_STREAM_HANDLE_RES;
			prot_head.nResult = result;
			prot_head.nStreamId = streamId;

			response res(prot_head.get_size());
			response_add_resprotocol<protocol_head_t>(res, &prot_head);
			Log::Info("dem1service:: Stream Handle Res: cmd:%d result:%d streamID:%d", prot_head.nCmd, prot_head.nResult, prot_head.nStreamId);

			//找到对应设备发送
			for (std::vector<std::string>::iterator it = list_t.begin(); it != list_t.end(); ++it)
			{
				Log::Info("dem1service:: test send Data to client : %s", (*it).c_str());
				std::shared_ptr<connection> conn = curr_conn_->connection_manager_.get_connect(*it);
				if (conn != NULL){
					conn->do_write(res);
				}
			}
			return 0;
		}

		int request_handler::handle_request_reboot_device(netbuffer *buf, unsigned char streamId)
		{
			api_detu_client_av_param_t *api_query = new api_detu_client_av_param_t;
			api_query->read(buf);

			api_av_param api_av;
			protocol_head_t prot_head;
			prot_head.nDataLen = 0;
			prot_head.nCmd = CMD_DEVICE_RESTART;
			prot_head.nResult = RESULT_SUCCESS;
			prot_head.nStreamId = streamId;

			response res(prot_head.get_size());
			response_add_resprotocol<protocol_head_t>(res, &prot_head);
			Log::Info("dem1service:: Reboot Device: cmd:%d streamID:%d", prot_head.nCmd, prot_head.nStreamId);


			std::string session_id = DetuNvrlist.getSessionIdByDeivceId((char*)api_query->szDeviceId);
			std::shared_ptr<connection> conn = curr_conn_->connection_manager_.get_connect(session_id);

			//添加到在线列表
			OnlineConnInfo_t conn_t;
			conn_t.client_session = curr_conn_->get_sessionid();
			conn_t.pvs_session = conn->get_sessionid();
			conn_t.cmd_id = (int)CMD_DEVICE_RESTART_RES;
			OnlineConnListIns.AddOnlineConn(conn_t);

			if (conn != NULL){
				conn->do_write(res);
			}
			return 0;
		}

		int request_handler::handle_request_reboot_device_res(short result, unsigned char streamId)
		{

			//先找到对应设备
			OnlineConnInfo_t conn_t;
			std::vector<std::string> list_t;
			conn_t.cmd_id = CMD_DEVICE_RESTART_RES;
			conn_t.pvs_session = curr_conn_->get_sessionid();
			list_t = OnlineConnListIns.GetList(conn_t);

			protocol_head_t prot_head;
			prot_head.nDataLen = 0;
			prot_head.nCmd = CMD_DETU_CLIENT_DEVICE_REBOOT_RES;
			prot_head.nResult = result;
			prot_head.nStreamId = streamId;

			response res(prot_head.get_size());
			response_add_resprotocol<protocol_head_t>(res, &prot_head);
			Log::Info("dem1service:: Reboot Device Res: cmd:%d result:%d streamID:%d", prot_head.nCmd, prot_head.nResult, prot_head.nStreamId);

			// 重启相机
			//找到对应设备发送
			for (std::vector<std::string>::iterator it = list_t.begin(); it != list_t.end(); ++it)
			{
				Log::Info("dem1service:: test send Data to client : %s", (*it).c_str());
				std::shared_ptr<connection> conn = curr_conn_->connection_manager_.get_connect(*it);
				if (conn != NULL){
					conn->do_write(res);
				}
			}
			return 0;
		}

		int request_handler::handle_request_app_register(netbuffer *buf)
		{
			api_detu_app_register_t detu_app;
			detu_app.read(buf);

			std::string appID = (char*)detu_app.appId;
			std::string pvsID = (char*)detu_app.pvsId;
			Log::Info("dem1service:: recieve detu app %s register, pvsID : %s", appID.c_str(), pvsID.c_str());

			//当前设备是否存在未释放的链路
			if (!DetuAPPlist.isDeviceIdExist(appID))
			{

				DetuAPPlist.addSessionId(curr_conn_->get_sessionid(), appID);
			}
			else
			{
				DetuAPPlist.replaceSessionId(curr_conn_->get_sessionid(), appID);
			}
			SessionManage.updateSessionManageTable(curr_conn_->get_sessionid(), appID, 3);
			std::string nvr_session_id = DetuNvrlist.getSessionIdByDeivceId(pvsID);
			std::string rtmp_path = DetuNvrlist.getRtmpPathByDeivceId(nvr_session_id);

			protocol_head_t port_detu_head;
			api_detu_app_register_res_t api_res_t;
			response res(port_detu_head.get_size() + api_res_t.get_size());
			port_detu_head.nCmd = CMD_DETU_APP_REGISTER_RES;
			port_detu_head.nResult = RESULT_SUCCESS;
			port_detu_head.nDataLen = api_res_t.get_size();
			port_detu_head.nStreamId = 0;

			memcpy(api_res_t.szRtmpURL, rtmp_path.c_str(), rtmp_path.length());

			std::map < std::string, api_pts_file_t>   ptsList = DetuNvrlist.getPtsList();
			std::map < std::string, api_pts_file_t>::iterator it = ptsList.begin();
			while (it != ptsList.end())
			{
				if (it->first == pvsID)
				{
					api_res_t.pts.nPtsLen = it->second.nPtsLen;
					memcpy(api_res_t.pts.pts_data, it->second.pts_data, API_PTS_LEN);
				}
				it++;
			}
			Log::Info("dem1service:: return rtmpUrl to app : %s    pts_length : %d", rtmp_path.c_str(), api_res_t.pts.nPtsLen);
			if (rtmp_path.empty() || api_res_t.pts.nPtsLen == 0)
			{
				port_detu_head.nResult = RESULT_FAILED;
			}
			response_add_resprotocol<protocol_head_t>(res, &port_detu_head);
			response_add_resprotocol<api_detu_app_register_res_t>(res, &api_res_t);

			std::string session_id = DetuAPPlist.getSessionIdByDeivceId(appID);
			std::shared_ptr<connection> conn = curr_conn_->connection_manager_.get_connect(session_id);
			if (conn != NULL){
				conn->do_write(res);
			}
			return 0;
		}

		int request_handler::handle_request_report_pts_data(netbuffer *buf, std::string session_id_)
		{
			api_detu_client_optmize api_detu;
			api_detu.read(buf);
			DetuNvrlist.savePTSData(session_id_, api_detu);
			PVSManage.saveOptmizeCailbrationInfo(api_detu);

			protocol_head_t port_detu_head;
			port_detu_head.nCmd = CMD_DETU_CLIENT_REPORT_OPTIMIZE_PTS_RES;
			port_detu_head.nResult = RESULT_SUCCESS;
			port_detu_head.nDataLen = 0;
			port_detu_head.nStreamId = 0;

			response res(port_detu_head.get_size());
			response_add_resprotocol<protocol_head_t>(res, &port_detu_head);
			Log::Info("dem1service:: Reboot Device Res: cmd:%d result:%d", port_detu_head.nCmd, port_detu_head.nResult);

			if (curr_conn_ != NULL){
				curr_conn_->do_write(res);
			}
			return 0;
		}

		int request_handler::handle_request_active_report(std::string session_id_, unsigned short result, unsigned char streamId)
		{
			std::string pvsID = DetuNvrlist.getDeviceIdBySessionld(session_id_);

			active_report_body_t api_detu;
			protocol_head_t port_detu_head;
			port_detu_head.nCmd = CMD_DETU_CLIENT_ACTIVE_REPORT;
			port_detu_head.nResult = RESULT_SUCCESS;
			port_detu_head.nDataLen = api_detu.get_size();
			port_detu_head.nStreamId = streamId;

			api_detu.nErrorCode = result;
			memcpy(api_detu.pvsId, pvsID.c_str(), API_ARRAY_LEN);
			response res(port_detu_head.get_size() + api_detu.get_size());
			response_add_resprotocol<protocol_head_t>(res, &port_detu_head);
			response_add_resprotocol<active_report_body_t>(res, &api_detu);
			Log::Info("dem1service:: report PVS active : cmd : %d result : %d streamId : %d", port_detu_head.nCmd, api_detu.nErrorCode, streamId);

			std::vector<std::string> sessionList;
			bool ret = SessionManage.getSessionIdByTypeFromTable(sessionList, 1);
			if (ret)
			{
				for (int i = 0; i < sessionList.size(); ++i)
				{
					std::shared_ptr<connection> conn = curr_conn_->connection_manager_.get_connect(sessionList[i]);
					if (conn != NULL){
						conn->do_write(res);
					}
				}
			}
			return 0;
		}

		int request_handler::handle_request_get_bandWidth(netbuffer *buf)
		{
			PVSManageTable_t *prot_body = new PVSManageTable_t;
			prot_body->read(buf);


			std::string pvsId = (char*)prot_body->pvsID;
			PVSManageTable_t api_body;
			if (PVSManage.getBandWidthFromTable(pvsId, api_body))
			{
				Log::Info("dem1service:: select data from PVSManageTable success");
				protocol_head_t port_detu_head;
				port_detu_head.nCmd = CMD_DETU_CLIENT_GET_BANDWIDTH_RES;
				port_detu_head.nResult = RESULT_SUCCESS;
				port_detu_head.nDataLen = api_body.get_size();
				port_detu_head.nStreamId = 0;

				response res(port_detu_head.get_size() + api_body.get_size());
				response_add_resprotocol<protocol_head_t>(res, &port_detu_head);
				response_add_resprotocol<PVSManageTable_t>(res, &api_body);
				Log::Info("dem1service:: get bandWidth: cmd : %d m1 : %d pvs : %d", port_detu_head.nCmd, api_body.nStream1Status, api_body.nStream2Status);

				if (curr_conn_ != NULL){
					curr_conn_->do_write(res);
				}
			}
			return 0;
		}

		int request_handler::handle_request_get_ptz_list()
		{
			PTZManageTableList_t ptzList;
			PTZManage.getPTZDeviceFromTable(ptzList);

			protocol_head_t port_detu_head;
			port_detu_head.nCmd = CMD_DETU_CLIENT_GET_PTZ_LIST_RES;
			port_detu_head.nResult = RESULT_SUCCESS;
			port_detu_head.nDataLen = ptzList.get_size();
			port_detu_head.nStreamId = 0;

			response res(port_detu_head.get_size() + ptzList.get_size());
			response_add_resprotocol<protocol_head_t>(res, &port_detu_head);
			response_add_resprotocol<PTZManageTableList_t>(res, &ptzList);
			Log::Info("dem1service:: get ptz list: cmd : %d list num : %d", port_detu_head.nCmd, ptzList.numlist);

			if (curr_conn_ != NULL){
				curr_conn_->do_write(res);
			}
			return 0;
		}

		int request_handler::handle_request_get_spy_list()
		{
			SPYManageTableList_t spyList;
			SPYManage.getSPYDeviceFromTable(spyList);

			protocol_head_t port_detu_head;
			port_detu_head.nCmd = CMD_DETU_CLIENT_GET_SPY_LIST_RES;
			port_detu_head.nResult = RESULT_SUCCESS;
			port_detu_head.nDataLen = spyList.get_size();
			port_detu_head.nStreamId = 0;

			response res(port_detu_head.get_size() + spyList.get_size());
			response_add_resprotocol<protocol_head_t>(res, &port_detu_head);
			response_add_resprotocol<SPYManageTableList_t>(res, &spyList);
			Log::Info("dem1service:: get spy list: cmd : %d list num : %d", port_detu_head.nCmd, spyList.numlist);

			if (curr_conn_ != NULL){
				curr_conn_->do_write(res);
			}
			return 0;
		}

		int request_handler::handle_request_delete_ptz(netbuffer *buf)
		{
			PTZManageTable_t prot_table;
			prot_table.read(buf);
			bool ret = PTZManage.deletePTZDeviceToTable((char*)prot_table.nIP);

			protocol_head_t port_detu_head;
			port_detu_head.nCmd = CMD_DETU_DELETE_PTZ_RES;
			port_detu_head.nResult = ret ? RESULT_SUCCESS : RESULT_FAILED;
			port_detu_head.nDataLen = 0;
			port_detu_head.nStreamId = 0;

			response res(port_detu_head.get_size());
			response_add_resprotocol<protocol_head_t>(res, &port_detu_head);
			Log::Info("dem1service:: delete ptz device: cmd : %d device ip : %s", port_detu_head.nCmd, prot_table.nIP);

			if (curr_conn_ != NULL){
				curr_conn_->do_write(res);
			}

			this->handle_request_get_ptz_list();
			return 0;
		}

		int request_handler::handle_request_delete_spy(netbuffer *buf)
		{
			SPYManageTable_t prot_table;
			prot_table.read(buf);
			bool ret = SPYManage.deleteSPYDeviceToTable((char*)prot_table.nIP);

			protocol_head_t port_detu_head;
			port_detu_head.nCmd = CMD_DETU_DELETE_SPY_RES;
			port_detu_head.nResult = ret ? RESULT_SUCCESS : RESULT_FAILED;
			port_detu_head.nDataLen = 0;
			port_detu_head.nStreamId = 0;

			response res(port_detu_head.get_size());
			response_add_resprotocol<protocol_head_t>(res, &port_detu_head);
			Log::Info("dem1service:: delete spy device: cmd : %d device ip : %s", port_detu_head.nCmd, prot_table.nIP);


			if (curr_conn_ != NULL){
				curr_conn_->do_write(res);
			}

			this->handle_request_get_spy_list();
			return 0;
		}

		int request_handler::handle_request_save_ptz_point(netbuffer *buf)
		{
			PtzPoint_t detu_reg;
			detu_reg.read(buf);

			bool ret = PTZManage.savePTZPoint(detu_reg);
			protocol_head_t port_detu_head;
			port_detu_head.nCmd = CMD_DETU_SAVE_PTZ_POINT_RES;
			port_detu_head.nResult = ret ? RESULT_SUCCESS : RESULT_FAILED;
			port_detu_head.nDataLen = 0;
			port_detu_head.nStreamId = 0;

			response res(port_detu_head.get_size());
			response_add_resprotocol<protocol_head_t>(res, &port_detu_head);
			Log::Info("dem1service:: save ptz point device: cmd : %d device ip : %s", port_detu_head.nCmd, detu_reg.nIP);

			if (curr_conn_ != NULL){
				curr_conn_->do_write(res);
			}
			return 0;
		}

		int request_handler::handle_request_get_ptz_point(netbuffer *buf)
		{
			PtzPoint_t detu_reg;
			detu_reg.read(buf);

			bool ret = PTZManage.getPTZPoint(detu_reg);
			protocol_head_t port_detu_head;
			port_detu_head.nCmd = CMD_DETU_GET_PTZ_POINT_RES;
			port_detu_head.nResult = ret ? RESULT_SUCCESS : RESULT_FAILED;
			port_detu_head.nDataLen = detu_reg.get_size();
			port_detu_head.nStreamId = 0;

			response res(port_detu_head.get_size() + detu_reg.get_size());
			response_add_resprotocol<protocol_head_t>(res, &port_detu_head);
			response_add_resprotocol<PtzPoint_t>(res, &detu_reg);
			Log::Info("dem1service:: get ptz point device: cmd : %d device ip : %s", port_detu_head.nCmd, detu_reg.nIP);

			if (curr_conn_ != NULL){
				curr_conn_->do_write(res);
			}
			return 0;
		}

		int request_handler::handle_request_tcs_register(netbuffer *buf)
		{
			api_detu_tcs_register_t detu_reg;
			detu_reg.read(buf);
			std::string sessionID = curr_conn_->get_sessionid();
			std::string serverID = boost::lexical_cast<std::string>(detu_reg.nServerId);
			SessionManage.updateSessionManageTable(sessionID, serverID, 2);

			int ret = TCSManage.saveTCSRegisterInfoToTable(detu_reg, sessionID);
			if (ret == RESULT_SUCCESS)
			{
				protocol_head_t port_detu_head;
				port_detu_head.nCmd = CMD_DETU_CLIENT_GET_TCS_INFO;
				port_detu_head.nResult = RESULT_SUCCESS;
				port_detu_head.nDataLen = detu_reg.get_size();
				port_detu_head.nStreamId = 0;

				response res(port_detu_head.get_size() + detu_reg.get_size());
				response_add_resprotocol<protocol_head_t>(res, &port_detu_head);
				response_add_resprotocol<api_detu_tcs_register_t>(res, &detu_reg);

				std::vector<std::string> sessionList;
				bool ret = SessionManage.getSessionIdByTypeFromTable(sessionList, 1);
				if (ret)
				{
					for (int i = 0; i < sessionList.size(); ++i)
					{
						std::shared_ptr<connection> conn = curr_conn_->connection_manager_.get_connect(sessionList[i]);
						if (conn != NULL){
							conn->do_write(res);
						}
					}
				}
			}

			protocol_head_t port_detu_head;
			port_detu_head.nCmd = CMD_DETU_TCS_REGISTER_RES;
			port_detu_head.nResult = ret;
			port_detu_head.nDataLen = 0;
			port_detu_head.nStreamId = 0;

			response res(port_detu_head.get_size());
			response_add_resprotocol<protocol_head_t>(res, &port_detu_head);
			Log::Info("dem1service:: get TCS register info: cmd : %d serverId  : %d", port_detu_head.nCmd, detu_reg.nServerId);

			if (curr_conn_ != NULL)
			{
				curr_conn_->do_write(res);
			}
			return 0;
		}

		int request_handler::handle_request_tcs_heartbeat(netbuffer *buf)
		{
			api_detu_tcs_heartbeat_t detu_reg;
			detu_reg.read(buf);

			bool ret = TCSManage.updateTCSDataToTable(detu_reg);
			if (ret)
			{
				protocol_head_t port_detu_head;
				port_detu_head.nCmd = CMD_DETU_CLIENT_UPDATE_TCSINFO;
				port_detu_head.nResult = RESULT_SUCCESS;
				port_detu_head.nDataLen = detu_reg.get_size();
				port_detu_head.nStreamId = 0;

				response res(port_detu_head.get_size() + detu_reg.get_size());
				response_add_resprotocol<protocol_head_t>(res, &port_detu_head);
				response_add_resprotocol<api_detu_tcs_heartbeat_t>(res, &detu_reg);

				std::vector<std::string> sessionList;
				bool ret = SessionManage.getSessionIdByTypeFromTable(sessionList, 1);
				if (ret)
				{
					for (int i = 0; i < sessionList.size(); ++i)
					{
						std::shared_ptr<connection> conn = curr_conn_->connection_manager_.get_connect(sessionList[i]);
						if (conn != NULL){
							conn->do_write(res);
						}
					}
				}
			}

			protocol_head_t port_detu_head;
			port_detu_head.nCmd = CMD_DETU_TCS_HEARTBEAT_RES;
			port_detu_head.nResult = RESULT_SUCCESS;
			port_detu_head.nDataLen = 0;
			port_detu_head.nStreamId = 0;

			response res(port_detu_head.get_size());
			response_add_resprotocol<protocol_head_t>(res, &port_detu_head);
	
			if (curr_conn_ != NULL)
			{
				curr_conn_->do_write(res);
			}
			return 0;
		}

		int request_handler::handle_request_tcs_offline(unsigned int nServerId)
		{
			api_detu_tcs_register_t detu_reg;
			detu_reg.nServerId = nServerId;

			protocol_head_t port_detu_head;
			port_detu_head.nCmd = CMD_DETU_CLINET_TCS_OFFLINE;
			port_detu_head.nResult = RESULT_SUCCESS;
			port_detu_head.nDataLen = detu_reg.get_size();
			port_detu_head.nStreamId = 0;

			response res(port_detu_head.get_size() + detu_reg.get_size());
			response_add_resprotocol<protocol_head_t>(res, &port_detu_head);
			response_add_resprotocol<api_detu_tcs_register_t>(res, &detu_reg);

			std::vector<std::string> sessionList;
			bool ret = SessionManage.getSessionIdByTypeFromTable(sessionList, 1);
			if (ret)
			{
				for (int i = 0; i < sessionList.size(); ++i)
				{
					std::shared_ptr<connection> conn = curr_conn_->connection_manager_.get_connect(sessionList[i]);
					if (conn != NULL){
						conn->do_write(res);
					}
				}
			}

			return 0;
		}

		int request_handler::handle_request_tcs_reset()
		{
			protocol_head_t port_detu_head;
			port_detu_head.nCmd = CMD_DETU_CLIENT_TCS_RESET_RES;
			port_detu_head.nDataLen = 0;
			port_detu_head.nStreamId = 0;

			bool ret = TCSManage.clearData();
			if (ret)
			{
				port_detu_head.nResult = RESULT_SUCCESS;
			}
			else
			{
				port_detu_head.nResult = RESULT_FAILED;
			}

			response res(port_detu_head.get_size());
			response_add_resprotocol<protocol_head_t>(res, &port_detu_head);

			if (curr_conn_ != NULL){
				curr_conn_->do_write(res);
			}

			return 0;
		}

		int request_handler::handle_request_set_m1_time(netbuffer *buf)
		{
			int a = 0;

			return 0;
		}

		int request_handler::handle_request_get_m1_time(netbuffer *buf)
		{
			api_device_time_t get_time;

			get_time.read(buf);

			return 0;
		}

		int request_handler::handle_request_set_record(netbuffer *buf)
		{

			return 0;
		}

		int request_handler::handle_request_get_record(netbuffer *buf)
		{
			api_record_policy_t set_record;
			set_record.read(buf);
			return 0;
		}

		int request_handler::handle_request_set_map_data(netbuffer *buf)
		{

			api_detu_vr_map_data_block api_detu;
			api_detu.read(buf);

			if (api_detu.offset == API_MAP_DATA_BLOCK_LEN)
			{
				remove("Map.zip");
			}

			FILE* map_zip = fopen("Map.zip", "ab+");
			if (map_zip)
			{
				fseek(map_zip, 0, SEEK_END);
				int sts = fwrite(api_detu.data, 1, API_MAP_DATA_BLOCK_LEN, map_zip);
				if (sts == 0)
				{
					Log::Debug("dem1service:: sts = fread(map_data, 1, map_data_length, pat_pts) failed");
					fclose(map_zip);
				}
			}
			fclose(map_zip);
			Log::Info("dem1service:: handle_request_set_map_data info: length : %d  offset  : %d", api_detu.length / API_MAP_DATA_BLOCK_LEN, api_detu.offset / API_MAP_DATA_BLOCK_LEN);

			return 0;
		}

		int request_handler::handle_request_get_map_data(netbuffer *buf)
		{
			//读取map.zip,并且循环发送
			fstream _file;
			_file.open("Map.zip", ios::in);

			//检测文件是否存在
			if (!_file)
			{
				Log::Info("dem1service:: MapWgt::SendMapDataThreadFunc()::Map.zip not exists!!");
				return 0;
			}
			//获取文件长度
			int map_data_length = 0;
			FILE* map_zip = fopen("Map.zip", "rb");
			if (map_zip)
			{
				fseek(map_zip, 0, SEEK_END);
				map_data_length = ftell(map_zip);
			}
			fclose(map_zip);

			int block_num = map_data_length / API_MAP_DATA_BLOCK_LEN;
			int last_block_length = map_data_length % API_MAP_DATA_BLOCK_LEN;

			//发送数据，先循环发送块，在发送最后一段

			for (int i = 0; i < block_num; i++)
			{
				protocol_head_t api_head;
				api_detu_vr_map_data_block api_detu;

				api_head.nCmd = CMD_DETU_GET_MAP_DATA_RES;
				api_head.nDataLen = api_detu.get_size();

				api_detu.length = map_data_length;
				api_detu.offset = API_MAP_DATA_BLOCK_LEN*(i + 1);

				//获取固定长度 API_MAP_DATA_BLOCK_LEN 大小的数据量
				unsigned char *map_data = (unsigned char *)malloc(API_MAP_DATA_BLOCK_LEN);
				memset(map_data, 0, API_MAP_DATA_BLOCK_LEN);

				FILE* map_zip = fopen("Map.zip", "rb");
				if (map_zip)
				{
					fseek(map_zip, api_detu.offset - API_MAP_DATA_BLOCK_LEN, SEEK_SET);
					int sts = fread(map_data, 1, API_MAP_DATA_BLOCK_LEN, map_zip);
					if (sts == 0)
					{
						Log::Debug("dem1service:: sts = fread(map_data, 1, map_data_length, pat_pts) failed");
						fclose(map_zip);
					}
					std::memcpy(api_detu.data, map_data, API_MAP_DATA_BLOCK_LEN);
				}
				fclose(map_zip);
				free(map_data);
				map_data = NULL;

				response res(api_head.get_size() + api_detu.get_size());
				response_add_resprotocol<protocol_head_t>(res, &api_head);
				response_add_resprotocol<api_detu_vr_map_data_block>(res, &api_detu);

				if (curr_conn_ != NULL)
				{
					curr_conn_->do_write(res);
				}
			}

			//发送最后一段
			if (last_block_length != 0)
			{
				protocol_head_t api_head;
				api_detu_vr_map_data_block api_detu;

				api_head.nCmd = CMD_DETU_GET_MAP_DATA_RES;
				api_head.nDataLen = api_detu.get_size();

				api_detu.length = map_data_length;
				api_detu.offset = map_data_length;

				//获取固定长度 API_MAP_DATA_BLOCK_LEN 大小的数据量
				unsigned char *map_data = (unsigned char *)malloc(API_MAP_DATA_BLOCK_LEN);
				memset(map_data, 0, API_MAP_DATA_BLOCK_LEN);

				FILE* pat_pts = fopen("Map.zip", "rb");
				if (pat_pts)
				{
					fseek(pat_pts, map_data_length - last_block_length, SEEK_SET);
					int sts = fread(map_data, 1, last_block_length, pat_pts);
					if (sts == 0)
					{
						Log::Debug("dem1service:: sts = fread(map_data, 1, map_data_length, pat_pts) failed");
						fclose(pat_pts);
					}
					std::memcpy(api_detu.data, map_data, last_block_length);
				}
				fclose(pat_pts);
				free(map_data);
				map_data = NULL;

				response res(api_head.get_size() + api_detu.get_size());
				response_add_resprotocol<protocol_head_t>(res, &api_head);
				response_add_resprotocol<api_detu_vr_map_data_block>(res, &api_detu);

				if (curr_conn_ != NULL)
				{
					Log::Debug("dem1service:: MapWgt::send_data_thread() :send last block!");
					curr_conn_->do_write(res);
				}
			}



			return 0;
		}

		int request_handler::handle_request_detu_register(netbuffer *buf)
		{
			std::vector<api_detu_client_register_res_t> nvrList;
			nvrList.clear();
			nvrList.resize(0);
			std::vector<api_detu_client_register_res_t>::iterator it;

			api_detu_client_register_t detu_reg;
			detu_reg.read(buf);
			//添加服务器保存客户端设备，当前只有一个
			std::string szDeviceId = (char*)detu_reg.szDetuDeviceUUId;
			Log::Info("dem1service:: recieve detu %s register", szDeviceId.c_str());
			if (!PanoManage.savePanoRegisterInfoToTable(detu_reg, curr_conn_->get_sessionid(), szDeviceId))
			{
				Log::Error("dem1service:: distributing the uuid is failed!");
				goto REGISTER_FAILED;
			}

			//当前设备是否存在未释放的链路
			if (!DetuClientlist.isDeviceIdExist(szDeviceId))
			{

				DetuClientlist.addSessionId(curr_conn_->get_sessionid(), szDeviceId);
			}
			else
			{
				DetuClientlist.replaceSessionId(curr_conn_->get_sessionid(), szDeviceId);
			}
// 			unsigned char 	szDetuDeviceId[API_ARRAY_LEN] = { "num0001" };
// 			std::string deviceId = (char*)szDetuDeviceId;
			SessionManage.updateSessionManageTable(curr_conn_->get_sessionid(), szDeviceId, 1);
			PVSManage.getPVSRegisterInfo(nvrList);

			int index = 1;
			if (nvrList.size() != 0)
			{
				it = nvrList.begin();
				while (it != nvrList.end())
				{
					api_detu_client_register_res_t api_res_t;
					memcpy(api_res_t.szDeviceId, it->szDeviceId, API_ARRAY_LEN);
					memcpy(api_res_t.szName, it->szName, API_ARRAY_LEN);
					memcpy(api_res_t.m1DeviceId, it->m1DeviceId, API_ARRAY_LEN);
					api_res_t.online = it->online;
					api_res_t.szUpDown = it->szUpDown;
					api_res_t.curr_num = index;
					api_res_t.total_num = nvrList.size();
					api_res_t.pts.nPtsLen = it->pts.nPtsLen;
					memcpy(api_res_t.pts.pts_data, it->pts.pts_data, API_PTS_LEN);

					protocol_head_t port_detu_head;
					response res(port_detu_head.get_size() + api_res_t.get_size());

					port_detu_head.nCmd = CMD_DETU_CLIENT_GET_LIST_RES;
					port_detu_head.nResult = RESULT_SUCCESS;
					port_detu_head.nDataLen = api_res_t.get_size();
					port_detu_head.nStreamId = 0;
					response_add_resprotocol<protocol_head_t>(res, &port_detu_head);
					response_add_resprotocol<api_detu_client_register_res_t>(res, &api_res_t);

					if (curr_conn_ != NULL){
						curr_conn_->do_write(res);
					}

					index++;
					it++;
				}

				//处理TCS转码服务列表
				std::vector<api_detu_tcs_register_t> detu_tcs;
				bool ret = TCSManage.getTCSDataListFromTable(detu_tcs);
				if (ret)
				{
					for (int i = 0; i < detu_tcs.size(); ++i)
					{
						protocol_head_t prot_detu_head;
						prot_detu_head.nCmd = CMD_DETU_CLIENT_GET_TCS_INFO;
						prot_detu_head.nResult = RESULT_SUCCESS;
						prot_detu_head.nDataLen = detu_tcs[i].get_size();
						prot_detu_head.nStreamId = 0;

						response res(prot_detu_head.get_size() + detu_tcs[i].get_size());
						response_add_resprotocol<protocol_head_t>(res, &prot_detu_head);
						response_add_resprotocol<api_detu_tcs_register_t>(res, &detu_tcs[i]);

						if (curr_conn_ != NULL){
							curr_conn_->do_write(res);
						}
					}
				}
			}
			else
			{
				goto REGISTER_FAILED;
			}
			return 0;
REGISTER_FAILED:
			protocol_head_t port_detu_head;
			response res(port_detu_head.get_size());

			port_detu_head.nCmd = CMD_DETU_CLIENT_GET_LIST_RES;
			port_detu_head.nResult = RESULT_FAILED;
			port_detu_head.nDataLen = 0;
			port_detu_head.nStreamId = 0;
			response_add_resprotocol<protocol_head_t>(res, &port_detu_head);

			if (curr_conn_ != NULL){
				curr_conn_->do_write(res);
			}
			return 0;
		}

		int request_handler::handle_request_playback_control(netbuffer *buf, unsigned char streamId)
		{


			api_detu_client_replay_control_t *api_query = new api_detu_client_replay_control_t;
			api_query->read(buf);

			protocol_head_t prot_head;
			api_playback_control_t prot_api;
			prot_head.nDataLen = prot_api.get_size();
			prot_head.nCmd = CMD_PLAYBACK_CONTROL;
			prot_head.nResult = RESULT_SUCCESS;
			prot_head.nStreamId = streamId;

			prot_api.nControlType = api_query->nControlType;
			prot_api.nSpeed = api_query->nSpeed;

			response res(prot_head.get_size() + prot_api.get_size());

			response_add_resprotocol<protocol_head_t>(res, &prot_head);
			response_add_resprotocol<api_playback_control_t>(res, &prot_api);



			std::string session_id = DetuNvrlist.getSessionIdByDeivceId((char*)api_query->szDeviceId);
			std::shared_ptr<connection> conn = curr_conn_->connection_manager_.get_connect(session_id);

			//添加到在线列表
			OnlineConnInfo_t conn_t;
			conn_t.client_session = curr_conn_->get_sessionid();
			conn_t.pvs_session = conn->get_sessionid();
			conn_t.cmd_id = (int)CMD_PLAYBACK_CONTROL_RES;
			OnlineConnListIns.AddOnlineConn(conn_t);

			if (conn != NULL){
				conn->do_write(res);
			}
			return 0;

		}

		int request_handler::handle_request_get_avparam(netbuffer *buf, unsigned char streamId)
		{
			api_detu_client_av_param_t *av_param = new api_detu_client_av_param_t;
			av_param->read(buf);
			protocol_head_t prot_head;
			prot_head.nDataLen = 0;
			prot_head.nCmd = CMD_GET_AVPARAM;
			prot_head.nResult = 0;
			prot_head.nStreamId = streamId;

			response res(prot_head.get_size());

			response_add_resprotocol<protocol_head_t>(res, &prot_head);

			std::string session_id = DetuNvrlist.getSessionIdByDeivceId((char*)av_param->szDeviceId);
			std::shared_ptr<connection> conn = curr_conn_->connection_manager_.get_connect(session_id);

			//添加到在线列表
			OnlineConnInfo_t conn_t;
			conn_t.client_session = curr_conn_->get_sessionid();
			conn_t.pvs_session = conn->get_sessionid();
			conn_t.cmd_id = (int)CMD_GET_AVPARAM_RES;
			OnlineConnListIns.AddOnlineConn(conn_t);

			if (conn != NULL){
				conn->do_write(res);
			}
			return 0;
		}

		int request_handler::handle_request_get_avparam_res(netbuffer *buf, unsigned char streamId)
		{
			//先找到对应设备
			OnlineConnInfo_t conn_t;
			std::vector<std::string> list_t;
			conn_t.cmd_id = CMD_GET_AVPARAM_RES;
			conn_t.pvs_session = curr_conn_->get_sessionid();
			list_t = OnlineConnListIns.GetList(conn_t);

			api_av_param_t *av_param = new api_av_param_t;
			av_param->read(buf);
			protocol_head_t prot_head;
			api_detu_client_av_param_t prot_api;
			prot_head.nDataLen = prot_api.get_size();
			prot_head.nCmd = CMD_DETU_CLIENT_GET_AVPARAM_RES;
			prot_head.nResult = RESULT_SUCCESS;
			prot_head.nStreamId = streamId;

			prot_api.nAudioEncoderType = av_param->nAudioEncoderType;
			prot_api.nBitRateType = av_param->nBitRateType;
			prot_api.nBitRate = av_param->nBitRate;
			prot_api.nFrameRate = av_param->nFrameRate;
			prot_api.nIFrameInterval = av_param->nIFrameInterval;
			prot_api.nIFrameIntervalUnit = av_param->nIFrameIntervalUnit;
			prot_api.nQuality = av_param->nQuality;
			prot_api.nVideoEncodeLevel = av_param->nVideoEncodeLevel;
			prot_api.nVideoEncoderType = av_param->nVideoEncoderType;
			prot_api.nVideoHeight = av_param->nVideoHeight;
			prot_api.nVideoWidth = av_param->nVideoWidth;

			response res(prot_head.get_size() + prot_api.get_size());
			response_add_resprotocol<protocol_head_t>(res, &prot_head);
			response_add_resprotocol<api_detu_client_av_param_t>(res, &prot_api);
			
			//找到对应设备发送
			for (std::vector<std::string>::iterator it = list_t.begin(); it != list_t.end(); ++it)
			{
				Log::Info("dem1service:: test send Data to client : %s", (*it).c_str());
				std::shared_ptr<connection> conn = curr_conn_->connection_manager_.get_connect(*it);
				if (conn != NULL){
					conn->do_write(res);
				}
			}

			return 0;
		}

		int request_handler::handle_request_set_avparam(netbuffer *buf, unsigned char streamId)
		{
			api_detu_client_av_param_t *av_param = new api_detu_client_av_param_t;
			av_param->read(buf);
			protocol_head_t prot_head;
			api_av_param api_av;
			prot_head.nDataLen = api_av.get_size();
			prot_head.nCmd = CMD_SET_AVPARAM;
			prot_head.nResult = 0;
			prot_head.nStreamId = streamId;

			api_av.nAudioEncoderType = av_param->nAudioEncoderType;
			api_av.nBitRate = av_param->nBitRate;
			api_av.nBitRateType = av_param->nBitRateType;
			api_av.nFrameRate = av_param->nFrameRate;
			api_av.nIFrameInterval = av_param->nIFrameInterval;
			api_av.nIFrameIntervalUnit = av_param->nIFrameIntervalUnit;
			api_av.nQuality = av_param->nQuality;
			api_av.nVideoEncodeLevel = av_param->nVideoEncodeLevel;
			api_av.nVideoEncoderType = av_param->nVideoEncoderType;
			api_av.nVideoHeight = av_param->nVideoHeight;
			api_av.nVideoWidth = av_param->nVideoWidth;

			response res(prot_head.get_size() + api_av.get_size());
			response_add_resprotocol<protocol_head_t>(res, &prot_head);
			response_add_resprotocol<api_av_param>(res, &api_av);

			std::string session_id = DetuNvrlist.getSessionIdByDeivceId((char*)av_param->szDeviceId);
			std::shared_ptr<connection> conn = curr_conn_->connection_manager_.get_connect(session_id);

			//添加到在线列表
			OnlineConnInfo_t conn_t;
			conn_t.client_session = curr_conn_->get_sessionid();
			conn_t.pvs_session = conn->get_sessionid();
			conn_t.cmd_id = (int)CMD_SET_AVPARAM_RES;
			OnlineConnListIns.AddOnlineConn(conn_t);

			if (conn != NULL){
				conn->do_write(res);
			}
			return 0;
		}

		int request_handler::handle_request_set_avparam_res(short result, unsigned char streamId)
		{
			//先找到对应设备
			OnlineConnInfo_t conn_t;
			std::vector<std::string> list_t;
			conn_t.cmd_id = CMD_SET_AVPARAM_RES;
			conn_t.pvs_session = curr_conn_->get_sessionid();
			list_t = OnlineConnListIns.GetList(conn_t);


			protocol_head_t prot_head;
			prot_head.nDataLen = 0;
			prot_head.nCmd = CMD_DETU_CLIENT_SET_AVPARAM_RES;
			prot_head.nResult = result;
			prot_head.nStreamId = streamId;

			response res(prot_head.get_size());
			response_add_resprotocol<protocol_head_t>(res, &prot_head);


			//找到对应设备发送
			for (std::vector<std::string>::iterator it = list_t.begin(); it != list_t.end(); ++it)
			{
				Log::Info("dem1service:: test send Data to client : %s", (*it).c_str());
				std::shared_ptr<connection> conn = curr_conn_->connection_manager_.get_connect(*it);
				if (conn != NULL){
					conn->do_write(res);
				}
			}
			return 0;
		}

		int request_handler::handle_request_disk_info(netbuffer *buf, unsigned char streamId)
		{

			
			api_detu_client_disk_size_list_t *disk_list = new api_detu_client_disk_size_list_t;
			disk_list->read(buf);

			protocol_head_t prot_head;
			prot_head.nDataLen = 0;
			prot_head.nCmd = CMD_GET_DISKINFO;
			prot_head.nResult = 0;
			prot_head.nStreamId = streamId;

			response res(prot_head.get_size());
			response_add_resprotocol<protocol_head_t>(res, &prot_head);

			//添加到在线列表
			OnlineConnInfo_t conn_t;
			conn_t.client_session = curr_conn_->get_sessionid();
			conn_t.pvs_session = "disk";
			conn_t.cmd_id = (int)CMD_GET_DISKINFO_RES;
			OnlineConnListIns.AddOnlineConn(conn_t);
			
			std::string session_id;
			std::shared_ptr<connection> conn;
			std::map < std::string, api_detu_client_register_res_t> nvr_list = DetuNvrlist.getNvrList();
			std::map < std::string, api_detu_client_register_res_t>::iterator it = nvr_list.begin();
			while (it != nvr_list.end())
			{
				conn = curr_conn_->connection_manager_.get_connect(it->first);
				if (conn != NULL){
					conn->do_write(res);

				}
				it++;
			}
			return 0;
		}

		int request_handler::handle_request_disk_format(netbuffer *buf, unsigned char streamId)
		{
			api_detu_client_disk_size_list_t disk_list ;
			disk_list.read(buf);

			protocol_head_t prot_head;
			prot_head.nDataLen = 0;
			prot_head.nCmd = CMD_DISK_FORMAT;
			prot_head.nResult = 0;
			prot_head.nStreamId = 0;

			std::string session_id;
			std::shared_ptr<connection> conn;
			for (int i = 0; i < disk_list.numlist; i++)
			{
				prot_head.nStreamId = disk_list.diskList[i].nDiskId;
				response res(prot_head.get_size());
				response_add_resprotocol<protocol_head_t>(res, &prot_head);
				session_id = DetuNvrlist.getSessionIdByDeivceId((char*)(disk_list.diskList[i].szDeviceId));
				conn = curr_conn_->connection_manager_.get_connect(session_id);

				//添加到在线列表
				OnlineConnInfo_t conn_t;
				conn_t.client_session = curr_conn_->get_sessionid();
				conn_t.pvs_session = conn->get_sessionid();
				conn_t.cmd_id = (int)CMD_DISK_FORMAT_RES;
				OnlineConnListIns.AddOnlineConn(conn_t);

				if (conn != NULL){
					conn->do_write(res);
				}

			}

			return 0;
		}

		int request_handler::handle_request_nvr_heart_beat(std::string session_id_, netbuffer *buf)
        {
            //处理心跳回复
			api_heartbeat_body_t *prot_body = new api_heartbeat_body_t;
			prot_body->read(buf);

			std::string pvsID = DetuNvrlist.getDeviceIdBySessionld(session_id_);
			PVSManageTable_t prot_table;
			memcpy(prot_table.pvsID, pvsID.c_str(), API_ARRAY_LEN);
			prot_table.nInputBandWidth = prot_body->nInputBandWidth;
			prot_table.nOuntputBandWidth = prot_body->nOuntputBandWidth;
			prot_table.nStream1Status = prot_body->nStream1Status;
			prot_table.nStream2Status = prot_body->nStream2Status;
			prot_table.nCalibrationStatus = prot_body->nCalibrationStatus;
			
			//校验主码流异常上报
			switch (prot_table.nStream1Status)
			{
			case 0:
				handle_request_active_report(session_id_, RESULT_OFFLINE_ERR, 0);
				break;
			case 1:
				handle_request_active_report(session_id_, RESULT_SYNC_ERR, 0);
				break;
			default:
				break;
			}

			//校验子码流异常上报
			switch (prot_table.nStream2Status)
			{
			case 0:
				handle_request_active_report(session_id_, RESULT_OFFLINE_ERR, 1);
				break;
			case 1:
				handle_request_active_report(session_id_, RESULT_SYNC_ERR, 1);
				break;
			default:
				break;
			}

			//校验标定信息是否成功
			if (prot_table.nCalibrationStatus != 0)
			{
				handle_request_active_report(session_id_, RESULT_CALIBRATIONERR, 0);
			}

			if (PVSManage.updatePVSManageTable(prot_table))
			{
		//		Log::Info("dem1service:: update PVMSManageTabel data success!");
			}

			//回复心跳
            protocol_head_t prot_head;
            prot_head.nDataLen = 0;
            prot_head.nCmd = CMD_HEART_BEAT_RES;
            prot_head.nResult = RESULT_SUCCESS;
			prot_head.nStreamId = 0;
            response res(prot_head.get_size());
            response_add_resprotocol<protocol_head_t>(res, &prot_head);
  
            if (curr_conn_ != NULL)
            {
                curr_conn_->do_write(res);
            }
            return 0;
        }

        int request_handler::handle_request_detu_client_heart_beat(std::string session_id_)
        {
		//	Log::Info("dem1service:: recieve detu client heart beat!");
            //处理心跳回复
            protocol_head_t prot_head;
            prot_head.nDataLen = 0;
            prot_head.nCmd = CMD_DETU_CLIENT_HEART_BEAT_RES;
            prot_head.nResult = RESULT_SUCCESS;
			prot_head.nStreamId = 0;

            response res(prot_head.get_size());
            response_add_resprotocol<protocol_head_t>(res, &prot_head);

			if (curr_conn_ != NULL)
			{
				curr_conn_->do_write(res);
			}

            return 0;
        }

		int request_handler::handle_request_detu_client_version_check(protocol_head_t *head)
		{
			protocol_head_t prot_head;
			prot_head.nDataLen = 0;
			prot_head.nCmd = CMD_DETU_CLIENT_VERSION_CHECK_RES;

			if (head->nResult == CLIENT_VERSION)
			{
				prot_head.nResult = 1;
			}
			else
			{
				prot_head.nResult = 0;

			}

			prot_head.nStreamId = 0;

			response res(prot_head.get_size());
			response_add_resprotocol<protocol_head_t>(res, &prot_head);

			if (curr_conn_ != NULL)
			{
				curr_conn_->do_write(res);
			}

			return 0;
		}

		int request_handler::handle_request(int n, netbuffer *buf, unsigned char streamId)
        {
			api_detu_client_record_query_t *record_query = new api_detu_client_record_query_t;
			record_query->read(buf);
            api_record_query_t api_query;
			api_query.nStartTime = record_query->nStartTime /*1498235757*/;
			api_query.nEndTime = record_query->nEndTime /*1498318457*/;

            protocol_head_t prot_head;
            prot_head.nDataLen = api_query.get_size();
            prot_head.nCmd = CMD_RECORD_QUERY;
            prot_head.nResult = RESULT_SUCCESS;
			prot_head.nStreamId = streamId;
    
            response res(prot_head.get_size() + api_query.get_size());

            response_add_resprotocol<protocol_head_t>(res, &prot_head);
            response_add_resprotocol<api_record_query_t>(res, &api_query);

         


			std::string session_id = DetuNvrlist.getSessionIdByDeivceId((char*)record_query->szDeviceId);
            std::shared_ptr<connection> conn = curr_conn_->connection_manager_.get_connect(session_id);

			//添加到在线列表
			OnlineConnInfo_t conn_t;
			conn_t.client_session = curr_conn_->get_sessionid();
			conn_t.pvs_session = conn->get_sessionid();
			conn_t.cmd_id = (int)CMD_RECORD_QUERY_RES;
			OnlineConnListIns.AddOnlineConn(conn_t);

            if (conn != NULL){
                conn->do_write(res);
            }
            return 0;
        }

        int request_handler::handle_request(api_record_query_respond_t *req)
        {
            return 0;
        }

        int request_handler::handle_request(netbuffer *buf, int n, unsigned char streamId)
        {


			//请求回放标定
			protocol_head_t prot_head_cali;
			api_record_query_t record;
			response res_cali(prot_head_cali.get_size() + record.get_size());

			prot_head_cali.nCmd = CMD_GET_RECORD_CALIBRATION;
			prot_head_cali.nResult = RESULT_SUCCESS;
			prot_head_cali.nDataLen = record.get_size();
			prot_head_cali.nStreamId = 0;

			record.nStartTime = 0;
			record.nEndTime = 0;

			response_add_resprotocol<protocol_head_t>(res_cali, &prot_head_cali);
			response_add_resprotocol<api_record_query_t>(res_cali, &record);

			if (curr_conn_ != NULL)
			{
				curr_conn_->do_write(res_cali);
			}

			//通知客户端查询结果
			//先找到对应设备
			OnlineConnInfo_t conn_t;
			std::vector<std::string> list_t;
			conn_t.cmd_id = CMD_RECORD_QUERY_RES;
			conn_t.pvs_session = curr_conn_->get_sessionid();
			list_t = OnlineConnListIns.GetList(conn_t);

            protocol_head_t prot_head;
			prot_head.nDataLen = buf->buffer_len;
			prot_head.nCmd = CMD_DETU_CLIENT_RECORD_QUERY_RES;
			prot_head.nResult = RESULT_SUCCESS;
			prot_head.nStreamId = streamId;

			response res(prot_head.get_size() + prot_head.nDataLen);
			response_add_resprotocol<protocol_head_t>(res, &prot_head);

			std::memcpy(res.netbuf_.buffer + res.netbuf_.buffer_offset, buf->buffer, buf->buffer_len);
			res.netbuf_.buffer_offset = res.netbuf_.buffer_offset + buf->buffer_len;

			//找到对应设备发送
			for (std::vector<std::string>::iterator it = list_t.begin(); it != list_t.end(); ++it)
			{
				Log::Info("dem1service:: test send Data to client : %s", (*it).c_str());
				std::shared_ptr<connection> conn = curr_conn_->connection_manager_.get_connect(*it);
				if (conn != NULL){
					conn->do_write(res);
				}
			}
            return 0;
        }

		int request_handler::handle_request_replay_calibration_res(protocol_head_t *head, netbuffer *buf)
		{
			DetuNvrlist.addNvrPts(head, buf);
			return 0;
		}



		int request_handler::handle_request_nvr_request_video_res(short nResult, unsigned char deviceType)
        {
            protocol_head_t prot_head;
            api_detu_client_request_video_res api_res;
            response res(prot_head.get_size() + sizeof(api_res));

			//把nvr推流的转发地址发送给客户端
			std::string rtmp_path = DetuNvrlist.getRtmpPathByDeivceId(curr_conn_->get_sessionid());
			memcpy(api_res.szRtmpURL, rtmp_path.c_str(), API_RTMP_LEN);

			std::string PVSID = DetuNvrlist.getDeviceIdBySessionld(curr_conn_->get_sessionid());
			memcpy(api_res.szDeviceId, PVSID.c_str(), API_ARRAY_LEN);

			int num = 0;
			bool ret = PVSManage.getPushFlowNum(PVSID, num);
			if (ret)
			{
				num++;
				PVSManage.updatePushFlowNum(PVSID, num);
			}

			//处理视频请求回复
			prot_head.nDataLen = sizeof(api_detu_client_request_video_res);
			prot_head.nCmd = CMD_DETU_CLIENT_REQUEST_VIDEO_RES;
			prot_head.nStreamId = 0;
			if (nResult==0)
            {
                prot_head.nResult = RESULT_SUCCESS;
            }
            else
            {                
				prot_head.nResult = RESULT_FAILED;
            }
			response_add_resprotocol<protocol_head_t>(res, &prot_head);
			response_add_resprotocol<api_detu_client_request_video_res>(res, &api_res);

			std::vector<std::string> session_vector;
			std::vector<std::string> list_t;
			OnlineConnInfo_t conn_t;
			switch (deviceType)
			{
			case SERVER_TYPE_CLINET:
				conn_t.cmd_id = CMD_REQUEST_VIDEO_RES;
				conn_t.pvs_session = curr_conn_->get_sessionid();
				list_t = OnlineConnListIns.GetList(conn_t);
				for (std::vector<std::string>::iterator it = list_t.begin(); it != list_t.end(); ++it)
				{
					Log::Info("dem1service:: test send Data to client : %s", (*it).c_str());
					std::shared_ptr<connection> conn = curr_conn_->connection_manager_.get_connect(*it);
					if (conn != NULL){
						conn->do_write(res);
					}
				}
				break;
			case SERVER_TYPE_TCS:
				if (SessionManage.getSessionIdByRequested(session_vector, PVSID, deviceType))
				{
					for (int i = 0; i < session_vector.size(); ++i)
					{
						Log::Info("dem1service:: test send Data to TCS : %s", session_vector[i].c_str());
						std::shared_ptr<connection> conn = curr_conn_->connection_manager_.get_connect(session_vector[i]);
						if (conn != NULL){
							conn->do_write(res);
						}
						SessionManage.updatePushFlowDevice("NULL", session_vector[i], deviceType);
					}
				}
				break;
			default:
				break;
			}
            return 0;
        }

		int request_handler::handle_request_detu_client_close_video(netbuffer *buf, unsigned char streamId, short result, std::string sessionID)
        {		
			api_detu_client_close_video_t api_info;
			api_info.read(buf);
			std::string pvsId = (char*)api_info.szDeviceId;
			std::string deviceID = "";
			TCSManage.getPushFlowDevice(deviceID, sessionID);
			if (deviceID != "")
			{
				//上报转码异常
				if (result == RESULT_FAILED || result == RESUKT_PULL_RTMP_ERROR || result == RESULT_PUSH_RTMP_ERROR)
				{
					protocol_head_t prot_head;
					api_detu_tcs_transcode_res_t api_detu;
					memcpy(api_detu.szDeviceId, deviceID.c_str(), API_ARRAY_LEN);

					//组装消息头
					prot_head.nDataLen = api_detu.get_size();
					prot_head.nCmd = CMD_DETU_CLIENT_TCS_REPORT_ERROR;
					prot_head.nResult = result;
					prot_head.nStreamId = streamId;


					response res(prot_head.get_size() + api_detu.get_size());
					response_add_resprotocol<protocol_head_t>(res, &prot_head);
					response_add_resprotocol<api_detu_tcs_transcode_res_t>(res, &api_detu);

					std::vector<std::string> sessionList;
					bool ret = SessionManage.getSessionIdByTypeFromTable(sessionList, 1);
					if (ret)
					{
						for (int i = 0; i < sessionList.size(); ++i)
						{
							std::shared_ptr<connection> conn = curr_conn_->connection_manager_.get_connect(sessionList[i]);
							if (conn != NULL){
								conn->do_write(res);
							}
						}
					}
				}
			}
			else
			{
				deviceID = pvsId;
			}

			//校验有一路以上在推流，不请求关闭流
			int pushFlowNum = 0;
			bool ret = PVSManage.getPushFlowNum(deviceID, pushFlowNum);
			if (ret)
			{
				if (pushFlowNum >1)
				{
					Log::Info("dem1service:: has been in the stream, do not close stream!");
					pushFlowNum--;
					PVSManage.updatePushFlowNum(deviceID, pushFlowNum);
					return -1;
				}
				else if (pushFlowNum == 1)
				{
					protocol_head_t prot_head;
					//组装消息头
					prot_head.nDataLen = 0;
					prot_head.nCmd = CMD_CLOSE_VIDEO;
					prot_head.nResult = RESULT_SUCCESS;
					prot_head.nStreamId = streamId;
					response res(prot_head.get_size());
					response_add_resprotocol<protocol_head_t>(res, &prot_head);

					std::string session_id = DetuNvrlist.getSessionIdByDeivceId(pvsId);
					std::shared_ptr<connection> conn = curr_conn_->connection_manager_.get_connect(session_id);
					if (conn != NULL){
						conn->do_write(res);
					}
				}
			}
            return 0;
        }

		int request_handler::handle_request_detu_client_login_checked(netbuffer *buf)
		{
			api_detu_client_register_t api_info;
			api_info.read(buf);

			int ret = PanoManage.getLoginInfo(api_info);
			if (ret != READ_DATABASE_ERR)
			{
				protocol_head_t prot_head;
				prot_head.nDataLen = api_info.get_size();
				prot_head.nCmd = CMD_DETU_CLIENT_LOGIN_CHECKED_RES;
				prot_head.nResult = ret;

				response res(prot_head.get_size() + api_info.get_size());
				response_add_resprotocol<protocol_head_t>(res, &prot_head);
				response_add_resprotocol<api_detu_client_register_t>(res, &api_info);

				if (curr_conn_ != NULL)
				{
					curr_conn_->do_write(res);
				}
			}
			return 0;
		}

		int request_handler::handle_request_detu_client_register_user(netbuffer *buf)
		{
			api_detu_client_register_t api_query;
			api_query.read(buf);

			std::string cUuid = boost::uuids::to_string(boost::uuids::random_generator()());
			int ret = PanoManage.registerUser(api_query, curr_conn_->get_sessionid(), cUuid);
			if (ret != READ_DATABASE_ERR)
			{
				protocol_head_t api_head;
				api_detu_client_register_t api_query_t;
				api_head.nCmd = CMD_DETU_CLIENT_REGISTER_USER_RES;
				api_head.nResult = ret;
				api_head.nDataLen = api_query_t.get_size();
				api_head.nStreamId = 0;

				memcpy(api_query_t.szDetuDeviceUUId, cUuid.c_str(), API_RTMP_LEN);
				memcpy(api_query_t.szDetuUserName, api_query.szDetuUserName, API_ARRAY_LEN);
				memcpy(api_query_t.szDetuPassWord, api_query.szDetuPassWord, API_ARRAY_LEN);

				response res(api_head.get_size() + api_query_t.get_size());
				response_add_resprotocol<protocol_head_t>(res, &api_head);
				response_add_resprotocol<api_detu_client_register_t>(res, &api_query_t);
				if (curr_conn_ != NULL)
				{
					curr_conn_->do_write(res);
				}
			}
			return 0;
		}

		bool request_handler::handle_reg_to_sql(api_register_t *req)
        {
            return true;
        }

    }  // namespace server
} // namespace dem1
