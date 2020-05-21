#ifndef PTZSETTINGSDLG_H
#define PTZSETTINGSDLG_H

#include <QDialog>
#include <QKeyEvent>
#include "ui_ptzSettingsDlg.h"

class ptzSettingsDlg : public QDialog
{
	Q_OBJECT
public:
	ptzSettingsDlg(QWidget *parent = 0);
	~ptzSettingsDlg();
	void setCurrData(QString IP, int port, QString user, QString passwd);   //设置当前数据
protected:
	void keyPressEvent(QKeyEvent *event);
signals:
	void sigOnBindPtz(QString ip, int port, QString user, QString passwd);     //绑定信号函数
private slots:
	void slotOnBindPtz();   //对话框绑定按钮槽函数
private:
	void initConnect();
	void init();
private:
	Ui::ptzSettingsDlg ui;
};

#endif // PTZSETTINGSDLG_H
