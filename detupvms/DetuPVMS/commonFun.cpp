#include "commonFun.h"
#include <QRegExp>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "logging.hpp"

unsigned int commonFun::getDateTime(QString date)
{
	QDateTime time = QDateTime::fromString(date, "yyyy-MM-dd");
	return time.toTime_t();
}

unsigned int commonFun::getDateTime(int time, QString date, int duration)
{
    QString m_datetime;
    switch(duration)
    {
    case 1:
    {
        if(time == 24)
        {
           m_datetime = QString("%1 23:59:59").arg(date);
        }
        else if(time / 10 == 0)
        {
            m_datetime = QString("%1 0%2:00:00").arg(date).arg(time);
        }
        else
        {
            m_datetime = QString("%1 %2:00:00").arg(date).arg(time);
        }
        break;
    }
    case 2:
    {
        int hour = time / 2;
        QString min = ((time % 2) ? "30" : "00");
        if(hour == 24)
        {
           m_datetime = QString("%1 23:59:59").arg(date);
        }
        else if(hour / 10 == 0)
        {
            m_datetime = QString("%1 0%2:%3:00").arg(date).arg(hour).arg(min);
        }
        else
        {
            m_datetime = QString("%1 %2:%3:00").arg(date).arg(hour).arg(min);
        }
        break;
    }
    case 3:
    {
        time *= 10;
        int hour = time / 60;
        QString min;
        if(time % 60 == 0)
        {
             min = "00";
        }
        else
        {
            min = QString::number(time % 60);
        }
        if(hour == 24)
        {
           m_datetime = QString("%1 23:59:59").arg(date);
        }
        else if(hour / 10 == 0)
        {
            m_datetime = QString("%1 0%2:%3:00").arg(date).arg(hour).arg(min);
        }
        else
        {
            m_datetime = QString("%1 %2:%3:00").arg(date).arg(hour).arg(min);
        }
        break;
    }
    case 4:
    {
        int hour = time / 60;
        QString min;
        if(time % 60 == 0)
        {
             min = "00";
        }
        else
        {
            if(time % 60 / 10 == 0)
            {
                 min = QString("0%1").arg(time % 60);
            }
            else
            {
                 min = QString("%1").arg(time % 60);
            }
        }
        if(hour == 24)
        {
           m_datetime = QString("%1 23:59:59").arg(date);
        }
        else if(hour / 10 == 0)
        {
            m_datetime = QString("%1 0%2:%3:00").arg(date).arg(hour).arg(min);
        }
        else
        {
            m_datetime = QString("%1 %2:%3:00").arg(date).arg(hour).arg(min);
        }
        break;
    }
    case 5:
    {
        time *= 10;
        int hour = time / 3600;
        QString min;
        QString second;
        if(time % 3600 / 60 / 10 == 0)
        {
           min = QString("0%1").arg(time % 3600 / 60);
        }
        else
        {
            min = QString("%1").arg(time % 3600 / 60);
        }
        if(time % 3600 % 60 == 0)
        {
             second = "00";
        }
        else
        {
             second = QString::number(time % 3600 % 60);
        }
        if(hour == 24)
        {
           m_datetime = QString("%1 23:59:59").arg(date);
        }
        else if(hour / 10 == 0)
        {
            m_datetime = QString("%1 0%2:%3:%4").arg(date).arg(hour).arg(min).arg(second);
        }
        else
        {
            m_datetime = QString("%1 %2:%3:%4").arg(date).arg(hour).arg(min).arg(second);
        }
        break;
    }
    case 6:
    {
        int hour = time / 3600;
        QString min;
        QString second;
        if(time % 3600 / 60 / 10 == 0)
        {
           min = QString("0%1").arg(time % 3600 / 60);
        }
        else
        {
            min = QString("%1").arg(time % 3600 / 60);
        }
        if(time % 3600 % 60 / 10 == 0)
        {
            second = QString("0%1").arg(time % 3600 % 60);
        }
        else
        {
             second = QString("%1").arg(time % 3600 % 60);
        }
        if(hour == 24)
        {
           m_datetime = QString("%1 23:59:59").arg(date);
        }
        else if(hour / 10 == 0)
        {
            m_datetime = QString("%1 0%2:%3:%4").arg(date).arg(hour).arg(min).arg(second);
        }
        else
        {
            m_datetime = QString("%1 %2:%3:%4").arg(date).arg(hour).arg(min).arg(second);
        }
        break;
    }
    }
    QDateTime dateTime = QDateTime::fromString(m_datetime, "yyyy-MM-dd hh:mm:ss");
	return dateTime.toTime_t();
}

