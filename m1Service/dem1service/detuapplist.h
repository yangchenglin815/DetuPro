#pragma once

#include <stdio.h>
#include <iostream>
#include <mysql_connection.h>
#include <mysql_driver.h>

#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include <memory>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>
#include <list>
#include "core.h"

#include "APIProtocol.h"

using namespace std;

// 使用宏替代单例实例
#define DetuAPPlist detuapplist::GetInstance()

namespace dem1 {
	namespace server {
		class connection;
		class detuapplist
		{
		private:
			friend class auto_ptr<detuapplist>;				/// 使用智能指针
			/// 即使从未被调用也会被构造(析构);如果对象使用static 修饰，意思是只有一个对象会被产生出来。
			/// 构造函数属性为 private ，可以防止对象的产生。(auto_ptr need #include <memory>)
			static auto_ptr<detuapplist> auto_ptr_instance;	/// 惟一实例
		private:
			detuapplist();
			~detuapplist(void);
		public:
			static detuapplist& GetInstance(void);		/// 实例(工厂方法)

			bool isDeviceIdExist(std::string appId);

			void addSessionId(std::string session_id, std::string appId);
			void replaceSessionId(std::string session_id, std::string appId);
			void removeSessionId(std::string session_id);
			std::string getSessionIdByDeivceId(std::string appId);
			std::map<std::string, std::string >   getAPPList();

		private:
			std::map<std::string, std::string >  app_list_;
		};
	}
}

