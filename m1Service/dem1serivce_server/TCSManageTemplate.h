#pragma once

#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include "../sqlite/include/sqlite3.h"
#include <list>
#include "core.h"

#include "APIProtocol.h"

using namespace std;

// 使用宏替代单例实例
#define TCSManage TCSManageTemplate::GetInstance()

namespace dem1 {
	namespace server {
		class TCSManageTemplate
		{
		private:
			friend class auto_ptr<TCSManageTemplate>;				/// 使用智能指针
			static auto_ptr<TCSManageTemplate> auto_ptr_instance;	/// 惟一实例
		private:
			TCSManageTemplate();
			~TCSManageTemplate(void);
		public:
			static TCSManageTemplate& GetInstance(void);		/// 实例(工厂方法)
			static int callback(void *NotUsed, int argc, char **argv, char **azColName);
			void initDatabase(sqlite3 * m_database);
			bool initTCSManageTable();
			int saveTCSRegisterInfoToTable(api_detu_tcs_register_t table_data, std::string sessionId);
			bool updateTCSDataToTable(api_detu_tcs_heartbeat_t table_data);
			bool deleteTCSFromTable(std::string sessionId);
			bool deleteTCSServer(int serverId);
			bool getTCSDataListFromTable(std::vector<api_detu_tcs_register_t> &tcsVector);
			bool updatePushFlowDevice(std::string deviceID, std::string sessionID);
			bool getPushFlowDevice(std::string &deviceID, std::string sessionID);
			bool getTCSServerID(int &nServerId, std::string sessionID);
			bool clearData();
		private:
			sqlite3 *database;
			std::vector<std::string> m_result;
			boost::mutex mutex_ctrl;
		};
	}
}

