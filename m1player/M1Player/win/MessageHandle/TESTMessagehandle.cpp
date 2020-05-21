#include <windows.h>
#include "TESTMessagehandle.h"

CManager::CManager()
{
	is_closed = false;
}

CManager::~CManager()
{

}

void CManager::start()
{
	CLivechannel* livechannel = new CLivechannel;
	livechannel->SetOwner(this);
	livechannel->start();
}

void CManager::handle_message(long session_id, int message_type)
{
	printf("CManager: recv message:%d, session id:%d.\n", message_type, session_id);
}

////////////////////////////////////////////////////////

CLivechannel::CLivechannel()
{
	is_closed = false;
}

CLivechannel::~CLivechannel()
{

}

void CLivechannel::start()
{
	CClient* client = new CClient;
	client->SetOwner(this);
	client->start();
	Sleep(1000);
}

void CLivechannel::handle_message(long session_id, int message_type)
{
	Notify(m_owner, GetID(), 20);

	is_closed = true;
	printf("CLivechannel: recv message:%d, session id:%d.\n", message_type, session_id);
}


/////////////////////////////////

CClient::CClient()
{

}

CClient::~CClient()
{

}

void CClient::start()
{
	Notify(m_owner, GetID(), 30);
	return;
}

void CClient::handle_message(long session_id, int message_type)
{
	printf("CClient: recv message:%d, session id:%d.\n", message_type, session_id);
}
