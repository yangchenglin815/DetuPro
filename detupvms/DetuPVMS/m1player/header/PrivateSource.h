#ifndef _PRIVATE_SOURCE_H_
#define _PRIVATE_SOURCE_H_

#include <memory>
#include <thread>

class CIDataSource;

class CPrivateSource : public CIDataSource
{
public:
	CPrivateSource();
	virtual ~CPrivateSource();

public:
	virtual int  InitSource(std::string url);
	virtual int  HandShake(void);
	virtual int  StartRecv(void);
	virtual int  CloseSource(void);
	virtual void SetStreamSaveTag(bool save_tag);

private:
	bool m_is_closed;
	std::shared_ptr<std::thread>	m_net_recv_thread;
};

#endif
