#include "TCSManageTemplate.h"

#include <stdexcept>
#include <exception>
#include <stdio.h>

namespace dem1 {
	namespace server {
		auto_ptr<TCSManageTemplate> TCSManageTemplate::auto_ptr_instance;
		TCSManageTemplate::TCSManageTemplate()
		{
			database = NULL;
		}

		TCSManageTemplate::~TCSManageTemplate()
		{

		}

		TCSManageTemplate& TCSManageTemplate::GetInstance(void)
		{
			if (auto_ptr_instance.get() == 0) {
				auto_ptr_instance.reset(new TCSManageTemplate());
			}
			return *(auto_ptr_instance.get());
		}

		int TCSManageTemplate::callback(void *NotUsed, int argc, char **argv, char **azColName)
		{
			int i;
			for (i = 0; i < argc; i++){
				if (argv[i] != NULL)
				{
					TCSManage.m_result.push_back(std::string(argv[i]));
				}
				else
				{
					TCSManage.m_result.push_back("");
				}
			}
			return 0;
		}

		void TCSManageTemplate::initDatabase(sqlite3 * m_database)
		{
			if (database == NULL)
			{
				database = m_database;
			}

			if (!initTCSManageTable())
			{
				Log::Debug("dem1service:: init TCSManage failed!");
			}
		}

		bool TCSManageTemplate::initTCSManageTable()
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "SELECT COUNT(*) FROM sqlite_master WHERE TYPE = 'table' AND NAME = 'TCSManageTable'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: select failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			if (atoi(m_result.front().c_str()) == 0)
			{
				Log::Info("dem1service:: create table : TCSManageTable");
				sqlArray = "CREATE TABLE TCSManageTable("  \
					"id  INTEGER PRIMARY KEY AUTOINCREMENT," \
					"szDevice                              TEXT  DEFAULT NULL," \
					"szTcsIp                                 TEXT," \
					"nPort                                    TEXT," \
					"sessionID                             TEXT," \
					"nServerId                             INT," \
					"nLimits                                 INT," \
					"nCAU                                    INT  DEFAULT 0," \
					"nHeartbeatInterval            INT);";
				rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
				if (rc != SQLITE_OK)
				{
					Log::Error("dem1service:: create table TCSManageTable failed : %s", errMsg);
					sqlite3_free(errMsg);
					mutex_ctrl.unlock();
					return false;
				}
			}
			mutex_ctrl.unlock();
			return true;
		}

