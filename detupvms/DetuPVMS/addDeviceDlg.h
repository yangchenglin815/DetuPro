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
	void setTitleLabel(QString text);   //设置标题栏
	void clearData();    //清空编辑区数据
	void setType(int type);
	void initPTZList(const QList<PtzInfo> &ptzInfoList);
	void initSPYList(const QList<SpyInfo> &spyInfoList);
	void setData(QString IP, int port, QString username, QString passwd);
protected:
	void keyPressEvent(QKeyEvent *event);
signals:
	void sigOnBindPtz(QString ip, int port, QString user, QString passwd, int type);     //绑定信号函数
private slots:
	void slotOnConfirm();    //确认槽函数
	void slotOnPageChanged(int index);     //选项卡改变槽函数
	void slotOnItemClicked(QListWidgetItem *item, QListWidgetItem *previousItem);
private:
	void init();
	void initConnect();
	void initListData();
private:
	Ui::addDeviceDlg ui;
	QButtonGroup *m_ctrlGroup;    //选项卡控制按钮

	QList<PtzInfo> m_ptzInfoList;
	QList<SpyInfo> m_spyInfoList;
	PtzInfo m_curr_ptzInfo;
	SpyInfo m_curr_SpyInfo;
	int m_currType;
};

#endif // ADDDEVICEDLG_H
