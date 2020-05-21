#include "HttpClient.h"
#include "HttpGetSrsStreamOrder.h"

HttpClient* HttpClient::m_pInstance = NULL;

HttpClient *HttpClient::instance()
{
    if (m_pInstance == NULL)
    {
        m_pInstance = new HttpClient;
    }
    return m_pInstance;
}

void HttpClient::getSrsStreamRequest(QString sUrl, int mode, QString pvsID, QString streamType)
{
	HttpGetSrsStreamOrder *p = new HttpGetSrsStreamOrder(sUrl, mode, pvsID, streamType);
     p->setNetManager(m_pManager);
     p->postRequest();
}

HttpClient::HttpClient(QObject *parent) : QObject(parent)
      , m_pManager(NULL)
{
    m_pManager = new QNetworkAccessManager();
}