		int TCSManageTemplate::saveTCSRegisterInfoToTable(api_detu_tcs_register_t table_data, std::string sessionId)
		{
			mutex_ctrl.lock();
			m_result.clear();

			std::string sqlArray;
			int rc;
			char *errMsg;
			std::string szTcsIp = (char*)table_data.szTcsIp;
			sqlArray = "SELECT COUNT(*) FROM TCSManageTable WHERE nServerId = '" + boost::lexical_cast<std::string>(table_data.nServerId) + "'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: select TCSManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return RESULT_FAILED;
			}
			if (atoi(m_result.front().c_str()) == 0)
			{
				sqlArray = "INSERT INTO TCSManageTable (szTcsIp, nPort, sessionID, nServerId, nLimits, nHeartbeatInterval) VALUES ('" \
					+ szTcsIp + "','"
					+ boost::lexical_cast<std::string>(table_data.nPort) + "','"
					+ sessionId + "','"
					+ boost::lexical_cast<std::string>(table_data.nServerId) + "','"
					+ boost::lexical_cast<std::string>(table_data.nLimits) + "','"
					+ boost::lexical_cast<std::string>(table_data.nHeartbeatInterval)
					+ "')";
				rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
				if (rc != SQLITE_OK)
				{
					Log::Error("dem1service:: insert TCSManageTable failed : %s", errMsg);
					sqlite3_free(errMsg);
					mutex_ctrl.unlock();
					return RESULT_FAILED;
				}
			}
			else
			{
				sqlArray = "UPDATE TCSManageTable SET szTcsIp = '" + szTcsIp + "', nPort = '" + boost::lexical_cast<std::string>(table_data.nPort) + "', sessionID = '" + sessionId + "', nLimits = '" + boost::lexical_cast<std::string>(table_data.nLimits) + "', nHeartbeatInterval = '" + boost::lexical_cast<std::string>(table_data.nHeartbeatInterval) + "' WHERE nServerId = '" + boost::lexical_cast<std::string>(table_data.nServerId) + "'";
				rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
				if (rc != SQLITE_OK)
				{
					Log::Error("dem1service:: update TCSManageTable failed : %s", errMsg);
					sqlite3_free(errMsg);
					mutex_ctrl.unlock();
					return RESULT_FAILED;
				}
				mutex_ctrl.unlock();
				return RESULT_SUCCESS;
			}
			mutex_ctrl.unlock();
			return RESULT_SUCCESS;
		}

		bool TCSManageTemplate::updateTCSDataToTable(api_detu_tcs_heartbeat_t table_data)
		{
			mutex_ctrl.lock();
			m_result.clear();

			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "UPDATE  TCSManageTable SET nCAU = '" + boost::lexical_cast<std::string>(table_data.nCAU) + "' WHERE nServerId = '" \
			+ boost::lexical_cast<std::string>(table_data.nServerId) + "'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: update TCSManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			mutex_ctrl.unlock();
			return true;
		}

		bool TCSManageTemplate::deleteTCSFromTable(std::string sessionId)
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "DELETE FROM TCSManageTable WHERE sessionID = '" + sessionId + "'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: delete TCSManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			mutex_ctrl.unlock();
			return true;
		}

		bool TCSManageTemplate::deleteTCSServer(int serverId)
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "DELETE FROM TCSManageTable WHERE nServerId = '" + boost::lexical_cast<std::string>(serverId) + "'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: delete TCSManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			mutex_ctrl.unlock();
			return true;
		}

		bool TCSManageTemplate::getTCSDataListFromTable(std::vector<api_detu_tcs_register_t> &tcsVector)
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "SELECT  szTcsIp, nPort, nServerId, nLimits, nHeartbeatInterval FROM TCSManageTable";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: select TCSManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}

			int size = m_result.size();
			if (size > 0 && size % 5 == 0)
			{
				for (int i = 0; i < size / 5; ++i)
				{
					api_detu_tcs_register_t prot;
					memcpy(prot.szTcsIp, m_result.at(0 + i * 5).c_str(), API_ARRAY_LEN);
					prot.nPort = atoi(m_result.at(1 + i * 5).c_str());
					prot.nServerId = atoi(m_result.at(2 + i * 5).c_str());
					prot.nLimits = atoi(m_result.at(3 + i * 5).c_str());
					prot.nHeartbeatInterval = atoi(m_result.at(4 + i * 5).c_str());

					tcsVector.push_back(prot);
				}
			}
			mutex_ctrl.unlock();
			return true;
		}

		bool TCSManageTemplate::updatePushFlowDevice(std::string deviceID, std::string sessionID)
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "UPDATE TCSManageTable SET szDevice = '" + deviceID + "' WHERE sessionID = '" + sessionID + "'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: update TCSManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			mutex_ctrl.unlock();
			return true;
		}

		bool TCSManageTemplate::getPushFlowDevice(std::string &deviceID, std::string sessionID)
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "SELECT szDevice FROM TCSManageTable WHERE sessionID = '" +sessionID + "'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: select TCSManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			if (m_result.size() > 0)
			{
				deviceID = m_result[0];
			}
			mutex_ctrl.unlock();
			return true;
		}

		bool TCSManageTemplate::getTCSServerID(int &serverID, std::string sessionID)
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "SELECT nServerId FROM TCSManageTable WHERE sessionID = '" + sessionID + "'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: select TCSManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}

			if (m_result.size() > 0)
			{
				serverID = atoi(m_result[0].c_str());
			}
			mutex_ctrl.unlock();
			return true;
		}

		bool TCSManageTemplate::clearData()
		{
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "DELETE FROM TCSManageTable";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: clear TCSManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			mutex_ctrl.unlock();
			return true;
		}

	}
}