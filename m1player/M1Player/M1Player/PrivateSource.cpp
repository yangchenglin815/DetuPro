#include "DataSource.h"
#include "PrivateSource.h"

CPrivateSource::CPrivateSource()
{
	m_is_closed = false;
}

CPrivateSource::~CPrivateSource()
{

}

int CPrivateSource::InitSource(std::string url)
{
	return 0;
}

int CPrivateSource::HandShake(void)
{
	return 0;
}

int CPrivateSource::StartRecv(void)
{
	return 0;
}

int CPrivateSource::CloseSource(void)
{
	return 0;
}

void CPrivateSource::SetStreamSaveTag(bool save_tag)
{
	return;
}
