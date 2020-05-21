/************************************************
* \file commonPageWgt.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* 控制台窗口定制的按钮
************************************************/
#ifndef COMMONPAGEWGT_H
#define COMMONPAGEWGT_H

#include <QWidget>

namespace Ui {
class commonPageWgt;
}

//控制台上的主按钮
class commonPageWgt : public QWidget
{
    Q_OBJECT

public:

	enum ConsoleButton
	{
		Play = 0,
		RePlay,
		Device,
		Storage,
		VRMap,
		VRView,
		IOTPlat,
	};

    explicit commonPageWgt(QWidget *parent = 0);
    ~commonPageWgt();

	//控制台设置标题和内容
	void setImageAndText(QString tittle, QString content, QString iconPath, commonPageWgt::ConsoleButton type);

protected:
	virtual void mousePressEvent(QMouseEvent *event);

signals:

	//控制台界面按钮控制主窗口界面信号
	void TrigConsoleButtonClicked(commonPageWgt::ConsoleButton type);

private:
    Ui::commonPageWgt *ui;

	commonPageWgt::ConsoleButton type_;
};

#endif // COMMONPAGEWGT_H
