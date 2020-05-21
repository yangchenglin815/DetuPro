#include "QTSocketManage.h"
#include "socketRequest.h"

namespace dm {
	namespace server {
		QTSocketManage* QTSocketManage::m_pInstance = NULL;

		QTSocketManage* QTSocketManage::instance()
		{
			if (m_pInstance == NULL)
			{
				m_pInstance = new QTSocketManage;
			}
			return m_pInstance;
		}

		void QTSocketManage::initSocket(QString ip, quint16 port)
		{
			if (!m_socket)
			{
				m_socket = new QTcpSocket(this);
				connect(m_socket, SIGNAL(connected()), this, SLOT(slotOnConnected()));
				connect(m_socket, SIGNAL(readyRead()), this, SLOT(slotOnReadyRead()));
				connect(m_socket, SIGNAL(disconnected()), this, SLOT(slotOnDisConnected()));
			}
			m_socket->connectToHost(ip, port, QTcpSocket::ReadWrite);
		}

		void QTSocketManage::closeSocket()
		{
			if (m_socket){
				m_socket->close();
				m_socket->deleteLater();
				m_socket = NULL;
			}
		}

		void QTSocketManage::requestOnTCSVideo(const api_detu_tcs_transcode &tmpInfo)
		{
			protocol_head_t api_head;
			api_detu_tcs_transcode_t api_detu;

			api_detu = tmpInfo;
			api_head.nCmd = CMD_DETU_TCS_TRANSCODE;
			api_head.nDataLen = api_detu.get_size();
			api_head.nResult = 0;
			api_head.nStreamId = 1;


			Log::Info("current pushFlow url is : %s", tmpInfo.szRtmpURL);
			netbuffer netbuf;
			packageData(netbuf, api_head.get_size() + api_detu.get_size());
			api_head.write(&netbuf);
			api_detu.write(&netbuf);

			if (m_socket){
				m_socket->write(netbuf.buffer, netbuf.buffer_len);
				m_socket->waitForBytesWritten();
				m_socket->flush();
			}
		}

		void QTSocketManage::requestOnCloseVideo(QString deviceId)
		{
			protocol_head_t api_head;
			api_detu_tcs_transcode_res api_detu;

			api_head.nCmd = CMD_DETU_TCS_TRANSCODE_STOP;
			api_head.nDataLen = api_detu.get_size();
			api_head.nResult = 0;
			api_head.nStreamId = 1;

			memcpy(api_detu.szDeviceId, deviceId.toStdString().c_str(), API_ARRAY_LEN);

			netbuffer netbuf;
			packageData(netbuf, api_head.get_size() + api_detu.get_size());
			api_head.write(&netbuf);
			api_detu.write(&netbuf);

			if (m_socket){
				int ret = m_socket->write(netbuf.buffer, netbuf.buffer_len);
				m_socket->waitForBytesWritten();
				m_socket->flush();
			}
		}

		QTSocketManage::QTSocketManage(QObject *parent)
			: QObject(parent)
			, m_socket(NULL)
			, m_incoming_buf_size_(2000000)
		{
			m_incoming_buf.buffer = new char[m_incoming_buf_size_];
			m_incoming_buf.buffer_len = m_incoming_buf_size_;
		}

		QTSocketManage::~QTSocketManage()
		{

		}

		void QTSocketManage::transformData(QByteArray result, int len)
		{
			m_incoming_buf.buffer_offset = 0;
			memset(m_incoming_buf.buffer, 0, m_incoming_buf_size_);
			m_incoming_buf.buffer_len = len;
			memcpy(m_incoming_buf.buffer, result.data(), m_incoming_buf.buffer_len);
		}

		void QTSocketManage::packageData(netbuffer_t &buf, int len)
		{
			buf.buffer_len = len;
			buf.buffer = (char*)malloc(buf.buffer_len);
			buf.buffer_offset = 0;
			memset(buf.buffer, 0, buf.buffer_len* sizeof(char));
		}

		void QTSocketManage::handleNetWorkRequest(short result, short cmd)
		{
			switch (result)
			{
			case RESULT_SUCCESS:
				if (cmd == CMD_DETU_TCS_TRANSCODE_RES)
				{
					emit sigOnPushFlowSuccess();
				}
				else if (cmd == CMD_DETU_TCS_TRANSCODE_STOP_RES)
				{
					emit sigOnCloseTranscode();
				}
				break;
			case RESULT_FAILED:
				if (cmd == CMD_DETU_TCS_TRANSCODE_RES)
				{
					emit sigOnPushFlowFailed();
				}
				else if (cmd == CMD_DETU_TCS_TRANSCODE_STOP_RES)
				{
					emit sigOnCloseTranscode();
				}
				break;
			case RESULT_TRANSCODE_EXIST:
				break;
			case RESULT_OCCIPIED:
				break;
			default:
				break;
			}
		}

		void QTSocketManage::slotOnConnected()
		{
			Log::Info("TCS SOCKET CONNECTED!");
		}

		void QTSocketManage::slotOnReadyRead()
		{
			QByteArray rec = m_socket->read(sizeof(protocol_head_t));

			protocol_head_t api_head;
			transformData(rec, api_head.get_size());
			api_head.read(&m_incoming_buf);

			if (api_head.nStartFlags == 0xAF && api_head.nEndFlags == 0xFA)
			{
				rec.clear();
				rec.resize(0);
				rec = m_socket->read(api_head.nDataLen);
				switch (api_head.nCmd)
				{
				case CMD_DETU_TCS_TRANSCODE_RES:
					handleNetWorkRequest(api_head.nResult, CMD_DETU_TCS_TRANSCODE_RES);
					break;
				case CMD_DETU_TCS_TRANSCODE_STOP_RES:
					handleNetWorkRequest(api_head.nResult, CMD_DETU_TCS_TRANSCODE_STOP_RES);
					break;
				default:
					break;
				}
			}
		}

		void QTSocketManage::slotOnDisConnected()
		{
			Log::Info("TCS SOCKET DISCONNECTED!");
		}
	}
}