/************************************************
 * \file feedback.h
 *
 * \author LiChangLing
 * \date 2017
 * 弹出框消息控件
 ************************************************/
#pragma once
#pragma execution_character_set("utf-8")


#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <QObject>
#include <QDialog>

namespace Ui {
	class feedback;
}
class TypeBar;

//通用弹出框
class Feedback : public QDialog
{
	Q_OBJECT
public:
	explicit Feedback(QWidget *parent = 0);
	~Feedback();
	static Feedback* instance();
	void maskUI(int type);//遮罩
	void tipsUI(short errCode, std::string PVSId, unsigned char streamId);
	void setContent(QString path, QString str);
private:
	void initConnect();
	void setTipContent(int code, QString &path, QString &str);
	void setReportContent(int errCode, QString &tips, QString stream, std::string PVSId);
public:
	Ui::feedback* ui;
	static Feedback* m_pInstance;
};

#endif // FEEDBACK_H
