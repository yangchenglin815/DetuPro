/************************************************
* \file lockDlg.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* Ëø¶¨Èí¼þµ¯¿ò
************************************************/
#ifndef LOCKDLG_H
#define LOCKDLG_H

#include <QDialog>
#include <QMouseEvent>
#include "ui_lockDlg.h"
#include <QPaintEvent>

class lockDlg : public QDialog
{
	Q_OBJECT

public:
	lockDlg(QWidget *parent = 0);
	~lockDlg();
signals:
	void sigOnUnlock();
protected:
	bool eventFilter(QObject *watched, QEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void closeEvent(QCloseEvent *event);
private:
	Ui::lockDlg ui;
};

#endif // LOCKDLG_H
