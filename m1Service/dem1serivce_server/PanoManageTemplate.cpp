#include "PanoManageTemplate.h"

#include <stdexcept>
#include <exception>
#include <stdio.h>

namespace dem1 {
	namespace server {
		auto_ptr<PanoManageTemplate> PanoManageTemplate::auto_ptr_instance;
		PanoManageTemplate::PanoManageTemplate()
		{
			m_database = nullptr;
		}

		PanoManageTemplate::~PanoManageTemplate()
		{

		}

		PanoManageTemplate& PanoManageTemplate::GetInstance(void)
		{
			if (auto_ptr_instance.get() == 0) {
				auto_ptr_instance.reset(new PanoManageTemplate());
			}
			return *(auto_ptr_instance.get());
		}

		int PanoManageTemplate::callback(void *NotUsed, int argc, char **argv, char **azColName)
		{
			int i;
			for (i = 0; i < argc; i++){
				if (argv[i] != NULL)
				{
					PanoManage.m_result.push_back(std::string(argv[i]));
				}
				else
				{
					PanoManage.m_result.push_back("");
				}
			}
			return 0;
		}

		void PanoManageTemplate::initDatabase(sqlite3 * database)
		{
			if (m_database == nullptr)
			{
				m_database = database;
			}

			if (!initPanoManageTable())
			{
				Log::Debug("dem1service:: init PanoManage failed!");
			}
		}

		bool PanoManageTemplate::initPanoManageTable()
		{
			boost::lock_guard<boost::mutex> lock(mutex_ctrl);
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "SELECT COUNT(*) FROM sqlite_master WHERE TYPE = 'table' AND NAME = 'PanoManageTable'";
			rc = sqlite3_exec(m_database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: select failed : %s", errMsg);
				sqlite3_free(errMsg);
				return false;
			}
			if (atoi(m_result.front().c_str()) == 0)
			{
				Log::Info("dem1service:: create table : PanoManageTable");
				sqlArray = "CREATE TABLE PanoManageTable("  \
					"id  INTEGER PRIMARY KEY AUTOINCREMENT," \
					"nClientID                              TEXT  DEFAULT NULL," \
					"sessionID                             TEXT," \
					"nUserName                         TEXT," \
					"nPassWd                              TEXT," \
					"online                                   INT DEFAULT 0);";
				rc = sqlite3_exec(m_database, sqlArray.c_str(), callback, 0, &errMsg);
				if (rc != SQLITE_OK)
				{
					Log::Error("dem1service:: create table PanoManageTable failed : %s", errMsg);
					sqlite3_free(errMsg);
					return false;
				}
			}
			return true;
		}

		bool PanoManageTemplate::savePanoRegisterInfoToTable(api_detu_client_register_t table_data, std::string sessionId, std::string Cuuid)
		{
			boost::lock_guard<boost::mutex> lock(mutex_ctrl);
			m_result.clear();

			std::string sqlArray;
			int rc;
			char *errMsg;
			std::string userName = (char*)table_data.szDetuUserName;
			std::string passWd = (char*)table_data.szDetuPassWord;
// 			sqlArray = "SELECT COUNT(*) FROM PanoManageTable WHERE nClientID = '" + Cuuid + "'";
// 			rc = sqlite3_exec(m_database, sqlArray.c_str(), callback, 0, &errMsg);
// 			if (rc != SQLITE_OK)
// 			{
// 				Log::Error("dem1service:: select PanoManageTable failed : %s", errMsg);
// 				sqlite3_free(errMsg);
// 				return 0;
// 			}
// 			if (atoi(m_result.front().c_str()) == 0)
// 			{
// 				sqlArray = "INSERT INTO PanoManageTable (nClientID, sessionID, nUserName, nPassWd, online) VALUES ('" \
// 					+ Cuuid + "','"
// 					+ sessionId + "','"
// 					+ userName + "','"
// 					+ passWd + "', 1)";
// 				rc = sqlite3_exec(m_database, sqlArray.c_str(), callback, 0, &errMsg);
// 				if (rc != SQLITE_OK)
// 				{
// 					Log::Error("dem1service:: insert PanoManageTable failed : %s", errMsg);
// 					sqlite3_free(errMsg);
// 					return 0;
// 				}
// 			}
// 			else
// 			{
				sqlArray = "UPDATE PanoManageTable SET nUserName = '" + userName + "', nPassWd = '" + passWd + "', sessionID = '" \
					+ sessionId + "', online = 1 WHERE nClientID = '" + Cuuid + "'";
				rc = sqlite3_exec(m_database, sqlArray.c_str(), callback, 0, &errMsg);
				if (rc != SQLITE_OK)
				{
					Log::Error("dem1service:: update PanoManageTable failed : %s", errMsg);
					sqlite3_free(errMsg);
					return 0;
				}
	/*		}*/
			return 1;
		}

