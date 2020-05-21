#include "request_handler.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "dmconnection.hpp"
#include "TcpDataManager.hpp"

#include "quazip/JlCompress.h"

namespace dm 
{
	namespace server 
	{
		request_handler::request_handler()
		{           
        }
        
        int request_handler::start(dmconnection* dm_conn)
		{            
            this->curr_conn_ = dm_conn;
            return 0;
        }
        
        
        void request_handler::stop(){
            
        }      

		int request_handler::handle_request(api_detu_client_register_res_t *req)
		{
			Log::Info("detu update nvr list OK");
			TcpDataManagerIns.SetList(req);
			return 0;
		}

		int request_handler::handle_request(netbuffer *buf, bool is_video_ok)
		{
			api_detu_client_request_video_res_t *detu_recoed_url = new api_detu_client_request_video_res_t;
			detu_recoed_url->read(buf);
			if (is_video_ok)
			{
				Log::Info("detu client request video res  OK");
				TcpDataManagerIns.SetRequestVideoSucceed(detu_recoed_url);
			}
			else
			{
				Log::Info("detu client request video res  FAILD");
				TcpDataManagerIns.SetRequestVideoFailed();
			}
			return 0;
		}

        int request_handler::handle_request(netbuffer *buf, int n)
        {
			std::vector<api_record_query_respond> qurey_list;
			qurey_list.resize(n);

            for (int i = 0; i < n;i++)
            {
				api_record_query_respond api_query;

                //一段一段读取，并且要大小端转换本地
                netbuffer* temp = new netbuffer();
				temp->buffer = (char*)malloc(sizeof(api_record_query_respond));
				temp->buffer_len = sizeof(api_record_query_respond);
                memcpy(temp->buffer, (buf->buffer + sizeof(api_record_query_respond)*i), sizeof(api_record_query_respond));
                api_query.read(temp);

				qurey_list[i] = api_query;
      
                free(temp);
      
            }
			Log::Info("detu client qurey res  OK");
            TcpDataManagerIns.SetRecordTime(qurey_list);
            return 0;
        }

		int request_handler::handle_request()
		{
			Log::Info("detu client heart beat res  OK");
			TcpDataManagerIns.breakHeart();
			return 0;
		}

		int request_handler::handle_request(netbuffer *buf, unsigned char streamId)
		{
			api_detu_client_av_param_t *detu_bitRate_url = new api_detu_client_av_param_t;
			detu_bitRate_url->read(buf);
			TcpDataManagerIns.getBitRate(detu_bitRate_url, streamId);
			return 0;
		}

		int request_handler::handle_request(unsigned char streamId, bool is_video_ok)
		{
			if (is_video_ok)
			{
				Log::Info("detu client set bitRate res  OK");
			}
			else
			{
				Log::Info("detu client set bitRate res  FAILD");
			}
			TcpDataManagerIns.setBitRate(streamId, is_video_ok);
			return 0;
		}

		int request_handler::handle_request(bool is_ok)
		{
			TcpDataManagerIns.setDiskFormat(is_ok);
			return 0;
		}

		int request_handler::handle_version_check(protocol_head_t head)
		{
			Log::Info("detu client version check res  OK");
			TcpDataManagerIns.version_check(head.nResult);
			return 0;
		}

		int request_handler::handle_request_ptz_register_res(bool is_ok, unsigned char streamId)
		{ 
			TcpDataManagerIns.ptz_register_res(is_ok, streamId);
			return 0;
		}

		int request_handler::handle_request_spy_register_res(bool is_ok, unsigned char streamId)
		{
			TcpDataManagerIns.spy_register_res(is_ok, streamId);
			return 0;
		}

		int request_handler::handle_request_replay_control(bool is_ok, unsigned char streamId)
		{
			TcpDataManagerIns.getPlaybackRes(is_ok);
			return 0;
		}

		int request_handler::handle_request_disk_size(netbuffer *buf, int n)
		{
			std::vector<api_detu_client_disk_size_t> qurey_list;
			qurey_list.resize(n);
			for (int i = 0; i < n; i++)
			{
				api_detu_client_disk_size_t api_query;// = new api_detu_client_disk_size_t();

				//一段一段读取，并且要大小端转换本地
				netbuffer* temp = new netbuffer();
				temp->buffer = (char*)malloc(sizeof(api_detu_client_disk_size_t));
				temp->buffer_len = sizeof(api_detu_client_disk_size_t);
				memcpy(temp->buffer, (buf->buffer + sizeof(api_detu_client_disk_size_t)*i), sizeof(api_detu_client_disk_size_t));
				api_query.read(temp);
				api_query.copyto(qurey_list[i]);

				free(temp);
			}
	     	TcpDataManagerIns.setDiskSizeList(qurey_list);
			return 0;
		}

		int request_handler::handle_request_handle_stream_res(short result, unsigned char streamId)
		{
			TcpDataManagerIns.handleStreamRes(result, streamId);
			return 0;
		}

		int request_handler::handle_request_reboot_device_res(short result, unsigned char streamId)
		{
			TcpDataManagerIns.handleRebootDeviceRes(result, streamId);
			return 0;
		}

		int request_handler::handle_request_active_report(netbuffer *buf, unsigned char streamId)
		{
			active_report_body_t *handle_api = new active_report_body_t;
			handle_api->read(buf);
			TcpDataManagerIns.handleActiveReport(handle_api->nErrorCode, (char*)handle_api->pvsId, streamId);
			return 0;
		}

