#include "IotDataManagerTemplate.h"

namespace dem1 {
	namespace server {
		auto_ptr<IotDataManagerTemplate> IotDataManagerTemplate::auto_ptr_instance;
		
		dem1::server::IotDataManagerTemplate::IotDataManagerTemplate()
		{
			database = NULL;
		}

		dem1::server::IotDataManagerTemplate::~IotDataManagerTemplate(void)
		{

		}

		dem1::server::IotDataManagerTemplate& IotDataManagerTemplate::GetInstance(void)
		{
			if (auto_ptr_instance.get() == 0) {
				auto_ptr_instance.reset(new IotDataManagerTemplate());
			}
			return *(auto_ptr_instance.get());
		}

		int IotDataManagerTemplate::callback(void *NotUsed, int argc, char **argv, char **azColName)
		{
			int i;
			for (i = 0; i < argc; i++){
				if (argv[i] != NULL)
				{
					IotDataManage.m_result.push_back(std::string(argv[i]));
				}
				else
				{
					IotDataManage.m_result.push_back("");
				}
			}
			return 0;
		}

		void IotDataManagerTemplate::initDatabase(sqlite3 * m_database)
		{
			if (database == NULL)
			{
				database = m_database;
			}

			if (!initSessionManageTable())
			{
				Log::Debug("dem1service:: init IOTManageTable failed!");
			}
		}

		bool IotDataManagerTemplate::initSessionManageTable()
		{
			boost::lock_guard<boost::mutex> lock(mutex_ctrl);
			m_result.clear();
			std::string sqlArray;
			int rc;
			char *errMsg;
			sqlArray = "SELECT COUNT(*) FROM sqlite_master WHERE TYPE = 'table' AND NAME = 'IOTManageTable'";

			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Error("dem1service:: select IOTManageTable failed : %s", errMsg);
				sqlite3_free(errMsg);
				return false;
			}
			if (atoi(m_result.front().c_str()) == 0)
			{
				Log::Info("dem1service:: create table : IOTManageTable");
				sqlArray = "CREATE TABLE IOTManageTable("  \
					"ID                 INT      NOT NULL," \
					"NAME           TEXT    NOT NULL," \
					"AGE            INT     ," \
					"ADDRESS        CHAR(50)," \
					"SALARY         REAL );";
				rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
				if (rc != SQLITE_OK)
				{
					Log::Error("dem1service:: create IOTManageTable failed : %s", errMsg);
					sqlite3_free(errMsg);
					return false;
				}

					/* Create SQL statement */
			sqlArray = "INSERT INTO IOTManageTable (ID,NAME,AGE,ADDRESS,SALARY) "  \
				"VALUES (1, 'Zhao', 32, 'BeiJing', 10000.00 ); " \
				"INSERT INTO IOTManageTable (ID,NAME,AGE,ADDRESS,SALARY) "  \
				"VALUES (2, 'Qian', 25, 'ShangHai', 20000.00 ); "     \
				"INSERT INTO IOTManageTable (ID,NAME,AGE,ADDRESS,SALARY)" \
				"VALUES (3, 'Sun', 23, 'GuangZhou', 20000.00 );" \
				"INSERT INTO IOTManageTable (ID,NAME,AGE,ADDRESS,SALARY)" \
				"VALUES (4, 'Li', 25, 'WuHan', 9000.00 );";

			/* Execute SQL statement */
			rc = sqlite3_exec(database, sqlArray.c_str(), callback, 0, &errMsg);
			if (rc != SQLITE_OK)
			{
				Log::Debug("dem1service:: IOTManageTable SQL error: %s", errMsg);
				sqlite3_free(errMsg);
			}
			}

		

			return true;
		}

	}
}