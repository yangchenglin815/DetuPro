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

using namespace std;

// ʹ�ú��������ʵ��
#define PTZManage PTZManageTemplate::GetInstance()

namespace dem1 {
	namespace server {
		class PTZManageTemplate
		{
		private:
			friend class auto_ptr<PTZManageTemplate>;				/// ʹ������ָ��
			static auto_ptr<PTZManageTemplate> auto_ptr_instance;	/// Ωһʵ��
		private:
			PTZManageTemplate();
			~PTZManageTemplate(void);
		public:
			static PTZManageTemplate& GetInstance(void);		/// ʵ��(��������)
			static int callback(void *NotUsed, int argc, char **argv, char **azColName);
			void initDatabase(sqlite3 * m_database);
			bool initPTZManageTable();
			bool updatePTZDeviceToTable(PTZManageTable_t prot_table);
			bool deletePTZDeviceToTable(std::string ip);
			bool getPTZDeviceFromTable(PTZManageTableList_t &ptzList);
			bool savePTZPoint(PtzPoint_t &pointList);
			bool getPTZPoint(PtzPoint_t &pointList);
		private:
			sqlite3 *database;
			std::vector<std::string> m_result;
			boost::mutex mutex_ctrl;
		};
	}
}

