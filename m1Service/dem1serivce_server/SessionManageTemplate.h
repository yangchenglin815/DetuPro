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
type字段表示当前sessionID的所属设备类型：0：PVS   1：客户端PVMS      2：TCS服务      3：手机APP     
sessionID存储当前设备链接ID
*******************************************************************************************************/

using namespace std;

// 使用宏替代单例实例
#define SessionManage SessionManageTemplate::GetInstance()

namespace dem1 {
	namespace server {
		class SessionManageTemplate
		{
		public:
			static SessionManageTemplate& GetInstance(void);		/// 实例(工厂方法)
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
			friend class auto_ptr<SessionManageTemplate>;				/// 使用智能指针
			static auto_ptr<SessionManageTemplate> auto_ptr_instance;	/// 惟一实例
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

