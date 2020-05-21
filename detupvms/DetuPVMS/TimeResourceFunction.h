/************************************************
 * \file TimeResourceFunction.h
 *
 * \author LiChangLing
 * \date 2017
 * 提供全局方法
 ************************************************/
#ifndef CURRENTTIME_H
#define CURRENTTIME_H
#pragma execution_character_set("utf-8")

#include <QtCore>

static qint64 CURRENT_TIME = 0;

namespace TimeResouceFunction
{
    static inline void SetCurrentTime(qint64 time)
    {
        CURRENT_TIME = time;
    }

    static inline qint64 GetCurrentTime()
    {
        return CURRENT_TIME;
    }

    //时间转换成字符串
    static inline QString TimeToString(qint64 time)
    {
        int hours = time / 3600;
        int minutes = (time - hours * 3600) / 60;
        int seconds = time % 60;

        QString hour = "";
        QString minute = "";
        QString second = "";

        hour = QString::number(hours);
        if (hours < 10)
        {
            hour.push_front("0");
        }

        minute = QString::number(minutes);
        if (minutes < 10)
        {
            minute.push_front("0");
        }

        second = QString::number(seconds);
        if (seconds < 10)
        {
            second.push_front("0");
        }

        return hour + ":" + minute + ":" + second;
    }
}

#endif