#include <stdexcept>
#include <exception>
#include <stdio.h>

#include "connect_pool.hpp"
namespace dem1 {
	namespace server {


		/// ��������
		/// ���� class static ������class ֮������������Ҫ��class ֮�ⶨ��.
		auto_ptr<DMConnctionPool> DMConnctionPool::auto_ptr_instance;

		/**
		* @Synopsis  DMConnctionPool
		*	���ӳع��캯��
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
				Log::Error("dem1service:: �������ӳ���;\n");
			}

			this->InitConnection(m_imaxSize / 2);
		}

		/**
		* @Synopsis  ~DMConnctionPool
		*	���ӳ���������
		*/
		DMConnctionPool::~DMConnctionPool(void)
		{
			this->TerminateConnectionPool();
		}

		/**
		* @Synopsis  GetInstance
		*	��ȡ���ӳض��󣬵���ģʽ
		* @Returns   ���ӳض���
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
		*	��ʼ�����ӳأ����������������һ��������
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
					Log::Error("dem1service:: ����Connection ����!");
				}
			}
			lock.unlock();
		}

		/**
		* @Synopsis  CreateConnection
		*	�������ӣ�����һ�� Connection
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
				Log::Error("dem1service:: �������ӳ��ִ���!");
				return NULL;
			}
			/*catch(sql::runtime_error  &e) {
			Log::Error("dem1service:: ����ʱ���ִ���!");
			return NULL;
			}*/
		}

		/**
		* @Synopsis  GetConnection
		*	�����ӳ��л�ȡһ������
		* @Returns   sql::connection*
		*/
		Connection* DMConnctionPool::GetConnection(void)
		{
			Connection *pConn;
			lock.lock();
			/// ���ӳ������л�������
			if (m_connlist.size() > 0) {
				pConn = m_connlist.front();		/// �õ���һ������
				m_connlist.pop_front();			/// �Ƴ���һ������
				/// ������ӳ��Ѿ��رգ�ɾ�������½���һ��
				if (pConn->isClosed()) {
					delete pConn;
					pConn = this->CreateConnection();
				}
				/// �������Ϊ�գ��򴴽����ӳ���
				if (NULL == pConn) {
					--m_icurSize;
				}
				lock.unlock();
				return pConn;
			}
			else {
				/// �����Դ����µ�����
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
					/// �������������Ѵﵽ m_imaxSize ����
					lock.unlock();
					return NULL;
				}
			}
		}

		/**
		* @Synopsis  ReleaseConnection
		*	�������ݿ�����
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
		*	�������ӳأ�����Ҫ���������ӳ��е�����
		*/
		void DMConnctionPool::TerminateConnectionPool(void)
		{
			list<Connection*>::iterator iconn;
			lock.lock();
			/// Ϊ�˷��Ϸ��ͱ�̶�ʹ�� != �ж�
			for (iconn = m_connlist.begin(); iconn != m_connlist.end(); ++iconn)
			{
				this->TerminateConnection(*iconn);	/// �������ӳ��е�����
			}
			m_icurSize = 0;
			m_connlist.clear();		/// ������ӳ��е�����
			lock.unlock();
		}

		/**
		* @Synopsis  TerminateConnection
		*	����һ������
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
		*	��ȡ��ǰ�̳߳��е���Ч��������(��ѡ)
		* @Returns
		*/
		int DMConnctionPool::GetCurrentSize(void)
		{
			return m_icurSize;
		}


	}
}
