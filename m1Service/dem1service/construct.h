#pragma once
#include "logging.hpp"

using namespace std;

const int CLIENT_VERSION = 2210;

typedef struct OnlineConnInfo
{
	string client_session;
	string pvs_session;
	int cmd_id;

	OnlineConnInfo()
	{
		client_session = "default";
		pvs_session = "default";
		cmd_id = -1;
	}

	//ÅÐ¶ÏÊÇ·ñ´æÔÚ
	bool operator ==(const OnlineConnInfo& info1)
	{
		if ((this->pvs_session != "default"&&this->pvs_session == info1.pvs_session)
			&& (this->cmd_id != -1 && this->cmd_id == info1.cmd_id))
		{
			return true;
		}

		else
		{
			return false;
		}
	}

}OnlineConnInfo_t;
