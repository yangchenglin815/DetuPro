#ifndef _CONFIG_TEST_H_
#define _CONFIG_TEST_H_

#include <string>

class CTESTConfig
{
public:
	CTESTConfig();
	~CTESTConfig();

public:
	int LoadConfig(std::string path);
	int Load(std::string path);

private:
	int m_expires;
	int m_server_id;
	int m_duration;
	int m_listen_port;
	int m_max_connections;

	std::string m_log_level;
	std::string m_bls_address;
};

#endif
