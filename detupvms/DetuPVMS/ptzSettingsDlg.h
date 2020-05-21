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
	void setCurrData(QString IP, int port, QString user, QString passwd);   //���õ�ǰ����
protected:
	void keyPressEvent(QKeyEvent *event);
signals:
	void sigOnBindPtz(QString ip, int port, QString user, QString passwd);     //���źź���
private slots:
	void slotOnBindPtz();   //�Ի���󶨰�ť�ۺ���
private:
	void initConnect();
	void init();
private:
	Ui::ptzSettingsDlg ui;
};

#endif // PTZSETTINGSDLG_H
