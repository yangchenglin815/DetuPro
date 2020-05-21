#include "SqliteTEST.h"
#include "Configure.h"
#include "Config.h"
#include "Error.h"
#include "logging.h"


static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	for (int i = 0; i < argc; i++){
		Log::Info("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	return 0;
}

CTESTSqlite::CTESTSqlite()
{
	m_db = NULL;
}

CTESTSqlite::~CTESTSqlite()
{

}

int CTESTSqlite::OpenDB(char* path)
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

int CTESTSqlite::Excute(char* sql)
{
	char *zErrMsg = 0;
	int rc = sqlite3_exec(m_db, sql, callback, (void*)this, &zErrMsg);
	if (rc != SQLITE_OK){
		Log::Error("SQL error: %s\n.", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		Log::Info("option successfully.\n");
	}

	return 0;
}

int CTESTSqlite::Close()
{
	if (m_db){
		sqlite3_close(m_db);
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////

#ifdef TCS_TEST_SQLITE

int main()
{
	std::string url = "../../bin/win32/Test.log";
	Log::Initialise(url);
	Log::SetThreshold(Log::LOG_TYPE_DEBUG);

	// create table
	char* sql_c = "CREATE TABLE PTS("  \
				  "NAME TEXT PRIMARY KEY NOT NULL," \
				  "CALIBRATION CHAR(4096));";

	// insert
	char* sql_i_1 = "INSERT INTO PTS (NAME,CALIBRATION) "  \
				    "VALUES ('0D2A14', 'f4_2048_3072_-485_46_2980_2980_124.991_5.98284_-173.713_194.914_0_-0.112273_0.115727_-17.941_70.6869_0_0_2048_3072_-415_38_2928_2928_36.7815_3.2481_176.863_192.422_0_-0.110477_0.0699403_-73.0553_19.7727_0_0_2048_3072_-471_69_2970_2970_-58.6942_0.811073_174.813_194.893_0_-0.171918_0.173397_53.0196_64.6597_0_0_2048_3072_-463_70_2958_2958_-144.396_-5.72697_179.843_197.473_0_-0.297646_0.381349_-9.90261_15.3308_0_0_2048_3072 ' );";

	char* sql_i_2 = "INSERT INTO PTS (NAME,CALIBRATION) "  \
					"VALUES ('0D5F4C', 'f4_768_1104_-181_17_1118_1071_60_2_0.5_199.909_0_0_-0.038049_-20.1339_18.1223_0_0_768_1104_-155_14_1098_1052_150.495_-3.64108_1.03595_196.497_0_0_-0.031709_-10.8518_5.68707_0_0_768_1104_-176_25_1114_1067_-120.957_-5.27204_-3.6941_202.126_0_0_-0.026345_-24.9443_12.4067_0_0_768_1104_-183_-1_1126_1079_-30.8474_3.37513_-6.78084_202.557_0_0_-0.057554_-18.7966_5.76274_0_0_768_1104 ' );";

	// select
	char* sql_s = "SELECT * from PTS where NAME='0D2A14'";

	// update
	char* sql_u = "UPDATE PTS set CALIBRATION = 'sdfghjkl' where NAME='0D2A14'; " \
				  "SELECT * from PTS";

	CTESTSqlite* db = new CTESTSqlite;
	db->OpenDB("pts.db");
	//db->Excute(sql_c);
	//db->Excute(sql_i_1);
	//db->Excute(sql_i_2);
	//db->Excute(sql_s);
	db->Excute(sql_u);
	db->Close();

	system("pause");
	return 0;
}

#endif
