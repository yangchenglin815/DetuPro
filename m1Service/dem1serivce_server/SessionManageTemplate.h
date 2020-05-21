#pragma once

#include <iostream>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include <memory>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include "../sqlite/include/sqlite3.h"
#include <list>
#include "core.h"

#include "APIProtocol.h"

/*******************************************************************************************************    
type�ֶα�ʾ��ǰsessionID�������豸���ͣ�0��PVS   1���ͻ���PVMS      2��TCS����      3���ֻ�APP     
sessionID�洢��ǰ�豸����ID
*******************************************************************************************************/

using namespace std;

// ʹ�ú��������ʵ��
#define SessionManage SessionManageTemplate::GetInstance()

namespace dem1 {
	namespace server {
		class SessionManageTemplate
		{
		public:
			static SessionManageTemplate& GetInstance(void);		/// ʵ��(��������)
			static int callback(void *NotUsed, int argc, char **argv, char **azColName);
			void initDatabase(sqlite3 * m_database);
			bool initSessionManageTable();
			bool updateSessionManageTable(std::string sessionId, std::string deviceId, int type);
			bool deleteSessionFromTable(std::string sessionId);
			bool getSessionIdTyptFromTable(std::string sessionId, int &type);
			bool getSessionIdByTypeFromTable(std::vector<std::string> &sessionList, int type);
			bool updatePushFlowDevice(std::string device, std::string sessionId,  int deviceType);
			bool getSessionIdByRequested(std::vector<std::string> &sessionList, std::string pvsId, int deviceType);
		private:
			friend class auto_ptr<SessionManageTemplate>;				/// ʹ������ָ��
			static auto_ptr<SessionManageTemplate> auto_ptr_instance;	/// Ωһʵ��
		private:
			SessionManageTemplate();
			~SessionManageTemplate(void);
		private:
			sqlite3 *database;
			std::vector<std::string> m_result;
			boost::mutex mutex_ctrl;
		};
	}
}

