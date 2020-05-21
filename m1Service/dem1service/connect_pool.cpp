#include <stdexcept>
#include <exception>
#include <stdio.h>

#include "connect_pool.hpp"
namespace dem1 {
	namespace server {


		/// 单例声明
		/// 类内 class static 除了在class 之内声明，还需要在class 之外定义.
		auto_ptr<DMConnctionPool> DMConnctionPool::auto_ptr_instance;

		/**
		* @Synopsis  DMConnctionPool
		*	连接池构造函数
		* @Param url
		* @Param userName
		* @Param password
		* @Param maxSize
		*/
		DMConnctionPool::DMConnctionPool(string url, string userName, string password, int maxSize)
			:m_imaxSize(maxSize), m_icurSize(0), m_suserName(userName), m_spassword(password), m_surl(url)
		{
			try {
				m_pdriver = get_driver_instance();
			}
			catch (sql::SQLException &e) {
				Log::Error("dem1service:: 驱动连接出错;\n");
			}

			this->InitConnection(m_imaxSize / 2);
		}

		/**
		* @Synopsis  ~DMConnctionPool
		*	连接池析构函数
		*/
		DMConnctionPool::~DMConnctionPool(void)
		{
			this->TerminateConnectionPool();
		}

		/**
		* @Synopsis  GetInstance
		*	获取连接池对象，单例模式
		* @Returns   连接池对象
		*/
		DMConnctionPool& DMConnctionPool::GetInstance(void)
		{
			if (auto_ptr_instance.get() == 0) {
				auto_ptr_instance.reset(new DMConnctionPool(MYSQL_CONNECT_URL, MYSQL_USERNAME, MYSQL_PASSWORD, MYSQL_THREAD_POOL_SIZE));
			}
			return *(auto_ptr_instance.get());
		}

		/**
		* @Synopsis  InitConnection
		*	初始化连接池，创建最大连接数的一半连接量
		* @Param iInitialSize
		*/
		void DMConnctionPool::InitConnection(int iInitialSize)
		{
			Connection *pConn;
			lock.lock();
			for (int i = 0; i < iInitialSize; ++i) {
				pConn = this->CreateConnection();
				if (pConn) {
					m_connlist.push_back(pConn);
					++(this->m_icurSize);
				}
				else {
					Log::Error("dem1service:: 创建Connection 出错!");
				}
			}
			lock.unlock();
		}

		/**
		* @Synopsis  CreateConnection
		*	创建连接，返回一个 Connection
		* @Returns   sql::connection*
		*/
		Connection* DMConnctionPool::CreateConnection(void)
		{
			Connection *pConn;
			try {
				pConn = m_pdriver->connect(this->m_surl, this->m_suserName, this->m_spassword);
				return pConn;
			}
			catch (sql::SQLException &e) {
				Log::Error("dem1service:: 创建连接出现错误!");
				return NULL;
			}
			/*catch(sql::runtime_error  &e) {
			Log::Error("dem1service:: 运行时出现错误!");
			return NULL;
			}*/
		}

		/**
		* @Synopsis  GetConnection
		*	在连接池中获取一个连接
		* @Returns   sql::connection*
		*/
		Connection* DMConnctionPool::GetConnection(void)
		{
			Connection *pConn;
			lock.lock();
			/// 连接池容器中还有连接
			if (m_connlist.size() > 0) {
				pConn = m_connlist.front();		/// 得到第一个连接
				m_connlist.pop_front();			/// 移除第一个连接
				/// 如果连接池已经关闭，删除后重新建立一个
				if (pConn->isClosed()) {
					delete pConn;
					pConn = this->CreateConnection();
				}
				/// 如果连接为空，则创建连接出错
				if (NULL == pConn) {
					--m_icurSize;
				}
				lock.unlock();
				return pConn;
			}
			else {
				/// 还可以创建新的连接
				if (m_icurSize < m_imaxSize) {
					pConn = this->CreateConnection();
					if (pConn) {
						++m_icurSize;
						lock.unlock();
						return pConn;
					}
					else {
						lock.unlock();
						return NULL;
					}
				}
				else {
					/// 建立的连接数已达到 m_imaxSize 上限
					lock.unlock();
					return NULL;
				}
			}
		}

		/**
		* @Synopsis  ReleaseConnection
		*	回收数据库连接
		* @Param pConn
		*/
		void DMConnctionPool::ReleaseConnection(Connection* pConn)
		{
			if (pConn) {
				lock.lock();
				m_connlist.push_back(pConn);
				lock.unlock();
			}
		}

		/**
		* @Synopsis  TerminateConnectionPool
		*	销毁连接池，首先要先销毁连接池中的连接
		*/
		void DMConnctionPool::TerminateConnectionPool(void)
		{
			list<Connection*>::iterator iconn;
			lock.lock();
			/// 为了符合泛型编程而使用 != 判断
			for (iconn = m_connlist.begin(); iconn != m_connlist.end(); ++iconn)
			{
				this->TerminateConnection(*iconn);	/// 销毁连接池中的连接
			}
			m_icurSize = 0;
			m_connlist.clear();		/// 清空连接池中的连接
			lock.unlock();
		}

		/**
		* @Synopsis  TerminateConnection
		*	销毁一个连接
		* @Param pConn
		*/
		void DMConnctionPool::TerminateConnection(Connection *pConn)
		{
			if (pConn) {
				try{
					pConn->close();
				}
				catch (sql::SQLException &e) {
					Log::Error(e.what());
				}
				/*catch(sql::runtime_error  &e) {
				Log::Error(e.what());
				}*/
			}
			delete pConn;
		}

		/**
		* @Synopsis  GetCurrentSize
		*	获取当前线程池中的有效的连接数(可选)
		* @Returns
		*/
		int DMConnctionPool::GetCurrentSize(void)
		{
			return m_icurSize;
		}


	}
}
