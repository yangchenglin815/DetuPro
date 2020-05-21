#include "SPYManageTemplate.h"

#include <stdexcept>
#include <exception>
#include <stdio.h>

namespace dem1 {
	namespace server {
		auto_ptr<SPYManageTemplate> SPYManageTemplate::auto_ptr_instance;
		SPYManageTemplate::SPYManageTemplate()
		{
			database = NULL;
		}


		SPYManageTemplate::~SPYManageTemplate()
		{

		}

		SPYManageTemplate& SPYManageTemplate::GetInstance(void)
		{
			if (auto_ptr_instance.get() == 0) {
				auto_ptr_instance.reset(new SPYManageTemplate());
			}
			return *(auto_ptr_instance.get());
		}

		int SPYManageTemplate::callback(void *NotUsed, int argc, char **argv, char **azColName)
		{
			int i;
			for (i = 0; i < argc; i++){
				if (argv[i] != NULL)
				{
					SPYManage.m_result.push_back(std::string(argv[i]));
				}
				else
				{
					SPYManage.m_result.push_back("");
				}
			}
			return 0;
		}

		void SPYManageTemplate::initDatabase(sqlite3 * m_database)
		{
			if (database == NULL)
			{
				database = m_database;
			}

			if (!initSPYManageTable())
			{
				Log::Debug("dem1service:: init SPYManage failed!");
			}
		}

		bool SPYManageTemplate::initSPYManageTable()
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "SELECT COUNT(*) FROM sqlite_master WHERE TYPE = 'table' AND NAME = 'SPYManageTable'";
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
				Log::Info("dem1service:: create table : SPYManageTable");
				sqlArray = "CREATE TABLE SPYManageTable("  \
					"id  INTEGER PRIMARY KEY AUTOINCREMENT," \
					"PVSId                                 TEXT," \
					"nPosX                                 INT DEFAULT -1," \
					"nPosY                                 INT DEFAULT -1," \
					"username                          TEXT," \
					"passwd                              TEXT," \
					"IP                                        TEXT," \
					"port                                   TEXT);";
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

		bool SPYManageTemplate::updateSPYDeviceToTable(SPYManageTable_t prot_table)
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
			sqlArray = "SELECT COUNT(*) FROM SPYManageTable WHERE IP = '" + ip + "'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: select SPYManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			if (atoi(m_result.front().c_str()) == 0)
			{
				sqlArray = "INSERT INTO SPYManageTable (PVSID, username, passwd, IP, port, nPosX, nPosY) VALUES ('" \
					+ pvsID + "','"
					+ username + "','"
					+ passwd + "','"
					+ ip + "','"
					+ boost::lexical_cast<std::string>(prot_table.nPort) + "','"
					+ boost::lexical_cast<std::string>(prot_table.nPosX) + "','"
					+ boost::lexical_cast<std::string>(prot_table.nPosY)
					+ "')";
				rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
				if (rc != SQLITE_OK)
				{
					Log::Error("dem1service:: insert SPYManageTable failed : %s", errMsg);
					sqlite3_free(errMsg);
					mutex_ctrl.unlock();
					return false;
				}
			}
			else
			{
				sqlArray = "UPDATE SPYManageTable SET PVSID = '" + pvsID
					+ "', username = '" + username
					+ "', passwd = '" + passwd
					+ "', port = '" + boost::lexical_cast<std::string>(prot_table.nPort)
					+ "', nPosX = '" + boost::lexical_cast<std::string>(prot_table.nPosX)
					+ "', nPosY = '" + boost::lexical_cast<std::string>(prot_table.nPosY)
					+ "' WHERE IP = '" + ip + "'";
				rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
				if (rc != SQLITE_OK)
				{
					Log::Error("dem1service:: update SPYManageTable failed : %s", errMsg);
					sqlite3_free(errMsg);
					mutex_ctrl.unlock();
					return false;
				}
			}
			mutex_ctrl.unlock();
			return true;
		}

		bool SPYManageTemplate::deleteSPYDeviceToTable(std::string ip)
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "DELETE FROM SPYManageTable WHERE IP = '" + ip + "'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: delete SPYManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			mutex_ctrl.unlock();
			return true;
		}

		bool SPYManageTemplate::getSPYDeviceFromTable(SPYManageTableList_t &spyList)
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "SELECT PVSId, username, passwd, IP, port, nPosX, nPosY FROM SPYManageTable";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: select all data from  SPYManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			int cnt = m_result.size() / 7;
			spyList.numlist = cnt;
			for (int i = 0; i < cnt; ++i)
			{
				SPYManageTable_t prot_table;
				memcpy(spyList.spyList[i].pvsID, m_result[0 + i * 7].c_str(), API_ARRAY_LEN);
				memcpy(spyList.spyList[i].username, m_result[1 + i * 7].c_str(), API_ARRAY_LEN);
				memcpy(spyList.spyList[i].passwd, m_result[2 + i * 7].c_str(), API_ARRAY_LEN);
				memcpy(spyList.spyList[i].nIP, m_result[3 + i * 7].c_str(), API_ARRAY_LEN);
				spyList.spyList[i].nPort = boost::lexical_cast<unsigned short>(m_result[4 + i * 7]);
				spyList.spyList[i].nPosX = boost::lexical_cast<unsigned short>(m_result[5 + i * 7]);
				spyList.spyList[i].nPosY = boost::lexical_cast<unsigned short>(m_result[6 + i * 7]);
			}
			mutex_ctrl.unlock();
			return true;
		}
	}
}