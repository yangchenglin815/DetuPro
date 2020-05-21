#ifndef _SQLITE_TEST_H_
#define _SQLITE_TEST_H_

#include <string>
#include "sqlite3.h"

class CTESTSqlite
{
public:
	CTESTSqlite();
	~CTESTSqlite();

	int OpenDB(char* path);
	int Excute(char* sql);
	int Close();

private:
	sqlite3* m_db;
};

#endif
