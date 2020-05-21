#include "detuClientlist.h"
#include "connection.hpp"

namespace dem1 {
    namespace server {
		/// ��������
		/// ���� class static ������class ֮������������Ҫ��class ֮�ⶨ��.
		auto_ptr<detuClientlist> detuClientlist::auto_ptr_instance;

		detuClientlist::detuClientlist()
		{
			client_list_.clear();
		}

		detuClientlist::~detuClientlist()
		{
		}

		detuClientlist& detuClientlist::GetInstance(void)
		{
			if (auto_ptr_instance.get() == 0) {
				auto_ptr_instance.reset(new detuClientlist());
			}
			return *(auto_ptr_instance.get());
		}

        bool detuClientlist::isDeviceIdExist(std::string deviceId)
        {
            std::map < std::string, std::string>::iterator it = client_list_.begin();
            while (it != client_list_.end())
            {
                if (it->second == deviceId)
                {
                    //it = client_list_.erase(it);
                    return true;
                }
				it++;
            }
            return false;
        }

        void detuClientlist::addSessionId(std::string session_id, std::string deviceId)
		{
			Log::Info("dem1service:: add detu client session : %s, deviceId : %s", session_id.c_str(), deviceId.c_str());
            client_list_[session_id] = deviceId;
		}

		void detuClientlist::replaceSessionId(std::string session_id, std::string deviceId)
		{
			//��ǰֻ��һ����·������ֱ��clear
			client_list_.clear();
			client_list_[session_id] = deviceId;
		}

		void detuClientlist::removeSessionId(std::string  session_id)
		{
            std::map < std::string, std::string>::iterator it = client_list_.begin();
            while (it != client_list_.end())
            {
                if (it->first == session_id)
                {
                    it = client_list_.erase(it);
                }
                else{
                    it++;
                }
            }
		}

        std::string detuClientlist::getSessionIdByDeivceId(std::string deviceId)
        {
            std::map < std::string, std::string>::iterator it = client_list_.begin();
            while (it != client_list_.end())
            {
                if (it->second == deviceId)
                {
                    return it->first;
                }

                it++;

            }

            return "";
        }

        std::map<std::string, std::string >  detuClientlist::getClientList()
        {
            return client_list_;
        }

    }
}