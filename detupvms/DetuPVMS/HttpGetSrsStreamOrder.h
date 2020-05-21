#ifndef HTTPGETSRSSTREAMORDER_H
#define HTTPGETSRSSTREAMORDER_H

#include <QObject>
#include "IHttpReqRes.h"

class HttpGetSrsStreamOrder : public IHttpReqRes
{
        Q_OBJECT
public:
	HttpGetSrsStreamOrder(QString sUrl, int mode, QString pvsID, QString streamType);
protected:
    void processResponse(QString strResult);
    void processError();
	void dealArrayMode(QJsonValue array_value);
private:
	int m_curr_id;
	int page_mode;
	bool m_curr_state;
	QString m_curr_pvsID;
	QString m_curr_streamType;
};

#endif // HTTPGETSRSSTREAMORDER_H
