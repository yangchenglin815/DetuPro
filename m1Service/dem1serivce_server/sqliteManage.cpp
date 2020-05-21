#include <stdexcept>
#include <exception>
#include <stdio.h>

#include "sqliteManage.h"

namespace dem1 {
	namespace server {
		auto_ptr<sqliteManage> sqliteManage::auto_ptr_instance; 
		sqliteManage::sqliteManage()
		{
			int rc;
			rc = sqlite3_open("detu.db", &database);
			if (rc)
			{
				Log::Info("dem1service:: open sqlite3 database failed : %s", sqlite3_errmsg(database));
			}
			else
			{
				Log::Info("dem1service:: open sqlite3 database success!");
			}
		}

		sqliteManage::~sqliteManage()
		{
			sqlite3_close(database);
		}

		sqliteManage& sqliteManage::GetInstance(void)
		{
			if (auto_ptr_instance.get() == 0) {
				auto_ptr_instance.reset(new sqliteManage());
			}
			return *(auto_ptr_instance.get());
		}

		void sqliteManage::initDataBase()
		{
			PanoManage.initDatabase(database);
			PVSManage.initDatabase(database);
			PTZManage.initDatabase(database);
			SPYManage.initDatabase(database);
			TCSManage.initDatabase(database);
			SessionManage.initDatabase(database);
			IotDataManage.initDatabase(database);
		}

	}
}