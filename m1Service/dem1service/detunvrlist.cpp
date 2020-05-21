#include <stdexcept>
#include <exception>
#include <stdio.h>

#include "detunvrlist.h"
#include "connection.hpp"
#include "../dem1serivce_server/sqliteManage.h"
#include "../dem1serivce_server/PVSManageTemplate.h"

namespace dem1 {
    namespace server {
        /// 单例声明
        /// 类内 class static 除了在class 之内声明，还需要在class 之外定义.
        auto_ptr<detuNvrList> detuNvrList::auto_ptr_instance;

        detuNvrList::detuNvrList()
        {
            nvr_list_.clear();
        }

        detuNvrList::~detuNvrList()
        {
        }

        detuNvrList& detuNvrList::GetInstance(void)
        {
            if (auto_ptr_instance.get() == 0) {
                auto_ptr_instance.reset(new detuNvrList());
            }
            return *(auto_ptr_instance.get());
        }

        bool detuNvrList::isDeviceIdExist(std::string deviceId)
        {
			std::map < std::string, api_detu_client_register_res_t>::iterator it = nvr_list_.begin();
            while (it != nvr_list_.end())
            {
                if (it->second.szDeviceId == (unsigned char*)deviceId.c_str())
                {
                    //不能删掉
                    //it = nvr_list_.erase(it);
                    return true;
                }
				it++;
            }
            return false;
        }

		void detuNvrList::addSessionId(std::string session_id, api_detu_client_register_res_t api_reg)
        {
			bool is_device_added = false;
			std::map < std::string, api_detu_client_register_res_t>::iterator it = nvr_list_.begin();
			while (it != nvr_list_.end())
			{
				if ((char*)api_reg.szDeviceId == (char*)it->second.szDeviceId)
				{
					//is_device_added = true;
					it = nvr_list_.erase(it);
				}
				it++;
			}
// 			if (!is_device_added)
// 			{
				Log::Info("dem1service:: Add Pano-VMS deviceId: %s", api_reg.szDeviceId);
				nvr_list_.insert(pair<std::string, api_detu_client_register_res_t >(session_id, api_reg));
/*			}*/
        }

		void detuNvrList::addSessionId(std::string session_id, unsigned char* m1DeviceId, int nPtsLen, unsigned char* ptsData)
		{
			Log::Info("dem1service:: Add M1 deviceId: %s", m1DeviceId);
			memcpy(nvr_list_[session_id].m1DeviceId, m1DeviceId, API_ARRAY_LEN);
			nvr_list_[session_id].pts.nPtsLen = nPtsLen;
			memcpy(nvr_list_[session_id].pts.pts_data, ptsData, API_PTS_LEN);
		}

		void detuNvrList::saveDeviceName(std::string session_id, api_detu_client_register_res_t api_reg)
		{
			std::map < std::string, api_detu_client_register_res_t>::iterator it = nvr_list_.begin();
			while (it != nvr_list_.end())
			{
				if ((char*)api_reg.szDeviceId == (char*)it->second.szDeviceId)
				{
					memcpy(it->second.szName, api_reg.szName, API_ARRAY_LEN);
					it->second.szUpDown = api_reg.szUpDown;
				}
				it++;
			}
		}

		void detuNvrList::savePTSData(std::string session_id, api_detu_client_optmize_t api_reg)
		{
			
			std::map < std::string, api_pts_file>::iterator it = pts_list_.begin();
			int cnt = 0;
			std::string szDeviceId = (char*)api_reg.szDeviceId;
			while (it != pts_list_.end())
			{
				if (it->first == szDeviceId)
				{
					it->second.nPtsLen = api_reg.optmize_pts.nPtsLen;
					memcpy(it->second.pts_data, api_reg.optmize_pts.pts_data, API_ARRAY_LEN);
					cnt++;
				}
				it++;
			}
			if (!cnt)
			{
				pts_list_.insert(pair<std::string, api_pts_file >(szDeviceId, api_reg.optmize_pts));
			}
		}

		bool detuNvrList::savePTZ(api_detu_client_register_res_t api_reg)
		{
			std::map < std::string, api_detu_client_register_res_t>::iterator it = nvr_list_.begin();
			while (it != nvr_list_.end())
			{
				if ((char*)api_reg.szDeviceId == (char*)it->second.szDeviceId)
				{
					memcpy(it->second.ptz.nIP, api_reg.ptz.nIP, API_ARRAY_LEN);
					it->second.ptz.nPort = api_reg.ptz.nPort;
					memcpy(it->second.ptz.nUser, api_reg.ptz.nUser, API_ARRAY_LEN);
					memcpy(it->second.ptz.nPasswd, api_reg.ptz.nPasswd, API_ARRAY_LEN);
					return true;
				}
				it++;
			}
			return false;
		}

		void detuNvrList::removeSessionId(std::string  session_id)
        {
			std::map < std::string, api_detu_client_register_res_t>::iterator it = nvr_list_.begin();
            while (it != nvr_list_.end())
            {
                if (it->first == session_id)
                {
                    it = nvr_list_.erase(it);
                }
                else{
                    it++;
                }
            }
        }

        std::string detuNvrList::getSessionIdByDeivceId(std::string deviceId)
        {
			std::map < std::string, api_detu_client_register_res_t>::iterator it = nvr_list_.begin();
            while (it != nvr_list_.end())
            {
				std::string temp = (char*)it->second.szDeviceId;
				if (temp == deviceId)
                {
                    return it->first;
                }

                it++;

            }

             return "";
        }

		std::string detuNvrList::getDeviceIdBySessionld(std::string sessionid)
		{
			std::map < std::string, api_detu_client_register_res_t>::iterator it = nvr_list_.begin();
			while (it != nvr_list_.end())
			{
				if (it->first == sessionid)
				{
					std::string temp = (char*)it->second.szDeviceId;
					return temp;
				}

				it++;

			}

 			return "";
		}

		std::map < std::string, api_detu_client_register_res_t>  detuNvrList::getNvrList()
        {
            return nvr_list_;
        }

		std::map<std::string, api_pts_file_t> detuNvrList::getPtsList()
		{
			return pts_list_;
		}

		void detuNvrList::updateCurrentNvrRtmpPath(std::string session_id, std::string nvr_rtmp_path)
		{
			nvr_current_rtmp_path_[session_id] = nvr_rtmp_path;
		}

		std::string detuNvrList::getRtmpPathByDeivceId(std::string session_id)
		{
			return nvr_current_rtmp_path_[session_id];
		}

		void detuNvrList::addNvrPts(protocol_head_t *head, netbuffer *buf)
		{
			if (head->nStreamId==1)
			{
				nvr_keep_five_pts_list_.clear();
				nvr_keep_five_pts_list_.resize(0);
			}
			api_record_query_t temp;
			temp.read(buf);
			nvr_keep_five_pts_list_.push_back(temp);
		}

	}
}