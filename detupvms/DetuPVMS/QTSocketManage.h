#ifndef QTSOCKETMANAGE_H
#define QTSOCKETMANAGE_H

#include <QObject>
#include <QTcpSocket>
#include <QHostInfo>
#include <QTimer>
#include <QThread>

#include "constStruct.h"
#include "APIProtocol.h"

namespace dm {
	namespace server {
		class QTSocketManage : public QObject
		{
			Q_OBJECT
		public:
			static QTSocketManage* instance();
			void initSocket(QString ip, quint16 port);
			void closeSocket();

			void requestOnTCSVideo(const api_detu_tcs_transcode &tmpInfo);
			void requestOnCloseVideo(QString deviceId);
		private:
			explicit QTSocketManage(QObject *parent = 0);
			~QTSocketManage();
			void transformData(QByteArray result, int len);
			void packageData(netbuffer_t &buf, int len);
			void handleNetWorkRequest(short result, short cmd);
		signals:
			void sigOnPushFlowSuccess();
			void sigOnPushFlowFailed();

			void sigOnCloseTranscode();
		private slots:
			void slotOnConnected();
			void slotOnReadyRead();
			void slotOnDisConnected();
		private:
			static QTSocketManage* m_pInstance;
			QTcpSocket *m_socket;
			netbuffer_t m_incoming_buf;
			int m_incoming_buf_size_;
		};
	}
}

#endif // QTSOCKETMANAGE_H