int commonFun::timeExchange(QString time, int param)
{
    int ret = 0;
    switch(param)
    {
    case 1:
    {
        QString hour = time.left(2);
        if (hour.left(1) == "0"){
            hour = hour.mid(1, 1);
        }
        ret = hour.toInt();
        break;
    }
    case 2:
    {
        QString hour = time.left(2);
        QString min = time.mid(3,2);
        if (hour.left(1) == "0"){
            hour = hour.mid(1, 1);
        }
        if (min.left(1) == "0"){
            min = min.mid(1, 1);
        }
        ret = (hour.toInt() * 60 + min.toInt()) / 30;
        break;
    }
    case 3:
    {
        QString hour = time.left(2);
        QString min = time.mid(3,2);
        if (hour.left(1) == "0"){
            hour = hour.mid(1, 1);
        }
        if (min.left(1) == "0"){
            min = min.mid(1, 1);
        }
        ret = (hour.toInt() * 60 + min.toInt()) / 10;
        break;
    }
    case 4:
    {
        QString hour = time.left(2);
        QString min = time.mid(3,2);
        if (hour.left(1) == "0"){
            hour = hour.mid(1, 1);
        }
        if (min.left(1) == "0"){
            min = min.mid(1, 1);
        }
        ret = (hour.toInt() * 60 + min.toInt());
        break;
    }
    case 5:
    {
        QString hour = time.left(2);
        QString min = time.mid(3, 2);
        QString second = time.right(2);
        if (hour.left(1) == "0"){
            hour = hour.mid(1, 1);
        }
        if (min.left(1) == "0"){
            min = min.mid(1, 1);
        }
        if(second.left(1) == "0"){
            second = second.mid(1, 1);
        }
        ret = (hour.toInt() * 60 * 60 + min.toInt() * 60 + second.toInt()) / 10;
        break;
    }
    case 6:
    {
        QString hour = time.left(2);
        QString min = time.mid(3, 2);
        QString second = time.right(2);
        if (hour.left(1) == "0"){
            hour = hour.mid(1, 1);
        }
        if (min.left(1) == "0"){
            min = min.mid(1, 1);
        }
        if(second.left(1) == "0"){
            second = second.mid(1, 1);
        }
        ret = (hour.toInt() * 60 * 60 + min.toInt() * 60 + second.toInt());
        break;
    }
    }
    return ret;
}

unsigned int commonFun::getStartTime(QString date)
{
	QString s_startTime = date + " 00:00:00";
	QDateTime startTime = QDateTime::fromString(s_startTime, "yyyy-MM-dd hh:mm:ss");
	return startTime.toTime_t();
}

unsigned int commonFun::getEndTime(QString date)
{
	QString s_endTime = date + " 23:59:59";
	QDateTime endTime = QDateTime::fromString(s_endTime, "yyyy-MM-dd hh:mm:ss");
	return endTime.toTime_t();
}

QString commonFun::getCurrentShowTime(int time)
{
	int hour = time / 60;
	int min = time % 60;
	//这里做时间判断，时间不可为负，24点为最大精度
	if (hour < 0)
	{
		hour = 0;
	}
	if (min < 0){
		min = 0;
	}
	if (hour == 24)
	{
		min = 0;
	}
	QString m_time;
	if (hour / 10 == 0 && min / 10 == 0){
		m_time = QString("0%2:0%3").arg(hour).arg(min);
	}
	else if (hour / 10 == 0)
	{
		m_time = QString("0%2:%3").arg(hour).arg(min);
	}
	else if (min / 10 == 0)
	{
		m_time = QString("%2:0%3").arg(hour).arg(min);
	}
	else
	{
		m_time = QString("%2:%3").arg(hour).arg(min);
	}
    return m_time;
}

