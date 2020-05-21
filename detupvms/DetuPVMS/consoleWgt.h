/************************************************
* \file consoleWgt.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* 控制面板窗口
************************************************/
#ifndef CONSOLEWGT_H
#define CONSOLEWGT_H

#include <QWidget>
#include "ui_consoleWgt.h"

namespace Ui {
class consoleWgt;
}

class consoleWgt : public QWidget
{
    Q_OBJECT

public:
    explicit consoleWgt(QWidget *parent = 0);
    ~consoleWgt();

signals:

	//控制台按钮控制主窗口界面信号转发
	void ConsoleButtonClicked(commonPageWgt::ConsoleButton type);
private:
	void init();
	void initConnect();
private:
    Ui::consoleWgt *ui;
};

#endif // CONSOLEWGT_H
