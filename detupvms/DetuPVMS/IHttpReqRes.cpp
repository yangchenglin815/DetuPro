#include "IHttpReqRes.h"
#include "logging.hpp"
#include <QDebug> // 测试用

IHttpReqRes::IHttpReqRes(QObject *parent)
    : QObject(parent)
    , m_nReconnectTimes(0)
    , m_nOverTimeLen(10)
    , m_bOverTime(false)
{
    initConnect();
}

IHttpReqRes::~IHttpReqRes()
{

}

void IHttpReqRes::setNetManager(QNetworkAccessManager* pManager)
{
    pManager->setNetworkAccessible(QNetworkAccessManager::Accessible);
    m_pManager = pManager;
}

void IHttpReqRes::setReqParams(QByteArray byArr)
{
    byArr.replace("+","%2B");
    byArr.replace("#", "%23");
    m_reqParams = byArr;
}

void IHttpReqRes::postRequest()
{
    QNetworkRequest request;
   // request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");             //post调用

    request.setUrl(QUrl(m_sUrlAddress));
	//get获取
    m_pReply = m_pManager->get(request);
	//post获取
//	m_pReply = m_pManager->post(request, m_reqParams);
    connect(m_pReply, SIGNAL(finished()), this, SLOT(slot_ReplyFinished()));

    m_bOverTime = false;
    if (!m_overTimer.isActive())
    {
        m_overTimer.start(m_nOverTimeLen*1000);
    }
}

QString IHttpReqRes::getTestUrl()
{
    return m_sTestUrl;
}

void IHttpReqRes::setOverTimeLengh(int nOverTimeLengh)
{
    m_nOverTimeLen = nOverTimeLengh;
}

bool IHttpReqRes::isOverTime()
{
    return m_bOverTime;
}

void IHttpReqRes::setReqUrlAddress(QString urlAddress)
{
    m_sUrlAddress = urlAddress;
}

void IHttpReqRes::slot_ReplyFinished()
{
    m_bOverTime = false;
    m_overTimer.stop();

    QTextCodec *codec = QTextCodec::codecForName("utf8");

    QNetworkReply::NetworkError err = m_pReply->error();

    if (err != QNetworkReply::NoError)
    {
		Log::Info("network error : %s; errorCode : %d; errorMsgs : %s", m_sTestUrl.toLocal8Bit().data(), err, m_pReply->errorString().toLocal8Bit().data());
        processError();
    }
    else
    {
        m_nReconnectTimes = 0;
        QByteArray array = m_pReply->readAll();
        QString strResult(array);
        m_pReply->deleteLater();
        m_pReply = NULL;
        processResponse(strResult);
    }
}

void IHttpReqRes::slot_overTimeout()
{
    m_bOverTime = true;
	Log::Info("network timeout : %s", m_sTestUrl.toLocal8Bit().data());
    processError();
}

void IHttpReqRes::initConnect()
{
    connect(&m_overTimer, SIGNAL(timeout()), this, SLOT(slot_overTimeout()));
}