QString commonFun::getCurrentTipTime(int min)
{
     int m_hour = min / 60;
     int m_min =  min % 60;
     QString time = QString("%1:%2").arg(m_hour).arg(m_min);
     if(m_min == 0){
         time.append("0");
     }
     return time;
}

QString commonFun::getCurrentTimeBySscond(int time)
{
    QString res;
    int hour = time / 600;
    int min = time % 600 / 10;
    if(min / 10 == 0){
        res = QString("%1:0%2").arg(hour).arg(min);
    }
    else{
        res = QString("%1:%2").arg(hour).arg(min);
    }
    return res;
}

QString commonFun::getCurrentTimeByPerSscond(int time)
{
    QString res;
    for(int i = 1; i < 6; ++i)
    {
        if((time/10 - i) % 6 == 0)
        {
             res = QString("%1").arg(i);
             res.append("0s");
             return res;
        }
    }
    int hour = time / 3600;
    int min = time % 3600 / 60;
    if(min / 10 == 0){
        res = QString("%1:0%2").arg(hour).arg(min);
    }
    else{
        res = QString("%1:%2").arg(hour).arg(min);
    }
    return res;
}

int commonFun::getMinFromStr(QString time)
{
    QStringList list = time.split(":");
    if(list.size() > 0)
    {
         return (list.at(0).toInt() * 60 + list.at(1).toInt());
    }
	else
	{
		return 0;
	}
}

/**
yyyy yyyy
uv    uv
->
yyyy yyyy
uu
vv
*/
void commonFun::yuv420sp_to_yuv420p(unsigned char* y, unsigned char* uv, unsigned char* y_tmp, unsigned char* u_tmp, unsigned char* v_tmp, int width, int height)
{
	int i, j;
	int y_size = width * height;

	// y
	memcpy(y_tmp, y, y_size);

	// u
	for (j = 0, i = 0; j < y_size / 2; j += 2, i++)
	{
		u_tmp[i] = uv[j];
		v_tmp[i] = uv[j + 1];
	}
}

/**
yyyy yyyy
uu
vv
->
yyyy yyyy
uv    uv
*/
void commonFun::yuv420p_to_yuv420sp(unsigned char* yuv420p, unsigned char* yuv420sp, int width, int height)
{
	int i, j;
	int y_size = width * height;

	unsigned char* y = yuv420p;
	unsigned char* u = yuv420p + y_size;
	unsigned char* v = yuv420p + y_size * 5 / 4;

	unsigned char* y_tmp = yuv420sp;
	unsigned char* uv_tmp = yuv420sp + y_size;

	// y
	memcpy(y_tmp, y, y_size);

	// u
	for (j = 0, i = 0; j < y_size / 2; j += 2, i++)
	{
		// 此处可调整U、V的位置，变成NV12或NV21
#if 01
		uv_tmp[j] = u[i];
		uv_tmp[j + 1] = v[i];
#else
		uv_tmp[j] = v[i];
		uv_tmp[j + 1] = u[i];
#endif
	}
}

