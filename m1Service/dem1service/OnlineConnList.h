/************************************************
* \file OnlineConnList.h
*
* \author HuZhengdong && YangChenglin
* \date 20180408
* ά�������б�����ͻ��˵�PVS�豸������
************************************************/
#pragma once

#include <iostream>
#include <memory>
#include <list>
#include "core.h"

#include "APIProtocol.h"
#include "construct.h"

#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;

// ʹ�ú��������ʵ��
#define OnlineConnListIns OnlineConnList::GetInstance()

namespace dem1 {
	namespace server {
		class connection;
		class OnlineConnList
		{
		private:
			friend class auto_ptr<OnlineConnList>;				/// ʹ������ָ��
			/// ��ʹ��δ������Ҳ�ᱻ����(����);�������ʹ��static ���Σ���˼��ֻ��һ������ᱻ����������
			/// ���캯������Ϊ private �����Է�ֹ����Ĳ�����(auto_ptr need #include <memory>)
			static auto_ptr<OnlineConnList> auto_ptr_instance;	/// Ωһʵ��

		private:
			OnlineConnList();	/// ���캯��(ע��:���췽��˽��)
			~OnlineConnList(void);							/// ��������

		public:
			static OnlineConnList& GetInstance(void);		/// ʵ��(��������)

			void AddOnlineConn(OnlineConnInfo_t conn);

			std::vector<string> GetList(OnlineConnInfo_t conn);

		private:
			std::vector<OnlineConnInfo_t> online_conn_;
			boost::mutex mutex_ctrl_;
		};

	}
}
