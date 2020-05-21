#ifndef ADDDEVICEDLG_H
#define ADDDEVICEDLG_H

#include <QDialog>
#include <QButtonGroup>
#include <QKeyEvent>
#include "constStruct.h"
#include "ui_addDeviceDlg.h"

class addDeviceDlg : public QDialog
{
	Q_OBJECT

public:
	addDeviceDlg(QWidget *parent = 0);
	~addDeviceDlg();
	void setTitleLabel(QString text);   //���ñ�����
	void clearData();    //��ձ༭������
	void setType(int type);
	void initPTZList(const QList<PtzInfo> &ptzInfoList);
	void initSPYList(const QList<SpyInfo> &spyInfoList);
	void setData(QString IP, int port, QString username, QString passwd);
protected:
	void keyPressEvent(QKeyEvent *event);
signals:
	void sigOnBindPtz(QString ip, int port, QString user, QString passwd, int type);     //���źź���
private slots:
	void slotOnConfirm();    //ȷ�ϲۺ���
	void slotOnPageChanged(int index);     //ѡ��ı�ۺ���
	void slotOnItemClicked(QListWidgetItem *item, QListWidgetItem *previousItem);
private:
	void init();
	void initConnect();
	void initListData();
private:
	Ui::addDeviceDlg ui;
	QButtonGroup *m_ctrlGroup;    //ѡ����ư�ť

	QList<PtzInfo> m_ptzInfoList;
	QList<SpyInfo> m_spyInfoList;
	PtzInfo m_curr_ptzInfo;
	SpyInfo m_curr_SpyInfo;
	int m_currType;
};

#endif // ADDDEVICEDLG_H