void commonFun::generateToJsonFunc(const QList<PanoMap> &panoMapList)
{
	QJsonArray mapArray;

	QList<PanoMap> panoList = panoMapList;
	for (int i = 0; i < panoList.size(); ++i)
	{
		QJsonObject pointObject;

		QJsonArray pointArray;

		for (int j = 0; j < panoList[i].panoramaList.size(); ++j){
			QJsonObject currPointObject;
			currPointObject.insert("curr_id", panoList[i].panoramaList[j].curr_id);
			currPointObject.insert("pos_x", panoList[i].panoramaList[j].pos_x);
			currPointObject.insert("pos_y", panoList[i].panoramaList[j].pos_y);
			currPointObject.insert("initial_angle", panoList[i].panoramaList[j].initial_angle);

			QJsonArray ptzArray;
			deviceInfo deviceInfo_ = panoList[i].panoramaList[j].cameraInfo;
			for (int k = 0; k <deviceInfo_.m_PtzInfoList.size(); ++k)
			{
				QJsonObject ptzObject;
				ptzObject.insert("userName", deviceInfo_.m_PtzInfoList[k].sUserName);
				ptzObject.insert("passWd", deviceInfo_.m_PtzInfoList[k].sPasswd);
				ptzObject.insert("ip", deviceInfo_.m_PtzInfoList[k].sIP);
				ptzObject.insert("port", deviceInfo_.m_PtzInfoList[k].wPort);
				ptzObject.insert("pvsId", deviceInfo_.m_PtzInfoList[k].pvsID);
				ptzObject.insert("m1Id", deviceInfo_.m_PtzInfoList[k].m1Id);
				ptzArray.append(ptzObject);
			}

			QJsonArray spyArray;
			for (int k = 0; k < deviceInfo_.m_SpyInfoList.size(); ++k)
			{
				QJsonObject spyObject;
				spyObject.insert("userName", deviceInfo_.m_SpyInfoList[k].sUserName);
				spyObject.insert("passWd", deviceInfo_.m_SpyInfoList[k].sPasswd);
				spyObject.insert("ip", deviceInfo_.m_SpyInfoList[k].sIP);
				spyObject.insert("port", deviceInfo_.m_SpyInfoList[k].wPort);
				spyObject.insert("pvsId", deviceInfo_.m_SpyInfoList[k].pvsID);
				spyObject.insert("m1Id", deviceInfo_.m_SpyInfoList[k].m1Id);
				spyObject.insert("posX", deviceInfo_.m_SpyInfoList[k].pos_x);
				spyObject.insert("posY", deviceInfo_.m_SpyInfoList[k].pos_y);
				spyArray.append(spyObject);
			}

			QJsonObject cameraObject;
			cameraObject.insert("id", panoList[i].panoramaList[j].cameraInfo.id);
			cameraObject.insert("deviceName", panoList[i].panoramaList[j].cameraInfo.name);
			cameraObject.insert("szDeviceId", panoList[i].panoramaList[j].cameraInfo.serialNo);
			cameraObject.insert("m1DeviceId", panoList[i].panoramaList[j].cameraInfo.m1DeviceId);
			cameraObject.insert("is_up_down", panoList[i].panoramaList[j].cameraInfo.is_up_down);
			cameraObject.insert("status", (int)(panoList[i].panoramaList[j].cameraInfo.status));
			cameraObject.insert("ptzNum", panoList[i].panoramaList[j].cameraInfo.m_PtzInfoList.size());
			cameraObject.insert("ptzList", QJsonValue(ptzArray));
			cameraObject.insert("spyNum", panoList[i].panoramaList[j].cameraInfo.m_SpyInfoList.size());
			cameraObject.insert("spyList", QJsonValue(spyArray));

			QJsonArray pictureArray;
			QJsonObject pictureObject;
			for (int k = 0; k < panoList[i].panoramaList[j].sceneInfo.sceneList.size(); ++k){
				pictureObject.insert("id", panoList[i].panoramaList[j].sceneInfo.sceneList[k].id);
				pictureObject.insert("pictureName", panoList[i].panoramaList[j].sceneInfo.sceneList[k].name);
				pictureObject.insert("picturePath", panoList[i].panoramaList[j].sceneInfo.sceneList[k].Path);
				pictureObject.insert("pictureData", panoList[i].panoramaList[j].sceneInfo.sceneList[k].fileData);
				pictureArray.append(pictureObject);
			}

			QJsonArray connPointArray;
			QMapIterator<int, float> it(panoList[i].panoramaList[j].sequencer_point_info_map_);
			while (it.hasNext())
			{
				it.next();
				QJsonObject connPointObject;
				connPointObject.insert("id", it.key());
				connPointObject.insert("angle", it.value());
				connPointArray.append(connPointObject);
			}

			QJsonObject sceneObject;
			sceneObject.insert("id", panoList[i].panoramaList[j].sceneInfo.id);
			sceneObject.insert("sceneName", panoList[i].panoramaList[j].sceneInfo.name);
			sceneObject.insert("scenePath", panoList[i].panoramaList[j].sceneInfo.Path);
			sceneObject.insert("sceneNum", panoList[i].panoramaList[j].sceneInfo.sceneList.size());
			sceneObject.insert("sceneGroups", QJsonValue(pictureArray));

			pointObject.insert("conn_point_num", panoList[i].panoramaList[j].sequencer_point_info_map_.count());
			pointObject.insert("conn_points", QJsonValue(connPointArray));
			pointObject.insert("curr_point", QJsonValue(currPointObject));

			pointObject.insert("onMapFlag", int(panoList[i].panoramaList[j].onMapFlag));
			pointObject.insert("map_point_type", panoList[i].panoramaList[j].map_point_type);

			pointObject.insert("deviceInfo", QJsonValue(cameraObject));
			pointObject.insert("sceneInfo", QJsonValue(sceneObject));
			pointArray.append(pointObject);
		}

		QJsonArray mapLineArray;
		for (int j = 0; j < panoList[i].mapLinesList.size(); ++j)
		{
			QJsonObject mapLineObject;
			QJsonObject startPosObject;
			QJsonObject endPosObject;
			QJsonArray areaArray;

			for (int k = 0; k < panoList[i].mapLinesList[j].pointEnterArea.size(); ++k)
			{
				QJsonObject areaPointObject;
				areaPointObject.insert("x", panoList[i].mapLinesList[j].pointEnterArea[k].x());
				areaPointObject.insert("y", panoList[i].mapLinesList[j].pointEnterArea[k].y());

				areaArray.append(areaPointObject);
			}
		
			startPosObject.insert("id", panoList[i].mapLinesList[j].previousPoint.curr_id);
			startPosObject.insert("XPos", panoList[i].mapLinesList[j].previousPoint.pos_x);
			startPosObject.insert("YPos", panoList[i].mapLinesList[j].previousPoint.pos_y);
			endPosObject.insert("id", panoList[i].mapLinesList[j].nextPoint.curr_id);
			endPosObject.insert("XPos", panoList[i].mapLinesList[j].nextPoint.pos_x);
			endPosObject.insert("YPos", panoList[i].mapLinesList[j].nextPoint.pos_y);

			mapLineObject.insert("startPos", QJsonValue(startPosObject));
			mapLineObject.insert("endPos", QJsonValue(endPosObject));
			mapLineObject.insert("pointEnterArea", QJsonValue(areaArray));
			mapLineObject.insert("pointEnterAreaNum", panoList[i].mapLinesList[j].pointEnterArea.size());
			mapLineArray.append(mapLineObject);
		}

		QJsonObject subObject;
		subObject.insert("mapName", QString("%1").arg(panoList[i].mapName));
		subObject.insert("mapPath", QString("%1").arg(panoList[i].mapPath));
		subObject.insert("mapData", QString("%1").arg(panoList[i].mapData));

		subObject.insert("mapPpointInfosNum", panoList[i].panoramaList.size());
		subObject.insert("mapPpointInfos", QJsonValue(pointArray));
		subObject.insert("mapLinesNum", panoList[i].mapLinesList.size());
		subObject.insert("mapLines", QJsonValue(mapLineArray));

		mapArray.append(subObject);
	}

	QJsonObject parentObject;
	parentObject.insert("mapNum", panoList.size());
	parentObject.insert("maps", QJsonValue(mapArray));

	QJsonDocument document;
	document.setObject(parentObject);
	QByteArray byteArray = document.toJson(QJsonDocument::Compact);

	QString file_path = QDir::homePath() + "/AppData/Local/Pano-VMS/Map/map.json";
	QFile file(file_path);
	file.remove();
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		Log::Info("write map file open failed or map file no exit!");
		return;
	}
	file.write(byteArray.data());
	file.close();
}

