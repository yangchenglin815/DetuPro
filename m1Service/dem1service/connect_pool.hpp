#pragma once

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


using namespace std;
using namespace sql;

/// ʹ�ú��������ʵ��
#define MySQLPool DMConnctionPool::GetInstance()

namespace dem1 {
	namespace server {
		class DMConnctionPool {
		private:
			int m_icurSize;		/// ��ǰ�ѽ��������ݿ�����
			int m_imaxSize;		/// ���ӳ��ж����������ݿ�������
			string m_suserName;	/// ���ݿ��û���
			string m_spassword;	/// ���ݿ��û�����
			string m_surl;		/// ���ݿ����� url

			list<Connection*>m_connlist;	/// ���ӳص���������
			boost::mutex lock;

			Driver *m_pdriver;				/// �������ݿ�����
			/// ����������Ϊ��һ�����friend������ʹ�˺�������private constuctors��Լ����
			friend class auto_ptr<DMConnctionPool>;				/// ʹ������ָ��
			/// ��ʹ��δ������Ҳ�ᱻ����(����);�������ʹ��static ���Σ���˼��ֻ��һ������ᱻ����������
			/// ���캯������Ϊ private �����Է�ֹ����Ĳ�����(auto_ptr need #include <memory>)
			static auto_ptr<DMConnctionPool> auto_ptr_instance;	/// Ωһʵ��

		private:
			DMConnctionPool(string url, string userName, string password, int maxSize);	/// ���캯��(ע��:���췽��˽��)
			~DMConnctionPool(void);							/// ��������
			Connection* CreateConnection(void);				/// ����һ������
			void InitConnection(int iInitialSize);			/// ��ʼ��һ������
			void TerminateConnection(Connection* pConn);	/// ��ֹһ�����ݿ����Ӷ���
			void TerminateConnectionPool(void);				/// ��ֹ���ݿ����ӳ�

		public:
			Connection* GetConnection(void);				///	������ݿ�����
			void ReleaseConnection(Connection *pConn);		/// �����ݿ����ӷŻص����ӳص�������
			static DMConnctionPool& GetInstance(void);		/// ��ȡ���ݿ����ӳ�ʵ��(��������)
			int GetCurrentSize(void);						/// ���ڹ۲�(�Ǳ�Ҫ)
		};
	}
}
