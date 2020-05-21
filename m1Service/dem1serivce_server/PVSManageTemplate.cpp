#include "PVSManageTemplate.h"

#include <stdexcept>
#include <exception>
#include <stdio.h>

namespace dem1 {
	namespace server {
		auto_ptr<PVSManageTemplate> PVSManageTemplate::auto_ptr_instance;
		PVSManageTemplate::PVSManageTemplate()
		{
			database = NULL;
		}


		PVSManageTemplate::~PVSManageTemplate()
		{

		}

		bool  PVSManageTemplate::initPVSManageTable()
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "SELECT COUNT(*) FROM sqlite_master WHERE TYPE = 'table' AND NAME = 'PVSManageTable'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: select PVSManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			if (atoi(m_result.front().c_str()) == 0)
			{
				Log::Info("dem1service:: create table : PVSManageTable");
				sqlArray = "CREATE TABLE PVSManageTable("  \
					"id  INTEGER PRIMARY KEY AUTOINCREMENT," \
					"PVSId                                 TEXT    NOT NULL," \
					"M1Id                                  TEXT," \
					"username                          TEXT," \
					"passwd                              TEXT," \
					"online                                 INT   DEFAULT 0," \
					"heartbeatInterval             INT   DEFAULT 0," \
					"sessionID                           TEXT," \
					"ptsData                              TEXT," \
					"ptsLength                          INT   DEFAULT 0," \
					"nCalibrationStatus           INT   DEFAULT 0, " \
					"nInputBandWidth             INT   DEFAULT 0," \
					"nOuntputBandWidth      INT    DEFAULT 0," \
					"nStream1Status               INT    DEFAULT 2," \
					"nStream2Status               INT    DEFAULT 2," \
					"sName                               TEXT," \
					"upDown                            INTEGER DEFAULT 0," \
					"pushFlowNum                 INT    DEFAULT 0," \
					"optPtsData                       TEXT," \
					"optPtsLength                   INT   DEFAULT 0);";
				rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
				if (rc != SQLITE_OK)
				{
					Log::Error("dem1service:: create PVSManageTable failed : %s", errMsg);
					sqlite3_free(errMsg);
					mutex_ctrl.unlock();
					return false;
				}
			}
			else
			{
				sqlArray = "UPDATE PVSManageTable SET online = 0";
				rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
				if (rc != SQLITE_OK)
				{
					Log::Error("dem1service:: update  PVSManageTable failed : %s", errMsg);
					sqlite3_free(errMsg);
					mutex_ctrl.unlock();
					return false;
				}
			}
			mutex_ctrl.unlock();
			return true;
		}

		bool PVSManageTemplate::updatePVSManageTable(PVSManageTable_t prot_table)
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string pvsId = (char*)prot_table.pvsID;
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "SELECT COUNT(*) FROM PVSManageTable WHERE PVSId = '" + pvsId + "'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: select PVSManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			if (atoi(m_result.front().c_str()) == 0){