		int request_handler::handle_request_get_bandWidth(netbuffer *buf)
		{
			PVSManageTable_t api_data;
			api_data.read(buf);
			TcpDataManagerIns.handleGetBandWidth(api_data);
			return 0;
		}

		int request_handler::handle_request_get_ptz_list(netbuffer *buf)
		{
			PTZManageTableList_t table_list;
			table_list.read(buf);

			std::vector<PTZManageTable_t> qurey_list;
			qurey_list.resize(table_list.numlist);
			for (int i = 0; i < table_list.numlist; ++i)
			{
				PTZManageTable_t api_query;
				table_list.ptzList[i].copyto(api_query);
				api_query.copyto(qurey_list[i]);
			}
			TcpDataManagerIns.handleGetPTZList(qurey_list);
			return 0;
		}

		int request_handler::handle_request_get_spy_list(netbuffer *buf)
		{
			SPYManageTableList_t table_list;
			table_list.read(buf);

			std::vector<SPYManageTable_t> qurey_list;
			qurey_list.resize(table_list.numlist);
			for (int i = 0; i < table_list.numlist; i++)
			{
				SPYManageTable_t api_query;// = new api_detu_client_disk_size_t();
				table_list.spyList[i].copyto(api_query);
				api_query.copyto(qurey_list[i]);				
			}
			TcpDataManagerIns.handleGetSPYList(qurey_list);
			return 0;
		}

		int request_handler::handle_request_delete_ptz(short result)
		{
			TcpDataManagerIns.handleDeletePtz(result);
			return 0;
		}

		int request_handler::handle_request_delete_spy(short result)
		{
			TcpDataManagerIns.handleDeleteSpy(result);
			return 0;
		}

		int request_handler::handle_request_get_ptz_point(netbuffer *buf)
		{
			PtzPoint_t point_list;
			point_list.read(buf);
			std::string ip = (char*)point_list.nIP;
			std::string point = (char*)point_list.nPoint;
			TcpDataManagerIns.handleGetPtzPoint(QString::fromStdString(ip), QString::fromStdString(point));
			return 0;
		}

		int request_handler::handle_request_get_tcs_info(netbuffer *buf)
		{
			api_detu_tcs_register_t detu_reg;
			detu_reg.read(buf);

			TcpDataManagerIns.handleGetTCSInfo(detu_reg);
			return 0;
		}

		int request_handler::handle_request_update_tcs_info(netbuffer *buf)
		{
			api_detu_tcs_heartbeat_t detu_reg;
			detu_reg.read(buf);

			TcpDataManagerIns.handleUpdateTCSInfo(detu_reg);
			return 0;
		}

		int request_handler::handle_request_report_tcs_error(netbuffer *buf, short result)
		{
			api_detu_tcs_transcode_res_t detu_reg;
			detu_reg.read(buf);

			TcpDataManagerIns.handleReportTCSError(detu_reg, result);
			return 0;
		}

		int request_handler::handle_request_tcs_offline(netbuffer *buf)
		{
			api_detu_tcs_register_t detu_reg;
			detu_reg.read(buf);

			TcpDataManagerIns.handleTCSOffLine(detu_reg);
			return 0;
		}

		int request_handler::handle_request_tcs_reset(short result)
		{
			TcpDataManagerIns.handleTCSReset(result);
			return 0;
		}

		int request_handler::handle_request_send_map_data_res(netbuffer *buf)
		{
			Log::Info("CMD_DETU_SEND_MAP_DATA success！");
			return 0;
		}

		int request_handler::handle_request_get_map_data_res(netbuffer *buf)
		{
			//读取地图数据文件，并写磁盘，写完后通知解压
			api_detu_vr_map_data_block api_detu;
			api_detu.read(buf);

			if (api_detu.offset == API_MAP_DATA_BLOCK_LEN)
			{
				remove(QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/Map.zip").toLocal8Bit());
			}

			FILE* map_zip = fopen(QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/Map.zip").toLocal8Bit(), "ab+");
			if (map_zip)
			{
				fseek(map_zip, 0, SEEK_END);
				int sts = fwrite(api_detu.data, 1, API_MAP_DATA_BLOCK_LEN, map_zip);
				if (sts == 0)
				{
					Log::Debug("sts = fread(map_data, 1, map_data_length, pat_pts) failed");
					fclose(map_zip);
				}
			}
			fclose(map_zip);
			Log::Info("handle_request_set_map_data info: length : %d  offset  : %d", api_detu.length / API_MAP_DATA_BLOCK_LEN, api_detu.offset / API_MAP_DATA_BLOCK_LEN);

			if (api_detu.offset == api_detu.length)
			{
				//解压缩Map文件夹

				JlCompress::extractDir(QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/Map.zip") , QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/Map"));
			}

			return 0;
		}

		int request_handler::handle_request_login_checked_res(netbuffer *buf, short result)
		{
			api_detu_client_register_t api_query;
			api_query.read(buf);

			TcpDataManagerIns.handleLoginChecked(api_query, result);
			return 0;
		}

		int request_handler::handle_request_register_user_res(netbuffer *buf, short result)
		{
			api_detu_client_register_t api_query;
			api_query.read(buf);

			TcpDataManagerIns.handleRegisterUser(api_query, result);
			return 0;
		}

	}  // namespace server
} // namespace dem1
