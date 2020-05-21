#pragma once

#include <QString>
#include <QStringList>
#include <QDateTime>

#include "constStruct.h"

class commonFun
{
public:
	static unsigned int getDateTime(QString date);
	static unsigned int getDateTime(int time, QString date, int duration);
	static int timeExchange(QString time, int param);
	static unsigned int getStartTime(QString date);
	static unsigned int getEndTime(QString date);
	static QString getCurrentShowTime(int time);
	static QString getCurrentTipTime(int min);
	static QString getCurrentTimeBySscond(int time);
	static QString getCurrentTimeByPerSscond(int time);
	static int getMinFromStr(QString time); 
	static void yuv420sp_to_yuv420p(unsigned char* y, unsigned char* uv, unsigned char* y_tmp, unsigned char* u_tmp, unsigned char* v_tmp, int width, int height);
	static void yuv420p_to_yuv420sp(unsigned char* yuv420p, unsigned char* yuv420sp, int width, int height);
	static void generateToJsonFunc(const QList<PanoMap> &panoMapList);
	static void resolveFromJsonFunc(QList<PanoMap> &panoMapList);
	static float calculateLineSlope(QPoint startPoint, QPoint endPoint);
	static QString readPTSData(QString deviceNo);
	static QString fomatFromSecond(int val);
};