				sqlArray = "INSERT INTO PVSManageTable (PVSId, nCalibrationStatus, nInputBandWidth, nOuntputBandWidth, nStream1Status, nStream2Status) " \
					"VALUES ('"
					+ pvsId + "','"
					+ boost::lexical_cast<std::string>(prot_table.nCalibrationStatus) + "','"
					+ boost::lexical_cast<std::string>(prot_table.nInputBandWidth) + "','"
					+ boost::lexical_cast<std::string>(prot_table.nOuntputBandWidth) + "','"
					+ boost::lexical_cast<std::string>(prot_table.nStream1Status) + "','"
					+ boost::lexical_cast<std::string>(prot_table.nStream2Status)
					+ "')";
				rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
				if (rc != SQLITE_OK)
				{
					Log::Error("dem1service:: insert PVSManageTable failed : %s", errMsg);
					sqlite3_free(errMsg);
					mutex_ctrl.unlock();
					return false;
				}
			}
			else
			{
				sqlArray = "UPDATE PVSManageTable SET nInputBandWidth =  '" + boost::lexical_cast<std::string>(prot_table.nInputBandWidth)
					+ "', nCalibrationStatus = '" + boost::lexical_cast<std::string>(prot_table.nCalibrationStatus)
					+ "', nOuntputBandWidth = '" + boost::lexical_cast<std::string>(prot_table.nOuntputBandWidth)
					+ "', nStream1Status = '" + boost::lexical_cast<std::string>(prot_table.nStream1Status)
					+ "', nStream2Status = '" + boost::lexical_cast<std::string>(prot_table.nStream2Status)
					+ "' WHERE PVSId = '" + pvsId + "'";
				rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
				if (rc != SQLITE_OK)
				{
					Log::Error("dem1service:: update PVSManageTable failed : %s", errMsg);
					sqlite3_free(errMsg);
					mutex_ctrl.unlock();
					return false;
				}
			}
			mutex_ctrl.unlock();
			return true;
		}

		bool PVSManageTemplate::getBandWidthFromTable(std::string pvsId, PVSManageTable_t &tableData)
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "SELECT nCalibrationStatus, nInputBandWidth, nOuntputBandWidth, nStream1Status, nStream2Status FROM PVSManageTable WHERE PVSID = '"
				+ pvsId + "'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: select PVSManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			memcpy(tableData.pvsID, pvsId.c_str(), API_ARRAY_LEN);
			if (m_result.size() == 5)
			{
				tableData.nCalibrationStatus = atoi(m_result.at(0).c_str());
				tableData.nInputBandWidth = atoi(m_result.at(1).c_str());
				tableData.nOuntputBandWidth = atoi(m_result.at(2).c_str());
				tableData.nStream1Status = atoi(m_result.at(3).c_str());
				tableData.nStream2Status = atoi(m_result.at(4).c_str());
			}
			mutex_ctrl.unlock();
			return true;
		}

		bool PVSManageTemplate:: deleteDeviceFromTable(std::string sessionId)
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "DELETE FROM PVSManageTable WHERE sessionID = '" + sessionId + "'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: delete PVSManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			mutex_ctrl.unlock();
			return true;
		}

		bool PVSManageTemplate::savePVSRegisterInfo(api_register_t prot_table, std::string sessionid)
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			std::string pvsId = (char*)prot_table.szDeviceId;
			std::string username = (char*)prot_table.szUserName;
			std::string passwd = (char*)prot_table.szPassWord;
			sqlArray = "SELECT COUNT(*) FROM PVSManageTable WHERE PVSId = '" + pvsId + "'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: select PVSManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			if (atoi(m_result.front().c_str()) == 0)
			{
				sqlArray = "INSERT INTO PVSManageTable (PVSId, username, passwd, online, heartbeatInterval, sessionID) VALUES ('" \
					+ pvsId + "','" + username + "','" + passwd + "', 1, '" + boost::lexical_cast<std::string>(prot_table.nHeartbeatInterval) + "','" + sessionid + "')";
				rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
				if (rc != SQLITE_OK)
				{
					Log::Error("dem1service:: insert PVSManageTable register info failed : %s", errMsg);
					sqlite3_free(errMsg);
					mutex_ctrl.unlock();
					return false;
				}
			}
			else
			{
				sqlArray = "UPDATE PVSManageTable SET username = '" + username + "', passwd = '" + passwd + "', online = 1, heartbeatInterval = '" \
					+ boost::lexical_cast<std::string>(prot_table.nHeartbeatInterval) + "', sessionID ='" \
					+ sessionid + "' WHERE PVSId = '" + pvsId + "'";
				rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
				if (rc != SQLITE_OK)
				{
					Log::Error("dem1service:: update PVSManageTable register info failed : %s", errMsg);
					sqlite3_free(errMsg);
					mutex_ctrl.unlock();
					return false;
				}
			}
			mutex_ctrl.unlock();
			return true;
		}

		bool PVSManageTemplate::saveCailbrationInfo(api_detu_client_register_res_t prot_table, std::string sessionId)
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			std::string M1ID = (char*)prot_table.m1DeviceId;
			std::string ptsData = (char*)prot_table.pts.pts_data;
			sqlArray = "UPDATE PVSManageTable SET M1Id = '" + M1ID + "', ptsData = '" + ptsData + "', ptsLength = '" \
				+ boost::lexical_cast<std::string>(prot_table.pts.nPtsLen) + "' WHERE sessionID = '" + sessionId + "'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: update PVSManageTable cailbration  info failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			mutex_ctrl.unlock();
			return true;
		}

		bool PVSManageTemplate::saveOptmizeCailbrationInfo(api_detu_client_optmize prot_table)
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			std::string pvsID = (char*)prot_table.szDeviceId;
			std::string ptsData = (char*)prot_table.optmize_pts.pts_data;
			sqlArray = "UPDATE PVSManageTable SET optPtsData = '" + ptsData + "', optPtsLength = '" + boost::lexical_cast<std::string>(prot_table.optmize_pts.nPtsLen) + "' WHERE PVSId = '" + pvsID + "'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: update PVSManageTable optmize cailbration  info failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			mutex_ctrl.unlock();
			return true;
		}

		bool PVSManageTemplate::saveDeviceInfo(api_detu_client_register_res_t prot_table)
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			std::string sName = (char*)prot_table.szName;
			std::string pvsID = (char*)prot_table.szDeviceId;
			sqlArray = "UPDATE PVSManageTable SET sName = '" + sName + "', upDown = '" + boost::lexical_cast<std::string>(prot_table.szUpDown) \
				+ "' WHERE PVSId = '" + pvsID + "'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: update PVSManageTable device  info failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			mutex_ctrl.unlock();
			return true;
		}

		bool PVSManageTemplate::getPVSRegisterInfo(std::vector<api_detu_client_register_res_t> &prot_table)
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "SELECT PVSId, online, sName, M1Id, upDown, ptsLength, ptsData FROM PVSManageTable";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: select PVSManageTable register  info failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			int size = m_result.size();
			if (size > 0 && size % 7 == 0)
			{
				for (int i = 0; i < size / 7; ++i)
				{
					api_detu_client_register_res_t prot;
					memcpy(prot.szDeviceId, m_result.at(0 + i * 7).c_str(), API_ARRAY_LEN);
					prot.online = atoi(m_result.at(1 + i * 7).c_str());
					memcpy(prot.szName, m_result.at(2 + i * 7).c_str(), API_ARRAY_LEN);
					memcpy(prot.m1DeviceId, m_result.at(3 + i * 7).c_str(), API_ARRAY_LEN);
					prot.szUpDown = atoi(m_result.at(4 + i * 7).c_str());
					prot.pts.nPtsLen = atoi(m_result.at(5 + i * 7).c_str());
					memcpy(prot.pts.pts_data, m_result.at(6 + i * 7).c_str(), prot.pts.nPtsLen);
					prot_table.push_back(prot);
				}
			}
			mutex_ctrl.unlock();
			return true;
		}

		bool PVSManageTemplate::updatePVSDeviceState(std::string sessionId)
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "UPDATE PVSManageTable SET online = 0 WHERE sessionID = '" + sessionId + "'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: update PVSManageTable state  failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			mutex_ctrl.unlock();
			return true;
		}

		bool PVSManageTemplate::getPushFlowNum(std::string deviceID, int &num)
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "SELECT pushFlowNum FROM PVSManageTable WHERE PVSId = '" + deviceID + "'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: select PVSManageTable  failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}

			if (m_result.size() > 0)
			{
				num = atoi(m_result[0].c_str());
			}
			else
			{
				num = 0;
			}
			mutex_ctrl.unlock();
			return true;
		}

		bool PVSManageTemplate::updatePushFlowNum(std::string deviceID, int num)
		{
			mutex_ctrl.lock();
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "UPDATE PVSManageTable SET pushFlowNum = '" + boost::lexical_cast<std::string>(num) + "' WHERE PVSId = '" + deviceID + "'";
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: update PVSManageTable  failed : %s", errMsg);
				sqlite3_free(errMsg);
				mutex_ctrl.unlock();
				return false;
			}
			mutex_ctrl.unlock();
			return true;
		}

		PVSManageTemplate& PVSManageTemplate::GetInstance(void)
		{
			if (auto_ptr_instance.get() == 0) {
				auto_ptr_instance.reset(new PVSManageTemplate());
			}
			return *(auto_ptr_instance.get());
		}

		int PVSManageTemplate::callback(void *NotUsed, int argc, char **argv, char **azColName)
		{
			int i;
			//PVSManage.m_result.clear();
			for (i = 0; i < argc; i++){
				//Log::Info("dem1service:: %s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
				if (argv[i] != NULL)
				{
					PVSManage.m_result.push_back(std::string(argv[i]));
				}
				else
				{
					PVSManage.m_result.push_back("");
				}
			}
			return 0;
		}

		void PVSManageTemplate::initDatabase(sqlite3 * m_database)
		{
			if (database == NULL)
			{
				database = m_database;
			}

			if (!initPVSManageTable())
			{
				Log::Debug("dem1service:: init PVSManage failed!");
			}
		}
	}
}
