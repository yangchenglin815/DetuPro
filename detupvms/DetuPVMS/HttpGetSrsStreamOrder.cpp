#include "HttpGetSrsStreamOrder.h"
#include "HttpSignal.h"
#include "DetuPVMSIni.h"
#include "logging.hpp"
#include "constStruct.h"

HttpGetSrsStreamOrder::HttpGetSrsStreamOrder(QString sUrl, int mode, QString pvsID, QString streamType)
{
	page_mode = mode;
	m_curr_pvsID = pvsID;
	m_curr_streamType = streamType;
    setReqUrlAddress(sUrl);
}

void HttpGetSrsStreamOrder::processResponse(QString strResult)
{
	Log::Info("http request return result : %s", strResult.toLocal8Bit().data());
    QJsonParseError hettp_error_;
    QByteArray http_array_ = strResult.toLocal8Bit();
	QJsonDocument document = QJsonDocument::fromJson(http_array_, &hettp_error_);
	if (hettp_error_.error == QJsonParseError::NoError){
            if(document.isObject()){
                QJsonObject object = document.object();
                   if(object.contains("code")){
                           QJsonValue code_value = object.take("code");
                           if(code_value.toInt() == 0){
                                 if(object.contains("streams")){
                                        QJsonValue array_value = object.take("streams");	
										dealArrayMode(array_value);		
                                 }
                           }
                           else{
                               //返回错误代码，网络异常
							   switch (page_mode)
							   {
							   case PREVIEW:
								   HttpSignal::instance()->sigOnNetWorkError(1);
								   break;
							   case REPLAY:
								   HttpSignal::instance()->sigOnReplayNetWorkError(1);
								   break;
							   case MAP_PLAY:
								   HttpSignal::instance()->sigOnMapNetWorkError(1);
								   break;
							   case MAP_REPLAY:
								   HttpSignal::instance()->sigOnMapBackNetWorkError(1);
								   break;
							   }               
                           }
                   }
            }
    }
	this->deleteLater();
}

void HttpGetSrsStreamOrder::processError()
{
    //网络请求失败
	switch (page_mode)
	{
	case PREVIEW:
		HttpSignal::instance()->sigOnNetWorkError(0);
		break;
	case REPLAY:
		HttpSignal::instance()->sigOnReplayNetWorkError(0);
		break;
	case MAP_PLAY:
		HttpSignal::instance()->sigOnMapNetWorkError(0);
		break;
	case MAP_REPLAY:
		HttpSignal::instance()->sigOnMapBackNetWorkError(0);
		break;
	}
	this->deleteLater();
}

void HttpGetSrsStreamOrder::dealArrayMode(QJsonValue array_value)
{
	if (array_value.isArray()){
		QJsonArray array = array_value.toArray();
		//仅有一条流数据，首次请求流，直接保存流信息
		if (array.size() == 0)
		{
			Log::Info("network request array is null");
			//返回错误代码，网络异常
			switch (page_mode)
			{
			case PREVIEW:
				HttpSignal::instance()->sigOnRequestNetWork();
				break;
			case REPLAY:
				HttpSignal::instance()->sigOnReplayRequestNetWork();
				break;
			case MAP_PLAY:
				HttpSignal::instance()->sigOnMapRequestNetWork();
				break;
			case MAP_REPLAY:
				HttpSignal::instance()->sigOnMapBackRequestNetWork();
				break;
			}
			return;
		}
		else
		{
			int count = 0;
			int cnt = 0;
			for (int i = 0; i < array.size(); ++i)
			{
				QJsonObject object = array.at(i).toObject();
				if (object.take("app").toString() == m_curr_pvsID && object.take("name").toString() == m_curr_streamType)
				{
					m_curr_id = object.take("id").toInt();
					QJsonValue publish_value = object.take("publish");
					QJsonObject publish_object = publish_value.toObject();
					m_curr_state = publish_object.take("active").toBool();
					if (m_curr_state)
					{
						cnt++;
					}
					count++;
				}
			}
			Log::Info("current http response count is %d", count);
			if (count)
			{
				if (cnt)
				{
					m_curr_state = true;
				}
				switch (page_mode)
				{
				case PREVIEW:
					HttpSignal::instance()->sigOnGetSrsInfo(m_curr_id, m_curr_state);
					break;
				case REPLAY:
					HttpSignal::instance()->sigOnReplayGetSrsInfo(m_curr_id, m_curr_state);
					break;
				case MAP_PLAY:
					HttpSignal::instance()->sigOnMapGetSrsInfo(m_curr_id, m_curr_state);
					break;
				case MAP_REPLAY:
					HttpSignal::instance()->sigOnMapBackGetSrsInfo(m_curr_id, m_curr_state);
					break;
				}
			}
			else
			{
					//
				Log::Info("not find the pvsID %s for srs stream %s!", m_curr_pvsID.toLocal8Bit().data(), m_curr_streamType.toLocal8Bit().data());
				switch (page_mode)
				{
				case PREVIEW:
					HttpSignal::instance()->sigOnPVSIDError();
					break;
				case REPLAY:
					HttpSignal::instance()->sigOnReplayPVSIDError();
					break;
				case MAP_PLAY:
					HttpSignal::instance()->sigOnMapPVSIDError();
					break;
				case MAP_REPLAY:
					HttpSignal::instance()->sigOnMapBackPVSIDError();
					break;
				}
			}
		}
	}
}