		int PanoManageTemplate::registerUser(api_detu_client_register_t table_data, std::string sessionId, std::string cUuid)
		{
			boost::lock_guard<boost::mutex> lock(mutex_ctrl);
			m_result.clear();

			std::string sqlArray;
			int rc;
			char *errMsg;
			std::string userName = (char*)table_data.szDetuUserName;
			std::string passWd = (char*)table_data.szDetuPassWord;
			sqlArray = "SELECT COUNT(*) FROM PanoManageTable WHERE nUserName = '" + userName + "'";
			rc = sqlite3_exec(m_database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: select PanoManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				return READ_DATABASE_ERR;
			}
			if (atoi(m_result.front().c_str()) == 0)
			{
				sqlArray = "INSERT INTO PanoManageTable (nClientID, sessionID, nUserName, nPassWd, online) VALUES ('" \
					+ cUuid + "','"
					+ sessionId + "','"
					+ userName + "','"
					+ passWd + "', 1)";
				rc = sqlite3_exec(m_database, sqlArray.c_str(), callback, 0, &errMsg);
				if (rc != SQLITE_OK)
				{
					Log::Error("dem1service:: insert PanoManageTable failed : %s", errMsg);
					sqlite3_free(errMsg);
					return READ_DATABASE_ERR;
				}
				return REGISTER_SUCCESSFUL;
			}
			return HAVE_BEEN_REGISTERED;
		}

		bool PanoManageTemplate::deletePanoFromTable(std::string sessionId)
		{
			boost::lock_guard<boost::mutex> lock(mutex_ctrl);
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "UPDATE PanoManageTable SET online = 0 WHERE sessionID = '" + sessionId + "'";
		//	sqlArray = "DELETE FROM PanoManageTable WHERE sessionID = '" + sessionId + "'";
			rc = sqlite3_exec(m_database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: delete PanoManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				return false;
			}
			return true;
		}

		int PanoManageTemplate::getLoginInfo(api_detu_client_register_t& table_data)
		{
			boost::lock_guard<boost::mutex> lock(mutex_ctrl);
			m_result.clear();
			std::string userName = (char*)table_data.szDetuUserName;
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "SELECT COUNT(*) FROM PanoManageTable WHERE nUserName = '" + userName + "'";
			rc = sqlite3_exec(m_database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: [getLoginInfo] select PanoManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				return READ_DATABASE_ERR;
			}
			if (atoi(m_result.front().c_str()) == 0)
			{
				return USERNAME_ERR;
			}

			m_result.clear();
			std::string passwd = (char*)table_data.szDetuPassWord;
			sqlArray = "SELECT nPassWd, nClientID, online FROM PanoManageTable WHERE nUserName = '" + userName + "'";
			rc = sqlite3_exec(m_database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: [getLoginInfo] select PanoManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				return READ_DATABASE_ERR;
			}
		    if (m_result[0] != passwd)
		    {
				return PASSWD_ERR;
		    }
			else if (atoi(m_result[2].c_str()) == 1)
			{
				return MUTI_CLIENT_ERR;
			}


			memcpy(table_data.szDetuDeviceUUId, m_result[1].c_str(), API_RTMP_LEN);
			return CHECK_FINISHED;
		}

	}
}