#include "PTZManageTemplate.h"

#include <stdexcept>
#include <exception>
#include <stdio.h>

namespace dem1 {
	namespace server {
		auto_ptr<PTZManageTemplate> PTZManageTemplate::auto_ptr_instance;
		PTZManageTemplate::PTZManageTemplate()
		{
			database = NULL;
		}


		PTZManageTemplate::~PTZManageTemplate()
		{

		}

		PTZManageTemplate& PTZManageTemplate::GetInstance(void)
		{
			if (auto_ptr_instance.get() == 0) {
				auto_ptr_instance.reset(new PTZManageTemplate());
			}
			return *(auto_ptr_instance.get());
		}

		int PTZManageTemplate::callback(void *NotUsed, int argc, char **argv, char **azColName)
		{
			int i;
			//PTZManage.m_result.clear();
			for (i = 0; i < argc; i++){
				//Log::Info("dem1service:: %s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
				if (argv[i] != NULL)
				{
					PTZManage.m_result.push_back(std::string(argv[i]));
				}
				else
				{
					PTZManage.m_result.push_back("");
				}
			}
			return 0;
		}

		void PTZManageTemplate::initDatabase(sqlite3 * m_database)
		{
			if (database == NULL)
			{
				database = m_database;
			}

			if (!initPTZManageTable())
			{
				Log::Debug("dem1service:: init PTZManage failed!");
			}
		}

		bool PTZManageTemplate::initPTZManageTable()
		{
			mutex_ctrl.lock();
			m_result.clear();

			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "SELECT COUNT(*) FROM sqlite_master WHERE TYPE = 'table' AND NAME = 'PTZManageTable'";
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
				Log::Info("dem1service:: create table : PTZManageTable");
				sqlArray = "CREATE TABLE PTZManageTable("  \
					"id  INTEGER PRIMARY KEY AUTOINCREMENT," \
					"PVSId                                 TEXT," \
					"username                          TEXT," \
					"passwd                              TEXT," \
					"IP                                        TEXT," \
					"port                                   TEXT,"  \
					"point                                 TEXT);";
				rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
				if (rc != SQLITE_OK)
				{
					Log::Error("dem1service:: create table failed : %s", errMsg);
					sqlite3_free(errMsg);
					mutex_ctrl.unlock();
					return false;
				}
			}
			mutex_ctrl.unlock();
			return true;
		}

		bool PTZManageTemplate::updatePTZDeviceToTable(PTZManageTable_t prot_table)
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			std::string pvsID = (char*)prot_table.pvsID;
			std::string username = (char*)prot_table.username;
			std::string passwd = (char*)prot_table.passwd;
			std::string ip = (char*)prot_table.nIP;
			sqlArray = "SELECT COUNT(*) FROM PTZManageTable WHERE IP = '" + ip + "'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: select PTZManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			if (atoi(m_result.front().c_str()) == 0)
			{
				sqlArray = "INSERT INTO PTZManageTable (PVSID, username, passwd, IP, port) VALUES ('" \
					+ pvsID + "','"
					+ username + "','"
					+ passwd + "','"
					+ ip + "','"
					+ boost::lexical_cast<std::string>(prot_table.nPort) 
					+ "')";
				rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
				if (rc != SQLITE_OK)
				{
					Log::Error("dem1service:: insert PTZManageTable failed : %s", errMsg);
					sqlite3_free(errMsg);
					mutex_ctrl.unlock();
					return false;
				}
			}
			else
			{
				sqlArray = "UPDATE PTZManageTable SET PVSID = '" + pvsID
					+ "', username = '" + username
					+ "', passwd = '" + passwd
					+ "', port = '" + boost::lexical_cast<std::string>(prot_table.nPort)
					+ "' WHERE IP = '" + ip + "'";
				rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
				if (rc != SQLITE_OK)
				{
					Log::Error("dem1service:: update PTZManageTable failed : %s", errMsg);
					sqlite3_free(errMsg);
					mutex_ctrl.unlock();
					return false;
				}
			}
			mutex_ctrl.unlock();
			return true;
		}

		bool PTZManageTemplate::deletePTZDeviceToTable(std::string ip)
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "DELETE FROM PTZManageTable WHERE IP = '" + ip + "'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: delete PTZManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			mutex_ctrl.unlock();
			return true;
		}

		bool PTZManageTemplate::getPTZDeviceFromTable(PTZManageTableList_t &ptzList)
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "SELECT PVSId, username, passwd, IP, port FROM PTZManageTable";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: select all data from  PTZManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			int cnt = m_result.size() / 5;
			ptzList.numlist = cnt;
			for (int i = 0; i < cnt; ++i)
			{
				PTZManageTable_t prot_table;
				memcpy(ptzList.ptzList[i].pvsID, m_result[0 + i * 5].c_str(), API_ARRAY_LEN);
				memcpy(ptzList.ptzList[i].username, m_result[1 + i * 5].c_str(), API_ARRAY_LEN);
				memcpy(ptzList.ptzList[i].passwd, m_result[2 + i * 5].c_str(), API_ARRAY_LEN);
				memcpy(ptzList.ptzList[i].nIP, m_result[3 + i * 5].c_str(), API_ARRAY_LEN);
				ptzList.ptzList[i].nPort = boost::lexical_cast<unsigned short>(m_result[4 + i * 5]);
			}
			mutex_ctrl.unlock();
			return true;
		}

		bool PTZManageTemplate::savePTZPoint(PtzPoint_t &pointList)
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			std::string ip = (char*)pointList.nIP;
			std::string point = (char*)pointList.nPoint;
			sqlArray = "UPDATE PTZManageTable SET point = '" + point + "' WHERE IP = '" + ip + "'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: update point from  PTZManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			mutex_ctrl.unlock();
			return true;
		}

		bool PTZManageTemplate::getPTZPoint(PtzPoint_t &pointList)
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			std::string ip = (char*)pointList.nIP;
			sqlArray = "SELECT point FROM PTZManageTable WHERE  ip = '" + ip + "'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: select point from  PTZManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			memcpy(pointList.nIP, ip.c_str(), API_ARRAY_LEN);
			if (m_result.size() > 0)
			{
				memcpy(pointList.nPoint, m_result.at(0).c_str(), API_ARRAY_LEN);
			}
			mutex_ctrl.unlock();
			return true;
		}

	}
}
