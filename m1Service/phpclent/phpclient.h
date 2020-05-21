#pragma once

#include <iostream>
#include <memory>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>


// ʹ�ú��������ʵ��
#define phpclientIns phpclient::GetInstance()

using namespace std;


		class phpclient
		{
			private:
				friend class auto_ptr<phpclient>;				/// ʹ������ָ��
				static auto_ptr<phpclient> auto_ptr_instance;	/// Ωһʵ��

			private:
				phpclient();
				~phpclient(void);

			public:
				static phpclient& GetInstance(void);		/// ʵ��(��������)
				static int callback(void *NotUsed, int argc, char **argv, char **azColName);

				void open();
				void send();
				void recv();

			private:
				std::vector<std::string> m_result;
		};
