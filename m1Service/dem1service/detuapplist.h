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

// ʹ�ú��������ʵ��
#define DetuAPPlist detuapplist::GetInstance()

namespace dem1 {
	namespace server {
		class connection;
		class detuapplist
		{
		private:
			friend class auto_ptr<detuapplist>;				/// ʹ������ָ��
			/// ��ʹ��δ������Ҳ�ᱻ����(����);�������ʹ��static ���Σ���˼��ֻ��һ������ᱻ����������
			/// ���캯������Ϊ private �����Է�ֹ����Ĳ�����(auto_ptr need #include <memory>)
			static auto_ptr<detuapplist> auto_ptr_instance;	/// Ωһʵ��
		private:
			detuapplist();
			~detuapplist(void);
		public:
			static detuapplist& GetInstance(void);		/// ʵ��(��������)

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

