#pragma once

#include <iostream>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include <memory>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include "../sqlite/include/sqlite3.h"
#include <list>
#include "core.h"

#include "APIProtocol.h"

using namespace std;

// 使用宏替代单例实例
#define PVSManage PVSManageTemplate::GetInstance()

namespace dem1 {
	namespace server {
		class PVSManageTemplate
		{
		private:
			friend class auto_ptr<PVSManageTemplate>;				/// 使用智能指针
			static auto_ptr<PVSManageTemplate> auto_ptr_instance;	/// 惟一实例
		private:
			PVSManageTemplate();
			~PVSManageTemplate(void);
		public :
			static PVSManageTemplate& GetInstance(void);		/// 实例(工厂方法)
			static int callback(void *NotUsed, int argc, char **argv, char **azColName);
			void initDatabase(sqlite3 * m_database);
			bool initPVSManageTable();
			bool updatePVSManageTable(PVSManageTable_t prot_table);
			bool getBandWidthFromTable(std::string pvsId, PVSManageTable_t &tableData);
			bool deleteDeviceFromTable(std::string sessionId);
			bool savePVSRegisterInfo(api_register_t prot_table, std::string sessionid);
			bool saveCailbrationInfo(api_detu_client_register_res_t prot_table, std::string sessionId);
			bool saveOptmizeCailbrationInfo(api_detu_client_optmize prot_table);
			bool saveDeviceInfo(api_detu_client_register_res_t prot_table);
			bool getPVSRegisterInfo(std::vector<api_detu_client_register_res_t> &prot_table);
			bool updatePVSDeviceState(std::string sessionId);
			bool getPushFlowNum(std::string deviceID, int &num);
			bool updatePushFlowNum(std::string deviceID, int num);
		private:
			sqlite3 *database;
			std::vector<std::string> m_result;
			boost::mutex mutex_ctrl;
		};
	}
}

