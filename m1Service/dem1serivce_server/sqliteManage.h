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

// 使用宏替代单例实例
#define SQLITE3Manage sqliteManage::GetInstance()

namespace dem1 {
	namespace server {
		class sqliteManage
		{
		private:
			friend class auto_ptr<sqliteManage>;				/// 使用智能指针
			static auto_ptr<sqliteManage> auto_ptr_instance;	/// 惟一实例
		private:
			sqliteManage();
			~sqliteManage(void);
		public:
			static sqliteManage& GetInstance(void);		/// 实例(工厂方法)
			void initDataBase();
		private:
			sqlite3 *database;
		};
	}
}

