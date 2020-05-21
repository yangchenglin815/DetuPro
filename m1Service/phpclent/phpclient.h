#pragma once

#include <iostream>
#include <memory>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>


// 使用宏替代单例实例
#define phpclientIns phpclient::GetInstance()

using namespace std;


		class phpclient
		{
			private:
				friend class auto_ptr<phpclient>;				/// 使用智能指针
				static auto_ptr<phpclient> auto_ptr_instance;	/// 惟一实例

			private:
				phpclient();
				~phpclient(void);

			public:
				static phpclient& GetInstance(void);		/// 实例(工厂方法)
				static int callback(void *NotUsed, int argc, char **argv, char **azColName);

				void open();
				void send();
				void recv();

			private:
				std::vector<std::string> m_result;
		};
