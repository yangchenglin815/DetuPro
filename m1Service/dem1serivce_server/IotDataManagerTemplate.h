#pragma once

#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include "../sqlite/include/sqlite3.h"

#include "core.h"
#include "APIProtocol.h"

using namespace std;

// 使用宏替代单例实例
#define IotDataManage IotDataManagerTemplate::GetInstance()
namespace dem1 {
	namespace server {
		class IotDataManagerTemplate
		{
		public:
		public:
			static IotDataManagerTemplate& GetInstance(void);		/// 实例(工厂方法)
			static int callback(void *NotUsed, int argc, char **argv, char **azColName);
			void initDatabase(sqlite3 * m_database);
			bool initSessionManageTable();
		private:
			friend class auto_ptr<IotDataManagerTemplate>;				/// 使用智能指针
			static auto_ptr<IotDataManagerTemplate> auto_ptr_instance;	/// 惟一实例
		
		private:
			IotDataManagerTemplate();
			~IotDataManagerTemplate(void);
		private:
			sqlite3 *database;
			std::vector<std::string> m_result;
			boost::mutex mutex_ctrl;
		};
	}
}