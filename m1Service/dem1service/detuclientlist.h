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
#define DetuClientlist detuClientlist::GetInstance()

namespace dem1 {
	namespace server {
		class connection;
	

		class detuClientlist
		{

		private:
			friend class auto_ptr<detuClientlist>;				/// 使用智能指针
			/// 即使从未被调用也会被构造(析构);如果对象使用static 修饰，意思是只有一个对象会被产生出来。
			/// 构造函数属性为 private ，可以防止对象的产生。(auto_ptr need #include <memory>)
			static auto_ptr<detuClientlist> auto_ptr_instance;	/// 惟一实例

		private:
			detuClientlist();	/// 构造函数(注意:构造方法私有)
			~detuClientlist(void);							/// 析构函数

		public:
			static detuClientlist& GetInstance(void);		/// 实例(工厂方法)

            bool isDeviceIdExist(std::string deviceId);

            void addSessionId(std::string session_id, std::string deviceId);

			void replaceSessionId(std::string session_id, std::string deviceId);
            void removeSessionId(std::string session_id);
            std::string getSessionIdByDeivceId(std::string deviceId);
            std::map<std::string, std::string >   getClientList();

        private:
            std::map<std::string, std::string >  client_list_;


		};
	}
}