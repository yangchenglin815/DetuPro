#include "detuapplist.h"
#include "connection.hpp"
#include "logging.hpp"

namespace dem1 {
	namespace server {
		/// 单例声明
		/// 类内 class static 除了在class 之内声明，还需要在class 之外定义.
		auto_ptr<detuapplist> detuapplist::auto_ptr_instance;

		detuapplist::detuapplist()
		{
			app_list_.clear();
		}

		detuapplist::~detuapplist()
		{

		}

		detuapplist& detuapplist::GetInstance(void)
		{
			if (auto_ptr_instance.get() == 0) {
				auto_ptr_instance.reset(new detuapplist());
			}
			return *(auto_ptr_instance.get());
		}

		bool detuapplist::isDeviceIdExist(std::string appId)
		{
			std::map < std::string, std::string>::iterator it = app_list_.begin();
			while (it != app_list_.end())
			{
				if (it->second == appId)
				{
					return true;
				}
				it++;
			}
			return false;
		}

		void detuapplist::addSessionId(std::string session_id, std::string appId)
		{
			Log::Info("dem1service:: add detu app session : %s, deviceId : %s", session_id.c_str(), appId.c_str());
			app_list_[session_id] = appId;
		}

		void detuapplist::replaceSessionId(std::string session_id, std::string appId)
		{
			//当前只有一个链路，可以直接clear
			app_list_.clear();
			app_list_[session_id] = appId;
		}

		void detuapplist::removeSessionId(std::string session_id)
		{
			std::map < std::string, std::string>::iterator it = app_list_.begin();
			while (it != app_list_.end())
			{
				if (it->first == session_id)
				{
					it = app_list_.erase(it);
				}
				else{
					it++;
				}
			}
		}

		std::string detuapplist::getSessionIdByDeivceId(std::string appId)
		{
			std::map < std::string, std::string>::iterator it = app_list_.begin();
			while (it != app_list_.end())
			{
				if (it->second == appId)
				{
					return it->first;
				}

				it++;

			}

			return "";
		}

		std::map<std::string, std::string > detuapplist::getAPPList()
		{
			return app_list_;
		}

	}
}