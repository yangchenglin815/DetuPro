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
#include "PTZManageTemplate.h"
#include "PVSManageTemplate.h"
#include "SPYManageTemplate.h"
#include "TCSManageTemplate.h"
#include "SessionManageTemplate.h"
#include "PanoManageTemplate.h"
#include "IotDataManagerTemplate.h"

#include <list>
#include "core.h"

#include "APIProtocol.h"

using namespace std;

// ʹ�ú��������ʵ��
#define SQLITE3Manage sqliteManage::GetInstance()

namespace dem1 {
	namespace server {
		class sqliteManage
		{
		private:
			friend class auto_ptr<sqliteManage>;				/// ʹ������ָ��
			static auto_ptr<sqliteManage> auto_ptr_instance;	/// Ωһʵ��
		private:
			sqliteManage();
			~sqliteManage(void);
		public:
			static sqliteManage& GetInstance(void);		/// ʵ��(��������)
			void initDataBase();
		private:
			sqlite3 *database;
		};
	}
}

