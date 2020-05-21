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
#define DetuClientlist detuClientlist::GetInstance()

namespace dem1 {
	namespace server {
		class connection;
	

		class detuClientlist
		{

		private:
			friend class auto_ptr<detuClientlist>;				/// ʹ������ָ��
			/// ��ʹ��δ������Ҳ�ᱻ����(����);�������ʹ��static ���Σ���˼��ֻ��һ������ᱻ����������
			/// ���캯������Ϊ private �����Է�ֹ����Ĳ�����(auto_ptr need #include <memory>)
			static auto_ptr<detuClientlist> auto_ptr_instance;	/// Ωһʵ��

		private:
			detuClientlist();	/// ���캯��(ע��:���췽��˽��)
			~detuClientlist(void);							/// ��������

		public:
			static detuClientlist& GetInstance(void);		/// ʵ��(��������)

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