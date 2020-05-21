#pragma once
#include "netbuffer.h"
#include "APIProtocol.h"
#include "request_handler.hpp"

#define API_HANDLER(name) api=malloc(sizeof(name)); \
((name *)api)->read(buf); \
handler->handle_request((name *)api); \
free(api);

using namespace dm::server;

static void APIProtocal_Handler(protocol_head_t head, netbuffer *buf, request_handler *handler){

    void* api = NULL;
    
	switch (head.nCmd)
	{
	case CMD_DETU_CLIENT_REQUEST_VIDEO_RES:
	{
		Log::Info("APIProtocal_Handler : CMD_DETU_CLIENT_REQUEST_VIDEO_RES");
												   if (head.nResult == RESULT_SUCCESS)
												   {
													   handler->handle_request(buf, true);
												   }
												   else
													   handler->handle_request(buf, false);
												   break;
	}
	case CMD_DETU_CLIENT_GET_LIST_RES:
	{
		Log::Info("APIProtocal_Handler : CMD_DETU_CLIENT_REGISTER_RES");
		API_HANDLER(api_detu_client_register_res_t);
		break;
	}
	case CMD_DETU_CLIENT_RECORD_QUERY_RES:
    {
		Log::Info("APIProtocal_Handler : CMD_DETU_CLIENT_RECORD_QUERY_RES");
        int n = buf->buffer_len / sizeof(api_record_query_respond_t);
        handler->handle_request(buf, n);
        break;
    }
	case CMD_DETU_CLIENT_HEART_BEAT_RES:
	{
		Log::Info("APIProtocal_Handler : CMD_DETU_CLIENT_HEART_BEAT_RES");
		handler->handle_request();
		break;
	}
	case CMD_DETU_CLIENT_VERSION_CHECK_RES:
	{
		Log::Info("APIProtocal_Handler : CMD_DETU_CLIENT_VERSION_CHECK_RES");
		handler->handle_version_check(head);
		break;
	}
	case CMD_DETU_CLIENT_PLAYBACK_CONTROL_RES:
	{
		Log::Info("APIProtocal_Handler : CMD_DETU_CLIENT_PLAYBACK_CONTROL_RES");
		if (head.nResult == RESULT_SUCCESS)
		{
			handler->handle_request_replay_control(true, head.nStreamId);
		}
		else
		{
			handler->handle_request_replay_control(false, head.nStreamId);
		}
		break;
	}
	case CMD_DETU_CLIENT_GET_AVPARAM_RES:
	{
		Log::Info("APIProtocal_Handler : CMD_DETU_CLIENT_GET_AVPARAM_RES");
		handler->handle_request(buf, head.nStreamId);
		break;
	}
	case CMD_DETU_CLIENT_SET_AVPARAM_RES:
	{
		Log::Info("APIProtocal_Handler : CMD_DETU_CLIENT_SET_AVPARAM_RES");
		if (head.nResult == RESULT_SUCCESS)
		{
			handler->handle_request(head.nStreamId, true);
		}
		else
			handler->handle_request(head.nStreamId, false);
		break;
	}
	case CMD_DETU_CLIENT_DISKINFO_RES:
	{
		Log::Info("APIProtocal_Handler : CMD_DETU_CLIENT_DISKINFO_RES");
		handler->handle_request_disk_size(buf, buf->buffer_len / sizeof(api_detu_client_disk_size_t));
		break;
	}
	case CMD_DETU_CLIENT_DISK_FORMAT_RES:
	{		
		Log::Info("APIProtocal_Handler : CMD_DETU_CLIENT_DISK_FORMAT_RES");
		if (head.nResult == RESULT_SUCCESS)
		{
			handler->handle_request(true);
		}
		else
			handler->handle_request(false);
		break;
	}
	case CMD_DETU_PTZ_REGISTER_RES:
	{	
		Log::Info("APIProtocal_Handler : CMD_DETU_PTZ_REGISTER_RES");
		if (head.nResult == RESULT_SUCCESS)
		{
			handler->handle_request_ptz_register_res(true, head.nStreamId);
		}
		else
		{
			handler->handle_request_ptz_register_res(false, head.nStreamId);
		}
		break;
	}
	case CMD_DETU_SPY_REGISTER_RES:
		Log::Info("APIProtocal_Handler : CMD_DETU_SPY_REGISTER_RES");
		if (head.nResult == RESULT_SUCCESS)
		{
			handler->handle_request_spy_register_res(true, head.nStreamId);
		}
		else
		{
			handler->handle_request_spy_register_res(false, head.nStreamId);
		}
		break;
	case CMD_DETU_CLIENT_STREAM_HANDLE_RES:
		Log::Info("APIProtocal_Handler : CMD_DETU_CLIENT_STREAM_HANDLE_RES");
		handler->handle_request_handle_stream_res(head.nResult, head.nStreamId);
		break;
	case CMD_DETU_CLIENT_DEVICE_REBOOT_RES:
		Log::Info("APIProtocal_Handler : CMD_DETU_CLIENT_DEVICE_REBOOT_RES");
		handler->handle_request_reboot_device_res(head.nResult, head.nStreamId);
		break;
	case CMD_DETU_CLIENT_REPORT_OPTIMIZE_PTS_RES:
		Log::Info("reportting pts data to server is is successful !");
		break;
	case CMD_DETU_CLIENT_ACTIVE_REPORT:
		Log::Info("APIProtocal_Handler : CMD_DETU_CLIENT_ACTIVE_REPORT");
		handler->handle_request_active_report(buf, head.nStreamId);
		break;
	case CMD_DETU_CLIENT_GET_BANDWIDTH_RES:
		Log::Info("APIProtocal_Handler : CMD_DETU_CLIENT_GET_BANDWIDTH_RES");
		handler->handle_request_get_bandWidth(buf);
		break;
	case CMD_DETU_CLIENT_GET_PTZ_LIST_RES:
		Log::Info("APIProtocal_Handler : CMD_DETU_CLIENT_GET_PTZ_LIST_RES");
		handler->handle_request_get_ptz_list(buf);
		break;
	case CMD_DETU_CLIENT_GET_SPY_LIST_RES:
		Log::Info("APIProtocal_Handler : CMD_DETU_CLIENT_GET_SPY_LIST_RES");
		handler->handle_request_get_spy_list(buf);
		break;
	case CMD_DETU_DELETE_PTZ_RES:
		Log::Info("APIProtocal_Handler : CMD_DETU_DELETE_PTZ_RES");
		handler->handle_request_delete_ptz(head.nResult);
		break;
	case CMD_DETU_DELETE_SPY_RES:
		Log::Info("APIProtocal_Handler : CMD_DETU_DELETE_SPY_RES");
		handler->handle_request_delete_spy(head.nResult);
		break;
	case CMD_DETU_SAVE_PTZ_POINT_RES:
		Log::Info("APIProtocal_Handler : CMD_DETU_SAVE_PTZ_POINT_RES %d", head.nResult);
		break;
	case CMD_DETU_GET_PTZ_POINT_RES:
		Log::Info("APIProtocal_Handler : CMD_DETU_SAVE_PTZ_POINT_RES %d", head.nResult);
		handler->handle_request_get_ptz_point(buf);
		break;
	case CMD_DETU_CLIENT_GET_TCS_INFO:
		Log::Info("APIProtocal_Handler : CMD_DETU_CLIENT_GET_TCS_INFO");
		handler->handle_request_get_tcs_info(buf);
		break;
	case CMD_DETU_CLIENT_UPDATE_TCSINFO:
		Log::Info("APIProtocal_Handler : CMD_DETU_CLIENT_UPDATE_TCSINFO");
		handler->handle_request_update_tcs_info(buf);
		break;
	case CMD_DETU_CLIENT_TCS_REPORT_ERROR:
		Log::Info("APIProtocal_Handler : CMD_DETU_CLIENT_TCS_REPORT_ERROR");
		handler->handle_request_report_tcs_error(buf, head.nResult);
		break;
	case CMD_DETU_CLINET_TCS_OFFLINE:
		Log::Info("APIProtocal_Handler : CMD_DETU_CLINET_TCS_OFFLINE");
		handler->handle_request_tcs_offline(buf);
		break;
	case CMD_DETU_CLIENT_TCS_RESET_RES:
		Log::Info("APIProtocal_Handler : CMD_DETU_CLIENT_TCS_RESET_RES");
		handler->handle_request_tcs_reset(head.nResult);
		break;
	case CMD_DETU_SEND_MAP_DATA_RES:
		Log::Info("APIProtocal_Handler : CMD_DETU_SEND_MAP_DATA_RES");
		handler->handle_request_send_map_data_res(buf);
		break;
	case CMD_DETU_GET_MAP_DATA_RES:
		Log::Info("APIProtocal_Handler : CMD_DETU_GET_MAP_DATA_RES");
		handler->handle_request_get_map_data_res(buf);
		break;
	case CMD_DETU_CLIENT_LOGIN_CHECKED_RES:
		Log::Info("APIProtocal_Handler : CMD_DETU_CLIENT_LOGIN_CHECKED_RES");
		handler->handle_request_login_checked_res(buf, head.nResult);
		break;
	case CMD_DETU_CLIENT_REGISTER_USER_RES:
		Log::Info("APIProtocal_Handler : CMD_DETU_CLIENT_REGISTER_USER_RES");
		handler->handle_request_register_user_res(buf, head.nResult);
		break;
	default:
		break;
	}
}
