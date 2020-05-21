#include "Platform.h"
#include "logging.h"
#include "TcsSession.h"
#include "TcsPanoplayer.h"
#include "Config.h"
#include "KillExe.h"

#ifdef WIN32
#include <windows.h>
#include <conio.h>
#include "ExceptionHandler.h"
#else
#include <unistd.h>
#endif

KillExe kill_exe_;

Log::Type string_to_log_level(std::string level)
{
	if (level == "debug"){
		return Log::LOG_TYPE_DEBUG;
	}else if(level == "warn"){
		return Log::LOG_TYPE_WARN;
	}else if (level == "error"){
		return Log::LOG_TYPE_ERROR;
	}else{
		return Log::LOG_TYPE_INFO;
	}
}

int main()
{
	kill_exe_.KillProcess(_T("dem1serivce_server.exe"));
	Sleep(500);

	std::string conf = "tcs.conf";
	CTcsConfig* config = new CTcsConfig;
	config->ParseOptions(conf);
	int ret = config->CheckConfig();
	if (ret != ERROR_SUCCESS) {
		printf("load config error, check your config file.");
		system("pause");
		return -1;
	}
	std::string path  = config->GetLogPath();
	std::string level = config->GetLogLevel();
	std::string dir = path.substr(0, path.find_last_of("/"));
	_mkdir(dir.c_str());

#ifdef WIN32
	GEH.StartMonitor("TCS");
	GEH.PreventOtherExceptionHandler();
#endif

	Log::Initialise(path);
	Log::SetThreshold(string_to_log_level(level));

	CTcsPanoPlayer::GetInstance().SetMaxChannels(config->GetMaxConnections());
	CTcsPanoPlayer::GetInstance().CreatSurface();

	CTcsSession* session = new CTcsSession;
	session->SetConfig(config);
	ret = session->Start();
	if (ret != ERROR_SUCCESS) {
		delete session;
		delete config;
		Log::Error("start tcs server error, press to restart!");
		//return -1;
		scanf("/n");
		return -1;
	}

#ifdef WIN32
	timeBeginPeriod(1);
#endif

	while (true) {
		char input = ' ';
		scanf("%c", &input);

		if (input == 'Q' || input == 'q') {
			break;
		} else if (input == 'D' || input == 'd'){
#ifdef WIN32
			GEH.DoMiniDump(NULL);
#endif
		}

#ifdef WIN32
		Sleep(2000);
#else
		sleep(2);
#endif
	}

	if (session) {
		session->Close();
		delete session;
	}
	if (config){
		delete config;
		config = NULL;
	}

#ifdef WIN32
	timeEndPeriod(1);
#endif

	Log::Info("TCS exit now.");
	return 0;
}
