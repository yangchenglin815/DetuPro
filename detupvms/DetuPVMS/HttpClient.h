#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>

class HttpClient : public QObject
{
    Q_OBJECT
public:
     static HttpClient* instance();
     void getSrsStreamRequest(QString sUrl, int mode, QString pvsID, QString streamType);
private:
    explicit HttpClient(QObject *parent = 0);
private:
    static HttpClient* m_pInstance;
    QNetworkAccessManager* m_pManager;
};

#endif // HTTPCLIENT_H
