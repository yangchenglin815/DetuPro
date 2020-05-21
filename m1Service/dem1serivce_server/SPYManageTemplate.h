#pragma once

#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include "../sqlite/include/sqlite3.h"
#include <list>
#include "core.h"

#include "APIProtocol.h"

using namespace std;

// 使用宏替代单例实例
#define SPYManage SPYManageTemplate::GetInstance()

namespace dem1 {
	namespace server {
		class SPYManageTemplate
		{
		private:
			friend class auto_ptr<SPYManageTemplate>;				/// 使用智能指针
			static auto_ptr<SPYManageTemplate> auto_ptr_instance;	/// 惟一实例
		private:
			SPYManageTemplate();
			~SPYManageTemplate(void);
		public:
			static SPYManageTemplate& GetInstance(void);		/// 实例(工厂方法)
			static int callback(void *NotUsed, int argc, char **argv, char **azColName);
			void initDatabase(sqlite3 * m_database);
			bool initSPYManageTable();
			bool updateSPYDeviceToTable(SPYManageTable_t prot_table);
			bool deleteSPYDeviceToTable(std::string ip);
			bool getSPYDeviceFromTable(SPYManageTableList_t &spyList);
		private:
			sqlite3 *database;
			std::vector<std::string> m_result;
			boost::mutex mutex_ctrl;
		};
	}
}