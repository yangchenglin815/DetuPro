#pragma once

#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include "../sqlite/include/sqlite3.h"
#include <list>
#include "core.h"

#include "APIProtocol.h"

using namespace std;

// ʹ�ú��������ʵ��
#define PanoManage PanoManageTemplate::GetInstance()

namespace dem1 {
	namespace server {
		class PanoManageTemplate
		{
		private:
			friend class auto_ptr<PanoManageTemplate>;				/// ʹ������ָ��
			static auto_ptr<PanoManageTemplate> auto_ptr_instance;	/// Ωһʵ��
		private:
			PanoManageTemplate();
			~PanoManageTemplate(void);
		public:
			static PanoManageTemplate& GetInstance(void);		/// ʵ��(��������)
			static int callback(void *NotUsed, int argc, char **argv, char **azColName);
			void initDatabase(sqlite3 * database);
			bool initPanoManageTable();
			bool savePanoRegisterInfoToTable(api_detu_client_register_t table_data, std::string sessionId, std::string Cuuid);
			int registerUser(api_detu_client_register_t table_data, std::string sessionId, std::string cUuid);
			bool deletePanoFromTable(std::string sessionId);
			int getLoginInfo(api_detu_client_register_t& table_data);
		private:
			sqlite3 *m_database;
			std::vector<std::string> m_result;
			boost::mutex mutex_ctrl;
		};
	}
}