void commonFun::resolveFromJsonFunc(QList<PanoMap> &panoMapList)
{
	QString file_path = QDir::homePath() + "/AppData/Local/Pano-VMS/Map/map.json";
	QFile file(file_path);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		Log::Info("read map file open failed or map file no exit!");
		return;
	}
	QByteArray val = file.readAll();
	file.close();

	QJsonParseError jsonError;
	QJsonDocument doucment = QJsonDocument::fromJson(val, &jsonError);
	if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
	{ // 解析未发生错误
		if (doucment.isObject())
		{
			QJsonObject object_1 = doucment.object();

			if (object_1.contains("mapNum"))
			{
				QJsonValue value = object_1.value("mapNum");
				if (value.isDouble())
				{
					int map_num = value.toInt();
					for (int i = 0; i < map_num; ++i)
					{
						PanoMap temp;
						panoMapList.append(temp);
						panoMapList[i].mapName = object_1.value("maps").toArray().at(i).toObject().value("mapName").toString();
						panoMapList[i].mapPath = object_1.value("maps").toArray().at(i).toObject().value("mapPath").toString();
						panoMapList[i].mapData = object_1.value("maps").toArray().at(i).toObject().value("mapData").toString();

						int mapLineNum = object_1.value("maps").toArray().at(i).toObject().value("mapLinesNum").toInt();
						QJsonArray mapLineArray = object_1.value("maps").toArray().at(i).toObject().value("mapLines").toArray();
						for (int j = 0; j < mapLineNum; ++j)
						{
							VRMapPointInfo lineInfo;
							panoMapList[i].mapLinesList.append(lineInfo);
							panoMapList[i].mapLinesList[j].previousPoint.curr_id = mapLineArray[j].toObject().value("startPos").toObject().value("id").toInt();
							panoMapList[i].mapLinesList[j].previousPoint.pos_x = mapLineArray[j].toObject().value("startPos").toObject().value("XPos").toDouble();
							panoMapList[i].mapLinesList[j].previousPoint.pos_y = mapLineArray[j].toObject().value("startPos").toObject().value("YPos").toDouble();
							panoMapList[i].mapLinesList[j].nextPoint.curr_id = mapLineArray[j].toObject().value("endPos").toObject().value("id").toInt();
							panoMapList[i].mapLinesList[j].nextPoint.pos_x = mapLineArray[j].toObject().value("endPos").toObject().value("XPos").toDouble();
							panoMapList[i].mapLinesList[j].nextPoint.pos_y = mapLineArray[j].toObject().value("endPos").toObject().value("YPos").toDouble();

							int areaNum = mapLineArray[j].toObject().value("pointEnterAreaNum").toInt();
							QJsonArray lineAreaArray = mapLineArray[j].toObject().value("pointEnterArea").toArray();
							for (int k = 0; k < areaNum; ++k)
							{
								int x = lineAreaArray[k].toObject().value("x").toInt();
								int y = lineAreaArray[k].toObject().value("y").toInt();
								QPointF ponitF(x, y);
								panoMapList[i].mapLinesList[j].pointEnterArea.append(ponitF);
							}
						}

						int mapPoint_num = object_1.value("maps").toArray().at(i).toObject().value("mapPpointInfosNum").toInt();
						QJsonArray mapPointArray = object_1.value("maps").toArray().at(i).toObject().value("mapPpointInfos").toArray();
						for (int j = 0; j < mapPoint_num; ++j)
						{
							PanoMapPointInfo temp_point;
							panoMapList[i].panoramaList.append(temp_point);
							panoMapList[i].panoramaList[j].curr_id = mapPointArray[j].toObject().value("curr_point").toObject().value("curr_id").toInt();
							panoMapList[i].panoramaList[j].pos_x = mapPointArray[j].toObject().value("curr_point").toObject().value("pos_x").toDouble();
							panoMapList[i].panoramaList[j].pos_y = mapPointArray[j].toObject().value("curr_point").toObject().value("pos_y").toDouble();
							panoMapList[i].panoramaList[j].initial_angle = mapPointArray[j].toObject().value("curr_point").toObject().value("initial_angle").toDouble();

							int conn_point_num = mapPointArray[j].toObject().value("conn_point_num").toInt();
							QJsonArray cunnPointArray = mapPointArray[j].toObject().value("conn_points").toArray();
							panoMapList[i].panoramaList[j].sequencer_point_info_map_.clear();
							for (int k = 0; k < conn_point_num; ++k)
							{
								int key = cunnPointArray[k].toObject().value("id").toInt();
								float value = cunnPointArray[k].toObject().value("angle").toDouble();
								panoMapList[i].panoramaList[j].sequencer_point_info_map_.insert(key, value);
							}

							panoMapList[i].panoramaList[j].onMapFlag = mapPointArray[j].toObject().value("onMapFlag").toInt();
							panoMapList[i].panoramaList[j].map_point_type = MapPointType(mapPointArray[j].toObject().value("map_point_type").toInt());

							panoMapList[i].panoramaList[j].cameraInfo.id = mapPointArray[j].toObject().value("deviceInfo").toObject().value("id").toInt();
							panoMapList[i].panoramaList[j].cameraInfo.name = mapPointArray[j].toObject().value("deviceInfo").toObject().value("deviceName").toString();
							panoMapList[i].panoramaList[j].cameraInfo.serialNo = mapPointArray[j].toObject().value("deviceInfo").toObject().value("szDeviceId").toString();
							panoMapList[i].panoramaList[j].cameraInfo.m1DeviceId = mapPointArray[j].toObject().value("deviceInfo").toObject().value("m1DeviceId").toString();
							panoMapList[i].panoramaList[j].cameraInfo.is_up_down = mapPointArray[j].toObject().value("deviceInfo").toObject().value("is_up_down").toInt();
							panoMapList[i].panoramaList[j].cameraInfo.status = mapPointArray[j].toObject().value("deviceInfo").toObject().value("status").toInt();

							int ptzNum = mapPointArray[j].toObject().value("deviceInfo").toObject().value("ptzNum").toInt();
							QJsonArray ptzArray = mapPointArray[j].toObject().value("deviceInfo").toObject().value("ptzList").toArray();
							for (int k = 0; k < ptzNum; ++k)
							{
								PtzInfo ptzInfo_;
								panoMapList[i].panoramaList[j].cameraInfo.m_PtzInfoList.append(ptzInfo_);
								panoMapList[i].panoramaList[j].cameraInfo.m_PtzInfoList[k].sUserName = ptzArray[k].toObject().value("userName").toString();
								panoMapList[i].panoramaList[j].cameraInfo.m_PtzInfoList[k].sPasswd = ptzArray[k].toObject().value("passWd").toString();
								panoMapList[i].panoramaList[j].cameraInfo.m_PtzInfoList[k].sIP = ptzArray[k].toObject().value("ip").toString();
								panoMapList[i].panoramaList[j].cameraInfo.m_PtzInfoList[k].wPort = ptzArray[k].toObject().value("port").toInt();
								panoMapList[i].panoramaList[j].cameraInfo.m_PtzInfoList[k].pvsID = ptzArray[k].toObject().value("pvsId").toString();
								panoMapList[i].panoramaList[j].cameraInfo.m_PtzInfoList[k].m1Id = ptzArray[k].toObject().value("m1Id").toString();
							}

							int spyNum = mapPointArray[j].toObject().value("deviceInfo").toObject().value("spyNum").toInt();
							QJsonArray spyArray = mapPointArray[j].toObject().value("deviceInfo").toObject().value("spyList").toArray();
							for (int k = 0; k < spyNum; ++k)
							{
								SpyInfo spyInfo_;
								panoMapList[i].panoramaList[j].cameraInfo.m_SpyInfoList.append(spyInfo_);
								panoMapList[i].panoramaList[j].cameraInfo.m_SpyInfoList[k].sUserName = spyArray[k].toObject().value("userName").toString();
								panoMapList[i].panoramaList[j].cameraInfo.m_SpyInfoList[k].sPasswd = spyArray[k].toObject().value("passWd").toString();
								panoMapList[i].panoramaList[j].cameraInfo.m_SpyInfoList[k].sIP = spyArray[k].toObject().value("ip").toString();
								panoMapList[i].panoramaList[j].cameraInfo.m_SpyInfoList[k].wPort = spyArray[k].toObject().value("port").toInt();
								panoMapList[i].panoramaList[j].cameraInfo.m_SpyInfoList[k].pvsID = spyArray[k].toObject().value("pvsId").toString();
								panoMapList[i].panoramaList[j].cameraInfo.m_SpyInfoList[k].m1Id = spyArray[k].toObject().value("m1Id").toString();
								panoMapList[i].panoramaList[j].cameraInfo.m_SpyInfoList[k].pos_x = spyArray[k].toObject().value("posX").toDouble();
								panoMapList[i].panoramaList[j].cameraInfo.m_SpyInfoList[k].pos_y = spyArray[k].toObject().value("posY").toDouble();
							}

							panoMapList[i].panoramaList[j].sceneInfo.id = mapPointArray[j].toObject().value("sceneInfo").toObject().value("id").toInt();
							panoMapList[i].panoramaList[j].sceneInfo.name = mapPointArray[j].toObject().value("sceneInfo").toObject().value("sceneName").toString();
							panoMapList[i].panoramaList[j].sceneInfo.Path = mapPointArray[j].toObject().value("sceneInfo").toObject().value("scenePath").toString();

							int sceneNum = mapPointArray[j].toObject().value("sceneInfo").toObject().value("sceneNum").toInt();
							QJsonArray sceneArray = mapPointArray[j].toObject().value("sceneInfo").toObject().value("sceneGroups").toArray();
							for (int k = 0; k < sceneNum; ++k)
							{
								PanoSceneInfo temp_scene;
								panoMapList[i].panoramaList[j].sceneInfo.sceneList.append(temp_scene);
								panoMapList[i].panoramaList[j].sceneInfo.sceneList[k].id = sceneArray[k].toObject().value("id").toInt();
								panoMapList[i].panoramaList[j].sceneInfo.sceneList[k].name = sceneArray[k].toObject().value("pictureName").toString();
								panoMapList[i].panoramaList[j].sceneInfo.sceneList[k].Path = sceneArray[k].toObject().value("picturePath").toString();
								panoMapList[i].panoramaList[j].sceneInfo.sceneList[k].fileData = sceneArray[k].toObject().value("pictureData").toString();
							}
						}
					}
				}
			}
		}
	}
}

