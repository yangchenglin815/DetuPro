#include "ConfigTEST.h"
#include "Configure.h"
#include "Config.h"
#include "Error.h"
#include "logging.h"


CTESTConfig::CTESTConfig()
{
	m_expires = 0;
	m_server_id = 0;
	m_duration = 0;
	m_listen_port = 0;
	m_max_connections = 0;
}

CTESTConfig::~CTESTConfig()
{

}

int CTESTConfig::LoadConfig(std::string path)
{
	CTcsConfig* tcs_config = new CTcsConfig;
	tcs_config->ParseOptions(path);
	int ret = tcs_config->CheckConfig();
	if (ret != ERROR_SUCCESS) {
		Log::Error("load config error.");
	}

	m_max_connections = tcs_config->GetMaxConnections();
	m_listen_port = tcs_config->GetListenPort();
	m_expires = tcs_config->GetExpires();
	m_server_id = tcs_config->GetServerId();
	m_bls_address = tcs_config->GetBLS();
	m_log_level = tcs_config->GetLogLevel();
	m_duration = tcs_config->GetLogDuration();

	Log::Info("listen port:%d, expires:%d, server id:%d, max connection:%d, log duration:%d, bls address:%s, log level:%s",
		m_listen_port, m_expires, m_server_id, m_max_connections, m_duration, m_bls_address.c_str(), m_log_level.c_str());

	return 0;
}

int CTESTConfig::Load(std::string path)
{
	CTcsConfig* tcs_config = new CTcsConfig;
	tcs_config->ParseOptions(path);
	return 0;
}

////////////////////////////////////////////////////////////////

#ifdef TCS_TEST_CONFIG

int main()
{
	std::string url = "../../bin/win32/Test.log";
	Log::Initialise(url);
	Log::SetThreshold(Log::LOG_TYPE_DEBUG);

	std::string path = "../../bin/win32/tcs.conf";
	CTESTConfig* conf_test = new CTESTConfig;
	conf_test->LoadConfig(path);
	//conf_test->Load(path);
	delete conf_test;

	system("pause");
	return 0;
}

#endif
