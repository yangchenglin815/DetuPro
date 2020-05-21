#ifndef SERVERSETTINGWGT_H
#define SERVERSETTINGWGT_H

#include <QWidget>
#include <QMovie>
#include <QKeyEvent>
#include "ui_serverSettingWgt.h"

class serverSettingWgt : public QWidget
{
	Q_OBJECT

public:
	serverSettingWgt(QWidget *parent = 0);
	~serverSettingWgt();
	void serverConnectFailed();
private slots:
	void slotOnConfirm();
	void slotONReconnect();
	void slotModifyIP();
signals:
	void sigOnCancel();
	void sigOnConfirm();
protected:
	void keyPressEvent(QKeyEvent *event);
private:
	void initConnect();
	void init();
private:
	Ui::serverSettingWgt ui;
	QMovie *mov_;
};

#endif // SERVERSETTINGWGT_H