float commonFun::calculateLineSlope(QPoint startPoint, QPoint endPoint)
{
	if (startPoint.x() == endPoint.x())
	{
		if (endPoint.y() - startPoint.y() > 0)
		{
			return M_PI / 2;
		}
		else{
			return M_PI * 3 / 2;
		}
	}
	else
	{
		//最表远点在左上角，所以y需要负一下
		return atan2(startPoint.y() - endPoint.y(), endPoint.x() - startPoint.x());
	}
}

QString commonFun::readPTSData(QString deviceNo)
{
	QString pts_file_path = QDir::homePath() + "/AppData/Local/Pano-VMS/pts/" + deviceNo + "/pat.pts";
	QFile file(pts_file_path);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		Log::Info("read pts file open failed or pts file no exit!");
		return "";
	}
	QByteArray array = file.readAll();
	QString data(array);
	return data;
}

QString commonFun::fomatFromSecond(int val)
{
	QString fomat;
	int second = val % 60;
	int minute = (val / 60) % 60;
	int hour = (val / 60 / 60) % 24;

	QString secondStr = QString::number(second);
	QString minuteStr = QString::number(minute);
	QString hourStr = QString::number(hour);
	if (second / 10 == 0)
	{
		secondStr = QString("0%1").arg(second);
	}
	if (minute / 10 == 0)
	{
		minuteStr = QString("0%1").arg(minute);
	}
	if (hour / 10 == 0)
	{
		hourStr = QString("0%1").arg(hour);
	}

	fomat = QString("%1:%2:%3").arg(hourStr).arg(minuteStr).arg(secondStr);
	return fomat;
}

