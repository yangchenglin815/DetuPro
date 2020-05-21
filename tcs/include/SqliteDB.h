#ifndef _TCS_SQLITE_DB_H_
#define _TCS_SQLITE_DB_H_

#include <mutex>
#include <string>
#include "sqlite3.h"

class CSqliteDB
{
public:
	static CSqliteDB& GetInstance()
	{
		if (m_instance == NULL) {
			std::lock_guard<std::mutex> lock(m_mtx);
			if (m_instance == NULL) {
				m_instance = new CSqliteDB();
			}
			return *m_instance;
		}
		return *m_instance;
	}

public:
	int OpenDB(char* path);
	int Excute(char* sql);
	int Close();
	std::string Select(char* sql);

private:
	CSqliteDB();
	~CSqliteDB();

private:
	static CSqliteDB* m_instance;
	static std::mutex m_mtx;

private:
	sqlite3* m_db;

public:
	std::string m_calibration;
};

#endif
