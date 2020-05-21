#include "SessionManageTemplate.h"

#include <stdexcept>
#include <exception>
#include <stdio.h>

namespace dem1 {
	namespace server {
		auto_ptr<SessionManageTemplate> SessionManageTemplate::auto_ptr_instance;
		SessionManageTemplate::SessionManageTemplate()
		{
			database = NULL;
		}

		SessionManageTemplate::~SessionManageTemplate()
		{

		}

        SessionManageTemplate& SessionManageTemplate::GetInstance(void)
		{
			if (auto_ptr_instance.get() == 0) {
				auto_ptr_instance.reset(new SessionManageTemplate());
			}
			return *(auto_ptr_instance.get());
		}

		int SessionManageTemplate::callback(void *NotUsed, int argc, char **argv, char **azColName)
		{
			int i;
			for (i = 0; i < argc; i++){
				if (argv[i] != NULL)
				{
					SessionManage.m_result.push_back(std::string(argv[i]));
				}
				else
				{
					SessionManage.m_result.push_back("");
				}
			}
			return 0;
		}

		bool SessionManageTemplate::updateSessionManageTable(std::string sessionId, std::string deviceId, int type)
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "SELECT COUNT(*) FROM SessionManageTable WHERE deviceID = '" + deviceId + "'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: select SessionManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			if (atoi(m_result.front().c_str()) == 0)
			{
				sqlArray = "INSERT INTO SessionManageTable (sessionID, deviceID, type)" \
					"VALUES ('" \
					+ sessionId + "','" \
					+ deviceId + "','" \
					+ boost::lexical_cast<std::string>(type)+"')";
				rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
				if (rc != SQLITE_OK)
				{
					Log::Error("dem1service:: insert SessionManageTable failed : %s", errMsg);
					sqlite3_free(errMsg);
					mutex_ctrl.unlock();
					return false;
				}
			}
			else
			{
				sqlArray = "UPDATE SessionManageTable SET sessionID = '" + sessionId + "' WHERE deviceID = '" + deviceId + "'";
				rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
				if (rc != SQLITE_OK)
				{
					Log::Error("dem1service:: update SessionManageTable failed : %s", errMsg);
					sqlite3_free(errMsg);
					mutex_ctrl.unlock();
					return false;
				}
			}
			mutex_ctrl.unlock();
			return true;
		}

		bool SessionManageTemplate::deleteSessionFromTable(std::string sessionId)
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "DELETE FROM SessionManageTable WHERE sessionID = '" + sessionId + "'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: delete SessionManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			mutex_ctrl.unlock();
			return true;
		}

		bool SessionManageTemplate::getSessionIdTyptFromTable(std::string sessionId, int &type)
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "SELECT type FROM SessionManageTable WHERE sessionID = '" + sessionId + "';";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: select SessionManageTable register  info failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			if (m_result.size() > 0)
			{
				type = atoi(m_result.at(0).c_str());
			}
			mutex_ctrl.unlock();
			return true;
		}

		bool SessionManageTemplate::getSessionIdByTypeFromTable(std::vector<std::string> &sessionList, int type)
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "SELECT sessionId FROM SessionManageTable WHERE type = '" + boost::lexical_cast<std::string>(type) + "'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: select SessionManageTable sessionidList failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}

			sessionList = m_result;
			mutex_ctrl.unlock();
			return true;
		}

		bool SessionManageTemplate::updatePushFlowDevice(std::string device, std::string sessionId, int deviceType)
		{
			mutex_ctrl.lock();
			int type = -1;
			switch (deviceType)
			{
			case SERVER_TYPE_CLINET:
				type = 1;
				break;
			case SERVER_TYPE_TCS:
				type = 2;
				break;
			default:
				break;
			}

			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "UPDATE SessionManageTable SET pushFlowDevice = '" + device + "' WHERE sessionID = '"
				 + sessionId + "' AND type = '" + boost::lexical_cast<std::string>(type) + "'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: update SessionManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			mutex_ctrl.unlock();
			return true;
		}

		bool SessionManageTemplate::getSessionIdByRequested(std::vector<std::string> &sessionList, std::string pvsId, int deviceType)
		{
			mutex_ctrl.lock();
			int type = -1;
			switch (deviceType)
			{
			case SERVER_TYPE_CLINET:
				type = 1;
				break;
			case SERVER_TYPE_TCS:
				type = 2;
				break;
			default:
				break;
			}

			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "SELECT sessionID FROM SessionManageTable WHERE pushFlowDevice = '" + pvsId + "' AND type = '" + boost::lexical_cast<std::string>(type) + "'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: select SessionManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			sessionList = m_result;
			mutex_ctrl.unlock();
			return true;
		}

		void dem1::server::SessionManageTemplate::initDatabase(sqlite3 * m_database)
		{
			if (database == NULL)
			{
				database = m_database;
			}

			if (!initSessionManageTable())
			{
				Log::Debug("dem1service:: init SessionManage failed!");
			}
		}

		bool dem1::server::SessionManageTemplate::initSessionManageTable()
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "SELECT COUNT(*) FROM sqlite_master WHERE TYPE = 'table' AND NAME = 'SessionManageTable'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: select SessionManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			if (atoi(m_result.front().c_str()) == 0)
			{
				Log::Info("dem1service:: create table : SessionManageTable");
				sqlArray = "CREATE TABLE SessionManageTable(" \
					"id  INTEGER PRIMARY KEY AUTOINCREMENT," \
					"sessionID                               TEXT," \
					"deviceID                                TEXT," \
					"pushFlowDevice                   TEXT DEFAULT NULL," \
					"type                                        INT);";
				rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
				if (rc != SQLITE_OK)
				{
					Log::Error("dem1service:: create SessionManageTable failed : %s", errMsg);
					sqlite3_free(errMsg);
					mutex_ctrl.unlock();
					return false;
				}
			}
			mutex_ctrl.unlock();
			return true;
		}
	}
}
