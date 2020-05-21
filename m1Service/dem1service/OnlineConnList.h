/************************************************
* \file OnlineConnList.h
*
* \author HuZhengdong && YangChenglin
* \date 20180408
* 维护在线列表，保存客户端到PVS设备的链接
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

// 使用宏替代单例实例
#define OnlineConnListIns OnlineConnList::GetInstance()

namespace dem1 {
	namespace server {
		class connection;
		class OnlineConnList
		{
		private:
			friend class auto_ptr<OnlineConnList>;				/// 使用智能指针
			/// 即使从未被调用也会被构造(析构);如果对象使用static 修饰，意思是只有一个对象会被产生出来。
			/// 构造函数属性为 private ，可以防止对象的产生。(auto_ptr need #include <memory>)
			static auto_ptr<OnlineConnList> auto_ptr_instance;	/// 惟一实例

		private:
			OnlineConnList();	/// 构造函数(注意:构造方法私有)
			~OnlineConnList(void);							/// 析构函数

		public:
			static OnlineConnList& GetInstance(void);		/// 实例(工厂方法)

			void AddOnlineConn(OnlineConnInfo_t conn);

			std::vector<string> GetList(OnlineConnInfo_t conn);

		private:
			std::vector<OnlineConnInfo_t> online_conn_;
			boost::mutex mutex_ctrl_;
		};

	}
}
