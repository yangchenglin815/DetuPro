#pragma once

#include "netbuffer.h"
#include "APIProtocol.h"
#include "request_handler.hpp"

// #define API_HANDLER(name) api=malloc(sizeof(name)); \
// 	((name *)api)->read(buf); \
// 	handler->handle_request((name *)api); \
// 	free(api);

using namespace dem1::server;

static void APIProtocal_Handler(protocol_head_t *head, netbuffer *buf, request_handler *handler, std::string session_id_){

 	void* api = NULL;
 
    switch (head->nCmd) 
    {
 	    case CMD_REGISTER:
        {
			Log::Info("dem1service:: APIProtocal_Handler : CMD_REGISTER");
			handler->handle_request_nvr_register(head, buf);
            break;
        }
		case CMD_GET_CALIBRATION_RES:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_GET_CALIBRATION_RES");
			handler->handle_request_calibration_res(head, buf);
			break;
		}
		case CMD_GET_RECORD_CALIBRATION_RES:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_GET_RECORD_CALIBRATION_RES");
			handler->handle_request_replay_calibration_res(head, buf);
			break;
		}
        case CMD_HEART_BEAT:
		{			
			Log::Info("dem1service:: APIProtocal_Handler : CMD_HEART_BEAT");
			handler->handle_request_nvr_heart_beat(session_id_, buf);
            break;
        }
        case CMD_DETU_CLIENT_HEART_BEAT:
        {
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_CLIENT_HEART_BEAT");
			handler->handle_request_detu_client_heart_beat(session_id_);
            break;
        }
		case CMD_DETU_CLIENT_VERSION_CHECK:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_CLIENT_VERSION_CHECK");
			handler->handle_request_detu_client_version_check(head);
			break;
		}
			
		case CMD_REQUEST_VIDEO_RES:
        {
			Log::Info("dem1service:: APIProtocal_Handler : CMD_REQUEST_VIDEO_RES");
			handler->handle_request_nvr_request_video_res(head->nResult, head->deviceNum);
            break;
        }
        case CMD_RECORD_QUERY_RES:
        {
			Log::Info("dem1service:: APIProtocal_Handler : CMD_RECORD_QUERY_RES");
            int n = buf->buffer_len / sizeof(api_record_query_respond_t);
            handler->handle_request(buf, n, head->nStreamId);
            break;
        }
        case CMD_DETU_CLIENT_GET_LIST:
        {						 
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_CLIENT_REGISTER");
			handler->handle_request_detu_register(buf);
            break;
        }

        case CMD_DETU_CLIENT_RECORD_QUERY:
        {
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_CLIENT_RECORD_QUERY");
            handler->handle_request(1, buf, head->nStreamId);
            break;
        }

        case CMD_DETU_CLIENT_REQUEST_VIDEO:
        {
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_CLIENT_REQUEST_VIDEO");
            handler->handle_request_detu_client_request_video(buf, head->nStreamId, head->deviceNum);
            break;
        }
        case CMD_DETU_CLIENT_CLOSE_VIDEO:
        {           
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_CLIENT_CLOSE_VIDEO");
			handler->handle_request_detu_client_close_video(buf, head->nStreamId, head->nResult, session_id_);
            break;
        }
		case CMD_DETU_CLIENT_PLAYBACK_CONTROL:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_CLIENT_PLAYBACK_CONTROL");
			 handler->handle_request_playback_control(buf, head->nStreamId);
			break;
		}
		case CMD_PLAYBACK_CONTROL_RES:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_PLAYBACK_CONTROL_RES");
			handler->handle_request(head->nResult, head->nStreamId);
			break;
		}
		case CMD_DETU_CLIENT_GET_AVPARAM:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_CLIENT_GET_AVPARAM");
			handler->handle_request_get_avparam(buf, head->nStreamId);
			break;
		}
		case CMD_GET_AVPARAM_RES:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_GET_AVPARAM_RES");
			handler->handle_request_get_avparam_res(buf, head->nStreamId);
			break;
		}
		case CMD_DETU_CLIENT_SET_AVPARAM:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_CLIENT_SET_AVPARAM");
			handler->handle_request_set_avparam(buf, head->nStreamId);
			break;
		}
		case CMD_SET_AVPARAM_RES:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_SET_AVPARAM_RES");
			handler->handle_request_set_avparam_res(head->nResult, head->nStreamId);
			break;
		}
		case  CMD_DETU_CLIENT_DISKINFO:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_CLIENT_DISKINFO");
		    handler->handle_request_disk_info(buf, head->nStreamId);
			break;
		}
		case CMD_GET_DISKINFO_RES:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_GET_DISKINFO_RES");
			int n = buf->buffer_len / sizeof(api_disk_info_t);
			handler->handle_request(session_id_, n, buf, head->nStreamId);
			break;
		}
		case CMD_DETU_CLIENT_DISK_FORMAT:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_CLIENT_DISK_FORMAT");
			handler->handle_request_disk_format(buf, head->nStreamId);
			break;
		}
		case CMD_DISK_FORMAT_RES:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DISK_FORMAT_RES");
			handler->handle_request(session_id_, head->nResult, head->nStreamId);
			break;
		}
		case CMD_DETU_REPORT_NAME:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_REPORT_NAME");
			handler->handle_request_report_name(buf, session_id_);
			break;
		}
		case CMD_CLOSE_VIDEO_RES:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_CLOSE_VIDEO_RES");
			handler->handle_request_close_video(head->nResult);
			break;
		}
		case CMD_DETU_PTZ_REGISTER:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_PTZ_REGISTER");
			handler->handle_request_ptz_register(buf, head->nStreamId);
			break;
		}		
		case CMD_DETU_SPY_REGISTER:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_SPY_REGISTER");
			handler->handle_request_spy_register(buf, head->nStreamId);
			break;
		}
		case CMD_DETU_CLIENT_GET_STREAM:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_CLIENT_GET_STREAM");
			handler->handle_request_get_stream(buf);
			break;
		}
		case CMD_DETU_CLIENT_ADD_STREAM:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_CLIENT_ADD_STREAM");
			handler->handle_request_add_stream(buf, head->nStreamId);
			break;
		}
		case CMD_DETU_CLIENT_DEL_STREAM:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_CLIENT_DEL_STREAM");
			handler->handle_request_del_stream(buf, head->nStreamId);
			break;
		}
		case CMD_STREAM_HANDLE_RES:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_STREAM_HANDLE_RES");
			handler->handle_request_handle_stream_res(head->nResult, head->nStreamId);
			break;
		}
		case CMD_DETU_CLIENT_DEVICE_REBOOT:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_CLIENT_DEVICE_REBOOT");
			handler->handle_request_reboot_device(buf, head->nStreamId);
			break;
		}
		case CMD_DEVICE_RESTART_RES:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DEVICE_RESTART_RES");
			handler->handle_request_reboot_device_res(head->nResult, head->nStreamId);
			break;
		}
		case CMD_DETU_APP_REGISTER:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_APP_REGISTER");
			handler->handle_request_app_register(buf);
			break;
		}
		case CMD_DETU_CLIENT_REPORT_OPTIMIZE_PTS:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_CLIENT_REPORT_OPTIMIZE_PTS");
			handler->handle_request_report_pts_data(buf, session_id_);
			break;
		}
		case CMD_ACTIVE_REPORT:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_ACTIVE_REPORT");
			handler->handle_request_active_report(session_id_, head->nResult, 0);
			break;
		}
		case CMD_DETU_CLIENT_GET_BANDWIDTH:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_CLIENT_GET_BANDWIDTH");
			handler->handle_request_get_bandWidth(buf);
			break;
		}
		case CMD_DETU_CLIENT_GET_PTZ_LIST:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_CLIENT_GET_PTZ_LIST");
			handler->handle_request_get_ptz_list();
			break;
		}
		case CMD_DETU_CLIENT_GET_SPY_LIST:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_CLIENT_GET_SPY_LIST");
		    handler->handle_request_get_spy_list();
			break;
		}
		case CMD_DETU_DELETE_PTZ:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_DELETE_PTZ"); 
			handler->handle_request_delete_ptz(buf);
			break;
		}
		case CMD_DETU_DELETE_SPY:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_DELETE_SPY"); 
			handler->handle_request_delete_spy(buf);
			break;
		}
		case CMD_DETU_SAVE_PTZ_POINT:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_SAVE_PTZ_POINT");
			handler->handle_request_save_ptz_point(buf);
			break;
		}
		case CMD_DETU_GET_PTZ_POINT:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_GET_PTZ_POINT");
			handler->handle_request_get_ptz_point(buf);
			break;
		}
		case CMD_DETU_TCS_REGISTER:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_TCS_REGISTER");
			handler->handle_request_tcs_register(buf);
			break;
		}
		case CMD_DETU_TCS_HEARTBEAT:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_TCS_HEARTBEAT");
			handler->handle_request_tcs_heartbeat(buf);
			break;
		}
		case CMD_DETU_CLIENT_TCS_RESET:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_CLIENT_TCS_RESET");
			handler->handle_request_tcs_reset();
			break;
		}
		case CMD_SET_M1_TIME_RES:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_SET_M1_TIME_RES");
			handler->handle_request_set_m1_time(buf);
			break;
		}
		case CMD_GET_M1_TIME_RES:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_GET_M1_TIME_RES");
			handler->handle_request_get_m1_time(buf);
			break;
		}
		case CMD_SET_RECORD_POLICY_RES:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_SET_RECORD_POLICY_RES");
			handler->handle_request_set_record(buf);
			break;
		}
		case CMD_GET_RECORD_POLICY_RES:
			Log::Info("dem1service:: APIProtocal_Handler : CMD_GET_RECORD_POLICY_RES");
			handler->handle_request_get_record(buf);
			break;
		case CMD_DETU_SEND_MAP_DATA:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_SEND_MAP_DATA");
			handler->handle_request_set_map_data(buf);
			break;
		}
		case CMD_DETU_GET_MAP_DATA:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_GET_MAP_DATA");
			handler->handle_request_get_map_data(buf);
			break;
		}
		case  CMD_DETU_CLIENT_LOGIN_CHECKED:
	    {
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_CLIENT_LOGIN_CHECKED");
			handler->handle_request_detu_client_login_checked(buf);
			break;
		}
		case CMD_DETU_CLIENT_REGISTER_USER:
		{
			Log::Info("dem1service:: APIProtocal_Handler : CMD_DETU_CLIENT_REGISTER_USER");
			handler->handle_request_detu_client_register_user(buf);
			break;
		}
 	    default:
        {
            Log::Info("dem1service:: APIProtocal_Handler : invalid message id = %d \n", head->nCmd);
            break;
        }
    }
}