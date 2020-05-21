#pragma once

#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include "../sqlite/include/sqlite3.h"
#include <list>
#include "core.h"

#include "APIProtocol.h"

using namespace std;

// ʹ�ú��������ʵ��
#define TCSManage TCSManageTemplate::GetInstance()

namespace dem1 {
	namespace server {
		class TCSManageTemplate
		{
		private:
			friend class auto_ptr<TCSManageTemplate>;				/// ʹ������ָ��
			static auto_ptr<TCSManageTemplate> auto_ptr_instance;	/// Ωһʵ��
		private:
			TCSManageTemplate();
			~TCSManageTemplate(void);
		public:
			static TCSManageTemplate& GetInstance(void);		/// ʵ��(��������)
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

