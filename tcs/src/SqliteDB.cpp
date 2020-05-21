#include "SqliteDB.h"
#include "logging.h"

CSqliteDB* CSqliteDB::m_instance = NULL;
std::mutex CSqliteDB::m_mtx;

static int callback(void *opaque, int argc, char **argv, char **azColName)
{
	CSqliteDB* db = (CSqliteDB*)opaque;
	for (int i = 0; i < argc; i++){
		Log::Info("%s=%s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		if (i == 1){
			db->m_calibration = argv[i];
		}
	}
	return 0;
}

CSqliteDB::CSqliteDB()
{
	m_db = NULL;
}

CSqliteDB::~CSqliteDB()
{

}

int CSqliteDB::OpenDB(char* path)
{
	int rc = sqlite3_open(path, &m_db);
	if (rc){
		Log::Error("Can't open database: %s.\n", sqlite3_errmsg(m_db));
		return -1;
	} else{
		Log::Info("Opened database successfully.\n");
	}

	return 0;
}

int CSqliteDB::Excute(char* sql)
{
	std::lock_guard<std::mutex> lock(m_mtx);

	char *zErrMsg = 0;
	int rc = sqlite3_exec(m_db, sql, NULL, (void*)this, &zErrMsg);
	if (rc != SQLITE_OK){
		Log::Error("SQL error: %s\n.", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	return 0;
}

int CSqliteDB::Close()
{
	if (m_db){
		sqlite3_close(m_db);
	}
	return 0;
}

std::string CSqliteDB::Select(char* sql)
{
	std::lock_guard<std::mutex> lock(m_mtx);

	char *zErrMsg = 0;
	int rc = sqlite3_exec(m_db, sql, callback, (void*)this, &zErrMsg);
	if (rc != SQLITE_OK){
		Log::Error("SQL error: %s\n.", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	return m_calibration;
}
